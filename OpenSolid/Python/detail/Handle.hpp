/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
*************************************************************************************/

#pragma once

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/config.hpp>

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

        OPENSOLID_PYTHON_MODULE_EXPORT virtual const char* what() const throw() override;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    Handle<Type>::Handle() : _pointer(nullptr) {}

    template <class Type>
    Handle<Type>::Handle(Type* argument) : _pointer(argument) {}

    template <class Type>
    bool Handle<Type>::isValid() const {return _pointer;}

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
