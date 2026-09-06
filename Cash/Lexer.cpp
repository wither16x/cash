#include <Cash/Lexer.hpp>
#include <Cash/Token.hpp>
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

        bool Lexer::lex(this Lexer &self)
        {
                self.reset();
                self.lexing = true;

                while (self.cursor < self.data.length() and self.lexing) {
                        // skip whitespaces, tabs and newlines
                        while (self.cursor < self.data.length() and self.foundBlank())
                                self.advance();

                        if (self.cursor >= self.data.length())
                                break;

                        Position start = self.position;
                        // handle integers
                        if (self.foundDigit()) {
                                self.curr_integer = "";
                                while (self.cursor < self.data.length() and self.lexing and self.foundDigit()) {
                                        self.curr_integer.appendChar(self.data[self.cursor]);
                                        self.advance();
                                }
                                self.tokens.emplaceBack(start, TokenType::Integer, self.curr_integer);
                                continue;
                        }

                        start = self.position;
                        // names start with a character or a _
                        if (isalpha(self.data[self.cursor]) or self.data[self.cursor] == '_') {
                                self.curr_name = "";
                                while (self.cursor < self.data.length() and self.lexing and (isalnum(self.data[self.cursor]) or self.data[self.cursor] == '_')) {
                                        self.curr_name.appendChar(self.data[self.cursor]);
                                        self.advance();
                                }

                                if (self.curr_name == TokenValues::Var) {
                                        self.tokens.emplaceBack(start, TokenType::Var, self.curr_name);
                                } else if (self.curr_name == TokenValues::Const) {
                                        self.tokens.emplaceBack(start, TokenType::Const, self.curr_name);
                                } else if (self.curr_name == TokenValues::True) {
                                        self.tokens.emplaceBack(start, TokenType::True, self.curr_name);
                                } else if (self.curr_name == TokenValues::False) {
                                        self.tokens.emplaceBack(start, TokenType::False, self.curr_name);
                                } else {
                                        self.tokens.emplaceBack(start, TokenType::Name, self.curr_name);
                                }
                                continue;
                        }

                        bool match =
                        self.handleToken(TokenValues::Plus, TokenType::Plus, "+")
                        or self.handleToken(TokenValues::Minus, TokenType::Minus, "-")
                        or self.handleToken(TokenValues::Star, TokenType::Star, "*")
                        or self.handleToken(TokenValues::Slash, TokenType::Slash, "/")
                        or self.handleToken(TokenValues::LeftParenthesis, TokenType::LeftParenthesis, "(")
                        or self.handleToken(TokenValues::RightParenthesis, TokenType::RightParenthesis, ")")
                        or self.handleToken(TokenValues::Equal, TokenType::Equal, "=")
                        or self.handleToken(FileSystem::EndOfFile, TokenType::EndOfFile, "EOF")
                        ;

                        if (not match)
                                self.error();
                }

                if (self.has_error)
                        return false;
                return true;
        }

        void Lexer::reset(this Lexer &self)
        {
                self.tokens.clear();
                self.cursor = 0;
                self.position = {0, 0};
                self.has_error = false;
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

        void Lexer::addToken(this Lexer &self, TokenType type, const String::String &value)
        {
                self.tokens.emplaceBack(self.position, type, value);
        }

        bool Lexer::handleToken(this Lexer &self, char expected, TokenType type, const Melon::String::String &value)
        {
                if (self.data[self.cursor] != expected)
                        return false;

                self.addToken(type, value);
                self.advance();
                return true;
        }

        void Lexer::error(this Lexer &self)
        {
                illegalCharacterError(self.data[self.cursor], self.position);
                self.lexing = false;
                self.has_error = true;
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