#include <Cash/Lexer.hpp>

#include <Melon/String.hpp>
#include <Melon/Typing.hpp>
#include <Melon/FileSystem.hpp>

using namespace Melon;

namespace Cash
{
        Lexer::Lexer(const String::String &data)
                : data(data)
        {}

        void Lexer::lex(this Lexer &self)
        {
                self.reset();

                for (; self.cursor < self.data.length(); self.cursor++) {
                        self.curr_integer = "";

                        self.advance();

                        // skip whitespaces, tabs and newlines
                        while (self.foundBlank())
                                self.advance();

                        // handle integers
                        while (self.foundDigit()) {
                                self.found_integer = true;
                                self.curr_integer.appendChar(self.data[self.cursor]);
                                ++self.cursor;
                                ++self.position.column;
                        }

                        if (self.found_integer) {
                                self.tokens.emplaceBack(self.position, TokenType::Integer);
                                self.found_integer = false;
                        }

                        switch (self.data[self.cursor]) {
                        case '+':
                                self.tokens.emplaceBack(self.position, TokenType::Plus);
                                break;

                        case '-':
                                self.tokens.emplaceBack(self.position, TokenType::Minus);
                                break;

                        case '*':
                                self.tokens.emplaceBack(self.position, TokenType::Star);
                                break;

                        case '/':
                                self.tokens.emplaceBack(self.position, TokenType::Slash);
                                break;

                        case '(':
                                self.tokens.emplaceBack(self.position, TokenType::LeftParenthesis);
                                break;

                        case ')':
                                self.tokens.emplaceBack(self.position, TokenType::RightParenthesis);
                                break;

                        case FileSystem::EndOfFile:
                                self.tokens.emplaceBack(self.position, TokenType::EndOfFile);
                                break;
                        }
                }
        }

        void Lexer::reset(this Lexer &self)
        {
                self.tokens.clear();
                self.cursor = 0;
                self.position = {0, 0};
        }

        void Lexer::advance(this Lexer &self)
        {
                ++self.position.column;

                if (self.data[self.cursor] == '\n') {
                        self.position.column = 0;
                        ++self.position.row;
                        ++self.cursor;
                }
        }

        void Lexer::setData(this Lexer &self, const String::String &new_data)
        {
                self.data = new_data;
        }

        bool Lexer::foundBlank(this const Lexer &self)
        {
                return Typing::isSpace(self.data[self.cursor]);
        }

        bool Lexer::foundDigit(this const Lexer &self)
        {
                return Typing::isDigit(self.data[self.cursor]);
        }

        const Vector::Vector<Token> &Lexer::getTokens(this const Lexer &self)
        {
                return self.tokens;
        }
} // namespace Cash