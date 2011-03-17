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

#ifndef OPENSOLID__COLLECTIONCONCATENATION_HPP
#define OPENSOLID__COLLECTIONCONCATENATION_HPP

#include <iterator>

namespace opensolid
{
    template <class DerivedType>
    class CollectionBase;
    
    template <class FirstDerivedType, class SecondDerivedType>
    class CollectionConcatenation :
        public CollectionBase<CollectionConcatenation<FirstDerivedType, SecondDerivedType> >
    {
    private:
        const CollectionBase<FirstDerivedType>& _first_collection;
        const CollectionBase<SecondDerivedType>& _second_collection;
    public:
        CollectionConcatenation(
            const CollectionBase<FirstDerivedType>& first_collection,
            const CollectionBase<SecondDerivedType>& second_collection
        );
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
}

////////// Implementation //////////

#include "CollectionBase.hpp"

namespace opensolid
{
    template <class FirstDerivedType, class SecondDerivedType>
    inline CollectionConcatenation<FirstDerivedType, SecondDerivedType>::CollectionConcatenation(
        const CollectionBase<FirstDerivedType>& first_collection,
        const CollectionBase<SecondDerivedType>& second_collection
    ) : _first_collection(first_collection), _second_collection(second_collection) {}
    
    template <class FirstDerivedType, class SecondDerivedType> template <class VisitorType>
    inline void CollectionConcatenation<FirstDerivedType, SecondDerivedType>::visit(
        const VisitorType& visitor
    ) const {
        _first_collection.visit(visitor);
        _second_collection.visit(visitor);
    }
}

#endif
