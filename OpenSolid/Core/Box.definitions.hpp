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

#include <OpenSolid/Core/Box.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/BoxVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <int iNumDimensions>
    class Box :
        public Convertible<Box<iNumDimensions>>,
        public Transformable<Box<iNumDimensions>>
    {
    private:
        Matrix<Interval, iNumDimensions, 1> _vector;
    public:
        Box();

        template <class TVector>
        explicit
        Box(const EigenBase<TVector>& vector);

        explicit
        Box(Interval x);

        Box(Interval x, Interval y);

        Box(Interval x, Interval y, Interval z);

        explicit
        Box(const Point<iNumDimensions>& point);

        const Interval*
        data() const;
        
        Interval*
        data();

        Matrix<Interval, iNumDimensions, 1>&
        vector();
        
        const Matrix<Interval, iNumDimensions, 1>&
        vector() const;

        Interval&
        x();
        
        Interval
        x() const;

        Interval&
        y();

        Interval
        y() const;

        Interval&
        z();
        
        Interval
        z() const;

        Interval&
        operator()(int index);
        
        Interval
        operator()(int index) const;

        bool
        isEmpty() const;

        Point<iNumDimensions>
        minVertex() const;
        
        Point<iNumDimensions>
        maxVertex() const;

        Point<iNumDimensions>
        vertex(std::int64_t index) const;

        detail::BoxVertices<iNumDimensions>
        vertices() const;
        
        Point<iNumDimensions>
        midPoint() const;
        
        Point<iNumDimensions>
        randomPoint() const;

        Matrix<double, iNumDimensions, 1>
        diagonalVector() const;

        Point<iNumDimensions>
        interpolated(double xValue, double yValue) const;

        Point<iNumDimensions>
        interpolated(double xValue, double yValue, double zValue) const;

        Box<iNumDimensions>
        interpolated(Interval xInterval, Interval yInterval) const;

        Box<iNumDimensions>
        interpolated(Interval xInterval, Interval yInterval, Interval zInterval) const;

        bool
        overlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;

        bool
        strictlyOverlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;
        
        bool
        contains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
        
        bool
        strictlyContains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
        
        bool
        contains(const Box<iNumDimensions>& other, double precision = 1e-12) const;
        
        bool
        strictlyContains(const Box<iNumDimensions>& other, double precision = 1e-12) const;

        Box<iNumDimensions>
        hull(const Point<iNumDimensions>& point) const;
        
        Box<iNumDimensions>
        hull(const Box<iNumDimensions>& other) const;

        Box<iNumDimensions>
        intersection(const Box<iNumDimensions>& other) const;

        Matrix<Interval, iNumDimensions, 1>
        operator-(const Point<iNumDimensions>& point) const;

        Matrix<Interval, iNumDimensions, 1>
        operator-(const Box<iNumDimensions>& other) const;

        static Box
        Empty();

        static Box
        Unit();

        static Box
        Hull(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint);
    };

    typedef Box<1> Box1d;
    typedef Box<2> Box2d;
    typedef Box<3> Box3d;

    template <int iNumDimensions, class TVector>
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const EigenBase<TVector>& vector);

    template <int iNumDimensions, class TVector>
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const EigenBase<TVector>& vector);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<Box1d>
    {
        Box1d
        operator()(const Box1d& box, double scale) const;
    };

    template <>
    struct ScalingFunction<Box2d>
    {
        Box2d
        operator()(const Box2d& box, double scale) const;
    };

    template <>
    struct ScalingFunction<Box3d>
    {
        Box3d
        operator()(const Box3d& box, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Box<iNumDimensions>>
    {
        template <class TVector>
        Box<iNumDimensions>
        operator()(const Box<iNumDimensions>& box, const EigenBase<TVector>& vector) const;
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<Box1d, iNumResultDimensions>
    {
        template <class TMatrix>
        Box<iNumResultDimensions>
        operator()(const Box1d& box, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<Box2d, iNumResultDimensions>
    {
        template <class TMatrix>
        Box<iNumResultDimensions>
        operator()(const Box2d& box, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<Box3d, iNumResultDimensions>
    {
        template <class TMatrix>
        Box<iNumResultDimensions>
        operator()(const Box3d& box, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Box<iNumDimensions>, iNumResultDimensions>
    {
        Box<iNumResultDimensions>
        operator()(
            const Box<iNumDimensions>& box,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Box<iNumDimensions>>
    {
        const Box<iNumDimensions>&
        operator()(const Box<iNumDimensions>& point) const;
    };
}
