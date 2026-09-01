#include <Cash/Parser.hpp>
#include <Cash/Token.hpp>
#include <Cash/Ast.hpp>
#include <Cash/Error.hpp>

using namespace Melon;

namespace Cash
{
        Parser::Parser(const tokens_t &tokens)
                : tokens(tokens)
        {}

        void Parser::parse(this Parser &self)
        {
                self.reset();

                NodeExpr *expr = self.parseExpr();
                if (expr)
                        self.nodes.pushBack(expr);
        }

        NodeExpr *Parser::parseExpr(this Parser &self)
        {
                NodeExpr *left = self.parseTerm();
                if (not left)
                        return nullptr;

                while (self.token_cursor < self.tokens.length()) {
                        TokenType op = self.tokens[self.token_cursor].type;
                        if (op != TokenType::Plus and op != TokenType::Minus)
                                break;

                        ++self.token_cursor;

                        NodeExpr *right = self.parseTerm();
                        if (not right) {
                                delete left;
                                        return nullptr;
                        }

                        NodeBinaryOp *node = new NodeBinaryOp;
                        node->left = left;
                        node->right = right;
                        node->op = op;

                        left = node;
                }

                return left;
        }

        NodeExpr *Parser::parseTerm(this Parser &self)
        {
                NodeExpr *left = self.parsePrimaryExpr();
                if (not left)
                        return nullptr;

                while (self.token_cursor < self.tokens.length()) {
                        TokenType op = self.tokens[self.token_cursor].type;
                        if (op != TokenType::Star and op != TokenType::Slash)
                                break;

                        ++self.token_cursor;

                        NodeExpr *right = self.parsePrimaryExpr();
                        if (not right) {
                                delete left;
                                return nullptr;
                        }

                        NodeBinaryOp *node = new NodeBinaryOp;
                        node->left = left;
                        node->right = right;
                        node->op = op;

                        left = node;
                }

                return left;
        }

        NodeExpr *Parser::parsePrimaryExpr(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length()) {
                        syntaxError(self.tokens[self.token_cursor - 1].value, self.tokens[self.token_cursor - 1].position);
                        return nullptr;
                }

                Token tok = self.tokens[self.token_cursor];
                if (tok.type == TokenType::Plus or tok.type == TokenType::Minus)
                        return self.parseUnaryOp();

                if (tok.type == TokenType::LeftParenthesis) {
                        ++self.token_cursor;

                        NodeExpr *inner = self.parseExpr();

                        if (self.token_cursor >= self.tokens.length() or self.tokens[self.token_cursor].type != TokenType::RightParenthesis) {
                                delete inner;
                                syntaxError(self.tokens[self.token_cursor - 1].value, self.tokens[self.token_cursor - 1].position);
                                return nullptr;
                        }

                        ++self.token_cursor;

                        return inner;
                }

                return self.parseInteger();
        }

        NodeUnaryOp *Parser::parseUnaryOp(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length())
                        return nullptr;

                Token tok = self.tokens[self.token_cursor];
                if (tok.type != TokenType::Plus and tok.type != TokenType::Minus)
                        return nullptr;

                ++self.token_cursor;

                NodeExpr *value = self.parsePrimaryExpr();
                if (not value)
                        return nullptr;

                NodeUnaryOp *node = new NodeUnaryOp;
                node->value = value;
                node->op = tok.type;

                return node;
        }

        NodeInteger *Parser::parseInteger(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length())
                        return nullptr;

                Token tok = self.tokens[self.token_cursor];
                if (tok.type == TokenType::Integer) {
                        ++self.token_cursor;

                        NodeInteger *node = new NodeInteger;
                        node->value = tok.value;

                        return node;
                }

                return nullptr;
        };

        void Parser::reset(this Parser &self)
        {
                self.token_cursor = 0;
                self.node_cursor = 0;
                self.nodes.clear();
        }

        void Parser::setTokens(this Parser &self, const tokens_t &new_tokens)
        {
                self.tokens = new_tokens;
        }

        const ast_t &Parser::getNodes(this const Parser &self)
        {
                return self.nodes;
        }
} // namespace Cash