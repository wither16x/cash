#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>
#include <Melon/Print.hpp>

namespace Cash
{
        void illegalCharacterError(char ch, Position pos);
        void syntaxError(const Melon::String::String &str, Position pos);
        void alreadyDeclaredError(const Melon::String::String &name);
        void notDeclaredError(const Melon::String::String &name);
        void isConstantError(const Melon::String::String &name);

        template<typename T>
        void divisionByZeroError(T x)
        {
                Melon::Print::println("error: cannot divide {} by zero",
                        x
                );
        }
} // namespace Cash