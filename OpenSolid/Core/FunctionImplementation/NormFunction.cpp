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

#include <OpenSolid/Core/FunctionImplementation/NormFunction.hpp>

namespace opensolid
{
    NormFunction::NormFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
    
    int
    NormFunction::numDimensionsImpl() const {
        return 1;
    }

    bool
    NormFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    FunctionImplementationPtr
    NormFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return new NormFunction(operand()->deduplicated(deduplicationCache));
    }
    
    void
    NormFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).colwise().norm();
    }
    
    void 
    NormFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).colwise().norm();
    }

    FunctionImplementationPtr
    NormFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex).dot(operand().normalized());
    }
    
    void
    NormFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "NormFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }
}
