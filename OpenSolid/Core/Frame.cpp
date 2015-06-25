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

#include <OpenSolid/Core/Frame.hpp>

#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>

namespace opensolid
{
    ParametricExpression<Point2d, Point2d>
    Frame2d::expression() const {
        Parameter2d u(0);
        Parameter2d v(1);
        return (
            originPoint() +
            u * xDirectionVector() +
            v * yDirectionVector()
        );
    }

    ParametricExpression<Point3d, Point3d>
    Frame3d::expression() const {
        Parameter3d u(0);
        Parameter3d v(1);
        Parameter3d w(2);
        return (
            originPoint() +
            u * xDirectionVector() +
            v * yDirectionVector() +
            w * zDirectionVector()
        );
    }
}
