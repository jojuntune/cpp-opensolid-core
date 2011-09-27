/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__FUNCTION_HPP
#define OPENSOLID__FUNCTION_HPP

#include <typeinfo>
#include <type_traits>

#include <boost/intrusive_ptr.hpp>

#include <OpenSolid/config.hpp>
#include <OpenSolid/declarations.hpp>
#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>
#include <OpenSolid/Function/FunctionImplementation/FunctionImplementation.hpp>
#include <OpenSolid/Function/FunctionImplementation/ConstantFunction.hpp>

namespace OpenSolid
{
    template <class ArgumentType>
    class FunctionResult;
    
    class Function : public Convertible<Function>, public Transformable<Function>
    {
    private:
        boost::intrusive_ptr<const FunctionImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Function();
        OPENSOLID_CORE_EXPORT Function(const FunctionImplementation* function);
        OPENSOLID_CORE_EXPORT Function(int value);
        OPENSOLID_CORE_EXPORT Function(double value);
        OPENSOLID_CORE_EXPORT Function(const Function& x, const Function& y);
        OPENSOLID_CORE_EXPORT Function(const Function& x, const Function& y, const Function& z);

        template <class VectorType>
        Function(const EigenBase<VectorType>& vector);
        
        OPENSOLID_CORE_EXPORT const FunctionImplementation* implementation() const;
        
        template <class Type>
        bool isA() const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;
        
        template <class ArgumentType>
        FunctionResult<ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_CORE_EXPORT Function derivative(int index = 0) const;
        OPENSOLID_CORE_EXPORT Function transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        OPENSOLID_CORE_EXPORT Function norm() const;
        OPENSOLID_CORE_EXPORT Function normalized() const;
        OPENSOLID_CORE_EXPORT Function squaredNorm() const;
        OPENSOLID_CORE_EXPORT Function x() const;
        OPENSOLID_CORE_EXPORT Function y() const;
        OPENSOLID_CORE_EXPORT Function z() const;
        OPENSOLID_CORE_EXPORT Function component(int index) const;
        OPENSOLID_CORE_EXPORT Function components(int index, int num) const;
        OPENSOLID_CORE_EXPORT Function concatenate(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function dot(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function cross(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function operator()(const Function& inner) const;
        OPENSOLID_CORE_EXPORT Function tangent() const;
        OPENSOLID_CORE_EXPORT Function curvature() const;
        OPENSOLID_CORE_EXPORT Function normal() const;
        OPENSOLID_CORE_EXPORT Function binormal() const;
        
        OPENSOLID_CORE_EXPORT Geometry operator()(const Domain& domain) const;
        OPENSOLID_CORE_EXPORT Geometry operator()(const Geometry& geometry) const;
        
        OPENSOLID_CORE_EXPORT RowVectorXd roots(const Interval& domain) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent = 0) const;

        OPENSOLID_CORE_EXPORT static Function Identity(int dimensions);
        
        OPENSOLID_CORE_EXPORT static Function Linear(
            const VectorXd& point,
            const MatrixXd& vectors
        );
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(
            const VectorXd& point,
            const MatrixXd& vectors
        );
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(
            const VectorXd& point,
            const MatrixXd& vectors,
            const VectorXb& convention
        );
    };
    
    template <>
    class Conversion<Function, double>
    {
    public:
        OPENSOLID_CORE_EXPORT double operator()(const Function& argument) const;
    };
    
    template <>
    class Conversion<Function, Vector2d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Function& argument) const;
    };
    
    template <>
    class Conversion<Function, Vector3d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Function& argument) const;
    };
    
    template <>
    class Conversion<Function, VectorXd>
    {
    public:
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Function& argument) const;
    };
    
    template <class FunctionType>
    class Conversion<Function, FunctionType>
    {
    static_assert(
        std::is_base_of<FunctionImplementation, FunctionType>::value,
        "Function can only be converted to double, Vector2d, Vector3d, VectorXd, "
        "or a FunctionImplementation subclass"
    );
    public:
        const FunctionType& operator()(const Function& argument) const;
    };

    OPENSOLID_CORE_EXPORT Function operator-(const Function& argument);
    
    OPENSOLID_CORE_EXPORT Function operator+(
        const Function& first_operand,
        const Function& second_operand
    );
    
    OPENSOLID_CORE_EXPORT Function operator-(
        const Function& first_operand,
        const Function& second_operand
    );
    
    OPENSOLID_CORE_EXPORT Function operator*(
        const Function& first_operand,
        const Function& second_operand
    );
    
    OPENSOLID_CORE_EXPORT Function operator/(
        const Function& first_operand,
        const Function& second_operand
    );
    
    OPENSOLID_CORE_EXPORT Function cos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function sin(const Function& argument);
    OPENSOLID_CORE_EXPORT Function tan(const Function& argument);
    OPENSOLID_CORE_EXPORT Function sqrt(const Function& argument);
    OPENSOLID_CORE_EXPORT Function acos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function asin(const Function& argument);
    OPENSOLID_CORE_EXPORT Function exp(const Function& argument);
    OPENSOLID_CORE_EXPORT Function log(const Function& argument);
    OPENSOLID_CORE_EXPORT Function pow(const Function& base, const Function& exponent);
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(
        std::ostream& stream,
        const Function& function
    );
}

////////// Implementation //////////

#include <OpenSolid/Function/Parameter.hpp>
#include <OpenSolid/Function/Parameters.hpp>
#include <OpenSolid/Function/FunctionResult.hpp>

namespace OpenSolid
{
    template <class VectorType>
    Function::Function(const EigenBase<VectorType>& vector) :
        _implementation(new ConstantFunction(vector)), _type(&typeid(ConstantFunction)) {}

    template <class Type>
    inline bool Function::isA() const {
        assert(_type);
        return *_type == typeid(Type);
    }
    
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Function::operator()(const ArgumentType& argument) const {
        return FunctionResult<ArgumentType>(*this, argument);
    }
    
    template <class FunctionType>
    inline const FunctionType& Conversion<Function, FunctionType>::operator()(
        const Function& argument
    ) const {
        assert(argument.isA<FunctionType>());
        return static_cast<const FunctionType&>(*argument.implementation());
    }
}

#endif
