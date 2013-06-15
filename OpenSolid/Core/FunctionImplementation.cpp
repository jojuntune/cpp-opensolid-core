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
 
#include <OpenSolid/Core/FunctionImplementation.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FunctionImplementation/ArccosineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ArcsineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ComponentsFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CompositionFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConcatenationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CosineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/DifferenceFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ExponentialFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LogarithmFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormalizedFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/PowerFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ProductFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/QuotientFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SquareRootFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SquaredNormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SumFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TangentFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TempScalingFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TempTransformationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TempTranslationFunction.hpp>

namespace opensolid
{
    const ConstantFunction*
    FunctionImplementation::asConstantImpl() const {
        return nullptr;
    }

    const IdentityFunction*
    FunctionImplementation::asIdentityImpl() const {
        return nullptr;
    }

    const ParameterFunction*
    FunctionImplementation::asParameterImpl() const {
        return nullptr;
    }

    // TODO - implement in subclasses and make pure virtual
    void
    FunctionImplementation::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        JacobianEvaluatorXd& cache
    ) const {
        throw FeatureNotImplemented();
    }
    
    // TODO - implement in subclasses and make pure virtual
    void
    FunctionImplementation::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        JacobianEvaluatorXI& cache
    ) const {
        throw FeatureNotImplemented();
    }

    FunctionImplementationPtr
    FunctionImplementation::composeImpl(const FunctionImplementation* innerFunction) const {
        return new CompositionFunction(this, innerFunction);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::componentsImpl(int startIndex, int numComponents) const {
        return new ComponentsFunction(this, startIndex, numComponents);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::scaledImpl(double scale) const {
        return new TempScalingFunction(scale, this);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::translatedImpl(const VectorXd& vector) const {
        return new TempTranslationFunction(this, vector);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::transformedImpl(const MatrixXd& transformationMatrix) const {
        return new TempTransformationFunction(transformationMatrix, this);
    }
    
    FunctionImplementationPr
    FunctionImplementation::normImpl() const {
        return new NormFunction(this);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalizedImpl() const {
        return new NormalizedFunction(this);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::squaredNormImpl() const {
        return new SquaredNormFunction(this);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::tangentVectorImpl() const {
        return derivative()->normalized();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::curvatureImpl() const {
        return tangentVector()->derivative()->norm()->quotient(derivative()->norm());
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalVectorImpl() const {
        if (numParameters() == 1) {
            return tangentVector()->derivative()->normalized();
        } else {
            return derivative(0)->crossProduct(derivative(1))->normalized();
        }
    }
    
    FunctionImplementationPtr
    FunctionImplementation::binormalVectorImpl() const {
        return tangentVector()->crossProduct(normalVector());
    }

    FunctionImplementationPtr
    FunctionImplementation::sqrtImpl() const {
        return new SquareRootFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::sinImpl() const {
        return new SineFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::cosImpl() const {
        return new CosineFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::tanImpl() const {
        return new TangentFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::acosImpl() const {
        return new ArccosineFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::asinImpl() const {
        return new ArcsineFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::expImpl() const {
        return new ExponentialFunction(this);
    }

    FunctionImplementationPtr
    FunctionImplementation::logImpl() const {
        return new LogarithmFunction(this);
    }

    FunctionImplementation::~FunctionImplementation() {
    }
    
    FunctionImplementationPtr
    FunctionImplementation::derivative(int parameterIndex) const {
        if (parameterIndex < 0 || parameterIndex >= numParameters()) {
            throw PlaceholderError();
        }
        return derivativeImpl(parameterIndex);
    }

    bool
    FunctionImplementation::isDuplicateOf(const FunctionImplementationPtr& other) const {
        if (this == other) {
            return true;
        }
        if (this->numDimensions() != other->numDimensions()) {
            return false;
        }
        if (this->numParameters() != other->numParameters()) {
            return false;
        }
        return this->isDuplicateOfImpl(other);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::deduplicated(Deduplicator& deduplicator) const {
        return deduplicatedImpl(deduplicator);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::compose(const FunctionImplementationPtr& innerFunction) const {
        if (innerFunction->numDimensions() != this->numParameters()) {
            throw PlaceholderError();
        }
        if (const ConstantFunction* constantFunction = innerFunction->asConstant()) {
            MapXcd argumentMap(
                constantFunction->vector().data(),
                constantFunction->numDimensions(),
                1,
                Stride<Dynamic, Dynamic>(1, 1)
            );
            
            VectorXd result(this->numDimensions());
            MapXd resultMap(
                result.data(),
                this->numDimensions(),
                1,
                Stride<Dynamic, Dynamic>(1, 1)
            );

            Evaluator evaluator;
            evaluate(argumentMap, resultMap, evaluator);
            
            return new ConstantFunction(result);
        }
        return this->composeImpl(innerFunction);
    }
     
    FunctionImplementationPtr
    FunctionImplementation::components(int startIndex, int numComponents) const {
        if (startIndex < 0 || numComponents < 1 || startIndex + numComponents > numDimensions()) {
            throw PlaceholderError();
        }
        if (numComponents == numDimensions()) {
            return this;
        }
        return componentsImpl(startIndex, numComponents);
    }

    FunctionImplementationPtr
    FunctionImplementation::component(int index) const {
        return components(index, 1);
    }

    FunctionImplementationPtr
    FunctionImplementation::x() const {
        return component(0);
    }

    FunctionImplementationPtr
    FunctionImplementation::y() const {
        return component(1);
    }

    FunctionImplementationPtr
    FunctionImplementation::z() const {
        return component(2);
    }

    FunctionImplementationPtr
    FunctionImplementation::concatenated(const FunctionImplementationPtr& other) const {
        if (this->asConstant() && other->asConstant()) {
            VectorXd vector(this->numDimensions() + other->numDimensions());
            vector.head(this->numDimensions()) = this->asConstant()->vector();
            vector.tail(other->numDimensions()) = other->asConstant()->vector();
            return new ConstantFunction(vector, numParameters());
        }
        return new ConcatenationFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::scaled(double scale) const {
        if (scale == Zero()) {
            return new ConstantFunction(VectorXd::Zero(numDimensions()), numParameters());
        }
        if (scale - 1 == Zero()) {
            return this;
        }
        if (scale + 1 == Zero()) {
            return negated();
        }
        return scaledImpl(scale);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::translated(const VectorXd& vector) const {
        if (vector.size() != numDimensions()) {
            throw PlaceholderError();
        }
        if (vector.isZero()) {
            return this;
        }
        return translatedImpl(vector);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::transformed(const MatrixXd& matrix) const {
        if (matrix.size() == 0) {
            throw PlaceholderError();
        }
        if (matrix.cols() != numDimensions()) {
            throw PlaceholderError();
        }
        if (matrix.isZero()) {
            return new ConstantFunction(VectorXd::Zero(matrix.rows()), numParameters());
        }
        if (matrix.rows() == matrix.cols() && matrix.isIdentity()) {
            return this;
        }
        return transformedImpl(matrix);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::norm() const {
        return normImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalized() const {
        return normalizedImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::squaredNorm() const {
        return squaredNormImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::tangentVector() const {
        if (numParameters() != 1) {
            throw PlaceholderError();
        }
        return tangentVectorImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::curvature() const {
        if (numParameters() != 1) {
            throw PlaceholderError();
        }
        return curvatureImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalVector() const {
        if (!(numParameters() == 1 || (numParameters() == 2 && numDimensions() == 3))) {
            throw PlaceholderError();
        }
        return normalVectorImpl();   
    }
    
    FunctionImplementationPtr
    FunctionImplementation::binormalVector() const {
        if (!(numParameters() == 1 && numDimensions() == 3)) {
            throw PlaceholderError();
        }
        return binormalVectorImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::negated() const {
        return negatedImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::sum(const FunctionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (const ConstantFunction* otherConstant = other->asConstant()) {
            return this->translated(otherConstant->vector());
        }
        if (const ConstantFunction* thisConstant = this->asConstant()) {
            return other->translated(thisConstant->vector());
        }
        return new SumFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::difference(const FunctionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (const ConstantFunction* otherConstant = other->asConstant()) {
            return this->translated(-otherConstant->vector());
        }
        if (const ConstantFunction* thisConstant = this->asConstant()) {
            return other->negated()->translated(thisConstant->vector());
        }
        return new DifferenceFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::product(const FunctionImplementationPtr& other) const {
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        // Determine which operand to use as the multiplier and which to use as the multiplicand:
        // The multiplier should be a scalar (one dimensional), and if possible should be constant
        // (to allow construction of a ScalingFunction instead of a generic ProductFunction).
        FunctionImplementationPtr multiplier;
        FunctionImplementationPtr multiplicand;
        if (this->numDimensions() == 1 && other.numDimensions() == 1) {
            // Either this or the other could be the multiplier, so pick whichever is constant
            // (defaulting to this)
            if (this->asConstant()) {
                multiplier = this;
                multiplicand = other;
            } else if (other.asConstant()) {
                multiplier = other;
                multiplicand = this;
            } else {
                multiplier = this;
                multiplicand = other;
            }
        } else if (this->numDimensions() == 1) {
            // Only this is a scalar, so use it as the multiplier
            multiplier = this;
            multiplicand = other;
        } else if (other.numDimensions() == 1) {
            // Only the other is a scalar, so use it as the multiplier
            multiplier = other;
            multiplicand = this;
        } else {
            // Error - neither operand is a scalar
            throw PlaceholderError();
        }
        if (const ConstantFunction* constant = multiplier->asConstant()) {
            // Delegate to scaling function
            return multiplicand->scaled(constant->value());
        } else if (multiplicand->asConstant() && multiplicand->asConstant()->vector().isZero()) {
            // Doesn't matter what the multiplier is - return the (zero) multiplicand
            return multiplicand;
        } else {
            return new ProductFunction(multiplier, multiplicand);
        }
    }

    FunctionImplementationPtr
    FunctionImplementation::quotient(const FunctionImplementationPtr& other) const {
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (other->numDimensions() != 1) {
            throw PlaceholderError();
        }
        if (const ConstantFunction* otherConstant = other.asConstant()) {
            double divisorValue = otherConstant->value();
            if (divisorValue == Zero()) {
                throw PlaceholderError();
            }
            return scaled(1 / divisorValue);
        } else if (this->asConstant() && this->asConstant()->vector().isZero()) {
            // Doesn't matter what the divisor is - return this (zero) dividend
            return this;
        } else {
            return new QuotientFunction(this, other);
        }
    }

    FunctionImplementationPtr
    FunctionImplementation::dotProduct(const FunctionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (this->asConstant() && other->asConstant()) {
            return new ConstantFunction(
                this->asConstant()->vector().dot(other->asConstant()->vector()),
                numParameters()
            );
        }
        if (numDimensions() == 1) {
            return this->product(other);
        }
        if (this->asConstant() && this->asConstant()->vector().isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        if (other->asConstant() && other->asConstant()->vector().isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        return new DotProductFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::crossProduct(const FunctionImplementationPtr& other) const {
        if (!(this->numDimensions() == 3 && other->numDimensions() == 3)) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (this->asConstant() && other->asConstant()) {
            Vector3d thisVector = this->asConstant()->vector();
            Vector3d otherVector = other->asConstant()->vector();
            return new ConstantFunction(thisVector.cross(otherVector), numParameters());
        }
        if (this->asConstant() && this->asConstant()->vector().isZero()) {
            return new ConstantFunction(Vector3d::Zero(), numParameters());
        }
        if (other->asConstant() && other->asConstant()->value().isZero()) {
            return new ConstantFunction(Vector3d::Zero(), numParameters());
        }
        return new CrossProductFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::sqrt() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return sqrtImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::sin() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return sinImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::cos() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return cosImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::tan() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return tanImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::acos() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return acosImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::asin() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return asinImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::exp() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return expImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::log() const {
        if (numDimensions() != 1) {
            throw PlaceholderError();
        }
        return logImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::pow(const FunctionImplementationPtr& other) const {
        if (this->numParameters() != other.numParameters()) {
            throw PlaceholderError();
        }
        if (!(this->numDimensions() == 1 && other->numDimensions() == 1)) {
            throw PlaceholderError();
        }
        const ConstantFunction* thisConstant = this->asConstant();
        const ConstantFunction* otherConstant = other->asConstant();
        if (thisConstant && otherConstant) {
            double baseValue = thisConstant->value();
            double exponentValue = otherConstant->value();
            if (baseValue == Zero() && exponentValue < Zero()) {
                throw PlaceholderError();
            }
            return new ConstantFunction(pow(baseValue, exponentValue), numParameters());
        } else {
            return new PowerFunction(this, other);
        }
    }

    void
    FunctionImplementation::debug(std::ostream& stream, int indent) const {
        for (int i = 0; i < indent; ++i) {
            stream << "  ";
        }
        stream << "R" << numParameters() << " -> R" << numDimensions() << " | ";
        stream << this << " | ";
        debugImpl(stream, indent);
    }
}
