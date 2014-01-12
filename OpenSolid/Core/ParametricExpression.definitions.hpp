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
 
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionEvaluation.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/JacobianEvaluation.declarations.hpp>

#include <typeinfo>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    class ParametricExpression :
        public ExpressionConstructors<iNumDimensions, iNumParameters>,
        public Convertible<ParametricExpression<iNumDimensions, iNumParameters>>
    {
    private:
        ExpressionImplementationPtr _implementationPtr;
    public:
        static_assert(
            iNumDimensions > 0 && iNumDimensions != Dynamic,
            "Invalid number of dimensions for ParametricExpression object"
        );

        static_assert(
            iNumParameters > 0 && iNumDimensions != Dynamic,
            "Invalid number of parameters for ParametricExpression object"
        );

        ParametricExpression();

        ParametricExpression(const ExpressionImplementation* implementationPtr);
        
        ParametricExpression(const ExpressionImplementationPtr& implementationPtr);
        
        const ExpressionImplementationPtr&
        implementation() const;

        Matrix<double, iNumDimensions, 1>
        evaluate(int value) const;
        
        Matrix<double, iNumDimensions, 1>
        evaluate(double value) const;
        
        Matrix<Interval, iNumDimensions, 1>
        evaluateBounds(Interval interval) const;

        Matrix<double, iNumDimensions, 1>
        evaluate(const Matrix<double, iNumParameters, 1> parameterValues) const;

        Matrix<Interval, iNumDimensions, 1>
        evaluate(const Matrix<Interval, iNumParameters, 1> parameterValues) const;

        SpatialList<Matrix<double, iNumDimensions, 1>>
        evaluate(
            const SpatialList<Matrix<double, iNumParameters, 1>>& parameterValues
        ) const;

        SpatialList<Matrix<double, iNumDimensions, 1>>
        evaluateBounds(
            const SpatialList<Matrix<Interval, iNumParameters, 1>>& parameterBounds
        ) const;

        JacobianEvaluation<iNumDimensions, 1, int>
        jacobian(int value) const;
        
        JacobianEvaluation<iNumDimensions, 1, double>
        jacobian(double value) const;
        
        JacobianEvaluation<iNumDimensions, 1, Interval>
        jacobianBounds(Interval interval) const;
        
        template <class TVector>
        JacobianEvaluation<iNumDimensions, iNumParameters, TVector>
        jacobian(const EigenBase<TVector>& vector) const;
        
        template <class TVector>
        JacobianEvaluation<iNumDimensions, iNumParameters, TVector>
        jacobianBounds(const EigenBase<TVector>& vector) const;
        
        template <int iNumInnerParameters>
        ParametricExpression<iNumDimensions, iNumInnerParameters>
        composed(
            const ParametricExpression<iNumParameters, iNumInnerParameters>& innerExpression
        ) const;
        
        ParametricExpression<iNumDimensions, iNumParameters>
        derivative(int parameterIndex = 0) const;
        
        ParametricExpression<1, iNumParameters>
        norm() const;
        
        ParametricExpression<iNumDimensions, iNumParameters>
        normalized() const;
        
        ParametricExpression<1, iNumParameters>
        squaredNorm() const;

        ParametricExpression<1, iNumParameters>
        squared() const;
        
        ParametricExpression<1, iNumParameters>
        x() const;
        
        ParametricExpression<1, iNumParameters>
        y() const;
        
        ParametricExpression<1, iNumParameters>
        z() const;
        
        ParametricExpression<1, iNumParameters>
        component(int index) const;
        
        template <int iNumComponents>
        ParametricExpression<iNumComponents, iNumParameters>
        components(int startIndex) const;
        
        template <int iNumOtherDimensions>
        ParametricExpression<iNumDimensions + iNumOtherDimensions, iNumParameters>
        concatenated(const ParametricExpression<iNumOtherDimensions, iNumParameters>& other) const;

        template <class TVector>
        ParametricExpression<1, iNumParameters>
        dot(const EigenBase<TVector>& vector) const;
        
        ParametricExpression<1, iNumParameters>
        dot(const ParametricExpression<iNumDimensions, iNumParameters>& other) const;
        
        template <class TVector>
        ParametricExpression<3, iNumParameters>
        cross(const EigenBase<TVector>& vector) const;
        
        ParametricExpression<3, iNumParameters>
        cross(const ParametricExpression<3, iNumParameters>& other) const;
        
        ParametricExpression<iNumDimensions, 1>
        tangentVector() const;
        
        ParametricExpression<1, 1>
        curvature() const;
        
        ParametricExpression<iNumDimensions, iNumParameters>
        normalVector() const;
        
        ParametricExpression<3, 1>
        binormalVector() const;
    };

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumParameters, iNumDimensions>
    operator-(const ParametricExpression<iNumParameters, iNumDimensions>& expression);

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(const ParametricExpression<1, iNumParameters>& expression, double value);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(double value, const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    );
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const EigenBase<TVector>& vector,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    );

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(const ParametricExpression<1, iNumParameters>& expression, double value);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(double value, const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    );
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const EigenBase<TVector>& vector,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    );
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        double value,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    );
    
    template <int iNumDimensions, int iNumParameters, class TMatrix>
    ParametricExpression<TMatrix::RowsAtCompileTime, iNumParameters>
    operator*(
        const EigenBase<TMatrix>& matrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );
    
    template <class TVector, int iNumParameters>
    ParametricExpression<TVector::RowsAtCompileTime, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    );

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    );

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    );

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    );

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    );
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator/(double value, const ParametricExpression<1, iNumParameters>& expression);
    
    template <class TVector, int iNumParameters>
    ParametricExpression<TVector::RowsAtCompileTime, iNumParameters>
    operator/(
        const EigenBase<TVector>& vector,
        const ParametricExpression<1, iNumParameters>& expression
    );

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    );
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sin(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    cos(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    tan(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sqrt(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    acos(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    asin(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    exp(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    log(const ParametricExpression<1, iNumParameters>& expression);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(const ParametricExpression<1, iNumParameters>& base, double exponent);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(double base, const ParametricExpression<1, iNumParameters>& exponent);
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(
        const ParametricExpression<1, iNumParameters>& base,
        const ParametricExpression<1, iNumParameters>& exponent
    );

    template <int iNumDimensions, int iNumParameters>
    std::ostream&
    operator<<(
        std::ostream& stream,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );
}
