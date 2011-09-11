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
        Simplex();
        
        Simplex(const Simplex<dimensions_, size_>& other);
        
        template <int other_dimensions_, int other_size_>
        Simplex(const Simplex<other_dimensions_, other_size_>& other);
        
        explicit Simplex(const Matrix<double, dimensions_, size_>& vertices);
        
        Simplex(double first_vertex, double second_vertex);
        
        Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex
        );
        
        Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex,
            const Matrix<double, dimensions_, 1>& third_vertex
        );
        
        Simplex(
            const Matrix<double, dimensions_, 1>& first_vertex,
            const Matrix<double, dimensions_, 1>& second_vertex,
            const Matrix<double, dimensions_, 1>& third_vertex,
            const Matrix<double, dimensions_, 1>& fourth_vertex
        );
        
        Simplex<dimensions_, size_>& operator=(const Simplex<dimensions_, size_>& other);
        
        template <int other_dimensions_, int other_size_>
        Simplex<dimensions_, size_>& operator=(
            const Simplex<other_dimensions_, other_size_>& othe
        );
        
        int dimensions() const;
        int size() const;
        
        Vertices& vertices();
        const Vertices& vertices() const;

        Vertex vertex(int index);
        ConstVertex vertex(int index) const;

        template <class MatrixType, class VectorType>
        Simplex<MatrixType::RowsAtCompileTime, size_> transformed(
            const MatrixType& matrix,
            const VectorType& vecto
        ) const;
        
        double length() const;
        double area() const;
        double volume() const;
        
        Vector vector() const;
        Vector centroid() const;
        Vector normal() const;
        
        Edge edge(int start_index, int end_index) const;
        Face face(int index) const;
        
        CoordinateSystem<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>
        coordinateSystem() const;
        
        Matrix<Interval, dimensions_, 1> bounds() const;
        
        template <int other_dimensions_, int other_size_>
        bool operator==(const Simplex<other_dimensions_, other_size_>& other) const;
    };
    
    typedef Simplex<1, 2> LineSegment1d;
    typedef Simplex<2, 2> LineSegment2d;
    typedef Simplex<3, 2> LineSegment3d;
    typedef Simplex<Dynamic, 2> LineSegmentXd;
    
    typedef Simplex<2, 3> Triangle2d;
    typedef Simplex<3, 3> Triangle3d;
    typedef Simplex<Dynamic, 3> TriangleXd;
    
    typedef Simplex<3, 4> Tetrahedron3d;
    typedef Simplex<Dynamic, 4> TetrahedronXd;
    
    typedef Simplex<Dynamic, Dynamic> SimplexXd;
}

////////// Implementation //////////

