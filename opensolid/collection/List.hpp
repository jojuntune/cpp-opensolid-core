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

#ifndef OPENSOLID__LIST_HPP
#define OPENSOLID__LIST_HPP

#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>

#include <opensolid/common/Bounds.hpp>
#include <opensolid/value/Matrix.hpp>
#include "CollectionBase.hpp"
#include "FixedSizeCollection.hpp"

namespace opensolid
{
    template <class Type>
    class ListMatrixAdapter;
    
    template <class Type>
    class ConstListMatrixAdapter;
}

namespace Eigen
{
    template <class Type>
    struct ei_traits<opensolid::ListMatrixAdapter<Type> >
    {
        typedef typename Type::Scalar Scalar;
        typedef Dense StorageKind;
        typedef int Index;
        typedef MatrixXpr XprKind;
        
        static const int RowsAtCompileTime = Type::RowsAtCompileTime;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = Type::MaxRowsAtCompileTime;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = LvalueBit | NestByRefBit;
        static const int CoeffReadCost = 2;
    };
    
    template <class Type>
    struct ei_traits<opensolid::ConstListMatrixAdapter<Type> >
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
    
    template <>
    struct ei_traits<opensolid::ListMatrixAdapter<double> >
    {
        typedef double Scalar;
        typedef Dense StorageKind;
        typedef int Index;
        typedef MatrixXpr XprKind;
        
        static const int RowsAtCompileTime = 1;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = 1;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = LvalueBit | NestByRefBit | RowMajorBit;
        static const int CoeffReadCost = 2;
    };
    
    template <>
    struct ei_traits<opensolid::ConstListMatrixAdapter<double> >
    {
        typedef double Scalar;
        typedef Dense StorageKind;
        typedef int Index;
        typedef MatrixXpr XprKind;
        
        static const int RowsAtCompileTime = 1;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = 1;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = NestByRefBit | RowMajorBit;
        static const int CoeffReadCost = 2;
    };
}

namespace opensolid
{
    template <class Type>
    class List : public FixedSizeCollection<List<Type> >
    {
    private:
        std::vector<Type> _vector;
        
        template <class DerivedType>
        void add(const FixedSizeCollection<DerivedType>& collection);
        
        template <class DerivedType>
        void add(const CollectionBase<DerivedType>& collection);
    public:
        typedef typename std::vector<Type>::iterator Iterator;
        typedef typename std::vector<Type>::const_iterator ConstIterator;
        
        List();
        explicit List(int size);
        
        template <class DerivedType>
        List(const CollectionBase<DerivedType>& collection);
        
        template <class IteratorType>
        List(IteratorType begin, IteratorType end);
        
        List(
            int size,
            const Type& first_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item,
            const Type& seventh_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item,
            const Type& seventh_item,
            const Type& eighth_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item,
            const Type& seventh_item,
            const Type& eighth_item,
            const Type& ninth_item
        );
        
        List(
            int size,
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item,
            const Type& seventh_item,
            const Type& eighth_item,
            const Type& ninth_item,
            const Type& tenth_item
        );
        
        ListMatrixAdapter<Type> matrix();
        ConstListMatrixAdapter<Type> matrix() const;
        
        int size() const;
        bool empty() const;
        
        template <class DerivedType>
        List<Type>& operator=(const CollectionBase<DerivedType>& collection);
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        typename Bounds<Type>::Type bounds() const;
        
        List<Type>& reserve(int size);
        List<Type>& resize(int size);
        
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        
        Type& front();
        const Type& front() const;
        Type& back();
        const Type& back() const;
        
        Type& operator[](int index);
        const Type& operator[](int index) const;
        
        List<Type>& append(const Type& object);
        
        template <class DerivedType>
        List<Type>& extend(const CollectionBase<DerivedType>& collection);
        
        Type pop();
        
        List<Type>& reverse();
        List<Type>& sort();
        
        template <class ComparatorType>
        List<Type>& sort(ComparatorType comparator);
        
        List<Type>& clear();
    };
    
    template <class FirstType, class SecondType>
    bool operator==(const List<FirstType>& first_list, const List<SecondType>& second_list);
    
