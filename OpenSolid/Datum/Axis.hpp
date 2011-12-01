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

#ifndef OPENSOLID__AXIS_HPP
#define OPENSOLID__AXIS_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    class Axis2d : public Datum<2, 1>
    {
    public:
        Axis2d();
        Axis2d(const Vector2d& origin, const Vector2d& direction);

        template <int dimensions_, int axes_>
        Axis2d(const Datum<dimensions_, axes_>& datum);
    };

    class Axis3d : public Datum<3, 1>
    {
    public:
        Axis3d();
        Axis3d(const Vector3d& origin, const Vector3d& direction);

        template <int dimensions_, int axes_>
        Axis3d(const Datum<dimensions_, axes_>& datum);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Axis2d::Axis2d() {initialize(Vector2d::Zero(), Vector2d::UnitX());}

    inline Axis2d::Axis2d(const Vector2d& origin, const Vector2d& direction) {
        initialize(origin, direction.normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis2d::Axis2d(const Datum<dimensions_, axes_>& datum) {
        assertCompatible<dimensions_, 2>();
        assert(datum.dimensions() == 2);
        assertCompatible<axes_, 1>();
        assert(datum.axes() == 1);
        assert(datum.direction().norm() == One());
        initialize(datum);
    }

    inline Axis3d::Axis3d() {initialize(Vector3d::Zero(), Vector3d::UnitX());}

    inline Axis3d::Axis3d(const Vector3d& origin, const Vector3d& direction) {
        initialize(origin, direction.normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis3d::Axis3d(const Datum<dimensions_, axes_>& datum) {
        assertCompatible<dimensions_, 3>();
        assert(datum.dimensions() == 3);
        assertCompatible<axes_, 1>();
        assert(datum.axes() == 1);
        assert(datum.direction().norm() == One());
        initialize(datum);
    }
}

#endif
