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

#ifndef OPENSOLID__FRAME_HPP
#define OPENSOLID__FRAME_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    class Frame : public Datum<dimensions_, dimensions_>
    {
    public:
        OPENSOLID_CORE_EXPORT Frame();

        OPENSOLID_CORE_EXPORT explicit Frame(int size);
        
        OPENSOLID_CORE_EXPORT explicit Frame(const Matrix<double, dimensions_, 1>& origin);
        
        template <class VectorsType>
        Frame(const Matrix<double, dimensions_, 1>& origin, const EigenBase<VectorsType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Frame(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Frame<1> Frame1d;
    typedef Frame<2> Frame2d;
    typedef Frame<3> Frame3d;
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_> template <class VectorsType>
    Frame<dimensions_>::Frame(
        const Matrix<double, dimensions_, 1>& origin,
        const EigenBase<VectorsType>& vectors
    ) : Datum<dimensions_, dimensions_>(origin, orthonormalBasis(vectors.derived())) {}
        
    template <int dimensions_>template <int other_dimensions_, int other_axes_>
    Frame<dimensions_>::Frame(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, dimensions_>(other.origin(), orthonormalBasis(other.basis())) {}
}

#endif
