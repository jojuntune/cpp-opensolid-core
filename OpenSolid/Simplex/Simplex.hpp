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

#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int size_>
    class Simplex
    {
    public:
        typedef Matrix<Double, dimensions_, size_> Vertices;
        typedef typename Vertices::ConstColXpr Vertex;
        typedef Simplex<dimensions_, 2> Edge;
        typedef Simplex<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)> Face;
        typedef Matrix<Double, dimensions_, 1> Vector;
    private:
        Vertices _vertices;
    public:
        typedef Matrix<Interval, dimensions_, 1> Bounds;
        
        Simplex();
        
        Simplex(const Simplex<dimensions_, size_>& other);
        
        template <int other_dimensions_, int other_size_>
        Simplex(const Simplex<other_dimensions_, other_size_>& other);
        
        template <class DerivedType>
        Simplex(const EigenBase<DerivedType>& vertices);
        
        Simplex(Double first_vertex, Double second_vertex);
        
        template <class FirstDerivedType, class SecondDerivedType>
        Simplex(
            const EigenBase<FirstDerivedType>& first_vertex,
            const EigenBase<SecondDerivedType>& second_vertex
        );
        
        template <class FirstDerivedType, class SecondDerivedType, class ThirdDerivedType>
        Simplex(
            const EigenBase<FirstDerivedType>& first_vertex,
            const EigenBase<SecondDerivedType>& second_vertex,
            const EigenBase<ThirdDerivedType>& third_vertex
        );
        
        template <
            class FirstDerivedType,
            class SecondDerivedType,
            class ThirdDerivedType,
            class FourthDerivedType
        >
        Simplex(
            const EigenBase<FirstDerivedType>& first_vertex,
            const EigenBase<SecondDerivedType>& second_vertex,
            const EigenBase<ThirdDerivedType>& third_vertex,
            const EigenBase<FourthDerivedType>& fourth_vertex
        );
        
        Simplex<dimensions_, size_>& operator=(const Simplex<dimensions_, size_>& other);
        
        template <int other_dimensions_, int other_size_>
        Simplex<dimensions_, size_>& operator=(
            const Simplex<other_dimensions_, other_size_>& other
        );
        
        int dimensions() const;
        int size() const;
        
        const Vertices& vertices() const;
        Vertex vertex(int index) const;
        
        Double length() const;
        Double area() const;
        Double volume() const;
        Double hypervolume() const;
        
        Vector centroid() const;
        Vector normal() const;
        
        Edge edge(int start_index, int end_index) const;
        Face face(int index) const;
        
        CoordinateSystem<dimensions_, (size_ == Dynamic ? Dynamic : size_ - 1)>
        coordinateSystem() const;
        
        Matrix<Interval, dimensions_, 1> bounds() const;
        std::size_t hashValue() const;
        
        template <int other_dimensions_, int other_size_>
        bool operator==(const Simplex<other_dimensions_, other_size_>& other) const;
    };
    
    typedef Simplex<1, 2> LineSegment1D;
    typedef Simplex<2, 2> LineSegment2D;
    typedef Simplex<3, 2> LineSegment3D;
    typedef Simplex<4, 2> LineSegment4D;
    typedef Simplex<Dynamic, 2> LineSegmentXD;
    
    typedef Simplex<2, 3> Triangle2D;
    typedef Simplex<3, 3> Triangle3D;
    typedef Simplex<4, 3> Triangle4D;
    typedef Simplex<Dynamic, 3> TriangleXD;
    
    typedef Simplex<3, 4> Tetrahedron3D;
    typedef Simplex<4, 4> Tetrahedron4D;
    typedef Simplex<Dynamic, 4> TetrahedronXD;
    
    typedef Simplex<4, 5> Pentachoron4D;
    typedef Simplex<Dynamic, 5> PentachoronXD;
    
    typedef Simplex<Dynamic, Dynamic> SimplexXD;
    
    template <int simplex_dimensions_, int simplex_size_, int datum_dimensions_, int datum_axes_>
    Simplex<datum_dimensions_, simplex_size_> operator*(
        const Simplex<simplex_dimensions_, simplex_size_>& simplex,
        const Datum<datum_dimensions_, datum_axes_>& datum
    );
    
    template <int simplex_dimensions_, int simplex_size_, int datum_dimensions_, int datum_axes_>
    Simplex<datum_axes_, simplex_size_> operator/(
        const Simplex<simplex_dimensions_, simplex_size_>& simplex,
        const Datum<datum_dimensions_, datum_axes_>& datum
    );
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
        const Simplex<other_dimensions_, other_size_>& other
    ) : _vertices(other.vertices()) {}
        
    template <int dimensions_, int size_> template <class DerivedType>
    inline Simplex<dimensions_, size_>::Simplex(const EigenBase<DerivedType>& vertices) :
        _vertices(vertices) {}
        
    template <int dimensions_, int size_>
    inline Simplex<dimensions_, size_>::Simplex(Double first_vertex, Double second_vertex) {
        static_assert(
            (dimensions_ == 1 || dimensions_ == Dynamic) && (size_ == 2 || size_ == Dynamic),
            "Only 1D line segments can be constructed from two Doubles"
        );
        _vertices.resize(1, 2);
        _vertices(0) = first_vertex;
        _vertices(1) = second_vertex;
    }

    template <int dimensions_, int size_>
    template <class FirstDerivedType, class SecondDerivedType>
    inline Simplex<dimensions_, size_>::Simplex(
        const EigenBase<FirstDerivedType>& first_vertex,
        const EigenBase<SecondDerivedType>& second_vertex
    ) {
        _vertices.resize(first_vertex.size(), 2);
        _vertices << first_vertex.derived(), second_vertex.derived();
    }
        
    template <int dimensions_, int size_>
    template <class FirstDerivedType, class SecondDerivedType, class ThirdDerivedType>
    inline Simplex<dimensions_, size_>::Simplex(
        const EigenBase<FirstDerivedType>& first_vertex,
        const EigenBase<SecondDerivedType>& second_vertex,
        const EigenBase<ThirdDerivedType>& third_vertex
    ) {
        _vertices.resize(first_vertex.size(), 3);
        _vertices << first_vertex.derived(), second_vertex.derived(), third_vertex.derived();
    }
        
    template <int dimensions_, int size_> 
    template <
        class FirstDerivedType,
        class SecondDerivedType,
        class ThirdDerivedType,
        class FourthDerivedType
    >
    inline Simplex<dimensions_, size_>::Simplex(
        const EigenBase<FirstDerivedType>& first_vertex,
        const EigenBase<SecondDerivedType>& second_vertex,
        const EigenBase<ThirdDerivedType>& third_vertex,
        const EigenBase<FourthDerivedType>& fourth_vertex
    ) {
        _vertices.resize(first_vertex.size(), 4);
        _vertices << first_vertex.derived(), second_vertex.derived(), third_vertex.derived(),
            fourth_vertex.derived();
    }
        
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
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::dimensions() const {return _vertices.rows();}
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::size() const {return _vertices.cols();}
    
    template <int dimensions_, int size_>
    inline const typename Simplex<dimensions_, size_>::Vertices&
    Simplex<dimensions_, size_>::vertices() const {return _vertices;}
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vertex
    Simplex<dimensions_, size_>::vertex(int index) const {return _vertices.col(index);}
    
    template <int dimensions_, int size_>
    inline Double Simplex<dimensions_, size_>::length() const {
        assert(size() == 2);
        if (dimensions() == 1) {
            return vertices()(0, 1) - vertices()(0, 0);
        } else {
            return (vertex(1) - vertex(0)).norm();
        }
    }
    
    template <int dimensions_, int size_>
    inline Double Simplex<dimensions_, size_>::area() const {
        assert(size() == 3);
        if (dimensions() == 2) {
            return (
                vertices().template rightCols<2>().colwise() - vertex(0)
            ).determinant() / 2;
        } else {
            Matrix2D temp;
            Double squared_area = 0.0;
            for (int i = 0; i < dimensions() - 1; ++i) {
                for (int j = i + 1; j < dimensions(); ++j) {
                    temp << vertices().row(i).tail(2).array() - vertices()(i, 0),
                        vertices().row(j).tail(2).array() - vertices()(j, 0);
                    Double determinant = temp.determinant();
                    squared_area += determinant * determinant / 4;
                }
            }
            return sqrt(squared_area);
        }
    }
    
    template <int dimensions_, int size_>
    inline Double Simplex<dimensions_, size_>::volume() const {
        assert(size() == 4);
        if (dimensions() == 3) {
            return (
                vertices().template rightCols<3>().colwise() - vertex(0)
            ).determinant() / 6;
        } else {
            Matrix3D temp;
            Double squared_volume = 0.0;
            for (int i = 0; i < dimensions() - 2; ++i) {
                for (int j = i + 1; j < dimensions() - 1; ++j) {
                    for (int k = j + 1; k < dimensions(); ++k) {
                        temp << vertices().row(i).tail(3).array() - vertices()(i, 0),
                            vertices().row(j).tail(3).array() - vertices()(j, 0),
                            vertices().row(k).tail(3).array() - vertices()(k, 0);
                        Double determinant = temp.determinant();
                        squared_volume += determinant * determinant / 36;
                    }
                }
            }
            return sqrt(squared_volume);
        }
    }
    
    template <int dimensions_, int size_>
    inline Double Simplex<dimensions_, size_>::hypervolume() const {
        assert(size() == 5);
        if (dimensions() == 4) {
            return (
                vertices().template rightCols<4>.colwise() - vertex(0)
            ).determinant() / 24;
        } else {
            Matrix4D temp;
            Double squared_hypervolume = 0.0;
            for (int i = 0; i < dimensions() - 3; ++i) {
                for (int j = i + 1; j < dimensions() - 2; ++j) {
                    for (int k = j + 1; k < dimensions() - 1; ++k) {
                        for (int l = k + 1; l < dimensions(); ++l) {
                            temp << vertices().row(i).tail(4).array() - vertices()(i, 0),
                                vertices().row(j).tail(4).array() - vertices()(j, 0),
                                vertices().row(k).tail(4).array() - vertices()(k, 0),
                                vertices().row(l).tail(4).array() - vertices()(l, 0);
                            Double determinant = temp.determinant();
                            squared_hypervolume += determinant * determinant / 576;
                        }
                    }
                }
            }
            return sqrt(squared_hypervolume);
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vector
    Simplex<dimensions_, size_>::centroid() const {return vertices().rowwise().mean();}
    
    namespace
    {
        inline Vector2D simplexNormal(const LineSegment2D& line_segment) {
            return (line_segment.vertex(1) - line_segment.vertex(0)).unitOrthogonal();
        }
        
        inline Vector2D simplexNormal(const LineSegmentXD& line_segment) {
            assert(line_segment.dimensions() == 2);
            return Vector2D(line_segment.vertex(1) - line_segment.vertex(0)).unitOrthogonal();
        }
        
        inline Vector3D simplexNormal(const Triangle3D& triangle) {
            Vector3D first_edge = triangle.vertex(1) - triangle.vertex(0);
            Vector3D second_edge = triangle.vertex(2) - triangle.vertex(0);
            return first_edge.cross(second_edge).normalized();
        }
        
        inline Vector3D simplexNormal(const TriangleXD& triangle) {
            assert(triangle.dimensions() == 3);
            Vector3D first_edge = triangle.vertex(1) - triangle.vertex(0);
            Vector3D second_edge = triangle.vertex(2) - triangle.vertex(0);
            return first_edge.cross(second_edge).normalized();
        }
        
        inline VectorXD simplexNormal(const SimplexXD& simplex) {
            assert(simplex.size() == 2 || simplex.size() == 3);
            if (simplex.size() == 2) {
                assert(simplex.dimensions() == 2);
                return Vector2D(simplex.vertex(1) - simplex.vertex(0)).unitOrthogonal();
            } else {
                assert(simplex.dimensions() == 3);
                Vector3D first_edge = simplex.vertex(1) - simplex.vertex(0);
                Vector3D second_edge = simplex.vertex(2) - simplex.vertex(0);
                return first_edge.cross(second_edge).normalized();
            }
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vector
    Simplex<dimensions_, size_>::normal() const {
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
    
    template <int dimensions_, int size_>
    inline std::size_t Simplex<dimensions_, size_>::hashValue() const {
        return argument.vertices().hashValue();
    }
        
    template <int dimensions_, int size_> template <int other_dimensions_, int other_size_>
    inline bool Simplex<dimensions_, size_>::operator==(
        const Simplex<other_dimensions_, other_size_>& other
    ) const {
        assert(dimensions() == other.dimensions());
        assert(size() == other.size());
        return vertices() == other.vertices();
    }
    
    template <int simplex_dimensions_, int simplex_size_, int datum_dimensions_, int datum_axes_>
    inline Simplex<datum_dimensions_, simplex_size_> operator*(
        const Simplex<simplex_dimensions_, simplex_size_>& simplex,
        const Datum<datum_dimensions_, datum_axes_>& datum
    ) {return Simplex<datum_dimensions_, simplex_size_>(simplex.vertices() * datum);}
    
    template <int simplex_dimensions_, int simplex_size_, int datum_dimensions_, int datum_axes_>
    inline Simplex<datum_axes_, simplex_size_> operator/(
        const Simplex<simplex_dimensions_, simplex_size_>& simplex,
        const Datum<datum_dimensions_, datum_axes_>& datum
    ) {return Simplex<datum_axes_, simplex_size_>(simplex.vertices() / datum);}
}

#endif
