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

#include <OpenSolid/config.hpp>

#include <typeinfo>

#include <boost/intrusive_ptr.hpp>

#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Datum/Datum.hpp>
#include <OpenSolid/Evaluation/Evaluation.hpp>
#include <OpenSolid/Function/FunctionConstructors.hpp>
#include <OpenSolid/Function/FunctionImplementation/FunctionImplementation.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    class FunctionImplementation;

    class Function :
        public FunctionConstructors,
        public Convertible<Function>,
        public Transformable<Function>
    {
    private:
        boost::intrusive_ptr<const FunctionImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Function();
        OPENSOLID_CORE_EXPORT Function(const FunctionImplementation* function);

        OPENSOLID_CORE_EXPORT Function(int value);
        OPENSOLID_CORE_EXPORT Function(double value);
        OPENSOLID_CORE_EXPORT Function(const VectorXd& vector);
        OPENSOLID_CORE_EXPORT Function(const Function& x, const Function& y);
        OPENSOLID_CORE_EXPORT Function(const Function& x, const Function& y, const Function& z);

        template <class DerivedType>
        Function(const EigenBase<DerivedType>& vector);
        
        OPENSOLID_CORE_EXPORT const FunctionImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;

        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameter_bounds, MapXI& results) const;
        
        template <class ArgumentType>
        Evaluation<Function, ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_CORE_EXPORT Function derivative(int index = 0) const;

        OPENSOLID_CORE_EXPORT Function transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
        
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
    };
    
    template <>
    struct Conversion<Function, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, Vector2d>
    {
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, Vector3d>
    {
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, VectorXd>
    {
        OPENSOLID_CORE_EXPORT const VectorXd& operator()(const Function& argument) const;
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

namespace OpenSolid
{
    template <class DerivedType>
    Function::Function(const EigenBase<DerivedType>& vector) {
        *this = Function(VectorXd(vector));
    }
    
    template <class ArgumentType>
    inline Evaluation<Function, ArgumentType> Function::operator()(const ArgumentType& argument) const {
        return Evaluation<Function, ArgumentType>(*this, argument);
    }
}

#endif
