#include <Cash/Value.hpp>

#include <Melon/Conversion.hpp>

using namespace Melon;

namespace Cash
{
        String::String EvalValue::toString(this const EvalValue &self)
        {
                return std::visit(overloaded{
                        [](std::monostate) {return String::String("null");},
                        [](String::String s) {return s;},
                        [](int i) {return Conversion::intToString(i, Conversion::Base::Decimal);}
                }, self.value);
        }

        int EvalValue::toInt(this const EvalValue &self)
        {
                return std::visit(overloaded{
                        [](std::monostate) {return 0;},
                        [](String::String s) {return Conversion::stringToInt<int>(s);},
                        [](int i) {return i;}
                }, self.value);
        }
} // namespace Cash