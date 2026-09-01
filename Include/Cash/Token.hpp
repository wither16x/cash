#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>

namespace Cash
{
        enum class TokenType
        {
                Integer,

                Plus,
                Minus,
                Star,
                Slash,

                LeftParenthesis,
                RightParenthesis,

                EndOfFile
        };

        struct Token
        {
                Position position;
                TokenType type;
                Melon::String::String value = "";
        };

        Melon::String::String tokenTypeToString(TokenType toktype);
} // namespace Cash