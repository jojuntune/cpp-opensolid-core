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

#include <OpenSolid/Core/FunctionImplementation.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LinearFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <algorithm>

namespace opensolid
{
    Function::Function() :
        _implementation() {
    }
    
    Function::Function(const FunctionImplementation* implementation) :
        _implementation(implementation) {
    }
     
    Function
    Function::compose(const Function& other) const {
        return implementation()->compose(other.implementation())->deduplicated();
    }
    
    Function
    Function::derivative(int parameterIndex) const {
        return implementation()->derivative(parameterIndex)->deduplicated();
    }
    
    Function
    Function::norm() const {
        return implementation()->norm()->deduplicated();
    }
    
    Function
    Function::normalized() const {
        return implementation()->normalized()->deduplicated();
    }
    
    Function
    Function::squaredNorm() const {
        return implementation()->squaredNorm()->deduplicated();
    }

    Function
    Function::x() const {
        return implementation()->x()->deduplicated();
    }

    Function
    Function::y() const {
        return implementation()->y()->deduplicated();
    }

    Function
    Function::z() const {
        return implementation()->z()->deduplicated();
    }
    
    Function
    Function::component(int index) const {
        return implementation()->component(index)->deduplicated();
    }
    
    Function
    Function::components(int startIndex, int numComponents) const {
        return implementation()->components(startIndex, numComponents)->deduplicated();
    }
    
    Function
    Function::concatenated(const Function& other) const {
        return implementation()->concatenated(other.implementation())->deduplicated();
    }
    
    Function
    Function::dot(const Function& other) const {
        return implementation()->dotProduct(other.implementation())->deduplicated();
    }
    
    Function
    Function::cross(const Function& other) const {
        return implementation()->crossProduct(other.implementation())->deduplicated();
    }
    
    Function
    Function::tangentVector() const {
        return implementation()->tangentVector()->deduplicated();
    }
    
    Function
    Function::curvature() const {
        return implementation()->curvature()->deduplicated();
    }
    
    Function
    Function::normalVector() const {
        return implementation()->normalVector()->deduplicated();
    }
    
    Function
    Function::binormalVector() const {
        return implementation()->binormalVector()->deduplicated();
    }

    Function
    Function::operator-() const {
        return implementation()->negated()->deduplicated();
    }
    
    Function
    Function::operator+(const Function& other) const {
        return implementation()->sum(other.implementation())->deduplicated();
    }
    
    Function
    Function::operator-(const Function& other) const {
        return implementation()->difference(other.implementation())->deduplicated();
    }
    
    Function
    Function::operator*(const Function& other) const {
        return implementation()->product(other.implementation())->deduplicated();
    }
    
    Function
    Function::operator/(const Function& other) const {
        return implementation()->quotient(other.implementation())->deduplicated();
    }

    Function
    operator+(const Function& function, double value) {
        return function.implementation()->translated(VectorXd::Constant(1, value))->deduplicated();
    }

    Function
    operator+(double value, const Function& function) {
        return function.implementation()->translated(VectorXd::Constant(1, value))->deduplicated();
    }

    Function
    operator+(const Function& function, const VectorXd& vector) {
        return function.implementation()->translated(vector)->deduplicated();
    }

    Function
    operator+(const VectorXd& vector, const Function& function) {
        return function.implementation()->translated(vector)->deduplicated();
    }

    Function
    operator-(const Function& function, double value) {
        return function.implementation()->translated(VectorXd::Constant(1, -value))->deduplicated();
    }

    Function
    operator-(double value, const Function& function) {
        return function.implementation()->negated()->translated(
            VectorXd::Constant(1, value)
        )->deduplicated();
    }

    Function
    operator-(const Function& function, const VectorXd& vector) {
        return function.implementation()->translated(-vector)->deduplicated();
    }

    Function
    operator-(const VectorXd& vector, const Function& function) {
        return function.implementation()->negated()->translated(vector)->deduplicated();
    }

    Function
    operator*(double value, const Function& function) {
        return function.implementation()->scaled(value)->deduplicated();
    }

    Function
    operator*(const Function& function, double value) {
        return function.implementation()->scaled(value)->deduplicated();
    }

    Function
    operator*(const MatrixXd& matrix, const Function& function) {
        return function.implementation()->transformed(matrix)->deduplicated();
    }

    Function
    operator*(const Function& function, const VectorXd& vector) {
        return function.implementation()->product(
            new ConstantFunction(vector, function.numParameters())
        )->deduplicated();
    }

    Function
    operator/(const Function& function, double value) {
        if (value == Zero()) {
            throw PlaceholderError();
        }
        return function.implementation()->scaled(1 / value)->deduplicated();
    }

    Function
    operator/(double value, const Function& function) {
        FunctionImplementationPtr constantFunction(
            new ConstantFunction(value, function.numParameters())
        );
        return constantFunction->quotient(function.implementation())->deduplicated();
    }

    Function
    operator/(const VectorXd& vector, const Function& function) {
        FunctionImplementationPtr constantFunction(
            new ConstantFunction(vector, function.numParameters())
        );
        return constantFunction->quotient(function.implementation())->deduplicated();
    }
    
    Function
    sin(const Function& function) {
        return function.implementation()->sin()->deduplicated();
    }
    
    Function
    cos(const Function& function) {
        return function.implementation()->cos()->deduplicated();
    }
    
    Function
    tan(const Function& function) {
        return function.implementation()->tan()->deduplicated();
    }
    
    Function
    sqrt(const Function& function) {
        return function.implementation()->sqrt()->deduplicated();
    }
    
    Function
    asin(const Function& function) {
        return function.implementation()->asin()->deduplicated();
    }
    
    Function
    acos(const Function& function) {
        return function.implementation()->acos()->deduplicated();
    }

    Function
    exp(const Function& function) {
        return function.implementation()->exp()->deduplicated();
    }

    Function
    log(const Function& function) {
        return function.implementation()->log()->deduplicated();
    }

    Function
    pow(const Function& baseFunction, const Function& exponentFunction) {
        return baseFunction.implementation()->pow(
            exponentFunction.implementation()
        )->deduplicated();
    }
    
    std::ostream&
    operator<<(std::ostream& stream, const Function& function) {
        function.implementation()->debug(stream, 0);
        return stream;
    }
}
