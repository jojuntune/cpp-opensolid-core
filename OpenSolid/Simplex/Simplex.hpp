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

#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/geometry.hpp>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int size_>
    class Simplex
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
        
        template <class DerivedType>
        Simplex(const EigenBase<DerivedType>& vertices);
        
        Simplex(double first_vertex, double second_vertex);
        
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
        
        Vertices& vertices();
        const Vertices& vertices() const;

        Vertex vertex(int index);
        ConstVertex vertex(int index) const;
        
        double length() const;
        double area() const;
        double volume() const;
        double hypervolume() const;
        
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

namespace std
{
    template <int dimensions_, int size_>
    struct hash<OpenSolid::Simplex<dimensions_, size_>>
    {
        size_t operator()(const OpenSolid::Simplex<dimensions_, size_>& argument) const;
    };
}

namespace boost
{
    template <int dimensions_, int size_>
    struct hash<OpenSolid::Simplex<dimensions_, size_>> :
        public std::hash<OpenSolid::Simplex<dimensions_, size_>>
    {
    };

    namespace geometry
    {
        namespace traits
        {
            template <>
            struct tag<OpenSolid::LineSegment2d>
            {
                typedef segment_tag type;
            };

            template <>
            struct tag<OpenSolid::LineSegment3d>
            {
                typedef segment_tag type;
            };

            template <>
            struct point_type<OpenSolid::LineSegment2d>
            {
                typedef Eigen::Vector2d type;
            };

            template <>
            struct point_type<OpenSolid::LineSegment3d>
            {
                typedef Eigen::Vector3d type;
            };

            template <std::size_t index_, std::size_t dimension_>
            struct indexed_access<OpenSolid::LineSegment2d, index_, dimension_>
            {
                static double get(const OpenSolid::LineSegment2d& argument);
                static inline void set(OpenSolid::LineSegment2d& argument, double value);
            };

            template <std::size_t index_, std::size_t dimension_>
            struct indexed_access<OpenSolid::LineSegment3d, index_, dimension_>
            {
                static double get(const OpenSolid::LineSegment3d& argument);
                static inline void set(OpenSolid::LineSegment3d& argument, double value);
            };
        }
    }
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
    inline Simplex<dimensions_, size_>::Simplex(double first_vertex, double second_vertex) {
        static_assert(
            (dimensions_ == 1 || dimensions_ == Dynamic) && (size_ == 2 || size_ == Dynamic),
            "Only 1D line segments can be constructed from two doubles"
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
    inline double Simplex<dimensions_, size_>::area() const {
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
    inline double Simplex<dimensions_, size_>::volume() const {
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
    inline double Simplex<dimensions_, size_>::hypervolume() const {
        assert(size() == 5);
        if (dimensions() == 4) {
            return (
                vertices().template rightCols<4>.colwise() - vertex(0)
            ).determinant() / 24;
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
    inline typename Simplex<dimensions_, size_>::Vector
    Simplex<dimensions_, size_>::vector() const {
        static_assert(
            size_ == 2 || size_ == Dynamic,
            "Simplex::vector() only valid for line segments"
        );
        assert(size() == 2 && "Simplex::vector() only valid for line segments");
        return vertex(1) - vertex(0);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::Vector
    Simplex<dimensions_, size_>::centroid() const {return vertices().rowwise().mean();}
    
    namespace
    {
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

namespace std
{
    template <int dimensions_, int size_>
    inline size_t hash<OpenSolid::Simplex<dimensions_, size_>>::operator()(
        const OpenSolid::Simplex<dimensions_, size_>& argument
    ) const {
        return hash<typename OpenSolid::Simplex<dimensions_, size_>::Vertices>()(
            argument.vertices()
        );
    }
}

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template <std::size_t index_, std::size_t dimension_>
            double indexed_access<OpenSolid::LineSegment2d, index_, dimension_>::get(
                const OpenSolid::LineSegment2d& argument
            ) {return argument.vertex(index_)(dimension_);}

            template <std::size_t index_, std::size_t dimension_>
            void indexed_access<OpenSolid::LineSegment2d, index_, dimension_>::set(
                OpenSolid::LineSegment2d& argument,
                double value
            ) {argument.vertex(index_)(dimension_) = value;}

            template <std::size_t index_, std::size_t dimension_>
            double indexed_access<OpenSolid::LineSegment3d, index_, dimension_>::get(
                const OpenSolid::LineSegment3d& argument
            ) {return argument.vertex(index_)(dimension_);}

            template <std::size_t index_, std::size_t dimension_>
            void indexed_access<OpenSolid::LineSegment3d, index_, dimension_>::set(
                OpenSolid::LineSegment3d& argument,
                double value
            ) {argument.vertex(index_)(dimension_) = value;}
        }
    }
}

#endif
