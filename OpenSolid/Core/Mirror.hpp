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

#include <OpenSolid/Core/Mirror.definitions.hpp>

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    Mirror<iNumDimensions>::Mirror(const Datum<iNumDimensions, iNumDimensions - 1>& datum) :
        _originPoint(datum.originPoint()) {

        Matrix<double, iNumDimensions, 1> normalVector = datum.normalVector();
        _transformationMatrix = Matrix<double, iNumDimensions, iNumDimensions>::Identity() -
            2 * normalVector * normalVector.transpose();
    }

    template <int iNumDimensions>
    inline const Point<iNumDimensions>&
    Mirror<iNumDimensions>::originPoint() const {
        return _originPoint;
    }

    template <int iNumDimensions>
    inline const Matrix<double, iNumDimensions, iNumDimensions>&
    Mirror<iNumDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }

    template <int iNumDimensions> template <class TTransformable>
    TTransformable
    Mirror<iNumDimensions>::operator()(const TTransformable& transformable) const {
        return TTransformable::translation(
            TTransformable::transformation(
                TTransformable::translation(
                    transformable,
                    -originPoint().vector()
                ),
                transformationMatrix()
            ),
            originPoint().vector()
        );
    }
}
