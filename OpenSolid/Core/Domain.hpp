/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
 *  ian.e.mackenzie@gmail.com                                                        *
 *                                                                                   *
 *  This library is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU Lesser General Public                       *
 *  License as published by the Free Software Foundation; either                     *
 *  version 2.1 of the License, or (at your option) any later version.               *
 *                                                                                   *
 *  This library is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 *  Lesser General Public License for more details.                                  *
 *                                                                                   *
 *  You should have received a copy of the GNU Lesser General Public                 *
 *  License along with this library; if not, write to the Free Software              *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 *                                                                                   *
 *************************************************************************************/
 
#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/DomainImplementation.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>

#include <OpenSolid/Core/Domain/DomainConstructors.hpp>

#include <OpenSolid/Core/Domain/declarations.hpp>

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
        OPENSOLID_CORE_EXPORT Domain(Interval interval);
        OPENSOLID_CORE_EXPORT Domain(Interval uInterval, Interval vInterval);
        OPENSOLID_CORE_EXPORT Domain(Interval uInterval, Interval vInterval, Interval wInterval);
        OPENSOLID_CORE_EXPORT Domain(const VectorXI& bounds);
        OPENSOLID_CORE_EXPORT Domain(const Triangle2d& triangle);
        OPENSOLID_CORE_EXPORT Domain(const Tetrahedron3d& tetrahedron);

        OPENSOLID_CORE_EXPORT const DomainImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;
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

        OPENSOLID_CORE_EXPORT VectorXI operator()(const Domain& domain) const;
    };

    template <>
    struct Conversion<Domain, Interval>
    {
        OPENSOLID_CORE_EXPORT Interval operator()(const Domain& domain) const;
    };
}

#include <OpenSolid/Core/Geometry.hpp>
