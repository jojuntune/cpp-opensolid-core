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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    class GeometryConstructors
    {
    public:
        OPENSOLID_CORE_EXPORT static Geometry
        Constant(double value, int numParameters);

        OPENSOLID_CORE_EXPORT static Geometry
        Constant(const VectorXd& vector, int numParameters);

        OPENSOLID_CORE_EXPORT static Geometry
        Arc2d(
            const Frame2d& frame,
            double radius,
            double startAngle,
            double endAngle
        );
        
        OPENSOLID_CORE_EXPORT static Geometry
        Arc2d(
            const Point2d& center,
            bool isCounterclockwise,
            const Point2d& startPoint,
            const Point2d& endPoint
        );

        OPENSOLID_CORE_EXPORT static Geometry
        Arc2d(const Point2d& startPoint, const Point2d& innerPoint, const Point2d& endPoint);

        OPENSOLID_CORE_EXPORT static Geometry
        Arc3d(const Plane3d& plane, double radius, double startAngle, double endAngle);

        OPENSOLID_CORE_EXPORT static Geometry
        Arc3d(const Axis3d& axis, const Point3d& startPoint, const Point3d& endPoint);

        OPENSOLID_CORE_EXPORT static Geometry
        Arc3d(const Point3d& startPoint, const Point3d& innerPoint, const Point3d& endPoint);

        OPENSOLID_CORE_EXPORT static Geometry
        Circle2d(const Point2d& center, double radius, bool isFilled = true);

        OPENSOLID_CORE_EXPORT static Geometry
        Circle3d(const Axis3d& axis, double radius, bool isFilled = true);

        OPENSOLID_CORE_EXPORT static Geometry
        Circle3d(const Plane3d& plane, double radius, bool isFilled = true);
        
        OPENSOLID_CORE_EXPORT static Geometry
        Helix3d(const Frame3d& frame, double radius, double pitch, Interval turnInterval);
    };
}
