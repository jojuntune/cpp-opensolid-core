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
                new ConstantExpression(ColMatrixXx1::Zero(iNumDimensions), iNumParameters)
            );
        }

        inline
        ConstMatrixViewXxX
        constView(const double& value) {
            return ConstMatrixViewXxX(&value, 1, 1, 1);
        }

        inline
        ConstIntervalMatrixViewXxX
        constView(const Interval& value) {
            return ConstIntervalMatrixViewXxX(&value, 1, 1, 1);
        }

        template <int iNumRows, int iNumColumns>
        inline
        ConstMatrixViewXxX
        constView(const Matrix<double, iNumRows, iNumColumns>& matrix) {
            return ConstMatrixViewXxX(matrix.data(), iNumRows, iNumColumns, iNumRows);
        }

        template <int iNumRows, int iNumColumns>
        inline
        ConstIntervalMatrixViewXxX
        constView(const Matrix<Interval, iNumRows, iNumColumns>& matrix) {
            return ConstIntervalMatrixViewXxX(matrix.data(), iNumRows, iNumColumns, iNumRows);
        }

        inline
        ConstMatrixViewXxX
        constView(const std::vector<double>& values) {
            return ConstMatrixViewXxX(&values.front(), 1, int(values.size()), 1);
        }

        inline
        ConstIntervalMatrixViewXxX
        constView(const std::vector<Interval>& values) {
            return ConstIntervalMatrixViewXxX(&values.front(), 1, int(values.size()), 1);
        }

        template <int iNumRows>
        inline
        ConstMatrixViewXxX
        constView(const std::vector<Matrix<double, iNumRows, 1>>& matrices) {
            return ConstMatrixViewXxX(
                matrices.front().data(),
                iNumRows,
                int(matrices.size()),
                iNumRows
            );
        }

        template <int iNumRows>
        inline
        ConstIntervalMatrixViewXxX
        constView(const std::vector<Matrix<Interval, iNumRows, 1>>& matrices) {
            return ConstIntervalMatrixViewXxX(
                matrices.front().data(),
                iNumRows,
                int(matrices.size()),
                iNumRows
            );
        }

        template <int iNumRows, int iNumColumns>
        inline
        MatrixViewXxX
        mutableView(Matrix<double, iNumRows, iNumColumns>& matrix) {
            return MatrixViewXxX(matrix.data(), iNumRows, iNumColumns, iNumRows);
        }

        template <int iNumRows, int iNumColumns>
        inline
        IntervalMatrixViewXxX
        mutableView(Matrix<Interval, iNumRows, iNumColumns>& matrix) {
            return IntervalMatrixViewXxX(matrix.data(), iNumRows, iNumColumns, iNumRows);
        }

        inline
        MatrixViewXxX
        mutableView(std::vector<double>& values) {
            return MatrixViewXxX(&values.front(), 1, int(values.size()), 1);
        }

        inline
        IntervalMatrixViewXxX
        mutableView(std::vector<Interval>& values) {
            return IntervalMatrixViewXxX(&values.front(), 1, int(values.size()), 1);
        }

        template <int iNumRows>
        inline
        MatrixViewXxX
        mutableView(std::vector<Matrix<double, iNumRows, 1>>& matrices) {
            return MatrixViewXxX(matrices.front().data(), iNumRows, int(matrices.size()), iNumRows);
        }

        template <int iNumRows>
        inline
        IntervalMatrixViewXxX
        mutableView(std::vector<Matrix<Interval, iNumRows, 1>>& matrices) {
            return IntervalMatrixViewXxX(
                matrices.front().data(),
                iNumRows,
                int(matrices.size()),
                iNumRows
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

        Matrix1x1 parameterValue;
        parameterValue.value() = u;

        return evaluate(parameterValue);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(double u, double v) const {
        static_assert(iNumParameters == 2, "Incorrect number of parameters");

        ColMatrix2x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;

        return evaluate(parameterValues);
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

        ColMatrix3x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;
        parameterValues(2) = w;

        return evaluate(parameterValues);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(Interval u) const {
        static_assert(iNumParameters == 1, "Incorrect number of parameters");

        IntervalMatrix1x1 parameterValue;
        parameterValue.value() = u;

        return evaluate(parameterValue);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(Interval u, Interval v) const {
        static_assert(iNumParameters == 2, "Incorrect number of parameters");

        IntervalColMatrix2x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;

        return evaluate(parameterValues);
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

        IntervalColMatrix3x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;
        parameterValues(2) = w;

        return evaluate(parameterValues);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumColumns>
    inline
    const Matrix<double, iNumDimensions, iNumColumns>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const Matrix<double, iNumParameters, iNumColumns>& colMatrix
    ) const {
        ConstMatrixViewXxX argumentView = detail::constView(colMatrix);

        Matrix<double, iNumDimensions, iNumColumns> results;
        MatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumColumns>
    inline
    const Matrix<Interval, iNumDimensions, iNumColumns>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const Matrix<Interval, iNumParameters, iNumColumns>& colMatrix
    ) const {
        ConstIntervalMatrixViewXxX argumentView = detail::constView(colMatrix);

        Matrix<Interval, iNumDimensions, iNumColumns> results;
        IntervalMatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<double, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<double>& parameterValues
    ) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");

        ConstMatrixViewXxX argumentView = detail::constView(parameterValues);

        std::vector<Matrix<double, iNumDimensions, 1>> results(parameterValues.size());
        MatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<Interval, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Interval>& parameterValues
    ) const {
        static_assert(iNumParameters == 1, "Multiple parameters required");

        ConstIntervalMatrixViewXxX argumentView = detail::constView(parameterValues);

        std::vector<Matrix<Interval, iNumDimensions, 1>> results(parameterValues.size());
        IntervalMatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<double, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Matrix<double, iNumParameters, 1>>& parameterValues
    ) const {
        ConstMatrixViewXxX argumentView = detail::constView(parameterValues);

        std::vector<Matrix<double, iNumDimensions, 1>> results(parameterValues.size());
        MatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    std::vector<Matrix<Interval, iNumDimensions, 1>>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const std::vector<Matrix<Interval, iNumParameters, 1>>& parameterValues
    ) const {
        ConstIntervalMatrixViewXxX argumentView = detail::constView(parameterValues);

        std::vector<Matrix<Interval, iNumDimensions, 1>> results(parameterValues.size());
        IntervalMatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluate(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(double u) const {
        static_assert(iNumParameters == 1, "Wrong number of parameters");

        Matrix1x1 parameterValue;
        parameterValue.value() = u;

        return jacobian(parameterValue);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(double u, double v) const {
        static_assert(iNumParameters == 2, "Wrong number of parameters");

        ColMatrix2x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;

        return jacobian(parameterValues);
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

        ColMatrix3x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;
        parameterValues(2) = w;

        return jacobian(parameterValues);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(Interval u) const {
        static_assert(iNumParameters == 1, "Wrong number of parameters");

        IntervalMatrix1x1 parameterValue;
        parameterValue.value() = u;

        return jacobian(parameterValue);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(Interval u, Interval v) const {
        static_assert(iNumParameters == 2, "Wrong number of parameters");

        IntervalColMatrix2x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;

        return jacobian(parameterValues);
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

        IntervalColMatrix3x1 parameterValues;
        parameterValues(0) = u;
        parameterValues(1) = v;
        parameterValues(2) = w;

        return jacobian(parameterValues);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<double, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        const Matrix<double, iNumParameters, 1>& colMatrix
    ) const {
        ConstMatrixViewXxX argumentView = detail::constView(colMatrix);

        Matrix<double, iNumDimensions, iNumParameters> results;
        MatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluateJacobian(argumentView, resultView, evaluator);

        return results;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const Matrix<Interval, iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        const Matrix<Interval, iNumParameters, 1>& colMatrix
    ) const {
        ConstIntervalMatrixViewXxX argumentView = detail::constView(colMatrix);

        Matrix<Interval, iNumDimensions, iNumParameters> results;
        IntervalMatrixViewXxX resultView = detail::mutableView(results);

        Evaluator evaluator;
        implementation()->evaluateJacobian(argumentView, resultView, evaluator);

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
    ParametricExpression<iNumDimensions, iNumParameters>::derivative(int parameterIndex) const {
        if (parameterIndex < 0 || parameterIndex >= iNumParameters) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->derivative(parameterIndex)->deduplicated(deduplicationCache);
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
    ParametricExpression<iNumDimensions, iNumParameters>::component(int index) const {
        if (index < 0 || index >= iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->component(index)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumComponents>
    ParametricExpression<iNumComponents, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::components(int startIndex) const {
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
        return implementation()->components(startIndex, iNumComponents)->
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
        const Matrix<double, iNumDimensions, 1>& colMatrix
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->dot(new ConstantExpression(colMatrix, iNumParameters))->
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
        const Matrix<double, 3, 1>& colMatrix
    ) const {
        static_assert(iNumDimensions == 3, "Cross product only defined in 3D");

        DeduplicationCache deduplicationCache;
        return implementation()->cross(new ConstantExpression(colMatrix, iNumParameters))->
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
        const Matrix<double, iNumDimensions, 1>& colMatrix
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() + colMatrix)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const Matrix<double, iNumDimensions, 1>& colMatrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (colMatrix + expression.implementation())->deduplicated(deduplicationCache);
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
        const Matrix<double, iNumDimensions, 1>& colMatrix
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() - colMatrix)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const Matrix<double, iNumDimensions, 1>& colMatrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (colMatrix - expression.implementation())->deduplicated(deduplicationCache);
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
        DeduplicationCache deduplicationCache;
        return (matrix * expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters, int iNumResultDimensions>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& expression,
        const Matrix<double, iNumResultDimensions, 1>& colMatrix
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() * colMatrix)->deduplicated(deduplicationCache);
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
        const Matrix<double, iNumResultDimensions, 1>& colMatrix,
        const ParametricExpression<1, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (colMatrix / expression.implementation())->deduplicated(deduplicationCache);
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
