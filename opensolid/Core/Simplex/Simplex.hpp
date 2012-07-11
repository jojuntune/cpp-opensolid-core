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

#pragma once

#include <OpenSolid/Core/Generic/Bounds.hpp>
#include <OpenSolid/Core/Generic/Conversion.hpp>
#include <OpenSolid/Core/Generic/Transformable.hpp>
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/Generic/TypeDescriptionFunction.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/config.hpp>

namespace opensolid
{
    template <int dimensions_, int size_>
    class Simplex;

    template <int dimensions_, int size_, class MatrixType>
    struct TransformedSimplex
    {
        typedef Simplex<
            (dimensions_ == Dynamic ? Dynamic : MatrixType::RowsAtCompileTime),
            size_
        > Type;
    };

    template <int dimensions_, int size_>
    class Simplex :
        public Transformable<Simplex<dimensions_, size_>>,
        public Convertible<Simplex<dimensions_, size_>>
    {
    static_assert(
        (dimensions_ == Dynamic) == (size_ == Dynamic),
        "Mixing static and dynamic simplex dimensions and sizes is not supported"
    );
    public:
        typedef Matrix<double, dimensions_, size_> Vertices;
        typedef typename Vertices::ColXpr Vertex;
        typedef typename Vertices::ConstColXpr ConstVertex;
        typedef Simplex<dimensions_, (size_ == Dynamic ? Dynamic : 2)> Edge;
        typedef Simplex<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)> Face;
        typedef Matrix<double, dimensions_, 1> Vector;
    private:
        Vertices _vertices;
    public:
        OPENSOLID_CORE_EXPORT Simplex();
        
        Simplex(const Simplex<dimensions_, size_>& other);
        
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
            
        Simplex<dimensions_, size_>& operator=(
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
        typename TransformedSimplex<dimensions_, size_, MatrixType>::Type
        transformed(const MatrixType& matrix, const VectorType& vector) const;
        
        OPENSOLID_CORE_EXPORT double length() const;
        OPENSOLID_CORE_EXPORT double area() const;
        OPENSOLID_CORE_EXPORT double volume() const;
        
        OPENSOLID_CORE_EXPORT Vector vector() const;
        OPENSOLID_CORE_EXPORT Vector centroid() const;
        OPENSOLID_CORE_EXPORT Vector normal() const;
        
        OPENSOLID_CORE_EXPORT Edge edge(int index) const;
        OPENSOLID_CORE_EXPORT Edge edge(int start_index, int end_index) const;
        OPENSOLID_CORE_EXPORT Face face(int index) const;
        
        OPENSOLID_CORE_EXPORT
        Datum<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)> coordinateSystem() const;
        
        OPENSOLID_CORE_EXPORT Matrix<Interval, dimensions_, 1> bounds() const;
        
        OPENSOLID_CORE_EXPORT bool operator==(const Simplex<dimensions_, size_>& other) const;
    };
    
    typedef Simplex<1, 2> Line1d;
    typedef Simplex<2, 2> Line2d;
    typedef Simplex<3, 2> Line3d;
    typedef Simplex<2, 3> Triangle2d;
    typedef Simplex<3, 3> Triangle3d;
    typedef Simplex<3, 4> Tetrahedron3d;
    typedef Simplex<Dynamic, Dynamic> SimplexXd;
}

////////// Specializations //////////

namespace opensolid
{
    template <int dimensions_, int size_>
    struct Bounds<Simplex<dimensions_, size_>>
    {
        typedef Matrix<Interval, dimensions_, 1> Type;

        Matrix<Interval, dimensions_, 1> operator()(
            const Simplex<dimensions_, size_>& argument
        ) const;
    };

    template <>
    struct TypeDescriptionFunction<SimplexXd>
    {
        OPENSOLID_CORE_EXPORT TypeDescription operator()() const;
    };

    template <>
    struct Conversion<SimplexXd, List>
    {
        OPENSOLID_CORE_EXPORT List operator()(const SimplexXd& argument) const;
    };

    template <>
    struct Conversion<List, SimplexXd>
    {
        OPENSOLID_CORE_EXPORT SimplexXd operator()(const List& argument) const;
    };

    template <>
    struct TypeName<Line1d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Line2d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Line3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Triangle2d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Triangle3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Tetrahedron3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<SimplexXd>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(const Simplex<dimensions_, size_>& other) :
        _vertices(other.vertices()) {}
        
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Simplex<other_dimensions_, other_size_>& other
    ) : _vertices(other.vertices()) {}
    
    template <int dimensions_, int size_> 
    inline Simplex<dimensions_, size_>& Simplex<dimensions_, size_>::operator=(
        const Simplex<dimensions_, size_>& other
    ) {
        _vertices = other.vertices();
        return *this;
    }
    
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>& Simplex<dimensions_, size_>::operator=(
        const Simplex<other_dimensions_, other_size_>& other
    ) {
        _vertices = other.vertices();
        return *this;
    }

    template <int dimensions_, int size_> template <class MatrixType, class VectorType>
    typename TransformedSimplex<dimensions_, size_, MatrixType>::Type
    Simplex<dimensions_, size_>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        assertValidTransform<dimensions_>(dimensions(), matrix, vector);
        return Simplex<(dimensions_ == Dynamic ? Dynamic : MatrixType::RowsAtCompileTime), size_>(
            (matrix * vertices()).colwise() + vector
        );
    }

    template <int dimensions_, int size_>
    Matrix<Interval, dimensions_, 1> Bounds<Simplex<dimensions_, size_>>::operator()(
        const Simplex<dimensions_, size_>& argument
    ) const {return argument.bounds();}
}
