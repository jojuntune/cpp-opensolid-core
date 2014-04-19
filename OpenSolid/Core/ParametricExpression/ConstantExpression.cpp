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

#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    ConstantExpression::numDimensionsImpl() const {
        return int(columnMatrix().size());
    }
        
    int
    ConstantExpression::numParametersImpl() const {
        return _numParameters;
    }
    
    void
    ConstantExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator&
    ) const {
        resultView.colwise() = columnMatrix();
    }
    
    void
    ConstantExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator&
    ) const {
        resultView.colwise() = columnMatrixXI();
    }

    void
    ConstantExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.setZero();
    }
    
    void
    ConstantExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.setZero();
    }
    
    ExpressionImplementationPtr
    ConstantExpression::derivativeImpl(int) const {
        return new ConstantExpression(ColumnMatrixXx1::Zero(numDimensions()), numParameters());
    }
    
    bool
    ConstantExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return (columnMatrix() - other->cast<ConstantExpression>()->columnMatrix()).isZero();
    }

    ExpressionImplementationPtr
    ConstantExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    ExpressionImplementationPtr
    ConstantExpression::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
        return this;
    }
    
    ExpressionImplementationPtr
    ConstantExpression::componentsImpl(int startIndex, int numComponents) const {
        return new ConstantExpression(
            columnMatrix().middleRows(startIndex, numComponents),
            numParameters()
        );
    }
    
    ExpressionImplementationPtr
    ConstantExpression::scalingImpl(double scale) const {
        return new ConstantExpression(scale * columnMatrix(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::translationImpl(const ColumnMatrixXd& columnMatrix) const {
        return new ConstantExpression(this->columnMatrix() + columnMatrix, numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::transformationImpl(const MatrixXxX& matrix) const {
        return new ConstantExpression(matrix * columnMatrix(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::normImpl() const {
        return new ConstantExpression(columnMatrix().norm(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::normalizedImpl() const {
        double norm = columnMatrix().norm();
        if (norm == Zero()) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(columnMatrix() / norm, numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::squaredNormImpl() const {
        return new ConstantExpression(columnMatrix().squaredNorm(), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::sqrtImpl() const {
        Interval domain(0, INFINITY);
        if (!domain.contains(value())) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(sqrt(domain.clamp(value())), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::sinImpl() const {
        return new ConstantExpression(sin(value()), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::cosImpl() const {
        return new ConstantExpression(cos(value()), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::tanImpl() const {
        if (std::fmod(value() - M_PI / 2, M_PI) == Zero()) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(tan(value()), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::acosImpl() const {
        Interval domain(-1, 1);
        if (!domain.contains(value())) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(acos(domain.clamp(value())), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::asinImpl() const {
        Interval domain(-1, 1);
        if (!domain.contains(value())) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(asin(domain.clamp(value())), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::expImpl() const {
        return new ConstantExpression(exp(value()), numParameters());
    }

    ExpressionImplementationPtr
    ConstantExpression::logImpl() const {
        if (value() <= Zero()) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(log(value()), numParameters());
    }

    void
    ConstantExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ConstantExpression: " << columnMatrix().transpose() << std::endl;
    }

    ConstantExpression::ConstantExpression(
        const ColumnMatrixXd& columnMatrix,
        int numParameters
    ) : _columnMatrix(columnMatrix),
        _columnMatrixXI(columnMatrix.cast<Interval>()),
        _numParameters(numParameters) {
    }

    ConstantExpression::ConstantExpression(double value, int numParameters) :
        _columnMatrix(ColumnMatrixXd::Constant(1, value)),
        _columnMatrixXI(ColumnMatrixXI::Constant(1, Interval(value))),
        _numParameters(numParameters) {
    }
}
