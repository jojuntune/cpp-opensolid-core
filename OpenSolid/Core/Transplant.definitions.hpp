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
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    class Transplant
    {
    private:
        Matrix<double, iNumSourceDimensions, 1> _sourceOriginPoint;
        Matrix<double, iNumDestinationDimensions, iNumSourceDimensions> _transformationMatrix;
        Matrix<double, iNumDestinationDimensions, 1> _destinationOriginPoint;
    public:
        template <int iNumAxes>
        Transplant(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        );

        const Matrix<double, iNumSourceDimensions, 1>&
        sourceOriginPoint() const;
        
        const Matrix<double, iNumDestinationDimensions, iNumSourceDimensions>&
        transformationMatrix() const;
        
        const Matrix<double, iNumDestinationDimensions, 1>&
        destinationOriginPoint() const;

        template <class TTransformable>
        typename TransformationFunction<TTransformable, iNumDestinationDimensions>::ResultType
        operator()(const TTransformable& transformable) const;
    };
}
