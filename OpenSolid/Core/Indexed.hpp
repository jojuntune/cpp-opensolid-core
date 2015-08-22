/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Indexed.definitions.hpp>

namespace opensolid
{
    template <class TObject>
    inline
    Indexed<TObject>::Indexed(const TObject& object, std::size_t index) :
        TObject(object),
        _index(index) {
    }

    template <class TObject>
    inline
    Indexed<TObject>::Indexed(TObject&& object, std::size_t index) :
        TObject(std::move(object)),
        _index(index) {
    }

    template <class TObject>
    inline
    Indexed<TObject>::Indexed(const Indexed<TObject>& other) :
        TObject(other),
        _index(other.index()) {
    }

    template <class TObject>
    inline
    Indexed<TObject>::Indexed(Indexed<TObject>&& other) :
        TObject(std::move(other)),
        _index(other.index()) {
    }

    template <class TObject>
    inline
    Indexed<TObject>&
    Indexed<TObject>::operator=(const Indexed<TObject>& other) {
        TObject::operator=(other);
        _index = other.index();
        return *this;
    }

    template <class TObject>
    inline
    Indexed<TObject>&
    Indexed<TObject>::operator=(Indexed<TObject>&& other) {
        TObject::operator=(std::move(other));
        _index = other.index();
        return *this;
    }

    template <class TObject>
    inline
    std::size_t
    Indexed<TObject>::index() const {
        return _index;
    }

    inline
    Indexed<double>::Indexed(double value, std::size_t index) :
        _value(value),
        _index(index) {
    }

    inline
    Indexed<double>::operator double() const {
        return _value;
    }

    inline
    std::size_t
    Indexed<double>::index() const {
        return _index;
    }

}
