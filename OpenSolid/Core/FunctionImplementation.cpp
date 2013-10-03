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
#include <OpenSolid/Core/FunctionImplementation/CrossProductFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/DeduplicationCache.hpp>
#include <OpenSolid/Core/FunctionImplementation/DifferenceFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/DotProductFunction.hpp>
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
#include <OpenSolid/Core/FunctionImplementation/ScalarMultiplicationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/MatrixMultiplicationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/VectorAdditionFunction.hpp>

namespace opensolid
{
    FunctionImplementationPtr
    FunctionImplementation::composedImpl(const FunctionImplementationPtr& innerFunction) const {
        return new CompositionFunction(this, innerFunction);
    }
    
    FunctionImplementationPtr
    FunctionImplementation::componentsImpl(int startIndex, int numComponents) const {
        return new ComponentsFunction(this, startIndex, numComponents);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::scalarMultiplicationImpl(double scale) const {
        return new ScalarMultiplicationFunction(scale, this);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::vectorAdditionImpl(const VectorXd& vector) const {
        return new VectorAdditionFunction(this, vector);
    }
        
    FunctionImplementationPtr
    FunctionImplementation::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return new MatrixMultiplicationFunction(matrix, this);
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
        return tangentVector()->derivative()->norm() / derivative()->norm();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalVectorImpl() const {
        if (numParameters() == 1) {
            return tangentVector()->derivative()->normalized();
        } else {
            return derivative(0)->cross(derivative(1))->normalized();
        }
    }
    
    FunctionImplementationPtr
    FunctionImplementation::binormalVectorImpl() const {
        return tangentVector()->cross(normalVector());
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
            throw Error(new PlaceholderError());
        }
        return derivativeImpl(parameterIndex);
    }

    bool
    FunctionImplementation::isDuplicateOf(const FunctionImplementationPtr& other) const {
        if (this == other.get()) {
            return true;
        }
        if (typeid(*this) != typeid(*other)) {
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
            [this] (const FunctionImplementationPtr& cachedFunctionImplementation) -> bool {
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
    FunctionImplementation::composed(const FunctionImplementationPtr& innerFunction) const {
        if (innerFunction->numDimensions() != this->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (innerFunction->isConstantFunction()) {
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
        return this->composedImpl(innerFunction);
    }
     
    FunctionImplementationPtr
    FunctionImplementation::components(int startIndex, int numComponents) const {
        if (startIndex < 0 || numComponents < 1 || startIndex + numComponents > numDimensions()) {
            throw Error(new PlaceholderError());
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
        if (this->isConstantFunction() && other->isConstantFunction()) {
            VectorXd vector(this->numDimensions() + other->numDimensions());
            vector.head(this->numDimensions()) = this->cast<ConstantFunction>()->vector();
            vector.tail(other->numDimensions()) = other->cast<ConstantFunction>()->vector();
            return new ConstantFunction(vector, numParameters());
        }
        return new ConcatenationFunction(this, other);
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
            throw Error(new PlaceholderError());
        }
        return tangentVectorImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::curvature() const {
        if (numParameters() != 1) {
            throw Error(new PlaceholderError());
        }
        return curvatureImpl();
    }
    
    FunctionImplementationPtr
    FunctionImplementation::normalVector() const {
        if (!(numParameters() == 1 || (numParameters() == 2 && numDimensions() == 3))) {
            throw Error(new PlaceholderError());
        }
        return normalVectorImpl();   
    }
    
    FunctionImplementationPtr
    FunctionImplementation::binormalVector() const {
        if (!(numParameters() == 1 && numDimensions() == 3)) {
            throw Error(new PlaceholderError());
        }
        return binormalVectorImpl();
    }

    FunctionImplementationPtr
    FunctionImplementation::dot(const FunctionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (this->numParameters() != other->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (this->isConstantFunction() && other->isConstantFunction()) {
            VectorXd thisVector = this->cast<ConstantFunction>()->vector();
            VectorXd otherVector = other->cast<ConstantFunction>()->vector();
            return new ConstantFunction(thisVector.dot(otherVector), numParameters());
        }
        if (numDimensions() == 1) {
            return self() * other;
        }
        if (this->isConstantFunction() && this->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        if (other->isConstantFunction() && other->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(0.0, numParameters());
        }
        return new DotProductFunction(this, other);
    }

    FunctionImplementationPtr
    FunctionImplementation::cross(const FunctionImplementationPtr& other) const {
        if (!(this->numDimensions() == 3 && other->numDimensions() == 3)) {
            throw Error(new PlaceholderError());
        }
        if (this->numParameters() != other->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (this->isConstantFunction() && other->isConstantFunction()) {
            Vector3d thisVector = this->cast<ConstantFunction>()->vector();
            Vector3d otherVector = other->cast<ConstantFunction>()->vector();
            return new ConstantFunction(thisVector.cross(otherVector), numParameters());
        }
        if (this->isConstantFunction() && this->cast<ConstantFunction>()->isZero()) {
            return new ConstantFunction(Vector3d::Zero(), numParameters());
        }
        if (other->isConstantFunction() && other->cast<ConstantFunction>()->isZero()) {
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
            throw Error(new PlaceholderError());
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantFunction()) {
            return firstOperand + secondOperand->cast<ConstantFunction>()->vector();
        }
        if (firstOperand->isConstantFunction()) {
            return secondOperand + firstOperand->cast<ConstantFunction>()->vector();
        }
        return new SumFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator+(const FunctionImplementationPtr& argument, const VectorXd& vector) {
        if (vector.size() != argument->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (vector.isZero()) {
            return argument;
        }
        return argument->vectorAdditionImpl(vector);
    }

    FunctionImplementationPtr
    operator+(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return secondOperand + firstOperand;
    }

    FunctionImplementationPtr
    operator+(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand + VectorXd::Constant(1, secondOperand);
    }

    FunctionImplementationPtr
    operator+(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return secondOperand + VectorXd::Constant(1, firstOperand);
    }

    FunctionImplementationPtr
    operator-(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numDimensions() != secondOperand->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantFunction()) {
            VectorXd secondVector = secondOperand->cast<ConstantFunction>()->vector();
            return firstOperand + (-secondVector);
        }
        if (firstOperand->isConstantFunction()) {
            VectorXd firstVector = firstOperand->cast<ConstantFunction>()->vector();
            return (-secondOperand) + firstVector;
        }
        return new DifferenceFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator-(const FunctionImplementationPtr& firstOperand, const VectorXd& secondOperand) {
        return firstOperand + (-secondOperand);
    }

    FunctionImplementationPtr
    operator-(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return (-secondOperand) + firstOperand;
    }

    FunctionImplementationPtr
    operator-(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand + VectorXd::Constant(1, -secondOperand);
    }

    FunctionImplementationPtr
    operator-(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return (-secondOperand) + VectorXd::Constant(1, firstOperand);
    }

    FunctionImplementationPtr
    operator*(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        // Determine which operand to use as the multiplier and which to use as the multiplicand:
        // The multiplier should be a scalar (one dimensional), and if possible should be constant
        // (to allow construction of a ScalingFunction instead of a generic ProductFunction).
        FunctionImplementationPtr multiplier;
        FunctionImplementationPtr multiplicand;
        if (firstOperand->numDimensions() == 1 && secondOperand->numDimensions() == 1) {
            // Either the first or second argument could be the multiplier, so pick whichever is
            // constant (defaulting to the first argument)
            if (firstOperand->isConstantFunction()) {
                multiplier = firstOperand;
                multiplicand = secondOperand;
            } else if (secondOperand->isConstantFunction()) {
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
        } else if (secondOperand->numDimensions() == 1) {
            // Only the second argument is a scalar, so use it as the multiplier
            multiplier = secondOperand;
            multiplicand = firstOperand;
        } else {
            // Error - neither operand is a scalar
            throw Error(new PlaceholderError());
        }
        if (multiplier->isConstantFunction()) {
            // Delegate to scaling function
            return multiplier->cast<ConstantFunction>()->value() * multiplicand;
        }
        if (multiplicand->isConstantFunction()) {
            if (multiplicand->cast<ConstantFunction>()->isZero()) {
                // Doesn't matter what the multiplier is - return the (zero) multiplicand
                return multiplicand;
            }
        }
        return new ProductFunction(multiplier, multiplicand);
    }

    FunctionImplementationPtr
    operator*(const FunctionImplementationPtr& firstOperand, const VectorXd& secondOperand) {
        return firstOperand * new ConstantFunction(secondOperand, firstOperand->numParameters());
    }

    FunctionImplementationPtr
    operator*(const MatrixXd& matrix, const FunctionImplementationPtr& argument) {
        if (matrix.size() == 0) {
            throw Error(new PlaceholderError());
        }
        if (matrix.size() == 1) {
            return matrix.value() * argument;
        }
        if (matrix.cols() != argument->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (matrix.isZero()) {
            return new ConstantFunction(VectorXd::Zero(matrix.rows()), argument->numParameters());
        }
        if (matrix.rows() == matrix.cols() && matrix.isIdentity()) {
            return argument;
        }
        if (matrix.rows() == matrix.cols() && (-matrix).isIdentity()) {
            return -argument;
        }
        return argument->matrixMultiplicationImpl(matrix);
    }

    FunctionImplementationPtr
    operator*(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        return secondOperand * firstOperand;
    }

    FunctionImplementationPtr
    operator*(double scale, const FunctionImplementationPtr& argument) {
        if (scale == Zero()) {
            return new ConstantFunction(
                VectorXd::Zero(argument->numDimensions()),
                argument->numParameters()
            );
        }
        if (scale - 1 == Zero()) {
            return argument;
        }
        if (scale + 1 == Zero()) {
            return -argument;
        }
        return argument->scalarMultiplicationImpl(scale);
    }

    FunctionImplementationPtr
    operator/(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantFunction()) {
            double divisor = secondOperand->cast<ConstantFunction>()->value();
            if (divisor == Zero()) {
                throw Error(new PlaceholderError());
            }
            return (1 / divisor) * firstOperand;
        }
        if (firstOperand->isConstantFunction()) {
            if (firstOperand->cast<ConstantFunction>()->isZero()) {
                // Doesn't matter what the divisor is - return the (zero) dividend
                return firstOperand;
            }
        }
        return new QuotientFunction(firstOperand, secondOperand);
    }

    FunctionImplementationPtr
    operator/(const VectorXd& firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    FunctionImplementationPtr
    operator/(const FunctionImplementationPtr& firstOperand, double secondOperand) {
        if (secondOperand == Zero()) {
            throw Error(new PlaceholderError());
        }
        return (1 / secondOperand) * firstOperand;
    }

    FunctionImplementationPtr
    operator/(double firstOperand, const FunctionImplementationPtr& secondOperand) {
        return new ConstantFunction(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    FunctionImplementationPtr
    sqrt(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->sqrtImpl();
    }

    FunctionImplementationPtr
    sin(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->sinImpl();
    }

    FunctionImplementationPtr
    cos(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->cosImpl();
    }

    FunctionImplementationPtr
    tan(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->tanImpl();
    }

    FunctionImplementationPtr
    acos(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->acosImpl();
    }

    FunctionImplementationPtr
    asin(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->asinImpl();
    }

    FunctionImplementationPtr
    exp(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->expImpl();
    }

    FunctionImplementationPtr
    log(const FunctionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->logImpl();
    }

    FunctionImplementationPtr
    pow(double base, const FunctionImplementationPtr& exponent) {
        return pow(new ConstantFunction(base, exponent->numParameters()), exponent);
    }

    FunctionImplementationPtr
    pow(const FunctionImplementationPtr& base, double exponent) {
        return pow(base, new ConstantFunction(exponent, base->numParameters()));
    }

    FunctionImplementationPtr
    pow(const FunctionImplementationPtr& base, const FunctionImplementationPtr& exponent) {
        if (base->numParameters() != exponent->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (!(base->numDimensions() == 1 && exponent->numDimensions() == 1)) {
            throw Error(new PlaceholderError());
        }
        if (base->isConstantFunction() && exponent->isConstantFunction()) {
            double baseValue = base->cast<ConstantFunction>()->value();
            double exponentValue = exponent->cast<ConstantFunction>()->value();
            if (baseValue == Zero() && exponentValue < Zero()) {
                throw Error(new PlaceholderError());
            }
            return new ConstantFunction(pow(baseValue, exponentValue), base->numParameters());
        }
        return new PowerFunction(base, exponent);
    }
}
