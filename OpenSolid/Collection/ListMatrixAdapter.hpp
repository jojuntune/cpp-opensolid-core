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

#ifndef OPENSOLID__LISTMATRIXADAPTER_HPP
#define OPENSOLID__LISTMATRIXADAPTER_HPP

#include <OpenSolid/Value/Matrix.hpp>

namespace OpenSolid
{
    template <class Type>
    class ListMatrixAdapter;
}

namespace Eigen
{
    namespace internal
    {
        template <class Type>
        struct traits<OpenSolid::ListMatrixAdapter<Type> >
        {
            typedef typename Type::Scalar Scalar;
            typedef Dense StorageKind;
            typedef int Index;
            typedef MatrixXpr XprKind;
            
            static const int RowsAtCompileTime = Type::RowsAtCompileTime;
            static const int ColsAtCompileTime = Dynamic;
            static const int MaxRowsAtCompileTime = Type::MaxRowsAtCompileTime;
            static const int MaxColsAtCompileTime = Dynamic;
            static const int Flags = NestByRefBit;
            static const int CoeffReadCost = 2;
        };
    }
}

namespace OpenSolid
{
    template <class ItemType>
    struct ListMatrixAdapterType
    {
        typedef ListMatrixAdapter<ItemType> Type;
    };
    
    template <>
    struct ListMatrixAdapterType<double>
    {
        typedef Map<const RowVectorXd> Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector2d>
    {
        typedef Map<const Matrix<double, 2, Dynamic> > Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector3d>
    {
        typedef Map<const Matrix<double, 3, Dynamic> > Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector4d>
    {
        typedef Map<const Matrix<double, 4, Dynamic> > Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Interval>
    {
        typedef Map<const RowVectorXI> Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector2I>
    {
        typedef Map<const Matrix<Interval, 2, Dynamic> > Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector3I>
    {
        typedef Map<const Matrix<Interval, 3, Dynamic> > Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector4I>
    {
        typedef Map<const Matrix<Interval, 4, Dynamic> > Type;
    };
    
    template <class Type>
    class ListMatrixAdapter : public MatrixBase<ListMatrixAdapter<Type> >
    {
    private:
        const List<Type>& _list;
    public:
        typedef MatrixBase<ListMatrixAdapter<Type> > Base;
        EIGEN_DENSE_PUBLIC_INTERFACE(ListMatrixAdapter<Type>)
        
        ListMatrixAdapter(const List<Type>& list);
        ListMatrixAdapter(const ListMatrixAdapter<Type>& other);
        
        int rows() const;
        int cols() const;
        
        typename Type::Scalar coeff(int row, int col) const;
    };
    
    template <class Type>
    ListMatrixAdapter<Type> listMatrixAdapter(const List<Type>& list);
    
    Map<const RowVectorXd> listMatrixAdapter(const List<double>& list);
    Map<const Matrix<double, 2, Dynamic> > listMatrixAdapter(const List<Vector2d>& list);
    Map<const Matrix<double, 3, Dynamic> > listMatrixAdapter(const List<Vector3d>& list);
    Map<const Matrix<double, 4, Dynamic> > listMatrixAdapter(const List<Vector4d>& list);
    Map<const RowVectorXI> listMatrixAdapter(const List<Interval>& list);
    Map<const Matrix<Interval, 2, Dynamic> > listMatrixAdapter(const List<Vector2I>& list);
    Map<const Matrix<Interval, 3, Dynamic> > listMatrixAdapter(const List<Vector3I>& list);
    Map<const Matrix<Interval, 4, Dynamic> > listMatrixAdapter(const List<Vector4I>& list);
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline ListMatrixAdapter<Type>::ListMatrixAdapter(const List<Type>& list) : _list(list) {}
    
    template <class Type>
    inline ListMatrixAdapter<Type>::ListMatrixAdapter(const ListMatrixAdapter<Type>& other) :
        _list(other._list) {}
    
    template <class Type>
    inline int ListMatrixAdapter<Type>::rows() const {return _list.front().size();}
    
    template <class Type>
    inline int ListMatrixAdapter<Type>::cols() const {return _list.size();}
    
    template <class Type>
    inline typename Type::Scalar ListMatrixAdapter<Type>::coeff(int row, int col) const {
        return _list[col](row);
    }
    
    template <class Type>
    inline ListMatrixAdapter<Type> listMatrixAdapter(const List<Type>& list) {
        return ListMatrixAdapter<Type>(list);
    }
    
    inline Map<const RowVectorXd> listMatrixAdapter(const List<double>& list) {
        assert(!list.empty());
        return Map<const RowVectorXd>(&list.front(), list.size());
    }
    
    inline Map<const Matrix<double, 2, Dynamic> > listMatrixAdapter(const List<Vector2d>& list) {
        assert(!list.empty());
        return Map<const Matrix<double, 2, Dynamic> >(list.front().data(), 2, list.size());
    }
    
    inline Map<const Matrix<double, 3, Dynamic> > listMatrixAdapter(const List<Vector3d>& list) {
        assert(!list.empty());
        return Map<const Matrix<double, 3, Dynamic> >(list.front().data(), 3, list.size());
    }
    
    inline Map<const Matrix<double, 4, Dynamic> > listMatrixAdapter(const List<Vector4d>& list) {
        assert(!list.empty());
        return Map<const Matrix<double, 4, Dynamic> >(list.front().data(), 4, list.size());
    }
    
    inline Map<const RowVectorXI> listMatrixAdapter(const List<Interval>& list) {
        assert(!list.empty());
        return Map<const RowVectorXI>(&list.front(), list.size());
    }
    
    inline Map<const Matrix<Interval, 2, Dynamic> > listMatrixAdapter(const List<Vector2I>& list) {
        assert(!list.empty());
        return Map<const Matrix<Interval, 2, Dynamic> >(list.front().data(), 2, list.size());
    }
    
    inline Map<const Matrix<Interval, 3, Dynamic> > listMatrixAdapter(const List<Vector3I>& list) {
        assert(!list.empty());
        return Map<const Matrix<Interval, 3, Dynamic> >(list.front().data(), 3, list.size());
    }
    
    inline Map<const Matrix<Interval, 4, Dynamic> > listMatrixAdapter(const List<Vector4I>& list) {
        assert(!list.empty());
        return Map<const Matrix<Interval, 4, Dynamic> >(list.front().data(), 4, list.size());
    }
}


#endif
