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
    class Plane : public Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>
    {
    private:
        static const int static_axes = (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1);
    public:
        Plane();

        template <class VectorsType>
        Plane(const Matrix<double, dimensions_, 1>& origin, const EigenBase<VectorsType>& vectors);

        Plane(const Vector3d& origin, const Vector3d& first_vector, const Vector3d& second_vector);
        
        template <int other_dimensions_, int other_axes_>
        Plane(const Datum<other_dimensions_, other_axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Plane<dimensions_>& operator=(const Datum<other_dimensions_, other_axes_>& other);

        static Plane<dimensions_> XY();
        static Plane<dimensions_> XZ();
        static Plane<dimensions_> YX();
        static Plane<dimensions_> YZ();
        static Plane<dimensions_> ZX();
        static Plane<dimensions_> ZY();
    };
    
    typedef Plane<3> Plane3d;
    typedef Plane<Dynamic> PlaneXd;
}

namespace std
{
    template <int dimensions_>
    struct hash<OpenSolid::Plane<dimensions_>> :
        public unary_function<OpenSolid::Plane<dimensions_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Plane<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Plane<dimensions_>> :
        public binary_function<OpenSolid::Plane<dimensions_>, OpenSolid::Plane<dimensions_>, bool>
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
    template <int dimensions_>
    inline Plane<dimensions_>::Plane() {}
    
    namespace
    {
        template <int dimensions_, int axes_, class VectorsType>
        Matrix<double, dimensions_, axes_> planeBasis(const VectorsType& vectors) {
            if (vectors.cols() == 1) {
                int sign = vectors.rows() % 2 == 0 ? -1 : 1;
                return sign * orthonormalBasis(vectors).rightCols(vectors.rows() - 1);
            } else {
                return orthonormalBasis(vectors).leftCols(vectors.rows() - 1);
            }
        }
    }
    
    template <int dimensions_> template <class VectorsType>
    Plane<dimensions_>::Plane(
        const Matrix<double, dimensions_, 1>& origin,
        const EigenBase<VectorsType>& vectors
    ) : Datum<dimensions_, static_axes>(origin, planeBasis<dimensions_, static_axes>(vectors)) {}

    namespace
    {
        inline Matrix<double, 3, 2> planeBasis(Vector3d first_vector, Vector3d second_vector) {
            first_vector.normalize();
            second_vector -= second_vector.dot(first_vector) * first_vector;
            second_vector.normalize();
            Matrix<double, 3, 2> result;
            result << first_vector, second_vector;
            return result;
        }
    }
    
    template <int dimensions_>
    Plane<dimensions_>::Plane(
        const Vector3d& origin,
        const Vector3d& first_vector,
        const Vector3d& second_vector
    ) : Datum<dimensions_, static_axes>(origin, planeBasis(first_vector, second_vector)) {
        assertCompatible<dimensions_, 3>();
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Plane<dimensions_>::Plane(const Datum<other_dimensions_, other_axes_>& other) :
        Datum<dimensions_, static_axes>(other) {
        assert(other.axes() == other.dimensions() - 1);
        assert(other.basis().isUnitary());
    }

    template <int dimensions_> template <int other_dimensions_, int other_axes_>
    inline Plane<dimensions_>& Plane<dimensions_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assert(other.axes() == other.dimensions() - 1);
        assert(other.basis().isUnitary());
        Datum<dimensions_, static_axes>::operator=(other);
        return *this;
    }

    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::XY() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitX(), Vector3d::UnitY());
    }
    
    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::XZ() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitX(), Vector3d::UnitZ());
    }
    
    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::YX() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitY(), Vector3d::UnitX());
    }
    
    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::YZ() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitY(), Vector3d::UnitZ());
    }
    
    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::ZX() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitZ(), Vector3d::UnitX());
    }
    
    template <int dimensions_>
    inline Plane<dimensions_> Plane<dimensions_>::ZY() {
        assertCompatible<dimensions_, 3>();
        return Plane<dimensions_>(Vector3d::Zero(), Vector3d::UnitZ(), Vector3d::UnitY());
    }
}

namespace std
{
    template <int dimensions_>
    inline size_t hash<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& argument
    ) const {
        return hash<
            OpenSolid::Datum<
                dimensions_,
                dimensions_ == Eigen::Dynamic ? Eigen::Dynamic : dimensions_ - 1
            >
        >()(argument);
    }

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& first_argument,
        const OpenSolid::Plane<dimensions_>& second_argument
    ) const {
        return equal_to<
            OpenSolid::Datum<
                dimensions_,
                dimensions_ == Eigen::Dynamic ? Eigen::Dynamic : dimensions_ - 1
            >
        >()(first_argument, second_argument);
    }
}

#endif
