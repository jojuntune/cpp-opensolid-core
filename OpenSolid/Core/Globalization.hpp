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

#include <OpenSolid/Core/Globalization.definitions.hpp>

#include <OpenSolid/Core/Datum.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    Globalization<iNumDimensions, iNumAxes>::Globalization(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) : _originPoint(datum.originPoint()),
        _transformationMatrix(datum.basisMatrix()) {
    }

    template <int iNumDimensions, int iNumAxes>
    const Point<iNumDimensions>&
    Globalization<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    const Matrix<double, iNumDimensions, iNumAxes>&
    Globalization<iNumDimensions, iNumAxes>::transformationMatrix() const {
        return _transformationMatrix;
    }

    template <int iNumDimensions, int iNumAxes> template <class TTransformable>
    typename TransformationFunction<TTransformable, iNumDimensions>::ResultType
    Globalization<iNumDimensions, iNumAxes>::operator()(const TTransformable& transformable) const {
        typedef typename TransformationFunction<TTransformable, iNumDimensions>::ResultType
            ResultType;

        TransformationFunction<TTransformable, iNumDimensions> transform;
        TranslationFunction<ResultType> translate;

        return translate(
            transform(transformable, transformationMatrix()),
            originPoint().vector()
        );
    }
}
