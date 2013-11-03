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

#include <OpenSolid/Core/Mirror.hpp>

namespace opensolid
{
    namespace
    {
        template <class TDerived>
        Matrix<double, TDerived::RowsAtCompileTime, TDerived::RowsAtCompileTime>
        mirrorTransformationMatrix(const EigenBase<TDerived>& normalVector) {
            return Matrix<double, TDerived::RowsAtCompileTime, TDerived::RowsAtCompileTime>::Identity() -
                2 * normalVector.derived() * normalVector.derived().transpose();
        }
    }

    Mirror2d::Mirror2d(const Axis<2>& axis) :
        LinearTransformation<2>(
            axis.originPoint(),
            mirrorTransformationMatrix(axis.directionVector().unitOrthogonal())
        ) {
    }

    Mirror3d::Mirror3d(const Plane3d& plane) :
        LinearTransformation<3>(
            plane.originPoint(),
            mirrorTransformationMatrix(plane.normalVector())
        ) {
    }
}
