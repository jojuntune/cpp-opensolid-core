/*************************************************************************************
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

// Public headers
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Zero.hpp>

// Internal headers
#include <OpenSolid/Core/Function/ArccosineFunction.hpp>
#include <OpenSolid/Core/Function/ArcsineFunction.hpp>
#include <OpenSolid/Core/Function/ComponentsFunction.hpp>
#include <OpenSolid/Core/Function/CompositionFunction.hpp>
#include <OpenSolid/Core/Function/ConcatenationFunction.hpp>
#include <OpenSolid/Core/Function/ConstantFunction.hpp>
#include <OpenSolid/Core/Function/CosineFunction.hpp>
#include <OpenSolid/Core/Function/CrossProductFunction.hpp>
#include <OpenSolid/Core/Function/DifferenceFunction.hpp>
#include <OpenSolid/Core/Function/DotProductFunction.hpp>
#include <OpenSolid/Core/Function/EllipticalFunction.hpp>
#include <OpenSolid/Core/Function/ExponentialFunction.hpp>
#include <OpenSolid/Core/Function/LinearFunction.hpp>
#include <OpenSolid/Core/Function/LogarithmFunction.hpp>
#include <OpenSolid/Core/Function/NegationFunction.hpp>
#include <OpenSolid/Core/Function/NormFunction.hpp>
#include <OpenSolid/Core/Function/NormalizedFunction.hpp>
#include <OpenSolid/Core/Function/ParametersFunction.hpp>
#include <OpenSolid/Core/Function/PowerFunction.hpp>
#include <OpenSolid/Core/Function/ProductFunction.hpp>
#include <OpenSolid/Core/Function/QuotientFunction.hpp>
#include <OpenSolid/Core/Function/SineFunction.hpp>
#include <OpenSolid/Core/Function/SquareRootFunction.hpp>
#include <OpenSolid/Core/Function/SquaredNormFunction.hpp>
#include <OpenSolid/Core/Function/SumFunction.hpp>
#include <OpenSolid/Core/Function/TangentFunction.hpp>

#include <algorithm>

namespace opensolid
{
    Function::Function() : _implementation(), _type(OPENSOLID_NULLPTR) {
    }
    
    Function::Function(const FunctionImplementation* implementation) :
        _implementation(implementation), _type(&typeid(implementation)) {
    }
    
    Function::Function(int value) {
        *this = Function(VectorXd::Constant(1, value));
    }

    Function::Function(double value) {
        *this = Function(VectorXd::Constant(1, value));
    }

    Function::Function(const VectorXd& vector) :
        _implementation(new ConstantFunction(vector)), _type(&typeid(ConstantFunction)) {
    }
    
    int Function::numParameters() const {
        return implementation() ? implementation()->numParameters() : 0;
    }
    
    int Function::numDimensions() const {
        return implementation() ? implementation()->numDimensions() : 0;
    }
    
    bool Function::isConstant() const {
        assert(implementation());
        assert(_type);
        return *_type == typeid(ConstantFunction);
    }

    void Function::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        implementation()->evaluate(parameterValues, results);
    }

    void Function::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        implementation()->evaluate(parameterBounds, results);
    }
    
    Function Function::derivative(int index) const {
        assert(implementation());
        Function result;
        implementation()->getDerivative(index, result);
        return result;
    }
    
    Function Function::transformed(
        const MatrixXd& transformMatrix,
        const VectorXd& transformVector
    ) const {
        assertValidTransform<Dynamic>(numDimensions(), transformMatrix, transformVector);
        assert(implementation());
        Function result;
        implementation()->getTransformed(transformMatrix, transformVector, result);
        return result;
    }
    
    Function Function::norm() const {
        assert(implementation());
        Function result;
        implementation()->getNorm(result);
        return result;
    }
    
    Function Function::normalized() const {
        assert(implementation());
        Function result;
        implementation()->getNormalized(result);
        return result;
    }
    
    Function Function::squaredNorm() const {
        assert(implementation());
        Function result;
        implementation()->getSquaredNorm(result);
        return result;
    }

    Function Function::x() const {
        assert(implementation());
        return component(0);
    }

    Function Function::y() const {
        assert(implementation());
        return component(1);
    }

    Function Function::z() const {
        assert(implementation());
        return component(2);
    }
    
    Function Function::component(int index) const {
        assert(implementation());
        Function result;
        implementation()->getComponents(index, 1, result);
        return result;
    }
    
    Function Function::components(int index, int num) const {
        assert(implementation());
        Function result;
        implementation()->getComponents(index, num, result);
        return result;
    }
    
    Function Function::concatenate(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        if (isConstant() && other.isConstant()) {
            VectorXd result(numDimensions() + other.numDimensions());
            result.head(numDimensions()) = this->as<VectorXd>();
            result.tail(other.numDimensions()) = other.as<VectorXd>();
            return result;
        } else {
            return new ConcatenationFunction(*this, other);
        }
    }
    
    Function Function::dot(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        if (numDimensions() == 1) {
            assert(other.numDimensions() == 1);
            return (*this) * other;
        } else if (isConstant() && other.isConstant()) {
            return this->as<VectorXd>().dot(other.as<VectorXd>());
        } else if (
            (isConstant() && this->as<VectorXd>().isZero()) ||
            (other.isConstant() && other.as<VectorXd>().isZero())
        ) {
            return 0.0;
        } else {
            return new DotProductFunction(*this, other);
        }
    }
    
    Function Function::cross(const Function& other) const {
        assert(implementation());
        assert(other.implementation());
        assert(numDimensions() == 3 && other.numDimensions() == 3);
        if (isConstant() && other.isConstant()) {
            return this->as<Vector3d>().cross(other.as<Vector3d>());
        }
        else if (
            (isConstant() && this->as<Vector3d>().isZero()) ||
            (other.isConstant() && other.as<Vector3d>().isZero())
        ) {
            return Vector3d::Zero();
        } else {
            return new CrossProductFunction(*this, other);
        }
    }
    
    Function Function::tangent() const {
        assert(implementation());
        assert(numParameters() == 1);
        Function result;
        implementation()->getTangent(result);
        return result;
    }
    
    Function Function::curvature() const {
        assert(implementation());
        assert(numParameters() == 1);
        Function result;
        implementation()->getCurvature(result);
        return result;
        
    }
    
    Function Function::normal() const {
        assert(implementation());
        assert(numParameters() == 1 || numParameters() == 2);
        Function result;
        implementation()->getNormal(result);
        return result;
    }
    
    Function Function::binormal() const {
        assert(implementation());
        assert(numParameters() == 1);
        Function result;
        implementation()->getBinormal(result);
        return result;
    }
     
    Function Function::operator()(const Function& inner) const {
        assert(implementation());
        assert(inner.implementation());
        if (isConstant()) {
            return *this;
        }
        assert(numParameters() == inner.numDimensions());
        if (inner.isConstant()) {
            return operator()(inner.as<VectorXd>());
        }
        Function result;
        implementation()->getComposition(inner, result);
        return result;
    }
    
    Geometry Function::operator()(const Domain& domain) const {
        assert(implementation());
        assert(isConstant() || !domain.isEmpty());
        return Geometry(*this, domain);
    }
    
    Geometry Function::operator()(const Geometry& geometry) const {
        assert(implementation());
        return Geometry(operator()(geometry.function()), geometry.domain());
    }

    void Function::debug(std::ostream& stream, int indent) const {
        assert(implementation());
        for (int i = 0; i < indent; ++i) {
            stream << "  ";
        }
        stream << "R" << numParameters() << " -> R" << numDimensions() << " | ";
        stream << implementation() << " | ";
        implementation()->debug(stream, indent);
    }
    
    Function operator-(const Function& operand) {
        if (operand.isConstant()) {
            return -operand.as<VectorXd>();
        }
        return new NegationFunction(operand);
    }

    Function operator*(const Function& function, double multiplicand) {
        return function * Function(multiplicand);
    }

    Function operator*(double multiplier, const Function& function) {
        return Function(multiplier) * function;
    }
    
    Function operator+(const Function& firstOperand, const Function& secondOperand) {
        if (firstOperand.isConstant() && secondOperand.isConstant()) {
            return firstOperand.as<VectorXd>() + secondOperand.as<VectorXd>();
        } else if (firstOperand.isConstant() && firstOperand.as<VectorXd>().isZero()) {
            return secondOperand;
        } else if (secondOperand.isConstant() && secondOperand.as<VectorXd>().isZero()) {
            return firstOperand;
        } else {
            return new SumFunction(firstOperand, secondOperand);
        }
    }
    
    Function operator-(const Function& firstOperand, const Function& secondOperand) {
        if (firstOperand.isConstant() && secondOperand.isConstant()) {
            return firstOperand.as<VectorXd>() - secondOperand.as<VectorXd>();
        } else if (firstOperand.isConstant() && firstOperand.as<VectorXd>().isZero()) {
            return -secondOperand;
        } else if (secondOperand.isConstant() && secondOperand.as<VectorXd>().isZero()) {
            return firstOperand;
        } else {
            return new DifferenceFunction(firstOperand, secondOperand);
        }
    }
    
    Function operator*(const Function& firstOperand, const Function& secondOperand) {
        Function multiplicand;
        Function multiplier;
        if (secondOperand.numDimensions() == 1) {
            multiplicand = firstOperand;
            multiplier = secondOperand;
        } else {
            multiplicand = secondOperand;
            multiplier = firstOperand;
        }
        if (multiplicand.isConstant() && multiplier.isConstant()) {
            double multiplierValue = multiplier.as<double>();
            return multiplicand.as<VectorXd>() * multiplierValue;
        } else if (multiplicand.isConstant() && multiplicand.as<VectorXd>().isZero()) {
            return multiplicand;
        } else if (multiplier.isConstant()) {
            double multiplierValue = multiplier.as<double>();
            if (multiplierValue == Zero()) {
                return VectorXd::Zero(multiplicand.numDimensions());
            } else if (multiplierValue - 1 == Zero()) {
                return multiplicand;
            } else if (multiplierValue + 1 == Zero()) {
                return -multiplicand;
            } else {
                return new ProductFunction(multiplicand, multiplier);
            }
        } else {
            return new ProductFunction(multiplicand, multiplier);
        }
    }
    
    Function operator/(const Function& firstOperand, const Function& secondOperand) {
        if (firstOperand.isConstant() && secondOperand.isConstant()) {
            double divisorValue = secondOperand.as<double>();
            return firstOperand.as<VectorXd>() / divisorValue;
        } else if (
            firstOperand.isConstant() &&
            firstOperand.as<VectorXd>().isZero()
        ) {
            return firstOperand;
        } else if (secondOperand.isConstant()) {
            double secondValue = secondOperand.as<double>();
            if (secondValue - 1 == Zero()) {
                return firstOperand;
            } else if (secondValue + 1 == Zero()) {
                return -firstOperand;
            } else {
                return new ProductFunction(firstOperand, 1 / secondValue);
            }
        } else {
            return new QuotientFunction(firstOperand, secondOperand);
        }
    }
    
    Function sin(const Function& operand) {
        if (operand.isConstant()) {
            return sin(operand.as<double>());
        } else {
            return new SineFunction(operand);
        }
    }
    
    Function cos(const Function& operand) {
        if (operand.isConstant()) {
            return cos(operand.as<double>());
        } else {
            return new CosineFunction(operand);
        }
    }
    
    Function tan(const Function& operand) {
        if (operand.isConstant()) {
            return tan(operand.as<double>());
        } else {
            return new TangentFunction(operand);
        }
    }
    
    Function sqrt(const Function& operand) {
        if (operand.isConstant()) {
            return sqrt(operand.as<double>());
        } else {
            return new SquareRootFunction(operand);
        }
    }
    
    Function asin(const Function& operand) {
        if (operand.isConstant()) {
            return asin(operand.as<double>());
        } else {
            return new ArcsineFunction(operand);
        }
    }
    
    Function acos(const Function& operand) {
        if (operand.isConstant()) {
            return acos(operand.as<double>());
        } else {
            return new ArccosineFunction(operand);
        }
    }

    Function exp(const Function& argument) {
        if (argument.isConstant()) {
            return exp(argument.as<double>());
        } else {
            return new ExponentialFunction(argument);
        }
    }

    Function log(const Function& argument) {
        if (argument.isConstant()) {
            return log(argument.as<double>());
        } else {
            return new LogarithmFunction(argument);
        }
    }

    Function pow(const Function& base, const Function& exponent) {
        if (base.isConstant() && exponent.isConstant()) {
            return pow(base.as<double>(), exponent.as<double>());
        } else {
            return new PowerFunction(base, exponent);
        }
    }
    
    std::ostream& operator<<(std::ostream& stream, const Function& function) {
        assert(function.implementation());
        function.debug(stream);
        return stream;
    }
    
    double Conversion<Function, double>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.numDimensions() == 1);
        return argument.as<VectorXd>().value();
    }
    
    Vector2d Conversion<Function, Vector2d>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.numDimensions() == 2);
        return argument.as<VectorXd>();
    }
    
    Vector3d Conversion<Function, Vector3d>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        assert(argument.numDimensions() == 3);
        return argument.as<VectorXd>();
    }
    
    const VectorXd& Conversion<Function, VectorXd>::operator()(const Function& argument) const {
        assert(argument.isConstant());
        return static_cast<const ConstantFunction*>(argument.implementation())->vector();
    }
}
