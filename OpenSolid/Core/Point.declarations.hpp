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

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Point;
    
    template <class TScalar, int iNumDimensions>
    struct Position;

    template <int iNumDimensions>
    struct Position<double, iNumDimensions>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct Position<Interval, iNumDimensions>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Point<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Point<iNumDimensions>, iNumResultDimensions>
    {
        typedef Point<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Point<iNumDimensions>, iNumResultDimensions>
    {
        typedef Point<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct BoundsType<Point<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };
}
