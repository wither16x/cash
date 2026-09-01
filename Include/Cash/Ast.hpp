#pragma once

#include <Cash/Token.hpp>

#include <Melon/String.hpp>
#include <Melon/Fmt.hpp>

namespace Cash
{
        using ast_t = Melon::Vector::Vector<struct Node *>;

        enum class NodeType
        {
                Node,
                Expr,
                UnaryOp,
                BinaryOp,
                Integer
        };

        struct Node
        {
                NodeType type = NodeType::Node;

                virtual ~Node()
                {}

                inline virtual Melon::String::String info() const
                {
                        return "Node()";
                }
        };

        struct NodeExpr : Node
        {
                NodeType type = NodeType::Expr;

                inline Melon::String::String info() const override
                {
                        return "NodeExpr()";
                }
        };

        struct NodeUnaryOp : NodeExpr
        {
                NodeType type = NodeType::UnaryOp;

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
                NodeType type = NodeType::BinaryOp;

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
                NodeType type = NodeType::Integer;

                Melon::String::String value;

                inline Melon::String::String info() const override
                {
                        return Melon::Fmt::formatString("NodeInteger(value={})",
                                this->value
                        );
                }
        };
} // namespace Cash