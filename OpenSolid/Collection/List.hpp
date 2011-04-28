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

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Shared.hpp>
#include <OpenSolid/Value/Matrix.hpp>
#include "CollectionBase.hpp"
#include "FixedSizeCollection.hpp"

namespace OpenSolid
{
    template <class Type>
    class ListMatrixAdapter;
    
    template <class Type>
    class List : public FixedSizeCollection<List<Type> >
    {
    private:
        Shared<ReferenceCounted<std::vector<Type> > > _vector;
        
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
        
        List(
            const Type& first_item,
            const Type& second_item
        );
        
        List(
            const Type& first_item,
            const Type& second_item,
            const Type& third_item
        );
        
        List(
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item
        );
        
        List(
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item
        );
        
        List(
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item
        );
        
        List(
            const Type& first_item,
            const Type& second_item,
            const Type& third_item,
            const Type& fourth_item,
            const Type& fifth_item,
            const Type& sixth_item,
            const Type& seventh_item
        );
        
        List(
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
        
        ListMatrixAdapter<Type> matrix() const;
        
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
        ConstIterator cbegin() const;
        ConstIterator cend() const;
        
        Type& front();
        const Type& front() const;
        Type& back();
        const Type& back() const;
        Type& item();
        const Type& item() const;
        
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
}

////////// Implementation //////////

#include "ListMatrixAdapter.hpp"

namespace OpenSolid
{   
    template <class Type> template <class DerivedType>
    inline void List<Type>::add(const FixedSizeCollection<DerivedType>& collection) {
        _vector.reference().resize(size() + collection.size());
        collection.copy(_vector.reference().end() - collection.size());
    }
    
    template <class Type> template <class DerivedType>
    inline void List<Type>::add(const CollectionBase<DerivedType>& collection) {
        collection.copy(std::back_inserter(_vector.reference()));
    }
        
    template <class Type>
    inline List<Type>::List() : _vector(new std::vector<Type>()) {}
    
    template <class Type>
    inline List<Type>::List(int size) : _vector(new std::vector<Type>(size)) {}
    
    template <class Type> template <class DerivedType>
    inline List<Type>::List(const CollectionBase<DerivedType>& collection) :
        _vector(new std::vector<Type>()) {add(collection.derived());}
        
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item
    ) : _vector(new std::vector<Type>(2)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item
    ) : _vector(new std::vector<Type>(3)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item
    ) : _vector(new std::vector<Type>(4)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item
    ) : _vector(new std::vector<Type>(5)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item
    ) : _vector(new std::vector<Type>(6)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
        _vector.reference()[5] = sixth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item
    ) : _vector(new std::vector<Type>(7)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
        _vector.reference()[5] = sixth_item;
        _vector.reference()[6] = seventh_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item,
        const Type& eighth_item
    ) : _vector(new std::vector<Type>(8)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
        _vector.reference()[5] = sixth_item;
        _vector.reference()[6] = seventh_item;
        _vector.reference()[7] = eighth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
        const Type& first_item,
        const Type& second_item,
        const Type& third_item,
        const Type& fourth_item,
        const Type& fifth_item,
        const Type& sixth_item,
        const Type& seventh_item,
        const Type& eighth_item,
        const Type& ninth_item
    ) : _vector(new std::vector<Type>(9)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
        _vector.reference()[5] = sixth_item;
        _vector.reference()[6] = seventh_item;
        _vector.reference()[7] = eighth_item;
        _vector.reference()[8] = ninth_item;
    }
    
    template <class Type>
    inline List<Type>::List(
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
    ) : _vector(new std::vector<Type>(10)) {
        _vector.reference()[0] = first_item;
        _vector.reference()[1] = second_item;
        _vector.reference()[2] = third_item;
        _vector.reference()[3] = fourth_item;
        _vector.reference()[4] = fifth_item;
        _vector.reference()[5] = sixth_item;
        _vector.reference()[6] = seventh_item;
        _vector.reference()[7] = eighth_item;
        _vector.reference()[8] = ninth_item;
        _vector.reference()[9] = tenth_item;
    }
        
    template <class Type>
    inline ListMatrixAdapter<Type> List<Type>::matrix() const {
        return ListMatrixAdapter<Type>(*this);
    }
    
    template <class Type>
    inline int List<Type>::size() const {return _vector.constReference().size();}
    
    template <class Type>
    inline bool List<Type>::empty() const {return _vector.constReference().empty();}
        
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
        _vector.reference().reserve(size);
        return *this;
    }
    
    template <class Type>
    inline List<Type>& List<Type>::resize(int size) {
        _vector.reference().resize(size);
        return *this;
    }
    
    template <class Type>
    inline typename List<Type>::Iterator List<Type>::begin() {return _vector.reference().begin();}
    
    template <class Type>
    inline typename List<Type>::Iterator List<Type>::end() {return _vector.reference().end();}
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::begin() const {
        return _vector.constReference().begin();
    }
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::end() const {
        return _vector.constReference().end();
    }
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::cbegin() const {
        return _vector.constReference().begin();
    }
    
    template <class Type>
    inline typename List<Type>::ConstIterator List<Type>::cend() const {
        return _vector.constReference().end();
    }
    
    template <class Type>
    inline Type& List<Type>::front() {return _vector.reference().front();}
    
    template <class Type>
    inline const Type& List<Type>::front() const {return _vector.constReference().front();}
    
    template <class Type>
    inline Type& List<Type>::back() {return _vector.reference().back();}
    
    template <class Type>
    inline const Type& List<Type>::back() const {return _vector.constReference().back();}
    
    template <class Type>
    inline Type& List<Type>::item() {
        assert(size() == 1);
        return front();
    }
    
    template <class Type>
    inline const Type& List<Type>::item() const {
        assert(size() == 1);
        return front();
    }
    
    template <class Type>
    inline Type& List<Type>::operator[](int index) {
        assert(index >= 0 && index < size());
        return _vector.reference()[index];
    }
    
    template <class Type>
    inline const Type& List<Type>::operator[](int index) const {
        assert(index >= 0 && index < size());
        return _vector.constReference()[index];
    }
    
    template <class Type>
    inline List<Type>& List<Type>::append(const Type& object) {
        _vector.reference().push_back(object);
        return *this;
    }
        
    template <class Type> template <class DerivedType>
    inline List<Type>& List<Type>::extend(const CollectionBase<DerivedType>& collection) {
        add(collection.derived());
        return *this;
    }
    
    template <class Type>
    inline Type List<Type>::pop() {
        Type result = _vector.constReference().back();
        _vector.reference().pop_back();
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
        _vector.reference().clear();
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
}

#endif
