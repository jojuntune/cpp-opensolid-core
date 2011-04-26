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

#include "Datum.hpp"

namespace OpenSolid
{
    template <int dimensions_>
    class Frame : public Datum<dimensions_, dimensions_>
    {
    public:
        typedef Matrix<double, dimensions_, 1> VectorType;
        typedef Matrix<double, dimensions_, dimensions_> MatrixType;
        
        Frame();
        explicit Frame(int size);
        
        explicit Frame(const VectorType& origin);
        
        template <class DerivedType>
        Frame(const VectorType& origin, const EigenBase<DerivedType>& vectors);
        
        Frame(const VectorType& origin, const List<VectorType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Frame(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Frame<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Frame<2> Frame2d;
    typedef Frame<3> Frame3d;
    typedef Frame<4> Frame4d;
    typedef Frame<Dynamic> FrameXd;
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_>
    inline Frame<dimensions_>::Frame() {
        if (dimensions_ != Dynamic) {
            this->_origin.setZero();
            this->_vectors.setIdentity();
            this->_normalized = true;
        }
    }
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(int size) {
        assert(size == dimensions_ || dimensions_ == Dynamic);
        this->_origin = VectorType::Zero(size);
        this->_vectors = MatrixType::Identity(size, size);
        this->_normalized = true;
    }
        
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        this->_origin = origin;
        this->_vectors = MatrixType::Identity(origin.size(), origin.size());
        this->_normalized = true;
    }
    
    template <int dimensions_> template <class DerivedType>
    inline Frame<dimensions_>::Frame(
        const VectorType& origin,
        const EigenBase<DerivedType>& vectors
    ) {initialize(origin, vectors, true);}
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const VectorType& origin, const List<VectorType>& vectors) {
        initialize(origin, vectors.matrix(), true);
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Frame<dimensions_>::Frame(const Datum<other_dimensions_, other_axes_>& other) {
        assert(other._normalized);
        initialize(other);
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Frame<dimensions_>& Frame<dimensions_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(other._normalized);
        initialize(other);
        return *this;
    }
}

#endif
