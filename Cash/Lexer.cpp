#include <Cash/Lexer.hpp>

#include <Melon/String.hpp>
#include <Melon/Typing.hpp>
#include <Melon/FileSystem.hpp>
#include <utility>

using namespace Melon;

namespace Cash
{
        namespace
        {
                const char *token_type_strings[] = {
                        "Integer",
                        "Plus",
                        "Minus",
                        "Star",
                        "Slash",
                        "LeftParenthesis",
                        "RightParenthesis",
                        "EndOfFile"
                };
        } // anonymous namespace

        void Lexer::lex(this Lexer &self, const String::String &data)
        {
                self.tokens.clear();
                self.position = {0, 0};

                for (Typing::USize i = 0; i < data.length(); i++) {
                        bool found_integer = false;
                        String::String integer_buf;

                        ++self.position.column;

                        if (data[i] == '\n') {
                                self.position.column = 0;
                                ++self.position.row;
                                ++i;
                        }

                        // skip whitespaces, tabs and newlines
                        while (Typing::isSpace(data[i]))
                                ++i;

                        // handle integers
                        while (Typing::isDigit(data[i])) {
                                found_integer = true;
                                integer_buf.appendChar(data[i]);
                                ++i;
                                ++self.position.column;
                        }

                        if (found_integer) {
                                self.tokens.emplaceBack(self.position, TokenType::Integer);
                                found_integer = false;
                        }

                        switch (data[i]) {
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

        const Vector::Vector<Token> &Lexer::getTokens(this const Lexer &self)
        {
                return self.tokens;
        }

        String::String tokenTypeToString(TokenType toktype)
        {
                return token_type_strings[std::to_underlying(toktype)];
        }
} // namespace Cash