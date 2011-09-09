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
        Frame();

        explicit Frame(int size);
        
        explicit Frame(const Matrix<double, dimensions_, 1>& origin);
        
        template <class VectorsType>
        Frame(const Matrix<double, dimensions_, 1>& origin, const EigenBase<VectorsType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Frame(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Frame<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Frame<2> Frame2d;
    typedef Frame<3> Frame3d;
    typedef Frame<Dynamic> FrameXd;
}

namespace std
{
    template <int dimensions_>
    struct hash<OpenSolid::Frame<dimensions_>> :
        public unary_function<OpenSolid::Frame<dimensions_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Frame<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Frame<dimensions_>> :
        public binary_function<OpenSolid::Frame<dimensions_>, OpenSolid::Frame<dimensions_>, bool>
    {
        bool operator()(
            const OpenSolid::Frame<dimensions_>& first_argument,
            const OpenSolid::Frame<dimensions_>& second_argument
        ) const;
    };
}

namespace boost
{
    template <int dimensions_>
    struct hash<OpenSolid::Frame<dimensions_>> : public std::hash<OpenSolid::Frame<dimensions_>>
    {
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    namespace
    {
        template <int dimensions_>
        inline Matrix<double, dimensions_, 1> defaultOrigin() {
            Matrix<double, dimensions_, 1> result;
            if (dimensions_ != Dynamic) {result.setZero();}
            return result;
        }

        template <int dimensions_>
        inline Matrix<double, dimensions_, dimensions_> defaultBasis() {
            Matrix<double, dimensions_, dimensions_> result;
            if (dimensions_ != Dynamic) {result.setIdentity();}
            return result;
        }
    }

    template <int dimensions_>
    inline Frame<dimensions_>::Frame() :
        Datum<dimensions_, dimensions_>(
            defaultOrigin<dimensions_>(),
            defaultBasis<dimensions_>()
        ) {}
    
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(int size) :
        Datum<dimensions_, dimensions_>(
            Matrix<double, dimensions_, 1>::Zero(size),
            Matrix<double, dimensions_, dimensions_>::Identity(size, size)
        ) {assertCompatible<dimensions_>(size);}
        
    template <int dimensions_>
    inline Frame<dimensions_>::Frame(const Matrix<double, dimensions_, 1>& origin) :
        Datum<dimensions_, dimensions_>(
            origin,
            Matrix<double, dimensions_, dimensions_>::Identity(origin.size(), origin.size())
        ) {assertCompatible<dimensions_>(origin.size());}
    
    template <int dimensions_> template <class VectorsType>
    inline Frame<dimensions_>::Frame(
        const Matrix<double, dimensions_, 1>& origin,
        const EigenBase<VectorsType>& vectors
    ) : Datum<dimensions_, dimensions_>(
            origin,
            orthonormalBasis(vectors.derived()).leftCols(origin.size())
        ) {}

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Frame<dimensions_>::Frame(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, dimensions_>(other) {
        assertCompatible<other_dimensions_, other_axes_>();
        assert(other.dimensions() == other.axes());
        assert(other.basis().isUnitary());
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Frame<dimensions_>& Frame<dimensions_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assertCompatible<other_dimensions_, other_axes_>();
        assert(other.dimensions() == other.axes());
        assert(other.basis().isUnitary());
        Datum<dimensions_, dimensions_>::operator=(other);
        return *this;
    }
}

namespace std
{
    template <int dimensions_>
    inline size_t hash<OpenSolid::Frame<dimensions_>>::operator()(
        const OpenSolid::Frame<dimensions_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, dimensions_>>()(argument);}

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Frame<dimensions_>>::operator()(
        const OpenSolid::Frame<dimensions_>& first_argument,
        const OpenSolid::Frame<dimensions_>& second_argument
    ) const {
        return equal_to<OpenSolid::Datum<dimensions_, dimensions_>>()(
            first_argument,
            second_argument
        );
    }
}

#endif
