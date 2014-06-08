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

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Parameter.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>

#include <typeinfo>
#include <vector>

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
            iNumDimensions > 0,
            "ParametricExpression must have positive number of dimensions"
        );

        static_assert(
            iNumParameters > 0,
            "ParametricExpression must have positive number of parameters"
        );

        ParametricExpression();

        ParametricExpression(const ExpressionImplementation* implementationPtr);
        
        ParametricExpression(const ExpressionImplementationPtr& implementationPtr);
        
        const ExpressionImplementationPtr&
        implementation() const;
        
        const Matrix<double, iNumDimensions, 1>
        evaluate(double u) const;

        const Matrix<double, iNumDimensions, 1>
        evaluate(double u, double v) const;

        const Matrix<double, iNumDimensions, 1>
        evaluate(double u, double v, double w) const;
        
        const Matrix<Interval, iNumDimensions, 1>
        evaluate(Interval u) const;
        
        const Matrix<Interval, iNumDimensions, 1>
        evaluate(Interval u, Interval v) const;
        
        const Matrix<Interval, iNumDimensions, 1>
        evaluate(Interval u, Interval v, Interval w) const;

        template <int iNumColumns>
        const Matrix<double, iNumDimensions, iNumColumns>
        evaluate(const Matrix<double, iNumParameters, iNumColumns>& parameterValues) const;

        template <int iNumColumns>
        const Matrix<Interval, iNumDimensions, iNumColumns>
        evaluate(const Matrix<Interval, iNumParameters, iNumColumns>& parameterValues) const;

        std::vector<Matrix<double, iNumDimensions, 1>>
        evaluate(const std::vector<double>& parameterValues) const;

        std::vector<Matrix<Interval, iNumDimensions, 1>>
        evaluate(const std::vector<Interval>& parameterValues) const;

        std::vector<Matrix<double, iNumDimensions, 1>>
        evaluate(
            const std::vector<Matrix<double, iNumParameters, 1>>& parameterValues
        ) const;

        std::vector<Matrix<Interval, iNumDimensions, 1>>
        evaluate(
            const std::vector<Matrix<Interval, iNumParameters, 1>>& parameterValues
        ) const;
        
        const Matrix<double, iNumDimensions, iNumParameters>
        jacobian(double u) const;
        
        const Matrix<double, iNumDimensions, iNumParameters>
        jacobian(double u, double v) const;
        
        const Matrix<double, iNumDimensions, iNumParameters>
        jacobian(double u, double v, double w) const;
        
        const Matrix<Interval, iNumDimensions, iNumParameters>
        jacobian(Interval u) const;
        
        const Matrix<Interval, iNumDimensions, iNumParameters>
        jacobian(Interval u, Interval v) const;
        
        const Matrix<Interval, iNumDimensions, iNumParameters>
        jacobian(Interval u, Interval v, Interval w) const;
        
        const Matrix<double, iNumDimensions, iNumParameters>
        jacobian(const Matrix<double, iNumParameters, 1>& parameterValues) const;
        
        const Matrix<Interval, iNumDimensions, iNumParameters>
        jacobian(const Matrix<Interval, iNumParameters, 1>& parameterValues) const;
        
        template <int iNumInnerParameters>
        ParametricExpression<iNumDimensions, iNumInnerParameters>
        composed(
            const ParametricExpression<iNumParameters, iNumInnerParameters>& innerExpression
        ) const;
        
        ParametricExpression<iNumDimensions, iNumParameters>
        derivative() const;

        ParametricExpression<iNumDimensions, iNumParameters>
        derivative(int parameterIndex) const;

        ParametricExpression<iNumDimensions, iNumParameters>
        derivative(const Parameter<iNumParameters>& parameter) const;
        
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

        ParametricExpression<1, iNumParameters>
        dot(const Matrix<double, iNumDimensions, 1>& columnMatrix) const;

        ParametricExpression<1, iNumParameters>
        dot(const ParametricExpression<iNumDimensions, iNumParameters>& other) const;

        ParametricExpression<3, iNumParameters>
        cross(const Matrix<double, 3, 1>& columnMatrix) const;

        ParametricExpression<3, iNumParameters>
        cross(const ParametricExpression<3, iNumParameters>& other) const;
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
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const Matrix<double, iNumDimensions, 1>& columnMatrix
    );
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const Matrix<double, iNumDimensions, 1>& columnMatrix,
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
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const Matrix<double, iNumDimensions, 1>& columnMatrix
    );
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const Matrix<double, iNumDimensions, 1>& columnMatrix,
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
    
    template <int iNumDimensions, int iNumParameters, int iNumResultDimensions>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator*(
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    );
    
    template <int iNumParameters, int iNumResultDimensions>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& expression,
        const Matrix<double, iNumResultDimensions, 1>& columnMatrix
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
    
    template <int iNumResultDimensions, int iNumParameters>
    ParametricExpression<iNumResultDimensions, iNumParameters>
    operator/(
        const Matrix<double, iNumResultDimensions, 1>& columnMatrix,
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
