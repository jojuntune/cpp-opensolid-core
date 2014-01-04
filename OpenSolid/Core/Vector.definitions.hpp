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

#include <OpenSolid/Core/Vector.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/IntervalVector.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Vector<iNumDimensions>>
    {
        typedef IntervalVector<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Vector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Vector<iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Vector<iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<iNumResultDimensions> Type;
    };

    template <>
    class Vector<1> :
        public VectorBase<1>,
        public Transformable<Vector<1>>,
        public Convertible<Vector<1>>
    {
    public:
        Vector();

        explicit
        Vector(double x);

        const double
        value() const;

        const double
        x() const;

        const double
        squaredNorm() const;

        const double
        norm() const;

        const UnitVector<1>
        normalized() const;

        const double
        dot(const Vector<1>& other) const;

        const Interval
        dot(const IntervalVector<1>& intervalVector) const;

        const double
        minComponent() const;

        const double
        minComponent(std::int64_t& index) const;

        const double
        maxComponent() const;

        const double
        maxComponent(std::int64_t& index) const;

        const IntervalVector<1>
        hull(const Vector<1>& other) const;

        const IntervalVector<1>
        hull(const IntervalVector<1>& intervalVector) const;

        const bool
        operator==(const Vector<1>& other) const;

        static const Vector<1>
        Zero();

        static const Vector<1>
        Random();
    };

    typedef Vector<1> Vector1d;

    template <>
    class Vector<2> :
        public VectorBase<2>,
        public Transformable<Vector<2>>,
        public Convertible<Vector<2>>
    {
    public:
        Vector();

        Vector(double x, double y);

        const double
        x() const;

        const double
        y() const;

        const double
        squaredNorm() const;

        const double
        norm() const;

        const UnitVector<2>
        normalized() const;

        const double
        dot(const Vector<2>& other) const;

        const Interval
        dot(const IntervalVector<2>& intervalVector) const;

        const double
        minComponent() const;

        const double
        minComponent(std::int64_t& index) const;

        const double
        maxComponent() const;

        const double
        maxComponent(std::int64_t& index) const;

        const IntervalVector<2>
        hull(const Vector<2>& other) const;

        const IntervalVector<2>
        hull(const IntervalVector<2>& intervalVector) const;

        const bool
        operator==(const Vector<2>& other) const;

        const UnitVector<2>
        unitOrthogonal() const;

        static const Vector<2>
        Zero();

        static const Vector<2>
        Random();
    };

    typedef Vector<2> Vector2d;

    template <>
    class Vector<3> :
        public VectorBase<3>,
        public Transformable<Vector<3>>,
        public Convertible<Vector<3>>
    {
    public:
        Vector();

        Vector(double x, double y, double z);

        const double
        x() const;

        const double
        y() const;

        const double
        z() const;

        const double
        squaredNorm() const;

        const double
        norm() const;

        const UnitVector<3>
        normalized() const;

        const double
        dot(const Vector<3>& other) const;

        const Interval
        dot(const IntervalVector<3>& intervalVector) const;

        const double
        minComponent() const;

        const double
        minComponent(std::int64_t& index) const;

        const double
        maxComponent() const;

        const double
        maxComponent(std::int64_t& index) const;

        const IntervalVector<3>
        hull(const Vector<3>& other) const;

        const IntervalVector<3>
        hull(const IntervalVector<3>& intervalVector) const;

        const bool
        operator==(const Vector<3>& other) const;

        const Vector<3>
        cross(const Vector<3>& other) const;

        const IntervalVector<3>
        cross(const IntervalVector<3>& intervalVector) const;

        const UnitVector<3>
        unitOrthogonal() const;

        static const Vector<3>
        Zero();

        static const Vector<3>
        Random();
    };

    typedef Vector<3> Vector3d;

    const bool
    operator==(const Vector1d& vector, Zero zero);

    const bool
    operator==(const Vector2d& vector, Zero zero);

    const bool
    operator==(const Vector3d& vector, Zero zero);

    const bool
    operator!=(const Vector1d& vector, Zero zero);

    const bool
    operator!=(const Vector2d& vector, Zero zero);

    const bool
    operator!=(const Vector3d& vector, Zero zero);

    const Vector1d
    operator*(double scale, const Vector1d& vector);

    const Vector2d
    operator*(double scale, const Vector2d& vector);

    const Vector3d
    operator*(double scale, const Vector3d& vector);

    const Vector1d
    operator*(const Vector1d& vector, double scale);

    const Vector2d
    operator*(const Vector2d& vector, double scale);

    const Vector3d
    operator*(const Vector3d& vector, double scale);

    const Vector1d
    operator/(const Vector1d& vector, double divisor);

    const Vector2d
    operator/(const Vector2d& vector, double divisor);

    const Vector3d
    operator/(const Vector3d& vector, double divisor);

    const Vector1d
    operator+(const Vector1d& firstVector, const Vector1d& secondVector);

    const Vector2d
    operator+(const Vector2d& firstVector, const Vector2d& secondVector);

    const Vector3d
    operator+(const Vector3d& firstVector, const Vector3d& secondVector);

    const Vector1d
    operator-(const Vector1d& firstVector, const Vector1d& secondVector);

    const Vector2d
    operator-(const Vector2d& firstVector, const Vector2d& secondVector);

    const Vector3d
    operator-(const Vector3d& firstVector, const Vector3d& secondVector);

    template <int iNumDimensions>
    struct EqualityFunction<Vector<iNumDimensions>>
    {
        const bool
        operator()(
            const Vector<iNumDimensions>& firstVector,
            const Vector<iNumDimensions>& secondVector,
            double precision
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Vector<iNumDimensions>>
    {
        const IntervalVector<iNumDimensions>
        operator()(const Vector<iNumDimensions>& vector) const;
    };
}
