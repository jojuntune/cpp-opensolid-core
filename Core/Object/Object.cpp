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
#include <OpenSolid/Core/Object/SerializedObject.pb.h>

namespace opensolid
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

        void operator()(bool&) const {}

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

    class SerializationVisitor
    {
    private:
        SerializedObject::NameValuePair* _name_value_pair;
    public:
        typedef void result_type;

        SerializationVisitor(SerializedObject::NameValuePair* name_value_pair) :
            _name_value_pair(name_value_pair) {}

        void operator()(bool value) const {
            _name_value_pair->set_bool_value(value);
        }

        void operator()(int value) const {
            _name_value_pair->set_int_value(value);
        }

        void operator()(double value) const {
            _name_value_pair->set_double_value(value);
        }

        void operator()(const std::string& value) const {
            _name_value_pair->set_string_value(value);
        }

        void operator()(const Interval& value) const {
            Serialization<Interval> serialization;
            _name_value_pair->set_interval_value(serialization(value));
        }

        void operator()(const MatrixXd& value) const {
            Serialization<MatrixXd> serialization;
            _name_value_pair->set_matrixxd_value(serialization(value));
        }

        void operator()(const MatrixXI& value) const {
            Serialization<MatrixXI> serialization;
            _name_value_pair->set_matrixxi_value(serialization(value));

        }

        void operator()(const DatumXd& value) const {
            Serialization<DatumXd> serialization;
            _name_value_pair->set_datumxd_value(serialization(value));
        }

        void operator()(const SimplexXd& value) const {
            Serialization<SimplexXd> serialization;
            _name_value_pair->set_simplexxd_value(serialization(value));
        }

        void operator()(const Function& value) const {
            Serialization<Function> serialization;
            _name_value_pair->set_function_value(serialization(value));
        }

        void operator()(const Geometry& value) const {
            Serialization<Geometry> serialization;
            _name_value_pair->set_geometry_value(serialization(value));
        }

        void operator()(const Domain& value) const {
            Serialization<Domain> serialization;
            _name_value_pair->set_domain_value(serialization(value));
        }

        void operator()(const Object& value) const {
            Serialization<Object> serialization;
            _name_value_pair->set_object_value(serialization(value));
        }
    };

    std::string Serialization<Object>::operator()(const Object& argument) const {
        SerializedObject temp;
        for (auto i = argument._properties.begin(); i != argument._properties.end(); ++i) {
            SerializedObject::NameValuePair* name_value_pair = temp.add_name_value_pair();
            name_value_pair->set_name(i->first);
            SerializationVisitor visitor(name_value_pair);
            boost::apply_visitor(visitor, i->second);
        }
        return temp.SerializeAsString();
    }

    Object Deserialization<Object>::operator()(const std::string& argument) const {
        SerializedObject temp;
        temp.ParseFromString(argument);
        Object result;
        for (int i = 0; i < temp.name_value_pair_size(); ++i) {
            const SerializedObject::NameValuePair& name_value_pair = temp.name_value_pair(i);
            std::string name = name_value_pair.name();
            if (name_value_pair.has_bool_value()) {
                result.set(name, name_value_pair.bool_value());
            } else if (name_value_pair.has_int_value()) {
                result.set(name, name_value_pair.int_value());
            } else if (name_value_pair.has_double_value()) {
                result.set(name, name_value_pair.double_value());
            } else if (name_value_pair.has_string_value()) {
                result.set(name, name_value_pair.string_value());
            } else if (name_value_pair.has_interval_value()) {
                Deserialization<Interval> deserialization;
                result.set(name, deserialization(name_value_pair.interval_value()));
            } else if (name_value_pair.has_matrixxd_value()) {
                Deserialization<MatrixXd> deserialization;
                result.set(name, deserialization(name_value_pair.matrixxd_value()));
            } else if (name_value_pair.has_matrixxi_value()) {
                Deserialization<MatrixXI> deserialization;
                result.set(name, deserialization(name_value_pair.matrixxi_value()));
            } else if (name_value_pair.has_datumxd_value()) {
                Deserialization<DatumXd> deserialization;
                result.set(name, deserialization(name_value_pair.datumxd_value()));
            } else if (name_value_pair.has_simplexxd_value()) {
                Deserialization<SimplexXd> deserialization;
                result.set(name, deserialization(name_value_pair.simplexxd_value()));
            } else if (name_value_pair.has_function_value()) {
                Deserialization<Function> deserialization;
                result.set(name, deserialization(name_value_pair.function_value()));
            } else if (name_value_pair.has_geometry_value()) {
                Deserialization<Geometry> deserialization;
                result.set(name, deserialization(name_value_pair.geometry_value()));
            } else if (name_value_pair.has_domain_value()) {
                Deserialization<Domain> deserialization;
                result.set(name, deserialization(name_value_pair.domain_value()));
            } else if (name_value_pair.has_object_value()) {
                Deserialization<Object> deserialization;
                result.set(name, deserialization(name_value_pair.object_value()));
            }
        }
        return result;
    }

    ObjectPropertyError::ObjectPropertyError(
        const Object& object,
        const std::string& name,
        const std::string& requested_type
    ) : PropertyError(name, requested_type), _object(object) {}

    const char* ObjectPropertyError::what() const throw() {
        return "ObjectPropertyError";
    }

    Object ObjectPropertyError::object() const {return _object;}
}
