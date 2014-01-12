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
#include <OpenSolid/Core/IntervalMatrix.declarations.hpp>
#include <OpenSolid/Core/IntervalVector.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Position/BoxBase.definitions.hpp>
#include <OpenSolid/Core/Position/BoxVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <ostream>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Box<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Box<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Box<iNumDimensions>, iNumResultDimensions>
    {
        typedef Box<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Box<iNumDimensions>, iNumResultDimensions>
    {
        typedef Box<iNumResultDimensions> Type;
    };

    template <>
    class Box<1> :
        public detail::BoxBase<1>,
        public Convertible<Box<1>>,
        public Transformable<Box<1>>
    {
    public:
        Box();

        explicit
        Box(Interval value);

        explicit
        Box(const IntervalVector<1>& intervalVector);

        explicit
        Box(const IntervalMatrix<1, 1>& components);

        explicit
        Box(const Interval* sourcePtr);

        const Interval
        value() const;

        Interval&
        value();

        const Interval
        x() const;

        Interval&
        x();

        const Point<1>
        interpolated(double xValue) const;

        const Box<1>
        interpolated(Interval xInterval) const;

        static const Box<1>
        Unit();

        static const Box<1>
        Hull(const Point<1>& firstPoint, const Point<1>& secondPoint);

        static const Box<1>
        Empty();

        static const Box<1>
        Whole();
    };

    typedef Box<1> Box1d;

    template <>
    class Box :
        public detail::BoxBase<2>,
        public Convertible<Box<2>>,
        public Transformable<Box<2>>
    {
    public:
        Box();

        Box(Interval x, Interval y);

        explicit
        Box(const IntervalVector<2>& intervalVector);

        explicit
        Box(const IntervalMatrix<2, 1>& components);

        explicit
        Box(const Interval* sourcePtr);

        const Interval
        x() const;

        Interval&
        x();

        const Interval
        y() const;
        
        Interval&
        y();

        const Point<2>
        interpolated(double xValue, double yValue) const;

        const Box<2>
        interpolated(Interval xInterval, Interval yInterval) const;

        static const Box<2>
        Unit();

        static const Box<2>
        Hull(const Point<2>& firstPoint, const Point<2>& secondPoint);

        static const Box<2>
        Empty();

        static const Box<2>
        Whole();
    };

    typedef Box<2> Box2d;

    template <>
    class Box :
        public detail::BoxBase<3>,
        public Convertible<Box<3>>,
        public Transformable<Box<3>>
    {
    public:
        Box();

        Box(Interval x, Interval y, Interval z);

        explicit
        Box(const IntervalVector<3>& intervalVector);

        explicit
        Box(const IntervalMatrix<3, 1>& components);

        explicit
        Box(const Interval* sourcePtr);

        const Interval
        x() const;

        Interval&
        x();

        const Interval
        y() const;
        
        Interval&
        y();

        const Interval
        z() const;
        
        Interval&
        z();

        const Point<3>
        interpolated(double xValue, double yValue, double zValue) const;

        const Box<3>
        interpolated(Interval xInterval, Interval yInterval, Interval zInterval) const;

        static const Box<3>
        Unit();

        static const Box<3>
        Hull(const Point<3>& firstPoint, const Point<3>& secondPoint);

        static const Box<3>
        Empty();

        static const Box<3>
        Whole();
    };

    typedef Box<3> Box3d;

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const IntervalVector<iNumDimensions>& vector);

    template <int iNumDimensions>
    const Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<iNumDimensions>& vector);

    template <int iNumDimensions>
    const Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const IntervalVector<iNumDimensions>& intervalVector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const IntervalVector<iNumDimensions>& vector);

    template <int iNumDimensions>
    const Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<iNumDimensions>& vector);

    template <int iNumDimensions>
    const Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const IntervalVector<iNumDimensions>& intervalVector);

    template <int iNumDimensions>
    const IntervalVector<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Box<iNumDimensions>& box);

    template <int iNumDimensions>
    const IntervalVector<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point);

    template <int iNumDimensions>
    const IntervalVector<iNumDimensions>
    operator-(const Box<iNumDimensions>& firstBox, const Box<iNumDimensions>& secondBox);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box);

    template <int iNumDimensions>
    struct BoundsFunction<Box<iNumDimensions>>
    {
        const Box<iNumDimensions>&
        operator()(const Box<iNumDimensions>& point) const;
    };

    template <int iNumDimensions>
    struct ScalingFunction<Box<iNumDimensions>>
    {
        const Box<iNumDimensions>
        operator()(const Box<iNumDimensions>& box, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Box<iNumDimensions>>
    {
        const Box<iNumDimensions>
        operator()(const Box<iNumDimensions>& box, const Vector<iNumDimensions>& vector) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Box<iNumDimensions>, iNumResultDimensions>
    {
        const Box<iNumResultDimensions>
        operator()(
            const Box<iNumDimensions>& box,
            const Matrix<iNumResultDimensions, iNumDimensions>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Box<iNumDimensions>, iNumResultDimensions>
    {
        const Box<iNumResultDimensions>
        operator()(
            const Box<iNumDimensions>& box,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
