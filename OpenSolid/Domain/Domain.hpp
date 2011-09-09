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
 
#include <functional>

#include <boost/functional/hash.hpp>

#include <OpenSolid/Common/config.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    class Geometry;

    template <>
    struct Bounds<Geometry>
    {
        typedef VectorXI Type;

        VectorXI operator()(const Geometry& geometry) const;
    };
    
    class Domain : public Transformable<Domain>
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

        const VectorXI& bounds() const;
        Interval value() const;
        double lower() const;
        double upper() const;
        
        bool operator==(const Domain& other) const;

        OPENSOLID_CORE_EXPORT Domain transformed(const MatrixXd& matrix, const VectorXd& vector) const;
    };
}

namespace std
{
    template <>
    struct hash<OpenSolid::Domain> : public unary_function<OpenSolid::Domain, size_t>
    {
        size_t operator()(const OpenSolid::Domain& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Domain> :
        public binary_function<OpenSolid::Domain, OpenSolid::Domain, bool>
    {
        bool operator()(
            const OpenSolid::Domain& first_argument,
            const OpenSolid::Domain& second_argument
        ) const;
    };
}

namespace boost
{
    template <>
    struct hash<OpenSolid::Domain> : public std::hash<OpenSolid::Domain>
    {
    };
}

////////// Implementation //////////

#include <boost/functional/hash.hpp>

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
    
    inline const VectorXI& Domain::bounds() const {
        assert(!empty());
        return boundaries().bounds();
    }

    inline Interval Domain::value() const {
        assert(!empty());
        assert(dimensions() == 1);
        return bounds().value();
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
}

namespace std
{
    inline size_t hash<OpenSolid::Domain>::operator()(const OpenSolid::Domain& argument) const {
        return hash<OpenSolid::Set<OpenSolid::Geometry>>()(argument.boundaries());
    }

    inline bool equal_to<OpenSolid::Domain>::operator()(
        const OpenSolid::Domain& first_argument,
        const OpenSolid::Domain& second_argument
    ) const {
        return equal_to<OpenSolid::Set<OpenSolid::Geometry>>()(
            first_argument.boundaries(),
            second_argument.boundaries()
        );
    }
}

#endif
