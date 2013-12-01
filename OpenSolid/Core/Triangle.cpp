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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Triangle.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>

namespace opensolid
{
    double
    Triangle2d::area() const {
        Matrix2d matrix;
        matrix.col(0) = vertex(1) - vertex(0);
        matrix.col(1) = vertex(2) - vertex(0);
        return matrix.determinant() / 2.0;
    }

    Point2d
    Triangle2d::centroid() const {
        return Point2d(
            (vertex(0).vector() + vertex(1).vector() + vertex(2).vector()) / 3.0
        );
    }

    CoordinateSystem2d
    Triangle2d::coordinateSystem() const {
        return CoordinateSystem2d(
            vertex(0),
            vertex(1) - vertex(0),
            vertex(2) - vertex(0)
        );
    }

    Triangle2d
    Triangle2d::Unit() {
        return Triangle2d(Point2d::Origin(), Point2d(1, 0), Point2d(0, 1));
    }

    double
    Triangle3d::area() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).norm() / 2.0;
    }

    Point3d
    Triangle3d::centroid() const {
        return Point3d(
            (vertex(0).vector() + vertex(1).vector() + vertex(2).vector()) / 3.0
        );
    }

    Vector3d
    Triangle3d::normalVector() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).normalized();
    }

    PlanarCoordinateSystem3d
    Triangle3d::coordinateSystem() const {
        return PlanarCoordinateSystem3d(
            vertex(0),
            vertex(1) - vertex(0),
            vertex(2) - vertex(0)
        );
    }

    Plane3d
    Triangle3d::plane() const {
        return Plane3d(vertex(0), normalVector());
    }

    Triangle2d
    ScalingFunction<Triangle2d>::operator()(const Triangle2d& triangle, double scale) const {
        return Triangle2d(
            detail::scaled(triangle.vertex(0), scale),
            detail::scaled(triangle.vertex(1), scale),
            detail::scaled(triangle.vertex(2), scale)
        );
    }

    Triangle3d
    ScalingFunction<Triangle3d>::operator()(const Triangle3d& triangle, double scale) const {
        return Triangle3d(
            detail::scaled(triangle.vertex(0), scale),
            detail::scaled(triangle.vertex(1), scale),
            detail::scaled(triangle.vertex(2), scale)
        );
    }

    Triangle2d
    TranslationFunction<Triangle2d>::operator()(
        const Triangle2d& triangle,
        const Vector2d& vector
    ) const {
        return Triangle2d(
            detail::translated(triangle.vertex(0), vector),
            detail::translated(triangle.vertex(1), vector),
            detail::translated(triangle.vertex(2), vector)
        );
    }

    Triangle3d
    TranslationFunction<Triangle3d>::operator()(
        const Triangle3d& triangle,
        const Vector3d& vector
    ) const {
        return Triangle3d(
            detail::translated(triangle.vertex(0), vector),
            detail::translated(triangle.vertex(1), vector),
            detail::translated(triangle.vertex(2), vector)
        );
    }

    Triangle2d
    TransformationFunction<Triangle2d, 2>::operator()(
        const Triangle2d& triangle,
        const Matrix2d& matrix\
    ) const {
        return Triangle2d(
            detail::transformed(triangle.vertex(0), matrix),
            detail::transformed(triangle.vertex(1), matrix),
            detail::transformed(triangle.vertex(2), matrix)
        );
    }

    Triangle3d
    TransformationFunction<Triangle2d, 3>::operator()(
        const Triangle2d& triangle,
        const Matrix<double, 3, 2>& matrix
    ) const {
        return Triangle3d(
            detail::transformed(triangle.vertex(0), matrix),
            detail::transformed(triangle.vertex(1), matrix),
            detail::transformed(triangle.vertex(2), matrix)
        );
    }

    Triangle3d
    TransformationFunction<Triangle3d, 3>::operator()(
        const Triangle3d& triangle,
        const Matrix3d& matrix
    ) const {
        return Triangle3d(
            detail::transformed(triangle.vertex(0), matrix),
            detail::transformed(triangle.vertex(1), matrix),
            detail::transformed(triangle.vertex(2), matrix)
        );
    }

    Triangle2d
    TransformationFunction<Triangle3d, 2>::operator()(
        const Triangle3d& triangle,
        const Matrix<double, 2, 3>& matrix
    ) const {
        return Triangle2d(
            detail::transformed(triangle.vertex(0), matrix),
            detail::transformed(triangle.vertex(1), matrix),
            detail::transformed(triangle.vertex(2), matrix)
        );
    }

    namespace detail
    {
        Triangle2d
        morphed(
            const Triangle2d& triangle,
            const ParametricExpression<2, 2>& morphingExpression
        ) {
            return Triangle2d(
                morphed(triangle.vertex(0), morphingExpression),
                morphed(triangle.vertex(1), morphingExpression),
                morphed(triangle.vertex(2), morphingExpression)
            );
        }

        Triangle3d
        morphed(
            const Triangle2d& triangle,
            const ParametricExpression<3, 2>& morphingExpression
        ) {
            return Triangle3d(
                morphed(triangle.vertex(0), morphingExpression),
                morphed(triangle.vertex(1), morphingExpression),
                morphed(triangle.vertex(2), morphingExpression)
            );
        }

        Triangle3d
        morphed(
            const Triangle3d& triangle,
            const ParametricExpression<3, 3>& morphingExpression
        ) {
            return Triangle3d(
                morphed(triangle.vertex(0), morphingExpression),
                morphed(triangle.vertex(1), morphingExpression),
                morphed(triangle.vertex(2), morphingExpression)
            );
        }

        Triangle2d
        morphed(
            const Triangle3d& triangle,
            const ParametricExpression<2, 3>& morphingExpression
        ) {
            return Triangle2d(
                morphed(triangle.vertex(0), morphingExpression),
                morphed(triangle.vertex(1), morphingExpression),
                morphed(triangle.vertex(2), morphingExpression)
            );
        }
    }

    TolerantComparator<Triangle2d>::TolerantComparator(double precision) :
        _precision(precision) {
    }

    bool
    TolerantComparator<Triangle2d>::operator()(
        const Triangle2d& firstTriangle,
        const Triangle2d& secondTriangle
    ) const {
        return (firstTriangle.vertex(0) - secondTriangle.vertex(0)).isZero(_precision) &&
            (firstTriangle.vertex(1) - secondTriangle.vertex(1)).isZero(_precision) &&
            (firstTriangle.vertex(2) - secondTriangle.vertex(2)).isZero(_precision);
    }

    TolerantComparator<Triangle3d>::TolerantComparator(double precision) :
        _precision(precision) {
    }

    bool
    TolerantComparator<Triangle3d>::operator()(
        const Triangle3d& firstTriangle,
        const Triangle3d& secondTriangle
    ) const {
        return (firstTriangle.vertex(0) - secondTriangle.vertex(0)).isZero(_precision) &&
            (firstTriangle.vertex(1) - secondTriangle.vertex(1)).isZero(_precision) &&
            (firstTriangle.vertex(2) - secondTriangle.vertex(2)).isZero(_precision);
    }
}
