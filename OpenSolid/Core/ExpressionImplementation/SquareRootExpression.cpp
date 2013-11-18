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

#include <OpenSolid/Core/ExpressionImplementation/SquareRootExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    SquareRootExpression::numDimensionsImpl() const {
        return 1;
    }
    
    struct SquareRoot
    {
        inline
        double
        operator()(double value) const {
            assert(value >= Zero());
            return value > 0.0 ? sqrt(value) : 0.0;
        }
        
        inline
        Interval
        operator()(Interval bounds) const {
            assert(bounds.upperBound() >= Zero());
            return sqrt(bounds);
        }
    };
    
    void
    SquareRootExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).unaryExpr(SquareRoot());
    }
    
    void
    SquareRootExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).unaryExpr(SquareRoot());
    }

    void
    SquareRootExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        if (operandValue <= Zero()) {
            throw Error(new PlaceholderError());
        }
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = 0.5 * operandJacobian / sqrt(operandValue);
    }
    
    void
    SquareRootExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterBounds).value();
        if (operandBounds <= Zero()) {
            throw Error(new PlaceholderError());
        }
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = Interval(0.5) * operandJacobian / sqrt(operandBounds);
    }

    ExpressionImplementationPtr
    SquareRootExpression::derivativeImpl(int parameterIndex) const {
        return 0.5 * operand()->derivative(parameterIndex) / self();
    }

    bool
    SquareRootExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    ExpressionImplementationPtr
    SquareRootExpression::squaredNormImpl() const {
        return operand();
    }
    
    void
    SquareRootExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "SquareRootExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    SquareRootExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return sqrt(newOperand);
    }

    SquareRootExpression::SquareRootExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
