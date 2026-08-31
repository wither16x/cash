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
} // namespace Cash