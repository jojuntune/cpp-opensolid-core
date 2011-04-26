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

#ifndef OPENSOLID__COLLECTIONMAP_HPP
#define OPENSOLID__COLLECTIONMAP_HPP

#include <iterator>

namespace OpenSolid
{
    template <class DerivedType>
    class CollectionBase;
    
    template <class DerivedType, class FunctionType, class ResultType>
    class CollectionMap :
        public CollectionBase<CollectionMap<DerivedType, FunctionType, ResultType> >
    {
    private:
        const CollectionBase<DerivedType>& _collection;
        FunctionType _function;
    public:
        CollectionMap(const CollectionBase<DerivedType>& collection, const FunctionType& function);
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
}

////////// Implementation //////////

#include "CollectionBase.hpp"
#include "VisitorMap.hpp"

namespace OpenSolid
{
    template <class DerivedType, class FunctionType, class ResultType>
    inline CollectionMap<DerivedType, FunctionType, ResultType>::CollectionMap(
        const CollectionBase<DerivedType>& collection,
        const FunctionType& function
    ) : _collection(collection), _function(function) {}
    
    template <class DerivedType, class FunctionType, class ResultType> template <class VisitorType>
    inline void CollectionMap<DerivedType, FunctionType, ResultType>::visit(
        const VisitorType& visitor
    ) const {_collection.visit(VisitorMap<VisitorType, FunctionType>(visitor, _function));}
}

#endif