    template <class Type, class DerivedType>
    bool operator==(const List<Type>& list, const CollectionBase<DerivedType>& collection);
    
    template <class DerivedType, class Type>
    bool operator==(const CollectionBase<DerivedType>& collection, const List<Type>& list);
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const List<Type>& list);
    
    template <class Type>
    class ListMatrixAdapter : public MatrixBase<ListMatrixAdapter<Type> >
    {
    private:
        List<Type>& _list;
        
        friend class ConstListMatrixAdapter<Type>;
    public:
        typedef MatrixBase<ListMatrixAdapter<Type> > Base;
        typedef typename Type::Scalar Scalar;
        typedef Scalar RealScalar;
        typedef Scalar PacketScalar;
        typedef Scalar CoeffReturnType;
        typedef typename Eigen::ei_nested<ListMatrixAdapter<Type> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = Type::RowsAtCompileTime;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = Type::MaxRowsAtCompileTime;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = LvalueBit | NestByRefBit;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ListMatrixAdapter(List<Type>& list);
        ListMatrixAdapter(ListMatrixAdapter<Type>& other);
        
        template <class DerivedType>
        void operator=(const ReturnByValue<DerivedType>& other);
        
        template <class DerivedType>
        void operator=(const MatrixBase<DerivedType>& other);
        
        void resize(int rows, int cols);
        
        int rows() const;
        int cols() const;
        
        typename const Type::Scalar& coeff(int row, int col) const;
        typename Type::Scalar& coeffRef(int row, int col);
    };
    
    template <class Type>
    class ConstListMatrixAdapter : public MatrixBase<ConstListMatrixAdapter<Type> >
    {
    private:
        const List<Type>& _list;
    public:
        typedef MatrixBase<ConstListMatrixAdapter<Type> > Base;
        typedef typename Type::Scalar Scalar;
        typedef Scalar RealScalar;
        typedef Scalar PacketScalar;
        typedef Scalar CoeffReturnType;
        typedef typename Eigen::ei_nested<ConstListMatrixAdapter<Type> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = Type::RowsAtCompileTime;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = Type::MaxRowsAtCompileTime;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = NestByRefBit;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ConstListMatrixAdapter(const List<Type>& list);
        ConstListMatrixAdapter(const ListMatrixAdapter<Type>& other);
        ConstListMatrixAdapter(const ConstListMatrixAdapter<Type>& other);
        
        int rows() const;
        int cols() const;
        
        typename Type::Scalar coeff(int row, int col) const;
    };
    
    template <>
    class ListMatrixAdapter<double> : public MatrixBase<ListMatrixAdapter<double> >
    {
    private:
        List<double>& _list;
        
        friend class ConstListMatrixAdapter<double>;
    public:
        typedef MatrixBase<ListMatrixAdapter<double> > Base;
        typedef double Scalar;
        typedef double RealScalar;
        typedef double PacketScalar;
        typedef double CoeffReturnType;
        typedef Eigen::ei_nested<ListMatrixAdapter<double> >::type Nested;
        typedef Dense StorageKind;
        typedef int Index;
        static const int RowsAtCompileTime = 1;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = 1;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int Flags = LvalueBit | NestByRefBit;
        static const int CoeffReadCost = 2;
        static const int SizeAtCompileTime = Dynamic;
        static const int MaxSizeAtCompileTime = Dynamic;
        static const int IsVectorAtCompileTime = false;
        using Base::derived;
        using Base::const_cast_derived;
        
        ListMatrixAdapter(List<double>& list);
        ListMatrixAdapter(ListMatrixAdapter<double>& other);
        
        template <class DerivedType>
        void operator=(const ReturnByValue<DerivedType>& other);
        
        template <class DerivedType>
        void operator=(const MatrixBase<DerivedType>& other);
        
        void resize(int rows, int cols);
        
        int rows() const;
        int cols() const;
        
        const double& coeff(int row, int col) const;
        double& coeffRef(int row, int col);
    };
    
    template <>
    class ConstListMatrixAdapter<double> : public MatrixBase<ConstListMatrixAdapter<double> >
    {
    private:
        const List<double>& _list;
    public:
        typedef MatrixBase<ConstListMatrixAdapter<double> > Base;
        typedef double Scalar;
        typedef double RealScalar;
        typedef double PacketScalar;
        typedef double CoeffReturnType;
        typedef Eigen::ei_nested<ConstListMatrixAdapter<double> >::type Nested;
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
        
        ConstListMatrixAdapter(const List<double>& list);
        ConstListMatrixAdapter(const ListMatrixAdapter<double>& other);
        ConstListMatrixAdapter(const ConstListMatrixAdapter<double>& other);
        
        int rows() const;
        int cols() const;
        
        double coeff(int row, int col) const;
    };
}

