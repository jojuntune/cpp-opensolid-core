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

#ifndef OPENSOLID__GEOMETRYDOMAIN_HPP
#define OPENSOLID__GEOMETRYDOMAIN_HPP

#include <opensolid/common/Bounds.hpp>
#include <opensolid/function/Function.hpp>
#include <opensolid/collection/Set.hpp>

namespace opensolid
{
    class Domain;
    class Geometry;
    
    template <>
    struct Bounds<Domain>
    {
        typedef VectorXI Type;
        
        static VectorXI bounds(const Domain& domain);
    };
    
    template <>
    struct Bounds<Geometry>
    {
        typedef VectorXI Type;
        
        static FunctionResult<VectorXI> bounds(const Geometry& geometry);
    };
    
    class Domain
    {
    private:
        Set<Geometry> _boundaries;
        
        OPENSOLID_EXPORT static Set<Geometry> rectangularBoundaries(const VectorXI& bounds);
    public:
        Domain();
        Domain(const Set<Geometry>& geometry);
        Domain(const Interval& bounds);
        
        template <class DerivedType>
        Domain(const EigenBase<DerivedType>& bounds);
        
        const Set<Geometry>& boundaries() const;
        bool empty() const;
        VectorXI bounds() const;
        int dimensions() const;
        
        OPENSOLID_EXPORT Domain concatenate(const Domain& other) const;
    };
    
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
        
        FunctionResult<VectorXI> bounds() const;
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
    
    OPENSOLID_EXPORT Geometry cos(const Geometry& argument);
    OPENSOLID_EXPORT Geometry sin(const Geometry& argument);
    OPENSOLID_EXPORT Geometry sqrt(const Geometry& argument);
}

////////// Implementation //////////

namespace opensolid
{
    inline VectorXI Bounds<Domain>::bounds(const Domain& domain) {return domain.bounds();}
    
    inline FunctionResult<VectorXI> Bounds<Geometry>::bounds(const Geometry& geometry) {
        return geometry.bounds();
    }
    
    inline Domain::Domain() : _boundaries() {}
    
    namespace
    {
        struct BoundaryChecker
        {
            const Domain& _domain;
            
            inline BoundaryChecker(const Domain& domain) : _domain(domain) {}
            
            inline void operator()(const Geometry& boundary) {
                assert(boundary.dimensions() == _domain.dimensions());
                assert(boundary.parameters() == _domain.dimensions() - 1);
            }
        };
    }
    
    inline Domain::Domain(const Set<Geometry>& boundaries) : _boundaries(boundaries) {
        boundaries.visit(BoundaryChecker(*this));
    }
    
    inline Domain::Domain(const Interval& bounds) {
        _boundaries = rectangularBoundaries(VectorXI::Constant(1, bounds));
    }
    
    template <class DerivedType>
    inline Domain::Domain(const EigenBase<DerivedType>& bounds) {
        _boundaries = rectangularBoundaries(bounds);
    }
    
    inline const Set<Geometry>& Domain::boundaries() const {return _boundaries;}
    
    inline bool Domain::empty() const {return boundaries().empty();}
    
    inline VectorXI Domain::bounds() const {
        if (boundaries().empty()) {
            return VectorXI();
        } else {
            return boundaries().bounds();
        }
    }
    
    inline int Domain::dimensions() const {return bounds().size();}
    
    inline Geometry::Geometry() : _function(), _domain() {}
    
    inline Geometry::Geometry(const Function& function, const Domain& domain) :
        _function(function), _domain(domain) {
        assert(domain.dimensions() == function.parameters());
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
    
    inline FunctionResult<VectorXI> Geometry::bounds() const {return function()(domain().bounds());}
    
    inline Set<Geometry> Geometry::boundaries() const {
        return domain().boundaries().mapped<Geometry>(function());
    }
    
    template <class ArgumentType>
    inline FunctionResult<ArgumentType> Geometry::operator()(const ArgumentType& argument) const {
        return function()(argument);
    }
}

#endif
