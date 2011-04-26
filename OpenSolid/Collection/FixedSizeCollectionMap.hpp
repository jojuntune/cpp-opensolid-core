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

#ifndef OPENSOLID__FIXEDSIZECOLLECTIONMAP_HPP
#define OPENSOLID__FIXEDSIZECOLLECTIONMAP_HPP

#include <iterator>

namespace OpenSolid
{
    template <class DerivedType>
    class FixedSizeCollection;
    
    template <class DerivedType, class FunctionType, class ResultType>
    class FixedSizeCollectionMap :
        public FixedSizeCollection<FixedSizeCollectionMap<DerivedType, FunctionType, ResultType> >
    {
    private:
        const FixedSizeCollection<DerivedType>& _collection;
        FunctionType _function;
    public:
        FixedSizeCollectionMap(
            const FixedSizeCollection<DerivedType>& collection,
            const FunctionType& function
        );
        
        int size() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
}

////////// Implementation //////////

#include "FixedSizeCollection.hpp"
#include "VisitorMap.hpp"

namespace OpenSolid
{
    template <class DerivedType, class FunctionType, class ResultType>
    inline FixedSizeCollectionMap<DerivedType, FunctionType, ResultType>::FixedSizeCollectionMap(
        const FixedSizeCollection<DerivedType>& collection,
        const FunctionType& function
    ) : _collection(collection), _function(function) {}
    
    template <class DerivedType, class FunctionType, class ResultType>
    inline int FixedSizeCollectionMap<DerivedType, FunctionType, ResultType>::size() const {
        return _collection.size();
    }
    
    template <class DerivedType, class FunctionType, class ResultType> template <class VisitorType>
    inline void FixedSizeCollectionMap<DerivedType, FunctionType, ResultType>::visit(
        const VisitorType& visitor
    ) const {_collection.visit(VisitorMap<VisitorType, FunctionType>(visitor, _function));}
}

#endif
