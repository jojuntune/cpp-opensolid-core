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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Quaternion.hpp>

namespace opensolid
{
    const Quaternion3d
    Quaternion3d::Slerp(
        const Quaternion3d& startQuaternion,
        const Quaternion3d& endQuaternion,
        double parameterValue
    ) {
        double angle = acos(Interval(-1, 1).clamp(startQuaternion.dot(endQuaternion)));
        double startCoefficient = 0.0;
        double endCoefficient = 0.0;
        double sinAngle = sin(angle);
        if (sinAngle == Zero()) {
            // Use linear interpolation for almost-parallel quaternions
            startCoefficient = 1 - parameterValue;
            endCoefficient = parameterValue;
        } else {
            startCoefficient = sin((1 - parameterValue) * angle) / sinAngle;
            endCoefficient = sin(parameterValue * angle) / sinAngle;
        }

        Matrix<double, 4, 1> slerpedComponents =
            startCoefficient * startQuaternion.components() +
            endCoefficient * endQuaternion.components();
        double squaredNorm = slerpedComponents.cwiseSquared().sum();
        if (squaredNorm == Zero()) {
            return Quaternion3d::Identity();
        } else {
            slerpedComponents /= sqrt(squaredNorm);
            return Quaternion3d(slerpedComponents);
        }
    }
}
