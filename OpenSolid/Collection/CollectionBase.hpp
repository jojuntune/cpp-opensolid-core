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

#ifndef OPENSOLID__COLLECTIONBASE_HPP
#define OPENSOLID__COLLECTIONBASE_HPP

#include <vector>

namespace OpenSolid
{
    template <class DerivedType, class FunctionType, class ResultType>
    class CollectionMap;
    
    template <class FirstDerivedType, class SecondDerivedType>
    class CollectionConcatenation;
    
    template <class DerivedType>
    class CollectionBase
    {
    public:
        const DerivedType& derived() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        template <class OutputIteratorType>
        void copy(OutputIteratorType iterator) const;
        
        template <class ResultType, class FunctionType>
        CollectionMap<DerivedType, FunctionType, ResultType> mapped(
            const FunctionType& function
        ) const;
    };
    
    template <class FirstDerivedType, class SecondDerivedType>
    CollectionConcatenation<FirstDerivedType, SecondDerivedType> operator+(
        const CollectionBase<FirstDerivedType>& first_collection,
        const CollectionBase<SecondDerivedType>& second_collection
    );
}

////////// Implementation //////////

#include "CollectionMap.hpp"
#include "CollectionConcatenation.hpp"

namespace OpenSolid
{
    template <class DerivedType>
    inline const DerivedType& CollectionBase<DerivedType>::derived() const {
        return static_cast<const DerivedType&>(*this);
    }
    
    template <class DerivedType> template <class VisitorType>
    inline void CollectionBase<DerivedType>::visit(const VisitorType& visitor) const {
        derived().visit(visitor);
    }
    
    namespace
    {
        template <class OutputIteratorType>
        class CopyVisitor
        {
        private:
            OutputIteratorType _iterator;
        public:
            inline CopyVisitor(OutputIteratorType iterator) : _iterator(iterator) {}
            
            template <class Type>
            inline void operator()(const Type& object) {
                *_iterator = object;
                ++_iterator;
            }
        };
    }
        
    template <class DerivedType> template <class OutputIteratorType>
    inline void CollectionBase<DerivedType>::copy(OutputIteratorType iterator) const {
        visit(CopyVisitor<OutputIteratorType>(iterator));
    }
        
    template <class DerivedType> template <class ResultType, class FunctionType>
    CollectionMap<DerivedType, FunctionType, ResultType> CollectionBase<DerivedType>::mapped(
        const FunctionType& function
    ) const {return CollectionMap<DerivedType, FunctionType, ResultType>(*this, function);}
    
    template <class FirstDerivedType, class SecondDerivedType>
    inline CollectionConcatenation<FirstDerivedType, SecondDerivedType> operator+(
        const CollectionBase<FirstDerivedType>& first_collection,
        const CollectionBase<SecondDerivedType>& second_collection
    ) {
        return CollectionConcatenation<FirstDerivedType, SecondDerivedType>(
            first_collection,
            second_collection
        );
    }
}

#endif
