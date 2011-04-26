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

#ifndef OPENSOLID__VERTEXDATA_HPP
#define OPENSOLID__VERTEXDATA_HPP

#include <OpenSolid/Common/ReferenceCountedBase.hpp>
#include <OpenSolid/Collection/CollectionBase.hpp>
#include <OpenSolid/Value/Matrix.hpp>

namespace opensolid
{
    template <int dimensions_>
    class VertexData : public ReferenceCountedBase<VertexData<dimensions_> >
    {
    public:
        typedef Matrix<double, dimensions_, Dynamic> MatrixType;
        typedef Matrix<double, dimensions_, 1> VectorType;
    private:
        MatrixType _matrix;
    public:
        template <class DerivedType>
        VertexData(const DenseBase<DerivedType>& matrix);
        
        template <class DerivedType>
        VertexData(const FixedSizeCollection<DerivedType>& collection);
        
        template <class DerivedType>
        VertexData(const CollectionBase<DerivedType>& collection);
        
        const MatrixType& matrix();
    };
    
    template <>
    class VertexData<Dynamic> : public ReferenceCountedBase<VertexData<Dynamic> >
    {
    public:
        typedef MatrixXd MatrixType;
        typedef VectorXd VectorType;
    private:
        MatrixXd _matrix;
    public:
        template <class DerivedType>
        VertexData(const DenseBase<DerivedType>& matrix);
        
        template <class OtherVectorType>
        VertexData(const List<OtherVectorType>& vectors);
        
        template <class DerivedType>
        VertexData(const CollectionBase<DerivedType>& collection);
        
        const MatrixXd& matrix();
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int dimensions_> template <class DerivedType>
    inline VertexData<dimensions_>::VertexData(const DenseBase<DerivedType>& matrix) :
        _matrix(matrix) {}
    
    template <int dimensions_> template <class DerivedType>
    inline VertexData<dimensions_>::VertexData(const FixedSizeCollection<DerivedType>& vectors) {
        _matrix.resize(dimensions_, vectors.size());
        vectors.copy(_matrix.colBegin());
    }
    
    template <int dimensions> template <class DerivedType>
    inline VertexData<dimensions>::VertexData(const CollectionBase<DerivedType>& vectors) {
        List<VectorType> list(collection.derived());
        _matrix.resize(dimensions_, list.size());
        list.copy(_matrix.colBegin());
    }
    
    template <int dimensions_>
    inline const typename VertexData<dimensions_>::MatrixType& VertexData<dimensions_>::matrix() {
        return _matrix;
    }
    
    template <> template <class DerivedType>
    inline VertexData<Dynamic>::VertexData(const DenseBase<DerivedType>& matrix) :
        _matrix(matrix) {}
    
    template <> template <class OtherVectorType>
    inline VertexData<Dynamic>::VertexData(const List<OtherVectorType>& vectors) {
        _matrix.resize(vectors.front().size(), vectors.size());
        vectors.copy(_matrix.colBegin());
    }
    
    template <> template <class DerivedType>
    inline VertexData<Dynamic>::VertexData(const CollectionBase<DerivedType>& vectors) {
        List<VectorType> list(collection.derived());
        _matrix.resize(list.front().size(), list.size());
        list.copy(_matrix.colBegin());
    }
    
    template <>
    inline const typename VertexData<Dynamic>::MatrixType& VertexData<dimensions>::matrix() {
        return _matrix;
    }
}

#endif
