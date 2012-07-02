/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/Common/List.hpp>

namespace opensolid
{
    Value::Value() : _value(0) {}

    Value::Value(bool argument) : _value(int(argument)) {}

    Value::Value(short argument) : _value(int(argument)) {}

    Value::Value(unsigned short argument) : _value(int(argument)) {}

    Value::Value(int argument) : _value(argument) {}

    Value::Value(unsigned argument) : _value(int(argument)) {}

    Value::Value(long argument) : _value(int(argument)) {}

    Value::Value(unsigned long argument) : _value(int(argument)) {}

    Value::Value(long long argument) : _value(int(argument)) {}

    Value::Value(unsigned long long argument) : _value(int(argument)) {}

    Value::Value(float argument) : _value(double(argument)) {}

    Value::Value(double argument) : _value(argument) {}

    Value::Value(long double argument) : _value(double(argument)) {}

    Value::Value(const char* argument) : _value(std::string(argument)) {}

    Value::Value(const std::string& argument) : _value(argument) {}

    Value::Value(const List& argument) : _value(argument) {}
    
    void Value::operator=(bool argument) {_value = int(argument);}

    void Value::operator=(short argument) {_value = int(argument);}

    void Value::operator=(unsigned short argument) {_value = int(argument);}

    void Value::operator=(int argument) {_value = argument;}

    void Value::operator=(unsigned argument) {_value = int(argument);}

    void Value::operator=(long argument) {_value = int(argument);}

    void Value::operator=(unsigned long argument) {_value = int(argument);}

    void Value::operator=(long long argument) {_value = int(argument);}

    void Value::operator=(unsigned long long argument) {_value = int(argument);}

    void Value::operator=(float argument) {_value = double(argument);}

    void Value::operator=(double argument) {_value = argument;}

    void Value::operator=(long double argument) {_value = double(argument);}
        
    void Value::operator=(const char* argument) {_value = std::string(argument);}

    void Value::operator=(const std::string& argument) {_value = argument;}

    void Value::operator=(const List& argument) {_value = argument;}

    struct TypeNameVisitor
    {
        typedef std::string result_type;

        template <class Type>
        std::string operator()(const Type&) const {return TypeName<Type>()();}
    };

    std::string Value::type() const {return accept(TypeNameVisitor());}
    
    ValueConversionError::ValueConversionError(
        const Value& value,
        const std::string& desired_type
    ) : _value(value), _desired_type(expected_type) {}

    Value ValueConversionError::value() const {return _value;}

    std::string ValueConversionError::desiredType() const {return _desired_type;}

    const char* ValueConversionError::what() const {
        return "ValueConversionError";
    }

    std::string TypeName<Value>::operator()() const {return "Value";}
    
    bool Conversion<Value, bool>::operator()(const Value& argument) const {
        return argument.convert<bool, int>();
    }

    short Conversion<Value, short>::operator()(const Value& argument) const {
        return argument.convert<short, int>();
    }

    unsigned short
    Conversion<Value, unsigned short>::operator()(const Value& argument) const {
        return argument.convert<unsigned short, int>();
    }

    int Conversion<Value, int>::operator()(const Value& argument) const {
        return argument.extract<int>();
    }

    unsigned Conversion<Value, unsigned>::operator()(const Value& argument) const {
        return argument.convert<unsigned, int>();
    }

    long Conversion<Value, long>::operator()(const Value& argument) const {
        return argument.convert<long, int>();
    }

    unsigned long Conversion<Value, unsigned long>::operator()(const Value& argument) const {
        return argument.convert<unsigned long, int>();
    }

    long long Conversion<Value, long long>::operator()(const Value& argument) const {
        return argument.convert<long long, int>();
    }

    unsigned long long
    Conversion<Value, unsigned long long>::operator()(const Value& argument) const {
        return argument.convert<unsigned long long, int>();
    }

    float Conversion<Value, float>::operator()(const Value& argument) const {
        return argument.convert<float, double>();
    }

    double Conversion<Value, double>::operator()(const Value& argument) const {
        return argument.extract<double>();
    }

    long double Conversion<Value, long double>::operator()(const Value& argument) const {
        return argument.convert<long double, double>();
    }

    const std::string&
    Conversion<Value, std::string>::operator()(const Value& argument) const {
        return argument.extract<std::string>();
    }
    
    const List& Conversion<Value, List>::operator()(const Value& argument) const {
        return argument.extract<List>();
    }
}
