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

#include <OpenSolid/Core/IntervalVector.declarations.hpp>

#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<IntervalVector<iNumDimensions>>
    {
        typedef IntervalVector<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<IntervalVector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<IntervalVector<iNumDimensions>, iNumResultDimensions>
    {
        typedef IntervalVector<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<IntervalVector<iNumDimensions>, iNumResultDimensions>
    {
        typedef IntervalVector<iNumResultDimensions> Type;
    };

    template <>
    class IntervalVector<1> :
        public detail::CartesianBase<Interval, 1>,
        public Transformable<IntervalVector<1>>,
        public Convertible<IntervalVector<1>>
    {
    public:
        IntervalVector();

        explicit
        IntervalVector(const IntervalMatrix<1, 1>& components);

        explicit
        IntervalVector(Interval x);

        const Interval
        value() const;

        const Interval
        x() const;

        const Interval
        squaredNorm() const;

        const Interval
        norm() const;

        const IntervalVector<1>
        normalized() const;

        const Interval
        dot(const Vector<1>& vector) const;

        const Interval
        dot(const IntervalVector<1>& other) const;

        const IntervalVector<1>
        hull(const IntervalVector<1>& other) const;

        const IntervalVector<1>
        hull(const Vector<1>& vector) const;

        static const IntervalVector<1>
        Unit();

        static const IntervalVector<1>
        Empty();

        static const IntervalVector<1>
        Whole();
    };

    template <>
    class IntervalVector<2> :
        public detail::CartesianBase<Interval, 2>,
        public Transformable<IntervalVector<2>>,
        public Convertible<IntervalVector<2>>
    {
    public:
        IntervalVector();

        explicit
        IntervalVector(const IntervalMatrix<2, 1>& components);

        IntervalVector(Interval x, Interval y);

        const IntervalMatrix<2, 1>& components

        const Interval
        x() const;

        const Interval
        y() const;

        const Interval
        squaredNorm() const;

        const Interval
        norm() const;

        const IntervalVector<2>
        normalized() const;

        const Interval
        dot(const Vector<2>& vector) const;

        const Interval
        dot(const IntervalVector<2>& other) const;

        const IntervalVector<2>
        hull(const IntervalVector<2>& other) const;

        const IntervalVector<2>
        hull(const Vector<2>& vector) const;

        static const IntervalVector<2>
        Unit();

        static const IntervalVector<2>
        Empty();

        static const IntervalVector<2>
        Whole();
    };

    typedef IntervalVector<2> IntervalVector2d;

    template <>
    class IntervalVector<3> :
        public detail::CartesianBase<Interval, 3>,
        public Transformable<IntervalVector<3>>,
        public Convertible<IntervalVector<3>>
    {
    public:
        IntervalVector();

        IntervalVector(Interval x, Interval y, Interval z);

        explicit
        IntervalVector(const IntervalMatrix<3, 1>& components);

        const Interval
        x() const;

        const Interval
        y() const;

        const Interval
        z() const;

        const Interval
        squaredNorm() const;

        const Interval
        norm() const;

        const IntervalVector<3>
        normalized() const;

        const Interval
        dot(const Vector<3>& vector) const;

        const Interval
        dot(const IntervalVector<3>& other) const;

        const IntervalVector<3>
        hull(const IntervalVector<3>& other) const;

        const IntervalVector<3>
        hull(const Vector<3>& vector) const;

        const IntervalVector<3>
        cross(const Vector<3>& vector) const;

        const IntervalVector<3>
        cross(const IntervalVector<3>& other) const;

        static const IntervalVector<3>
        Unit();

        static const IntervalVector<3>
        Empty();

        static const IntervalVector<3>
        Whole();
    };

    typedef IntervalVector<3> IntervalVector3d;

    const IntervalVector1d
    operator*(Interval scale, const Vector1d& vector);

    const IntervalVector2d
    operator*(Interval scale, const Vector2d& vector);

    const IntervalVector3d
    operator*(Interval scale, const Vector3d& vector);

    const IntervalVector1d
    operator*(double scale, const IntervalVector1d& intervalVector);

    const IntervalVector2d
    operator*(double scale, const IntervalVector2d& intervalVector);

    const IntervalVector3d
    operator*(double scale, const IntervalVector3d& intervalVector);

    const IntervalVector1d
    operator*(Interval scale, const IntervalVector1d& intervalVector);

    const IntervalVector2d
    operator*(Interval scale, const IntervalVector2d& intervalVector);

    const IntervalVector3d
    operator*(Interval scale, const IntervalVector3d& intervalVector);

    const IntervalVector1d
    operator*(const Vector1d& vector, Interval scale);

    const IntervalVector2d
    operator*(const Vector2d& vector, Interval scale);

    const IntervalVector3d
    operator*(const Vector3d& vector, Interval scale);

    const IntervalVector1d
    operator*(const IntervalVector1d& intervalVector, double scale);

    const IntervalVector2d
    operator*(const IntervalVector2d& intervalVector, double scale);

    const IntervalVector3d
    operator*(const IntervalVector3d& intervalVector, double scale);

    const IntervalVector1d
    operator*(const IntervalVector1d& intervalVector, Interval scale);

    const IntervalVector2d
    operator*(const IntervalVector2d& intervalVector, Interval scale);

    const IntervalVector3d
    operator*(const IntervalVector3d& intervalVector, Interval scale);

    const IntervalVector1d
    operator/(const Vector1d& vector, Interval divisor);

    const IntervalVector2d
    operator/(const Vector2d& vector, Interval divisor);

    const IntervalVector3d
    operator/(const Vector3d& vector, Interval divisor);

    const IntervalVector1d
    operator/(const IntervalVector1d& intervalVector, double divisor);

    const IntervalVector2d
    operator/(const IntervalVector2d& intervalVector, double divisor);

    const IntervalVector3d
    operator/(const IntervalVector3d& intervalVector, double divisor);

    const IntervalVector1d
    operator/(const IntervalVector1d& intervalVector, Interval divisor);

    const IntervalVector2d
    operator/(const IntervalVector2d& intervalVector, Interval divisor);

    const IntervalVector3d
    operator/(const IntervalVector3d& intervalVector, Interval divisor);

    const IntervalVector1d
    operator+(const Vector1d& vector, const IntervalVector1d& intervalVector);

    const IntervalVector1d
    operator+(const IntervalVector1d& intervalVector, const Vector1d& vector);

    const IntervalVector1d
    operator+(
        const IntervalVector1d& firstIntervalVector,
        const IntervalVector1d& secondIntervalVector
    );

    const IntervalVector2d
    operator+(const Vector2d& vector, const IntervalVector2d& intervalVector);

    const IntervalVector2d
    operator+(const IntervalVector2d& intervalVector, const Vector2d& vector);

    const IntervalVector2d
    operator+(
        const IntervalVector2d& firstIntervalVector,
        const IntervalVector2d& secondIntervalVector
    );

    const IntervalVector3d
    operator+(const Vector3d& vector, const IntervalVector3d& intervalVector);

    const IntervalVector3d
    operator+(const IntervalVector3d& intervalVector, const Vector3d& vector);

    const IntervalVector3d
    operator+(
        const IntervalVector3d& firstIntervalVector,
        const IntervalVector3d& secondIntervalVector
    );

    const IntervalVector1d
    operator-(const Vector1d& vector, const IntervalVector1d& intervalVector);

    const IntervalVector1d
    operator-(const IntervalVector1d& intervalVector, const Vector1d& vector);

    const IntervalVector1d
    operator-(
        const IntervalVector1d& firstIntervalVector,
        const IntervalVector1d& secondIntervalVector
    );

    const IntervalVector2d
    operator-(const Vector2d& vector, const IntervalVector2d& intervalVector);

    const IntervalVector2d
    operator-(const IntervalVector2d& intervalVector, const Vector2d& vector);

    const IntervalVector2d
    operator-(
        const IntervalVector2d& firstIntervalVector,
        const IntervalVector2d& secondIntervalVector
    );

    const IntervalVector3d
    operator-(const Vector3d& vector, const IntervalVector3d& intervalVector);

    const IntervalVector3d
    operator-(const IntervalVector3d& intervalVector, const Vector3d& vector);

    const IntervalVector3d
    operator-(
        const IntervalVector3d& firstIntervalVector,
        const IntervalVector3d& secondIntervalVector
    );

    template <int iNumDimensions>
    struct BoundsFunction<IntervalVector<iNumDimensions>>
    {
        const IntervalVector<iNumDimensions>&
        operator()(const IntervalVector<iNumDimensions>& intervalVector) const;
    };
}
