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

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{   
    int
    SquareRootFunction::numDimensionsImpl() const {
        return 1;
    }
    
    struct SquareRoot
    {
        inline double
        operator()(double value) const {
            assert(value >= Zero());
            return value > 0.0 ? sqrt(value) : 0.0;
        }
        
        inline Interval
        operator()(Interval bounds) const {
            assert(bounds.upperBound() >= Zero());
            return sqrt(bounds);
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

    void
    SquareRootFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        if (operandValue <= Zero()) {
            throw PlaceholderError();
        }
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = 0.5 * operandJacobian / sqrt(operandValue);
    }
    
    void
    SquareRootFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterBounds).value();
        if (operandBounds <= Zero()) {
            throw PlaceholderError();
        }
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = Interval(0.5) * operandJacobian / sqrt(operandBounds);
    }

    FunctionImplementationPtr
    SquareRootFunction::derivativeImpl(int parameterIndex) const {
        return 0.5 * operand()->derivative(parameterIndex) / self();
    }

    bool
    SquareRootFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    FunctionImplementationPtr
    SquareRootFunction::squaredNormImpl() const {
        return operand();
    }
    
    void
    SquareRootFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "SquareRootFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    SquareRootFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return sqrt(newOperand);
    }

    SquareRootFunction::SquareRootFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
