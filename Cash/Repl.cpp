#include <Cash/Repl.hpp>
#include <Cash/Lexer.hpp>
#include <Cash/Parser.hpp>
#include <Cash/Interpreter.hpp>

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
                Interpreter interpreter;

                bool running = true;

                while (running) {
                        String::String command = Input::input("cash> ");
                        lexer.setData(command);
                        lexer.lex();
                        
                        tokens_t tokens = lexer.getTokens();
                        parser.setTokens(tokens);
                        parser.parse();

                        ast_t nodes = parser.getNodes();
                        interpreter.setNodes(nodes);
                        interpreter.interpret();

                        for (auto &val : interpreter.getEvalValues())
                                Print::println("{}", val.toString());
                }
        }
} // namespace Cash