#include <Cash/Lexer.hpp>

#include <Melon/String.hpp>
#include <Melon/Typing.hpp>
#include <Melon/FileSystem.hpp>

using namespace Melon;

namespace Cash
{
        void Lexer::lex(this Lexer &self, const String::String &data)
        {
                self.reset();

                for (; self.cursor < data.length(); self.cursor++) {
                        self.curr_integer = "";

                        self.advance(data[self.cursor]);

                        // skip whitespaces, tabs and newlines
                        while (Typing::isSpace(data[self.cursor]))
                                self.advance(data[self.cursor]);

                        // handle integers
                        while (Typing::isDigit(data[self.cursor])) {
                                self.found_integer = true;
                                self.curr_integer.appendChar(data[self.cursor]);
                                ++self.cursor;
                                ++self.position.column;
                        }

                        if (self.found_integer) {
                                self.tokens.emplaceBack(self.position, TokenType::Integer);
                                self.found_integer = false;
                        }

                        switch (data[self.cursor]) {
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

        void Lexer::advance(this Lexer &self, char curr_ch)
        {
                ++self.position.column;

                if (curr_ch == '\n') {
                        self.position.column = 0;
                        ++self.position.row;
                        ++self.cursor;
                }
        }

        const Vector::Vector<Token> &Lexer::getTokens(this const Lexer &self)
        {
                return self.tokens;
        }
} // namespace Cash