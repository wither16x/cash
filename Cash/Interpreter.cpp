#include <Cash/Ast.hpp>
#include <Cash/Token.hpp>
#include <Cash/Interpreter.hpp>

#include <Melon/Conversion.hpp>

using namespace Melon;

namespace Cash
{
        String::String EvalValue::toString(this const EvalValue &self)
        {
                return std::visit(overloaded{
                        [](std::monostate) {return String::String("null");},
                        [](Melon::String::String s) {return s;},
                        [](int i) {return Melon::Conversion::intToString(i, Melon::Conversion::Base::Decimal);}
                }, self.value);
        }

        Interpreter::Interpreter(const ast_t &nodes)
                : nodes(nodes)
        {}

        void Interpreter::interpret(this Interpreter &self)
        {
                self.reset();

                for (auto &nd : self.nodes)
                        self.eval_values.pushBack(self.evaluate(nd));
        }

        EvalValue Interpreter::evaluate(this Interpreter &self, Node *const &node)
        {
                if (isNodeType<Node>(node)) {
                        std::monostate null;
                        return {null};
                } else if (isNodeType<NodeExpr>(node)) {
                        std::monostate null;
                        return {null};
                } else if (isNodeType<NodeUnaryOp>(node)) {
                        NodeUnaryOp *unop_node = static_cast<NodeUnaryOp *>(node);
                        EvalValue val = self.evaluate(unop_node->value);

                        int int_val = Melon::Conversion::stringToInt<int>(val.toString());
                        
                        int result;
                        if (unop_node->op == TokenType::Plus)
                                result = +int_val;
                        else if (unop_node->op == TokenType::Minus)
                                result = -int_val;

                        EvalValue value = {
                                result
                        };
                        return value;
                } else if (isNodeType<NodeBinaryOp>(node)) {
                        NodeBinaryOp *binop_node = static_cast<NodeBinaryOp *>(node);
                        EvalValue left = self.evaluate(binop_node->left);
                        EvalValue right = self.evaluate(binop_node->right);

                        int left_val = Melon::Conversion::stringToInt<int>(left.toString());
                        int right_val = Melon::Conversion::stringToInt<int>(right.toString());

                        int result;
                        if (binop_node->op == TokenType::Plus)
                                result = left_val + right_val;
                        else if (binop_node->op == TokenType::Minus)
                                result = left_val - right_val;
                        else if (binop_node->op == TokenType::Star)
                                result = left_val * right_val;
                        else if (binop_node->op == TokenType::Slash)
                                result = left_val / right_val;

                        EvalValue value = {
                                result
                        };
                        return value;
                } else if (isNodeType<NodeInteger>(node)) {
                        NodeInteger *int_node = static_cast<NodeInteger *>(node);
                        EvalValue value = {
                                Melon::Conversion::stringToInt<int>(int_node->value)
                        };
                        return value;
                }

                std::monostate null;
                return {null};
        }

        void Interpreter::reset(this Interpreter &self)
        {
                self.eval_values.clear();
        }

        void Interpreter::setNodes(this Interpreter &self, const ast_t &new_nodes)
        {
                self.nodes = new_nodes;
        }

        const eval_values_t &Interpreter::getEvalValues(this const Interpreter &self)
        {
                return self.eval_values;
        }
} // namespace Cash