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

#include <OpenSolid/Core/Vector.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.definitions.hpp>
#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <class TScalar, int iNumDimensions>
    struct BoundsType<Vector<TScalar, iNumDimensions>>
    {
        typedef Vector<Interval, iNumDimensions> Type;
    };

    template <class TScalar, int iNumDimensions>
    struct NumDimensions<Vector<TScalar, iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Vector<double, 2> :
        public detail::VectorBase<double, 2>,
        public Transformable<Vector<double, 2>, Vector<double, 2>>,
        public Convertible<Vector<double, 2>>
    {
    public:
        Vector();

        Vector(double x, double y);

        explicit
        Vector(const Matrix<double, 2, 1>& components);

        bool
        operator==(const Vector<double, 2>& other) const;

        bool
        operator!=(const Vector<double, 2>& other) const;

        bool
        equals(const Vector<double, 2>& other, double precision = 1e-12) const;

        Vector<Interval, 2>
        bounds() const;

        UnitVector<2>
        normalized() const;

        UnitVector<2>
        unitOrthogonal() const;

        template <class TTransformation>
        Vector<double, 2>
        transformedBy(const TTransformation& transformation) const;

        Vector<double, 2>
        projectedOnto(const Axis<2>& axis) const;

        Vector<double, 3>
        placedOnto(const Plane3d& plane) const;
    };

    typedef Vector<double, 2> Vector2d;

    template <>
    class Vector<double, 3> :
        public detail::VectorBase<double, 3>,
        public Transformable<Vector<double, 3>, Vector<double, 3>>,
        public Convertible<Vector<double, 3>>
    {
    public:
        Vector();

        Vector(double x, double y, double z);

        explicit
        Vector(const Matrix<double, 3, 1>& components);

        bool
        operator==(const Vector<double, 3>& other) const;

        bool
        operator!=(const Vector<double, 3>& other) const;

        bool
        equals(const Vector<double, 3>& other, double precision = 1e-12) const;

        Vector<Interval, 3>
        bounds() const;

        Vector<double, 3>
        cross(const Vector<double, 3>& other) const;

        Vector<Interval, 3>
        cross(const Vector<Interval, 3>& intervalVector) const;

        UnitVector<3>
        normalized() const;

        OPENSOLID_CORE_EXPORT
        UnitVector<3>
        unitOrthogonal() const;

        template <class TTransformation>
        Vector<double, 3>
        transformedBy(const TTransformation& transformation) const;

        Vector<double, 3>
        projectedOnto(const Axis<3>& axis) const;

        Vector<double, 3>
        projectedOnto(const Plane3d& plane) const;

        Vector<double, 2>
        projectedInto(const Plane3d& plane) const;
    };

    typedef Vector<double, 3> Vector3d;

    template <>
    class Vector<Interval, 2> :
        public detail::IntervalVectorBase<2>,
        public Convertible<Vector<Interval, 2>>
    {
    public:
        Vector();

        explicit
        Vector(const Matrix<Interval, 2, 1>& components);

        Vector(Interval x, Interval y);

        bool
        operator==(const Vector<Interval, 2>& other) const;

        bool
        operator!=(const Vector<Interval, 2>& other) const;

        const Vector<Interval, 2>&
        bounds() const;
    };

    typedef Vector<Interval, 2> IntervalVector2d;

    template <>
    class Vector<Interval, 3> :
        public detail::IntervalVectorBase<3>,
        public Convertible<Vector<Interval, 3>>
    {
    public:
        Vector();

        Vector(Interval x, Interval y, Interval z);

        explicit
        Vector(const Matrix<Interval, 3, 1>& components);

        bool
        operator==(const Vector<Interval, 3>& other) const;

        bool
        operator!=(const Vector<Interval, 3>& other) const;

        const Vector<Interval, 3>&
        bounds() const;

        Vector<Interval, 3>
        cross(const Vector<double, 3>& other) const;

        Vector<Interval, 3>
        cross(const Vector<Interval, 3>& other) const;
    };

    typedef Vector<Interval, 3> IntervalVector3d;

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator*(double scale, const Vector<TScalar, iNumDimensions>& vector);

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator*(Interval scale, const Vector<TScalar, iNumDimensions>& vector);

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, double scale);

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, Interval scale);

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, double divisor);

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, Interval divisor);

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator-(const Vector<TScalar, iNumDimensions>& vector);

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    Vector<decltype(TFirstScalar() + TSecondScalar()), iNumDimensions>
    operator+(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    );

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    Vector<decltype(TFirstScalar() - TSecondScalar()), iNumDimensions>
    operator-(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    );

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Vector<double, 2>& vector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Vector<double, 3>& vector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Vector<Interval, 2>& vector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const Vector<Interval, 3>& vector);

    template <int iNumDimensions>
    struct EqualityFunction<Vector<double, iNumDimensions>>
    {
        bool
        operator()(
            const Vector<double, iNumDimensions>& firstVector,
            const Vector<double, iNumDimensions>& secondVector,
            double precision
        ) const;
    };
}
