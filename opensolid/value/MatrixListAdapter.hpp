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

#ifndef OPENSOLID__MATRIXLISTADAPTER_HPP
#define OPENSOLID__MATRIXLISTADAPTER_HPP

#include <opensolid/collection/FixedSizeCollection.hpp>
#include <opensolid/collection/IteratorRange.hpp>

namespace opensolid
{
    template <class DerivedType>
    class MatrixListAdapter : public FixedSizeCollection<MatrixListAdapter<DerivedType> >
    {
    private:
        const DerivedType& _matrix;
    public:
        typedef typename DerivedType::ConstColIterator Iterator;
        
        MatrixListAdapter(const DerivedType& matrix);
        
        int size() const;
        bool empty() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        typename Bounds<typename DerivedType::ColXpr::PlainObject>::Type bounds() const;
        
        Iterator begin() const;
        Iterator end() const;
        
        const typename DerivedType::ColXpr front() const;
        const typename DerivedType::ColXpr back() const;
        
        const typename DerivedType::ColXpr operator[](int index) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class DerivedType>
    inline MatrixListAdapter<DerivedType>::MatrixListAdapter(const DerivedType& matrix) :
        _matrix(matrix) {}
    
    template <class DerivedType>
    inline int MatrixListAdapter<DerivedType>::size() const {return _matrix.cols();}
    
    template <class DerivedType>
    inline bool MatrixListAdapter<DerivedType>::empty() const {return _matrix.cols() == 0;}
    
    template <class DerivedType> template <class VisitorType>
    inline void MatrixListAdapter<DerivedType>::visit(const VisitorType& visitor) const {
        IteratorRange<Iterator>(begin(), end()).visit(visitor);
    }
    
    template <class DerivedType>
    inline typename Bounds<typename DerivedType::ColXpr::PlainObject>::Type
    MatrixListAdapter<DerivedType>::bounds() const {
        typename Bounds<typename DerivedType::ColXpr::PlainObject>::Type result =
            _matrix.col(0).template cast<Interval>();
        for (int i = 1; i < _matrix.cols(); ++i) {
            result = result.hull(_matrix.col(i));
        }
        return result;
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColIterator MatrixListAdapter<DerivedType>::begin() const {
        return _matrix.colBegin();
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColIterator MatrixListAdapter<DerivedType>::end() const {
        return _matrix.colEnd();
    }
    
    template <class DerivedType>
    inline const typename DerivedType::ColXpr MatrixListAdapter<DerivedType>::front() const {
        return _matrix.col(0);
    }
    
    template <class DerivedType>
    inline const typename DerivedType::ColXpr MatrixListAdapter<DerivedType>::back() const {
        return _matrix.col(_matrix.cols() - 1);
    }
    
    template <class DerivedType>
    inline const typename DerivedType::ColXpr MatrixListAdapter<DerivedType>::operator[](
        int index
    ) const {return _matrix.col(index);}
    
}

#endif
