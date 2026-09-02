#include "Cash/Token.hpp"
#include <Cash/Lexer.hpp>
#include <Cash/Error.hpp>

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

                while (self.cursor < self.data.length()) {
                        // skip whitespaces, tabs and newlines
                        while (self.cursor < self.data.length() and self.foundBlank())
                                self.advance();

                        if (self.cursor >= self.data.length())
                                break;

                        Position start = self.position;

                        // handle integers
                        if (self.foundDigit()) {
                                self.curr_integer = "";
                                while (self.cursor < self.data.length() and self.foundDigit()) {
                                        self.curr_integer.appendChar(self.data[self.cursor]);
                                        self.advance();
                                }
                                self.tokens.emplaceBack(start, TokenType::Integer, self.curr_integer);
                                continue;
                        }

                        switch (self.data[self.cursor]) {
                        case TokenValues::Plus:
                                self.tokens.emplaceBack(self.position, TokenType::Plus, "+");
                                self.advance();
                                break;

                        case TokenValues::Minus:
                                self.tokens.emplaceBack(self.position, TokenType::Minus, "-");
                                self.advance();
                                break;

                        case TokenValues::Star:
                                self.tokens.emplaceBack(self.position, TokenType::Star, "*");
                                self.advance();
                                break;

                        case TokenValues::Slash:
                                self.tokens.emplaceBack(self.position, TokenType::Slash, "/");
                                self.advance();
                                break;

                        case TokenValues::LeftParenthesis:
                                self.tokens.emplaceBack(self.position, TokenType::LeftParenthesis, "(");
                                self.advance();
                                break;

                        case TokenValues::RightParenthesis:
                                self.tokens.emplaceBack(self.position, TokenType::RightParenthesis, ")");
                                self.advance();
                                break;

                        case FileSystem::EndOfFile:
                                self.tokens.emplaceBack(self.position, TokenType::EndOfFile, "EOF");
                                break;

                        case '\0':
                                break;

                        default:
                                illegalCharacterError(self.data[self.cursor], self.position);
                                self.advance();
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
                if (self.data[self.cursor] == '\n') {
                        self.position.column = 0;
                        ++self.position.row;
                } else {
                        ++self.position.column;
                }

                ++self.cursor;
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