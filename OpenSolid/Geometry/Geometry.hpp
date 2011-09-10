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

#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    class Geometry : public Transformable<Geometry>
    {
    private:
        Function _function;
        Domain _domain;
    public:
        typedef VectorXI Bounds;
        
        Geometry();
        Geometry(const Function& function, const Domain& domain);
        Geometry(double value);
        
        template <class DerivedType>
        Geometry(const EigenBase<DerivedType>& value);
        
        const Function& function() const;
        const Domain& domain() const;
        
        const VectorXd& vector() const;
        double value() const;
        
        int parameters() const;
        int dimensions() const;
        
        VectorXI bounds() const;
        
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
}

////////// Implementation //////////

#include <OpenSolid/Domain/Domain.hpp>

namespace OpenSolid
{
    inline Geometry::Geometry() : _function(), _domain() {}
    
    inline Geometry::Geometry(const Function& function, const Domain& domain) :
        _function(function), _domain(domain) {
        assert(function.isA<ConstantFunction>() || domain.dimensions() == function.parameters());
    }
    
    inline Geometry::Geometry(double value) : _function(value), _domain() {}
    
    template <class DerivedType>
    inline Geometry::Geometry(const EigenBase<DerivedType>& value) :
        _function(value), _domain() {}
    
    inline const Function& Geometry::function() const {return _function;}
    
    inline const Domain& Geometry::domain() const {return _domain;}
    
    inline const VectorXd& Geometry::vector() const {
        assert(function().isA<ConstantFunction>());
        return function().as<ConstantFunction>().vector();
    }

    inline double Geometry::value() const {
        assert(function().isA<ConstantFunction>());
        assert(dimensions() == 1);
        return vector().value();
    }
    
    inline int Geometry::parameters() const {return function().parameters();}
    
    inline int Geometry::dimensions() const {return function().dimensions();}
    
    inline VectorXI Geometry::bounds() const {
        if (function().isA<ConstantFunction>()) {
            return function().as<ConstantFunction>().vector().cast<Interval>();
        } else {
            return function()(domain().bounds());
        }
    }
    
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Geometry::operator()(const ArgumentType& argument) const {
        return function()(argument);
    }

    inline VectorXI Bounds<Geometry>::operator()(const Geometry& argument) const {
        return argument.bounds();
    }
}

namespace std
{
}

#endif
