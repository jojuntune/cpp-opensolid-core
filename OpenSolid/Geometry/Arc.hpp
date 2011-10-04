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

#ifndef OPENSOLID__ARC_HPP
#define OPENSOLID__ARC_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Datum/Plane.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    OPENSOLID_CORE_EXPORT Geometry Arc2d(
        const Vector2d& center,
        double radius,
        double start_angle,
        double end_angle
    );
        
    OPENSOLID_CORE_EXPORT Geometry Arc2d(
        const Vector2d& center,
        const Vector2d& start,
        const Vector2d& end,
        bool counterclockwise
    );

    OPENSOLID_CORE_EXPORT Geometry Arc3d(
        const Plane3d& plane,
        double radius,
        double start_angle,
        double end_angle
    );

    OPENSOLID_CORE_EXPORT Geometry Arc3d(
        const Axis3d& axis,
        const Vector3d& start,
        const Vector3d& end
    );
}

#endif
