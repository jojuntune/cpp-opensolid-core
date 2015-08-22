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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricExpression/CompiledExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/DeduplicationCache.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ParametricExpression/TransformableExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Vector.hpp>

#include <type_traits>

namespace opensolid
{
    namespace detail
    {
        template <class TValue, class TParameter>
        ExpressionImplementationPtr
        zeroExpression() {
            return ExpressionImplementationPtr(
                new ConstantExpression(
                    ColumnMatrixXd::zero(NumDimensions<TValue>::Value),
                    NumDimensions<TParameter>::Value
                )
            );
        }

        inline
        ConstMatrixViewXd
        constView(const double& value) {
            return ConstMatrixViewXd(&value, 1, 1, sizeof(double));
        }

        inline
        ConstIntervalMatrixViewXd
        constView(const Interval& value) {
            return ConstIntervalMatrixViewXd(&value, 1, 1, sizeof(Interval));
        }

        template <int iNumDimensions>
        inline
        ConstMatrixViewXd
        constView(const Vector<double, iNumDimensions>& vector) {
            return vector.components().view();
        }

        template <int iNumDimensions>
        inline
        ConstIntervalMatrixViewXd
        constView(const Vector<Interval, iNumDimensions>& intervalVector) {
            return intervalVector.components().view();
        }

        template <int iNumDimensions>
        inline
        ConstMatrixViewXd
        constView(const Point<iNumDimensions>& point) {
            return point.components().view();
        }

        template <int iNumDimensions>
        inline
        ConstIntervalMatrixViewXd
        constView(const Box<iNumDimensions>& box) {
            return box.components().view();
        }

        inline
        ConstMatrixViewXd
        constView(const std::vector<double>& values) {
            return ConstMatrixViewXd(
                values.data(),
                1,
                int(values.size()),
                sizeof(double)
            );
        }

        inline
        ConstIntervalMatrixViewXd
        constView(const std::vector<Interval>& values) {
            return ConstIntervalMatrixViewXd(
                values.data(),
                1,
                int(values.size()),
                sizeof(Interval)
            );
        }

