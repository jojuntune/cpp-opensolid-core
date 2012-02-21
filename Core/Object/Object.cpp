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
    struct TypeName<Object::None>
    {
        std::string operator()() {return "None";}
    };

    template <class Type>
    Type Object::extract() const {
        try {
            return boost::get<Type>(_value);
        } catch (const boost::bad_get&) {
            throw ObjectConversionError(*this, TypeName<Type>()());
        }
    }

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
        std::string operator()(const Type&) const {return TypeName<Type>()();}
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
        return result;
    }

    int Conversion<Object, int>::operator()(const Object& object) const {
        return object.extract<int>();
    }

    double Conversion<Object, double>::operator()(const Object& object) const {
        return object.extract<double>();
    }

    std::string Conversion<Object, std::string>::operator()(const Object& object) const {
        return object.extract<std::string>();
    }

    Interval Conversion<Object, Interval>::operator()(const Object& object) const {
        return object.extract<Interval>();
    }

    MatrixXd Conversion<Object, MatrixXd>::operator()(const Object& object) const {
        return object.extract<MatrixXd>();
    }

    MatrixXI Conversion<Object, MatrixXI>::operator()(const Object& object) const {
        return object.extract<MatrixXI>();
    }

    DatumXd Conversion<Object, DatumXd>::operator()(const Object& object) const {
        return object.extract<DatumXd>();
    }

    SimplexXd Conversion<Object, SimplexXd>::operator()(const Object& object) const {
        return object.extract<SimplexXd>();
    }

    Function Conversion<Object, Function>::operator()(const Object& object) const {
        return object.extract<Function>();
    }

    Geometry Conversion<Object, Geometry>::operator()(const Object& object) const {
        return object.extract<Geometry>();
    }

    Domain Conversion<Object, Domain>::operator()(const Object& object) const {
        return object.extract<Domain>();
    }

    template <class MatrixType>
    MatrixType convertToMatrix(const Object& object) {
        typedef Matrix<typename MatrixType::Scalar, Dynamic, Dynamic> DynamicMatrixType;
        DynamicMatrixType dynamic_matrix;
        try {
            dynamic_matrix = object.as<DynamicMatrixType>();
        } catch (const ObjectConversionError&) {
            throw ObjectConversionError(object, TypeName<MatrixType>()());
        }
        int compile_time_rows = MatrixType::RowsAtCompileTime;
        int compile_time_cols = MatrixType::ColsAtCompileTime;
        if (dynamic_matrix.rows() != compile_time_rows && compile_time_rows != Dynamic) {
            throw ObjectConversionError(object, TypeName<MatrixType>()());
        }
        if (dynamic_matrix.cols() != compile_time_cols && compile_time_cols != Dynamic) {
            throw ObjectConversionError(object, TypeName<MatrixType>()());
        }
        return dynamic_matrix;
    }

    Vector2d Conversion<Object, Vector2d>::operator()(const Object& object) const {
        return convertToMatrix<Vector2d>(object);
    }

    Vector3d Conversion<Object, Vector3d>::operator()(const Object& object) const {
        return convertToMatrix<Vector3d>(object);
    }

    VectorXd Conversion<Object, VectorXd>::operator()(const Object& object) const {
        return convertToMatrix<VectorXd>(object);
    }

    RowVector2d Conversion<Object, RowVector2d>::operator()(const Object& object) const {
        return convertToMatrix<RowVector2d>(object);
    }

    RowVector3d Conversion<Object, RowVector3d>::operator()(const Object& object) const {
        return convertToMatrix<RowVector3d>(object);
    }

    RowVectorXd Conversion<Object, RowVectorXd>::operator()(const Object& object) const {
        return convertToMatrix<RowVectorXd>(object);
    }

    Matrix2d Conversion<Object, Matrix2d>::operator()(const Object& object) const {
        return convertToMatrix<Matrix2d>(object);
    }

    Matrix3d Conversion<Object, Matrix3d>::operator()(const Object& object) const {
        return convertToMatrix<Matrix3d>(object);
    }

    Vector2I Conversion<Object, Vector2I>::operator()(const Object& object) const {
        return convertToMatrix<Vector2I>(object);
    }

    Vector3I Conversion<Object, Vector3I>::operator()(const Object& object) const {
        return convertToMatrix<Vector3I>(object);
    }

    VectorXI Conversion<Object, VectorXI>::operator()(const Object& object) const {
        return convertToMatrix<VectorXI>(object);
    }

    RowVector2I Conversion<Object, RowVector2I>::operator()(const Object& object) const {
        return convertToMatrix<RowVector2I>(object);
    }

    RowVector3I Conversion<Object, RowVector3I>::operator()(const Object& object) const {
        return convertToMatrix<RowVector3I>(object);
    }

    RowVectorXI Conversion<Object, RowVectorXI>::operator()(const Object& object) const {
        return convertToMatrix<RowVectorXI>(object);
    }

    Matrix2I Conversion<Object, Matrix2I>::operator()(const Object& object) const {
        return convertToMatrix<Matrix2I>(object);
    }

    Matrix3I Conversion<Object, Matrix3I>::operator()(const Object& object) const {
        return convertToMatrix<Matrix3I>(object);
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
