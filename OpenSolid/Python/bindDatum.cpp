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

#include <OpenSolid/Datum/Datum.hpp>
#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Datum/Frame.hpp>
#include <OpenSolid/Datum/Plane.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    MatrixXd origin(const DatumXd& datum) {return datum.origin();}

    MatrixXd basis(const DatumXd& datum) {return datum.basis();}

    MatrixXd inverseMatrix(const DatumXd& datum) {return datum.inverseMatrix();}

    MatrixXd projectionMatrix(const DatumXd& datum) {return datum.projectionMatrix();}

    MatrixXd point1(const DatumXd& datum, double x) {
        return datum.point(x);
    }

    MatrixXd point2(const DatumXd& datum, double x, double y) {
        return datum.point(x, y);
    }

    MatrixXd point3(const DatumXd& datum, double x, double y, double z) {
        return datum.point(x, y, z);
    }

    MatrixXd vector1(const DatumXd& datum, double x) {
        return datum.vector(x);
    }

    MatrixXd vector2(const DatumXd& datum, double x, double y) {
        return datum.vector(x, y);
    }

    MatrixXd vector3(const DatumXd& datum, double x, double y, double z) {
        return datum.vector(x, y, z);
    }

    MatrixXd xDirection(const DatumXd& datum) {return datum.xDirection();}

    MatrixXd yDirection(const DatumXd& datum) {return datum.yDirection();}

    MatrixXd zDirection(const DatumXd& datum) {return datum.zDirection();}

    MatrixXd direction1(const DatumXd& datum, int index) {return datum.direction(index);}

    MatrixXd direction2(const DatumXd& datum) {return datum.direction();}

    MatrixXd normal(const DatumXd& datum) {return datum.normal();}
    
    DatumXd xAxis(const DatumXd& datum) {return datum.xAxis();}

    DatumXd yAxis(const DatumXd& datum) {return datum.yAxis();}

    DatumXd zAxis(const DatumXd& datum) {return datum.zAxis();}
    
    DatumXd axis(const DatumXd& datum, int index) {return datum.axis(index);}
    
    DatumXd normalAxis(const DatumXd& datum) {return datum.normalAxis();}

    DatumXd xyPlane(const DatumXd& datum) {return datum.xyPlane();}

    DatumXd xzPlane(const DatumXd& datum) {return datum.xzPlane();}

    DatumXd yxPlane(const DatumXd& datum) {return datum.yxPlane();}

    DatumXd yzPlane(const DatumXd& datum) {return datum.yzPlane();}

    DatumXd zxPlane(const DatumXd& datum) {return datum.zxPlane();}

    DatumXd zyPlane(const DatumXd& datum) {return datum.zyPlane();}
    
    DatumXd plane(const DatumXd& datum, int first_index, int second_index) {
        return datum.plane(first_index, second_index);
    }

    DatumXd normalPlane(const DatumXd& datum) {return datum.normalPlane();}

    DatumXd transformed(const DatumXd& datum, const MatrixXd& matrix, const MatrixXd& vector) {
        return datum.transformed(matrix, vector);
    }

    DatumXd scaled1(const DatumXd& datum, double scale) {return datum.scaled(scale);}

    DatumXd scaled2(const DatumXd& datum, double scale, const MatrixXd& point) {
        return datum.scaled(scale, point);
    }

    DatumXd translated1(const DatumXd& datum, const MatrixXd& vector) {
        return datum.translated(vector);
    }

    DatumXd translated2(const DatumXd& datum, double distance, const DatumXd& axis) {
        return datum.translated(distance, axis);
    }

    DatumXd rotated1(const DatumXd& datum, double angle, const MatrixXd& point) {
        return datum.rotated(angle, point);
    }

    DatumXd rotated2(const DatumXd& datum, double angle, const DatumXd& axis) {
        return datum.rotated(angle, axis);
    }

    DatumXd mirrored(const DatumXd& datum, const DatumXd& plane) {return datum.mirrored(plane);}

    DatumXd reversed1(const DatumXd& datum, int index) {return datum.reversed(index);}

    DatumXd reversed2(const DatumXd& datum) {return datum.reversed();}

    DatumXd axis2d(const MatrixXd& origin, const MatrixXd& direction) {
        return Axis2d(origin, direction);
    }

    DatumXd axis3d(const MatrixXd& origin, const MatrixXd& direction) {
        return Axis3d(origin, direction);
    }

    DatumXd frame2d1() {return Frame2d();}

    DatumXd frame2d2(const MatrixXd& origin) {return Frame2d(origin);}

    DatumXd frame2d3(const MatrixXd& origin, const MatrixXd& x_direction) {
        return Frame2d(origin, x_direction);
    }
    
    DatumXd frame3d1() {return Frame3d();}

    DatumXd frame3d2(const MatrixXd& origin) {return Frame3d(origin);}

    DatumXd frame3d3(
        const MatrixXd& origin,
        const MatrixXd& x_direction,
        const MatrixXd& y_direction
    ) {return Frame3d(origin, x_direction, y_direction);}

    DatumXd plane3d1(const MatrixXd& origin, const MatrixXd& normal) {
        return Plane3d(origin, normal);
    }

    DatumXd plane3d2(
        const MatrixXd& origin,
        const MatrixXd& x_direction,
        const MatrixXd& y_direction
    ) {return Plane3d(origin, x_direction, y_direction);}

    DatumXd datum2d1(
        const MatrixXd& origin,
        const MatrixXd& basis
    ) {return Datum2d(origin, basis);}

    DatumXd datum2d2(
        const MatrixXd& origin,
        const MatrixXd& x_direction,
        const MatrixXd& y_direction
    ) {return Datum2d(origin, x_direction, y_direction);}

    DatumXd datum3d1(
        const MatrixXd& origin,
        const MatrixXd& basis
    ) {return Datum3d(origin, basis);}

    DatumXd datum3d2(
        const MatrixXd& origin,
        const MatrixXd& x_direction,
        const MatrixXd& y_direction,
        const MatrixXd& z_direction
    ) {return Datum3d(origin, x_direction, y_direction, z_direction);}


    struct DatumPickleSuite : public pickle_suite
    {
        static tuple getinitargs(const DatumXd&) {return tuple();}

        static tuple getstate(const DatumXd& datum) {
            return make_tuple(MatrixXd(datum.origin()), MatrixXd(datum.basis()));
        }

        static void setstate(DatumXd& datum, tuple state) {
            VectorXd origin = MatrixXd(extract<MatrixXd>(state[0]));
            MatrixXd basis = extract<MatrixXd>(state[1]);
            datum = DatumXd(origin, basis);
        }
    };

    void bindDatum() {
        class_<DatumXd>("DatumXd")
            .def(init<MatrixXd, MatrixXd>())
            .def("origin", &origin)
            .def("basis", &basis)
            .def("inverseMatrix", &inverseMatrix)
            .def("projectionMatrix", &projectionMatrix)
            .def("dimensions", &DatumXd::dimensions)
            .def("axes", &DatumXd::axes)
            .def("point", &point1)
            .def("point", &point2)
            .def("point", &point3)
            .def("vector", &vector1)
            .def("vector", &vector2)
            .def("vector", &vector3)
            .def("xDirection", &xDirection)
            .def("yDirection", &yDirection)
            .def("zDirection", &zDirection)
            .def("direction", &direction1)
            .def("direction", &direction2)
            .def("normal", &normal)
            .def("xAxis", &xAxis)
            .def("yAxis", &yAxis)
            .def("zAxis", &zAxis)
            .def("axis", &axis)
            .def("normalAxis", &normalAxis)
            .def("xyPlane", &xyPlane)
            .def("xzPlane", &xzPlane)
            .def("yxPlane", &yxPlane)
            .def("yzPlane", &yzPlane)
            .def("zxPlane", &zxPlane)
            .def("zyPlane", &zyPlane)
            .def("plane", &plane)
            .def("normalPlane", &normalPlane)
            .def("transformed", &transformed)
            .def("scaled", &scaled1)
            .def("scaled", &scaled2)
            .def("translated", &translated1)
            .def("translated", &translated2)
            .def("rotated", &rotated1)
            .def("rotated", &rotated2)
            .def("mirrored", &mirrored)
            .def("xReversed", &DatumXd::xReversed)
            .def("yReversed", &DatumXd::yReversed)
            .def("zReversed", &DatumXd::zReversed)
            .def("reversed", &reversed1)
            .def("reversed", &reversed2)
            .def("orientation", &DatumXd::orientation)
            .def(self * self)
            .def(self / self)
            .def(self % self)
            .def_pickle(DatumPickleSuite());
        def("Axis2d", &axis2d);
        def("Axis3d", &axis3d);
        def("Datum2d", &datum2d1);
        def("Datum2d", &datum2d2);
        def("Datum3d", &datum3d1);
        def("Datum3d", &datum3d2);
        def("Frame2d", &frame2d1);
        def("Frame2d", &frame2d2);
        def("Frame2d", &frame2d3);
        def("Frame3d", &frame3d1);
        def("Frame3d", &frame3d2);
        def("Frame3d", &frame3d3);
        def("Plane3d", &plane3d1);
        def("Plane3d", &plane3d2);
    }
}
