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
    class List;
    
    template <class Type>
    class ListMatrixAdapter;
}

namespace Eigen
{
    namespace internal
    {
        template <class Type>
        struct DirectAccessTraits
        {
            static const int bit = 0;
        };
        
        template <>
        struct DirectAccessTraits<Vector2d>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 2;
        };
        
        template <>
        struct DirectAccessTraits<Vector3d>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 3;
        };
        
        template <>
        struct DirectAccessTraits<Vector4d>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 4;
        };
        
        template <>
        struct DirectAccessTraits<Vector2I>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 2;
        };
        
        template <>
        struct DirectAccessTraits<Vector3I>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 3;
        };
        
        template <>
        struct DirectAccessTraits<Vector4I>
        {
            static const int bit = DirectAccessBit;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 4;
        };
        
        template <class Type>
        struct traits<OpenSolid::ListMatrixAdapter<Type> > : public DirectAccessTraits<Type>
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
        
        template <>
        struct traits<OpenSolid::ListMatrixAdapter<double> >
        {
            typedef double Scalar;
            typedef Dense StorageKind;
            typedef int Index;
            typedef MatrixXpr XprKind;
            
            static const int RowsAtCompileTime = 1;
            static const int ColsAtCompileTime = Dynamic;
            static const int MaxRowsAtCompileTime = 1;
            static const int MaxColsAtCompileTime = Dynamic;
            static const int Flags = NestByRefBit | RowMajorBit | DirectAccessBit;
            static const int CoeffReadCost = 2;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 1;
        };
        
        template <>
        struct traits<OpenSolid::ListMatrixAdapter<Interval> >
        {
            typedef Interval Scalar;
            typedef Dense StorageKind;
            typedef int Index;
            typedef MatrixXpr XprKind;
            
            static const int RowsAtCompileTime = 1;
            static const int ColsAtCompileTime = Dynamic;
            static const int MaxRowsAtCompileTime = 1;
            static const int MaxColsAtCompileTime = Dynamic;
            static const int Flags = NestByRefBit | RowMajorBit | DirectAccessBit;
            static const int CoeffReadCost = 2;
            static const int InnerStrideAtCompileTime = 1;
            static const int OuterStrideAtCompileTime = 1;
        };
    }
}

namespace OpenSolid
{
    template <class Type, int bit_>
    class DirectAccessAdapter
    {   
    };
    
    template <class Type>
    class DirectAccessAdapter<Type, DirectAccessBit>
    {
    public:
        const typename Type::Scalar* data() const;
    };
    
    template <class Type>
    class ListMatrixAdapter :
        public MatrixBase<ListMatrixAdapter<Type> >,
        public DirectAccessAdapter<Type, internal::DirectAccessTraits<Type>::bit>
    {
    private:
        const List<Type>& _list;
        
        friend class DirectAccessAdapter<Type, internal::DirectAccessTraits<Type>::bit>;
    public:
        typedef MatrixBase<ListMatrixAdapter<Type> > Base;
        typedef typename Type::Scalar Scalar;
        typedef Scalar RealScalar;
        typedef Scalar PacketScalar;
        typedef Scalar CoeffReturnType;
        typedef typename Eigen::internal::nested<ListMatrixAdapter<Type> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = Type::RowsAtCompileTime;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = Type::MaxRowsAtCompileTime;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = internal::traits<ListMatrixAdapter<Type> >::Flags;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ListMatrixAdapter(const List<Type>& list);
        ListMatrixAdapter(const ListMatrixAdapter<Type>& other);
        
        int rows() const;
        int cols() const;
        
        typename Type::Scalar coeff(int row, int col) const;
    };
    
    template <>
    class ListMatrixAdapter<double> : public MatrixBase<ListMatrixAdapter<double> >
    {
    private:
        const List<double>& _list;
    public:
        typedef MatrixBase<ListMatrixAdapter<double> > Base;
        typedef double Scalar;
        typedef double RealScalar;
        typedef double PacketScalar;
        typedef double CoeffReturnType;
        typedef Eigen::internal::nested<ListMatrixAdapter<double> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = 1;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = 1;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = NestByRefBit;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ListMatrixAdapter(const List<double>& list);
        ListMatrixAdapter(const ListMatrixAdapter<double>& other);
        
        int rows() const;
        int cols() const;
        
        double coeff(int row, int col) const;
        const double* data() const;
    };
    
    template <>
    class ListMatrixAdapter<Interval> : public MatrixBase<ListMatrixAdapter<Interval> >
    {
    private:
        const List<Interval>& _list;
    public:
        typedef MatrixBase<ListMatrixAdapter<Interval> > Base;
        typedef Interval Scalar;
        typedef Interval RealScalar;
        typedef Interval PacketScalar;
        typedef Interval CoeffReturnType;
        typedef Eigen::internal::nested<ListMatrixAdapter<Interval> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = 1;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = 1;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = NestByRefBit;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ListMatrixAdapter(const List<Interval>& list);
        ListMatrixAdapter(const ListMatrixAdapter<Interval>& other);
        
        int rows() const;
        int cols() const;
        
        Interval coeff(int row, int col) const;
        const Interval* data() const;
    };
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
