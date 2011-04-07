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

#ifndef OPENSOLID__MESH_HPP
#define OPENSOLID__MESH_HPP

#include <opensolid/collection/Set.hpp>
#include "VertexData.hpp"
#include "Simplex.hpp"

namespace opensolid
{
    template <int dimensions_, int order_>
    class Mesh
    {
    private:
        VertexData::Pointer _vertices;
    public:
        template<class DerivedType>
        Mesh(const EigenBase<DerivedType>& vertices);
        
        template<class DerivedType>
        Mesh(const CollectionBase<DerivedType>& vertices);
        
        const MatrixXd& vertices() const;
        
        int dimensions() const;
        int order() const;
        
        const MatrixXd::ColXpr vertex(int index) const;
        const MatrixXi::ColXpr indices(int index) const;
        
        VectorXI bounds() const;
    };
    
    template <int dimensions_, int order_>
    struct Bounds<Mesh>
    {
        typedef Matrix<Interval, dimensions_, 1> Type;
        static Type bounds(const Mesh<dimensions_, order_>& mesh);
    };
}

////////// Implementation //////////

namespace opensolid
{
    // inline SimplexData::SimplexData(const MatrixXd& vertices_) : vertices(vertices_) {}
    // 
    // inline Simplex::Simplex(const MatrixXd& vertices) : _data(new SimplexData(vertices)) {}
    // 
    // inline const MatrixXd& Simplex::vertices() const {return _data->vertices;}
    // 
    // inline int Simplex::dimensions() const {return vertices().rows();}
    // 
    // inline int Simplex::size() const {return vertices().cols();}
    // 
    // inline const MatrixXd::ColXpr Simplex::vertex(int index) const {
    //     assert(index >= 0 && index < size());
    //     return vertices().col(index);
    // }
    // 
    // inline VectorXI Simplex::bounds() const {
    //     VectorXI result = vertex(0).cast<Interval>();
    //     for (int i = 1; i < size(); ++i) {result = result.hull(vertex(i));}
    //     return result;
    // }
    // 
    // inline VectorXI Bounds<Simplex>::bounds(const Simplex& simplex) {return simplex.bounds();}
}

#endif
