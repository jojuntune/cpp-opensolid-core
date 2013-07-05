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

#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    int
    ConstantFunction::numDimensionsImpl() const {
        return vector().size();
    }
        
    int
    ConstantFunction::numParametersImpl() const {
        return _numParameters;
    }
    
    void
    ConstantFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results.colwise() = vector();
    }
    
    void
    ConstantFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results.colwise() = bounds();
    }

    void
    ConstantFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
    }
    
    void
    ConstantFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results.setZero();
    }
    
    FunctionImplementationPtr
    ConstantFunction::derivativeImpl(int) const {
        return new ConstantFunction(VectorXd::Zero(numDimensions()), numParameters());
    }
    
    bool
    ConstantFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return (this->vector() - other->cast<ConstantFunction>()->vector()).isZero();
    }

    FunctionImplementationPtr
    ConstantFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    FunctionImplementationPtr
    ConstantFunction::composedImpl(const FunctionImplementationPtr& innerFunction) const {
        return this;
    }
    
    FunctionImplementationPtr
    ConstantFunction::componentsImpl(int startIndex, int numComponents) const {
        return new ConstantFunction(
            vector().middleRows(startIndex, numComponents),
            numParameters()
        );
    }
    
    FunctionImplementationPtr
    ConstantFunction::scalarMultiplicationImpl(double scale) const {
        return new ConstantFunction(scale * vector(), numParameters());
    }
    
    FunctionImplementationPtr
    ConstantFunction::vectorAdditionImpl(const VectorXd& vector) const {
        return new ConstantFunction(this->vector() + vector, numParameters());
    }
    
    FunctionImplementationPtr
    ConstantFunction::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new ConstantFunction(matrix * vector(), numParameters());
    }
    
    FunctionImplementationPtr
    ConstantFunction::normImpl() const {
        return new ConstantFunction(vector().norm(), numParameters());
    }
    
    FunctionImplementationPtr
    ConstantFunction::normalizedImpl() const {
        double norm = vector().norm();
        if (norm == Zero()) {
            throw PlaceholderError();
        }
        return new ConstantFunction(vector() / norm, numParameters());
    }
    
    FunctionImplementationPtr
    ConstantFunction::squaredNormImpl() const {
        return new ConstantFunction(vector().squaredNorm(), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::sqrtImpl() const {
        Interval domain(0, infinity());
        if (!domain.contains(value())) {
            throw PlaceholderError();
        }
        return new ConstantFunction(sqrt(domain.clamp(value())), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::sinImpl() const {
        return new ConstantFunction(sin(value()), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::cosImpl() const {
        return new ConstantFunction(cos(value()), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::tanImpl() const {
        if (std::fmod(value() - M_PI / 2, M_PI) == Zero()) {
            throw PlaceholderError();
        }
        return new ConstantFunction(tan(value()), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::acosImpl() const {
        Interval domain(-1, 1);
        if (!domain.contains(value())) {
            throw PlaceholderError();
        }
        return new ConstantFunction(acos(domain.clamp(value())), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::asinImpl() const {
        Interval domain(-1, 1);
        if (!domain.contains(value())) {
            throw PlaceholderError();
        }
        return new ConstantFunction(asin(domain.clamp(value())), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::expImpl() const {
        return new ConstantFunction(exp(value()), numParameters());
    }

    FunctionImplementationPtr
    ConstantFunction::logImpl() const {
        if (value() <= Zero()) {
            throw PlaceholderError();
        }
        return new ConstantFunction(log(value()), numParameters());
    }

    void
    ConstantFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ConstantFunction: " << vector().transpose() << std::endl;
    }

    ConstantFunction::ConstantFunction(const VectorXd& vector, int numParameters) :
        _vector(vector),
        _bounds(vector.cast<Interval>()),
        _numParameters(numParameters) {
    }

    ConstantFunction::ConstantFunction(double value, int numParameters) :
        _vector(VectorXd::Constant(1, value)),
        _bounds(VectorXI::Constant(1, Interval(value))),
        _numParameters(numParameters) {
    }
}
