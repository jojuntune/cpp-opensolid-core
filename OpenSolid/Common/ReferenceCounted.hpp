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

#ifndef OPENSOLID__REFERENCECOUNTED_HPP
#define OPENSOLID__REFERENCECOUNTED_HPP

#include "ReferenceCountedBase.hpp"

namespace OpenSolid
{
    template <class Type>
    class ReferenceCounted : public ReferenceCountedBase<ReferenceCounted<Type>>
    {
    private:
        Type* _object;
    public:
        ReferenceCounted(Type* object);
        ~ReferenceCounted();
        
        Type* object() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    ReferenceCounted<Type>::ReferenceCounted(Type* object) : _object(object) {}
    
    template <class Type>
    ReferenceCounted<Type>::~ReferenceCounted() {delete _object;}
    
    template <class Type>
    Type* ReferenceCounted<Type>::object() const {return _object;}
}

#endif
