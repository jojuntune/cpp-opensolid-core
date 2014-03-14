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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/DeduplicationCache.hpp>
#include <OpenSolid/Core/ParametricExpression/Eigen.hpp>
#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

#include <type_traits>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions, int iNumParameters>
        ExpressionImplementationPtr
        zeroExpression() {
            return ExpressionImplementationPtr(
                new ConstantExpression(ColumnMatrixXd::Zero(iNumDimensions), iNumParameters)
            );
        }
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression() :
        _implementationPtr(detail::zeroExpression<iNumDimensions, iNumParameters>()) {
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression(
        const ExpressionImplementation* implementationPtr
    ) : _implementationPtr(implementationPtr) {
        if (!implementationPtr) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
        if (implementationPtr->numDimensions() != iNumDimensions) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
        if (implementationPtr->numParameters() != iNumParameters) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression(
        const ExpressionImplementationPtr& implementationPtr
    ) : _implementationPtr(implementationPtr) {
        if (!implementationPtr) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
        if (implementationPtr->numDimensions() != iNumDimensions) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
        if (implementationPtr->numParameters() != iNumParameters) {
            throw Error(new PlaceholderError());
            _implementationPtr = detail::zeroExpression<iNumDimensions, iNumParameters>();
        }
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const ExpressionImplementationPtr&
    ParametricExpression<iNumDimensions, iNumParameters>::implementation() const {
        return _implementationPtr;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(double u) const {
        static_assert(iNumParameters == 1, "Incorrect number of parameters");

        return evaluate(Matrix1x1(u));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(double u, double v) const {
        static_assert(iNumParameters == 2, "Incorrect number of parameters");

        return evaluate(Matrix2x1(u, v));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        double u,
        double v,
        double w
    ) const {
        static_assert(iNumParameters == 3, "Incorrect number of parameters");

        return evaluate(Matrix3x1(u, v, w));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(Interval u) const {
        static_assert(iNumParameters == 1, "Incorrect number of parameters");

        return evaluate(IntervalMatrix1x1(u));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(Interval u, Interval v) const {
        static_assert(iNumParameters == 2, "Incorrect number of parameters");

        return evaluate(IntervalMatrix2x1(u, v));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        Interval u,
        Interval v,
        Interval w
    ) const {
        static_assert(iNumParameters == 3, "Incorrect number of parameters");

        return evaluate(IntervalMatrix3x1(u, v, w));
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumColumns>
    inline
    const Matrix<double, iNumDimensions, iNumColumns>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const Matrix<double, iNumParameters, iNumColumns>& columnMatrix
    ) const {
        MapXcd argumentMap = detail::constMap(columnMatrix);

        Matrix<double, iNumDimensions, iNumColumns> results;
        MapXd resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumColumns>
    inline
    const Matrix<Interval, iNumDimensions, iNumColumns>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const Matrix<Interval, iNumParameters, iNumColumns>& columnMatrix
    ) const {
        MapXcI argumentMap = detail::constMap(columnMatrix);

        Matrix<Interval, iNumDimensions, iNumColumns> results;
        MapXI resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<double, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<double>& parameterValues
    ) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");

        MapXcd argumentMap = detail::constMap(parameterValues);

        std::vector<Matrix<double, iNumDimensions, 1>> results(parameterValues.size());
        MapXd resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<Interval, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Interval>& parameterValues
    ) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");

        MapXcI argumentMap = detail::constMap(parameterValues);

        std::vector<Matrix<Interval, iNumDimensions, 1>> results(parameterValues.size());
        MapXI resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<double, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Matrix<double, iNumParameters, 1>>& parameterValues
    ) const {
        MapXcd argumentMap = detail::constMap(parameterValues);

        std::vector<Matrix<double, iNumDimensions, 1>> results(parameterValues.size());
        MapXd resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<Interval, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Matrix<Interval, iNumParameters, 1>>& parameterValues
    ) const {
        MapXcI argumentMap = detail::constMap(parameterValues);

        std::vector<Matrix<Interval, iNumDimensions, 1>> results(parameterValues.size());
        MapXI resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(double u) const {
        static_assert(iNumParameters == 1, "Wrong number of parameters");

        return jacobian(Matrix1x1(u));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(double u, double v) const {
        static_assert(iNumParameters == 2, "Wrong number of parameters");

        return jacobian(Matrix2x1(u, v));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        double u,
        double v,
        double w
    ) const {
        static_assert(iNumParameters == 3, "Wrong number of parameters");

        return jacobian(Matrix3x1(u, v, w));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(Interval u) const {
        static_assert(iNumParameters == 1, "Wrong number of parameters");

        return jacobian(IntervalMatrix1x1(u));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(Interval u, Interval v) const {
        static_assert(iNumParameters == 2, "Wrong number of parameters");

        return jacobian(IntervalMatrix2x1(u, v));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        Interval u,
        Interval v,
        Interval w
    ) const {
        static_assert(iNumParameters == 3, "Wrong number of parameters");

        return jacobian(IntervalMatrix3x1(u, v, w));
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        const Matrix<double, iNumParameters, 1>& columnMatrix
    ) const {
        MapXcd argumentMap = detail::constMap(columnMatrix);

        Matrix<double, iNumDimensions, iNumParameters> results;
        MapXd resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluateJacobian(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        const Matrix<Interval, iNumParameters, 1>& columnMatrix
    ) const {
        MapXcI argumentMap = detail::constMap(columnMatrix);

        Matrix<Interval, iNumDimensions, iNumParameters> results;
        MapXI resultMap = detail::mutableMap(results);

        Evaluator evaluator;
        implementation()->evaluateJacobian(argumentMap, resultMap, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters> template <int iNumInnerParameters>
    ParametricExpression<iNumDimensions, iNumInnerParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::composed(
        const ParametricExpression<iNumParameters, iNumInnerParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->composed(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::derivative(
        std::int64_t parameterIndex
    ) const {
        if (parameterIndex < 0 || parameterIndex >= iNumParameters) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->derivative(int(parameterIndex))->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::norm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->norm()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::normalized() const {
        DeduplicationCache deduplicationCache;
        return implementation()->normalized()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::squaredNorm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->squaredNorm()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::squared() const {
        static_assert(
            iNumDimensions == 1,
            "Use squaredNorm() for vectors (squared() is only for scalars)"
        );

        return squaredNorm();
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::x() const {
        DeduplicationCache deduplicationCache;
        return implementation()->x()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::y() const {
        static_assert(
            iNumDimensions >= 2,
            "No Y component exists"
        );

        DeduplicationCache deduplicationCache;
        return implementation()->y()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::z() const {
        static_assert(
            iNumDimensions >= 3,
            "No Z component exists"
        );

        DeduplicationCache deduplicationCache;
        return implementation()->z()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::component(std::int64_t index) const {
        if (index < 0 || index >= iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->component(int(index))->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumComponents>
    ParametricExpression<iNumComponents, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::components(
        std::int64_t startIndex
    ) const {
        static_assert(
            iNumComponents <= iNumDimensions,
            "Too many components requested"
        );
        static_assert(
            iNumComponents > 0,
            "Zero or negative number of components requested"
        );

        if (startIndex < 0 || startIndex + iNumComponents > iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->components(int(startIndex), iNumComponents)->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumOtherDimensions>
    ParametricExpression<iNumDimensions + iNumOtherDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::concatenated(
        const ParametricExpression<iNumOtherDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->concatenated(other.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::dot(
        const Matrix<double, iNumDimensions, 1>& columnMatrix
    ) const {
        DeduplicationCache deduplicationCache;
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        return implementation()->dot(new ConstantExpression(columnMatrixXd, iNumParameters))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::dot(
        const ParametricExpression<iNumDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->dot(other.implementation())->deduplicated(deduplicationCache);
    }
        
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<3, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::cross(
        const Matrix<double, 3, 1>& columnMatrix
    ) const {
        static_assert(iNumDimensions == 3, "Cross product only defined in 3D");

        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return implementation()->cross(new ConstantExpression(columnMatrixXd, iNumParameters))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<3, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::cross(
        const ParametricExpression<3, iNumParameters>& other
    ) const {
        static_assert(iNumDimensions == 3, "Cross product only defined in 3D");

        DeduplicationCache deduplicationCache;
        return implementation()->cross(other.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumParameters, iNumDimensions>
    operator-(const ParametricExpression<iNumParameters, iNumDimensions>& expression) {
        DeduplicationCache deduplicationCache;
        return (-expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(const ParametricExpression<1, iNumParameters>& expression, double value) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() + value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(double value, const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return (value + expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const Matrix<double, iNumDimensions, 1>& columnMatrix
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (expression.implementation() + columnMatrixXd)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const Matrix<double, iNumDimensions, 1>& columnMatrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (columnMatrixXd + expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() + secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(const ParametricExpression<1, iNumParameters>& expression, double value) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() - value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(double value, const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return (value - expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const Matrix<double, iNumDimensions, 1>& columnMatrix
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (expression.implementation() - columnMatrixXd)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const Matrix<double, iNumDimensions, 1>& columnMatrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (columnMatrixXd - expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() - secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        double value,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (value * expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() * value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator*(
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        MatrixXd matrixXd = detail::constMap(matrix);
        DeduplicationCache deduplicationCache;
        return (matrixXd * expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters, int iNumResultDimensions>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& expression,
        const Matrix<double, iNumResultDimensions, 1>& columnMatrix
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (expression.implementation() * columnMatrixXd)->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() / value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator/(
        double value,
        const ParametricExpression<1, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (value / expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumResultDimensions, int iNumParameters>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator/(
        const Matrix<double, iNumResultDimensions, 1>& columnMatrix,
        const ParametricExpression<1, iNumParameters>& expression
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(columnMatrix);
        DeduplicationCache deduplicationCache;
        return (columnMatrixXd / expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() / secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sin(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return sin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    cos(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return cos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    tan(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return tan(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sqrt(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return sqrt(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    acos(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return acos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    asin(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return asin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    exp(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return exp(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    log(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return log(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(const ParametricExpression<1, iNumParameters>& base, double exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(double base, const ParametricExpression<1, iNumParameters>& exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base, exponent.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(
        const ParametricExpression<1, iNumParameters>& base,
        const ParametricExpression<1, iNumParameters>& exponent
    ) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    std::ostream&
    operator<<(
        std::ostream& stream,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        expression.implementation()->debug(stream, 0);
        return stream;
    }
}
