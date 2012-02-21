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
            .def(init<Function>())
            .def(init<SimplexXd>())
            .def(init<DatumXd>())
            .def(init<MatrixXI>())
            .def(init<MatrixXd>())
            .def(init<Interval>())
            .def(init<std::string>())
            .def(init<double>())
            .def(init<int>())
            .def("hasValue", &Object::hasValue)
            .def("has", &Object::has)
            .def("get", &Object::get)
            .def("set", &Object::set)
            .def("transformed", &transformed)
            .def("scalae", &scaled)
            .def("translated", &translated1)
            .def("translated", &translated2)
            .def("rotated", &rotated1)
            .def("rotated", &rotated2)
            .def("mirrored", &mirrored);
    }
}
