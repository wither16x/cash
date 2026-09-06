#pragma once

#include <Cash/Position.hpp>

#include <Melon/String.hpp>

namespace Cash
{
        using tokens_t = Melon::Vector::Vector<struct Token>;

        enum class TokenType
        {
                Integer,
                Name,

                Plus,
                Minus,
                Star,
                Slash,
                Equal,

                LeftParenthesis,
                RightParenthesis,

                Var,
                Const,
                True,
                False,

                EndOfFile
        };

        namespace TokenValues
        {
                constexpr char Plus             = '+';
                constexpr char Minus            = '-';
                constexpr char Star             = '*';
                constexpr char Slash            = '/';
                constexpr char Equal            = '=';

                constexpr char LeftParenthesis  = '(';
                constexpr char RightParenthesis = ')';

                constexpr char Var[]            = "var";
                constexpr char Const[]          = "const";
                constexpr char True[]           = "true";
                constexpr char False[]          = "false";
        } // namespace TokenValues

        struct Token
        {
                Position position;
                TokenType type;
                Melon::String::String value = "";
        };

        Melon::String::String tokenTypeToString(TokenType toktype);
} // namespace Cash