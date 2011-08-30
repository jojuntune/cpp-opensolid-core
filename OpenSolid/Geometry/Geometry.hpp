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

#include <functional>

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
        
        Set<Geometry> boundaries() const;

        Geometry reversed() const;
        
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
    
    OPENSOLID_CORE_EXPORT Geometry operator*(const Geometry& geometry, const DatumXd& datum);
    OPENSOLID_CORE_EXPORT Geometry operator/(const Geometry& geometry, const DatumXd& datum);
}

namespace std
{
    template <>
    struct hash<OpenSolid::Geometry> : public unary_function<OpenSolid::Geometry, size_t>
    {
        size_t operator()(const OpenSolid::Geometry& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Geometry> :
        public binary_function<OpenSolid::Geometry, OpenSolid::Geometry, bool>
    {
        bool operator()(
            const OpenSolid::Geometry& first_argument,
            const OpenSolid::Geometry& second_argument
        ) const;
    };
}

namespace boost
{
    template <>
    struct hash<OpenSolid::Geometry> : public std::hash<OpenSolid::Geometry>
    {
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
    
    inline Set<Geometry> Geometry::boundaries() const {
        Set<Geometry> results;
        domain().boundaries().transform(
            [this] (const Geometry& domain_boundary) {
                return Geometry(
                    this->function()(domain_boundary.function()),
                    domain_boundary.domain()
                );
            },
            results.inserter()
        );
        return results;
    }

    inline Geometry Geometry::reversed() const {
        assert(parameters() == 1);
        Function reversed_parameter = domain().lower() + domain().upper() - Parameter();
        return Geometry(function()(reversed_parameter), domain());
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
    inline size_t hash<OpenSolid::Geometry>::operator()(const OpenSolid::Geometry& argument) const {
        size_t result = 0;
        boost::hash_combine(result, hash<OpenSolid::Function>()(argument.function()));
        boost::hash_combine(result, hash<OpenSolid::Domain>()(argument.domain()));
        return result;
    }

    inline bool equal_to<OpenSolid::Geometry>::operator()(
        const OpenSolid::Geometry& first_argument,
        const OpenSolid::Geometry& second_argument
    ) const {
        return equal_to<OpenSolid::Function>()(
            first_argument.function(),
            second_argument.function()
        ) && equal_to<OpenSolid::Domain>()(
            first_argument.domain(),
            second_argument.domain()
        );
    }
}

#endif
