#pragma once

#include <Cash/Ast.hpp>
#include <Cash/Symbol.hpp>
#include <Cash/Value.hpp>

#include <Melon/Conversion.hpp>

namespace Cash
{
        class Interpreter
        {
                ast_t nodes;
                eval_values_t eval_values;
                SymbolTable symbol_table;

        public:
                Interpreter() = default;
                Interpreter(const ast_t &nodes);

                void interpret(this Interpreter &self);
                EvalValue evaluate(this Interpreter &self, Node *const &node);
                void reset(this Interpreter &self);
                void setNodes(this Interpreter &self, const ast_t &new_nodes);

                const eval_values_t &getEvalValues(this const Interpreter &self);
        };
} // namespace Cash