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

#include <OpenSolid/Core/Transplant.declarations.hpp>

#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>

namespace opensolid
{
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    class Transplant
    {
    private:
        Point<iNumSourceDimensions> _sourceOriginPoint;
        Matrix<double, iNumDestinationDimensions, iNumSourceDimensions> _transformationMatrix;
        Point<iNumDestinationDimensions> _destinationOriginPoint;
    public:
        template <int iNumAxes>
        Transplant(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        );

        const Point<iNumSourceDimensions>&
        sourceOriginPoint() const;
        
        const Matrix<double, iNumDestinationDimensions, iNumSourceDimensions>&
        transformationMatrix() const;
        
        const Point<iNumDestinationDimensions>&
        destinationOriginPoint() const;

        template <class TTransformable>
        typename ChangeDimensions<TTransformable, iNumDestinationDimensions>::Type
        operator()(const TTransformable& transformable) const;
    };
}
