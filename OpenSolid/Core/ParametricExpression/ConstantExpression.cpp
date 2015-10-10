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

#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        ConstantExpression::numDimensionsImpl() const {
            return int(columnMatrix().numComponents());
        }
            
        int
        ConstantExpression::numParametersImpl() const {
            return _numParameters;
        }
        
        void
        ConstantExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [this] (MatrixViewXd results) {
                    results = ConstMatrixViewXd(
                        columnMatrix().data(),
                        numDimensions(),
                        results.numColumns(),
                        0
                    );
                }
            );
        }
        
        void
        ConstantExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [this] (IntervalMatrixViewXd results) {
                    results = ConstIntervalMatrixViewXd(
                        intervalColumnMatrix().data(),
                        numDimensions(),
                        results.numColumns(),
                        0
                    );
                }
            );
        }

        void
        ConstantExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [] (MatrixViewXd results) {
                    results.setZero();
                }
            );
        }
        
        void
        ConstantExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [] (IntervalMatrixViewXd results) {
                    results.setZero();
                }
            );
        }
        
        ExpressionImplementationPtr
        ConstantExpression::derivativeImpl(int) const {
            return std::make_shared<ConstantExpression>(
                ColumnMatrixXd::zero(numDimensions()),
                numParameters()
            );
        }
        
        bool
        ConstantExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return (columnMatrix() - other->cast<ConstantExpression>()->columnMatrix()).isZero();
        }

        ExpressionImplementationPtr
        ConstantExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
            return self();
        }
        
        ExpressionImplementationPtr
        ConstantExpression::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
            return self();
        }
        
        ExpressionImplementationPtr
        ConstantExpression::componentsImpl(int startIndex, int numComponents) const {
            return std::make_shared<ConstantExpression>(
                columnMatrix().block(startIndex, 0, numComponents, 1),
                numParameters()
            );
        }
        
        ExpressionImplementationPtr
        ConstantExpression::scalingImpl(double scale) const {
            return std::make_shared<ConstantExpression>(scale * columnMatrix(), numParameters());
        }
        
        ExpressionImplementationPtr
        ConstantExpression::translationImpl(const ColumnMatrixXd& columnMatrix) const {
            return std::make_shared<ConstantExpression>(
                this->columnMatrix() + columnMatrix,
                numParameters()
            );
        }
        
        ExpressionImplementationPtr
        ConstantExpression::transformationImpl(const MatrixXd& matrix) const {
            return std::make_shared<ConstantExpression>(matrix * columnMatrix(), numParameters());
        }
        
        ExpressionImplementationPtr
        ConstantExpression::normImpl() const {
            return std::make_shared<ConstantExpression>(
                opensolid::sqrt(columnMatrix().cwiseSquared().sum()),
                numParameters()
            );
        }
        
        ExpressionImplementationPtr
        ConstantExpression::normalizedImpl() const {
            double norm = opensolid::sqrt(columnMatrix().cwiseSquared().sum());
            if (norm == Zero()) {
                throw Error(new PlaceholderError());
            }
            return std::make_shared<ConstantExpression>(columnMatrix() / norm, numParameters());
        }
        
        ExpressionImplementationPtr
        ConstantExpression::squaredNormImpl() const {
            return std::make_shared<ConstantExpression>(
                columnMatrix().cwiseSquared().sum(),
                numParameters()
            );
        }

        ExpressionImplementationPtr
        ConstantExpression::sqrtImpl() const {
            if (value() >= 0.0) {
                return std::make_shared<ConstantExpression>(
                    opensolid::sqrt(value()),
                    numParameters()
                );
            } else if (value() == Zero()) {
                return std::make_shared<ConstantExpression>(0.0, numParameters());
            } else {
                throw Error(new PlaceholderError());
            }
        }

        ExpressionImplementationPtr
        ConstantExpression::sinImpl() const {
            return std::make_shared<ConstantExpression>(opensolid::sin(value()), numParameters());
        }

        ExpressionImplementationPtr
        ConstantExpression::cosImpl() const {
            return std::make_shared<ConstantExpression>(opensolid::cos(value()), numParameters());
        }

        ExpressionImplementationPtr
        ConstantExpression::tanImpl() const {
            if (std::fmod(value() - M_PI / 2, M_PI) == Zero()) {
                throw Error(new PlaceholderError());
            }
            return std::make_shared<ConstantExpression>(opensolid::tan(value()), numParameters());
        }

        ExpressionImplementationPtr
        ConstantExpression::acosImpl() const {
            if (-1.0 <= value() && value() <= 1.0) {
                return std::make_shared<ConstantExpression>(
                    opensolid::acos(value()),
                    numParameters()
                );
            } else if (value() + 1.0 == Zero()) {
                return std::make_shared<ConstantExpression>(M_PI, numParameters());
            } else if (value() - 1.0 == Zero()) {
                return std::make_shared<ConstantExpression>(0.0, numParameters());
            } else {
                throw Error(new PlaceholderError());
            }
        }

        ExpressionImplementationPtr
        ConstantExpression::asinImpl() const {
            if (-1.0 <= value() && value() <= 1.0) {
                return std::make_shared<ConstantExpression>(
                    opensolid::asin(value()),
                    numParameters()
                );
            } else if (value() + 1.0 == Zero()) {
                return std::make_shared<ConstantExpression>(-M_PI / 2.0, numParameters());
            } else if (value() - 1.0 == Zero()) {
                return std::make_shared<ConstantExpression>(M_PI / 2.0, numParameters());
            } else {
                throw Error(new PlaceholderError());
            }
        }

        ExpressionImplementationPtr
        ConstantExpression::expImpl() const {
            return std::make_shared<ConstantExpression>(opensolid::exp(value()), numParameters());
        }

        ExpressionImplementationPtr
        ConstantExpression::logImpl() const {
            if (value() <= Zero()) {
                throw Error(new PlaceholderError());
            }
            return std::make_shared<ConstantExpression>(opensolid::log(value()), numParameters());
        }

        void
        ConstantExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "ConstantExpression: " << columnMatrix() << std::endl;
        }

        ConstantExpression::ConstantExpression(
            const ColumnMatrixXd& columnMatrix,
            int numParameters
        ) : _columnMatrix(columnMatrix),
            _intervalColumnMatrix(
                columnMatrix.map(
                    [] (double component) {
                        return Interval(component);
                    }
                )
            ),
            _numParameters(numParameters) {
        }

        ConstantExpression::ConstantExpression(double value, int numParameters) :
            _columnMatrix(ColumnMatrixXd::constant(1, value)),
            _intervalColumnMatrix(IntervalColumnMatrixXd::constant(1, Interval(value))),
            _numParameters(numParameters) {
        }
    }
}
