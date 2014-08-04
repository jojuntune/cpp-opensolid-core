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
 
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>

#include <OpenSolid/Core/BoundsType.definitions.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>
#include <OpenSolid/Core/Parameter.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

#include <typeinfo>
#include <type_traits>
#include <vector>

namespace opensolid
{
    template <class TValue, class TParameter>
    struct NumDimensions<ParametricExpression<TValue, TParameter>>
    {
        static const int Value = NumDimensions<TValue>::Value;
    };

    template <class TValue, class TParameter, int iNumResultDimensions>
    struct TransformedType<ParametricExpression<TValue, TParameter>, iNumResultDimensions>
    {
        typedef ParametricExpression<
            typename TransformedType<TValue, iNumResultDimensions>::Type,
            TParameter
        > Type;
    };

    template <class TValue, class TParameter, class TResultValue>
    struct MorphedType<
        ParametricExpression<TValue, TParameter>,
        ParametricExpression<TResultValue, TValue>
    >
    {
        typedef ParametricExpression<TResultValue, TParameter> Type;
    };

    template <class TValue, class TParameter>
    class ParametricExpression :
        public detail::ExpressionConstructors<TValue, TParameter>,
        public Convertible<ParametricExpression<TValue, TParameter>>,
        public Transformable<ParametricExpression<TValue, TParameter>>
    {
    private:
        detail::ExpressionImplementationPtr _implementationPtr;
    public:
        ParametricExpression();

        ParametricExpression(const detail::ExpressionImplementation* implementationPtr);
        
        ParametricExpression(const detail::ExpressionImplementationPtr& implementationPtr);
        
        const detail::ExpressionImplementationPtr&
        implementation() const;
        
        TValue
        evaluate(const TParameter& parameterValue) const;
        
        typename BoundsType<TValue>::Type
        evaluate(const typename BoundsType<TParameter>::Type& parameterBounds) const;

        std::vector<TValue>
        evaluate(const std::vector<TParameter>& parameterValues) const;

        std::vector<typename BoundsType<TValue>::Type>
        evaluate(const std::vector<typename BoundsType<TParameter>::Type>& parameterBounds) const;
        
        const Matrix<double, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value>
        jacobian(const TParameter& parameterValue) const;
        
        const Matrix<Interval, NumDimensions<TValue>::Value, NumDimensions<TParameter>::Value>
        jacobian(const typename BoundsType<TParameter>::Type& parameterBounds) const;
        
        template <class TInnerParameter>
        ParametricExpression<TValue, TInnerParameter>
        composed(const ParametricExpression<TParameter, TInnerParameter>& innerExpression) const;
        
        ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
        derivative() const;

        ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
        derivative(int parameterIndex) const;

        ParametricExpression<typename DerivativeType<TValue>::Type, TParameter>
        derivative(const Parameter<TParameter>& parameter) const;
        
        ParametricExpression<double, TParameter>
        norm() const;
        
        ParametricExpression<TValue, TParameter>
        normalized() const;
        
        ParametricExpression<double, TParameter>
        squaredNorm() const;

        ParametricExpression<double, TParameter>
        squared() const;
        
        ParametricExpression<double, TParameter>
        x() const;
        
        ParametricExpression<double, TParameter>
        y() const;
        
        ParametricExpression<double, TParameter>
        z() const;
        
        ParametricExpression<double, TParameter>
        component(int index) const;

        ParametricExpression<double, TParameter>
        dot(const TValue& vector) const;

        ParametricExpression<double, TParameter>
        dot(const ParametricExpression<TValue, TParameter>& other) const;

        ParametricExpression<TValue, TParameter>
        cross(const TValue& vector) const;

        ParametricExpression<TValue, TParameter>
        cross(const ParametricExpression<TValue, TParameter>& other) const;
    };

