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
 
#ifndef OPENSOLID__DOMAIN_HPP
#define OPENSOLID__DOMAIN_HPP

#include <OpenSolid/Collection/Set.hpp>
#include <OpenSolid/Value/Matrix.hpp>
#include <OpenSolid/Function/Function.hpp>
#include "GeometryDomain.hpp"

namespace OpenSolid
{   
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
        Interval interval() const;
        int dimensions() const;
        
        OPENSOLID_EXPORT Domain concatenate(const Domain& other) const;
    };
}

////////// Implementation //////////

#include "Geometry.hpp"

namespace OpenSolid
{   
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
    
    inline Interval Domain::interval() const {
        assert(dimensions() == 1);
        if (boundaries().empty()) {
            return Interval::Empty();
        } else {
            return boundaries().bounds().scalar();
        }
    }
    
    inline int Domain::dimensions() const {return bounds().size();}
    
    inline VectorXI Bounds<Domain>::bounds(const Domain& domain) {return domain.bounds();}
}

#endif
