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

#include <boost/functional/hash.hpp>
#include <boost/intrusive_ptr.hpp>

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>
#include "FunctionImplementation.hpp"
#include "implementations/ConstantFunction.hpp"

namespace OpenSolid
{
    template <class ArgumentType>
    class FunctionResult;
    
    class Domain;
    class Geometry;
    
    class Function
    {
    private:
        boost::intrusive_ptr<const FunctionImplementation> _implementation;
        const std::type_info* _type;
    public:
        Function();
        Function(const FunctionImplementation* function);
        Function(Double value);
        
        template <class DerivedType>
        Function(const EigenBase<DerivedType>& value);
        
        template <class XType, class YType>
        Function(const XType& x, const YType& y);
        
        template <class XType, class YType, class ZType>
        Function(const XType& x, const YType& y, const ZType& z);
        
        template <class XType, class YType, class ZType, class WType>
        Function(const XType& x, const YType& y, const ZType& z, const WType& w);
        
        const FunctionImplementation* implementation() const;
        
        template <class Type>
        bool isA() const;
        
        template <class Type>
        const Type& as() const;
        
        int parameters() const;
        int dimensions() const;
        
        std::size_t hashValue() const;
        
        bool operator==(const Function& other) const;
        
        template <class ArgumentType>
        FunctionResult<ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_CORE_EXPORT Function derivative(int index = 0) const;
        OPENSOLID_CORE_EXPORT Function norm() const;
        OPENSOLID_CORE_EXPORT Function normalized() const;
        OPENSOLID_CORE_EXPORT Function squaredNorm() const;
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
        
        OPENSOLID_CORE_EXPORT RowVectorXD zeros(const Interval& domain) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent = 0) const;
        
        OPENSOLID_CORE_EXPORT static Function t;
        OPENSOLID_CORE_EXPORT static Function u;
        OPENSOLID_CORE_EXPORT static Function v;
        
        OPENSOLID_CORE_EXPORT static Function CurveParameter();
        OPENSOLID_CORE_EXPORT static Function SurfaceParameter(int index);
        OPENSOLID_CORE_EXPORT static Function VolumeParameter(int index);
        OPENSOLID_CORE_EXPORT static Function HypervolumeParameter(int index);
        OPENSOLID_CORE_EXPORT static Function Parameter(int total, int index);
        OPENSOLID_CORE_EXPORT static Function Parameters(int total, int index, int num);
        OPENSOLID_CORE_EXPORT static Function Identity(int dimensions);
        
        OPENSOLID_CORE_EXPORT static Function Linear(
            const VectorXD& point,
            const MatrixXD& vectors
        );
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(
            const VectorXD& point,
            const MatrixXD& vectors
        );
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(
            const VectorXD& point,
            const MatrixXD& vectors,
            const VectorXb& convention
        );
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
    
    OPENSOLID_CORE_EXPORT Function operator*(const Function& function, const DatumXD& datum);
    OPENSOLID_CORE_EXPORT Function operator/(const Function& function, const DatumXD& datum);
    
    OPENSOLID_CORE_EXPORT Function cos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function sin(const Function& argument);
    OPENSOLID_CORE_EXPORT Function tan(const Function& argument);
    OPENSOLID_CORE_EXPORT Function sqrt(const Function& argument);
    OPENSOLID_CORE_EXPORT Function acos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function asin(const Function& argument);
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(
        std::ostream& stream,
        const Function& function
    );
}

////////// Implementation //////////

#include "FunctionResult.hpp"

namespace OpenSolid
{
    inline Function::Function() : _implementation(0), _type(0) {}
    
    inline Function::Function(const FunctionImplementation* implementation) :
        _implementation(implementation), _type(&typeid(implementation)) {}
    
    inline Function::Function(Double value) :
        _implementation(new ConstantFunction(VectorXD::Constant(1, value))),
        _type(&typeid(ConstantFunction)) {}
    
    template <class DerivedType>
    inline Function::Function(const EigenBase<DerivedType>& value) :
        _implementation(new ConstantFunction(value)), _type(&typeid(ConstantFunction)) {}
        
    template <class XType, class YType>
    Function::Function(const XType& x, const YType& y) {
        _implementation = Function(x).concatenate(y).implementation();
        _type = &typeid(implementation());
    }
    
    template <class XType, class YType, class ZType>
    Function::Function(const XType& x, const YType& y, const ZType& z) {
        _implementation = Function(x).concatenate(y).concatenate(z).implementation();
        _type = &typeid(implementation());
    }
    
    template <class XType, class YType, class ZType, class WType>
    Function::Function(const XType& x, const YType& y, const ZType& z, const WType& w) {
        _implementation = Function(x).concatenate(y).concatenate(z).concatenate(w).implementation();
        _type = &typeid(implementation());
    }
    
    inline const FunctionImplementation* Function::implementation() const {
        return _implementation.get();
    }
    
    template <class Type>
    inline bool Function::isA() const {
        assert(_type);
        return *_type == typeid(Type);
    }
    
    template <class Type>
    inline const Type& Function::as() const {
        assert(isA<Type>());
        return static_cast<const Type&>(*implementation());
    }
    
    inline int Function::parameters() const {return implementation()->parameters();}
    
    inline int Function::dimensions() const {return implementation()->dimensions();}
        
    inline std::size_t Function::hashValue() const {return boost::hash_value(implementation());}
    
    inline bool Function::operator==(const Function& other) const {
        return implementation() == other.implementation();
    }
    
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Function::operator()(const ArgumentType& argument) const {
        return FunctionResult<ArgumentType>(*this, argument);
    }
}

#endif
