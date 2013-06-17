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

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ParameterFunction::ParameterFunction(int numParameters, int parameterIndex) :
        _numParameters(numParameters),
        _parameterIndex(parameterIndex) {

        assert(numParameters > 0);
        assert(parameterIndex >= 0 && parameterIndex < numParameters);
    }

    int ParameterFunction::numParameters() const {
        return _numParameters;
    }

    int ParameterFunction::numDimensions() const {
        return 1;
    }

    bool ParameterFunction::isDuplicateOf(const Function& function) const {
        const ParameterFunction* other =
            dynamic_cast<const ParameterFunction*>(function.implementation());
        if (other) {
            return this->numParameters() == other->numParameters() &&
                this->index() == other->index();
        } else {
            return false;
        }
    }

    Function ParameterFunction::deduplicated(DeduplicationCache&) const {
        return this;
    }
    
    void ParameterFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results = parameterValues.row(parameterIndex());
    }
    
    void ParameterFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results = parameterBounds.row(parameterIndex());
    }

    Function ParameterFunction::derivative(int index) const {
        return Function::Constant(index == this->parameterIndex() ? 1.0 : 0.0, numParameters());
    }
    
    Function ParameterFunction::compose(const Function& innerFunction) const {
        return innerFunction.components(parameterIndex(), 1);
    }
    
    void ParameterFunction::debug(std::ostream& stream, int indent) const {
        stream << "ParameterFunction: parameter index = " << parameterIndex() << std::endl;
    }
}
