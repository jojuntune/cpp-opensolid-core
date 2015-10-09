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
    namespace detail
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
                return opensolid::pow(base, exponent);
            }

            inline
            Interval
            operator()(const Interval& base, const Interval& exponent) const {
                return opensolid::pow(base, exponent);
            }
        };
            
        void
        PowerExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            if (_exponentIsInteger) {
                int integerExponent = _integerExponent;
                expressionCompiler.compute(
                    resultID,
                    [integerExponent] (MatrixViewXd results) {
                        results.setMap(
                            results,
                            [integerExponent] (double baseValue) {
                                return opensolid::pow(baseValue, integerExponent);
                            }
                        );
                    }
                );
            } else if (_exponentIsConstant) {
                double constantExponent = _constantExponent;
                expressionCompiler.compute(
                    resultID,
                    [constantExponent] (MatrixViewXd results) {
                        results.setMap(
                            results,
                            [constantExponent] (double baseValue) {
                                return opensolid::pow(baseValue, constantExponent);
                            }
                        );
                    }
                );
            } else {
                expressionCompiler.compute(
                    expressionCompiler.evaluate(secondOperand(), parameterID),
                    resultID,
                    [] (ConstMatrixViewXd exponentValues, MatrixViewXd results) {
                        results.setBinaryMap(
                            results,
                            exponentValues,
                            [] (double baseValue, double exponentValue) {
                                return opensolid::pow(baseValue, exponentValue);
                            }
                        );
                    }
                );
            }
        }

        void
        PowerExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            if (_exponentIsInteger) {
                int integerExponent = _integerExponent;
                expressionCompiler.compute(
                    resultID,
                    [integerExponent] (IntervalMatrixViewXd results) {
                        results.setMap(
                            results,
                            [integerExponent] (Interval baseValue) {
                                return opensolid::pow(baseValue, integerExponent);
                            }
                        );
                    }
                );
            } else if (_exponentIsConstant) {
                double constantExponent = _constantExponent;
                expressionCompiler.compute(
                    resultID,
                    [constantExponent] (IntervalMatrixViewXd results) {
                        results.setMap(
                            results,
                            [constantExponent] (Interval baseValue) {
                                return opensolid::pow(baseValue, constantExponent);
                            }
                        );
                    }
                );
            } else {
                expressionCompiler.compute(
                    expressionCompiler.evaluate(secondOperand(), parameterID),
                    resultID,
                    [] (ConstIntervalMatrixViewXd exponentValues, IntervalMatrixViewXd results) {
                        results.setBinaryMap(
                            results,
                            exponentValues,
                            [] (Interval baseValue, Interval exponentValue) {
                                return opensolid::pow(baseValue, exponentValue);
                            }
                        );
                    }
                );
            }
        }

        void
        PowerExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            if (_exponentIsConstant) {
                double constantExponent = _constantExponent;
                expressionCompiler.compute(
                    expressionCompiler.evaluate(firstOperand(), parameterID),
                    resultID,
                    [constantExponent] (
                        ConstMatrixViewXd baseValues,
                        MatrixViewXd results
                    ) {
                        double baseValue = baseValues.value();
                        if (baseValue <= Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        results *= (
                            constantExponent * opensolid::pow(baseValue, constantExponent - 1.0)
                        );
                    }
                );
            } else {
                expressionCompiler.compute(
                    expressionCompiler.evaluate(firstOperand(), parameterID),
                    expressionCompiler.evaluate(secondOperand(), parameterID),
                    expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                    expressionCompiler.createTemporary(numDimensions(), numParameters()),
                    resultID,
                    [] (
                        ConstMatrixViewXd baseValues,
                        ConstMatrixViewXd exponentValues,
                        ConstMatrixViewXd exponentJacobian,
                        MatrixViewXd scaledExponentJacobian,
                        MatrixViewXd results
                    ) {
                        double baseValue = baseValues.value();
                        if (baseValue <= Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        double exponentValue = exponentValues.value();
                        scaledExponentJacobian = exponentJacobian;
                        scaledExponentJacobian *= opensolid::log(baseValue);
                        results *= (exponentValue / baseValue);
                        results += scaledExponentJacobian;
                        results *= opensolid::pow(baseValue, exponentValue);
                    }
                );
            }
        }
        
        void
        PowerExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            if (_exponentIsConstant) {
                double constantExponent = _constantExponent;
                expressionCompiler.compute(
                    expressionCompiler.evaluate(firstOperand(), parameterID),
                    resultID,
                    [constantExponent] (
                        ConstIntervalMatrixViewXd baseValues,
                        IntervalMatrixViewXd results
                    ) {
                        Interval baseValue = baseValues.value();
                        if (baseValue.upperBound() <= Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        results *= (
                            constantExponent * opensolid::pow(baseValue, constantExponent - 1.0)
                        );
                    }
                );
            } else {
                expressionCompiler.compute(
                    expressionCompiler.evaluate(firstOperand(), parameterID),
                    expressionCompiler.evaluate(secondOperand(), parameterID),
                    expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                    expressionCompiler.createTemporary(numDimensions(), numParameters()),
                    resultID,
                    [] (
                        ConstIntervalMatrixViewXd baseValues,
                        ConstIntervalMatrixViewXd exponentValues,
                        ConstIntervalMatrixViewXd exponentJacobian,
                        IntervalMatrixViewXd scaledExponentJacobian,
                        IntervalMatrixViewXd results
                    ) {
                        Interval baseValue = baseValues.value();
                        if (baseValue.upperBound() <= Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        Interval exponentValue = exponentValues.value();
                        scaledExponentJacobian = exponentJacobian;
                        scaledExponentJacobian *= opensolid::log(baseValue);
                        results *= (exponentValue / baseValue);
                        results += scaledExponentJacobian;
                        results *= opensolid::pow(baseValue, exponentValue);
                    }
                );
            }
        }

        ExpressionImplementationPtr
        PowerExpression::derivativeImpl(int parameterIndex) const {
            if (_exponentIsConstant) {
                return (
                    _constantExponent *  pow(firstOperand(), secondOperand() - 1) *
                    firstOperand()->derivative(parameterIndex)
                );
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
}
