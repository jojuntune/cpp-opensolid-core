/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/Simplex/TetrahedronEdges.definitions.hpp>

#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>

namespace opensolid
{
    namespace detail
    {
        inline
        TetrahedronEdges::TetrahedronEdges(const Tetrahedron3d& tetrahedron) :
            _tetrahedron(tetrahedron) {
        }

        inline
        const Tetrahedron3d&
        TetrahedronEdges::tetrahedron() const {
            return _tetrahedron;
        }

        inline
        IndexIterator<TetrahedronEdges>
        TetrahedronEdges::begin() const {
            return IndexIterator<TetrahedronEdges>::begin(this);
        }

        inline
        IndexIterator<TetrahedronEdges>
        TetrahedronEdges::end() const {
            return IndexIterator<TetrahedronEdges>::end(this);
        }

        inline
        bool
        TetrahedronEdges::isEmpty() const {
            return false;
        }

        inline
        std::size_t
        TetrahedronEdges::size() const {
            return 6;
        }

        inline
        LineSegment3d
        TetrahedronEdges::operator[](std::size_t index) const {
            return tetrahedron().edge(int(index));
        }
    }
}
