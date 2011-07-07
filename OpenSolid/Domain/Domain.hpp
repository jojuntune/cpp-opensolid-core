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
 
#include <boost/functional/hash.hpp>

#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    class Geometry;
    
    class Domain
    {
    private:
        Set<Geometry, VectorXI> _boundaries;
        
        OPENSOLID_CORE_EXPORT static Set<Geometry, VectorXI> rectangularBoundaries(
            const VectorXI& bounds
        );
    public:
        typedef VectorXI Bounds;
        
        Domain();
        Domain(const Set<Geometry, VectorXI>& geometry);
        Domain(const Interval& bounds);
        
        template <class DerivedType>
        Domain(const EigenBase<DerivedType>& bounds);
        
        const Set<Geometry, VectorXI>& boundaries() const;
        bool empty() const;
        VectorXI bounds() const;
        std::size_t hashValue() const;
        int dimensions() const;
        
        bool operator==(const Domain& other) const;
        
        OPENSOLID_CORE_EXPORT Domain concatenate(const Domain& other) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    inline Domain::Domain() : _boundaries() {}
    
    inline Domain::Domain(const Set<Geometry, VectorXI>& boundaries) : _boundaries(boundaries) {}
    
    inline Domain::Domain(const Interval& bounds) {
        _boundaries = rectangularBoundaries(VectorXI::Constant(1, bounds));
    }
    
    template <class DerivedType>
    inline Domain::Domain(const EigenBase<DerivedType>& bounds) {
        _boundaries = rectangularBoundaries(bounds);
    }
    
    inline const Set<Geometry, VectorXI>& Domain::boundaries() const {return _boundaries;}
    
    inline bool Domain::empty() const {return boundaries().empty();}
    
    inline VectorXI Domain::bounds() const {
        if (boundaries().empty()) {
            return VectorXI();
        } else {
            return boundaries().bounds();
        }
    }
    
    inline std::size_t Domain::hashValue() const {return boundaries().hashValue();}
    
    inline int Domain::dimensions() const {return bounds().size();}
        
    inline bool Domain::operator==(const Domain& other) const {
        return boundaries() == other.boundaries();
    }
}

#endif
