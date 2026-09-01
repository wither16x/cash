#include <Cash/Repl.hpp>
#include <Cash/Lexer.hpp>
#include <Cash/Parser.hpp>

#include <Melon/String.hpp>
#include <Melon/Input.hpp>
#include <Melon/Print.hpp>

using namespace Melon;

namespace Cash
{
        void repl()
        {
                Lexer lexer;
                Parser parser;

                bool running = true;

                while (running) {
                        String::String command = Input::input("cash> ");
                        lexer.setData(command);
                        lexer.lex();
                        
                        auto tokens = lexer.getTokens();
                        parser.setTokens(tokens);
                        parser.parse();

                        for (auto &nd : parser.getNodes())
                                Print::println("Node {}", nd->info());
                }
        }
} // namespace Cash