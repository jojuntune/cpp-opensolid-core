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

#include <OpenSolid/Core/Common/TypeName.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

namespace OpenSolid
{
    template <>
    struct Hash<Object::None>
    {
        std::size_t operator()(const Object::None&) {return 0;}
    };

    template <>
    struct TypeName<Object::None>
    {
        std::string operator()(const Object::None&) {return "None";}
    };

    Object::Object() {}

    Object::Object(int value) {_value = value;}

    Object::Object(double value) {_value = value;}

    Object::Object(const std::string& value) {_value = value;}

    Object::Object(const Interval& value) {_value = value;}

    Object::Object(const DatumXd& value) {_value = value;}

    Object::Object(const SimplexXd& value) {_value = value;}

    Object::Object(const Function& value) {_value = value;}

    Object::Object(const Geometry& value) {_value = value;}

    Object::Object(const Domain& value) {_value = value;}

    bool Object::hasValue() const {return !boost::get<None>(&_value);}

    struct TypeNameVisitor
    {
        typedef std::string result_type;

        template <class Type>
        std::string operator()(const Type& argument) {return TypeName<Type>()(argument);}
    };

    std::string Object::valueType() const {
        return boost::apply_visitor(TypeNameVisitor(), _value);
    }

    bool Object::has(const std::string& name) const {
        return _properties.find(name) != _properties.end();
    }

    void Object::set(const std::string& name, const Object& object) {_properties[name] = object;}

    Object Object::get(const std::string& name) const {
        if (has(name)) {
            return _properties.at(name);
        } else {
            throw ObjectPropertyError(*this, name);
        }
    }

    class TransformVisitor
    {
    private:
        const MatrixXd& _matrix;
        const VectorXd& _vector;
    public:
        typedef void result_type;

        TransformVisitor(const MatrixXd& matrix, const VectorXd& vector) :
            _matrix(matrix), _vector(vector) {}

        void operator()(Object::None&) const {}

        void operator()(int&) const {}

        void operator()(double&) const {}

        void operator()(std::string&) const {}

        void operator()(Interval&) const {}

        void operator()(MatrixXd& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(MatrixXI& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(DatumXd& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(SimplexXd& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(Function& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(Geometry& value) const {
            value = value.transformed(_matrix, _vector);
        }

        void operator()(Domain& value) const {
            value = value.transformed(_matrix, _vector);
        }
    };

    Object Object::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        Object result;
        result._value = _value;
        boost::apply_visitor(TransformVisitor(matrix, vector), result._value);
        for (auto i = _properties.begin(); i != _properties.end(); ++i) {
            result._properties[i->first] = i->second.transformed(matrix, vector);
        }
    }

    ObjectPropertyError::ObjectPropertyError(const Object& object, const std::string& name) :
        _object(object), _name(name) {}

    const char* ObjectPropertyError::what() const {
        return "ObjectPropertyError";
    }

    Object ObjectPropertyError::object() const {return _object;}

    std::string ObjectPropertyError::name() const {return _name;}


    ObjectConversionError::ObjectConversionError(
        const Object& object,
        const std::string& requested_type
    ) : _object(object), _requested_type(requested_type) {}

    const char* ObjectConversionError::what() const {
        return "ObjectConversionError";
    }

    Object ObjectConversionError::object() const {return _object;}

    std::string ObjectConversionError::requestedType() const {return _requested_type;}
}
