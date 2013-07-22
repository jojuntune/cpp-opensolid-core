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

#include <OpenSolid/Core/Axis.definitions.hpp>

#include <OpenSolid/Core/CoordinateSystem.definitions.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    Axis<iNumDimensions>::Axis() :
        _originPoint(Point<iNumDimensions>::Origin()),
        _directionVector(Matrix<double, iNumDimensions, 1>::Zero()) {
    }

    template <int iNumDimensions>
    Axis<iNumDimensions>::Axis(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, 1>& directionVector
    ) : _originPoint(originPoint) {

        if (directionVector.isZero()) {
            throw PlaceholderError();
        }
        double squaredNorm = directionVector.squaredNorm();
        if (squaredNorm - 1 == Zero()) {
            _directionVector = directionVector;
        } else {
            _directionVector = directionVector / sqrt(squaredNorm);
        }
    }

    template <int iNumDimensions>
    const Point<iNumDimensions>&
    Axis<iNumDimensions>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions>
    const Matrix<double, iNumDimensions, 1>&
    Axis<iNumDimensions>::directionVector() const {
        return _directionVector;
    }

    template <int iNumDimensions>
    Axis<iNumDimensions>
    Axis<iNumDimensions>::flipped() const {
        return Axis<iNumDimensions>(originPoint(), -directionVector());
    }

    template <int iNumDimensions>
    CoordinateSystem<iNumDimensions, 1>
    Axis<iNumDimensions>::coordinateSystem() const {
        return CoordinateSystem<iNumDimensions, 1>(originPoint(), directionVector());
    }

    template <int iNumDimensions>
    Axis<iNumDimensions>
    ScalingFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        double scale
    ) const {
        return Axis<iNumDimensions>(
            Point<iNumDimensions>::scaling(axis.originPoint(), scale),
            scale * axis.directionVector() // Necessary since scale could be negative
        );
    }

    template <int iNumDimensions> template <class TVector>
    Axis<iNumDimensions>
    TranslationFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        const EigenBase<TVector>& vector
    ) const {
        return Axis<iNumDimensions>(axis.originPoint() + vector.derived(), axis.directionVector());
    }

    template <int iNumDimensions, int iNumTransformedDimensions> template <class TMatrix>
    Axis<iNumTransformedDimensions>
    TransformationFunction<Axis<iNumDimensions>, iNumTransformedDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Axis<iNumTransformedDimensions>(
            Point<iNumDimensions>::transformed(axis.originPoint(), matrix.derived()),
            matrix.derived() * axis.directionVector()
        );
    }

    template <int iNumDimensions, int iNumDestinationDimensions>
    Axis<iNumDestinationDimensions>
    MorphingFunction<Axis<iNumDimensions>, iNumDestinationDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const Function<iNumDestinationDimensions, iNumDimensions>& function
    ) const {
        return Axis<iNumTransformedDimensions>(
            axis.originPoint().morphed(function),
            function.jacobian(axis.originPoint().vector()) * axis.directionVector()
        );
    }
}
