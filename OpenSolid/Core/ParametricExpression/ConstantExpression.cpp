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
        return vector().size();
    }
        
    int
    ConstantExpression::numParametersImpl() const {
        return _numParameters;
    }
    
    void
    ConstantExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results.colwise() = vector();
    }
    
    void
    ConstantExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results.colwise() = bounds();
    }

    void
    ConstantExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
    }
    
    void
    ConstantExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
    }
    
    ExpressionImplementationPtr
    ConstantExpression::derivativeImpl(int) const {
        return new ConstantExpression(VectorXd::Zero(numDimensions()), numParameters());
    }
    
    bool
    ConstantExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return (this->vector() - other->cast<ConstantExpression>()->vector()).isZero();
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
            vector().middleRows(startIndex, numComponents),
            numParameters()
        );
    }
    
    ExpressionImplementationPtr
    ConstantExpression::scalarMultiplicationImpl(double scale) const {
        return new ConstantExpression(scale * vector(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::vectorAdditionImpl(const VectorXd& vector) const {
        return new ConstantExpression(this->vector() + vector, numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new ConstantExpression(matrix * vector(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::normImpl() const {
        return new ConstantExpression(vector().norm(), numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::normalizedImpl() const {
        double norm = vector().norm();
        if (norm == Zero()) {
            throw Error(new PlaceholderError());
        }
        return new ConstantExpression(vector() / norm, numParameters());
    }
    
    ExpressionImplementationPtr
    ConstantExpression::squaredNormImpl() const {
        return new ConstantExpression(vector().squaredNorm(), numParameters());
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
        stream << "ConstantExpression: " << vector().transpose() << std::endl;
    }

    ConstantExpression::ConstantExpression(const VectorXd& vector, int numParameters) :
        _vector(vector),
        _bounds(vector.cast<Interval>()),
        _numParameters(numParameters) {
    }

    ConstantExpression::ConstantExpression(double value, int numParameters) :
        _vector(VectorXd::Constant(1, value)),
        _bounds(VectorXI::Constant(1, Interval(value))),
        _numParameters(numParameters) {
    }
}
