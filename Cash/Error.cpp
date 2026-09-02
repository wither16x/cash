#include <Cash/Error.hpp>

#include <Melon/Print.hpp>

using namespace Melon;

namespace Cash
{
        void illegalCharacterError(char ch, Position pos)
        {
                Print::println("error: illegal character '{}' at line {} and column {}",
                        ch, pos.row, pos.column
                );
        }

        void syntaxError(const Melon::String::String &str, Position pos)
        {
                Print::println("error: invalid syntax at '{}' at line {} and column {}",
                        str, pos.row, pos.column
                );
        }

        void alreadyDeclaredError(const Melon::String::String &name)
        {
                Print::println("error: symbol \"{}\" is already declared",
                        name
                );
        }

        void notDeclaredError(const Melon::String::String &name)
        {
                Print::println("error: symbol \"{}\" is not declared",
                        name
                );
        }
} // namespace Cash