    template <class TValue, class TParameter>
    ParametricExpression<typename NegatedType<TValue>::Type, TParameter>
    operator-(const ParametricExpression<TValue, TParameter>& expression);

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename SumType<TFirstValue, TSecondValue>::Type, TParameter>
    operator+(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename DifferenceType<TFirstValue, TSecondValue>::Type, TParameter>
    operator-(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const ParametricExpression<TFirstValue, TParameter>& expression,
        const TSecondValue& value
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename ProductType<TFirstValue, TSecondValue>::Type, TParameter>
    operator*(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    );

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename QuotientType<TFirstValue, TSecondValue>::Type, TParameter>
    operator/(
        const ParametricExpression<TFirstValue, TParameter>& firstExpression,
        const ParametricExpression<TSecondValue, TParameter>& secondExpression
    );

    template <class TValue, class TParameter>
    ParametricExpression<typename QuotientType<TValue, double>::Type, TParameter>
    operator/(const ParametricExpression<TValue, TParameter>& expression, double value);

    template <class TFirstValue, class TSecondValue, class TParameter>
    ParametricExpression<typename QuotientType<TFirstValue, TSecondValue>::Type, TParameter>
    operator/(
        const TFirstValue& value,
        const ParametricExpression<TSecondValue, TParameter>& expression
    );
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    sin(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    cos(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    tan(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    sqrt(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    acos(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    asin(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    exp(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    log(const ParametricExpression<double, TParameter>& expression);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(const ParametricExpression<double, TParameter>& base, double exponent);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(double base, const ParametricExpression<double, TParameter>& exponent);
    
    template <class TParameter>
    ParametricExpression<double, TParameter>
    pow(
        const ParametricExpression<double, TParameter>& base,
        const ParametricExpression<double, TParameter>& exponent
    );

    template <class TValue, class TParameter>
    std::ostream&
    operator<<(std::ostream& stream, const ParametricExpression<TValue, TParameter>& expression);

    template <>
    struct DerivativeType<double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct DerivativeType<Vector<double, iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct DerivativeType<Point<iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <>
    struct NegatedType<double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct NegatedType<Vector<double, iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <>
    struct SumType<double, double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct SumType<Vector<double, iNumDimensions>, Vector<double, iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct SumType<Point<iNumDimensions>, Vector<double, iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <>
    struct DifferenceType<double, double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct DifferenceType<Vector<double, iNumDimensions>, Vector<double, iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct DifferenceType<Point<iNumDimensions>, Vector<double, iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct DifferenceType<Point<iNumDimensions>, Point<iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <>
    struct ProductType<double, double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct ProductType<double, Vector<double, iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ProductType<Vector<double, iNumDimensions>, double>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <>
    struct QuotientType<double, double>
    {
        typedef double Type;
    };

    template <int iNumDimensions>
    struct QuotientType<Vector<double, iNumDimensions>, double>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions, class TParameter>
    struct ScalingFunction<ParametricExpression<Vector<double, iNumDimensions>, TParameter>>
    {
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>
        operator()(
            const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression,
            const Point<iNumDimensions>& originPoint,
            double scale
        ) const;
    };

    template <int iNumDimensions, class TParameter>
    struct ScalingFunction<ParametricExpression<Point<iNumDimensions>, TParameter>>
    {
        ParametricExpression<Point<iNumDimensions>, TParameter>
        operator()(
            const ParametricExpression<Point<iNumDimensions>, TParameter>& expression,
            const Point<iNumDimensions>& originPoint,
            double scale
        ) const;
    };

    template <int iNumDimensions, class TParameter>
    struct TranslationFunction<ParametricExpression<Vector<double, iNumDimensions>, TParameter>>
    {
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>
        operator()(
            const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, class TParameter>
    struct TranslationFunction<ParametricExpression<Point<iNumDimensions>, TParameter>>
    {
        ParametricExpression<Point<iNumDimensions>, TParameter>
        operator()(
            const ParametricExpression<Point<iNumDimensions>, TParameter>& expression,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, class TParameter, int iNumResultDimensions>
    struct TransformationFunction<
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>,
        iNumResultDimensions
    >
    {
        ParametricExpression<Vector<double, iNumResultDimensions>, TParameter>
        operator()(
            const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression,
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
            const Point<iNumResultDimensions>& destinationPoint
        ) const;
    };

    template <int iNumDimensions, class TParameter, int iNumResultDimensions>
    struct TransformationFunction<
        ParametricExpression<Point<iNumDimensions>, TParameter>,
        iNumResultDimensions
    >
    {
        ParametricExpression<Point<iNumResultDimensions>, TParameter>
        operator()(
            const ParametricExpression<Point<iNumDimensions>, TParameter>& expression,
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
            const Point<iNumResultDimensions>& destinationPoint
        ) const;
    };

    template <class TValue, class TParameter, class TResultValue>
    struct MorphingFunction<
        ParametricExpression<TValue, TParameter>,
        ParametricExpression<TResultValue, TValue>
    >
    {
        ParametricExpression<TResultValue, TParameter>
        operator()(
            const ParametricExpression<TValue, TParameter>& expression,
            const ParametricExpression<TResultValue, TValue>& morphingExpression
        ) const;
    };
}
