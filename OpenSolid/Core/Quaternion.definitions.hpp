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

#include <OpenSolid/Core/Quaternion.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    template <>
    class Quaternion<2> :
        public Convertible<Quaternion<2>>
    {
    private:
        Matrix<double, 2, 1> _components;
    public:
        Quaternion();

        explicit
        Quaternion(const Matrix<double, 2, 1>& components);

        Quaternion(double cosAngle, double sinAngle);

        Quaternion(double angle);

        const Matrix<double, 2, 1>&
        components() const;

        double
        cosAngle() const;

        double
        sinAngle() const;

        double
        angle() const;

        double
        dot(const Quaternion<2>& other) const;

        const Quaternion<2>
        inverse() const;

        const Matrix<double, 2, 2>
        rotationMatrix() const;

        const Quaternion<2>
        operator*(const Quaternion<2>& other) const;

        static const Quaternion<2>
        identity();

        OPENSOLID_CORE_EXPORT
        static const Quaternion<2>
        slerp(
            const Quaternion<2>& startQuaternion,
            const Quaternion<2>& endQuaternion,
            double parameterValue
        );
    };

    typedef Quaternion<2> Quaternion2d;

    template <>
    class Quaternion<3> :
        public Convertible<Quaternion<3>>
    {
    private:
        Matrix<double, 4, 1> _components;
    public:
        Quaternion();

        explicit
        Quaternion(const Matrix<double, 4, 1>& components);

        Quaternion(double x, double y, double z, double w);

        Quaternion(const UnitVector<3>& unitVector, double angle);

        const Matrix<double, 4, 1>&
        components() const;

        double
        x() const;

        double
        y() const;

        double
        z() const;

        double
        w() const;

        UnitVector<3>
        unitVector() const;

        double
        angle() const;

        double
        dot(const Quaternion<3>& other) const;

        const Quaternion<3>
        inverse() const;

        const Matrix<double, 3, 3>
        rotationMatrix() const;

        Quaternion<3>
        operator*(const Quaternion<3>& other) const;

        static const Quaternion<3>
        identity();

        OPENSOLID_CORE_EXPORT
        static const Quaternion<3>
        slerp(
            const Quaternion<3>& startQuaternion,
            const Quaternion<3>& endQuaternion,
            double parameterValue
        );
    };

    typedef Quaternion<3> Quaternion3d;
}
