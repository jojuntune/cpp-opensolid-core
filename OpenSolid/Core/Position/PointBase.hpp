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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Position/PointBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        PointBase<iNumDimensions>::derived() const {
            return static_cast<const Point<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase() {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(const Matrix<iNumDimensions, 1>& components) :
            detail::CartesianBase<double, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(const double* sourcePtr) :
            detail::CartesianBase<double, iNumDimensions>(sourcePtr) {
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointBase<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
            return Box<iNumDimensions>(
                components.binaryMap(
                    other.components(),
                    [] (double component, double otherComponent) {
                        return Interval::Hull(component, otherComponent);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointBase<iNumDimensions>::hull(const Box<iNumDimensions>& box) const {
            return Box<iNumDimensions>(
                components.binaryMap(
                    box.components(),
                    [] (double component, Interval boxComponent) {
                        boxComponent.hull(component);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::isOrigin(double precision) const {
            return components().all(
                [] (double component) {
                    return component == Zero(precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
            return vector() == other.vector();
        }
    }
}
