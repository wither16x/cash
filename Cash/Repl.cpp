#include <Cash/Repl.hpp>
#include <Cash/Lexer.hpp>

#include <Melon/String.hpp>
#include <Melon/Input.hpp>
#include <Melon/Print.hpp>

using namespace Melon;

namespace Cash
{
        void repl()
        {
                Lexer lexer;

                bool running = true;

                while (running) {
                        String::String command = Input::input("cash> ");
                        lexer.lex(command);

                        for (auto &tok : lexer.getTokens())
                                Print::println("Token {} found at {};{}", tokenTypeToString(tok.type), tok.position.column, tok.position.row);
                }
        }
} // namespace Cash