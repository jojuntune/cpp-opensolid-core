/************************************************************************************
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Simplex/TetrahedronFaces.declarations.hpp>

#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    template <>
    struct ItemType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    template <>
    struct ItemReferenceType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    namespace detail
    {
        class TetrahedronFaces :
            public LazyCollection<TetrahedronFaces>
        {
        private:
            Tetrahedron3d _tetrahedron;
        public:
            TetrahedronFaces(const Tetrahedron3d& tetrahedron);

            const Tetrahedron3d&
            tetrahedron() const;

            IndexIterator<TetrahedronFaces>
            begin() const;

            IndexIterator<TetrahedronFaces>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Triangle<3>
            operator[](std::int64_t index) const;
        };
    }
}
