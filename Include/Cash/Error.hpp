#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>

namespace Cash
{
        void illegalCharacterError(char ch, Position pos);
        void syntaxError(const Melon::String::String &str, Position pos);
} // namespace Cash