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

#include <OpenSolid/Core/Curve.definitions.hpp>

#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    Curve<iNumDimensions>::Curve() :
        Geometry<iNumDimensions, 1>() {
    }

    template <int iNumDimensions>
    Curve<iNumDimensions>::Curve(const Geometry<iNumDimensions, 1>& other) :
        Geometry<iNumDimensions, 1>(other) {
    }

    template <int iNumDimensions>
    Curve<iNumDimensions>::Curve(const Function<iNumDimensions, 1>& function, Interval domain) :
        Geometry<iNumDimensions, 1>(function, domain) {
    }

    template <int iNumDimensions>
    Curve<iNumDimensions>::Curve(const LineSegment<iNumDimensions>& lineSegment) :
        Geometry<iNumDimensions, 1>(lineSegment) {
    }

    template <int iNumDimensions>
    Curve<iNumDimensions>
    Curve<iNumDimensions>::reversed() const {
        Function<1, 1> reversedParameter =
            this->domain().upperBound() + this->domain().lowerBound() - Function<1, 1>::t();
        return Curve<iNumDimensions>(this->function().composed(reversedParameter), this->domain());
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    Curve<iNumDimensions>::startPoint() const {
        return Point<iNumDimensions>(this->function()(this->domain().lowerBound()));
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    Curve<iNumDimensions>::endPoint() const {
        return Point<iNumDimensions>(this->function()(this->domain().upperBound()));
    }
}
