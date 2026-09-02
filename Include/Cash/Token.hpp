#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>

namespace Cash
{
        using tokens_t = Melon::Vector::Vector<struct Token>;

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

        namespace TokenValues
        {
                constexpr char Plus             = '+';
                constexpr char Minus            = '-';
                constexpr char Star             = '*';
                constexpr char Slash            = '/';
                constexpr char LeftParenthesis  = '(';
                constexpr char RightParenthesis = ')';
        } // namespace TokenValues

        struct Token
        {
                Position position;
                TokenType type;
                Melon::String::String value = "";
        };

        Melon::String::String tokenTypeToString(TokenType toktype);
} // namespace Cash