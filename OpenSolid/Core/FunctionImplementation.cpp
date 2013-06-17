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
#include <OpenSolid/Core/FunctionImplementation/DeduplicationCache.hpp>
#include <OpenSolid/Core/FunctionImplementation/DifferenceFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ExponentialFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LogarithmFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NegatedFunction.hpp>
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
    
    FunctionImplementationPtr
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
    FunctionImplementation::negatedImpl() const {
        return new NegatedFunction(this);
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
        if (this == other.get()) {
            return true;
        }
        if (typeid(this) != typeid(other.get())) {
            return false;
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
    FunctionImplementation::deduplicated(DeduplicationCache& deduplicationCache) const {
        // Try to find a function implementation in the cache that this is a duplicate of
        auto iterator = std::find_if(
            deduplicationCache.begin(),
            deduplicationCache.end(),
            [&functionImplementation] (
                const FunctionImplementationPtr& cachedFunctionImplementation
            ) -> bool {
                return this->isDuplicateOf(cachedFunctionImplementation);
            }
        );

        // Return the cached duplicate if one was found
        if (iterator != deduplicationCache.end()) {
            return *iterator;
        }

        // No matching function implementation was found: add a deduplicated copy of this
        // function implementation to the list, then return it.
        FunctionImplementationPtr result = deduplicatedImpl(deduplicationCache);
        deduplicationCache.add(result);
        return result;
    }
    
    FunctionImplementationPtr
    FunctionImplementation::compose(const FunctionImplementationPtr& innerFunction) const {
        if (innerFunction->numDimensions() != this->numParameters()) {
            throw PlaceholderError();
        }
        if (innerFunction->isConstant()) {
            MapXcd argumentMap(
                innerFunction->cast<ConstantFunction>()->vector().data(),
                innerFunction->numDimensions(),
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
            
            return new ConstantFunction(result, innerFunction->numParameters());
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
        if (this->isConstant() && other->isConstant()) {
            VectorXd vector(this->numDimensions() + other->numDimensions());
            vector.head(this->numDimensions()) = this->cast<ConstantFunction>()->vector();
            vector.tail(other->numDimensions()) = other->cast<ConstantFunction>()->vector();
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
    FunctionImplementation::dot(const FunctionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (this->isConstant() && other->isConstant()) {
            VectorXd thisVector = this->cast<ConstantFunction>()->vector();
            VectorXd otherVector = other->cast<ConstantFunction>()->vector();
            return new ConstantFunction(thisVector.dot(otherVector), numParameters());
        }
        if (numDimensions() == 1) {
            return this->product(other);
        }
        if (this->isConstant() && this->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        if (other->isConstant() && other->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        return new DotProductFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::cross(const FunctionImplementationPtr& other) const {
        if (!(this->numDimensions() == 3 && other->numDimensions() == 3)) {
            throw PlaceholderError();
        }
        if (this->numParameters() != other->numParameters()) {
            throw PlaceholderError();
        }
        if (this->isConstant() && other->isConstant()) {
            Vector3d thisVector = this->cast<ConstantFunction>()->vector();
            Vector3d otherVector = other->cast<ConstantFunction>()->vector();
            return new ConstantFunction(thisVector.cross(otherVector), numParameters());
        }
        if (this->isConstant() && this->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(Vector3d::Zero(), numParameters());
        }
        if (other->isConstant() && other->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(Vector3d::Zero(), numParameters());
        }
        return new CrossProductFunction(this, other);
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

    FunctionImplementationPtr
    operator-(const FunctionImplementationPtr& operand) {
        return operand->negatedImpl();
    }

    FunctionImplementationPtr
    operator+(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numDimensions() != secondOperand->numDimensions()) {
            throw PlaceholderError();
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw PlaceholderError();
        }
        if (secondOperand->isConstant()) {
            return firstOperand->translated(secondOperand->cast<ConstantFunction>()->vector());
        }
        if (firstOperand->isConstant()) {
            return secondOperand->translated(firstOperand->cast<ConstantFunction>()->vector());
        }
        return new SumFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator+(const FunctionImplementationPtr& firstOperand, const VectorXd& secondOperand) {
        return firstOperand + new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator+(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) + secondOperand;
    }

    FunctionImplementationPtr
    operator+(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand + new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator+(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) + secondOperand;
    }

    FunctionImplementationPtr
    operator-(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numDimensions() != secondOperand->numDimensions()) {
            throw PlaceholderError();
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw PlaceholderError();
        }
        if (secondOperand->isConstant()) {
            VectorXd secondVector = secondOperand->cast<ConstantFunction>()->vector();
            return firstOperand->translated(-secondVector);
        }
        if (firstOperand->isConstant()) {
            VectorXd firstVector = firstOperand->cast<ConstantFunction>()->vector();
            return (-secondOperand)->translated(firstVector);
        }
        return new DifferenceFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator-(const FunctionImplementationPtr& firstOperand, const VectorXd& secondOperand) {
        return firstOperand - new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator-(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) - secondOperand;
    }

    FunctionImplementationPtr
    operator-(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand - new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator-(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) - secondOperand;
    }

    FunctionImplementationPtr
    operator*(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw PlaceholderError();
        }
        // Determine which operand to use as the multiplier and which to use as the multiplicand:
        // The multiplier should be a scalar (one dimensional), and if possible should be constant
        // (to allow construction of a ScalingFunction instead of a generic ProductFunction).
        FunctionImplementationPtr multiplier;
        FunctionImplementationPtr multiplicand;
        if (firstOperand->numDimensions() == 1 && secondOperand.numDimensions() == 1) {
            // Either the first or second argument could be the multiplier, so pick whichever is
            // constant (defaulting to the first argument)
            if (firstOperand->isConstant()) {
                multiplier = firstOperand;
                multiplicand = secondOperand;
            } else if (secondOperand->isConstant()) {
                multiplier = secondOperand;
                multiplicand = firstOperand;
            } else {
                multiplier = firstOperand;
                multiplicand = secondOperand;
            }
        } else if (firstOperand->numDimensions() == 1) {
            // Only the first argument is a scalar, so use it as the multiplier
            multiplier = firstOperand;
            multiplicand = secondOperand;
        } else if (secondOperand.numDimensions() == 1) {
            // Only the second argument is a scalar, so use it as the multiplier
            multiplier = secondOperand;
            multiplicand = firstOperand;
        } else {
            // Error - neither operand is a scalar
            throw PlaceholderError();
        }
        if (multiplier->isConstant()) {
            // Delegate to scaling function
            return multiplicand->scaled(multiplier->cast<ConstantFunction>()->value());
        }
        if (multiplicand->isConstant() && multiplicand->cast<ConstantFunction>()->isZero()) {
            // Doesn't matter what the multiplier is - return the (zero) multiplicand
            return multiplicand;
        }
        return new ProductFunction(multiplier, multiplicand);
    }

    FunctionImplementationPtr
    operator*(const FunctionImplementationPtr& firstOperand, const VectorXd& secondOperand) {
        return firstOperand * new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator*(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) * secondOperand;
    }

    FunctionImplementationPtr
    operator*(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand * new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator*(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) * secondOperand;
    }

    FunctionImplementationPtr
    operator/(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) const {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw PlaceholderError();
        }
        if (secondOperand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        if (secondOperand->isConstant()) {
            double divisor = secondOperand->cast<ConstantFunction>()->value();
            if (divisor == Zero()) {
                throw PlaceholderError();
            }
            return firstOperand->scaled(1 / divisor);
        }
        if (firstOperand->isConstant() && firstOperand->cast<ConstantFunction>()->isZero()) {
            // Doesn't matter what the divisor is - return the (zero) dividend
            return firstOperand;
        }
        return new QuotientFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator/(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    FunctionImplementationPtr
    operator/(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand / new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator/(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    FunctionImplementationPtr
    sqrt(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->sqrtImpl();
    }

    FunctionImplementationPtr
    sin(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->sinImpl();
    }

    FunctionImplementationPtr
    cos(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->cosImpl();
    }

    FunctionImplementationPtr
    tan(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->tanImpl();
    }

    FunctionImplementationPtr
    acos(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->acosImpl();
    }

    FunctionImplementationPtr
    asin(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->asinImpl();
    }

    FunctionImplementationPtr
    exp(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->expImpl();
    }

    FunctionImplementationPtr
    log(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw PlaceholderError();
        }
        return operand->logImpl();
    }

    FunctionImplementationPtr
    pow(const FunctionImplementationPtr& base, const FunctionImplementationPtr& exponent) {
        if (base->numParameters() != exponent->numParameters()) {
            throw PlaceholderError();
        }
        if (!(base->numDimensions() == 1 && exponent->numDimensions() == 1)) {
            throw PlaceholderError();
        }
        if (base->isConstant() && exponent->isConstant()) {
            double baseValue = base->cast<ConstantFunction>()->value();
            double exponentValue = exponent->cast<ConstantFunction>()->value();
            if (baseValue == Zero() && exponentValue < Zero()) {
                throw PlaceholderError();
            }
            return new ConstantFunction(pow(baseValue, exponentValue), base->numParameters());
        }
        return new PowerFunction(base, exponent);
    }
}
