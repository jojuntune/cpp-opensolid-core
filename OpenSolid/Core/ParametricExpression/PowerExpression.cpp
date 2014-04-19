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

#include <OpenSolid/Core/ParametricExpression/PowerExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{       
    int
    PowerExpression::numDimensionsImpl() const {
        return 1;
    }

    bool
    PowerExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }

    struct IntegerPower
    {
        int exponent;

        inline
        IntegerPower(int exponent_) :
            exponent(exponent_) {
        }

        inline
        double
        operator()(double base) const {
            return std::pow(base, exponent);
        }

        inline
        Interval
        operator()(const Interval& base) const {
            return pow(base, exponent);
        }
    };

    struct ConstantPower
    {
        double exponent;

        inline
        ConstantPower(double exponent_) :
            exponent(exponent_) {
        }

        inline
        Interval
        operator()(const Interval& base) const {
            return pow(base, exponent);
        }
    };

    struct Power
    {
        inline
        double
        operator()(double base, double exponent) const {
            return pow(base, exponent);
        }

        inline
        Interval
        operator()(const Interval& base, const Interval& exponent) const {
            return pow(base, exponent);
        }
    };
        
    void
    PowerExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd baseValues = evaluator.evaluate(firstOperand(), parameterView);
        if (_exponentIsInteger) {
            resultView = baseValues.unaryExpr(IntegerPower(_integerExponent));
        } else if (_exponentIsConstant) {
            resultView = baseValues.array().pow(_constantExponent);
        } else {
            MapXcd exponentValues = evaluator.evaluate(secondOperand(), parameterView);
            resultView = baseValues.binaryExpr(exponentValues, Power());
        }
    }

    void
    PowerExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI baseBounds = evaluator.evaluate(firstOperand(), parameterView);
        if (_exponentIsInteger) {
            resultView = baseBounds.unaryExpr(IntegerPower(_integerExponent));
        } else if (_exponentIsConstant) {
            resultView = baseBounds.array().unaryExpr(ConstantPower(_constantExponent));
        } else {
            MapXcI exponentBounds = evaluator.evaluate(secondOperand(), parameterView);
            resultView = baseBounds.binaryExpr(exponentBounds, Power());
        }
    }

    void
    PowerExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        double baseValue = evaluator.evaluate(firstOperand(), parameterView).value();
        if (baseValue <= Zero()) {
            throw Error(new PlaceholderError());
        }
        MapXcd baseJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        if (_exponentIsConstant) {
            resultView = _constantExponent * pow(baseValue, _constantExponent - 1) * baseJacobian;
        } else {
            double exponentValue = evaluator.evaluate(secondOperand(), parameterView).value();
            MapXcd exponentJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
            resultView = pow(baseValue, exponentValue) *
                (log(baseValue) * exponentJacobian + exponentValue * baseJacobian / baseValue);
        }
    }
    
    void
    PowerExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        Interval baseBounds = evaluator.evaluate(firstOperand(), parameterView).value();
        if (baseBounds.upperBound() <= Zero()) {
            throw Error(new PlaceholderError());
        }
        MapXcI baseJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        if (_exponentIsConstant) {
            resultView = _constantExponent * pow(baseBounds, Interval(_constantExponent - 1)) *
                baseJacobian;
        } else {
            Interval exponentBounds = evaluator.evaluate(secondOperand(), parameterView).value();
            MapXcI exponentJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
            resultView = pow(baseBounds, exponentBounds) *
                (log(baseBounds) * exponentJacobian + exponentBounds * baseJacobian / baseBounds);
        }
    }

    ExpressionImplementationPtr
    PowerExpression::derivativeImpl(int parameterIndex) const {
        if (_exponentIsConstant) {
            return _constantExponent *  pow(firstOperand(), secondOperand() - 1) *
                firstOperand()->derivative(parameterIndex);
        } else {
            return (
                secondOperand()->derivative(parameterIndex) * log(firstOperand()) +
                secondOperand() * firstOperand()->derivative(parameterIndex) / firstOperand()
            ) * self();
        }
    }
        
    void
    PowerExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "PowerExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    PowerExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return pow(newFirstOperand, newSecondOperand);
    }

    PowerExpression::PowerExpression(
        const ExpressionImplementationPtr& baseExpression,
        const ExpressionImplementationPtr& exponentExpression
    ) : BinaryOperation(baseExpression, exponentExpression) {

        assert(baseExpression->numDimensions() == 1);
        assert(exponentExpression->numDimensions() == 1);

        if (exponentExpression->isConstantExpression()) {
            _exponentIsConstant = true;
            _constantExponent = exponentExpression->cast<ConstantExpression>()->value();
            _integerExponent = int(floor(_constantExponent + 0.5));
            _exponentIsInteger = (_constantExponent - _integerExponent == Zero());
        } else {
            _exponentIsConstant = false;
            _exponentIsInteger = false;
            _constantExponent = 0.0;
            _integerExponent = 0;
        }
    }
}
