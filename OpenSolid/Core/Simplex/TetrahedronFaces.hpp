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

#include <OpenSolid/Core/Simplex/TetrahedronFaces.definitions.hpp>

#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    namespace detail
    {
        inline
        TetrahedronFaces::TetrahedronFaces(const Tetrahedron3d& tetrahedron) :
            _tetrahedron(tetrahedron) {
        }

        inline
        const Tetrahedron3d&
        TetrahedronFaces::tetrahedron() const {
            return _tetrahedron;
        }

        inline
        IndexIterator<TetrahedronFaces>
        TetrahedronFaces::begin() const {
            return IndexIterator<TetrahedronFaces>::Begin(this);
        }

        inline
        IndexIterator<TetrahedronFaces>
        TetrahedronFaces::end() const {
            return IndexIterator<TetrahedronFaces>::End(this);
        }

        inline
        bool
        TetrahedronFaces::isEmpty() const {
            return false;
        }

        inline
        std::int64_t
        TetrahedronFaces::size() const {
            return 4;
        }

        inline
        Triangle3d
        TetrahedronFaces::operator[](std::int64_t index) const {
            return tetrahedron().face(index);
        }
    }
}
