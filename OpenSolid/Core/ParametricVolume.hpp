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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricVolume.definitions.hpp>

#include <OpenSolid/Core/BoundedVolume.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    const ParametricExpression<Point3d, Point3d>&
    ParametricVolume3d::expression() const {
        return _expression;
    }

    inline
    const BoundedVolume3d&
    ParametricVolume3d::domain() const {
        return _domain;
    }

    inline
    Handedness
    ParametricVolume3d::handedness() const {
        return _handedness;
    }

    inline
    const Box3d&
    ParametricVolume3d::bounds() const {
        return _bounds;
    }

    template <class TTransformation>
    ParametricVolume3d
    ParametricVolume3d::transformedBy(const TTransformation& transformation) const {
        return ParametricVolume3d(
            expression().transformedBy(transformation),
            domain(),
            handedness().transformedBy(transformation)
        );
    }
}
