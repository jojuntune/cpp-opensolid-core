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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Point.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Position/PointBase.definitions.hpp>
#include <OpenSolid/Core/Tetrahedron.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <ostream>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Point<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Point<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Point<iNumDimensions>, iNumResultDimensions>
    {
        typedef Point<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Point<iNumDimensions>, iNumResultDimensions>
    {
        typedef Point<iNumResultDimensions> Type;
    };

    template <>
    class Point<1> :
        public detail::PointBase<1>,
        public Convertible<Point<1>>,
        public Transformable<Point<1>>
    {
    public:
        Point();

        explicit
        Point(double value);

        explicit
        Point(const Vector<1>& vector);

        explicit
        Point(const Matrix<1, 1>& components);

        explicit
        Point(const double* sourcePtr);

        const double
        value() const;

        double&
        value();

        const double
        x() const;

        double&
        x();

        static const Point<1>
        Origin();
    };

    typedef Point<1> Point1d;

    template <>
    class Point<2> :
        public detail::PointBase<2>,
        public Convertible<Point<2>>,
        public Transformable<Point<2>>
    {
    public:
        Point();

        Point(double x, double y);

        explicit
        Point(const Vector<2>& vector);

        explicit
        Point(const Matrix<2, 1>& components);

        explicit
        Point(const double* sourcePtr);

        const double
        x() const;

        double&
        x();

        const double
        y() const;

        double&
        y();

        const double
        distanceTo(const Axis<2>& axis) const;

        const bool
        isOn(const Axis<2>& axis, double precision = 1e-12) const;

        const bool
        isOn(const LineSegment<2>& lineSegment, double precision = 1e-12) const;

        static const Point<2>
        Origin();

        static const Point<2>
        Polar(double radius, double angle);
    };

    typedef Point<2> Point2d;

    template <>
    class Point<3> :
        public detail::PointBase<3>,
        public Convertible<Point<3>>,
        public Transformable<Point<3>>
    {
    public:
        Point();

        Point(double x, double y, double z);

        explicit
        Point(const Vector<3>& vector);

        explicit
        Point(const Matrix<3, 1>& components);

        explicit
        Point(const double* sourcePtr);

        const double
        x() const;

        double&
        x();

        const double
        y() const;

        double&
        y();

        const double
        z() const;

        double&
        z();

        const double
        squaredDistanceTo(const Axis<3>& axis) const;

        const double
        distanceTo(const Axis<3>& axis) const;

        const double
        distanceTo(const Plane3d& plane) const;

        const bool
        isOn(const Axis<3>& axis, double precision = 1e-12) const;

        const bool
        isOn(const Plane3d& plane, double precision = 1e-12) const;

        const bool
        isOn(const LineSegment<3>& lineSegment, double precision = 1e-12) const;

        const bool
        isOn(const Triangle<3>& triangle, double precision = 1e-12) const;

        static const Point<3>
        Origin();
        
        static const Point<3>
        Cylindrical(double radius, double angle, double height);

        static const Point<3>
        Spherical(double radius, double polarAngle, double elevationAngle);
    };

    typedef Point<3> Point3d;

    template <int iNumDimensions>
    Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<iNumDimensions>& vector);

    template <int iNumDimensions>
    Point<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<iNumDimensions>& vector);

    template <int iNumDimensions>
    Vector<iNumDimensions>
    operator-(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point);

    template <int iNumDimensions>
    struct EqualityFunction<Point<iNumDimensions>>
    {
        const bool
        operator()(
            const Point<iNumDimensions>& firstPoint,
            const Point<iNumDimensions>& secondPoint,
            double precision
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Point<iNumDimensions>>
    {
        const Box<iNumDimensions>
        operator()(const Point<iNumDimensions>& point) const;
    };

    template <int iNumDimensions>
    struct ScalingFunction<Point<iNumDimensions>>
    {
        const Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Point<iNumDimensions>>
    {
        const Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, const Vector<iNumDimensions>& vector) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Point<iNumDimensions>, iNumResultDimensions>
    {
        const Point<iNumResultDimensions>
        operator()(
            const Point<iNumDimensions>& point,
            const Matrix<iNumResultDimensions, iNumDimensions>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Point<iNumDimensions>, iNumResultDimensions>
    {
        Point<iNumResultDimensions>
        operator()(
            const Point<iNumDimensions>& point,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
