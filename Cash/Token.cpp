#include <Cash/Token.hpp>

#include <utility>

using namespace Melon;

namespace Cash
{
        namespace
        {
                const char *token_type_strings[] = {
                        "Integer",
                        "Name",
                        "Plus",
                        "Minus",
                        "Star",
                        "Slash",
                        "Equal",
                        "EqualEqual",
                        "NotEqual",
                        "LesserThan",
                        "GreaterThan",
                        "LesserThanEqual",
                        "GreaterThanEqual",
                        "LeftParenthesis",
                        "RightParenthesis",
                        "Var",
                        "Const",
                        "True",
                        "False",
                        "EndOfFile"
                };
        } // anonymous namespace

        String::String tokenTypeToString(TokenType toktype)
        {
                return token_type_strings[std::to_underlying(toktype)];
        }
} // namespace Cash