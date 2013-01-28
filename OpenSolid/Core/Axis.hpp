/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    template <>
    class Axis<2> : public Datum<2, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT Axis();

        Axis(const Datum<2, 1>& otherAxis);

        OPENSOLID_CORE_EXPORT Axis(const Vector2d& originPoint, const Vector2d& directionVector);

        OPENSOLID_CORE_EXPORT static Axis<2> X();
        OPENSOLID_CORE_EXPORT static Axis<2> X(const Vector2d& originPoint);
        OPENSOLID_CORE_EXPORT static Axis<2> Y();
        OPENSOLID_CORE_EXPORT static Axis<2> Y(const Vector2d& originPoint);

        OPENSOLID_CORE_EXPORT static Axis<2> FromBasisVector(
            const Vector2d& originPoint,
            const Vector2d& basisVector
        );
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> : public Datum<3, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT Axis();

        Axis(const Datum<3, 1>& otherAxis);

        OPENSOLID_CORE_EXPORT Axis(const Vector3d& originPoint, const Vector3d& directionVector);

        OPENSOLID_CORE_EXPORT static Axis<3> X();
        OPENSOLID_CORE_EXPORT static Axis<3> X(const Vector3d& originPoint);
        OPENSOLID_CORE_EXPORT static Axis<3> Y();
        OPENSOLID_CORE_EXPORT static Axis<3> Y(const Vector3d& originPoint);
        OPENSOLID_CORE_EXPORT static Axis<3> Z();
        OPENSOLID_CORE_EXPORT static Axis<3> Z(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Axis<3> FromBasisVector(
            const Vector3d& originPoint,
            const Vector3d& basisVector
        );
    };

    typedef Axis<3> Axis3d;
}

////////// Implementation //////////

namespace opensolid
{
    inline Axis<2>::Axis(const Datum<2, 1>& otherAxis) : Datum<2, 1>(otherAxis) {
    }

    inline Axis<3>::Axis(const Datum<3, 1>& otherAxis) : Datum<3, 1>(otherAxis) {
    }
}
