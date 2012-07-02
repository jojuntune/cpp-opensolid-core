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

#include <OpenSolid/Core/Datum/Axis.hpp>
#include <OpenSolid/Core/Datum/Frame.hpp>
#include <OpenSolid/Core/Datum/Plane.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>

namespace opensolid
{
    class Geometry;
    class Domain;

    class GeometryConstructors
    {
    public:
        OPENSOLID_CORE_EXPORT static Geometry Arc2d(
            const Frame2d& frame,
            double radius,
            double start_angle,
            double end_angle
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Arc2d(
            const Vector2d& center,
            bool counterclockwise,
            const Vector2d& start,
            const Vector2d& end
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc2d(
            const Vector2d& start_point,
            const Vector2d& inner_point,
            const Vector2d& end_point
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Plane3d& plane,
            double radius,
            double start_angle,
            double end_angle
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Axis3d& axis,
            const Vector3d& start,
            const Vector3d& end
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Vector3d& start_point,
            const Vector3d& inner_point,
            const Vector3d& end_point
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle2d(
            const Vector2d& center,
            double radius,
            bool filled = true
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle3d(
            const Axis3d& axis,
            double radius,
            bool filled = true
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle3d(
            const Plane3d& plane,
            double radius,
            bool filled = true
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Helix3d(
            const Frame3d& frame,
            double radius,
            double pitch,
            const Interval& turns
        );
    };
}
