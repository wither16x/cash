#pragma once

#include <Cash/Position.hpp>
#include <Cash/Token.hpp>

#include <Melon/Vector.hpp>
#include <Melon/String.hpp>

namespace Cash
{
        class Lexer
        {
                Melon::Vector::Vector<Token> tokens;
                Position position;
                Melon::Typing::USize cursor;
                Melon::String::String curr_integer;
                Melon::String::String data;

        public:
                Lexer(const Melon::String::String &data = "");

                void lex(this Lexer &self);
                void reset(this Lexer &self);
                void advance(this Lexer &self);
                void setData(this Lexer &self, const Melon::String::String &new_data);

                bool foundBlank(this const Lexer &self);
                bool foundDigit(this const Lexer &self);

                const Melon::Vector::Vector<Token> &getTokens(this const Lexer &self);
        };
} // namespace Cash