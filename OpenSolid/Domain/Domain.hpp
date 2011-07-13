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

#include <OpenSolid/Common/config.hpp>
#include <OpenSolid/Common/Traits.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Geometry/Traits.hpp>

namespace OpenSolid
{
    class Geometry;
    
    class Domain
    {
    private:
        Set<Geometry> _boundaries;
        
        OPENSOLID_CORE_EXPORT static Set<Geometry> rectangularBoundaries(const VectorXI& bounds);
    public:
        Domain();
        Domain(const Set<Geometry>& boundaries);
        Domain(const Interval& bounds);
        
        template <class DerivedType>
        Domain(const EigenBase<DerivedType>& bounds);
        
        const Set<Geometry>& boundaries() const;
        bool empty() const;
        int dimensions() const;

        VectorXI bounds() const;
        Interval value() const;
        double lower() const;
        double upper() const;
        
        bool operator==(const Domain& other) const;
        
        OPENSOLID_CORE_EXPORT Domain concatenate(const Domain& other) const;
    };

    template <>
    struct Traits<Domain>
    {
        typedef VectorXI Bounds;

        VectorXI bounds(const Domain& argument);
        std::size_t hash(const Domain& argument);
        bool equal(const Domain& first_argument, const Domain& second_argument);
    };
}

////////// Implementation //////////

#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    inline Domain::Domain() : _boundaries() {}
    
    inline Domain::Domain(const Set<Geometry>& boundaries) : _boundaries(boundaries) {}
    
    inline Domain::Domain(const Interval& bounds) {
        _boundaries = rectangularBoundaries(VectorXI::Constant(1, bounds));
    }
    
    template <class DerivedType>
    inline Domain::Domain(const EigenBase<DerivedType>& bounds) {
        _boundaries = rectangularBoundaries(bounds);
    }
    
    inline const Set<Geometry>& Domain::boundaries() const {return _boundaries;}
    
    inline bool Domain::empty() const {return boundaries().empty();}
    
    inline int Domain::dimensions() const {return bounds().size();}
    
    inline VectorXI Domain::bounds() const {
        if (boundaries().empty()) {
            return VectorXI();
        } else {
            return boundaries().bounds();
        }
    }

    inline Interval Domain::value() const {
        if (boundaries().empty()) {
            return Interval::Empty();
        } else {
            return bounds().value();
        }
    }

    inline double Domain::lower() const {
        assert(!empty());
        assert(dimensions() == 1);
        return value().lower();
    }

    inline double Domain::upper() const {
        assert(!empty());
        assert(dimensions() == 1);
        return value().upper();
    }
    
    inline VectorXI Traits<Domain>::bounds(const Domain& argument) {return argument.bounds();}

    inline std::size_t Traits<Domain>::hash(const Domain& argument) {
        return Traits<Set<Geometry>>::hash(argument.boundaries());
    }

    inline bool Traits<Domain>::equal(const Domain& first_argument, const Domain& second_argument) {
        return Traits<Set<Geometry>>::equal(
            first_argument.boundaries(),
            second_argument.boundaries()
        );
    }
}

#endif
