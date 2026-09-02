#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>
#include <Melon/Print.hpp>

namespace Cash
{
        void illegalCharacterError(char ch, Position pos);
        void syntaxError(const Melon::String::String &str, Position pos);

        template<typename T>
        void divisionByZeroError(T x)
        {
                Melon::Print::println("error: cannot divide {} by zero",
                        x
                );
        }
} // namespace Cash