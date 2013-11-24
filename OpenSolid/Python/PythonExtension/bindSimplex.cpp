/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include "PythonModule.hpp"
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Matrix.hpp>

using namespace boost::python;

namespace opensolid
{
    MatrixXd* vertices(const SimplexXd& simplex) {
        return new MatrixXd(simplex.vertices());
    }

    MatrixXd* vertex(const SimplexXd& simplex, int index) {
        return new MatrixXd(simplex.vertex(index));
    }

    SimplexXd transformed(
        const SimplexXd& simplex,
        const MatrixXd& matrix,
        const MatrixXd& vector
    ) {return simplex.transformed(matrix, vector.col(0));}

    SimplexXd scaled(const SimplexXd& simplex, double scale, const MatrixXd& point) {
        return simplex.scaled(scale, VectorXd(point));
    }

    SimplexXd translated1(const SimplexXd& simplex, const MatrixXd& vector) {
        return simplex.translated(VectorXd(vector));
    }

    SimplexXd translated2(const SimplexXd& simplex, double distance, const DatumXd& axis) {
        return simplex.translated(distance, axis);
    }

    SimplexXd rotated1(const SimplexXd& simplex, double angle, const MatrixXd& point) {
        return simplex.rotated(angle, Vector2d(point));
    }

    SimplexXd rotated2(const SimplexXd& simplex, double angle, const DatumXd& axis) {
        return simplex.rotated(angle, axis);
    }

    SimplexXd mirrored(const SimplexXd& simplex, const DatumXd& plane) {
        return simplex.mirrored(plane);
    }

    MatrixXd* vector(const SimplexXd& simplex) {return new MatrixXd(simplex.vector());}

    MatrixXd* centroid(const SimplexXd& simplex) {return new MatrixXd(simplex.centroid());}

    MatrixXd* normal(const SimplexXd& simplex) {return new MatrixXd(simplex.normal());}

    SimplexXd edge1(const SimplexXd& simplex, int index) {
        return simplex.edge(index);
    }

    SimplexXd edge2(const SimplexXd& simplex, int first_index, int second_index) {
        return simplex.edge(first_index, second_index);
    }

    SimplexXd face(const SimplexXd& simplex, int index) {return simplex.face(index);}

    DatumXd coordinateSystem(const SimplexXd& simplex) {return simplex.coordinateSystem();}

    MatrixXI* bounds(const SimplexXd& simplex) {return new MatrixXI(simplex.bounds());}

    struct SimplexPickleSuite : public pickle_suite
    {
        static tuple getinitargs(const SimplexXd& simplex) {
            return make_tuple(MatrixXd(simplex.vertices()));
        }
    };

    SimplexXd line1d(double first_vertex, double second_vertex) {
        return LineSegment1d(first_vertex, second_vertex);
    }

    SimplexXd line1d2(MatrixXd vertices) {
        return LineSegment1d(vertices);
    }

    SimplexXd line2d(const MatrixXd& first_vertex, const MatrixXd& second_vertex) {
        return LineSegment2d(first_vertex, second_vertex);
    }

    SimplexXd line2d2(const MatrixXd& vertices) {
        return LineSegment2d(vertices);
    }

    SimplexXd line3d(const MatrixXd& first_vertex, const MatrixXd& second_vertex) {
        return LineSegment3d(first_vertex, second_vertex);
    }

    SimplexXd line3d2(const MatrixXd& vertices) {
        return LineSegment3d(vertices);
    }

    SimplexXd triangle2d(
        const MatrixXd& first_vertex,
        const MatrixXd& second_vertex,
        const MatrixXd& third_vertex
    ) {
        return Triangle2d(first_vertex, second_vertex, third_vertex);
    }

    SimplexXd triangle2d2(const MatrixXd& vertices) {
        return Triangle2d(vertices);
    }

    SimplexXd triangle3d(
        const MatrixXd& first_vertex,
        const MatrixXd& second_vertex,
        const MatrixXd& third_vertex
    ) {
        return Triangle3d(first_vertex, second_vertex, third_vertex);
    }

    SimplexXd triangle3d2(const MatrixXd& vertices) {
        return Triangle3d(vertices);
    }

    SimplexXd tetrahedron3d(
        const MatrixXd& first_vertex,
        const MatrixXd& second_vertex,
        const MatrixXd& third_vertex,
        const MatrixXd& fourth_vertex
    ) {
        return Tetrahedron3d(first_vertex, second_vertex, third_vertex, fourth_vertex);
    }

    SimplexXd tetrahedron3d2(const MatrixXd& vertices) {
        return Tetrahedron3d(vertices);
    }

    void bindSimplex() {
        return_value_policy<manage_new_object> manage_new_matrix;
        class_<SimplexXd>("SimplexXd", init<MatrixXd>())
            .def("dimensions", &SimplexXd::dimensions)
            .def("size", &SimplexXd::size)
            .def("vertices", &vertices, manage_new_matrix)
            .def("vertex", &vertex, manage_new_matrix)
            .def("transformed", &transformed)
            .def("scaled", &scaled)
            .def("translated", &translated1)
            .def("translated", &translated2)
            .def("rotated", &rotated1)
            .def("rotated", &rotated2)
            .def("mirrored", &mirrored)
            .def("length", &SimplexXd::length)
            .def("area", &SimplexXd::area)
            .def("volume", &SimplexXd::volume)
            .def("vector", &vector, manage_new_matrix)
            .def("centroid", &centroid, manage_new_matrix)
            .def("normal", &normal, manage_new_matrix)
            .def("edge", &edge1)
            .def("edge", &edge2)
            .def("face", &face)
            .def("coordinateSystem", &coordinateSystem)
            .def("bounds", &bounds, manage_new_matrix)
            .def(self == self)
            .def(self * DatumXd())
            .def(self / DatumXd())
            .def(self % DatumXd())
            .def_pickle(SimplexPickleSuite());
        def("LineSegment1d", &line1d);
        def("LineSegment1d", &line1d2);
        def("LineSegment2d", &line2d);
        def("LineSegment2d", &line2d2);
        def("LineSegment3d", &line3d);
        def("LineSegment3d", &line3d2);
        def("Triangle2d", &triangle2d);
        def("Triangle2d", &triangle2d2);
        def("Triangle3d", &triangle3d);
        def("Triangle3d", &triangle3d2);
        def("Tetrahedron3d", &tetrahedron3d);
        def("Tetrahedron3d", &tetrahedron3d2);
    }
}
