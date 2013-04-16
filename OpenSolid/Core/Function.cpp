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

#include <OpenSolid/Core/Function.hpp>

#include <OpenSolid/Core/Zero.hpp>

#include <OpenSolid/Core/FunctionImplementation/ArccosineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ArcsineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ComponentsFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CompositionFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConcatenationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CosineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CrossProductFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/DifferenceFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/DotProductFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ExponentialFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LinearFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LogarithmFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormalizedFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/PowerFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ProductFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/QuotientFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SineFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SquareRootFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SquaredNormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SumFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TangentFunction.hpp>

#include <algorithm>

namespace opensolid
{
    Function::Function() :
        _implementation() {
    }
    
    Function::Function(const FunctionImplementation* implementation) :
        _implementation(implementation) {
    }
    
    int
    Function::numDimensions() const {
        return isValid() ? implementation()->numDimensions() : 0;
    }
    
    int
    Function::numParameters() const {
        return isValid() ? implementation()->numParameters() : 0;
    }
    
    const ConstantFunction*
    Function::asConstant() const {
        return isValid() ? implementation()->asConstant() : 0;
    }
    
    const IdentityFunction*
    Function::asIdentity() const {
        return isValid() ? implementation()->asIdentity() : 0;
    }
    
    const ParameterFunction*
    Function::asParameter() const {
        return isValid() ? implementation()->asParameter() : 0;
    }

    bool
    Function::isDuplicate(const Function& other) const {
        if (!this->isValid() || !other.isValid()) {
            // Two functions are not duplicates if either one is null
            return false;
        }
        if (this->implementation() == other.implementation()) {
            // Two functions are considered duplicates if they share the same implementation
            return true;
        }
        if (this->numDimensions() != other.numDimensions()) {
            // Two functions cannot be duplicates if they have different numbers of dimensions
            return false;
        }
        if (this->numParameters() != other.numParameters()) {
            // Two functions cannot be duplicates if they have different numbers of parameters
            return false;
        }
        return implementation()->isDuplicate(other);
    }

    Function
    Function::deduplicated() const {
        std::vector<Function> temp;
        return deduplicated(temp);
    }

    Function
    Function::deduplicated(std::vector<Function>& others) const {
        if (!isValid()) {
            assert(false);
            return *this;
        }
        // Try to find a function in the given list that is a duplicate of this function
        auto iterator = std::find_if(
            others.begin(),
            others.end(),
            [this] (const Function& other) -> bool {
                return this->isDuplicate(other);
            }
        );
        if (iterator < others.end()) {
            // A matching function was found: return it
            return *iterator;
        } else {
            // No matching function was found: add a deduplicated copy of this function to the list,
            // then return it
            Function result = implementation()->deduplicated(others);
            others.push_back(result);
            return result;
        }
    }
     
    Function
    Function::compose(const Function& other) const {
        if (!this->isValid() || !other.isValid()) {
            assert(false);
            return Function();
        }
        if (this->numParameters() != other.numDimensions()) {
            assert(false);
            return Function();
        }
        if (this->asConstant()) {
            return *this;
        } else if (other.asConstant()) {
            return Function::Constant(operator()(other.asConstant()->vector()), numParameters());
        } else {
            return this->implementation()->compose(other).deduplicated();
        }
    }
    