////////// Implementation //////////

namespace opensolid
{   
    template <class Type> template <class DerivedType>
    inline void List<Type>::add(const FixedSizeCollection<DerivedType>& collection) {
        _vector.resize(size() + collection.size());
        collection.copy(_vector.end() - collection.size());
    }
    
    template <class Type> template <class DerivedType>
    inline void List<Type>::add(const CollectionBase<DerivedType>& collection) {
        collection.copy(std::back_inserter(_vector));
    }
        
    template <class Type>
    inline List<Type>::List() {}
    
    template <class Type>
    inline List<Type>::List(int size) : _vector(size) {}
    
    template <class Type> template <class DerivedType>
    inline List<Type>::List(const CollectionBase<DerivedType>& collection) {
        add(collection.derived());
    }
        
    template <class Type> template <class IteratorType>
    inline List<Type>::List(IteratorType begin, IteratorType end) : _vector(begin, end) {}
        
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item
    ) : _vector(1) {
        assert(size == 1);
        _vector[0] = first_item;
    }
        
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item
    ) : _vector(2) {
        assert(size == 2);
        _vector[0] = first_item;
        _vector[1] = second_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item
    ) : _vector(3) {
        assert(size == 3);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item
    ) : _vector(4) {
        assert(size == 4);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item
    ) : _vector(5) {
        assert(size == 5);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item
    ) : _vector(6) {
        assert(size == 6);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
        _vector[5] = sixth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item
    ) : _vector(7) {
        assert(size == 7);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
        _vector[5] = sixth_item;
        _vector[6] = seventh_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item,
        const Type& eighth_item
    ) : _vector(8) {
        assert(size == 8);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
        _vector[5] = sixth_item;
        _vector[6] = seventh_item;
        _vector[7] = eighth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item,
        const Type& eighth_item,
        const Type& ninth_item
    ) : _vector(9) {
        assert(size == 9);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
        _vector[5] = sixth_item;
        _vector[6] = seventh_item;
        _vector[7] = eighth_item;
        _vector[8] = ninth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        int size,
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item,
        const Type& eighth_item,
        const Type& ninth_item,
        const Type& tenth_item
    ) : _vector(10) {
        assert(size == 10);
        _vector[0] = first_item;
        _vector[1] = second_item;
        _vector[2] = third_item;
        _vector[3] = fourth_item;
        _vector[4] = fifth_item;
        _vector[5] = sixth_item;
        _vector[6] = seventh_item;
        _vector[7] = eighth_item;
        _vector[8] = ninth_item;
        _vector[9] = tenth_item;
    }
        
    template <class Type>
    inline ListMatrixAdapter<Type> List<Type>::matrix() {
        return ListMatrixAdapter<Type>(*this);
    }
    
    template <class Type>
    inline ConstListMatrixAdapter<Type> List<Type>::matrix() const {
        return ConstListMatrixAdapter<Type>(*this);
    }
    
    template <class Type>
    inline int List<Type>::size() const {return _vector.size();}
    
    template <class Type>
    inline bool List<Type>::empty() const {return _vector.empty();}
        
    template <class Type> template <class DerivedType>
    inline List<Type>& List<Type>::operator=(const CollectionBase<DerivedType>& collection) {
        clear();
        add(collection.derived());
        return *this;
    }
        
    template <class Type> template <class VisitorType>
    inline void List<Type>::visit(const VisitorType& visitor) const {
        std::for_each(begin(), end(), const_cast<VisitorType&>(visitor));
    }
    
    template <class Type>    
    typename Bounds<Type>::Type List<Type>::bounds() const {
        if (empty()) {return typename Bounds<Type>::Type();}
        typename Bounds<Type>::Type result = Bounds<Type>::bounds(front());
        for (Iterator i = begin() + 1; i != end(); ++i) {
            result = result.hull(Bounds<Type>::bounds(*i));
        }
        return result;
    }
    
    template <class Type>
    inline List<Type>& List<Type>::reserve(int size) {
        _vector.reserve(size);
        return *this;
    }
    
    template <class Type>
    inline List<Type>& List<Type>::resize(int size) {
        _vector.resize(size);
        return *this;
    }
    
    template <class Type>
    inline typename List<Type>::Iterator List<Type>::begin() {return _vector.begin();}
    
    template <class Type>
    inline typename List<Type>::Iterator List<Type>::end() {return _vector.end();}
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::begin() const {return _vector.begin();}
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::end() const {return _vector.end();}
    
    template <class Type>
    inline Type& List<Type>::front() {return _vector.front();}
    
    template <class Type>
    inline const Type& List<Type>::front() const {return _vector.front();}
    
    template <class Type>
    inline Type& List<Type>::back() {return _vector.back();}
    
    template <class Type>
    inline const Type& List<Type>::back() const {return _vector.back();}
    
    template <class Type>
    inline Type& List<Type>::operator[](int index) {
        assert(index >= 0 && index < size());
        return _vector[index];
    }
    
    template <class Type>
    inline const Type& List<Type>::operator[](int index) const {
        assert(index >= 0 && index < size());
        return _vector[index];
    }
    
    template <class Type>
    inline List<Type>& List<Type>::append(const Type& object) {
        _vector.push_back(object);
        return *this;
    }
        
    template <class Type> template <class DerivedType>
    inline List<Type>& List<Type>::extend(const CollectionBase<DerivedType>& collection) {
        add(collection.derived());
        return *this;
    }
    
    template <class Type>
    inline Type List<Type>::pop() {
        Type result = _vector.back();
        _vector.pop_back();
        return result;
    }
    
    template <class Type>
    inline List<Type>& List<Type>::reverse() {
        std::reverse(begin(), end());
        return *this;
    }
    
    template <class Type>
    inline List<Type>& List<Type>::sort() {
        std::sort(begin(), end());
        return *this;
    }
    
    template <class Type> template <class ComparatorType>
    inline List<Type>& List<Type>::sort(ComparatorType comparator) {
        std::sort(begin(), end(), comparator);
        return *this;
    }
    
    template <class Type>
    List<Type>& List<Type>::clear() {
        _vector.clear();
        return *this;
    }
    
    template <class FirstType, class SecondType>
    inline bool operator==(const List<FirstType>& first_list, const List<SecondType>& second_list) {
        return first_list.size() == second_list.size() &&
            std::equal(first_list.begin(), first_list.end(), second_list.begin());
    }
    
    namespace
    {
        template <class Type>
        class EqualityVisitor
        {
        private:
            typename List<Type>::ConstIterator _iterator;
            typename List<Type>::ConstIterator _end;
            bool _equal;
        public:
            inline EqualityVisitor(const List<Type>& list) :
                _iterator(list.begin()), _end(list.end()), _equal(true) {}
            
            template <class OtherType>
            inline void visit(const OtherType& item) {
                if (_iterator == _end) {
                    _equal = false;
                } else {
                    if (item != *_iterator) {_equal = false;}
                    ++_iterator;
                }
            }
            
            inline bool equal() const {return _equal;}
        };
    }
    
    template <class Type, class DerivedType>
    inline bool operator==(const List<Type>& list, const CollectionBase<DerivedType>& collection) {
        EqualityVisitor<Type> visitor(list);
        collection.visit(visitor);
        return visitor.equal();
    }
    
    template <class DerivedType, class Type>
    inline bool operator==(const CollectionBase<DerivedType>& collection, const List<Type>& list) {
        EqualityVisitor<Type> visitor(list);
        collection.visit(visitor);
        return visitor.equal();
    }
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const List<Type>& list) {
        stream << "[";
        stream << list.front();
        for (int i = 1; i < list.size(); ++i) {stream << "," << list[i];}
        stream << "]";
        return stream;
    }
    
    template <class Type>
    inline ListMatrixAdapter<Type>::ListMatrixAdapter(List<Type>& list) : _list(list) {}
    
    template <class Type>
    inline ListMatrixAdapter<Type>::ListMatrixAdapter(ListMatrixAdapter<Type>& other) :
        _list(other._list) {}
        
    template <class Type>
    inline void ListMatrixAdapter<Type>::resize(int rows, int cols) {
        _list.resize(cols);
        for (int i = 0; i < cols; ++i) {_list[i].resize(rows, 1);}
    }
    
    template <class Type>
    inline int ListMatrixAdapter<Type>::rows() const {return _list.front().size();}
    
    template <class Type>
    inline int ListMatrixAdapter<Type>::cols() const {return _list.size();}
    
    template <class Type>
    inline const typename Type::Scalar& ListMatrixAdapter<Type>::coeff(int row, int col) const {
        return _list[col](row);
    }
    
    template <class Type>
    inline typename Type::Scalar& ListMatrixAdapter<Type>::coeffRef(int row, int col) {
        return _list[col](row);
    }
    
    template <class Type>
    inline ConstListMatrixAdapter<Type>::ConstListMatrixAdapter(const List<Type>& list) :
        _list(list) {}
    
    template <class Type>
    inline ConstListMatrixAdapter<Type>::ConstListMatrixAdapter(
        const ListMatrixAdapter<Type>& other
    ) : _list(other._list) {}
    
    template <class Type>
    inline ConstListMatrixAdapter<Type>::ConstListMatrixAdapter(
        const ConstListMatrixAdapter<Type>& other
    ) : _list(other._list) {}
        
    template <class Type>
    inline int ConstListMatrixAdapter<Type>::rows() const {return _list.front().size();}
    
    template <class Type>
    inline int ConstListMatrixAdapter<Type>::cols() const {return _list.size();}
    
    template <class Type>
    inline typename Type::Scalar ConstListMatrixAdapter<Type>::coeff(int row, int col) const {
        return _list[col](row);
    }
    
    inline ListMatrixAdapter<double>::ListMatrixAdapter(List<double>& list) : _list(list) {}
    
    inline ListMatrixAdapter<double>::ListMatrixAdapter(ListMatrixAdapter<double>& other) :
        _list(other._list) {}
    
    inline void ListMatrixAdapter<double>::resize(int rows, int cols) {
        _list.resize(cols);
        assert(rows == 1);
    }
    
    inline int ListMatrixAdapter<double>::rows() const {return 1;}
    
    inline int ListMatrixAdapter<double>::cols() const {return _list.size();}
    
    inline const double& ListMatrixAdapter<double>::coeff(int row, int col) const {
        assert(row == 0);
        return _list[col];
    }
    
    inline double& ListMatrixAdapter<double>::coeffRef(int row, int col) {
        assert(row == 0);
        return _list[col];
    }
    
    inline ConstListMatrixAdapter<double>::ConstListMatrixAdapter(const List<double>& list) :
        _list(list) {}
    
    inline ConstListMatrixAdapter<double>::ConstListMatrixAdapter(
        const ListMatrixAdapter<double>& other
    ) : _list(other._list) {}
    
    inline ConstListMatrixAdapter<double>::ConstListMatrixAdapter(
        const ConstListMatrixAdapter<double>& other
    ) : _list(other._list) {}
    
    inline int ConstListMatrixAdapter<double>::rows() const {return 1;}
    
    inline int ConstListMatrixAdapter<double>::cols() const {return _list.size();}
    
    inline double ConstListMatrixAdapter<double>::coeff(int row, int col) const {
        assert(row == 0);
        return _list[col];
    }
}

#endif