        template <int iNumDimensions>
        inline
        ConstMatrixViewXd
        constView(const std::vector<Vector<double, iNumDimensions>>& vectors) {
            return ConstMatrixViewXd(
                vectors.front().data(),
                iNumDimensions,
                int(vectors.size()),
                sizeof(Vector<double, iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        ConstIntervalMatrixViewXd
        constView(const std::vector<Vector<Interval, iNumDimensions>>& intervalVectors) {
            return ConstIntervalMatrixViewXd(
                intervalVectors.front().data(),
                iNumDimensions,
                int(intervalVectors.size()),
                sizeof(Vector<Interval, iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        ConstMatrixViewXd
        constView(const std::vector<Point<iNumDimensions>>& points) {
            return ConstMatrixViewXd(
                points.front().data(),
                iNumDimensions,
                int(points.size()),
                sizeof(Point<iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        ConstIntervalMatrixViewXd
        constView(const std::vector<Box<iNumDimensions>>& boxes) {
            return ConstIntervalMatrixViewXd(
                boxes.front().data(),
                iNumDimensions,
                int(boxes.size()),
                sizeof(Box<iNumDimensions>)
            );
        }

        inline
        MatrixViewXd
        mutableView(double& value) {
            return MatrixViewXd(&value, 1, 1, sizeof(double));
        }

        inline
        IntervalMatrixViewXd
        mutableView(Interval& value) {
            return IntervalMatrixViewXd(&value, 1, 1, sizeof(Interval));
        }

        template <int iNumDimensions>
        inline
        MatrixViewXd
        mutableView(Vector<double, iNumDimensions>& vector) {
            return vector.components().view();
        }

        template <int iNumDimensions>
        inline
        IntervalMatrixViewXd
        mutableView(Vector<Interval, iNumDimensions>& intervalVector) {
            return intervalVector.components().view();
        }

        template <int iNumDimensions>
        inline
        MatrixViewXd
        mutableView(Point<iNumDimensions>& point) {
            return point.components().view();
        }

        template <int iNumDimensions>
        inline
        IntervalMatrixViewXd
        mutableView(Box<iNumDimensions>& box) {
            return box.components().view();
        }

        inline
        MatrixViewXd
        mutableView(std::vector<double>& values) {
            return MatrixViewXd(
                values.data(),
                1,
                int(values.size()),
                sizeof(double)
            );
        }

        inline
        IntervalMatrixViewXd
        mutableView(std::vector<Interval>& values) {
            return IntervalMatrixViewXd(
                values.data(),
                1,
                int(values.size()),
                sizeof(Interval)
            );
        }

        template <int iNumDimensions>
        inline
        MatrixViewXd
        mutableView(std::vector<Vector<double, iNumDimensions>>& vectors) {
            return MatrixViewXd(
                vectors.front().data(),
                iNumDimensions,
                int(vectors.size()),
                sizeof(Vector<double, iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        IntervalMatrixViewXd
        mutableView(std::vector<Vector<Interval, iNumDimensions>>& intervalVectors) {
            return IntervalMatrixViewXd(
                intervalVectors.front().data(),
                iNumDimensions,
                int(intervalVectors.size()),
                sizeof(Vector<Interval, iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        MatrixViewXd
        mutableView(std::vector<Point<iNumDimensions>>& points) {
            return MatrixViewXd(
                points.front().data(),
                iNumDimensions,
                int(points.size()),
                sizeof(Point<iNumDimensions>)
            );
        }

        template <int iNumDimensions>
        inline
        IntervalMatrixViewXd
        mutableView(std::vector<Box<iNumDimensions>>& boxes) {
            return IntervalMatrixViewXd(
                boxes.front().data(),
                iNumDimensions,
                int(boxes.size()),
                sizeof(Box<iNumDimensions>)
            );
        }

        inline
        ColumnMatrixXd
        components(double value) {
            return ColumnMatrixXd::constant(1, value);
        }

        template <int iNumDimensions>
        inline
        ColumnMatrixXd
        components(const Vector<double, iNumDimensions>& vector) {
            return vector.components();
        }

        template <int iNumDimensions>
        inline
        ColumnMatrixXd
        components(const Point<iNumDimensions>& point) {
            return point.components();
        }

        template <class TValue>
        struct IsVector
        {
            static const bool Value = false;
        };

        template <int iNumDimensions>
        struct IsVector<Vector<double, iNumDimensions>>
        {
            static const bool Value = true;
        };
    }

    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>::ParametricExpression() :
        _compiledExpressionPtr(
            new detail::CompiledExpression(detail::zeroExpression<TValue, TParameter>())
        ) {
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>::ParametricExpression(
        const detail::ExpressionImplementation* implementationPtr
    ) : _compiledExpressionPtr(new detail::CompiledExpression(implementationPtr)) {
        if (!implementation()) {
            throw Error(new PlaceholderError());
        }
        if (implementation()->numDimensions() != NumDimensions<TValue>::Value) {
            throw Error(new PlaceholderError());
        }
        if (implementation()->numParameters() != NumDimensions<TParameter>::Value) {
            throw Error(new PlaceholderError());
        }
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>::ParametricExpression(
        detail::ExpressionImplementationPtr implementationPtr
    ) : _compiledExpressionPtr(new detail::CompiledExpression(std::move(implementationPtr))) {
        if (!implementation()) {
            throw Error(new PlaceholderError());
        }
        if (implementation()->numDimensions() != NumDimensions<TValue>::Value) {
            throw Error(new PlaceholderError());
        }
        if (implementation()->numParameters() != NumDimensions<TParameter>::Value) {
            throw Error(new PlaceholderError());
        }
    }

    template <class TValue, class TParameter>
    inline
    const detail::ExpressionImplementationPtr&
    ParametricExpression<TValue, TParameter>::implementation() const {
        return _compiledExpressionPtr->implementation();
    }
        
    template <class TValue, class TParameter>
    inline
    TValue
    ParametricExpression<TValue, TParameter>::evaluate(const TParameter& parameterValue) const {
        ConstMatrixViewXd parameterView = detail::constView(parameterValue);

        TValue result;
        MatrixViewXd resultView = detail::mutableView(result);

        _compiledExpressionPtr->evaluate(parameterView, resultView);

        return result;
    }
    
    template <class TValue, class TParameter>
    inline
    typename BoundsType<TValue>::Type
    ParametricExpression<TValue, TParameter>::evaluate(
        const typename BoundsType<TParameter>::Type& parameterBounds
    ) const {
        ConstIntervalMatrixViewXd parameterView = detail::constView(parameterBounds);

        typename BoundsType<TValue>::Type result;
        IntervalMatrixViewXd resultView = detail::mutableView(result);

        _compiledExpressionPtr->evaluate(parameterView, resultView);

        return result;
    }

    template <class TValue, class TParameter>
    inline
    std::vector<TValue>
    ParametricExpression<TValue, TParameter>::evaluate(
        const std::vector<TParameter>& parameterValues
    ) const {
        ConstMatrixViewXd parameterView = detail::constView(parameterValues);

        std::vector<TValue> results(parameterValues.size());
        MatrixViewXd resultView = detail::mutableView(results);

        _compiledExpressionPtr->evaluate(parameterView, resultView);

        return results;
    }

    template <class TValue, class TParameter>
    inline
    std::vector<typename BoundsType<TValue>::Type>
    ParametricExpression<TValue, TParameter>::evaluate(
        const std::vector<typename BoundsType<TParameter>::Type>& parameterBounds
    ) const {
        ConstIntervalMatrixViewXd parameterView = detail::constView(parameterBounds);

        std::vector<typename BoundsType<TValue>::Type> results(parameterBounds.size());
        IntervalMatrixViewXd resultView = detail::mutableView(results);

        _compiledExpressionPtr->evaluate(parameterView, resultView);

        return results;
    }
    
    template <class TValue, class TParameter>
    inline
    Matrix<double, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value>
    ParametricExpression<TValue, TParameter>::jacobian(const TParameter& parameterValue) const {
        ConstMatrixViewXd parameterView = detail::constView(parameterValue);

        Matrix<double, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value> result;
        MatrixViewXd resultView = result.view();

        _compiledExpressionPtr->evaluateJacobian(parameterView, resultView);

        return result;
    }
    
    template <class TValue, class TParameter>
    inline
    Matrix<Interval, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value>
    ParametricExpression<TValue, TParameter>::jacobian(
        const typename BoundsType<TParameter>::Type& parameterBounds
    ) const {
        ConstIntervalMatrixViewXd parameterView = detail::constView(parameterBounds);

        Matrix<Interval, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value> result;
        IntervalMatrixViewXd resultView = result.view();

        _compiledExpressionPtr->evaluateJacobian(parameterView, resultView);

        return result;
    }

    template <class TValue, class TParameter> template <class TInnerParameter>
    ParametricExpression<TValue, TInnerParameter>
    ParametricExpression<TValue, TParameter>::composed(
        const ParametricExpression<TParameter, TInnerParameter>& innerExpression
    ) const {
        detail::DeduplicationCache deduplicationCache;
        return implementation()->composed(
            innerExpression.implementation()
        )->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
    ParametricExpression<TValue, TParameter>::derivative() const {
        static_assert(
            std::is_same<TParameter, double>::value,
            "Must supply Parameter object or parameter index to derivative() if parametric "
            "expression has multiple parameters"
        );
        detail::DeduplicationCache deduplicationCache;
        return implementation()->derivative(0)->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
    ParametricExpression<TValue, TParameter>::derivative(int parameterIndex) const {
        if (parameterIndex < 0 || parameterIndex >= NumDimensions<TParameter>::Value) {
            throw Error(new PlaceholderError());
        }
        detail::DeduplicationCache deduplicationCache;
        return implementation()->derivative(parameterIndex)->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
    ParametricExpression<TValue, TParameter>::derivative(
        const Parameter<TParameter>& parameter
    ) const {
        return derivative(parameter.parameterIndex());
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::norm() const {
        static_assert(
            detail::IsVector<TValue>::Value,
            "norm() only defined for vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->norm()->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>
    ParametricExpression<TValue, TParameter>::normalized() const {
        static_assert(
            detail::IsVector<TValue>::Value,
            "normalized() only defined for vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->normalized()->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::squaredNorm() const {
        static_assert(
            detail::IsVector<TValue>::Value,
            "squaredNorm() only defined for vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->squaredNorm()->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::squared() const {
        static_assert(
            std::is_same<TValue, double>::value,
            "squared() is only defined for scalars"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->squaredNorm()->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::x() const {
        detail::DeduplicationCache deduplicationCache;
        return implementation()->x()->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::y() const {
        static_assert(
            NumDimensions<TValue>::Value >= 2,
            "No Y component exists"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->y()->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::z() const {
        static_assert(
            NumDimensions<TValue>::Value >= 3,
            "No Z component exists"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->z()->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::component(int index) const {
        if (index < 0 || index >= NumDimensions<TValue>::Value) {
            throw Error(new PlaceholderError());
        }
        detail::DeduplicationCache deduplicationCache;
        return implementation()->component(index)->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::dot(const TValue& vector) const {
        static_assert(
            detail::IsVector<TValue>::Value,
            "dot() only defined for vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->dot(
            new detail::ConstantExpression(vector.components(), NumDimensions<TParameter>::Value)
        )->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<double, TParameter>
    ParametricExpression<TValue, TParameter>::dot(
        const ParametricExpression<TValue, TParameter>& other
    ) const {
        static_assert(
            detail::IsVector<TValue>::Value,
            "dot() only defined for vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->dot(other.implementation())->deduplicated(deduplicationCache);
    }
        
    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>
    ParametricExpression<TValue, TParameter>::cross(const TValue& vector) const {
        static_assert(
            std::is_same<TValue, Vector3d>::value,
            "Cross product only defined for 3D vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->cross(
            new detail::ConstantExpression(vector.components(), NumDimensions<TParameter>::Value)
        )->deduplicated(deduplicationCache);
    }
    
    template <class TValue, class TParameter>
    ParametricExpression<TValue, TParameter>
    ParametricExpression<TValue, TParameter>::cross(
        const ParametricExpression<TValue, TParameter>& other
    ) const {
        static_assert(
            std::is_same<TValue, Vector3d>::value,
            "Cross product only defined for 3D vectors"
        );

        detail::DeduplicationCache deduplicationCache;
        return implementation()->cross(other.implementation())->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<typename NegatedType<TValue>::Type, TParameter>
    operator-(const ParametricExpression<TValue, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return (-expression.implementation())->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            firstExpression.implementation() + secondExpression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            expression.implementation() + detail::components(value)
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            detail::components(value) + expression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            firstExpression.implementation() - secondExpression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            expression.implementation() - detail::components(value)
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            detail::components(value) - expression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            firstExpression.implementation() * secondExpression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            expression.implementation() * detail::components(value)
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            detail::components(value) * expression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename QuotientType<TFirstValue, TSecondValue>::Type, TParameter>
    operator/(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            firstExpression.implementation() / secondExpression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    ParametricExpression<typename QuotientType<TValue, double>::Type, TParameter>
    operator/(const ParametricExpression<TValue, TParameter>& expression, double value) {
        detail::DeduplicationCache deduplicationCache;
        return (expression.implementation() / value)->deduplicated(deduplicationCache);
    }

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename QuotientType<TFirstValue, TSecondValue>::Type, TParameter>
    operator/(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    ) {
        detail::DeduplicationCache deduplicationCache;
        return (
            detail::components(value) / expression.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TParameter>
    ParametricExpression<double, TParameter>
    sin(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return sin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    cos(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return cos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    tan(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return tan(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    sqrt(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return sqrt(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    acos(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return acos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    asin(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return asin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    exp(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return exp(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    log(const ParametricExpression<double, TParameter>& expression) {
        detail::DeduplicationCache deduplicationCache;
        return log(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(const ParametricExpression<double, TParameter>& base, double exponent) {
        detail::DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent)->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(double base, const ParametricExpression<double, TParameter>& exponent) {
        detail::DeduplicationCache deduplicationCache;
        return pow(base, exponent.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(
        const ParametricExpression<double, TParameter>& base,
        const ParametricExpression<double, TParameter>& exponent
    ) {
        detail::DeduplicationCache deduplicationCache;
        return pow(
            base.implementation(),
            exponent.implementation()
        )->deduplicated(deduplicationCache);
    }

    template <class TValue, class TParameter>
    std::ostream&
    operator<<(
        std::ostream& stream,
        const ParametricExpression<TValue, TParameter>& expression
    ) {
        expression.implementation()->debug(stream, 0);
        return stream;
    }
}
