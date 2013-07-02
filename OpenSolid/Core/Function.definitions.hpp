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
 
#include <OpenSolid/Core/Function.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/Function/FunctionConstructors.definitions.hpp>
#include <OpenSolid/Core/Function/JacobianReturnValue.declarations.hpp>
#include <OpenSolid/Core/Function/FunctionReturnValue.declarations.hpp>
#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>

#include <typeinfo>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    class Function :
        public FunctionConstructors<iNumDimensions, iNumParameters>,
        public Convertible<Function<iNumDimensions, iNumParameters>>
    {
    private:
        FunctionImplementationPtr _implementation;
    public:
        Function();

        Function(const FunctionImplementation* implementation);
        
        Function(const FunctionImplementationPtr& implementation);
        
        const FunctionImplementationPtr&
        implementation() const;

        bool
        isConstant() const;
        
        bool
        isIdentity() const;
        
        bool
        isParameter() const;

        FunctionReturnValue<iNumDimensions, 1, int>
        operator()(int value) const;
        
        FunctionReturnValue<iNumDimensions, 1, double>
        operator()(double value) const;
        
        FunctionReturnValue<iNumDimensions, 1, Interval>
        operator()(Interval interval) const;
        
        template <class TMatrix>
        FunctionReturnValue<iNumDimensions, iNumParameters, TMatrix>
        operator()(const EigenBase<TMatrix>& matrix) const;

        JacobianReturnValue<iNumDimensions, 1, int>
        jacobian(int value) const;
        
        JacobianReturnValue<iNumDimensions, 1, double>
        jacobian(double value) const;
        
        JacobianReturnValue<iNumDimensions, 1, Interval>
        jacobian(Interval interval) const;
        
        template <class TVector>
        JacobianReturnValue<iNumDimensions, iNumParameters, TVector>
        jacobian(const EigenBase<TVector>& vector) const;
        
        template <int iNumInnerParameters>
        Function<iNumDimensions, iNumInnerParameters>
        composed(const Function<iNumParameters, iNumInnerParameters>& innerFunction) const;
        
        Function<iNumDimensions, iNumParameters>
        derivative(int parameterIndex = 0) const;
        
        Function<1, iNumParameters>
        norm() const;
        
        Function<iNumDimensions, iNumParameters>
        normalized() const;
        
        Function<1, iNumParameters>
        squaredNorm() const;
        
        Function<1, iNumParameters>
        x() const;
        
        Function<1, iNumParameters>
        y() const;
        
        Function<1, iNumParameters>
        z() const;
        
        Function<1, iNumParameters>
        component(int index) const;
        
        template <int iNumComponents>
        Function<iNumComponents, iNumParameters>
        components(int startIndex) const;
        
        template <int iNumOtherDimensions>
        Function<iNumDimensions + iNumOtherDimensions, iNumParameters>
        concatenated(const Function<iNumOtherDimensions, iNumParameters>& other) const;
        
        Function<1, iNumParameters>
        dot(const Function<iNumDimensions, iNumParameters>& other) const;
        
        Function<3, iNumParameters>
        cross(const Function<3, iNumParameters>& other) const;
        
        Function<iNumDimensions, 1>
        tangentVector() const;
        
        Function<1, 1>
        curvature() const;
        
        Function<iNumDimensions, iNumParameters>
        normalVector() const;
        
        Function<3, 1>
        binormalVector() const;
    };

    template <int iNumParameters, int iNumDimensions>
    Function<iNumParameters, iNumDimensions>
    operator-(const Function<iNumParameters, iNumDimensions>& function);

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator+(const Function<1, iNumParameters>& function, double value);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator+(double value, const Function<1, iNumParameters>& function);
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const Function<iNumDimensions, iNumParameters>& function,
        const EigenBase<TVector>& vector
    );
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const EigenBase<TVector>& vector,
        const Function<iNumDimensions, iNumParameters>& function
    );

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator+(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    );

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator-(const Function<1, iNumParameters>& function, double value);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator-(double value, const Function<1, iNumParameters>& function);
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const Function<iNumDimensions, iNumParameters>& function,
        const EigenBase<TVector>& vector
    );
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const EigenBase<TVector>& vector,
        const Function<iNumDimensions, iNumParameters>& function
    );

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator-(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    );
    
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator*(double value, const Function<iNumDimensions, iNumParameters>& function);

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator*(const Function<iNumDimensions, iNumParameters>& function, double value);
    
    template <int iNumDimensions, int iNumParameters, class TMatrix>
    Function<TMatrix::RowsAtCompileTime, iNumParameters>
    operator*(
        const EigenBase<TMatrix>& matrix,
        const Function<iNumDimensions, iNumParameters>& function
    );
    
    template <class TVector, int iNumParameters>
    Function<TVector::RowsAtCompileTime, iNumParameters>
    operator*(const Function<1, iNumParameters>& function, const EigenBase<TVector>& vector);

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator*(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    );

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator*(
        const Function<1, iNumParameters>& firstFunction,
        const Function<iNumDimensions, iNumParameters>& secondFunction
    );

    template <int iNumParameters>
    Function<1, iNumParameters>
    operator*(
        const Function<1, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    );

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    operator/(const Function<iNumDimensions, iNumParameters>& function, double value);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    operator/(double value, const Function<1, iNumParameters>& function);
    
    template <class TVector, int iNumParameters>
    Function<TVector::RowsAtCompileTime, iNumParameters>
    operator/(const EigenBase<TVector>& vector, const Function<1, iNumParameters>& function);

    template <int iNumParameters, int iNumDimensions>
    Function<iNumDimensions, iNumParameters>
    operator/(
        const Function<iNumDimensions, iNumParameters>& firstFunction,
        const Function<1, iNumParameters>& secondFunction
    );
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    sin(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    cos(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    tan(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    sqrt(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    acos(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    asin(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    exp(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    log(const Function<1, iNumParameters>& argument);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(const Function<1, iNumParameters>& base, double exponent);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(double base, const Function<1, iNumParameters>& exponent);
    
    template <int iNumParameters>
    Function<1, iNumParameters>
    pow(const Function<1, iNumParameters>& base, const Function<1, iNumParameters>& exponent);

    template <int iNumDimensions, int iNumParameters>
    std::ostream&
    operator<<(std::ostream& stream, const Function<iNumDimensions, iNumParameters>& function);
}
