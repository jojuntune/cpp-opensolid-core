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

#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    int
    ParameterFunction::numDimensionsImpl() const {
        return 1;
    }

    int
    ParameterFunction::numParametersImpl() const {
        return _numParameters;
    }
    
    void
    ParameterFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results = parameterValues.row(parameterIndex());
    }
    
    void
    ParameterFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results = parameterBounds.row(parameterIndex());
    }

    void
    ParameterFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
        results(0, parameterIndex()) = 1;
    }
    
    void
    ParameterFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
        results(0, parameterIndex()) = 1;
    }

    FunctionImplementationPtr
    ParameterFunction::derivativeImpl(int parameterIndex) const {
        return new ConstantFunction(
            parameterIndex == this->parameterIndex() ? 1.0 : 0.0,
            numParameters()
        );
    }

    bool
    ParameterFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return this->parameterIndex() == other->cast<ParameterFunction>()->parameterIndex();
    }

    FunctionImplementationPtr
    ParameterFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    FunctionImplementationPtr
    ParameterFunction::composedImpl(const FunctionImplementationPtr& innerFunction) const {
        return innerFunction->component(parameterIndex());
    }
    
    void
    ParameterFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ParameterFunction: parameter index = " << parameterIndex() << std::endl;
    }

    ParameterFunction::ParameterFunction(int numParameters, int parameterIndex) :
        _numParameters(numParameters),
        _parameterIndex(parameterIndex) {

        assert(numParameters > 0);
        assert(parameterIndex >= 0 && parameterIndex < numParameters);
    }
}
