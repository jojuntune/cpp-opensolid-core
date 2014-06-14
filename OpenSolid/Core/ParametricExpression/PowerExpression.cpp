/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXd baseValues = evaluator.evaluate(firstOperand(), parameterView);
        if (_exponentIsInteger) {
            resultView.setMap(
                baseValues,
                [this] (double baseValue) {
                    return pow(baseValue, _integerExponent);
                }                
            );
        } else if (_exponentIsConstant) {
            resultView.setMap(
                baseValues,
                [this] (double baseValue) {
                    return pow(baseValue, _constantExponent);
                }             
            );
        } else {
            ConstMatrixViewXd exponentValues = evaluator.evaluate(secondOperand(), parameterView);
            resultView.setBinaryMap(
                exponentValues,
                [] (double baseValue, double exponentValue) {
                    return pow(baseValue, exponentValue);
                },
                baseValues
            );
        }
    }

    void
    PowerExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXd baseValues = evaluator.evaluate(firstOperand(), parameterView);
        if (_exponentIsInteger) {
            resultView.setMap(
                baseValues,
                [this] (Interval baseValue) {
                    return pow(baseValue, _integerExponent);
                }         
            );
        } else if (_exponentIsConstant) {
            resultView.setMap(
                baseValues,
                [this] (Interval baseValue) {
                    return pow(baseValue, _constantExponent);
                }            
            );
        } else {
            ConstIntervalMatrixViewXd exponentValues =
                evaluator.evaluate(secondOperand(), parameterView);
            resultView.setBinaryMap(
                exponentValues,
                [] (Interval baseValue, Interval exponentValue) {
                    return pow(baseValue, exponentValue);
                },
                baseValues
            );
        }
    }

    void
    PowerExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double baseValue = evaluator.evaluate(firstOperand(), parameterView).value();
        if (baseValue <= Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstMatrixViewXd baseJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        if (_exponentIsConstant) {
            resultView = _constantExponent * pow(baseValue, _constantExponent - 1) * baseJacobian;
        } else {
            double exponentValue = evaluator.evaluate(secondOperand(), parameterView).value();
            ConstMatrixViewXd exponentJacobian =
                evaluator.evaluateJacobian(secondOperand(), parameterView);
            resultView = pow(baseValue, exponentValue) *
                (log(baseValue) * exponentJacobian + exponentValue * baseJacobian / baseValue);
        }
    }
    
    void
    PowerExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval baseValue = evaluator.evaluate(firstOperand(), parameterView).value();
        if (baseValue.upperBound() <= Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstIntervalMatrixViewXd baseJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        if (_exponentIsConstant) {
            resultView = _constantExponent * pow(baseValue, _constantExponent - 1) * baseJacobian;
        } else {
            Interval exponentValue = evaluator.evaluate(secondOperand(), parameterView).value();
            ConstIntervalMatrixViewXd exponentJacobian =
                evaluator.evaluateJacobian(secondOperand(), parameterView);
            resultView = pow(baseValue, exponentValue) *
                (log(baseValue) * exponentJacobian + exponentValue * baseJacobian / baseValue);
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
