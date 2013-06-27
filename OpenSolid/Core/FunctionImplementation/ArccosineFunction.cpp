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

#include <OpenSolid/Core/FunctionImplementation/ArccosineFunction.hpp>

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    int
    ArccosineFunction::numDimensionsImpl() const {
        return 1;
    }

    struct Arccosine
    {
        inline double operator()(double value) const {
            Interval domain(-1, 1);
            assert(domain.contains(value));
            return acos(domain.clamp(value));
        }
        
        inline Interval operator()(const Interval& bounds) const {
            Interval domain(-1, 1);
            assert(domain.overlaps(bounds));
            return acos(domain.clamp(bounds));
        }
    };
    
    void
    ArccosineFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).unaryExpr(Arccosine());
    }
    
    void
    ArccosineFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).unaryExpr(Arccosine());
    }
    
    FunctionImplementationPtr
    ArccosineFunction::derivativeImpl(int index) const {
        return -operand()->derivative(index) / sqrt(1.0 - operand()->squaredNorm());
    }
    
    bool
    ArccosineFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    ArccosineFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ArccosineFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    ArccosineFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return new ArccosineFunction(newOperand);
    }

    ArccosineFunction::ArccosineFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {

        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
    }
}
