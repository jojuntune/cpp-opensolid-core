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

#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumSourceDimensions, int iNumResultDimensions> template <int iNumAxes>
    Transplant<iNumSourceDimensions, iNumResultDimensions>::Transplant(
        const CoordinateSystem<iNumSourceDimensions, iNumAxes>& sourceCoordinateSystem,
        const CoordinateSystem<iNumResultDimensions, iNumAxes>& destinationCoordinateSystem
    ) : _sourceOriginPoint(sourceCoordinateSystem.originPoint()),
        _transformationMatrix(
            destinationCoordinateSystem.basisMatrix() * sourceCoordinateSystem.inverseMatrix()
        ),
        _destinationOriginPoint(destinationCoordinateSystem.originPoint()) {
    }

    template <int iNumSourceDimensions, int iNumResultDimensions>
    const Point<iNumSourceDimensions>&
    Transplant<iNumSourceDimensions, iNumResultDimensions>::sourceOriginPoint() const {
        return _sourceOriginPoint;
    }
    
    template <int iNumSourceDimensions, int iNumResultDimensions>
    const Matrix<double, iNumResultDimensions, iNumSourceDimensions>&
    Transplant<iNumSourceDimensions, iNumResultDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }
    
    template <int iNumSourceDimensions, int iNumResultDimensions>
    const Point<iNumResultDimensions>&
    Transplant<iNumSourceDimensions, iNumResultDimensions>::destinationOriginPoint() const {
        return _destinationOriginPoint;
    }

    template <int iNumSourceDimensions, int iNumResultDimensions>
    template <class TTransformable>
    typename TransplantedType<TTransformable, iNumResultDimensions>::Type
    Transplant<iNumSourceDimensions, iNumResultDimensions>::operator()(
        const TTransformable& transformable
    ) const {
        return detail::translated(
            detail::transformed(
                detail::translated(transformable, -sourceOriginPoint().vector()),
                transformationMatrix()
            ),
            destinationOriginPoint().vector()
        );
    }
}
