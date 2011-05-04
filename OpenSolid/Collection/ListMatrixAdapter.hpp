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
            static const int Flags = NestByRefBit | DirectAccessTraits<Type>::bit;
            static const int CoeffReadCost = 2;
        };
    }
}

namespace OpenSolid
{
    template <class Type>
    struct ListMatrixAdapterType
    {
        typedef ListMatrixAdapter<Type> Type;
    };
    
    template <>
    struct ListMatrixAdapterType<double>
    {
        typedef MapXcd Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector2d>
    {
        typedef MapXcd Type;
    };
    
    template <>
    struct ListMatrixAdaterType<Vector3d>
    {
        typedef MapXcd Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector4d>
    {
        typedef MapXcd Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Interval>
    {
        typedef MapXcI Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector2I>
    {
        typedef MapXcI Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector3I>
    {
        typedef MapXcI Type;
    };
    
    template <>
    struct ListMatrixAdapterType<Vector4I>
    {
        typedef MapXcI Type;
    };
    
    template <class Type>
    class ListMatrixAdapter : public MatrixBase<ListMatrixAdapter<Type> >
    {
    private:
        const List<Type>& _list;
    public:
        EIGEN_DENSE_PUBLIC_INTERFACE(ListMatrixAdapter<Type>)
        
        ListMatrixAdapter(const List<Type>& list);
        ListMatrixAdapter(const ListMatrixAdapter<Type>& other);
        
        int rows() const;
        int cols() const;
        
        typename Type::Scalar coeff(int row, int col) const;
    };
    
    template <class Type>
    ListMatrixAdapter<Type> listMatrixAdapter(const List<Type>& list);
    
    MapXcd listMatrixAdapter(const List<double>& list);
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline const typename Type::Scalar* DirectAccessAdapter<Type, DirectAccessBit>::data() const {
        return static_cast<const ListMatrixAdapter<Type>&>(*this)._list.front().data();
    };
    
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
    
    inline ListMatrixAdapter<double>::ListMatrixAdapter(const List<double>& list) : _list(list) {}
    
    inline ListMatrixAdapter<double>::ListMatrixAdapter(const ListMatrixAdapter<double>& other) :
        _list(other._list) {}
    
    inline int ListMatrixAdapter<double>::rows() const {return 1;}
    
    inline int ListMatrixAdapter<double>::cols() const {return _list.size();}
    
    inline double ListMatrixAdapter<double>::coeff(int row, int col) const {
        assert(row == 0);
        return _list[col];
    }
    
    inline double& ListMatrixAdapter<double>::coeff(int row, int col) const {
        assert(row == 0);
        return _list[col];
    }
    
    inline const double* ListMatrixAdapter<double>::data() const {return &_list.front();}
    
    inline ListMatrixAdapter<Interval>::ListMatrixAdapter(const List<Interval>& list) :
        _list(list) {}
    
    inline ListMatrixAdapter<Interval>::ListMatrixAdapter(
        const ListMatrixAdapter<Interval>& other
    ) : _list(other._list) {}
    
    inline int ListMatrixAdapter<Interval>::rows() const {return 1;}
    
    inline int ListMatrixAdapter<Interval>::cols() const {return _list.size();}
    
    inline Interval ListMatrixAdapter<Interval>::coeff(int row, int col) const {
        assert(row == 0);
        return _list[col];
    }
    
    inline const Interval* ListMatrixAdapter<Interval>::data() const {return &_list.front();}
}


#endif
