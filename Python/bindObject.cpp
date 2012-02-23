/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <OpenSolid/Core/Object/Object.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

namespace OpenSolid
{
    void setObject(Object& object, const std::string& name, const Object& value) {
        object.set(name, value);
    }

    void setDomain(Object& object, const std::string& name, const Domain& value) {
        object.set(name, value);
    }

    void setGeometry(Object& object, const std::string& name, const Geometry& value) {
        object.set(name, value);
    }

    void setFunction(Object& object, const std::string& name, const Function& value) {
        object.set(name, value);
    }

    void setSimplexXd(Object& object, const std::string& name, const SimplexXd& value) {
        object.set(name, value);
    }

    void setDatumXd(Object& object, const std::string& name, const DatumXd& value) {
        object.set(name, value);
    }

    void setMatrixXI(Object& object, const std::string& name, const MatrixXI& value) {
        object.set(name, value);
    }

    void setMatrixXd(Object& object, const std::string& name, const MatrixXd& value) {
        object.set(name, value);
    }

    void setInterval(Object& object, const std::string& name, const Interval& value) {
        object.set(name, value);
    }

    void setString(Object& object, const std::string& name, const std::string& value) {
        object.set(name, value);
    }

    void setDouble(Object& object, const std::string& name, double value) {
        object.set(name, value);
    }

    void setInt(Object& object, const std::string& name, int value) {
        object.set(name, value);
    }

    void setBool(Object& object, const std::string& name, bool value) {
        object.set(name, value);
    }

    struct GetObjectProperty
    {
        struct Visitor
        {
            typedef boost::python::object result_type;

            template <class Type>
            boost::python::object operator()(const Type& argument) const {
                return boost::python::object(argument);
            }
        };

        static boost::python::object get(const Object& object, const std::string& name) {
            if (!object.has(name)) {
                throw ObjectPropertyError(object, name, "");
            }
            return boost::apply_visitor(Visitor(), object._properties.at(name));
        }
    };

    Object transformed(
        const Object& object,
        const MatrixXd& matrix,
        const MatrixXd& vector
    ) {return object.transformed(matrix, vector.col(0));}

    Object scaled(const Object& object, double scale, const MatrixXd& point) {
        return object.scaled(scale, VectorXd(point));
    }

    Object translated1(const Object& object, const MatrixXd& vector) {
        return object.translated(VectorXd(vector));
    }

    Object translated2(const Object& object, double distance, const DatumXd& axis) {
        return object.translated(distance, axis);
    }

    Object rotated1(const Object& object, double angle, const MatrixXd& point) {
        return object.rotated(angle, Vector2d(point));
    }

    Object rotated2(const Object& object, double angle, const DatumXd& axis) {
        return object.rotated(angle, axis);
    }

    Object mirrored(const Object& object, const DatumXd& plane) {
        return object.mirrored(plane);
    }

    void bindObject() {
        using namespace boost::python;
        class_<Object>("Object")
            .def("has", &Object::has)
            .def("get", &GetObjectProperty::get)
            .def("set", &setObject)
            .def("set", &setDomain)
            .def("set", &setGeometry)
            .def("set", &setFunction)
            .def("set", &setSimplexXd)
            .def("set", &setDatumXd)
            .def("set", &setMatrixXI)
            .def("set", &setMatrixXd)
            .def("set", &setInterval)
            .def("set", &setString)
            .def("set", &setDouble)
            .def("set", &setInt)
            .def("set", &setBool)
            .def("transformed", &transformed)
            .def("scaled", &scaled)
            .def("translated", &translated1)
            .def("translated", &translated2)
            .def("rotated", &rotated1)
            .def("rotated", &rotated2)
            .def("mirrored", &mirrored);
    }
}
