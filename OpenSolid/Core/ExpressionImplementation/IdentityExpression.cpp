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

#include <OpenSolid/Core/ExpressionImplementation/IdentityExpression.hpp>

#include <OpenSolid/Core/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    IdentityExpression::numDimensionsImpl() const {
        return _numDimensions;
    }

    int
    IdentityExpression::numParametersImpl() const {
        return _numDimensions;
    }
    
    void
    IdentityExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results = parameterValues;
    }
    
    void
    IdentityExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results = parameterBounds;
    }

    void
    IdentityExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results.setIdentity();
    }
    
    void
    IdentityExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results.setIdentity();
    }

    ExpressionImplementationPtr
    IdentityExpression::derivativeImpl(int parameterIndex) const {
        return new ConstantExpression(
            VectorXd::Unit(numDimensions(), parameterIndex),
            numDimensions()
        );
    }

    bool
    IdentityExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        // ExpressionImplementation already checks that numbers of parameters/dimensions are equal
        return true;
    }

    ExpressionImplementationPtr
    IdentityExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    ExpressionImplementationPtr
    IdentityExpression::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
        return innerExpression;
    }
    
    void
    IdentityExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "IdentityExpression" << std::endl;
    }

    IdentityExpression::IdentityExpression(int numDimensions) :
        _numDimensions(numDimensions) {

        assert(numDimensions > 0);
    }
}
