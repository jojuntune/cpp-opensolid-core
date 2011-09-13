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

#ifndef OPENSOLID__SIMPLEX_HPP
#define OPENSOLID__SIMPLEX_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int size_>
    class Simplex : public Transformable<Simplex<dimensions_, size_>>
    {
    public:
        typedef Matrix<double, dimensions_, size_> Vertices;
        typedef typename Vertices::ColXpr Vertex;
        typedef typename Vertices::ConstColXpr ConstVertex;
        typedef Simplex<dimensions_, 2> Edge;
        typedef Simplex<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)> Face;
        typedef Matrix<double, dimensions_, 1> Vector;
    private:
        Vertices _vertices;
    public:
        OPENSOLID_CORE_EXPORT Simplex();
        
        OPENSOLID_CORE_EXPORT Simplex(const Simplex<dimensions_, size_>& other);
        
        template <int other_dimensions_, int other_size_>
        Simplex(const Simplex<other_dimensions_, other_size_>& other);
        
        OPENSOLID_CORE_EXPORT explicit Simplex(const Matrix<double, dimensions_, size_>& vertices);
        
        OPENSOLID_CORE_EXPORT Simplex(double first_vertex, double second_vertex);
        
        OPENSOLID_CORE_EXPORT Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex
        );
        
        OPENSOLID_CORE_EXPORT Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex,
            const Matrix<double, dimensions_, 1>& third_vertex
        );
        
        OPENSOLID_CORE_EXPORT Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex,
            const Matrix<double, dimensions_, 1>& third_vertex,
            const Matrix<double, dimensions_, 1>& fourth_vertex
        );
            
        OPENSOLID_CORE_EXPORT Simplex<dimensions_, size_>& operator=(
            const Simplex<dimensions_, size_>& other
        );
        
        template <int other_dimensions_, int other_size_>
        Simplex<dimensions_, size_>& operator=(
            const Simplex<other_dimensions_, other_size_>& other
        );
        
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT int size() const;
        
        OPENSOLID_CORE_EXPORT Vertices& vertices();
        OPENSOLID_CORE_EXPORT const Vertices& vertices() const;

        OPENSOLID_CORE_EXPORT Vertex vertex(int index);
        OPENSOLID_CORE_EXPORT ConstVertex vertex(int index) const;

        template <class MatrixType, class VectorType>
        Simplex<MatrixType::RowsAtCompileTime, size_> transformed(
            const MatrixType& matrix,
            const VectorType& vector
        ) const;
        
        OPENSOLID_CORE_EXPORT double length() const;
        OPENSOLID_CORE_EXPORT double area() const;
        OPENSOLID_CORE_EXPORT double volume() const;
        
        OPENSOLID_CORE_EXPORT Vector vector() const;
        OPENSOLID_CORE_EXPORT Vector centroid() const;
        OPENSOLID_CORE_EXPORT Vector normal() const;
        
        OPENSOLID_CORE_EXPORT Edge edge(int start_index, int end_index) const;
        OPENSOLID_CORE_EXPORT Face face(int index) const;
        
        OPENSOLID_CORE_EXPORT
        CoordinateSystem<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>
        coordinateSystem() const;
        
        OPENSOLID_CORE_EXPORT Matrix<Interval, dimensions_, 1> bounds() const;
        
        OPENSOLID_CORE_EXPORT bool operator==(const Simplex<dimensions_, size_>& other) const;
    };
    
    typedef Simplex<1, 2> LineSegment1d;
    typedef Simplex<2, 2> LineSegment2d;
    typedef Simplex<3, 2> LineSegment3d;
    
    typedef Simplex<2, 3> Triangle2d;
    typedef Simplex<3, 3> Triangle3d;
    
    typedef Simplex<3, 4> Tetrahedron3d;
    
    typedef Simplex<Dynamic, Dynamic> SimplexXd;
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Simplex<other_dimensions_, other_size_>& other
    ) : _vertices(other.vertices()) {}
    
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>& Simplex<dimensions_, size_>::operator=(
        const Simplex<other_dimensions_, other_size_>& other
    ) {
        _vertices = other.vertices();
        return *this;
    }

    template <int dimensions_, int size_> template <class MatrixType, class VectorType>
    Simplex<MatrixType::RowsAtCompileTime, size_> Simplex<dimensions_, size_>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        assertValidTransform<dimensions_>(dimensions(), matrix, vector);
        static const int new_dimensions = MatrixType::RowsAtCompileTime;
        return Simplex<new_dimensions, size_>((matrix * vertices()).colwise() + vector);
    }
}

#endif
