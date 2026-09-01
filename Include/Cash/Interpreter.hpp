#pragma once

#include <Cash/Ast.hpp>

#include <Melon/Conversion.hpp>

#include <variant>

namespace Cash
{
        class EvalValue {
                template<class... Ts>
                struct overloaded : Ts...
                {
                        using Ts::operator()...;
                };

        public:
                std::variant<
                        std::monostate,
                        Melon::String::String,
                        int
                > value;
        
                Melon::String::String toString(this const EvalValue &self);
                int toInt(this const EvalValue &self);
        };

        inline constexpr EvalValue null_value = {std::monostate()};

        using eval_values_t = Melon::Vector::Vector<EvalValue>;

        class Interpreter
        {
                ast_t nodes;
                eval_values_t eval_values;

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