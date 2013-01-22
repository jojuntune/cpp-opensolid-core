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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Simplex.hpp>

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
            double startAngle,
            double endAngle
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Arc2d(
            const Vector2d& center,
            bool isCounterclockwise,
            const Vector2d& startPoint,
            const Vector2d& endPoint
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc2d(
            const Vector2d& startPoint,
            const Vector2d& innerPoint,
            const Vector2d& endPoint
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Plane3d& plane,
            double radius,
            double startAngle,
            double endAngle
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Axis3d& axis,
            const Vector3d& startPoint,
            const Vector3d& endPoint
        );

        OPENSOLID_CORE_EXPORT static Geometry Arc3d(
            const Vector3d& startPoint,
            const Vector3d& innerPoint,
            const Vector3d& endPoint
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle2d(
            const Vector2d& center,
            double radius,
            bool isFilled = true
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle3d(
            const Axis3d& axis,
            double radius,
            bool isFilled = true
        );

        OPENSOLID_CORE_EXPORT static Geometry Circle3d(
            const Plane3d& plane,
            double radius,
            bool isFilled = true
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Helix3d(
            const Frame3d& frame,
            double radius,
            double pitch,
            Interval turnInterval
        );
    };
}
