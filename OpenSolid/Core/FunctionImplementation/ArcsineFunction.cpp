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

#include <OpenSolid/Core/FunctionImplementation/ArcsineFunction.hpp>

namespace opensolid
{
    int
    ArcsineFunction::numDimensionsImpl() const {
        return 1;
    }

    struct Arcsine
    {
        inline double
        operator()(double value) const {
            Interval domain(-1, 1);
            assert(domain.contains(value));
            return asin(domain.clamp(value));
        }
        
        inline Interval
        operator()(const Interval& bounds) const {
            Interval domain(-1, 1);
            assert(domain.overlaps(bounds));
            return asin(domain.clamp(bounds));
        }
    };
    
    void
    ArcsineFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).unaryExpr(Arcsine());
    }
    
    void
    ArcsineFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).unaryExpr(Arcsine());
    }
    
    FunctionImplementationPtr
    ArcsineFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) / sqrt(1.0 - operand()->squaredNorm());
    }
    
    bool
    ArcsineFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    ArcsineFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ArcsineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    ArcsineFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return asin(newOperand);
    }

    ArcsineFunction::ArcsineFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {

        assert(operand->numDimensions() == 1);
    }
}
