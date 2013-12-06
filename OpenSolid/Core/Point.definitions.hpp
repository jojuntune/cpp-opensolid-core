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
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <ostream>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        struct Position;

        template <int iNumDimensions>
        struct Position<double, iNumDimensions>
        {
            typedef Point<iNumDimensions> Type;
        };

        template <int iNumDimensions>
        struct Position<Interval, iNumDimensions>
        {
            typedef Box<iNumDimensions> Type;
        };

        template <int iNumDimensions>
        class PointBase
        {
        private:
            Matrix<double, iNumDimensions, 1> _vector;
        protected:
            PointBase();

            template <class TVector>
            PointBase(const EigenBase<TVector>& vector);

            PointBase(double value);

            PointBase(double x, double y);

            PointBase(double x, double y, double z);
        public:
            const Matrix<double, iNumDimensions, 1>&
            vector() const;

            Matrix<double, iNumDimensions, 1>&
            vector();

            const double*
            data() const;
            
            double*
            data();

            double&
            operator()(int index);
            
            double
            operator()(int index) const;

            Box<iNumDimensions>
            hull(const Point<iNumDimensions>& other) const;

            bool
            isOrigin(double precision = 1e-12) const;

            bool
            operator==(const Point<iNumDimensions>& other) const;

            Matrix<double, iNumDimensions, 1>
            operator-(const Point<iNumDimensions>& other) const;

            Matrix<Interval, iNumDimensions, 1>
            operator-(const Box<iNumDimensions>& box) const;

            static Point<iNumDimensions>
            Origin();
        };
    }

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

        template <class TVector>
        explicit
        Point(const EigenBase<TVector>& vector);

        double
        value() const;

        double&
        value();
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

        template <class TVector>
        explicit
        Point(const EigenBase<TVector>& vector);

        double
        x() const;

        double&
        x();

        double
        y() const;

        double&
        y();

        double
        distanceTo(const Axis<2>& axis);

        static Point
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

        template <class TVector>
        explicit
        Point(const EigenBase<TVector>& vector);

        double
        x() const;

        double&
        x();

        double
        y() const;

        double&
        y();

        double
        z() const;

        double&
        z();

        double
        distanceTo(const Plane3d& plane);

        static Point
        Cylindrical(double radius, double angle, double height);

        static Point
        Spherical(double radius, double polarAngle, double elevationAngle);
    };

    typedef Point<3> Point3d;

    template <int iNumDimensions, class TVector>
    typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type
    operator+(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector);

    template <int iNumDimensions, class TVector>
    typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type
    operator-(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point);
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct ScalingFunction<Point<iNumDimensions>>
    {
        Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Point<iNumDimensions>>
    {
        template <class TVector>
        Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Point<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        Point<iNumResultDimensions>
        operator()(
            const Point<iNumDimensions>& point,
            const EigenBase<TMatrix>& matrix
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

    template <int iNumDimensions>
    struct BoundsFunction<Point<iNumDimensions>>
    {
        Box<iNumDimensions>
        operator()(const Point<iNumDimensions>& point) const;
    };

    template <int iNumDimensions>
    struct EqualityFunction<Point<iNumDimensions>>
    {
        bool
        operator()(
            const Point<iNumDimensions>& firstPoint,
            const Point<iNumDimensions>& secondPoint,
            double precision
        ) const;
    };
}
