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

#include <OpenSolid/Core/Domain.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    Domain<iNumDimensions>::Domain() {
    }

    template <int iNumDimensions>
    inline
    Domain<iNumDimensions>::Domain(
        const SpatialSet<Geometry<iNumDimensions, iNumDimensions - 1>>& boundaries
    ) : _boundaries(boundaries) {
    }
    
    template <int iNumDimensions>
    inline
    const SpatialSet<Geometry<iNumDimensions, iNumDimensions - 1>>&
    Domain<iNumDimensions>::boundaries() const {
        return _boundaries;
    }

    template <int iNumDimensions>
    inline
    bool
    Domain<iNumDimensions>::isEmpty() const {
        return boundaries().isEmpty();
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    Domain<iNumDimensions>::bounds() const {
        return boundaries().bounds();
    }

    template <int iNumDimensions>
    Domain<iNumDimensions>
    ScalingFunction<Domain<iNumDimensions>>::operator()(
        const Domain<iNumDimensions>& domain,
        double scale
    ) const {
        return Domain<iNumDimensions>(detail::scaled(domain.boundaries(), scale));
    }

    template <int iNumDimensions> template <class TVector>
    inline
    Domain<iNumDimensions>
    TranslationFunction<Domain<iNumDimensions>>::operator()(
        const Domain<iNumDimensions>& domain,
        const EigenBase<TVector>& vector
    ) const {
        return Domain<iNumDimensions>(domain.boundaries().translatedBy(vector.derived()));
    }

    template <int iNumDimensions> template <class TMatrix>
    inline
    Domain<iNumDimensions>
    TransformationFunction<Domain<iNumDimensions>, iNumDimensions>::operator()(
        const Domain<iNumDimensions>& domain,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Domain<iNumDimensions>(detail::transformed(domain.boundaries(), matrix.derived()));
    }

    template <int iNumDimensions>
    inline
    Domain<iNumDimensions>
    MorphingFunction<Domain<iNumDimensions>, iNumDimensions>::operator()(
        const Domain<iNumDimensions>& domain,
        const ParametricExpression<iNumDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Domain<iNumDimensions>(domain.boundaries().morphed(morphingExpression));
    }
}
