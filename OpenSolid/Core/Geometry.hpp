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
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    inline
    Geometry<iNumDimensions, iNumParameters>::Geometry() :
        _expression(),
        _domain(),
        _bounds() {
    }

    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>::Geometry(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression, 
        const Domain<iNumParameters>& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain.bounds())) {
    }

    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>::Geometry(
        const Simplex<iNumDimensions, iNumParameters + 1>& simplex
    ) : _expression(ParametricExpression<iNumDimensions, iNumParameters>::Linear(simplex.datum())),
        _domain(Simplex<iNumParameters, iNumParameters + 1>::Unit()) {
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const ParametricExpression<iNumDimensions, iNumParameters>&
    Geometry<iNumDimensions, iNumParameters>::expression() const {
        return _expression;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Domain<iNumParameters>&
    Geometry<iNumDimensions, iNumParameters>::domain() const {
        return _domain;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    bool
    Geometry<iNumDimensions, iNumParameters>::isValid() const {
        return !domain().isEmpty();
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Box<iNumDimensions>&
    Geometry<iNumDimensions, iNumParameters>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions, int iNumParameters> template <class TVector>
    inline
    Point<iNumDimensions>
    Geometry<iNumDimensions, iNumParameters>::operator()(
        const EigenBase<TVector>& parameterValues
    ) const {
        return Point<iNumDimensions>(expression().evaluate(parameterValues));
    }

    template <int iNumDimensions, int iNumParameters>
    SpatialSet<Geometry<iNumDimensions, iNumParameters - 1>>
    Geometry<iNumDimensions, iNumParameters>::boundaries() const {
        return domain().boundaries().morphed(expression());
    }

    template <int iNumDimensions>
    Geometry<iNumDimensions, 1>::Geometry() :
        _expression(),
        _domain(),
        _bounds() {
    }

    template <int iNumDimensions>
    Geometry<iNumDimensions, 1>::Geometry(
        const ParametricExpression<iNumDimensions, 1>& expression,
        Interval domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain)) {
    }

    template <int iNumDimensions>
    Geometry<iNumDimensions, 1>::Geometry(const Simplex<iNumDimensions, 2>& simplex) :
        _expression(ParametricExpression<iNumDimensions, 1>::Linear(simplex.coordinateSystem())),
        _domain(Interval::Unit()) {
    }

    template <int iNumDimensions>
    inline
    const ParametricExpression<iNumDimensions, 1>&
    Geometry<iNumDimensions, 1>::expression() const {
        return _expression;
    }
    
    template <int iNumDimensions>
    inline
    Interval
    Geometry<iNumDimensions, 1>::domain() const {
        return _domain;
    }

    template <int iNumDimensions>
    inline
    bool
    Geometry<iNumDimensions, 1>::isValid() const {
        return !domain().isEmpty();
    }
    
    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>&
    Geometry<iNumDimensions, 1>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    Geometry<iNumDimensions, 1>::operator()(double parameterValue) const {
        return Point<iNumDimensions>(expression().evaluate(parameterValue));
    }

    template <int iNumDimensions>
    SpatialSet<Point<iNumDimensions>>
    Geometry<iNumDimensions, 1>::boundaries() const {
        Point<iNumDimensions> results[2];
        results[0] = Point<iNumDimensions>(expression().evaluate(domain().lowerBound()));
        results[1] = Point<iNumDimensions>(expression().evaluate(domain().upperBound()));
        return SpatialSet<Point<iNumDimensions>>(results, results + 2);
    }

    template <int iNumDimensions, int iNumParameters>
    Geometry<iNumDimensions, iNumParameters>
    ScalingFunction<Geometry<iNumDimensions, iNumParameters>>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        double scale
    ) const {
        return Geometry<iNumDimensions, iNumParameters>(
            scale * geometry.expression(),
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
            geometry.expression() + vector.derived(),
            geometry.domain()
        );
    }

    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    template <class TMatrix>
    Geometry<iNumResultDimensions, iNumParameters>
    TransformationFunction<
        Geometry<iNumDimensions, iNumParameters>,
        iNumResultDimensions
    >::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Geometry<iNumResultDimensions, iNumParameters>(
            matrix.derived() * geometry.expression(),
            geometry.domain()
        );
    }

    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    Geometry<iNumResultDimensions, iNumParameters>
    MorphingFunction<Geometry<iNumDimensions, iNumParameters>, iNumResultDimensions>::operator()(
        const Geometry<iNumDimensions, iNumParameters>& geometry,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Geometry<iNumResultDimensions, iNumParameters>(
            morphingExpression.composed(geometry.expression()),
            geometry.domain()
        );
    }
}
