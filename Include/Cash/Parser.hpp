#pragma once

#include <Cash/Ast.hpp>
#include <Cash/Token.hpp>

#include <Melon/Vector.hpp>
#include <Melon/Typing.hpp>

namespace Cash
{
        class Parser
        {
                Melon::Vector::Vector<Node *> nodes;
                Melon::Vector::Vector<Token> tokens;
                Melon::Typing::USize token_cursor;
                Melon::Typing::USize node_cursor;

        public:
                Parser() = default;
                Parser(const Melon::Vector::Vector<Token> &tokens);

                void parse(this Parser &self);
                NodeExpr *parseExpr(this Parser &self);
                NodeExpr *parseTerm(this Parser &self);
                NodeExpr *parsePrimaryExpr(this Parser &self);
                NodeUnaryOp *parseUnaryOp(this Parser &self);
                NodeInteger *parseInteger(this Parser &self);

                void reset(this Parser &self);
                void setTokens(this Parser &self, const Melon::Vector::Vector<Token> &new_tokens);
        
                const Melon::Vector::Vector<Node *> &getNodes(this const Parser &self);
        };
} // namespace Cash