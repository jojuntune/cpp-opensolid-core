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
    void Object::throwPropertyError(
        const std::string& name,
        const std::string& requested_type
    ) const {throw ObjectPropertyError(*this, name, requested_type);}

    Object::Object() {}

    bool Object::has(const std::string& name) const {
        return _properties.find(name) != _properties.end();
    }

    struct TypeNameVisitor
    {
        typedef std::string result_type;

        template <class Type>
        std::string operator()(const Type&) const {return TypeName<Type>()();}
    };

    std::string Object::type(const std::string& name) const {
        if (has(name)) {
            return boost::apply_visitor(TypeNameVisitor(), _properties.at(name));
        } else {
            throw ObjectPropertyError(*this, name, "");
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

        void operator()(Object& value) const {
            value = value.transformed(_matrix, _vector);
        }
    };

    Object Object::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        Object result(*this);
        std::for_each(
            result._properties.begin(),
            result._properties.end(),
            [&] (std::pair<const std::string, Variant>& name_value_pair) {
                boost::apply_visitor(TransformVisitor(matrix, vector), name_value_pair.second);
            }
        );
        return result;
    }

    std::string TypeName<Object>::operator()() const {return "Object";}

    ObjectPropertyError::ObjectPropertyError(
        const Object& object,
        const std::string& name,
        const std::string& requested_type
    ) : PropertyError(name, requested_type), _object(object) {}

    const char* ObjectPropertyError::what() const {
        return "ObjectPropertyError";
    }

    Object ObjectPropertyError::object() const {return _object;}
}
