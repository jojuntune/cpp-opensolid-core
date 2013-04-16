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

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <OpenSolid/Core/Function/FunctionConstructors.hpp>
#include <OpenSolid/Core/Function/JacobianReturnValue.hpp>
#include <OpenSolid/Core/Function/MatrixReturnValue.hpp>
 
#include <boost/intrusive_ptr.hpp>

#include <typeinfo>

namespace opensolid
{
    class Function :
        public FunctionConstructors,
        public Convertible<Function>,
        public Transformable<Function>
    {
    private:
        boost::intrusive_ptr<const FunctionImplementation> _implementation;
    public:
        OPENSOLID_CORE_EXPORT
        Function();
        
        OPENSOLID_CORE_EXPORT
        Function(const FunctionImplementation* function);

        OPENSOLID_CORE_EXPORT
        Function(const Rotation2d& rotation);
        
        OPENSOLID_CORE_EXPORT
        Function(const Rotation3d& rotation);
        
        OPENSOLID_CORE_EXPORT
        Function(const Mirror2d& mirror);
        
        OPENSOLID_CORE_EXPORT
        Function(const Mirror3d& mirror);
        
        OPENSOLID_CORE_EXPORT
        Function(const Projection2d& projection);
        
        OPENSOLID_CORE_EXPORT
        Function(const Projection3d& projection);

        template <int iNumSourceDimensions, int iNumDestinationDimensions>
        Function(const Transplant<iNumSourceDimensions, iNumDestinationDimensions>& transplant);
        
        const FunctionImplementation*
        implementation() const;
        
        bool
        isValid() const;
        
        OPENSOLID_CORE_EXPORT int
        numDimensions() const;
        
        OPENSOLID_CORE_EXPORT int
        numParameters() const;

        OPENSOLID_CORE_EXPORT const ConstantFunction*
        asConstant() const;
        
        OPENSOLID_CORE_EXPORT const IdentityFunction*
        asIdentity() const;
        
        OPENSOLID_CORE_EXPORT const ParameterFunction*
        asParameter() const;

        OPENSOLID_CORE_EXPORT bool
        isDuplicate(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        deduplicated() const;
        
        OPENSOLID_CORE_EXPORT Function
        deduplicated(std::vector<Function>& others) const;

        MatrixReturnValue<int>
        operator()(int value) const;
        
        MatrixReturnValue<double>
        operator()(double value) const;
        
        MatrixReturnValue<Interval>
        operator()(Interval interval) const;
        
        template <class TMatrix>
        MatrixReturnValue<TMatrix>
        operator()(const EigenBase<TMatrix>& matrix) const;

        JacobianReturnValue<Function, int>
        jacobian(int value) const;
        
        JacobianReturnValue<Function, double>
        jacobian(double value) const;
        
        JacobianReturnValue<Function, Interval>
        jacobian(Interval interval) const;
        
        template <class TVector>
        JacobianReturnValue<Function, TVector>
        jacobian(const EigenBase<TVector>& vector) const;
        
        OPENSOLID_CORE_EXPORT Function
        compose(const Function& function) const;
        
        OPENSOLID_CORE_EXPORT Function
        derivative(int parameterIndex = 0) const;
        
        OPENSOLID_CORE_EXPORT Function
        norm() const;
        
        OPENSOLID_CORE_EXPORT Function
        normalized() const;
        
        OPENSOLID_CORE_EXPORT Function
        squaredNorm() const;
        
        OPENSOLID_CORE_EXPORT Function
        x() const;
        
        OPENSOLID_CORE_EXPORT Function
        y() const;
        
        OPENSOLID_CORE_EXPORT Function
        z() const;
        
        OPENSOLID_CORE_EXPORT Function
        component(int index) const;
        
        OPENSOLID_CORE_EXPORT Function
        components(int startIndex, int numComponents) const;
        
        OPENSOLID_CORE_EXPORT Function
        concatenate(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        dot(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        cross(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        tangentVector() const;
        
        OPENSOLID_CORE_EXPORT Function
        curvature() const;
        
        OPENSOLID_CORE_EXPORT Function
        normalVector() const;
        
        OPENSOLID_CORE_EXPORT Function
        binormalVector() const;

        OPENSOLID_CORE_EXPORT Function
        operator+(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        operator-(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        operator*(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT Function
        operator/(const Function& other) const;

        OPENSOLID_CORE_EXPORT void
        debug(std::ostream& stream, int indent = 0) const;
    };

    OPENSOLID_CORE_EXPORT Function
    operator-(const Function& function);

    OPENSOLID_CORE_EXPORT Function
    operator+(const Function& function, double value);
    
    OPENSOLID_CORE_EXPORT Function
    operator+(double value, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    operator+(const Function& function, const VectorXd& vector);
    
    OPENSOLID_CORE_EXPORT Function
    operator+(const VectorXd& vector, const Function& function);

    OPENSOLID_CORE_EXPORT Function
    operator-(const Function& function, double value);
    
    OPENSOLID_CORE_EXPORT Function
    operator-(double value, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    operator-(const Function& function, const VectorXd& vector);
    
    OPENSOLID_CORE_EXPORT Function
    operator-(const VectorXd& vector, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    operator*(double value, const Function& function);

    OPENSOLID_CORE_EXPORT Function
    operator*(const Function& function, double scale);
    
    OPENSOLID_CORE_EXPORT Function
    operator*(const MatrixXd& matrix, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    operator*(const Function& function, const VectorXd& vector);

    OPENSOLID_CORE_EXPORT Function
    operator/(const Function& function, double value);
    
    OPENSOLID_CORE_EXPORT Function
    operator/(double value, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    operator/(const VectorXd& vector, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function
    sin(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    cos(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    tan(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    sqrt(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    acos(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    asin(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    exp(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    log(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function
    pow(const Function& base, const Function& exponent);

    OPENSOLID_CORE_EXPORT std::ostream&
    operator<<(std::ostream& stream, const Function& function);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<Function>
    {
        Function
        operator()(const Function& function, double scale) const;
    };

    template <>
    struct TranslationFunction<Function>
    {
        Function
        operator()(const Function& function, const VectorXd& vector) const;
    };

    template <int iTransformedDimensions>
    struct TransformationFunction<Function, iTransformedDimensions>
    {
        typedef Function Type;

        Function
        operator()(const Function& function, const MatrixXd& matrix) const;
    };
}
