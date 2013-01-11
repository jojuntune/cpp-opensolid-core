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
 
#pragma once

#include <OpenSolid/config.hpp>

#include "Domain/declarations.hpp"
#include "Domain/DomainConstructors.hpp"
#include "Domain/DomainImplementation.hpp"

#include <OpenSolid/Utils/Conversion.hpp>
#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/Simplex.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    class Domain :
        public DomainConstructors,
        public Convertible<Domain>,
        public Transformable<Domain>
    {
    private:
        boost::intrusive_ptr<const DomainImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Domain();
        OPENSOLID_CORE_EXPORT Domain(const DomainImplementation* implementation);

        OPENSOLID_CORE_EXPORT Domain(const Set<Geometry>& boundaries);
        OPENSOLID_CORE_EXPORT Domain(const Interval& interval);
        OPENSOLID_CORE_EXPORT Domain(const Interval& u, const Interval& v);
        OPENSOLID_CORE_EXPORT Domain(const Interval& u, const Interval& v, const Interval& w);
        OPENSOLID_CORE_EXPORT Domain(const VectorXI& bounds);
        OPENSOLID_CORE_EXPORT Domain(const SimplexXd& simplex);

        template <class DerivedType>
        Domain(const EigenBase<DerivedType>& bounds);

        template <int dimensions_, int size_>
        Domain(const Simplex<dimensions_, size_>& simplex);

        OPENSOLID_CORE_EXPORT const DomainImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;

        OPENSOLID_CORE_EXPORT Domain transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Domain>
    {
        typedef VectorXI Type;

        OPENSOLID_CORE_EXPORT VectorXI operator()(const Domain& argument) const;
    };

    template <>
    struct Conversion<Domain, Interval>
    {
        OPENSOLID_CORE_EXPORT Interval operator()(const Domain& argument) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    template <class DerivedType>
    Domain::Domain(const EigenBase<DerivedType>& bounds) {
        *this = Domain(VectorXI(bounds));
    }

    template <int dimensions_, int size_>
    Domain::Domain(const Simplex<dimensions_, size_>& simplex) {
        *this = Domain(SimplexXd(simplex));
    }
}