    Function
    Function::derivative(int parameterIndex) const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->derivative(parameterIndex).deduplicated();
    }
    
    Function
    Function::norm() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->norm().deduplicated();
    }
    
    Function
    Function::normalized() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->normalized().deduplicated();
    }
    
    Function
    Function::squaredNorm() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->squaredNorm().deduplicated();
    }

    Function
    Function::x() const {
        return component(0);
    }

    Function
    Function::y() const {
        return component(1);
    }

    Function
    Function::z() const {
        return component(2);
    }
    
    Function
    Function::component(int index) const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        if (numDimensions() == 1) {
            assert(index == 0);
            return *this;
        }
        return implementation()->components(index, 1).deduplicated();
    }
    
    Function
    Function::components(int startIndex, int numComponents) const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        if (startIndex == 0 && numComponents == numDimensions()) {
            return *this;
        }
        return implementation()->components(startIndex, numComponents).deduplicated();
    }

    namespace
    {
        inline bool
        validBinaryOperation(
            const Function& firstFunction,
            const Function& secondFunction,
            bool requireSameNumDimensions
        ) {
            if (!firstFunction.isValid()) {
                return false;
            }
            if (!secondFunction.isValid()) {
                return false;
            }
            if (firstFunction.numParameters() != secondFunction.numParameters()) {
                return false;
            }
            if (!requireSameNumDimensions) {
                return true;
            }
            if (firstFunction.numDimensions() != secondFunction.numDimensions()) {
                return false;
            }
            return true;
        }
    }
    
    Function
    Function::concatenate(const Function& other) const {
        if (!validBinaryOperation(*this, other, false)) {
            assert(false);
            return Function();
        }
        if (this->asConstant() && other.asConstant()) {
            VectorXd vector(this->numDimensions() + other.numDimensions());
            vector.head(this->numDimensions()) = this->asConstant()->vector();
            vector.tail(other.numDimensions()) = other.asConstant()->vector();
            return Function::Constant(vector, numParameters());
        } else {
            return Function(new ConcatenationFunction(*this, other)).deduplicated();
        }
    }
    
    Function
    Function::dot(const Function& other) const {
        if (!validBinaryOperation(*this, other, true)) {
            assert(false);
            return Function();
        }
        if (this->asConstant() && other.asConstant()) {
            return Function::Constant(
                this->asConstant()->vector().dot(other.asConstant()->vector()),
                numParameters()
            );
        } else if (numDimensions() == 1) {
            return (*this) * other;
        } else if (this->asConstant() && this->asConstant()->vector().isZero()) {
            return Function::Constant(0.0, numParameters());
        } else if (other.asConstant() && other.asConstant()->vector().isZero()) {
            return Function::Constant(0.0, numParameters());
        } else {
            return Function(new DotProductFunction(*this, other)).deduplicated();
        }
    }
    
    Function
    Function::cross(const Function& other) const {
        if (!validBinaryOperation(*this, other, true) || numDimensions() != 3) {
            assert(false);
            return Function();
        }
        if (this->asConstant() && other.asConstant()) {
            Vector3d value = this->asConstant()->vector();
            Vector3d otherValue = other.asConstant()->vector();
            return Function::Constant(value.cross(otherValue), numParameters());
        } else if (this->asConstant() && this->asConstant()->vector().isZero()) {
            return Function::Constant(Vector3d::Zero(), numParameters());
        } else if (other.asConstant() && other.asConstant()->vector().isZero()) {
            return Function::Constant(Vector3d::Zero(), numParameters());
        } else {
            return Function(new CrossProductFunction(*this, other)).deduplicated();
        }
    }
    
    Function
    Function::tangentVector() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->tangentVector().deduplicated();
    }
    
    Function
    Function::curvature() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->curvature().deduplicated();
    }
    
    Function
    Function::normalVector() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->normalVector().deduplicated();
    }
    
    Function
    Function::binormalVector() const {
        if (!isValid()) {
            assert(false);
            return Function();
        }
        return implementation()->binormalVector().deduplicated();
    }
    
    Function
    Function::operator+(const Function& other) const {
        if (!validBinaryOperation(*this, other, true)) {
            assert(false);
            return Function();
        }
        if (other.asConstant()) {
            // Delegate to translation function
            return *this + other.asConstant()->vector();
        } else if (this->asConstant()) {
            // Delegate to translation function
            return this->asConstant()->vector() + other;
        } else {
            return Function(new SumFunction(*this, other)).deduplicated();
        }
    }
    
    Function
    Function::operator-(const Function& other) const {
        if (!validBinaryOperation(*this, other, true)) {
            assert(false);
            return Function();
        }
        if (other.asConstant()) {
            // Delegate to translation function
            return *this - other.asConstant()->vector();
        } else if (this->asConstant()) {
            // Delegate to translation function
            return this->asConstant()->vector() - other;
        } else {
            return Function(new DifferenceFunction(*this, other)).deduplicated();
        }
    }
    
    Function
    Function::operator*(const Function& other) const {
        if (!validBinaryOperation(*this, other, false)) {
            assert(false);
            return Function();
        }
        // Determine which operand to use as the multiplier and which to use as the multiplicand:
        // The multiplier should be a scalar (one dimensional), and if possible should be constant
        // (to allow construction of a ScalingFunction instead of a generic ProductFunction).
        Function multiplier;
        Function multiplicand;
        if (this->numDimensions() == 1 && other.numDimensions() == 1) {
            // Either this or the other could be the multiplier, so pick whichever is constant
            // (defaulting to this)
            if (this->asConstant()) {
                multiplier = *this;
                multiplicand = other;
            } else if (other.asConstant()) {
                multiplier = other;
                multiplicand = *this;
            } else {
                multiplier = *this;
                multiplicand = other;
            }
        } else if (this->numDimensions() == 1) {
            // Only this is a scalar, so use it as the multiplier
            multiplier = *this;
            multiplicand = other;
        } else if (other.numDimensions() == 1) {
            // Only the other is a scalar, so use it as the multiplier
            multiplier = other;
            multiplicand = *this;
        } else {
            // Error - neither operand is a scalar
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = multiplier.asConstant()) {
            // Delegate to scaling function
            return constant->vector().value() * multiplicand;
        } else if (multiplicand.asConstant() && multiplicand.asConstant()->vector().isZero()) {
            // Doesn't matter what the multiplier is - return the (zero) multiplicand
            return multiplicand;
        } else {
            return Function(new ProductFunction(multiplier, multiplicand)).deduplicated();
        }
    }
    
    Function
    Function::operator/(const Function& other) const {
        if (!validBinaryOperation(*this, other, false) || other.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = other.asConstant()) {
            // Delegate to scaling function
            return *this / constant->vector().value();
        } else if (this->asConstant() && this->asConstant()->vector().isZero()) {
            // Doesn't matter what the divisor is - return this (zero) dividend
            return *this;
        } else {
            return Function(new QuotientFunction(*this, other)).deduplicated();
        }
    }

    void
    Function::debug(std::ostream& stream, int indent) const {
        if (!implementation()) {
            assert(false);
            return;
        }
        for (int i = 0; i < indent; ++i) {
            stream << "  ";
        }
        stream << "R" << numParameters() << " -> R" << numDimensions() << " | ";
        stream << implementation() << " | ";
        implementation()->debug(stream, indent);
    }

    Function
    operator-(const Function& function) {
        return -1.0 * function;
    }

    Function
    operator+(const Function& function, double value) {
        return function + VectorXd::Constant(1, value);
    }

    Function
    operator+(double value, const Function& function) {
        return function + value;
    }

    Function
    operator+(const Function& function, const VectorXd& vector) {
        if (!function.isValid()) {
            assert(false);
            return Function();
        }
        if (vector.size() != function.numDimensions()) {
            assert(false);
            return Function();
        }
        if (vector.isZero()) {
            return function;
        } else {
            return function.implementation()->translated(vector).deduplicated();
        }
    }

    Function
    operator+(const VectorXd& vector, const Function& function) {
        return function + vector;
    }

    Function
    operator-(const Function& function, double value) {
        return function + (-value);
    }

    Function
    operator-(double value, const Function& function) {
        return -function + value;
    }

    Function
    operator-(const Function& function, const VectorXd& vector) {
        return function + (-vector);
    }

    Function
    operator-(const VectorXd& vector, const Function& function) {
        return -function + vector;
    }

    Function
    operator*(double value, const Function& function) {
        if (!function.isValid()) {
            assert(false);
            return Function();
        }
        if (value == opensolid::Zero()) {
            return Function::Zero(function.numDimensions(), function.numParameters());
        } else if (value - 1 == opensolid::Zero()) {
            return function;
        } else {
            return function.implementation()->scaled(value).deduplicated();
        }
    }

    Function
    operator*(const Function& function, double value) {
        return value * function;
    }

    Function
    operator*(const MatrixXd& matrix, const Function& function) {
        if (!function.isValid()) {
            assert(false);
            return Function();
        }
        if (matrix.cols() != function.numDimensions()) {
            assert(false);
            return Function();
        }
        if (matrix.isZero()) {
            return Function::Zero(matrix.rows(), function.numParameters());
        } else if (matrix.rows() == matrix.cols() && matrix.isIdentity()) {
            return function;
        } else {
            return function.implementation()->transformed(matrix).deduplicated();
        }
    }

    Function
    operator*(const Function& function, const VectorXd& vector) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        return function * Function::Constant(vector, function.numParameters());
    }

    Function
    operator/(const Function& function, double value) {
        if (value == Zero()) {
            assert(false);
            return Function();
        }
        return (1.0 / value) * function;
    }

    Function
    operator/(double value, const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        return Function::Constant(value, function.numParameters()) / function;
    }

    Function
    operator/(const VectorXd& vector, const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        return Function::Constant(vector, function.numParameters()) / function;
    }
    
    Function
    sin(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            return Function::Constant(sin(value), function.numParameters());
        } else {
            return Function(new SineFunction(function)).deduplicated();
        }
    }
    
    Function
    cos(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            return Function::Constant(cos(value), function.numParameters());
        } else {
            return Function(new CosineFunction(function)).deduplicated();
        }
    }
    
    Function
    tan(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            if (std::fmod(value - pi() / 2, pi()) == opensolid::Zero()) {
                assert(false);
                return Function();
            }
            return Function::Constant(tan(value), function.numParameters());
        } else {
            return Function(new TangentFunction(function)).deduplicated();
        }
    }
    
    Function
    sqrt(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            if (value < opensolid::Zero()) {
                assert(false);
                return Function();
            }
            value = max(value, 0.0);
            return Function::Constant(sqrt(value), function.numParameters());
        } else {
            return Function(new SquareRootFunction(function)).deduplicated();
        }
    }
    
    Function
    asin(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            if (!Interval(-1.0, 1.0).contains(value)) {
                assert(false);
                return Function();
            }
            value = Interval(-1.0, 1.0).clamp(value);
            return Function::Constant(asin(value), function.numParameters());
        } else {
            return Function(new ArcsineFunction(function)).deduplicated();
        }
    }
    
    Function
    acos(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            if (!Interval(-1.0, 1.0).contains(value)) {
                assert(false);
                return Function();
            }
            value = Interval(-1.0, 1.0).clamp(value);
            return Function::Constant(acos(value), function.numParameters());
        } else {
            return Function(new ArccosineFunction(function)).deduplicated();
        }
    }

    Function
    exp(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            return Function::Constant(exp(value), function.numParameters());
        } else {
            return Function(new ExponentialFunction(function)).deduplicated();
        }
    }

    Function
    log(const Function& function) {
        if (!function.isValid() || function.numDimensions() != 1) {
            assert(false);
            return Function();
        }
        if (const ConstantFunction* constant = function.asConstant()) {
            double value = constant->vector().value();
            if (value <= opensolid::Zero()) {
                assert(false);
                return Function();
            }
            return Function::Constant(log(value), function.numParameters());
        } else {
            return Function(new LogarithmFunction(function)).deduplicated();
        }
    }

    Function
    pow(const Function& baseFunction, const Function& exponentFunction) {
        assert(baseFunction.numParameters() == exponentFunction.numParameters());
        const ConstantFunction* constantBase = baseFunction.asConstant();
        const ConstantFunction* constantExponent = exponentFunction.asConstant();
        if (constantBase && constantExponent) {
            double baseValue = constantBase->vector().value();
            double exponentValue = constantExponent->vector().value();
            if (baseValue == opensolid::Zero() && exponentValue < opensolid::Zero()) {
                assert(false);
                return Function();
            }
            return Function::Constant(pow(baseValue, exponentValue), baseFunction.numParameters());
        } else {
            return Function(new PowerFunction(baseFunction, exponentFunction)).deduplicated();
        }
    }
    
    std::ostream&
    operator<<(std::ostream& stream, const Function& function) {
        function.debug(stream);
        return stream;
    }
}
