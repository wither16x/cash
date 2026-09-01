#pragma once

#include <Cash/Token.hpp>

#include <Melon/String.hpp>
#include <Melon/Fmt.hpp>

namespace Cash
{
        struct Node
        {
                virtual ~Node()
                {}

                inline virtual Melon::String::String info() const
                {
                        return "Node()";
                }
        };

        struct NodeExpr : Node
        {
                inline Melon::String::String info() const override
                {
                        return "NodeExpr()";
                }
        };

        struct NodeUnaryOp : NodeExpr
        {
                NodeExpr *value;
                TokenType op;

                inline Melon::String::String info() const override
                {
                        return Melon::Fmt::formatString("NodeUnaryOp(value={}, op={})",
                                this->value->info(), tokenTypeToString(this->op)
                        );
                }
        };

        struct NodeBinaryOp : NodeExpr
        {
                NodeExpr *left;
                NodeExpr *right;
                TokenType op;

                inline Melon::String::String info() const override
                {
                        return Melon::Fmt::formatString("NodeBinaryOp(left={}, right={}, op={})",
                                this->left->info(), this->right->info(), tokenTypeToString(this->op)
                        );
                }
        };

        struct NodeInteger : NodeExpr
        {
                Melon::String::String value;

                inline Melon::String::String info() const override
                {
                        return Melon::Fmt::formatString("NodeInteger(value={})",
                                this->value
                        );
                }
        };
} // namespace Cash