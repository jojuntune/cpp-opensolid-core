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
#include <OpenSolid/Core/Geometry/BoundsType.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

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
    Geometry<iNumDimensions, iNumParameters>::Geometry(
        const Simplex<iNumDimensions, iNumParameters + 1>& simplex
    ) : _function(Function::Linear(simplex.datum())),
        _domain(Simplex<iNumParameters, iNumParameters + 1>::Unit()) {
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
    inline bool
    Geometry<iNumDimensions, iNumParameters>::isValid() const {
        return function().isValid() && !domain().isEmpty();
    }

    template <int iNumDimensions, int iNumParameters>
    inline const Box<iNumDimensions>&
    Geometry<iNumDimensions, iNumParameters>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions, int iNumParameters> template <class TVector>
    inline Point<iNumDimensions>
    Geometry<iNumDimensions, iNumParameters>::operator()(
        const EigenBase<TVector>& parameterValues
    ) const {
        return Point<iNumDimensions>(function()(parameterValues));
    }

    template <int iNumDimensions, int iNumParameters>
    Set<Geometry<iNumDimensions, iNumParameters - 1>>
    Geometry<iNumDimensions, iNumParameters>::boundaries() const {
        return domain().boundaries().mapped(
            [this] (const Geometry<iNumParameters, iNumParameters - 1>& domainBoundary) {
                return Geometry<iNumDimensions, iNumParameters - 1>(
                    function().compose(domainBoundary.function()),
                    domainBoundary.domain()
                );
            }
        );
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
    Geometry<iNumDimensions, 1>::Geometry(const Simplex<iNumDimensions, 2>& simplex) :
        _function(Function::Linear(simplex.datum())),
        _domain(Interval::Unit()) {
    }

    template <int iNumDimensions>
    inline const Function&
    Geometry<iNumDimensions, 1>::function() const {
        return _function;
    }
    
    template <int iNumDimensions>
    inline Interval
    Geometry<iNumDimensions, 1>::domain() const {
        return _domain;
    }

    template <int iNumDimensions>
    inline bool
    Geometry<iNumDimensions, 1>::isValid() const {
        return function().isValid() && !domain().isEmpty();
    }
    
    template <int iNumDimensions>
    inline const Box<iNumDimensions>&
    Geometry<iNumDimensions, 1>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Geometry<iNumDimensions, 1>::operator()(double parameterValue) const {
        return Point<iNumDimensions>(function()(parameterValue));
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

    template <int iNumDimensions, int iNumParameters, int iNumTransformedDimensions>
    template <class TMatrix>
    Geometry<iNumTransformedDimensions, iNumParameters>
    TransformationFunction<Geometry<iNumDimensions, iNumParameters>, iNumTransformedDimensions>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Geometry<iNumTransformedDimensions, iNumParameters>(
            matrix.derived() * geometry.function(),
            geometry.domain()
        );
    }

    template <int iNumDimensions, int iNumParameters, int iNumDestinationDimensions>
    Geometry<iNumDestinationDimensions, iNumParameters>
    MorphingFunction<Geometry<iNumDimensions, iNumParameters>, iNumDestinationDimensions>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const Function<iNumDestinationDimensions, iNumDimensions>& function
    ) const {
        return Geometry<iNumDestinationDimensions, iNumParameters>(
            function.compose(geometry.function()),
            geometry.domain()
        );
    }
}
