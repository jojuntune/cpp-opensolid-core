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

#include <OpenSolid/Core/Geometry.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <OpenSolid/Core/Geometry/BoundsFunction.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>::Geometry() :
        _function(Function::Zero(iNumDimensions, iNumParameters)),
        _domain(),
        _bounds() {
    }

    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>::Geometry(
        const Function& function, 
        const Domain<iNumParameters>& domain
    ) : _function(function),
        _domain(domain),
        _bounds(function(domain.bounds())) {
    }

    template <int iNumDimensions, int iNumParameters>
    inline const Function&
    Geometry<iNumDimensions, iNumParameters>::function() const {
        return _function;
    }

    template <int iNumDimensions, int iNumParameters>
    inline const Domain<iNumParameters>&
    Geometry<iNumDimensions, iNumParameters>::domain() const {
        return _domain;
    }

    template <int iNumDimensions, int iNumParameters>
    inline const Box<iNumDimensions>&
    Geometry<iNumDimensions, iNumParameters>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions, int iNumParameters> template <class TArgument>
    inline MatrixReturnValue<TArgument>
    Geometry<iNumDimensions, iNumParameters>::operator()(const TArgument& argument) const {
        return function()(argument);
    }

    template <int iNumDimensions, int iNumParameters>
    Set<Geometry<iNumDimensions, iNumParameters - 1>>
    Geometry<iNumDimensions, iNumParameters>::boundaries() const {
        Set<Geometry<iNumDimensions, iNumParameters - 1>> results;
        domain().boundaries().transform(
            [this] (const Geometry<iNumParameters, iNumParameters - 1>& domainBoundary) {
                return Geometry<iNumDimensions, iNumParameters - 1>(
                    function()(domainBoundary.function()),
                    domainBoundary.domain()
                );
            },
            results.inserter()
        );
        return results;
    }

    template <int iNumDimensions>
    Geometry<iNumDimensions, 1>::Geometry() :
        _function(Function::Zero(iNumDimensions, 1)),
        _domain(),
        _bounds() {
    }

    template <int iNumDimensions>
    Geometry<iNumDimensions, 1>::Geometry(const Function& function, Interval domain) :
        _function(function),
        _domain(domain),
        _bounds(function(domain)) {
    }

    template <int iNumDimensions>
    const Function&
    Geometry<iNumDimensions, 1>::function() const {
        return _function;
    }
    
    template <int iNumDimensions>
    Interval
    Geometry<iNumDimensions, 1>::domain() const {
        return _domain;
    }
    
    template <int iNumDimensions>
    const Box<iNumDimensions>&
    Geometry<iNumDimensions, 1>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions> template <class TArgument>
    MatrixReturnValue<TArgument>
    Geometry<iNumDimensions, 1>::operator()(const TArgument& argument) const {
        return function()(argument);
    }

    template <int iNumDimensions>
    Set<Point<iNumDimensions>>
    Geometry<iNumDimensions, 1>::boundaries() const {
        Set<Point<iNumDimensions>> results;
        results.insert(Point<iNumDimensions>(function()(domain().lowerBound())));
        results.insert(Point<iNumDimensions>(function()(domain().upperBound())));
        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>
    ScalingFunction<Geometry<iNumDimensions, iNumParameters>>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        double scale
    ) const {
        return Geometry<iNumDimensions, iNumParameters>(
            scale * geometry.function(),
            geometry.domain()
        );
    }

    template <int iNumDimensions, int iNumParameters>
    template <class TVector>
    Geometry<iNumDimensions, iNumParameters>
    TranslationFunction<Geometry<iNumDimensions, iNumParameters>>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const EigenBase<TVector>& vector
    ) const {
        return Geometry<iNumDimensions, iNumParameters>(
            geometry.function() + vector.derived(),
            geometry.domain()
        );
    }

    template <int iNumDimensions, int iNumParameters, int iTransformedDimensions>
    template <class TMatrix>
    Geometry<iTransformedDimensions, iNumParameters>
    TransformationFunction<Geometry<iNumDimensions, iNumParameters>, iTransformedDimensions>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Geometry<iTransformedDimensions, iNumParameters>(
            matrix.derived() * geometry.function(),
            geometry.domain()
        );
    }
}
