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

#include <boost/functional/hash.hpp>

#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Domain/Domain.hpp>

namespace OpenSolid
{   
    class Geometry
    {
    private:
        Function _function;
        Domain _domain;
    public:
        Geometry();
        Geometry(const Function& function, const Domain& domain);
        Geometry(double value);
        
        template <class DerivedType>
        Geometry(const EigenBase<DerivedType>& value);
        
        const Function& function() const;
        const Domain& domain() const;
        
        const VectorXd& value() const;
        
        int parameters() const;
        int dimensions() const;
        
        VectorXI bounds() const;
        Set<Geometry> boundaries() const;
        
        template <class ArgumentType>
        FunctionResult<ArgumentType> operator()(const ArgumentType& argument) const;
        
        OPENSOLID_EXPORT Geometry derivative(int parameter_index = 0) const;
        OPENSOLID_EXPORT Geometry norm() const;
        OPENSOLID_EXPORT Geometry normalized() const;
        OPENSOLID_EXPORT Geometry squaredNorm() const;
        OPENSOLID_EXPORT Geometry component(int index) const;
        OPENSOLID_EXPORT Geometry components(int index, int num) const;
        OPENSOLID_EXPORT Geometry concatenate(const Geometry& other) const;
        OPENSOLID_EXPORT Geometry dot(const Geometry& other) const;
        OPENSOLID_EXPORT Geometry cross(const Geometry& other) const;
        OPENSOLID_EXPORT Geometry tangent() const;
        OPENSOLID_EXPORT Geometry curvature() const;
        OPENSOLID_EXPORT Geometry normal() const;
        OPENSOLID_EXPORT Geometry binormal() const;
        
        bool operator==(const Geometry& other) const;
        
        OPENSOLID_EXPORT static Geometry Line(const VectorXd& start, const VectorXd& end);
        
        OPENSOLID_EXPORT static Geometry Arc(double radius, const Interval& angle);
        
        OPENSOLID_EXPORT static Geometry Arc(
            const Vector2d& center,
            const Vector2d& start,
            const Vector2d& end,
            bool counterclockwise
        );
        
        OPENSOLID_EXPORT static Geometry Arc(
            const Axis3d& axis,
            const Vector3d& start,
            const Vector3d& end
        );
        
        OPENSOLID_EXPORT static Geometry Circle(double radius);
        
        OPENSOLID_EXPORT static Geometry Helix(double radius, double pitch, const Interval& angle);
    };

    OPENSOLID_EXPORT Geometry operator-(const Geometry& argument);
    
    OPENSOLID_EXPORT Geometry operator+(
        const Geometry& first_argument,
        const Geometry& second_argument
    );
    
    OPENSOLID_EXPORT Geometry operator-(
        const Geometry& first_argument,
        const Geometry& second_argument
    );
    
    OPENSOLID_EXPORT Geometry operator*(
        const Geometry& first_argument,
        const Geometry& second_argument
    );
    
    OPENSOLID_EXPORT Geometry operator/(
        const Geometry& first_argument,
        const Geometry& second_argument
    );
    
    OPENSOLID_EXPORT Geometry operator*(const Geometry& geometry, const DatumXd& datum);
    OPENSOLID_EXPORT Geometry operator/(const Geometry& geometry, const DatumXd& datum);
    
    OPENSOLID_EXPORT Geometry cos(const Geometry& argument);
    OPENSOLID_EXPORT Geometry sin(const Geometry& argument);
    OPENSOLID_EXPORT Geometry sqrt(const Geometry& argument);
    
    std::size_t hash_value(const Geometry& geometry);
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Geometry::Geometry() : _function(), _domain() {}
    
    inline Geometry::Geometry(const Function& function, const Domain& domain) :
        _function(function), _domain(domain) {
        assert(function.isA<ConstantFunction>() || domain.dimensions() == function.parameters());
    }
    
    inline Geometry::Geometry(double value) : _function(value), _domain() {}
    
    template <class DerivedType>
    inline Geometry::Geometry(const EigenBase<DerivedType>& value) : _function(value), _domain() {}
    
    inline const Function& Geometry::function() const {return _function;}
    
    inline const Domain& Geometry::domain() const {return _domain;}
    
    inline const VectorXd& Geometry::value() const {
        assert(function().isA<ConstantFunction>());
        return function().as<ConstantFunction>().value();
    }
    
    inline int Geometry::parameters() const {return function().parameters();}
    
    inline int Geometry::dimensions() const {return function().dimensions();}
    
    inline VectorXI Geometry::bounds() const {return function()(domain().bounds());}
    
    inline Set<Geometry> Geometry::boundaries() const {
        Set<Geometry> results;
        for (auto i = domain().boundaries().begin(); i != domain().boundaries().end(); ++i) {
            results.insert(function()(*i));
        }
        return results;
    }
    
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Geometry::operator()(const ArgumentType& argument) const {
        return function()(argument);
    }
        
    inline bool Geometry::operator==(const Geometry& other) const {
        return function() == other.function() && domain() == other.domain();
    }
    
    inline VectorXI Bounds<Geometry>::bounds(const Geometry& geometry) {
        return geometry.bounds();
    }
    
    inline std::size_t hash_value(const Geometry& geometry) {
        std::size_t result = 0;
        boost::hash_combine(result, geometry.function());
        boost::hash_combine(result, geometry.domain());
        return result;
    }
}

#endif
