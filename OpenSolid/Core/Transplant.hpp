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

#include <OpenSolid/Core/Transplant.definitions.hpp>

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    template <int iNumSourceDimensions, int iNumDestinationDimensions> template <int iNumAxes>
    Transplant<iNumSourceDimensions, iNumDestinationDimensions>::Transplant(
        const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
        const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
    ) : _sourceOriginPoint(sourceDatum.originPoint()),
        _transformationMatrix(destinationDatum.basisMatrix() * sourceDatum.inverseMatrix()),
        _destinationOriginPoint(destinationDatum.originPoint()) {
    }

    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Point<iNumSourceDimensions>&
    Transplant<iNumSourceDimensions, iNumDestinationDimensions>::sourceOriginPoint() const {
        return _sourceOriginPoint;
    }
    
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Matrix<double, iNumDestinationDimensions, iNumSourceDimensions>&
    Transplant<iNumSourceDimensions, iNumDestinationDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }
    
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Point<iNumDestinationDimensions>&
    Transplant<iNumSourceDimensions, iNumDestinationDimensions>::destinationOriginPoint() const {
        return _destinationOriginPoint;
    }

    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    template <class TTransformable>
    typename TransformationFunction<TTransformable, iNumDestinationDimensions>::ResultType
    Transplant<iNumSourceDimensions, iNumDestinationDimensions>::operator()(
        const TTransformable& transformable
    ) const {
        typedef typename TransformationFunction<
            TTransformable,
            iNumDestinationDimensions
        >::ResultType TransformedType; 

        TranslationFunction<TTransformable> sourceTranslation;
        TransformationFunction<TTransformable, iNumDestinationDimensions> transformation;
        TranslationFunction<TransformedType> destinationTranslation;

        TTransformable temp1 = sourceTranslation(transformable, -sourceOriginPoint().vector());
        TransformedType temp2 = transformation(temp1, transformationMatrix());
        return translation(temp2, destinationOriginPoint().vector());
    }
}
