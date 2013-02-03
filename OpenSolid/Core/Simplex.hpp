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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>
 
#include <OpenSolid/Core/Simplex/declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    class Simplex :
        public Transformable<Simplex<iNumDimensions, iNumVertices>>,
        public Convertible<Simplex<iNumDimensions, iNumVertices>>
    {
    private:
        Matrix<double, iNumDimensions, iNumVertices> _vertices;
    public:
        Simplex();
        
        Simplex(const Simplex<iNumDimensions, iNumVertices>& otherSimplex);
        
        explicit Simplex(const Matrix<double, iNumDimensions, iNumVertices>& vertices);
            
        Simplex<iNumDimensions, iNumVertices>& operator=(
            const Simplex<iNumDimensions, iNumVertices>& otherSimplex
        );
        
        Matrix<double, iNumDimensions, iNumVertices>& vertices();
        const Matrix<double, iNumDimensions, iNumVertices>& vertices() const;

        typename Matrix<double, iNumDimensions, iNumVertices>::ColXpr vertex(int index);
        typename Matrix<double, iNumDimensions, iNumVertices>::ConstColXpr vertex(int index) const;
        
        double length() const;
        double squaredLength() const;
        double area() const;
        double volume() const;
        
        Matrix<double, iNumDimensions, 1> vector() const;
        Matrix<double, iNumDimensions, 1> centroid() const;
        Matrix<double, iNumDimensions, 1> normalVector() const;
        
        Simplex<iNumDimensions, 2> edge(int index) const;
        Simplex<iNumDimensions, 2> edge(int startIndex, int endIndex) const;

        Simplex<iNumDimensions, 3> face(int index) const;
        
        Datum<iNumDimensions, iNumVertices - 1> datum() const;
        Datum<iNumDimensions, 1> axis() const;
        Datum<3, 2> plane() const;
        
        Matrix<Interval, iNumDimensions, 1> bounds() const;
        
        bool operator==(const Simplex<iNumDimensions, iNumVertices>& otherSimplex) const;
    };

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices> operator*(
        double scaleFactor,
        const Simplex<iNumDimensions, iNumVertices>& simplex
    );

    template <int iNumDimensions, int iNumVertices, class TVector>
    Simplex<iNumDimensions, iNumVertices> operator+(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const EigenBase<TVector>& vector
    );

    template <int iNumDimensions, int iNumVertices, class TMatrix>
    Simplex<TMatrix::RowsAtCompileTime, iNumVertices> operator*(
        const EigenBase<TMatrix>& transformationMatrix,
        const Simplex<iNumDimensions, iNumVertices>& simplex
    );
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    struct Bounds<Simplex<iNumDimensions, iNumVertices>>
    {
        typedef Matrix<Interval, iNumDimensions, 1> Type;

        Matrix<Interval, iNumDimensions, 1> operator()(
            const Simplex<iNumDimensions, iNumVertices>& simplex
        ) const;
    };

    template <int iNumDimensions, int iNumVertices, int iTransformedDimensions>
    struct Transformed<Simplex<iNumDimensions, iNumVertices>, iTransformedDimensions>
    {
        typedef Simplex<iTransformedDimensions, iNumVertices> Type;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    inline Simplex<iNumDimensions, iNumVertices>::Simplex() {
        _vertices.setZero();
    }

    template <int iNumDimensions, int iNumVertices>
    inline Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) : _vertices(otherSimplex.vertices()) {
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, iNumVertices>& vertices
    ) : _vertices(vertices) {
    }
    
    template <int iNumDimensions, int iNumVertices> 
    inline Simplex<iNumDimensions, iNumVertices>& Simplex<iNumDimensions, iNumVertices>::operator=(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) {
        _vertices = otherSimplex.vertices();
        return *this;
    }

    template <int iNumDimensions, int iNumVertices>
    Matrix<double, iNumDimensions, iNumVertices>&
    Simplex<iNumDimensions, iNumVertices>::vertices() {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    const Matrix<double, iNumDimensions, iNumVertices>&
    Simplex<iNumDimensions, iNumVertices>::vertices() const {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    typename Matrix<double, iNumDimensions, iNumVertices>::ColXpr
    Simplex<iNumDimensions, iNumVertices>::vertex(int index) {
        return _vertices.col(index);
    }

    template <int iNumDimensions, int iNumVertices>
    typename Matrix<double, iNumDimensions, iNumVertices>::ConstColXpr
    Simplex<iNumDimensions, iNumVertices>::vertex(int index) const {
        return _vertices.col(index);
    }

    template <>
    inline double Simplex<1, 2>::length() const {
        return vertices()(0, 1) - vertices()(0, 0);
    }

    template <>
    inline double Simplex<2, 2>::length() const {
        return (vertex(1) - vertex(0)).norm();
    }

    template <>
    inline double Simplex<3, 2>::length() const {
        return (vertex(1) - vertex(0)).norm();
    }

    template <>
    inline double Simplex<1, 2>::squaredLength() const {
        double length = vertices()(0, 1) - vertices()(0, 0);
        return length * length;
    }

    template <>
    inline double Simplex<2, 2>::squaredLength() const {
        return (vertex(1) - vertex(0)).squaredNorm();
    }

    template <>
    inline double Simplex<3, 2>::squaredLength() const {
        return (vertex(1) - vertex(0)).squaredNorm();
    }

    template <>
    inline double Simplex<2, 3>::area() const {
        return (vertices().rightCols<2>().colwise() - vertex(0)).determinant() / 2;
    }

    template <>
    inline double Simplex<3, 3>::area() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).norm() / 2;
    }

    template <>
    inline double Simplex<3, 4>::volume() const {
        return (vertices().rightCols<3>().colwise() - vertex(0)).determinant() / 6;
    }

    template <>
    inline Matrix1d Simplex<1, 2>::vector() const {
        return vertex(1) - vertex(0);
    }

    template <>
    inline Vector2d Simplex<2, 2>::vector() const {
        return vertex(1) - vertex(0);
    }

    template <>
    inline Vector3d Simplex<3, 2>::vector() const {
        return vertex(1) - vertex(0);
    }
    
    template <int iNumDimensions, int iNumVertices>
    inline Matrix<double, iNumDimensions, 1>
    Simplex<iNumDimensions, iNumVertices>::centroid() const {
        return vertices().rowwise().mean();
    }

    template <>
    inline Vector2d Simplex<2, 2>::normalVector() const {
        return (vertex(1) - vertex(0)).unitOrthogonal();
    }

    template <>
    inline Vector3d Simplex<3, 2>::normalVector() const {
        return (vertex(1) - vertex(0)).unitOrthogonal();
    }

    template <>
    inline Vector3d Simplex<3, 3>::normalVector() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).normalized();
    }
    
    template <>
    inline Simplex<2, 2> Simplex<2, 3>::edge(int index) const {
        assert(0 <= index && index < 3);
        Matrix2d vertices;
        vertices << vertex(index), vertex((index + 1) % 3);
        return Simplex<2, 2>(vertices);
    }
    
    template <>
    inline Simplex<3, 2> Simplex<3, 3>::edge(int index) const {
        assert(0 <= index && index < 3);
        Matrix<double, 3, 2> vertices;
        vertices << vertex(index), vertex((index + 1) % 3);
        return Simplex<3, 2>(vertices);
    }
    
    template <>
    inline Simplex<2, 2> Simplex<2, 3>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 3);
        assert(0 <= endIndex && endIndex < 3);
        assert(startIndex != endIndex);
        Matrix2d vertices;
        vertices << vertex(startIndex), vertex(endIndex);
        return Simplex<2, 2>(vertices);
    }
    
    template <>
    inline Simplex<3, 2> Simplex<3, 3>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 3);
        assert(0 <= endIndex && endIndex < 3);
        assert(startIndex != endIndex);
        Matrix<double, 3, 2> vertices;
        vertices << vertex(startIndex), vertex(endIndex);
        return Simplex<3, 2>(vertices);
    }
    
    template <>
    inline Simplex<3, 2> Simplex<3, 4>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < 4);
        assert(0 <= endIndex && endIndex < 4);
        assert(startIndex != endIndex);
        Matrix<double, 3, 2> vertices;
        vertices << vertex(startIndex), vertex(endIndex);
        return Simplex<3, 2>(vertices);
    }
    
    template <>
    inline Simplex<3, 3> Simplex<3, 4>::face(int index) const {
        Matrix3d faceVertices;
        RowVector3i indices;
        for (int i = 0; i < 3; ++i) {
            indices(i) = (index + 1 + i) % 4;
        }
        if (index % 2 != 0) {
            indices.tail(2).reverseInPlace();
        }
        for (int i = 0; i < 3; ++i) {
            faceVertices.col(i) = vertex(indices(i));
        }
        return Simplex<3, 3>(faceVertices);
    }

    template <int iNumDimensions, int iNumVertices>
    Datum<iNumDimensions, iNumVertices - 1>
    Simplex<iNumDimensions, iNumVertices>::datum() const {
        return Datum<iNumDimensions, iNumVertices - 1>(
            vertex(0),
            vertices().template rightCols<iNumVertices - 1>().colwise() - vertex(0)
        );
    }

    template <>
    inline Datum<2, 1> Simplex<2, 2>::axis() const {
        return datum().normalized();
    }

    template <>
    inline Datum<3, 1> Simplex<3, 2>::axis() const {
        return datum().normalized();
    }

    template <>
    inline Datum<3, 2> Simplex<3, 3>::plane() const {
        return datum().normalized();
    }
    
    template <int iNumDimensions, int iNumVertices>
    Matrix<Interval, iNumDimensions, 1> Simplex<iNumDimensions, iNumVertices>::bounds() const {
        return _vertices.rowwise().minCoeff().hull(_vertices.rowwise().maxCoeff());
    }
        
    template <int iNumDimensions, int iNumVertices>
    bool Simplex<iNumDimensions, iNumVertices>::operator==(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) const {
        return vertices() == otherSimplex.vertices();
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices> operator*(
        double scaleFactor,
        const Simplex<iNumDimensions, iNumVertices>& simplex
    ) {
        return Simplex<iNumDimensions, iNumVertices>(scaleFactor * simplex.vertices());
    }

    template <int iNumDimensions, int iNumVertices, class TVector>
    Simplex<iNumDimensions, iNumVertices> operator+(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const EigenBase<TVector>& vector
    ) {
        return Simplex<iNumDimensions, iNumVertices>(
            simplex.vertices().colwise() + vector.derived()
        );
    }

    template <int iNumDimensions, int iNumVertices, class TMatrix>
    Simplex<TMatrix::RowsAtCompileTime, iNumVertices> operator*(
        const EigenBase<TMatrix>& transformationMatrix,
        const Simplex<iNumDimensions, iNumVertices>& simplex
    ) {
        return Simplex<TMatrix::RowsAtCompileTime, iNumVertices>(
            transformationMatrix.derived() * simplex.vertices()
        );
    }

    template <int iNumDimensions, int iNumVertices>
    Matrix<Interval, iNumDimensions, 1> Bounds<Simplex<iNumDimensions, iNumVertices>>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex
    ) const {
        return simplex.bounds();
    }
}
