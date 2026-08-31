#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>

using namespace Melon;

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
                String::String value = "";
        };

        String::String tokenTypeToString(TokenType toktype);
} // namespace Cash