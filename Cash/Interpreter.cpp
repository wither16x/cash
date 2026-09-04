#include <Cash/Ast.hpp>
#include <Cash/Token.hpp>
#include <Cash/Interpreter.hpp>
#include <Cash/Error.hpp>

#include <Melon/Conversion.hpp>

using namespace Melon;

namespace Cash
{
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
                        return null_value;
                } else if (isNodeType<NodeExpr>(node)) {
                        return null_value;
                } else if (isNodeType<NodeDecl>(node)) {
                        return null_value;
                } else if (isNodeType<NodeVarDecl>(node)) {
                        NodeVarDecl *vardecl_node = static_cast<NodeVarDecl *>(node);
                        EvalValue value = self.evaluate(vardecl_node->value);

                        Symbol symbol(
                                vardecl_node->name,
                                value,
                                SymbolType::Variable
                        );
                        if (not self.symbol_table.addSymbol(symbol))
                                return null_value;
                        
                        return value;
                } else if (isNodeType<NodeUnaryOp>(node)) {
                        NodeUnaryOp *unop_node = static_cast<NodeUnaryOp *>(node);
                        EvalValue val = self.evaluate(unop_node->value);

                        int int_val = val.toInt();
                        
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

                        int left_val = left.toInt();
                        int right_val = right.toInt();

                        int result;
                        if (binop_node->op == TokenType::Plus) {
                                result = left_val + right_val;
                        } else if (binop_node->op == TokenType::Minus) {
                                result = left_val - right_val;
                        } else if (binop_node->op == TokenType::Star) {
                                result = left_val * right_val;
                        } else if (binop_node->op == TokenType::Slash) {
                                if (right_val == 0) {
                                        divisionByZeroError(left_val);
                                        return null_value;
                                }
                                result = left_val / right_val;
                        }

                        EvalValue value = {
                                result
                        };
                        return value;
                } else if (isNodeType<NodeInteger>(node)) {
                        NodeInteger *int_node = static_cast<NodeInteger *>(node);

                        EvalValue value = {
                                Conversion::stringToInt<int>(int_node->value)
                        };
                        return value;
                } else if (isNodeType<NodeName>(node)) {
                        NodeName *name_node = static_cast<NodeName *>(node);
                        const Symbol &symbol = self.symbol_table.getSymbol(name_node->name);
                        if (not symbol.isDefined())
                                return null_value;

                        EvalValue value = symbol.value;
                        return value;
                } else if (isNodeType<NodeAssign>(node)) {
                        NodeAssign *assign_node = static_cast<NodeAssign *>(node);
                        EvalValue value = self.evaluate(assign_node->value);

                        if (not self.symbol_table.getSymbol(assign_node->name).isDefined())
                                return null_value;

                        self.symbol_table.setSymbolValue(assign_node->name, value);
                        return self.symbol_table.getSymbol(assign_node->name).value;
                }

                return null_value;
        }

        void Interpreter::reset(this Interpreter &self)
        {
                self.eval_values.clear();
                self.symbol_table.clear();
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