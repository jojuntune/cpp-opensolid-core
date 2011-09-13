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

#ifndef OPENSOLID__GEOMETRY_HPP
#define OPENSOLID__GEOMETRY_HPP

#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Datum/Axis.hpp>

namespace OpenSolid
{
    class Geometry : public Convertible<Geometry>, public Transformable<Geometry>
    {
    private:
        Function _function;
        Domain _domain;
    public:
        OPENSOLID_CORE_EXPORT Geometry();
        OPENSOLID_CORE_EXPORT Geometry(const Function& function, const Domain& domain);
        OPENSOLID_CORE_EXPORT Geometry(double value);
        OPENSOLID_CORE_EXPORT Geometry(const VectorXd& value);
        
        OPENSOLID_CORE_EXPORT const Function& function() const;
        OPENSOLID_CORE_EXPORT const Domain& domain() const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;

        OPENSOLID_CORE_EXPORT Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        OPENSOLID_CORE_EXPORT Geometry reversed() const;
        
        template <class ArgumentType>
        FunctionResult<ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_CORE_EXPORT static Geometry Line(const VectorXd& start, const VectorXd& end);
        
        OPENSOLID_CORE_EXPORT static Geometry Arc(double radius, const Interval& angle);
        
        OPENSOLID_CORE_EXPORT static Geometry Arc(
            const Vector2d& center,
            const Vector2d& start,
            const Vector2d& end,
            bool counterclockwise
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Arc(
            const Axis3d& axis,
            const Vector3d& start,
            const Vector3d& end
        );
        
        OPENSOLID_CORE_EXPORT static Geometry Circle(double radius);
        
        OPENSOLID_CORE_EXPORT static Geometry Helix(
            double radius,
            double pitch,
            const Interval& angle
        );
    };
    
    template <>
    class Conversion<Geometry, double>
    {
    public:
        OPENSOLID_CORE_EXPORT double operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, Vector2d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, Vector3d>
    {
    public:
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Geometry& argument) const;
    };
    
    template <>
    class Conversion<Geometry, VectorXd>
    {
    public:
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Geometry& argument) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Domain/Domain.hpp>

namespace OpenSolid
{   
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Geometry::operator()(const ArgumentType& argument) const {
        return function()(argument);
    }
}

#endif
