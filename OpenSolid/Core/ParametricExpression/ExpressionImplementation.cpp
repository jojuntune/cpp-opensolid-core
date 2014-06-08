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
 
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ArccosineExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ArcsineExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ComponentsExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/CompositionExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConcatenationExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/CosineExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/CrossProductExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/DeduplicationCache.hpp>
#include <OpenSolid/Core/ParametricExpression/DifferenceExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/DotProductExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ExponentialExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/LogarithmExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/NegatedExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/NormalizedExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/NormExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/PowerExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ProductExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/QuotientExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ScalingExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/SineExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/SquaredNormExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/SquareRootExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/SumExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/TangentExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/TransformationExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/TranslationExpression.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    ExpressionImplementationPtr
    ExpressionImplementation::composedImpl(
        const ExpressionImplementationPtr& innerExpression
    ) const {
        return new CompositionExpression(this, innerExpression);
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::componentsImpl(int startIndex, int numComponents) const {
        return new ComponentsExpression(this, startIndex, numComponents);
    }
        
    ExpressionImplementationPtr
    ExpressionImplementation::scalingImpl(double scale) const {
        return new ScalingExpression(scale, this);
    }
        
    ExpressionImplementationPtr
    ExpressionImplementation::translationImpl(const ColumnMatrixXd& columnMatrix) const {
        return new TranslationExpression(this, columnMatrix);
    }
        
    ExpressionImplementationPtr
    ExpressionImplementation::transformationImpl(const MatrixXd& matrix) const {
        return new TransformationExpression(matrix, this);
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::normImpl() const {
        return new NormExpression(this);
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::normalizedImpl() const {
        return new NormalizedExpression(this);
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::squaredNormImpl() const {
        return new SquaredNormExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::negatedImpl() const {
        return new NegatedExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::sqrtImpl() const {
        return new SquareRootExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::sinImpl() const {
        return new SineExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::cosImpl() const {
        return new CosineExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::tanImpl() const {
        return new TangentExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::acosImpl() const {
        return new ArccosineExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::asinImpl() const {
        return new ArcsineExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::expImpl() const {
        return new ExponentialExpression(this);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::logImpl() const {
        return new LogarithmExpression(this);
    }

    ExpressionImplementation::~ExpressionImplementation() {
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::derivative(int parameterIndex) const {
        if (parameterIndex < 0 || parameterIndex >= numParameters()) {
            throw Error(new PlaceholderError());
        }
        return derivativeImpl(parameterIndex);
    }

    bool
    ExpressionImplementation::isDuplicateOf(const ExpressionImplementationPtr& other) const {
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
    
    ExpressionImplementationPtr
    ExpressionImplementation::deduplicated(DeduplicationCache& deduplicationCache) const {
        // Try to find a function implementation in the cache that this is a duplicate of
        auto iterator = std::find_if(
            deduplicationCache.begin(),
            deduplicationCache.end(),
            [this] (const ExpressionImplementationPtr& cachedExpressionImplementation) -> bool {
                return this->isDuplicateOf(cachedExpressionImplementation);
            }
        );

        // Return the cached duplicate if one was found
        if (iterator != deduplicationCache.end()) {
            return *iterator;
        }

        // No matching function implementation was found: add a deduplicated copy of this
        // function implementation to the list, then return it.
        ExpressionImplementationPtr result = deduplicatedImpl(deduplicationCache);
        deduplicationCache.add(result);
        return result;
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::composed(const ExpressionImplementationPtr& innerExpression) const {
        if (innerExpression->numDimensions() != this->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (innerExpression->isConstantExpression()) {
            ConstMatrixViewXd argumentMap(
                innerExpression->cast<ConstantExpression>()->columnMatrix().data(),
                innerExpression->numDimensions(),
                1,
                0
            );
            
            ColumnMatrixXd result(this->numDimensions());
            MatrixViewXd resultMap(
                result.data(),
                this->numDimensions(),
                1,
                0
            );

            Evaluator evaluator;
            evaluate(argumentMap, resultMap, evaluator);
            
            return new ConstantExpression(result, innerExpression->numParameters());
        }
        return this->composedImpl(innerExpression);
    }
     
    ExpressionImplementationPtr
    ExpressionImplementation::components(int startIndex, int numComponents) const {
        if (startIndex < 0 || numComponents < 1 || startIndex + numComponents > numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (numComponents == numDimensions()) {
            return this;
        }
        return componentsImpl(startIndex, numComponents);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::component(int index) const {
        return components(index, 1);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::x() const {
        return component(0);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::y() const {
        return component(1);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::z() const {
        return component(2);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::concatenated(const ExpressionImplementationPtr& other) const {
        if (this->isConstantExpression() && other->isConstantExpression()) {
            ColumnMatrixXd columnMatrix(this->numDimensions() + other->numDimensions());
            columnMatrix.block(0, 0, this->numDimensions(), 1) =
                this->cast<ConstantExpression>()->columnMatrix();
            columnMatrix.block(this->numDimensions(), 0, other->numDimensions(), 1) =
                other->cast<ConstantExpression>()->columnMatrix();
            return new ConstantExpression(columnMatrix, numParameters());
        }
        return new ConcatenationExpression(this, other);
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::norm() const {
        return normImpl();
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::normalized() const {
        return normalizedImpl();
    }
    
    ExpressionImplementationPtr
    ExpressionImplementation::squaredNorm() const {
        return squaredNormImpl();
    }

    ExpressionImplementationPtr
    ExpressionImplementation::dot(const ExpressionImplementationPtr& other) const {
        if (this->numDimensions() != other->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (this->numParameters() != other->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (this->isConstantExpression() && other->isConstantExpression()) {
            ColumnMatrixXd thisColumnMatrix = this->cast<ConstantExpression>()->columnMatrix();
            ColumnMatrixXd otherColumnMatrix = other->cast<ConstantExpression>()->columnMatrix();
            return new ConstantExpression(
                thisColumnMatrix.cwiseProduct(otherColumnMatrix).sum(),
                numParameters()
            );
        }
        if (numDimensions() == 1) {
            return self() * other;
        }
        if (this->isConstantExpression() && this->cast<ConstantExpression>()->isZero()) {
            return new ConstantExpression(0.0, numParameters());
        }
        if (other->isConstantExpression() && other->cast<ConstantExpression>()->isZero()) {
            return new ConstantExpression(0.0, numParameters());
        }
        return new DotProductExpression(this, other);
    }

    ExpressionImplementationPtr
    ExpressionImplementation::cross(const ExpressionImplementationPtr& other) const {
        if (!(this->numDimensions() == 3 && other->numDimensions() == 3)) {
            throw Error(new PlaceholderError());
        }
        if (this->numParameters() != other->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (this->isConstantExpression() && other->isConstantExpression()) {
            Vector3d thisVector(this->cast<ConstantExpression>()->columnMatrix());
            Vector3d otherVector(other->cast<ConstantExpression>()->columnMatrix());
            return new ConstantExpression(
                thisVector.cross(otherVector).components(),
                numParameters()
            );
        }
        if (this->isConstantExpression() && this->cast<ConstantExpression>()->isZero()) {
            return new ConstantExpression(ColumnMatrixXd::zero(3), numParameters());
        }
        if (other->isConstantExpression() && other->cast<ConstantExpression>()->isZero()) {
            return new ConstantExpression(ColumnMatrixXd::zero(3), numParameters());
        }
        return new CrossProductExpression(this, other);
    }

    void
    ExpressionImplementation::debug(std::ostream& stream, int indent) const {
        for (int i = 0; i < indent; ++i) {
            stream << "  ";
        }
        stream << "R" << numParameters() << " -> R" << numDimensions() << " | ";
        stream << this << " | ";
        debugImpl(stream, indent);
    }

    ExpressionImplementationPtr
    operator-(const ExpressionImplementationPtr& operand) {
        return operand->negatedImpl();
    }

    ExpressionImplementationPtr
    operator+(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numDimensions() != secondOperand->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantExpression()) {
            return firstOperand + secondOperand->cast<ConstantExpression>()->columnMatrix();
        }
        if (firstOperand->isConstantExpression()) {
            return secondOperand + firstOperand->cast<ConstantExpression>()->columnMatrix();
        }
        return new SumExpression(firstOperand, secondOperand);
    }

    ExpressionImplementationPtr
    operator+(const ExpressionImplementationPtr& argument, const ColumnMatrixXd& columnMatrix) {
        if (columnMatrix.size() != argument->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (columnMatrix.isZero()) {
            return argument;
        }
        return argument->translationImpl(columnMatrix);
    }

    ExpressionImplementationPtr
    operator+(
        const ColumnMatrixXd& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        return secondOperand + firstOperand;
        
    }

    ExpressionImplementationPtr
    operator+(const ExpressionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand + ColumnMatrixXd::constant(1, secondOperand);
    }

    ExpressionImplementationPtr
    operator+(double firstOperand, const ExpressionImplementationPtr& secondOperand) {
        return secondOperand + ColumnMatrixXd::constant(1, firstOperand);
    }

    ExpressionImplementationPtr
    operator-(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numDimensions() != secondOperand->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantExpression()) {
            ColumnMatrixXd secondColumnMatrix =
                secondOperand->cast<ConstantExpression>()->columnMatrix();
            return firstOperand + (-secondColumnMatrix);
        } else if (firstOperand->isConstantExpression()) {
            ColumnMatrixXd firstColumnMatrix =
                firstOperand->cast<ConstantExpression>()->columnMatrix();
            return (-secondOperand) + firstColumnMatrix;
        } else {
            return new DifferenceExpression(firstOperand, secondOperand);
        }
    }

    ExpressionImplementationPtr
    operator-(
        const ExpressionImplementationPtr& firstOperand,
        const ColumnMatrixXd& secondOperand
    ) {
        return firstOperand + (-secondOperand);
    }

    ExpressionImplementationPtr
    operator-(
        const ColumnMatrixXd& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        return (-secondOperand) + firstOperand;
    }

    ExpressionImplementationPtr
    operator-(const ExpressionImplementationPtr& firstOperand, double secondOperand) {
        return firstOperand + ColumnMatrixXd::constant(1, -secondOperand);
    }

    ExpressionImplementationPtr
    operator-(double firstOperand, const ExpressionImplementationPtr& secondOperand) {
        return (-secondOperand) + ColumnMatrixXd::constant(1, firstOperand);
    }

    ExpressionImplementationPtr
    operator*(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        // Determine which operand to use as the multiplier and which to use as the multiplicand:
        // The multiplier should be a scalar (one dimensional), and if possible should be constant
        // (to allow construction of a ScalingExpression instead of a generic ProductExpression).
        ExpressionImplementationPtr multiplier;
        ExpressionImplementationPtr multiplicand;
        if (firstOperand->numDimensions() == 1 && secondOperand->numDimensions() == 1) {
            // Either the first or second argument could be the multiplier, so pick whichever is
            // constant (defaulting to the first argument)
            if (firstOperand->isConstantExpression()) {
                multiplier = firstOperand;
                multiplicand = secondOperand;
            } else if (secondOperand->isConstantExpression()) {
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
        if (multiplier->isConstantExpression()) {
            // Delegate to scaling function
            return multiplier->cast<ConstantExpression>()->value() * multiplicand;
        }
        if (multiplicand->isConstantExpression()) {
            if (multiplicand->cast<ConstantExpression>()->isZero()) {
                // Doesn't matter what the multiplier is - return the (zero) multiplicand
                return multiplicand;
            }
        }
        return new ProductExpression(multiplier, multiplicand);
    }

    ExpressionImplementationPtr
    operator*(
        const ExpressionImplementationPtr& firstOperand,
        const ColumnMatrixXd& secondOperand
    ) {
        return firstOperand * new ConstantExpression(secondOperand, firstOperand->numParameters());
    }

    ExpressionImplementationPtr
    operator*(const MatrixXd& matrix, const ExpressionImplementationPtr& argument) {
        if (matrix.size() == 0) {
            throw Error(new PlaceholderError());
        }
        if (matrix.size() == 1) {
            return matrix.value() * argument;
        }
        if (matrix.numColumns() != argument->numDimensions()) {
            throw Error(new PlaceholderError());
        }
        if (matrix.isZero()) {
            return new ConstantExpression(
                ColumnMatrixXd::zero(matrix.numRows()),
                argument->numParameters()
            );
        }
        if (matrix.numRows() == matrix.numColumns() && matrix.isIdentity()) {
            return argument;
        }
        if (matrix.numRows() == matrix.numColumns() && (-matrix).isIdentity()) {
            return -argument;
        }
        return argument->transformationImpl(matrix);
    }

    ExpressionImplementationPtr
    operator*(const ExpressionImplementationPtr& firstOperand, double secondOperand) {
        return secondOperand * firstOperand;
    }

    ExpressionImplementationPtr
    operator*(double scale, const ExpressionImplementationPtr& argument) {
        if (scale == Zero()) {
            return new ConstantExpression(
                ColumnMatrixXd::zero(argument->numDimensions()),
                argument->numParameters()
            );
        }
        if (scale - 1 == Zero()) {
            return argument;
        }
        if (scale + 1 == Zero()) {
            return -argument;
        }
        return argument->scalingImpl(scale);
    }

    ExpressionImplementationPtr
    operator/(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        if (firstOperand->numParameters() != secondOperand->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        if (secondOperand->isConstantExpression()) {
            double divisor = secondOperand->cast<ConstantExpression>()->value();
            if (divisor == Zero()) {
                throw Error(new PlaceholderError());
            }
            return (1 / divisor) * firstOperand;
        }
        if (firstOperand->isConstantExpression()) {
            if (firstOperand->cast<ConstantExpression>()->isZero()) {
                // Doesn't matter what the divisor is - return the (zero) dividend
                return firstOperand;
            }
        }
        return new QuotientExpression(firstOperand, secondOperand);
    }

    ExpressionImplementationPtr
    operator/(
        const ColumnMatrixXd& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) {
        return new ConstantExpression(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    ExpressionImplementationPtr
    operator/(const ExpressionImplementationPtr& firstOperand, double secondOperand) {
        if (secondOperand == Zero()) {
            throw Error(new PlaceholderError());
        }
        return (1 / secondOperand) * firstOperand;
    }

    ExpressionImplementationPtr
    operator/(double firstOperand, const ExpressionImplementationPtr& secondOperand) {
        return new ConstantExpression(firstOperand, secondOperand->numParameters()) / secondOperand;
    }

    ExpressionImplementationPtr
    sqrt(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->sqrtImpl();
    }

    ExpressionImplementationPtr
    sin(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->sinImpl();
    }

    ExpressionImplementationPtr
    cos(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->cosImpl();
    }

    ExpressionImplementationPtr
    tan(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->tanImpl();
    }

    ExpressionImplementationPtr
    acos(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->acosImpl();
    }

    ExpressionImplementationPtr
    asin(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->asinImpl();
    }

    ExpressionImplementationPtr
    exp(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->expImpl();
    }

    ExpressionImplementationPtr
    log(const ExpressionImplementationPtr& operand) {
        if (operand->numDimensions() != 1) {
            throw Error(new PlaceholderError());
        }
        return operand->logImpl();
    }

    ExpressionImplementationPtr
    pow(double base, const ExpressionImplementationPtr& exponent) {
        return pow(new ConstantExpression(base, exponent->numParameters()), exponent);
    }

    ExpressionImplementationPtr
    pow(const ExpressionImplementationPtr& base, double exponent) {
        return pow(base, new ConstantExpression(exponent, base->numParameters()));
    }

    ExpressionImplementationPtr
    pow(const ExpressionImplementationPtr& base, const ExpressionImplementationPtr& exponent) {
        if (base->numParameters() != exponent->numParameters()) {
            throw Error(new PlaceholderError());
        }
        if (!(base->numDimensions() == 1 && exponent->numDimensions() == 1)) {
            throw Error(new PlaceholderError());
        }
        if (base->isConstantExpression() && exponent->isConstantExpression()) {
            double baseValue = base->cast<ConstantExpression>()->value();
            double exponentValue = exponent->cast<ConstantExpression>()->value();
            if (baseValue == Zero() && exponentValue < Zero()) {
                throw Error(new PlaceholderError());
            }
            return new ConstantExpression(pow(baseValue, exponentValue), base->numParameters());
        }
        return new PowerExpression(base, exponent);
    }
}
