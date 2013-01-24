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

        OPENSOLID_CORE_EXPORT Axis(const Vector2d& originPoint, const Vector2d& axisVector);

        template <int iNumDimensions, int iNumAxes>
        Axis(const Datum<iNumDimensions, iNumAxes>& otherAxis);
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> : public Datum<3, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT Axis();

        OPENSOLID_CORE_EXPORT Axis(const Vector3d& originPoint, const Vector3d& axisVector);

        template <int iNumDimensions, int iNumAxes>
        Axis(const Datum<iNumDimensions, iNumAxes>& otherAxis);
    };

    typedef Axis<3> Axis3d;
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    Axis<2>::Axis(const Datum<iNumDimensions, iNumAxes>& otherAxis) : Datum<2, 1>(otherAxis) {
    }

    template <int iNumDimensions, int iNumAxes>
    Axis<3>::Axis(const Datum<iNumDimensions, iNumAxes>& otherAxis) : Datum<3, 1>(otherAxis) {
    }
}
