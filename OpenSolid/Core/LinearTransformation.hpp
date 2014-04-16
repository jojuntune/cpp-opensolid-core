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

#include <OpenSolid/Core/LinearTransformation.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    LinearTransformation<iNumDimensions>::LinearTransformation(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumDimensions>& transformationMatrix
    ) : _originPoint(originPoint),
        _transformationMatrix(transformationMatrix) {
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>&
    LinearTransformation<iNumDimensions>::originPoint() const {
        return _originPoint;
    }

    template <int iNumDimensions>
    inline
    const Matrix<double, iNumDimensions, iNumDimensions>&
    LinearTransformation<iNumDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }

    template <int iNumDimensions> template <class TTransformable>
    typename TransformedAboutPointType<TTransformable>::Type
    LinearTransformation<iNumDimensions>::operator()(const TTransformable& transformable) const {
        Vector<double, iNumDimensions> originVector(originPoint().components());
        return translationFunction(
            transformationFunction(
                translationFunction(
                    transformable,
                    -originVector
                ),
                transformationMatrix()
            ),
            originVector
        );
    }
}
