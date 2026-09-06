#include <Cash/Value.hpp>

#include <Melon/Conversion.hpp>

using namespace Melon;

namespace Cash
{
        String::String EvalValue::toString(this const EvalValue &self)
        {
                return std::visit(Overloaded{
                        [](std::monostate) {return String::String("null");},
                        [](String::String s) {return s;},
                        [](int i) {return Conversion::intToString(i, Conversion::Base::Decimal);},
                        [](bool b) {return b ? String::String("true") : String::String("false");}
                }, self.value);
        }

        int EvalValue::toInt(this const EvalValue &self)
        {
                return std::visit(Overloaded{
                        [](std::monostate) {return 0;},
                        [](String::String s) {return Conversion::stringToInt<int>(s);},
                        [](int i) {return i;},
                        [](bool b) {return b ? 1 : 0;}
                }, self.value);
        }
} // namespace Cash