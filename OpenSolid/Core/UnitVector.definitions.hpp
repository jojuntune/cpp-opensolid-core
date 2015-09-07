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

#include <OpenSolid/Core/UnitVector.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Cartesian.definitions.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Sign.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<UnitVector<iNumDimensions>>
    {
        typedef Vector<Interval, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<UnitVector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class UnitVector<2> :
        public Cartesian<double, 2>,
        public Transformable<UnitVector<2>, Vector<double, 2>>,
        public Convertible<UnitVector<2>>
    {
    private:
        const Vector<double, 2>&
        asVector() const;
    public:
        UnitVector();

        explicit
        UnitVector(int index);

        UnitVector(double x, double y);

        explicit
        UnitVector(const Matrix<double, 2, 1>& components);

        operator const Vector<double, 2>&() const;

        bool
        operator==(const Vector<double, 2>& vector) const;

        bool
        operator!=(const Vector<double, 2>& vector) const;

        bool
        equals(const Vector<double, 2>& vector, double precision = 1e-12) const;

        Vector<Interval, 2>
        bounds() const;

        bool
        isZero() const;

        double
        dot(const Vector<double, 2>& vector) const;

        UnitVector<2>
        unitOrthogonal() const;

        template <class TTransformation>
        UnitVector<2>
        transformedBy(const TTransformation& transformation) const;

        Vector<double, 2>
        projectedOnto(const Axis<2>& axis) const;

        UnitVector<3>
        placedOnto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        static UnitVector<2>
        random();

        static UnitVector<2>
        X();

        OPENSOLID_CORE_EXPORT
        static UnitVector<2>
        Y();
    };

    typedef UnitVector<2> UnitVector2d;

    template <>
    class UnitVector<3> :
        public Cartesian<double, 3>,
        public Transformable<UnitVector<3>, Vector<double, 3>>,
        public Convertible<UnitVector<3>>
    {
    private:
        const Vector<double, 3>&
        asVector() const;
    public:
        UnitVector();

        explicit
        UnitVector(int index);

        UnitVector(double x, double y, double z);

        explicit
        UnitVector(const Matrix<double, 3, 1>& components);

        operator const Vector<double, 3>&() const;

        bool
        operator==(const Vector<double, 3>& vector) const;

        bool
        operator!=(const Vector<double, 3>& vector) const;

        bool
        equals(const Vector<double, 3>& vector, double precision = 1e-12) const;

        Vector<Interval, 3>
        bounds() const;

        bool
        isZero() const;

        double
        dot(const Vector<double, 3>& vector) const;

        Vector<double, 3>
        cross(const Vector<double, 3>& vector) const;

        UnitVector<3>
        unitOrthogonal() const;

        template <class TTransformation>
        UnitVector<3>
        transformedBy(const TTransformation& transformation) const;

        Vector<double, 3>
        projectedOnto(const Axis<3>& axis) const;

        Vector<double, 3>
        projectedOnto(const Plane3d& plane) const;

        Vector<double, 2>
        projectedInto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        static UnitVector<3>
        random();

        static UnitVector<3>
        X();

        OPENSOLID_CORE_EXPORT
        static UnitVector<3>
        Y();

        OPENSOLID_CORE_EXPORT
        static UnitVector<3>
        Z();
    };

    typedef UnitVector<3> UnitVector3d;

    UnitVector<2>
    operator-(const UnitVector<2>& unitVector);

    UnitVector<3>
    operator-(const UnitVector<3>& unitVector);

    UnitVector<2>
    operator*(Sign sign, const UnitVector<2>& unitVector);

    UnitVector<2>
    operator*(const UnitVector<2>& unitVector, Sign sign);

    UnitVector<3>
    operator*(Sign sign, const UnitVector<3>& unitVector);

    UnitVector<3>
    operator*(const UnitVector<3>& unitVector, Sign sign);

    Vector<double, 2>
    operator*(double scale, const UnitVector<2>& unitVector);

    Vector<Interval, 2>
    operator*(Interval scale, const UnitVector<2>& unitVector);

    Vector<double, 2>
    operator*(const UnitVector<2>& unitVector, double scale);

    Vector<Interval, 2>
    operator*(const UnitVector<2>& unitVector, Interval scale);

    Vector<double, 3>
    operator*(double scale, const UnitVector<3>& unitVector);

    Vector<Interval, 3>
    operator*(Interval scale, const UnitVector<3>& unitVector);

    Vector<double, 3>
    operator*(const UnitVector<3>& unitVector, double scale);

    Vector<Interval, 3>
    operator*(const UnitVector<3>& unitVector, Interval scale);

    Vector<double, 2>
    operator/(const UnitVector<2>& unitVector, double scale);

    Vector<Interval, 2>
    operator/(const UnitVector<2>& unitVector, Interval scale);

    Vector<double, 3>
    operator/(const UnitVector<3>& unitVector, double scale);

    Vector<Interval, 3>
    operator/(const UnitVector<3>& unitVector, Interval scale);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<2>& unitVector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<3>& unitVector);

    template <int iNumDimensions, class TTo>
    struct ConversionFunction<UnitVector<iNumDimensions>, TTo> :
        public ConversionFunction<Vector<double, iNumDimensions>, TTo>
    {
    };
}
