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

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>

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
        public Vector<double, 2>,
        public Convertible<UnitVector<2>>
    {
    public:
        UnitVector();

        UnitVector(double x, double y);

        explicit
        UnitVector(const Matrix<double, 2, 1>& components);

        double
        norm() const;

        double
        squaredNorm() const;

        UnitVector<2>
        normalized() const;

        UnitVector<2>
        unitOrthogonal() const;

        UnitVector<2>
        rotatedBy(double angle) const;

        UnitVector<2>
        rotatedBy(const Matrix<double, 2, 2>& rotationMatrix) const;

        UnitVector<2>
        toLocalIn(const Frame<2>& frame) const;

        UnitVector<2>
        toGlobalFrom(const Frame<2>& frame) const;

        UnitVector<3>
        toGlobalFrom(const Plane3d& plane) const;

        UnitVector<2>
        mirroredAlong(const UnitVector<2>& mirrorDirection) const;

        UnitVector<2>
        mirroredAbout(const Axis<2>& axis) const;

        using Convertible<UnitVector<2>>::to;
        using Convertible<UnitVector<2>>::from;
    };

    typedef UnitVector<2> UnitVector2d;

    template <>
    class UnitVector<3> :
        public Vector<double, 3>,
        public Convertible<UnitVector<3>>
    {
    public:
        UnitVector();

        UnitVector(double x, double y, double z);

        explicit
        UnitVector(const Matrix<double, 3, 1>& components);

        double
        norm() const;

        double
        squaredNorm() const;

        UnitVector<3>
        normalized() const;

        UnitVector<3>
        rotatedBy(const Matrix<double, 3, 3>& rotationMatrix) const;

        UnitVector<3>
        toLocalIn(const Frame<3>& frame) const;

        UnitVector<3>
        toGlobalFrom(const Frame<3>& frame) const;

        using Vector<double, 3>::toLocalIn;

        UnitVector<3>
        mirroredAlong(const UnitVector<3>& mirrorDirection) const;

        UnitVector<3>
        mirroredAbout(const Plane3d& plane) const;

        using Convertible<UnitVector<3>>::to;
        using Convertible<UnitVector<3>>::from;
    };

    typedef UnitVector<3> UnitVector3d;

    UnitVector2d
    operator-(const UnitVector2d& unitVector);

    UnitVector3d
    operator-(const UnitVector3d& unitVector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<2>& unitVector);

    OPENSOLID_CORE_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<3>& unitVector);

    template <int iNumDimensions>
    struct BoundsFunction<UnitVector<iNumDimensions>> :
        public BoundsFunction<Vector<double, iNumDimensions>>
    {
    };

    template <int iNumDimensions, class TTo>
    struct ConversionFunction<UnitVector<iNumDimensions>, TTo> :
        public ConversionFunction<Vector<double, iNumDimensions>, TTo>
    {
    };
}
