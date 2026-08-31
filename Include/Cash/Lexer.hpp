#pragma once

#include <Cash/Position.hpp>

#include <Melon/Vector.hpp>
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
        };

        class Lexer
        {
                Vector::Vector<Token> tokens;
                Position position;

        public:
                void lex(this Lexer &self, const String::String &data);

                const Vector::Vector<Token> &getTokens(this const Lexer &self);
        };

        String::String tokenTypeToString(TokenType toktype);
} // namespace Cash