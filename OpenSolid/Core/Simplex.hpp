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

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Utils/Convertible.hpp>

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
        Vector normalVector() const;
        
        Edge edge(int index) const;
        Edge edge(int startIndex, int endIndex) const;
        Face face(int index) const;
        
        Datum<iNumDimensions, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)>
        coordinateSystem() const;
        
        Matrix<Interval, iNumDimensions, 1> bounds() const;
        
        bool operator==(const Simplex<iNumDimensions, iNumVertices>& otherSimplex) const;

        static Simplex<iNumDimensions, iNumVertices> Unit();
        static Simplex<iNumDimensions, iNumVertices> Unit(int numDimensions);
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
    
    typedef Simplex<1, 2> LineSegment1d;
    typedef Simplex<2, 2> LineSegment2d;
    typedef Simplex<3, 2> LineSegment3d;
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
    Simplex<iNumDimensions, iNumVertices>::Simplex() {
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

    namespace detail
    {
        inline double simplexLength(const LineSegment1d& lineSegment) {
            return lineSegment.vertices()(0, 1) - lineSegment.vertices()(0, 0);
        }

        template <int iNumDimensions>
        inline double simplexLength(const Simplex<iNumDimensions, 2>& lineSegment) {
            return (lineSegment.vertex(1) - lineSegment.vertex(0)).norm();
        }

        inline double simplexLength(const SimplexXd& simplex) {
            if (simplex.numVertices() == 2) {
                if (simplex.numDimensions() == 1) {
                    return simplexLength(LineSegment1d(simplex));
                } else {
                    return (simplex.vertex(1) - simplex.vertex(0)).norm();
                }
            }
            assert(false);
            return 0.0;
        }
    }

    template <int iNumDimensions, int iNumVertices>
    inline double Simplex<iNumDimensions, iNumVertices>::length() const {
        return detail::simplexLength(*this);
    }

    namespace detail
    {
        inline double simplexArea(const Triangle2d& triangle) {
            Matrix2d edgeVectors =
                triangle.vertices().rightCols<2>().colwise() - triangle.vertex(0);
            return edgeVectors.determinant() / 2;
        }

        inline double simplexArea(const Triangle3d& triangle) {
            Vector3d first_edge = triangle.vertex(1) - triangle.vertex(0);
            Vector3d second_edge = triangle.vertex(2) - triangle.vertex(0);
            return first_edge.cross(second_edge).norm() / 2;
        }

        inline double simplexArea(const SimplexXd& simplex) {
            if (simplex.numVertices() == 3) {
                if (simplex.numDimensions() == 2) {
                    return simplexArea(Triangle2d(simplex));
                } else if (simplex.numDimensions() == 3) {
                    return simplexArea(Triangle3d(simplex));
                }
            }
            assert(false);
            return 0.0;
        }
    }

    template <int iNumDimensions, int iNumVertices>
    inline double Simplex<iNumDimensions, iNumVertices>::area() const {
        return detail::simplexArea(*this);
    }

    namespace detail
    {
        inline double simplexVolume(const Tetrahedron3d& tetrahedron) {
            Matrix3d edgeVectors =
                tetrahedron.vertices().rightCols<3>().colwise() - tetrahedron.vertex(0);
            return edgeVectors.determinant() / 6;
        }

        inline double simplexVolume(const SimplexXd& simplex) {
            if (simplex.numDimensions() == 3 && simplex.numVertices() == 4) {
                return simplexVolume(Tetrahedron3d(simplex));
            } else {
                assert(false);
                return 0.0;
            }
        }
    }

    template <int iNumDimensions, int iNumVertices>
    inline double Simplex<iNumDimensions, iNumVertices>::volume() const {
        return detail::simplexVolume(*this);
    }

    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector
    Simplex<iNumDimensions, iNumVertices>::vector() const {
        assert(numVertices() == 2);
        return vertex(1) - vertex(0);
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector
    Simplex<iNumDimensions, iNumVertices>::centroid() const {
        return vertices().rowwise().mean();
    }

    namespace detail
    {
        inline Vector2d simplexNormalVector(const LineSegment2d& lineSegment) {
            return (lineSegment.vertex(1) - lineSegment.vertex(0)).unitOrthogonal();
        }

        inline Vector3d simplexNormalVector(const LineSegment3d& lineSegment) {
            return (lineSegment.vertex(1) - lineSegment.vertex(0)).unitOrthogonal();
        }

        inline Vector3d simplexNormalVector(const Triangle3d& triangle) {
            Vector3d firstEdgeVector = triangle.vertex(1) - triangle.vertex(0);
            Vector3d secondEdgeVector = triangle.vertex(2) - triangle.vertex(0);
            return firstEdgeVector.cross(secondEdgeVector).normalized();
        }

        inline VectorXd simplexNormalVector(const SimplexXd& simplex) {
            if (simplex.numDimensions() == 2) {
                if (simplex.numVertices() == 2) {
                    return simplexNormalVector(LineSegment2d(simplex));
                }
            } else if (simplex.numDimensions() == 3) {
                if (simplex.numVertices() == 2) {
                    return simplexNormalVector(LineSegment3d(simplex));
                } else if (simplex.numVertices() == 3) {
                    return simplexNormalVector(Triangle3d(simplex));
                }
            }
            assert(false);
            return VectorXd::Zero(simplex.numDimensions());
        }
    }
    
    template <int iNumDimensions, int iNumVertices>
    typename Simplex<iNumDimensions, iNumVertices>::Vector
    Simplex<iNumDimensions, iNumVertices>::normalVector() const {
        return detail::simplexNormalVector(*this);
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
        Matrix<int, 1, (iNumVertices == Dynamic ? Dynamic : iNumVertices - 1)> indices(
            numVertices() - 1
        );
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
    bool Simplex<iNumDimensions, iNumVertices>::operator==(
        const Simplex<iNumDimensions, iNumVertices>& otherSimplex
    ) const {
        assert(numDimensions() == otherSimplex.numDimensions());
        assert(numVertices() == otherSimplex.numVertices());
        return vertices() == otherSimplex.vertices();
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices> Simplex<iNumDimensions, iNumVertices>::Unit() {
        Matrix<double, iNumDimensions, iNumDimensions + 1> vertices;
        vertices.col(0).setZero();
        vertices.template rightCols<iNumDimensions>().setIdentity();
        return Simplex<iNumDimensions, iNumVertices>(vertices);
    }

    template <int iNumDimensions, int iNumVertices>
    Simplex<iNumDimensions, iNumVertices> Simplex<iNumDimensions, iNumVertices>::Unit(
        int numDimensions
    ) {
        Matrix<double, iNumDimensions, iNumDimensions == Dynamic ? Dynamic : iNumDimensions + 1> vertices(
            numDimensions,
            numDimensions + 1
        );
        vertices.col(0).setZero();
        vertices.rightCols(numDimensions).setIdentity();
        return Simplex<iNumDimensions, iNumVertices>(vertices);
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
