
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

#pragma once

#include <opensolid/Error.hpp>
#include <opensolid/config.hpp>

#include <memory>

namespace opensolid
{
    template <class Type>
    class Handle
    {
    private:
        std::shared_ptr<Type> _pointer;
    public:
        Handle();
        explicit Handle(Type* argument);

        bool isValid() const;
        const Type& readAccess() const;
        Type& writeAccess();
    };

    class InvalidHandle : public Error
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT ~InvalidHandle() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT virtual const char* what() const throw() OPENSOLID_OVERRIDE;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    Handle<Type>::Handle() : _pointer(OPENSOLID_NULLPTR) {}

    template <class Type>
    Handle<Type>::Handle(Type* argument) : _pointer(argument) {}

    template <class Type>
    Handle<Type>::isValid() const {return _pointer;}

    template <class Type>
    const Type& Handle<Type>::readAccess() const {
        assert(_pointer);
        return *_pointer;
    }

    template <class Type>
    Type& Handle<Type>::writeAccess() {
        assert(_pointer);
        if (!_pointer.unique()) {_pointer.reset(new Type(readAccess()));}
        return *_pointer;
    }
}