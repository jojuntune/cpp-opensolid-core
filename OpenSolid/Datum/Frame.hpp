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
        typedef Eigen::Matrix<Double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<Double, dimensions_, dimensions_> Matrix;
        
        Frame();
        explicit Frame(int size);
        
        explicit Frame(const Vector& origin);
        
        template <class DerivedType>
        Frame(const Vector& origin, const EigenBase<DerivedType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Frame(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Frame<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Frame<2> Frame2D;
    typedef Frame<3> Frame3D;
    typedef Frame<4> Frame4D;
    typedef Frame<Dynamic> FrameXD;
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
    inline Frame<dimensions_>::Frame(const Vector& origin) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        this->_origin = origin;
        this->_vectors = Matrix::Identity(origin.size(), origin.size());
        this->_normalized = true;
    }
    
    template <int dimensions_> template <class DerivedType>
    inline Frame<dimensions_>::Frame(
        const Vector& origin,
        const EigenBase<DerivedType>& vectors
    ) {initialize(origin, vectors, true);}

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
