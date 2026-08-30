#include <Cash/Repl.hpp>

#include <Melon/String.hpp>
#include <Melon/Input.hpp>
#include <Melon/Print.hpp>

using namespace Melon;

namespace Cash
{
        void repl()
        {
                bool running = true;

                while (running) {
                        String::String command = Input::input("cash> ");
                        Print::println("You entered {}.", command);
                }
        }
} // namespace Cash