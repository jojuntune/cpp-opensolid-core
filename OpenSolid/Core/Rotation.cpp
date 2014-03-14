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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Rotation.hpp>

namespace opensolid
{
    namespace
    {
        inline
        Matrix2x2
        rotationMatrix2d(double angle) {
            double sinAngle = sin(angle);
            double cosAngle = cos(angle);
            return Matrix2x2(cosAngle, sinAngle, -sinAngle, cosAngle);
        }

        inline
        Matrix3x3
        rotationMatrix3d(const UnitVector3d& axisVector, double angle) {
            Matrix3x1 axisComponents = axisVector.components();
            double x = axisComponents(0);
            double y = axisComponents(1);
            double z = axisComponents(2);
            double sinAngle = sin(angle);
            double cosAngle = cos(angle);
            return (1 - cosAngle) * axisComponents * axisComponents.transpose() +
                cosAngle * Matrix3x3::Identity() +
                sinAngle * Matrix3x3(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);
        }
    }

    Rotation2d::Rotation2d(const Point2d& originPoint, double angle) :
        LinearTransformation<2>(originPoint, rotationMatrix2d(angle)) {
    }

    Rotation3d::Rotation3d(const Axis<3>& axis, double angle) :
        LinearTransformation<3>(
            axis.originPoint(),
            rotationMatrix3d(axis.directionVector(), angle)
        ) {
    }
}
