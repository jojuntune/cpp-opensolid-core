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

#ifndef OPENSOLID__ITERATORRANGE_HPP
#define OPENSOLID__ITERATORRANGE_HPP

#include <iterator>

#include "CollectionBase.hpp"

namespace opensolid
{
    template <class IteratorType>
    class IteratorRange : public FixedSizeCollection<IteratorRange<IteratorType> >
    {
    private:
        IteratorType _begin;
        IteratorType _end;
        int _size;
    public:
        IteratorRange(IteratorType begin, IteratorType end);
        
        IteratorType begin() const;
        IteratorType end() const;
        
        int size() const;
        bool empty() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
    
    template <class IteratorType>
    IteratorRange<IteratorType> iteratorRange(IteratorType begin, IteratorType end);
}

////////// Implementation //////////

namespace opensolid
{
    template <class IteratorType>
    inline IteratorRange<IteratorType>::IteratorRange(IteratorType begin, IteratorType end) :
        _begin(begin), _end(end), _size(std::distance(begin, end)) {}
    
    template <class IteratorType>
    inline IteratorType IteratorRange<IteratorType>::begin() const {return _begin;}
    
    template <class IteratorType>
    inline IteratorType IteratorRange<IteratorType>::end() const {return _end;}
    
    template <class IteratorType>
    inline int IteratorRange<IteratorType>::size() const {return _size;}
    
    template <class IteratorType>
    inline bool IteratorRange<IteratorType>::empty() const {return size() == 0;}
        
    template <class IteratorType> template <class VisitorType>
    inline void IteratorRange<IteratorType>::visit(const VisitorType& visitor) const {
        std::for_each(begin(), end(), const_cast<VisitorType&>(visitor));
    }
    
    template <class IteratorType>
    inline IteratorRange<IteratorType> iteratorRange(IteratorType begin, IteratorType end) {
        return IteratorRange<IteratorType>(begin, end);
    }
}

#endif
