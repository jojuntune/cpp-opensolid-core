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

#include <OpenSolid/Value/Matrix.hpp>
#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int size_>
    class Simplex
    {
    public:
        typedef Matrix<double, dimensions_, size_> VerticesType;
        typedef typename VerticesType::ConstColXpr VertexType;
        typedef Simplex<dimensions_, 2> EdgeType;
        typedef Simplex<dimensions_, size_ == Dynamic ? Dynamic : size_ - 1> FaceType;
        typedef Matrix<Interval, dimensions_, 1> BoundsType;
        typedef Matrix<double, dimensions_, 1> VectorType;
    private:
        VerticesType _vertices;
    public:
        Simplex();
        
        template <class DerivedType>
        Simplex(const EigenBase<DerivedType>& vertices);
        
        template <class FirstVertexType, class SecondVertexType>
        Simplex(const FirstVertexType& first_vertex, const SecondVertexType& second_vertex);
        
        template <class FirstVertexType, class SecondVertexType, class ThirdVertexType>
        Simplex(
            const FirstVertexType& first_vertex,
            const SecondVertexType& second_vertex,
            const ThirdVertexType& third_vertex
        );
        
        template <
            class FirstVertexType,
            class SecondVertexType,
            class ThirdVertexType,
            class FourthVertexType
        >
        Simplex(
            const FirstVertexType& first_vertex,
            const SecondVertexType& second_vertex,
            const ThirdVertexType& third_vertex,
            const FourthVertexType& fourth_vertex
        );
        
        int dimensions() const;
        int size() const;
        
        const VerticesType& vertices() const;
        VertexType vertex(int index) const;
        
        double length() const;
        double area() const;
        double volume() const;
        double hypervolume() const;
        
        VectorType centroid() const;
        VectorType normal() const;
        
        EdgeType edge(int start_index, int end_index) const;
        FaceType face(int index) const;
        
        BoundsType bounds() const;
    };
    
    typedef Simplex<1, 2> LineSegment1d;
    typedef Simplex<2, 2> LineSegment2d;
    typedef Simplex<3, 2> LineSegment3d;
    typedef Simplex<4, 2> LineSegment4d;
    typedef Simplex<Dynamic, 2> LineSegmentXd;
    
    typedef Simplex<2, 3> Triangle2d;
    typedef Simplex<3, 3> Triangle3d;
    typedef Simplex<4, 3> Triangle4d;
    typedef Simplex<Dynamic, 3> TriangleXd;
    
    typedef Simplex<3, 4> Tetrahedron3d;
    typedef Simplex<4, 4> Tetrahedron4d;
    typedef Simplex<Dynamic, 4> TetrahedronXd;
    
    typedef Simplex<4, 5> Pentachoron4d;
    typedef Simplex<Dynamic, 5> PentachoronXd;
    
    typedef Simplex<Dynamic, Dynamic> SimplexXd;
    
    template <int dimensions_, int size_>
    struct Bounds<Simplex<dimensions_, size_> >
    {
        typedef typename Simplex<dimensions_, size_>::BoundsType Type;
        static Type bounds(const Simplex<dimensions_, size_>& simplex);
    };
    
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
        
    template <int dimensions_, int size_> template <class DerivedType>
    inline Simplex<dimensions_, size_>::Simplex(const EigenBase<DerivedType>& vertices) :
        _vertices(vertices) {}
        
    template <int dimensions_, int size_> template <class FirstVertexType, class SecondVertexType>
    inline Simplex<dimensions_, size_>::Simplex(
        const FirstVertexType& first_vertex,
        const SecondVertexType& second_vertex
    ) {
        _vertices.resize(first_vertex.size(), 2);
        _vertices << first_vertex, second_vertex;
    }
    
    template <int dimensions_, int size_>
    template <class FirstVertexType, class SecondVertexType, class ThirdVertexType>
    inline Simplex<dimensions_, size_>::Simplex(
        const FirstVertexType& first_vertex,
        const SecondVertexType& second_vertex,
        const ThirdVertexType& third_vertex
    ) {
        _vertices.resize(first_vertex.size(), 3);
        _vertices << first_vertex, second_vertex, third_vertex;
    }
    
    template <int dimensions_, int size_> 
    template <
        class FirstVertexType,
        class SecondVertexType,
        class ThirdVertexType,
        class FourthVertexType
    >
    inline Simplex<dimensions_, size_>::Simplex(
        const FirstVertexType& first_vertex,
        const SecondVertexType& second_vertex,
        const ThirdVertexType& third_vertex,
        const FourthVertexType& fourth_vertex
    ) {
        _vertices.resize(first_vertex.size(), 4);
        _vertices << first_vertex, second_vertex, third_vertex, fourth_vertex;
    }
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::dimensions() const {return _vertices.rows();}
    
    template <int dimensions_, int size_>
    inline int Simplex<dimensions_, size_>::size() const {return _vertices.cols();}
    
    template <int dimensions_, int size_>
    inline const typename Simplex<dimensions_, size_>::VerticesType&
    Simplex<dimensions_, size_>::vertices() const {return _vertices;}
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::VertexType
    Simplex<dimensions_, size_>::vertex(int index) const {return _vertices.col(index);}
    
    template <int dimensions_, int size_>
    inline double Simplex<dimensions_, size_>::length() const {
        assert(size() == 2);
        if (dimensions() == 1) {
            return vertices()(0, 1) - vertices()(0, 0);
        } else {
            return (vertices().col(1) - vertices().col(0)).norm();
        }
    }
    
    template <int dimensions_, int size_>
    inline double Simplex<dimensions_, size_>::area() const {
        assert(size() == 3);
        if (dimensions() == 2) {
            return (vertices().rightCols<2>().colwise() - vertices().col(0)).determinant() / 2;
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
    inline double Simplex<dimensions_, size_>::volume() const {
        assert(size() == 4);
        if (dimensions() == 3) {
            return (vertices().rightCols<3>().colwise() - vertices().col(0)).determinant() / 6;
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
    inline double Simplex<dimensions_, size_>::hypervolume() const {
        assert(size() == 5);
        if (dimensions() == 4) {
            return (vertices().rightCols<4>.colwise() - vertices().col(0)).determinant() / 24;
        } else {
            Matrix4d temp;
            double squared_hypervolume = 0.0;
            for (int i = 0; i < dimensions() - 3; ++i) {
                for (int j = i + 1; j < dimensions() - 2; ++j) {
                    for (int k = j + 1; k < dimensions() - 1; ++k) {
                        for (int l = k + 1; l < dimensions(); ++l) {
                            temp << vertices().row(i).tail(4).array() - vertices()(i, 0),
                                vertices().row(j).tail(4).array() - vertices()(j, 0),
                                vertices().row(k).tail(4).array() - vertices()(k, 0),
                                vertices().row(l).tail(4).array() - vertices()(l, 0);
                            double determinant = temp.determinant();
                            squared_hypervolume += determinant * determinant / 576;
                        }
                    }
                }
            }
            return sqrt(squared_hypervolume);
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::VectorType
    Simplex<dimensions_, size_>::centroid() const {return vertices().rowwise().mean();}
    
    inline Vector2d simplexNormal(const LineSegment2d& line_segment) {
        return (line_segment.vertex(1) - line_segment.vertex(0)).unitOrthogonal();
    }
    
    inline Vector2d simplexNormal(const LineSegmentXd& line_segment) {
        assert(line_segment.dimensions() == 2);
        return Vector2d(line_segment.vertex(1) - line_segment.vertex(0)).unitOrthogonal();
    }
    
    inline Vector3d simplexNormal(const Triangle3d& triangle) {
        Vector3d first_edge = triangle.vertex(1) - triangle.vertex(0);
        Vector3d second_edge = triangle.vertex(2) - triangle.vertex(0);
        return first_edge.cross(second_edge).normalized();
    }
    
    inline Vector3d simplexNormal(const TriangleXd& triangle) {
        assert(triangle.dimensions() == 3);
        Vector3d first_edge = triangle.vertex(1) - triangle.vertex(0);
        Vector3d second_edge = triangle.vertex(2) - triangle.vertex(0);
        return first_edge.cross(second_edge).normalized();
    }
    
    inline VectorXd simplexNormal(const SimplexXd& simplex) {
        assert(simplex.size() == 2 || simplex.size() == 3);
        if (simplex.size() == 2) {
            assert(simplex.dimensions() == 2);
            return Vector2d(simplex.vertex(1) - simplex.vertex(0)).unitOrthogonal();
        } else {
            assert(simplex.dimensions() == 3);
            Vector3d first_edge = simplex.vertex(1) - simplex.vertex(0);
            Vector3d second_edge = simplex.vertex(2) - simplex.vertex(0);
            return first_edge.cross(second_edge).normalized();
        }
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::VectorType
    Simplex<dimensions_, size_>::normal() const {
        assert(size() == dimensions());
        return simplexNormal(*this);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::EdgeType
    Simplex<dimensions_, size_>::edge(int start_index, int end_index) const {
        typename EdgeType::VerticesType edge_vertices;
        edge_vertices.col(0) = vertices().col(start_index);
        edge_vertices.col(1) = vertices().col(end_index);
        return EdgeType(edge_vertices);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::FaceType
    Simplex<dimensions_, size_>::face(int index) const {
        typename FaceType::VerticesType face_vertices;
        Matrix<int, 1, size_ == Dynamic ? Dynamic : size_ - 1> indices(size() - 1);
        for (int i = 0; i < indices.size(); ++i) {indices(i) = (index + 1 + i) % size();}
        if (size() % 2 == 0 && index % 2 != 0) {indices.tail(2).reverseInPlace();}
        for (int i = 0; i < indices.size(); ++i) {
            face_vertices.col(i) = vertices().col(indices(i));
        }
        return FaceType(face_vertices);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::BoundsType
    Simplex<dimensions_, size_>::bounds() const {
        return _vertices.rowwise().minCoeff().hull(_vertices.rowwise().maxCoeff());
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::BoundsType
    Bounds<Simplex<dimensions_, size_> >::bounds(
        const Simplex<dimensions_, size_>& simplex
    ) {return simplex.bounds();}
    
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
