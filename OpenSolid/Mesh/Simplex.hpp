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
        typedef Matrix<Interval, dimensions_, 1> BoundsType;
    private:
        VerticesType _vertices;
    public:
        template <class DerivedType>
        Simplex(const EigenBase<DerivedType>& vertices);
        
        int dimensions() const;
        int size() const;
        
        const VerticesType& vertices() const;
        VertexType vertex(int index) const;
        
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
