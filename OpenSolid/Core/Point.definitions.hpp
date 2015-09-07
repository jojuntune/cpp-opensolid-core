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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Point.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Cartesian.definitions.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/NumDimensions.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <ostream>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class PointCommon :
            public Cartesian<double, iNumDimensions>,
            public Transformable<Point<iNumDimensions>, Point<iNumDimensions>>
        {
        private:
            const Point<iNumDimensions>&
            derived() const;
        protected:
            PointCommon();

            PointCommon(double x, double y);

            PointCommon(double x, double y, double z);

            PointCommon(const Matrix<double, iNumDimensions, 1>& components);
        public:
            Box<iNumDimensions>
            bounds() const;

            double
            squaredDistanceTo(const Point<iNumDimensions>& other) const;

            double
            distanceTo(const Point<iNumDimensions>& other) const;

            bool
            equals(const Point<iNumDimensions>& other, double precision = 1e-12) const;

            bool
            isOrigin(double precision = 1e-12) const;

            double
            distanceAlong(const Axis<iNumDimensions>& axis) const;

            Box<iNumDimensions>
            hull(const Point<iNumDimensions>& other) const;

            Box<iNumDimensions>
            hull(const Box<iNumDimensions>& box) const;

            template <class TTransformation>
            Point<iNumDimensions>
            transformedBy(const TTransformation& transformation) const;

            Point<iNumDimensions>
            projectedOnto(const Axis<iNumDimensions>& axis) const;

            bool
            operator==(const Point<iNumDimensions>& other) const;

            bool
            operator!=(const Point<iNumDimensions>& other) const;

            static Point<iNumDimensions>
            ORIGIN();
        };
    }

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

    template <>
    class Point<2> :
        public detail::PointCommon<2>,
        public Convertible<Point<2>>
    {
    public:
        Point();

        Point(double x, double y);

        explicit
        Point(const Matrix<double, 2, 1>& components);

        double
        distanceTo(const Axis<2>& axis) const;

        using detail::PointCommon<2>::distanceTo;

        bool
        isOn(const Axis<2>& axis, double precision = 1e-12) const;

        OPENSOLID_CORE_EXPORT
        bool
        isOn(const LineSegment<2>& lineSegment, double precision = 1e-12) const;

        Point<3>
        placedOnto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        static Point<2>
        polar(double radius, double angle);
    };

    typedef Point<2> Point2d;

    template <>
    class Point<3> :
        public detail::PointCommon<3>,
        public Convertible<Point<3>>
    {
    public:
        Point();

        Point(double x, double y, double z);

        explicit
        Point(const Matrix<double, 3, 1>& components);

        double
        squaredDistanceTo(const Axis<3>& axis) const;

        using detail::PointCommon<3>::squaredDistanceTo;

        double
        distanceTo(const Axis<3>& axis) const;

        double
        distanceTo(const Plane3d& plane) const;

        using detail::PointCommon<3>::distanceTo;

        bool
        isOn(const Axis<3>& axis, double precision = 1e-12) const;

        OPENSOLID_CORE_EXPORT
        bool
        isOn(const LineSegment<3>& lineSegment, double precision = 1e-12) const;

        OPENSOLID_CORE_EXPORT
        bool
        isOn(const Triangle<3>& triangle, double precision = 1e-12) const;

        bool
        isOn(const Plane3d& plane, double precision = 1e-12) const;

        Point<2>
        projectedInto(const Plane3d& plane) const;

        Point<3>
        projectedOnto(const Plane3d& plane) const;

        using detail::PointCommon<3>::projectedOnto;
        
        OPENSOLID_CORE_EXPORT
        static Point<3>
        cylindrical(double radius, double angle, double height);

        OPENSOLID_CORE_EXPORT
        static Point<3>
        spherical(double radius, double polarAngle, double elevationAngle);
    };

    typedef Point<3> Point3d;

    template <int iNumDimensions>
    Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector);

    template <int iNumDimensions>
    Point<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector);

    template <int iNumDimensions>
    Vector<double, iNumDimensions>
    operator-(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Point<2>& point);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Point<3>& point);
}
