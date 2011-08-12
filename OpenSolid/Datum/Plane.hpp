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

#ifndef OPENSOLID__PLANE_HPP
#define OPENSOLID__PLANE_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    class Plane : public Datum<dimensions_, dimensions_ == Dynamic ? Dynamic : dimensions_ - 1>
    {
    public:
        static const int static_axes = dimensions_ == Dynamic ? Dynamic : dimensions_ - 1;
        typedef Eigen::Matrix<double, dimensions_, 1> Vector;
        typedef Eigen::Matrix<double, dimensions_, static_axes> Matrix;
    private:
        template <class DerivedType>
        void initialize(const Vector& origin, const EigenBase<DerivedType>& vectors);
        
        using Datum<dimensions_, static_axes>::initialize;
    public:
        Plane();
        
        template <class DerivedType>
        Plane(const Vector& origin, const EigenBase<DerivedType>& vectors);
        
        template <int other_dimensions_, int other_axes_>
        Plane(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Plane<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
    };
    
    typedef Plane<2> Plane2d;
    typedef Plane<3> Plane3d;
    typedef Plane<4> Plane4d;
    typedef Plane<Dynamic> PlaneXd;
}

namespace std
{
    template <int dimensions_>
    struct hash<OpenSolid::Plane<dimensions_>>
    {
        std::size_t operator()(const OpenSolid::Plane<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Plane<dimensions_>>
    {
        bool operator()(
            const OpenSolid::Plane<dimensions_>& first_argument,
            const OpenSolid::Plane<dimensions_>& second_argument
        ) const;
    };
}

namespace boost
{
    template <int dimensions_>
    struct hash<OpenSolid::Plane<dimensions_>> : public std::hash<OpenSolid::Plane<dimensions_>>
    {
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_> template <class DerivedType>
    inline void Plane<dimensions_>::initialize(
        const Vector& origin,
        const EigenBase<DerivedType>& vectors
    ) {
        assert(origin.size() == dimensions_ || dimensions_ == Dynamic);
        this->_origin = origin;
        assert(vectors.rows() == origin.size());
        assert(vectors.cols() == 1 || vectors.cols() == origin.size() - 1);
        if (vectors.cols() == 1) {
            this->_vectors = orthogonalBasis(vectors).rightCols(origin.size() - 1);
        } else {
            this->_vectors = orthogonalBasis(vectors).leftCols(origin.size() - 1);
        }
        this->_normalized = true;
    }
        
    template <int dimensions_>
    inline Plane<dimensions_>::Plane() {}
    
    template <int dimensions_> template <class DerivedType>
    inline Plane<dimensions_>::Plane(
        const Vector& origin,
        const EigenBase<DerivedType>& vectors
    ) {initialize(origin, vectors);}

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Plane<dimensions_>::Plane(const Datum<other_dimensions_, other_axes_>& other) {
        assert(other._normalized);
        initialize(other);
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Plane<dimensions_>& Plane<dimensions_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(other._normalized);
        initialize(other);
        return *this;
    }
}

namespace std
{
    template <int dimensions_>
    inline size_t hash<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& argument
    ) const {
        return hash<
            OpenSolid::Datum<dimensions_, dimensions_ == Dynamic ? Dynamic : dimensions_ - 1>
        >()(argument);
    }

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& first_argument,
        const OpenSolid::Plane<dimensions_>& second_argument
    ) const {
        return equal_to<
            OpenSolid::Datum<dimensions_, dimensions_ == Dynamic ? Dynamic : dimensions_ - 1>
        >()(first_argument, second_argument);
    }
}

#endif
