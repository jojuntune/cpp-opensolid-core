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
    private:
        VerticesType _vertices;
    public:
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
        
        EdgeType edge(int index) const;
        FaceType face(int index) const;
        
        BoundsType bounds() const;
    };
    
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
    
    template<int dimensions_, int size_>
    struct Bounds<Simplex<dimensions_, size_> >
    {
        typedef typename Simplex<dimensions_, size_>::BoundsType Type;
        static Type bounds(const Simplex<dimensions_, size_>& simplex);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
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
    inline typename Simplex<dimensions_, size_>::EdgeType
    Simplex<dimensions_, size_>::edge(int index) const {
        EdgeType::VerticesType edge_vertices;
        edge_vertices.col(0) = vertices().col(index);
        edge_vertices.col(1) = vertices().col((index + 1) % size());
        return EdgeType(edge_vertices);
    }
    
    template <int dimensions_, int size_>
    inline typename Simplex<dimensions_, size_>::FaceType
    Simplex<dimensions_, size_>::face(int index) const {
        FaceType::VerticesType face_vertices;
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
}

#endif
