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
                String::String data;

        public:
                Lexer(const String::String &data = "");

                void lex(this Lexer &self);
                void reset(this Lexer &self);
                void advance(this Lexer &self);
                void setData(this Lexer &self, const String::String &new_data);

                bool foundBlank(this const Lexer &self);
                bool foundDigit(this const Lexer &self);

                const Vector::Vector<Token> &getTokens(this const Lexer &self);
        };
} // namespace Cash