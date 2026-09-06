#pragma once

#include <Melon/String.hpp>

#include <variant>

namespace Cash
{
        class EvalValue
        {
                template<class... Ts>
                struct Overloaded : Ts...
                {
                        using Ts::operator()...;
                };

        public:
                std::variant<
                        std::monostate,
                        Melon::String::String,
                        int,
                        bool
                > value;
        
                Melon::String::String toString(this const EvalValue &self);
                int toInt(this const EvalValue &self);
        };

        inline constexpr EvalValue null_value = {std::monostate()};

        using eval_values_t = Melon::Vector::Vector<EvalValue>;
} // namespace Cahs