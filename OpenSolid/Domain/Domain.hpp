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
#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    class Geometry;
    class DomainImplementation;

    class Domain : public Convertible<Domain>, public Transformable<Domain>
    {
    private:
        boost::intrusive_ptr<const DomainImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Domain();
        OPENSOLID_CORE_EXPORT Domain(const DomainImplementation* implementation);
        OPENSOLID_CORE_EXPORT Domain(const Set<Geometry>& boundaries);
        OPENSOLID_CORE_EXPORT Domain(const Interval& interval);
        template <class DerivedType> Domain(const EigenBase<DerivedType>& bounds);

        const DomainImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
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
}

////////// Implementation //////////

#include <OpenSolid/Domain/DomainImplementation/IntervalDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/Vector2IDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/Vector3IDomain.hpp>
#include <OpenSolid/Domain/DomainImplementation/VectorXIDomain.hpp>

namespace OpenSolid
{
    template <class DerivedType>
    Domain::Domain(const EigenBase<DerivedType>& bounds) {
        if (bounds.size() == 1) {
            _implementation = new IntervalDomain(bounds.value());
            _type = &typeid(IntervalDomain);
        } else if (bounds.size() == 2) {
            _implementataion = new Vector2IDomain(bounds);
            _type = &typeid(Vector2IDomain);
        } else if (bounds.size() == 3) {
            _implementataion = new Vector3IDomain(bounds);
            _type = &typeid(Vector3IDomain);
        } else {
            _implementataion = new VectorXIDomain(bounds);
            _type = &typeid(VectorXIDomain);
        }
    }

    inline const DomainImplementation* Domain::implementation() const {
        assert(_implementation);
        return _implementation.get();
    }
}

#endif
