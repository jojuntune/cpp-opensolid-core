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

#include "Mesh.hpp"

namespace opensolid
{
    class Simplex
    {
    private:
        Mesh _mesh;
        int _simplex_index;
    public:
        Simplex(const Mesh& mesh, int index);
        
        const Mesh& mesh() const;
        int index() const;
        
        //const MatrixXd& vertices() const;
        
        int dimensions() const;
        int order() const;
        
        const MatrixXd::ColXpr vertex(int index) const;
        VectorXI bounds() const;
    };
    
    template<>
    struct Bounds<Simplex>
    {
        typedef VectorXI Type;
        static VectorXI bounds(const Simplex& simplex);
    };
}

////////// Implementation //////////

namespace opensolid
{
    // inline Simplex::Simplex(const Mesh& mesh, int index)
    // : _mesh(mesh), _index(index) {}
    // 
    // //inline const MatrixXd& Simplex::vertices() const {return _data->vertices;}
    // 
    // inline const Mesh& Simplex::mesh() const {return _mesh;}
    // 
    // inline int Simplex::index() const {return _index;}
    // 
    // inline int Simplex::dimensions() const {return mesh().dimensions();}
    // 
    // inline int Simplex::order() const {return mesh().order();}
    // 
    // inline const MatrixXd::ColXpr Simplex::vertex(int vertex_index) const {
    //     assert(index >= 0 && vertex_index < size());
    //     return mesh().vertex(mesh().indices(index)(vertex_index));
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
