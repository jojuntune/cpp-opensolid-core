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

#ifndef OPENSOLID__FIXEDSIZECOLLECTION_HPP
#define OPENSOLID__FIXEDSIZECOLLECTION_HPP

#include "CollectionBase.hpp"

namespace OpenSolid
{
    template <class DerivedType, class FunctionType, class ResultType>
    class FixedSizeCollectionMap;
    
    template <class FirstDerivedType, class SecondDerivedType>
    class FixedSizeCollectionConcatenation;
    
    template <class DerivedType>
    class FixedSizeCollection : public CollectionBase<DerivedType>
    {
    public:
        int size() const;
        
        template <class ResultType, class FunctionType>
        FixedSizeCollectionMap<DerivedType, FunctionType, ResultType> mapped(
            const FunctionType& function
        ) const;
    };
    
    template <class FirstDerivedType, class SecondDerivedType>
    FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType> operator+(
        const FixedSizeCollection<FirstDerivedType>& first_collection,
        const FixedSizeCollection<SecondDerivedType>& second_collection
    );
}

////////// Implementation //////////

#include "FixedSizeCollectionMap.hpp"
#include "FixedSizeCollectionConcatenation.hpp"

namespace OpenSolid
{
    template <class DerivedType>
    inline int FixedSizeCollection<DerivedType>::size() const {return this->derived().size();}
        
    template <class DerivedType> template <class ResultType, class FunctionType>
    inline FixedSizeCollectionMap<DerivedType, FunctionType, ResultType>
    FixedSizeCollection<DerivedType>::mapped(const FunctionType& function) const {
        return FixedSizeCollectionMap<DerivedType, FunctionType, ResultType>(*this, function);
    }
    
    template <class FirstDerivedType, class SecondDerivedType>
    inline FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType> operator+(
        const FixedSizeCollection<FirstDerivedType>& first_collection,
        const FixedSizeCollection<SecondDerivedType>& second_collection
    ) {
        return FixedSizeCollectionConcatenation<FirstDerivedType, SecondDerivedType>(
            first_collection,
            second_collection
        );
    }
}

#endif