namespace OpenSolid
{   
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex() : _vertices() {}
        
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(const Simplex<dimensions_, size_>& other)
        : _vertices(other.vertices()) {}
    
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Simplex<other_dimensions_, other_size_>& othe
    ) : _vertices(other.vertices()) {}
        
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, size_>& vertices
    ) : _vertices(vertices) {}
        
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(double first_vertex, double second_vertex) {
        assertCompatible<dimensions_, 1>();
        assertCompatible<size_, 2>();
        _vertices.resize(1, 2);
        _vertices(0) = first_vertex;
        _vertices(1) = second_vertex;
    }

    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex
    ) {
        assertCompatible<size_, 2>();
        assert(first_vertex.size() == second_vertex.size());
        _vertices.resize(first_vertex.size(), 2);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
    }
        
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex,
        const Matrix<double, dimensions_, 1>& third_vertex
    ) {
        assertCompatible<size_, 3>();
        assert(first_vertex.size() == second_vertex.size());
        assert(first_vertex.size() == third_vertex.size());
        _vertices.resize(first_vertex.size(), 3);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
        _vertices.col(2) = third_vertex;
    }
        
    template <int dimensions_, int size_> 
    inline Simplex<dimensions_, size_>::Simplex(
        const Matrix<double, dimensions_, 1>& first_vertex,
        const Matrix<double, dimensions_, 1>& second_vertex,
        const Matrix<double, dimensions_, 1>& third_vertex,
        const Matrix<double, dimensions_, 1>& fourth_vertex
    ) {
        assertCompatible<size_, 4>();
        assert(first_vertex.size() == second_vertex.size());
        assert(first_vertex.size() == third_vertex.size());
        assert(first_vertex.size() == fourth_vertex.size());
        _vertices.resize(first_vertex.size(), 4);
        _vertices.col(0) = first_vertex;
        _vertices.col(1) = second_vertex;
        _vertices.col(2) = third_vertex;
        _vertices.col(3) = fourth_vertex;
    }
        
    template <int dimensions_, int size_> 
    inline Simplex<dimensions_, size_>& Simplex<dimensions_, size_>::operator=(
        const Simplex<dimensions_, size_>& othe
    ) {
        _vertices = other.vertices();
        return *this;
    }
    
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline Simplex<dimensions_, size_>& Simplex<dimensions_, size_>::operator=(
        const Simplex<other_dimensions_, other_size_>& othe
    ) {
        _vertices = other.vertices();
        return *this;
    }
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::dimensions() const {return _vertices.rows();}
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::size() const {return _vertices.cols();}
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vertices&
    Simplex<dimensions_, size_>::vertices() {return _vertices;}
    
    template <int dimensions_, int size_>
    inline const typename Simplex<dimensions_, size_>::Vertices&
    Simplex<dimensions_, size_>::vertices() const {return _vertices;}
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vertex
    Simplex<dimensions_, size_>::vertex(int index) {return _vertices.col(index);}
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::ConstVertex
    Simplex<dimensions_, size_>::vertex(int index) const {return _vertices.col(index);}

    template <int dimensions_, int size_> template <class MatrixType, class VectorType>
    Simplex<MatrixType::RowsAtCompileTime, size_> Simplex<dimensions_, size_>::transformed(
        const MatrixType& matrix,
        const VectorType& vecto
    ) const {
        assertValidTransform<dimensions_>(dimensions(), matrix, vector);
        static const int new_dimensions = MatrixType::RowsAtCompileTime;
        return Simplex<new_dimensions, size_>((matrix * vertices()).colwise() + vector);
    }
    
    template <int dimensions_, int size_>
    inline double Simplex<dimensions_, size_>::length() const {
        assert(size() == 2);
        if (dimensions() == 1) {
            return vertices()(0, 1) - vertices()(0, 0);
        } else {
            return (vertex(1) - vertex(0)).norm();
        }
    }
    
    template <int dimensions_, int size_>
    double Simplex<dimensions_, size_>::area() const {
        assert(size() == 3);
        if (dimensions() == 2) {
            return (
                vertices().template rightCols<2>().colwise() - vertex(0)
            ).determinant() / 2;
        } else {
            Matrix2d temp;
            double squared_area = 0.0;
            for (int i = 0; i < dimensions() - 1; ++i) {
                for (int j = i + 1; j < dimensions(); ++j) {
                    temp << vertices().row(i).tail(2).array() - vertices()(i, 0),
                        vertices().row(j).tail(2).array() - vertices()(j, 0);
                    double determinant = temp.determinant();
                    squared_area += determinant * determinant / 4;
                }
            }
            return sqrt(squared_area);
        }
    }
    
    template <int dimensions_, int size_>
    double Simplex<dimensions_, size_>::volume() const {
        assert(size() == 4);
        if (dimensions() == 3) {
            return (
                vertices().template rightCols<3>().colwise() - vertex(0)
            ).determinant() / 6;
        } else {
            Matrix3d temp;
            double squared_volume = 0.0;
            for (int i = 0; i < dimensions() - 2; ++i) {
                for (int j = i + 1; j < dimensions() - 1; ++j) {
                    for (int k = j + 1; k < dimensions(); ++k) {
                        temp << vertices().row(i).tail(3).array() - vertices()(i, 0),
                            vertices().row(j).tail(3).array() - vertices()(j, 0),
                            vertices().row(k).tail(3).array() - vertices()(k, 0);
                        double determinant = temp.determinant();
                        squared_volume += determinant * determinant / 36;
                    }
                }
            }
            return sqrt(squared_volume);
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vecto
    Simplex<dimensions_, size_>::vector() const {
        assertCompatible<size_, 2>();
        assert(size() == 2);
        return vertex(1) - vertex(0);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vecto
    Simplex<dimensions_, size_>::centroid() const {return vertices().rowwise().mean();}
    
    namespace
    {
        inline Vector2d lineNormal(const Matrix2d& vertices) {
            return (vertices.col(1) - vertices.col(0)).unitOrthogonal();
        }

        inline Vector3d triangleNormal(const Matrix3d& vertices) {
            Matrix3d edges;
            edges.col(0) = vertices.col(1) - vertices.col(0);
            edges.col(1) = vertices.col(2) - vertices.col(1);
            edges.col(2) = vertices.col(0) - vertices.col(2);
            Matrix3d::Index longest_edge_index;
            edges.colwise().norm().maxCoeff(&longest_edge_index);
            Matrix3d::Index first_index = (longest_edge_index + 1) % 3;
            Matrix3d::Index second_index = (longest_edge_index + 2) % 3;
            return edges.col(first_index).cross(edges.col(second_index)).normalized();
        }

        inline Vector2d simplexNormal(const LineSegment2d& line_segment) {
            return lineNormal(line_segment.vertices());
        }
        
        inline Vector2d simplexNormal(const LineSegmentXd& line_segment) {
            assert(line_segment.dimensions() == 2);
            return lineNormal(line_segment.vertices());
        }
        
        inline Vector3d simplexNormal(const Triangle3d& triangle) {
            return triangleNormal(triangle.vertices());
        }
        
        inline Vector3d simplexNormal(const TriangleXd& triangle) {
            assert(triangle.dimensions() == 3);
            return triangleNormal(triangle.vertices());
        }
        
        inline VectorXd simplexNormal(const SimplexXd& simplex) {
            assert(simplex.size() == 2 || simplex.size() == 3);
            if (simplex.size() == 2) {
                assert(simplex.dimensions() == 2);
                return lineNormal(simplex.vertices());
            } else {
                assert(simplex.dimensions() == 3);
                return triangleNormal(simplex.vertices());
            }
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vecto
    Simplex<dimensions_, size_>::normal() const {
        assertCompatible<size_, dimensions_>();
        assert(size() == dimensions());
        return simplexNormal(*this);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Edge
    Simplex<dimensions_, size_>::edge(int start_index, int end_index) const {
        typename Edge::Vertices edge_vertices;
        edge_vertices.col(0) = vertex(start_index);
        edge_vertices.col(1) = vertex(end_index);
        return Edge(edge_vertices);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Face
    Simplex<dimensions_, size_>::face(int index) const {
        typename Face::Vertices face_vertices;
        Matrix<int, 1, (size_ == Dynamic ? Dynamic : size_ - 1)> indices(size() - 1);
        for (int i = 0; i < indices.size(); ++i) {indices(i) = (index + 1 + i) % size();}
        if (size() % 2 == 0 && index % 2 != 0) {indices.tail(2).reverseInPlace();}
        for (int i = 0; i < indices.size(); ++i) {
            face_vertices.col(i) = vertex(indices(i));
        }
        return Face(face_vertices);
    }

    template <int dimensions_, int size_>
    inline CoordinateSystem<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>
    Simplex<dimensions_, size_>::coordinateSystem() const {
        return CoordinateSystem<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>(
            vertex(0),
            vertices().rightCols(size() - 1).colwise() - vertex(0)
        );
    }
    
    template <int dimensions_, int size_>
    inline Matrix<Interval, dimensions_, 1> Simplex<dimensions_, size_>::bounds() const {
        return _vertices.rowwise().minCoeff().hull(_vertices.rowwise().maxCoeff());
    }
        
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline bool Simplex<dimensions_, size_>::operator==(
        const Simplex<other_dimensions_, other_size_>& othe
    ) const {
        assertCompatible<dimensions_, other_dimensions_>();
        assertCompatible<size_, other_size_>();
        assert(dimensions() == other.dimensions());
        assert(size() == other.size());
        return vertices() == other.vertices();
    }
}

#endif
