#include <Melon/Print.hpp>

#include <Cash/Repl.hpp>

using namespace Melon;

int main(int argc, char **argv)
{
        if (argc < 2)
                Cash::repl();

        return 0;
}