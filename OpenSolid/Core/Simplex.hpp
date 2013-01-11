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

#include "Simplex/declarations.hpp"

#include <OpenSolid/Utils/Conversion.hpp>
#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    class Simplex :
        public Transformable<Simplex<iNumDimensions, iNumVertices>>,
        public Convertible<Simplex<iNumDimensions, iNumVertices>>
    {
    public:
        typedef Matrix<double, iNumDimensions, iNumVertices> Vertices;
        typedef typename Vertices::ColXpr Vertex;
        typedef typename Vertices::ConstColXpr ConstVertex;
        typedef Simplex<iNumDimensions, 2> Edge;
        typedef Simplex<iNumDimensions, 3> Face;
        typedef Matrix<double, iNumDimensions, 1> Vector;
    private:
        Vertices _vertices;
    public:
        Simplex();
        
        Simplex(const Simplex<iNumDimensions, iNumVertices>& otherSimplex);
        
        template <int iOtherNumDimensions, int iOtherNumVertices>
        Simplex(const Simplex<iOtherNumDimensions, iOtherNumVertices>& otherSimplex);
        
        explicit Simplex(const Matrix<double, iNumDimensions, iNumVertices>& vertices);
        
        Simplex(double firstVertex, double secondVertex);
        
        Simplex(
            const Matrix<double, iNumDimensions, 1>& firstVertex,
            const Matrix<double, iNumDimensions, 1>& secondVertex
        );
        
        Simplex(
            const Matrix<double, iNumDimensions, 1>& firstVertex,
            const Matrix<double, iNumDimensions, 1>& secondVertex,
            const Matrix<double, iNumDimensions, 1>& thirdVertex
        );
        
        Simplex(
            const Matrix<double, iNumDimensions, 1>& firstVertex,
            const Matrix<double, iNumDimensions, 1>& secondVertex,
            const Matrix<double, iNumDimensions, 1>& thirdVertex,
            const Matrix<double, iNumDimensions, 1>& fourthVertex
        );
            
        Simplex<iNumDimensions, iNumVertices>& operator=(
            const Simplex<iNumDimensions, iNumVertices>& otherSimplex
        );
        
        template <int iOtherNumDimensions, int iOtherNumVertices>
        Simplex<iNumDimensions, iNumVertices>& operator=(
            const Simplex<iOtherNumDimensions, iOtherNumVertices>& otherSimplex
        );
        
        int numDimensions() const;
        int numVertices() const;
        
        Vertices& vertices();
        const Vertices& vertices() const;

        Vertex vertex(int index);
        ConstVertex vertex(int index) const;
        
        double length() const;
        double area() const;
        double volume() const;
        
        Vector vector() const;
        Vector centroid() const;
        Vector normal() const;
        
        Edge edge(int index) const;
        Edge edge(int startIndex, int endIndex) const;
        Face face(int index) const;
        
        Datum<iNumDimensions, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)>
        coordinateSystem() const;
        
        Matrix<Interval, iNumDimensions, 1> bounds() const;

        template <class TTransformMatrix, class TTransformVector>
        Simplex<TTransformMatrix::RowsAtCompileTime, iNumVertices> transformed(
            const MatrixType& transformMatrix,
            const TTransformVector& transformVector
        ) const;
        
        bool operator==(const Simplex<iNumDimensions, iNumVertices>& otherSimplex) const;
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
    template <int iNumDimensions, int iNumVertices>
    struct Bounds<Simplex<iNumDimensions, iNumVertices>>
    {
        typedef Matrix<Interval, iNumDimensions, 1> Type;

        Matrix<Interval, iNumDimensions, 1> operator()(
            const Simplex<iNumDimensions, iNumVertices>& simplex
        ) const;
    };


    template <int iNumDimensions, int iNumVertices, int iNumTransformedDimensions>
    struct Transformed
    {
        typedef Simplex<iNumTransformedDimensions, iNumVertices> Type;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex() : _vertices() {
    }

    template <int iNumDimensions, int iNumVertices>
    inline Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) : _vertices(otherSimplex.vertices()) {
    }
        
    template <int iNumDimensions, int iNumVertices>
    template <int iOtherNumDimensions, int iOtherNumVertices>
    inline Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Simplex<iOtherNumDimensions, iOtherNumVertices>& otherSimplex
    ) : _vertices(otherSimplex.vertices()) {
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, iNumVertices>& vertices
    ) : _vertices(vertices) {
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex(double firstVertex, double secondVertex) {
        _vertices.resize(1, 2);
        _vertices(0) = firstVertex;
        _vertices(1) = secondVertex;
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, 1>& firstVertex,
        const Matrix<double, iNumDimensions, 1>& secondVertex
    ) {
        assert(firstVertex.size() == secondVertex.size());
        _vertices.resize(firstVertex.size(), 2);
        _vertices.col(0) = firstVertex;
        _vertices.col(1) = secondVertex;
    }
        
    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, 1>& firstVertex,
        const Matrix<double, iNumDimensions, 1>& secondVertex,
        const Matrix<double, iNumDimensions, 1>& thirdVertex
    ) {
        assertCompatible<iNumVertices, 3>();
        assert(firstVertex.size() == secondVertex.size());
        assert(firstVertex.size() == thirdVertex.size());
        _vertices.resize(firstVertex.size(), 3);
        _vertices.col(0) = firstVertex;
        _vertices.col(1) = secondVertex;
        _vertices.col(2) = thirdVertex;
    }

    template <int iNumDimensions, int iNumVertices> 
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const Matrix<double, iNumDimensions, 1>& firstVertex,
        const Matrix<double, iNumDimensions, 1>& secondVertex,
        const Matrix<double, iNumDimensions, 1>& thirdVertex,
        const Matrix<double, iNumDimensions, 1>& fourthVertex
    ) {
        assertCompatible<iNumVertices, 4>();
        assert(firstVertex.size() == secondVertex.size());
        assert(firstVertex.size() == thirdVertex.size());
        assert(firstVertex.size() == fourthVertex.size());
        _vertices.resize(firstVertex.size(), 4);
        _vertices.col(0) = firstVertex;
        _vertices.col(1) = secondVertex;
        _vertices.col(2) = thirdVertex;
        _vertices.col(3) = fourthVertex;
    }
    
    template <int iNumDimensions, int iNumVertices> 
    inline Simplex<iNumDimensions, iNumVertices>& Simplex<iNumDimensions, iNumVertices>::operator=(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) {
        _vertices = otherSimplex.vertices();
        return *this;
    }
    
    template <int iNumDimensions, int iNumVertices>
    template <int iOtherNumDimensions, int iOtherNumVertices>
    inline Simplex<iNumDimensions, iNumVertices>& Simplex<iNumDimensions, iNumVertices>::operator=(
        const Simplex<iOtherNumDimensions, iOtherNumVertices>& otherSimplex
    ) {
        _vertices = otherSimplex.vertices();
        return *this;
    }

    template <int iNumDimensions, int iNumVertices>
    int Simplex<iNumDimensions, iNumVertices>::numDimensions() const {
        return _vertices.rows();
    }

    template <int iNumDimensions, int iNumVertices>
    int Simplex<iNumDimensions, iNumVertices>::numVertices() const {
        return _vertices.cols();
    }

    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vertices&
    Simplex<iNumDimensions, iNumVertices>::vertices() {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    const typename Simplex<iNumDimensions, iNumVertices>::Vertices&
    Simplex<iNumDimensions, iNumVertices>::vertices() const {
        return _vertices;
    }

    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vertex
    Simplex<iNumDimensions, iNumVertices>::vertex(int index) {
        return _vertices.col(index);
    }

    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::ConstVertex
    Simplex<iNumDimensions, iNumVertices>::vertex(int index) const {
        return _vertices.col(index);
    }

    template <int iNumDimensions, int iNumVertices>
    double Simplex<iNumDimensions, iNumVertices>::length() const {
        assert(numVertices() == 2);
        if (numDimensions() == 1) {
            return vertices()(0, 1) - vertices()(0, 0);
        } else {
            return (vertex(1) - vertex(0)).norm();
        }
    }

    namespace detail
    {
        template <class SimplexType>
        inline double triangleArea2d(const SimplexType& triangle) {
            Matrix2d edges;
            edges.col(0) = triangle.vertex(1) - triangle.vertex(0);
            edges.col(1) = triangle.vertex(2) - triangle.vertex(0);
            return edges.determinant() / 2;
        }

        template <class SimplexType>
        inline double triangleArea3d(const SimplexType& triangle) {
            Vector3d first_edge = triangle.vertex(1) - triangle.vertex(0);
            Vector3d second_edge = triangle.vertex(2) - triangle.vertex(0);
            return first_edge.cross(second_edge).norm() / 2;
        }

        inline double triangleArea(const Simplex<2, 3>& triangle) {
            return triangleArea2d(triangle);
        }

        inline double triangleArea(const Simplex<3, 3>& triangle) {
            return triangleArea3d(triangle);
        }

        inline double triangleArea(const Simplex<Dynamic, Dynamic>& triangle) {
            return triangle.numDimensions() == 2 ? triangleArea2d(triangle) : triangleArea3d(triangle);
        }
    }

    template <int iNumDimensions, int iNumVertices>
    double Simplex<iNumDimensions, iNumVertices>::area() const {
        assert(numVertices() == 3);
        assert(numDimensions() >= 2);
        return detail::triangleArea(*this);
    }

    template <int iNumDimensions, int iNumVertices>
    double Simplex<iNumDimensions, iNumVertices>::volume() const {
        assert(numVertices() == 4);
        assert(numDimensions() == 3);
        return (vertices().template rightCols<3>().colwise() - vertex(0)).determinant() / 6;
    }

    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector Simplex<iNumDimensions, iNumVertices>::vector() const {
        assert(numVertices() == 2);
        return vertex(1) - vertex(0);
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector
    Simplex<iNumDimensions, iNumVertices>::centroid() const {
        return vertices().rowwise().mean();
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector
    Simplex<iNumDimensions, iNumVertices>::normal() const {
        assert(numVertices() <= numDimensions());
        return coordinateSystem().normal();
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Edge
    Simplex<iNumDimensions, iNumVertices>::edge(int index) const {
        assert(0 <= index && index < numVertices());
        return Edge(vertex(index), vertex((index + 1) % numVertices()));
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Edge
    Simplex<iNumDimensions, iNumVertices>::edge(int startIndex, int endIndex) const {
        assert(0 <= startIndex && startIndex < numVertices());
        assert(0 <= endIndex && endIndex < numVertices());
        assert(startIndex != endIndex);
        return Edge(vertex(startIndex), vertex(endIndex));
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Face
    Simplex<iNumDimensions, iNumVertices>::face(int index) const {
        typename Face::Vertices faceVertices(numDimensions(), numVertices() - 1);
        Matrix<int, 1, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)> indices(numVertices() - 1);
        for (int i = 0; i < indices.size(); ++i) {
            indices(i) = (index + 1 + i) % numVertices();
        }
        if (numVertices() % 2 != 0 || index % 2 != 0) {
            indices.tail(2).reverseInPlace();
        }
        for (int i = 0; i < indices.size(); ++i) {
            faceVertices.col(i) = vertex(indices(i));
        }
        return Face(faceVertices);
    }

    template <int iNumDimensions, int iNumVertices>
    Datum<iNumDimensions, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)>
    Simplex<iNumDimensions, iNumVertices>::coordinateSystem() const {
        return Datum<iNumDimensions, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)>(
            vertex(0),
            vertices().rightCols(numVertices() - 1).colwise() - vertex(0)
        );
    }
    
    template <int iNumDimensions, int iNumVertices>
    Matrix<Interval, iNumDimensions, 1> Simplex<iNumDimensions, iNumVertices>::bounds() const {
        return _vertices.rowwise().minCoeff().hull(_vertices.rowwise().maxCoeff());
    }

    template <int iNumDimensions, int iNumVertices>
    template <class TTransformMatrix, class TTransformVector>
    Simplex<MatrixType::RowsAtCompileTime, iNumVertices>
    Simplex<iNumDimensions, iNumVertices>::transformed(
        const TTransformMatrix& transformMatrix,
        const TTransformVector& transformVector
    ) const {
        assertValidTransform<iNumDimensions>(numDimensions(), transformMatrix, transformVector);
        return Simplex<
            (iNumDimensions == Dynamic ? Dynamic : TTransformMatrix::RowsAtCompileTime),
            iNumVertices
        >((transformMatrix * vertices()).colwise() + transformVector);
    }
        
    template <int iNumDimensions, int iNumVertices>
    bool Simplex<iNumDimensions, iNumVertices>::operator==(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) const {
        assert(numDimensions() == otherSimplex.numDimensions());
        assert(numVertices() == otherSimplex.numVertices());
        return vertices() == otherSimplex.vertices();
    }

    template <int iNumDimensions, int iNumVertices>
    Matrix<Interval, iNumDimensions, 1> Bounds<Simplex<iNumDimensions, iNumVertices>>::operator()(
        const Simplex<iNumDimensions, iNumVertices>& simplex
    ) const {
        return simplex.bounds();
    }
}
