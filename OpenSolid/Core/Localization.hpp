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

#include <OpenSolid/Core/Localization.definitions.hpp>

#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    inline
    Localization<iNumDimensions, iNumAxes>::Localization(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem
    ) : _originPoint(coordinateSystem.originPoint()),
        _transformationMatrix(coordinateSystem.inverseMatrix()) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>&
    Localization<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Matrix<double, iNumAxes, iNumDimensions>&
    Localization<iNumDimensions, iNumAxes>::transformationMatrix() const {
        return _transformationMatrix;
    }

    template <int iNumDimensions, int iNumAxes> template <class TTransformable>
    typename LocalizedType<TTransformable, iNumAxes>::Type
    Localization<iNumDimensions, iNumAxes>::operator()(const TTransformable& transformable) const {
        return transformationFunction(
            translationFunction(
                transformable,
                Vector<double, iNumDimensions>(-originPoint().components())
            ),
            transformationMatrix()
        );
    }
}
