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

#include <OpenSolid/Core/UnitVector.declarations.hpp>

#include <OpenSolid/Core/Vector.definitions.hpp>

namespace opensolid
{
    template <>
    class UnitVector<1> :
        public Vector<1>
    {
    public:
        UnitVector();

        explicit
        UnitVector(double x);

        explicit
        UnitVector(const Vector1d& vector);

        const double
        norm();

        const double
        squaredNorm() const;

        const UnitVector<1>
        normalized() const;

        static const UnitVector<1>
        X();

        static const UnitVector<1>
        Random();
    };

    typedef UnitVector<1> UnitVector1d;
 
    template <>
    class UnitVector<2> :
        public Vector<2>
    {
    public:
        UnitVector();

        UnitVector(double x, double y);

        explicit
        UnitVector(const Vector2d& vector);

        const double
        norm() const;

        const double
        squaredNorm() const;

        const UnitVector<2>
        normalized() const;

        const UnitVector<2>
        unitOrthogonal() const;

        static const UnitVector<2>
        X();

        static const UnitVector<2>
        Y();

        static const UnitVector<2>
        Random();
    };

    typedef UnitVector<2> UnitVector2d;

    template <>
    class UnitVector<3> :
        public Vector<3>
    {
    public:
        UnitVector();

        UnitVector(double x, double y, double z);

        explicit
        UnitVector(const Vector3d& vector);

        double
        norm() const;

        double
        squaredNorm() const;

        UnitVector<3>
        normalized() const;

        static const UnitVector<3>
        X();

        static const UnitVector<3>
        Y();

        static const UnitVector<3>
        Z();

        static const UnitVector<3>
        Random();
    };

    typedef UnitVector<3> UnitVector3d;

    const UnitVector1d
    operator-(const UnitVector1d& unitVector);

    const UnitVector2d
    operator-(const UnitVector2d& unitVector);

    const UnitVector3d
    operator-(const UnitVector3d& unitVector);
}
