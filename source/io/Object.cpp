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
    void Object::throwDictionaryError(
        const std::string& key,
        const std::string& requested_type
    ) const {throw ObjectGetValueError(*this, key, requested_type);}

    Object::Object() {}

    bool Object::has(const std::string& key) const {return _map.find(key) != _map.end();}

    struct TypeNameVisitor
    {
        typedef std::string result_type;

        template <class Type>
        std::string operator()(const Type&) const {return TypeName<Type>()();}
    };

    std::string Object::type(const std::string& key) const {
        if (has(key)) {
            return boost::apply_visitor(TypeNameVisitor(), _map.at(key));
        } else {
            throw ObjectGetValueError(*this, key, "");
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
            result._map.begin(),
            result._map.end(),
            [&] (std::pair<const std::string, Variant>& key_value_pair) {
                boost::apply_visitor(TransformVisitor(matrix, vector), key_value_pair.second);
            }
        );
        return result;
    }

    std::string TypeName<Object>::operator()() const {return "Object";}

    class SerializationVisitor
    {
    private:
        SerializedObject::KeyValuePair* _key_value_pair;
    public:
        typedef void result_type;

        SerializationVisitor(SerializedObject::KeyValuePair* key_value_pair) :
            _key_value_pair(key_value_pair) {}

        void operator()(bool value) const {
            _key_value_pair->set_bool_value(value);
        }

        void operator()(int value) const {
            _key_value_pair->set_int_value(value);
        }

        void operator()(double value) const {
            _key_value_pair->set_double_value(value);
        }

        void operator()(const std::string& value) const {
            _key_value_pair->set_string_value(value);
        }

        void operator()(const Interval& value) const {
            Serialization<Interval> serialization;
            _key_value_pair->set_interval_value(serialization(value));
        }

        void operator()(const MatrixXd& value) const {
            Serialization<MatrixXd> serialization;
            _key_value_pair->set_matrixxd_value(serialization(value));
        }

        void operator()(const MatrixXI& value) const {
            Serialization<MatrixXI> serialization;
            _key_value_pair->set_matrixxi_value(serialization(value));

        }

        void operator()(const DatumXd& value) const {
            Serialization<DatumXd> serialization;
            _key_value_pair->set_datumxd_value(serialization(value));
        }

        void operator()(const SimplexXd& value) const {
            Serialization<SimplexXd> serialization;
            _key_value_pair->set_simplexxd_value(serialization(value));
        }

        void operator()(const Function& value) const {
            Serialization<Function> serialization;
            _key_value_pair->set_function_value(serialization(value));
        }

        void operator()(const Geometry& value) const {
            Serialization<Geometry> serialization;
            _key_value_pair->set_geometry_value(serialization(value));
        }

        void operator()(const Domain& value) const {
            Serialization<Domain> serialization;
            _key_value_pair->set_domain_value(serialization(value));
        }

        void operator()(const Object& value) const {
            Serialization<Object> serialization;
            _key_value_pair->set_object_value(serialization(value));
        }
    };

    std::string Serialization<Object>::operator()(const Object& argument) const {
        SerializedObject temp;
        for (auto i = argument._map.begin(); i != argument._map.end(); ++i) {
            SerializedObject::KeyValuePair* key_value_pair = temp.add_key_value_pair();
            key_value_pair->set_key(i->first);
            SerializationVisitor visitor(key_value_pair);
            boost::apply_visitor(visitor, i->second);
        }
        return temp.SerializeAsString();
    }

    Object Deserialization<Object>::operator()(const std::string& argument) const {
        SerializedObject temp;
        temp.ParseFromString(argument);
        Object result;
        for (int i = 0; i < temp.key_value_pair_size(); ++i) {
            const SerializedObject::KeyValuePair& key_value_pair = temp.key_value_pair(i);
            std::string key = key_value_pair.key();
            if (key_value_pair.has_bool_value()) {
                result.set(key, key_value_pair.bool_value());
            } else if (key_value_pair.has_int_value()) {
                result.set(key, key_value_pair.int_value());
            } else if (key_value_pair.has_double_value()) {
                result.set(key, key_value_pair.double_value());
            } else if (key_value_pair.has_string_value()) {
                result.set(key, key_value_pair.string_value());
            } else if (key_value_pair.has_interval_value()) {
                Deserialization<Interval> deserialization;
                result.set(key, deserialization(key_value_pair.interval_value()));
            } else if (key_value_pair.has_matrixxd_value()) {
                Deserialization<MatrixXd> deserialization;
                result.set(key, deserialization(key_value_pair.matrixxd_value()));
            } else if (key_value_pair.has_matrixxi_value()) {
                Deserialization<MatrixXI> deserialization;
                result.set(key, deserialization(key_value_pair.matrixxi_value()));
            } else if (key_value_pair.has_datumxd_value()) {
                Deserialization<DatumXd> deserialization;
                result.set(key, deserialization(key_value_pair.datumxd_value()));
            } else if (key_value_pair.has_simplexxd_value()) {
                Deserialization<SimplexXd> deserialization;
                result.set(key, deserialization(key_value_pair.simplexxd_value()));
            } else if (key_value_pair.has_function_value()) {
                Deserialization<Function> deserialization;
                result.set(key, deserialization(key_value_pair.function_value()));
            } else if (key_value_pair.has_geometry_value()) {
                Deserialization<Geometry> deserialization;
                result.set(key, deserialization(key_value_pair.geometry_value()));
            } else if (key_value_pair.has_domain_value()) {
                Deserialization<Domain> deserialization;
                result.set(key, deserialization(key_value_pair.domain_value()));
            } else if (key_value_pair.has_object_value()) {
                Deserialization<Object> deserialization;
                result.set(key, deserialization(key_value_pair.object_value()));
            }
        }
        return result;
    }

    ObjectGetValueError::ObjectGetValueError(
        const Object& object,
        const std::string& key,
        const std::string& requested_type
    ) : DictionaryError(key, requested_type), _object(object) {}

    const char* ObjectGetValueError::what() const throw() {
        return "ObjectGetValueError";
    }

    Object ObjectGetValueError::object() const {return _object;}
}
