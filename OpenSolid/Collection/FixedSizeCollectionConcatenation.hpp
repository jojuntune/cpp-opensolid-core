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

#ifndef OPENSOLID__FIXEDSIZECOLLECTIONCONCATENATION_HPP
#define OPENSOLID__FIXEDSIZECOLLECTIONCONCATENATION_HPP

#include <iterator>

namespace OpenSolid
{
    template <class DerivedType>
    class FixedSizeCollection;
    
    template <class FirstDerivedType, class SecondDerivedType>
    class FixedSizeCollectionConcatenation :
        public FixedSizeCollection<
            FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType>
        >
    {
    private:
        const FixedSizeCollection<FirstDerivedType>& _first_collection;
        const FixedSizeCollection<SecondDerivedType>& _second_collection;
    public:
        FixedSizeCollectionConcatenation(
            const FixedSizeCollection<FirstDerivedType>& first_collection,
            const FixedSizeCollection<SecondDerivedType>& second_collection
        );
        
        int size() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
}

////////// Implementation //////////

#include "FixedSizeCollection.hpp"

namespace OpenSolid
{
    template <class FirstDerivedType, class SecondDerivedType>
    inline FixedSizeCollectionConcatenation<
        FirstDerivedType,
        SecondDerivedType
    >::FixedSizeCollectionConcatenation(
        const FixedSizeCollection<FirstDerivedType>& first_collection,
        const FixedSizeCollection<SecondDerivedType>& second_collection
    ) : _first_collection(first_collection), _second_collection(second_collection) {}
    
    template <class FirstDerivedType, class SecondDerivedType>
    inline int FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType>::size() const {
        return _first_collection.size() + _second_collection.size();
    }
    
    template <class FirstDerivedType, class SecondDerivedType> template <class VisitorType>
    inline void FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType>::visit(
        const VisitorType& visitor
    ) const {
        _first_collection.visit(visitor);
        _second_collection.visit(visitor);
    }
}

#endif
