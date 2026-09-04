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

                if (NodeDecl *decl = self.parseDecl())
                        self.nodes.pushBack(decl);
                else if (NodeExpr *expr = self.parseExpr())
                        self.nodes.pushBack(expr);
        }

        NodeDecl *Parser::parseDecl(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length()) {
                        syntaxError(self.precedentToken().value, self.precedentToken().position);
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                if (self.expect(TokenType::Var)) {
                        ++self.token_cursor;
                        return self.parseVarDecl();
                }

                self.node_allocator.freeAll();
                return nullptr;
        }

        NodeVarDecl *Parser::parseVarDecl(this Parser &self)
        {
                Token name = self.currentToken();
                if (self.expect(TokenType::Name)) {
                        ++self.token_cursor;

                        if (self.token_cursor >= self.tokens.length()) {
                                self.node_allocator.freeAll();
                                return nullptr;
                        }

                        if (self.expect(TokenType::Equal)) {
                                ++self.token_cursor;
                                NodeExpr *value = self.parseExpr();

                                NodeVarDecl *node = self.node_allocator.allocateNode<NodeVarDecl>();
                                node->name = name.value;
                                node->value = value;

                                return node;
                        } else {
                                self.node_allocator.freeAll();
                                return nullptr;
                        }
                }

                self.node_allocator.freeAll();
                return nullptr;
        }

        NodeExpr *Parser::parseExpr(this Parser &self)
        {
                NodeExpr *left = self.parseTerm();
                if (not left) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                while (self.token_cursor < self.tokens.length()) {
                        TokenType op = self.currentToken().type;
                        if (not self.expect(TokenType::Plus) and not self.expect(TokenType::Minus))
                                break;

                        ++self.token_cursor;

                        NodeExpr *right = self.parseTerm();
                        if (not right) {
                                self.node_allocator.freeAll();
                                return nullptr;
                        }

                        NodeBinaryOp *node = self.node_allocator.allocateNode<NodeBinaryOp>();
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
                if (not left) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                while (self.token_cursor < self.tokens.length()) {
                        TokenType op = self.currentToken().type;
                        if (not self.expect(TokenType::Star) and not self.expect(TokenType::Slash))
                                break;

                        ++self.token_cursor;

                        NodeExpr *right = self.parsePrimaryExpr();
                        if (not right) {
                                self.node_allocator.freeAll();
                                return nullptr;
                        }

                        NodeBinaryOp *node = self.node_allocator.allocateNode<NodeBinaryOp>();
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
                        syntaxError(self.precedentToken().value, self.precedentToken().position);
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                if (self.expect(TokenType::Plus) or self.expect(TokenType::Minus))
                        return self.parseUnaryOp();

                if (self.expect(TokenType::LeftParenthesis)) {
                        ++self.token_cursor;

                        NodeExpr *inner = self.parseExpr();

                        if (self.token_cursor >= self.tokens.length() or not self.expect(TokenType::RightParenthesis)) {
                                syntaxError(self.precedentToken().value, self.precedentToken().position);
                                self.node_allocator.freeAll();
                                return nullptr;
                        }

                        ++self.token_cursor;

                        return inner;
                }

                if (NodeInteger *int_node = self.parseInteger())
                        return int_node;
                else if (NodeAssign *assign_node = self.parseAssign())
                        return assign_node;
                return self.parseName();
        }

        NodeUnaryOp *Parser::parseUnaryOp(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length()) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                if (not self.expect(TokenType::Plus) and not self.expect(TokenType::Minus)) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                ++self.token_cursor;

                NodeExpr *value = self.parsePrimaryExpr();
                if (not value) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                NodeUnaryOp *node = self.node_allocator.allocateNode<NodeUnaryOp>();
                node->value = value;
                node->op = self.precedentToken().type;

                return node;
        }

        NodeInteger *Parser::parseInteger(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length()) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                if (self.expect(TokenType::Integer)) {
                        ++self.token_cursor;

                        NodeInteger *node = self.node_allocator.allocateNode<NodeInteger>();
                        node->value = self.precedentToken().value;

                        return node;
                }

                self.node_allocator.freeAll();
                return nullptr;
        };

        NodeName *Parser::parseName(this Parser &self)
        {
                if (self.token_cursor >= self.tokens.length()) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                if (self.expect(TokenType::Name)) {
                        ++self.token_cursor;

                        NodeName *node = self.node_allocator.allocateNode<NodeName>();
                        node->name = self.precedentToken().value;

                        return node;
                }

                self.node_allocator.freeAll();
                return nullptr;
        }

        NodeAssign *Parser::parseAssign(this Parser &self)
        {
                Typing::USize start_cursor = self.token_cursor;

                if (self.token_cursor >= self.tokens.length()) {
                        self.node_allocator.freeAll();
                        return nullptr;
                }

                Token name = self.currentToken();
                if (self.expect(TokenType::Name)) {
                        ++self.token_cursor;

                        if (self.token_cursor >= self.tokens.length()) {
                                self.token_cursor = start_cursor;
                                self.node_allocator.freeAll();
                                return nullptr;
                        }

                        if (self.expect(TokenType::Equal)) {
                                ++self.token_cursor;

                                NodeExpr *value = self.parseExpr();
                                if (value) {
                                        NodeAssign *node = self.node_allocator.allocateNode<NodeAssign>();
                                        node->name = name.value;
                                        node->value = value;

                                        return node;
                                }
                        }
                }

                self.token_cursor = start_cursor;
                self.node_allocator.freeAll();
                return nullptr;
        }

        void Parser::reset(this Parser &self)
        {
                self.token_cursor = 0;
                self.node_cursor = 0;
                self.nodes.clear();
                self.node_allocator.freeAll();
        }

        void Parser::setTokens(this Parser &self, const tokens_t &new_tokens)
        {
                self.tokens = new_tokens;
        }

        bool Parser::expect(this const Parser &self, TokenType token)
        {
                if (self.token_cursor >= self.tokens.length())
                        return false;
                return self.currentToken().type == token;
        }

        const ast_t &Parser::getNodes(this const Parser &self)
        {
                return self.nodes;
        }
} // namespace Cash