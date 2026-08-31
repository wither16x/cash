#pragma once

#include <Cash/Position.hpp>
#include <Cash/Token.hpp>

#include <Melon/Vector.hpp>
#include <Melon/String.hpp>

using namespace Melon;

namespace Cash
{
        class Lexer
        {
                Vector::Vector<Token> tokens;
                Position position;
                Typing::USize cursor;
                bool found_integer;
                String::String curr_integer;

        public:
                void lex(this Lexer &self, const String::String &data);
                void reset(this Lexer &self);
                void advance(this Lexer &self, char curr_ch);

                const Vector::Vector<Token> &getTokens(this const Lexer &self);
        };
} // namespace Cash