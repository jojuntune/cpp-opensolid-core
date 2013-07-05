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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Function.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Function/FunctionConstructors.hpp>
#include <OpenSolid/Core/Function/FunctionReturnValue.hpp>
#include <OpenSolid/Core/Function/JacobianReturnValue.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>
#include <OpenSolid/Core/FunctionImplementation/DeduplicationCache.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>::Function() :
        _implementation(new ConstantFunction(VectorXd::Zero(iNumDimensions), iNumParameters)) {
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>::Function(
        const FunctionImplementation* implementation
    ) : _implementation(implementation) {
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>::Function(
        const FunctionImplementationPtr& implementation
    ) : _implementation(implementation) {
    }

    template <int iNumDimensions, int iNumParameters>
    inline const FunctionImplementationPtr&
    Function<iNumDimensions, iNumParameters>::implementation() const {
        return _implementation;
    }

    template <int iNumDimensions, int iNumParameters>
    bool
    Function<iNumDimensions, iNumParameters>::isConstant() const {
        return implementation()->isConstant();
    }
    
    template <int iNumDimensions, int iNumParameters>
    bool
    Function<iNumDimensions, iNumParameters>::isIdentity() const {
        static_assert(
            iNumDimensions == iNumParameters,
            "Cannot be identity: number of dimensions not equal to number of parameters"
        );
        return implementation()->isIdentity();
    }
    
    template <int iNumDimensions, int iNumParameters>
    bool
    Function<iNumDimensions, iNumParameters>::isParameter() const {
        static_assert(iNumDimensions == 1, "Cannot be parameter: number of dimensions is not 1");
        return implementation()->isParameter();
    }

    template <int iNumDimensions, int iNumParameters>
    inline FunctionReturnValue<iNumDimensions, 1, int>
    Function<iNumDimensions, iNumParameters>::operator()(int value) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return FunctionReturnValue<iNumDimensions, 1, int>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline FunctionReturnValue<iNumDimensions, 1, double>
    Function<iNumDimensions, iNumParameters>::operator()(double value) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return FunctionReturnValue<iNumDimensions, 1, double>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline FunctionReturnValue<iNumDimensions, 1, Interval>
    Function<iNumDimensions, iNumParameters>::operator()(Interval interval) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return FunctionReturnValue<iNumDimensions, 1, Interval>(implementation().get(), interval);
    }
    
    template <int iNumDimensions, int iNumParameters> template <class TMatrix>
    inline FunctionReturnValue<iNumDimensions, iNumParameters, TMatrix>
    Function<iNumDimensions, iNumParameters>::operator()(const EigenBase<TMatrix>& matrix) const {
        static_assert(
            TMatrix::RowsAtCompileTime == iNumParameters || TMatrix::RowsAtCompileTime == Dynamic,
            "Incorrect number of parameters supplied"
        );
        return FunctionReturnValue<iNumDimensions, iNumParameters, TMatrix>(
            implementation().get(),
            matrix.derived()
        );
    }

    template <int iNumDimensions, int iNumParameters>
    inline JacobianReturnValue<iNumDimensions, 1, int>
    Function<iNumDimensions, iNumParameters>::jacobian(int value) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return JacobianReturnValue<iNumDimensions, 1, int>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline JacobianReturnValue<iNumDimensions, 1, double>
    Function<iNumDimensions, iNumParameters>::jacobian(double value) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return JacobianReturnValue<iNumDimensions, 1, double>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline JacobianReturnValue<iNumDimensions, 1, Interval>
    Function<iNumDimensions, iNumParameters>::jacobian(Interval interval) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");
        return JacobianReturnValue<iNumDimensions, 1, Interval>(implementation().get(), interval);
    }

    template <int iNumDimensions, int iNumParameters> template <class TVector>
    inline JacobianReturnValue<iNumDimensions, iNumParameters, TVector>
    Function<iNumDimensions, iNumParameters>::jacobian(const EigenBase<TVector>& vector) const {
        static_assert(
            TVector::RowsAtCompileTime == iNumParameters || TVector::RowsAtCompileTime == Dynamic,
            "Incorrect number of parameters supplied"
        );
        return JacobianReturnValue<iNumDimensions, iNumParameters, TVector>(
            implementation().get(),
            vector.derived()
        );
    }

    template <int iNumDimensions, int iNumParameters> template <int iNumInnerParameters>
    Function<iNumDimensions, iNumInnerParameters>
    Function<iNumDimensions, iNumParameters>::composed(
        const Function<iNumParameters, iNumInnerParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->composed(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    Function<iNumDimensions, iNumParameters>::derivative(int parameterIndex) const {
        DeduplicationCache deduplicationCache;
        return implementation()->derivative(parameterIndex)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::norm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->norm()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    Function<iNumDimensions, iNumParameters>::normalized() const {
        DeduplicationCache deduplicationCache;
        return implementation()->normalized()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::squaredNorm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->squaredNorm()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::x() const {
        DeduplicationCache deduplicationCache;
        return implementation()->x()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::y() const {
        static_assert(iNumDimensions >= 2, "No Y component exists");
        DeduplicationCache deduplicationCache;
        return implementation()->y()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::z() const {
        static_assert(iNumDimensions >= 3, "No Z component exists");
        DeduplicationCache deduplicationCache;
        return implementation()->z()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::component(int index) const {
        DeduplicationCache deduplicationCache;
        return implementation()->component(index)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumComponents>
    Function<iNumComponents, iNumParameters>
    Function<iNumDimensions, iNumParameters>::components(int startIndex) const {
        static_assert(iNumComponents <= iNumDimensions, "Too many components requested");
        static_assert(iNumComponents > 0, "Zero or negative number of components requested");
        DeduplicationCache deduplicationCache;
        return implementation()->components(startIndex, iNumComponents)->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumOtherDimensions>
    Function<iNumDimensions + iNumOtherDimensions, iNumParameters>
    Function<iNumDimensions, iNumParameters>::concatenated(
        const Function<iNumOtherDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->concatenated(other.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<1, iNumParameters>
    Function<iNumDimensions, iNumParameters>::dot(
        const Function<iNumDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->dot(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<3, iNumParameters>
    Function<iNumDimensions, iNumParameters>::cross(
        const Function<3, iNumParameters>& other
    ) const {
        static_assert(iNumDimensions == 3, "Cross product only defined in 3D");
        DeduplicationCache deduplicationCache;
        return implementation()->cross(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, 1>
    Function<iNumDimensions, iNumParameters>::tangentVector() const {
        static_assert(iNumParameters == 1, "Tangent vector only defined for curves");
        DeduplicationCache deduplicationCache;
        return implementation()->tangentVector()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<1, 1>
    Function<iNumDimensions, iNumParameters>::curvature() const {
        static_assert(iNumParameters == 1, "Curvature only defined for curves");
        DeduplicationCache deduplicationCache;
        return implementation()->curvature()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    Function<iNumDimensions, iNumParameters>::normalVector() const {
        static_assert(
            (iNumParameters == 1) ||
            (iNumDimensions == 3 && iNumParameters == 2),
            "Invalid numbers of dimensions/parameters for definition of normal vector"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->normalVector()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<3, 1>
    Function<iNumDimensions, iNumParameters>::binormalVector() const {
        static_assert(
            iNumDimensions == 3 && iNumParameters == 1,
            "Binormal only defined for 3D curves"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->binormalVector()->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumParameters, iNumDimensions>
    operator-(const Function<iNumParameters, iNumDimensions>& function) {
        DeduplicationCache deduplicationCache;
        return (-function.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator+(const Function<1, iNumParameters>& function, double value) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() + value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator+(double value, const Function<1, iNumParameters>& function) {
        DeduplicationCache deduplicationCache;
        return (value + function.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const Function<iNumDimensions, iNumParameters>& function,
        const EigenBase<TVector>& vector
    ) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() + VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const EigenBase<TVector>& vector,
        const Function<iNumDimensions, iNumParameters>& function
    ) {
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) + function.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() + secondFunction.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator-(const Function<1, iNumParameters>& function, double value) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() - value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator-(double value, const Function<1, iNumParameters>& function) {
        DeduplicationCache deduplicationCache;
        return (value - function.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const Function<iNumDimensions, iNumParameters>& function,
        const EigenBase<TVector>& vector
    ) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() - VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const EigenBase<TVector>& vector,
        const Function<iNumDimensions, iNumParameters>& function
    ) {
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) - function.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() - secondFunction.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator*(double value, const Function<iNumDimensions, iNumParameters>& function) {
        DeduplicationCache deduplicationCache;
        return (value * function.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator*(const Function<iNumDimensions, iNumParameters>& function, double value) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() * value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TMatrix>
    Function<TMatrix::RowsAtCompileTime, iNumParameters>
    operator*(
        const EigenBase<TMatrix>& matrix,
        const Function<iNumDimensions, iNumParameters>& function
    ) {
        DeduplicationCache deduplicationCache;
        return (MatrixXd(matrix.derived()) * function.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <class TVector, int iNumParameters>
    Function<TVector::RowsAtCompileTime, iNumParameters>
    operator*(const Function<1, iNumParameters>& function, const EigenBase<TVector>& vector) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() * VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator*(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() * secondFunction.implementation())->\
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator*(
        const Function<1, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() * secondFunction.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator*(
        const Function<1, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() * secondFunction.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator/(const Function<iNumDimensions, iNumParameters>& function, double value) {
        DeduplicationCache deduplicationCache;
        return (function.implementation() / value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator/(double value, const Function<1, iNumParameters>& function) {
        DeduplicationCache deduplicationCache;
        return (value / function.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TVector, int iNumParameters>
    Function<TVector::RowsAtCompileTime, iNumParameters>
    operator/(const EigenBase<TVector>& vector, const Function<1, iNumParameters>& function) {
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) / function.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator/(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    ) {
        DeduplicationCache deduplicationCache;
        return (firstFunction.implementation() / secondFunction.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    sin(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return sin(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    cos(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return cos(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    tan(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return tan(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    sqrt(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return sqrt(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    acos(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return acos(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    asin(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return asin(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    exp(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return exp(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    log(const Function<1, iNumParameters>& argument) {
        DeduplicationCache deduplicationCache;
        return log(argument.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(const Function<1, iNumParameters>& base, double exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(double base, const Function<1, iNumParameters>& exponent) {
        DeduplicationCache deduplicationCache;
        return (base, exponent.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(const Function<1, iNumParameters>& base, const Function<1, iNumParameters>& exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    std::ostream&
    operator<<(std::ostream& stream, const Function<iNumDimensions, iNumParameters>& function) {
        function.implementation()->debug(stream, 0);
        return stream;
    }
}
