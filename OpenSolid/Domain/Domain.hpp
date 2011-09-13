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

#include <OpenSolid/config.hpp>
#include <OpenSolid/declarations.hpp>
#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    template <>
    struct Bounds<Geometry>
    {
        typedef VectorXI Type;

        OPENSOLID_CORE_EXPORT VectorXI operator()(const Geometry& geometry) const;
    };
    
    class Domain : public Convertible<Domain>, public Transformable<Domain>
    {
    private:
        Set<Geometry> _boundaries;
    public:
        OPENSOLID_CORE_EXPORT Domain();
        OPENSOLID_CORE_EXPORT Domain(const Set<Geometry>& boundaries);
        OPENSOLID_CORE_EXPORT Domain(const Interval& bounds);

        template <class BoundsType>
        Domain(const EigenBase<BoundsType>& bounds);
        
        OPENSOLID_CORE_EXPORT const Set<Geometry>& boundaries() const;
        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;

        OPENSOLID_CORE_EXPORT Domain transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
    };
    
    template <>
    class Conversion<Domain, Interval>
    {
    public:
        OPENSOLID_CORE_EXPORT Interval operator()(const Domain& argument) const;
    };

    OPENSOLID_CORE_EXPORT Set<Geometry> rectangularBoundaries(const VectorXI& bounds);
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class BoundsType>
    Domain::Domain(const EigenBase<BoundsType>& bounds) :
        _boundaries(rectangularBoundaries(bounds)) {}
}

#endif
