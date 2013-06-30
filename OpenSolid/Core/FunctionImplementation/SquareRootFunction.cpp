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

#include <OpenSolid/Core/FunctionImplementation/SquareRootFunction.hpp>

namespace opensolid
{
    SquareRootFunction::SquareRootFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
    
    int
    SquareRootFunction::numDimensionsImpl() const {
        return 1;
    }

    bool
    SquareRootFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    FunctionImplementationPtr
    SquareRootFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return new SquareRootFunction(operand()->deduplicated(deduplicationCache));
    }
    
    struct SquareRoot
    {
        inline double
        operator()(double value) const {
            assert(value >= Zero());
            return value > 0.0 ? sqrt(value) : 0.0;
        }
        
        inline Interval
        operator()(const Interval& bounds) const {
            assert(bounds >= Zero());
            return Interval(operator()(bounds.lowerBound()), operator()(bounds.upperBound()));
        }
    };
    
    void
    SquareRootFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).unaryExpr(SquareRoot());
    }
    
    void
    SquareRootFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).unaryExpr(SquareRoot());
    }

    FunctionImplementationPtr
    SquareRootFunction::derivativeImpl(int parameterIndex) const {
        return 0.5 * operand()->derivative(parameterIndex) / self();
    }
    
    FunctionImplementationPtr
    SquareRootFunction::squaredNorm() const {
        return operand().norm();
    }
    
    void
    SquareRootFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "SquareRootFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }
}
