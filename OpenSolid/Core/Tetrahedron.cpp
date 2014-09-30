/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/Tetrahedron.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    LineSegment3d
    Tetrahedron3d::edge(int index) const {
        switch (index) {
        case 0:
            return LineSegment3d(vertex(0), vertex(1));
        case 1:
            return LineSegment3d(vertex(1), vertex(2));
        case 2:
            return LineSegment3d(vertex(0), vertex(2));
        case 3:
            return LineSegment3d(vertex(2), vertex(3));
        case 4:
            return LineSegment3d(vertex(0), vertex(3));
        case 5:
            return LineSegment3d(vertex(3), vertex(1));
        default:
            assert(false);
            return LineSegment3d();
        }
    }

    Triangle3d
    Tetrahedron3d::face(int oppositeIndex) const {
        switch (oppositeIndex) {
        case 0:
            return Triangle3d(vertex(1), vertex(2), vertex(3));
        case 1:
            return Triangle3d(vertex(0), vertex(3), vertex(2));
        case 2:
            return Triangle3d(vertex(3), vertex(0), vertex(1));
        case 3:
            return Triangle3d(vertex(2), vertex(1), vertex(0));
        default:
            assert(false);
            return Triangle3d();
        }
    }

    double
    Tetrahedron3d::volume() const {
        Matrix3d matrix;
        matrix.column(0) = vertex(1).components() - vertex(0).components();
        matrix.column(1) = vertex(2).components() - vertex(0).components();
        matrix.column(2) = vertex(3).components() - vertex(0).components();
        return matrix.determinant() / 6.0;
    }

    Point3d
    Tetrahedron3d::centroid() const {
        return Point3d(
            (
                vertex(0).components() +
                vertex(1).components() +
                vertex(2).components() +
                vertex(3).components()
            ) / 4.0
        );
    }

    CoordinateSystem3d
    Tetrahedron3d::coordinateSystem() const {
        return CoordinateSystem3d(
            vertex(0),
            vertex(1) - vertex(0),
            vertex(2) - vertex(0),
            vertex(3) - vertex(0)
        );
    }

    bool
    Tetrahedron3d::contains(const Point3d& point, double precision) const {
        Point3d localCoordinates = point / coordinateSystem();
        double a = localCoordinates.x();
        double b = localCoordinates.y();
        double c = localCoordinates.z();
        Zero zero(precision);
        return a >= zero && b >= zero && c >= zero && 1 - a - b - c >= zero;
    }

    bool
    Tetrahedron3d::strictlyContains(const Point3d& point, double precision) const {
        Point3d localCoordinates = point / coordinateSystem();
        double a = localCoordinates.x();
        double b = localCoordinates.y();
        double c = localCoordinates.z();
        Zero zero(precision);
        return a > zero && b > zero && c > zero && 1 - a - b - c > zero;
    }

    Tetrahedron3d
    Tetrahedron3d::unit() {
        return Tetrahedron3d(
            Point3d::origin(),
            Point3d(1, 0, 0),
            Point3d(0, 1, 0),
            Point3d(0, 0, 1)
        );
    }

    Tetrahedron3d
    ScalingFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& tetrahedron,
        const Point3d& originPoint,
        double scale
    ) const {
        return Tetrahedron3d(
            scaled(tetrahedron.vertex(0), originPoint, scale),
            scaled(tetrahedron.vertex(1), originPoint, scale),
            scaled(tetrahedron.vertex(2), originPoint, scale),
            scaled(tetrahedron.vertex(3), originPoint, scale)
        );
    }

    Tetrahedron3d
    TranslationFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& tetrahedron,
        const Vector3d& vector
    ) const {
        return Tetrahedron3d(
            translated(tetrahedron.vertex(0), vector),
            translated(tetrahedron.vertex(1), vector),
            translated(tetrahedron.vertex(2), vector),
            translated(tetrahedron.vertex(3), vector)
        );
    }

    Tetrahedron3d
    TransformationFunction<Tetrahedron3d, 3>::operator()(
        const Tetrahedron3d& tetrahedron,
        const Point3d& originPoint,
        const Matrix3d& transformationMatrix,
        const Point3d& destinationPoint
    ) const {
        return Tetrahedron3d(
            transformed(tetrahedron.vertex(0), originPoint, transformationMatrix, destinationPoint),
            transformed(tetrahedron.vertex(1), originPoint, transformationMatrix, destinationPoint),
            transformed(tetrahedron.vertex(2), originPoint, transformationMatrix, destinationPoint),
            transformed(tetrahedron.vertex(3), originPoint, transformationMatrix, destinationPoint)
        );
    }

    Tetrahedron3d
    MorphingFunction<Tetrahedron3d, ParametricExpression<Point3d, Point3d>>::operator()(
        const Tetrahedron3d& tetrahedron,
        const ParametricExpression<Point3d, Point3d>& morphingExpression
    ) const {
        return Tetrahedron3d(
            morphed(tetrahedron.vertex(0), morphingExpression),
            morphed(tetrahedron.vertex(1), morphingExpression),
            morphed(tetrahedron.vertex(2), morphingExpression),
            morphed(tetrahedron.vertex(3), morphingExpression)
        );
    }
}
