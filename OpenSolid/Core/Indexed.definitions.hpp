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

#include <OpenSolid/Core/Indexed.declarations.hpp>

namespace opensolid
{
    template <class TObject>
    class Indexed :
        public TObject
    {
    private:
        std::size_t _index;
    public:
        Indexed(const TObject& object, std::size_t index);

        Indexed(TObject&& object, std::size_t index);

        Indexed(const Indexed<TObject>& other);

        Indexed(Indexed<TObject>&& other);

        Indexed<TObject>&
        operator=(const Indexed<TObject>& other);

        Indexed<TObject>&
        operator=(Indexed<TObject>&& other);

        std::size_t
        index() const;
    };

    template <>
    class Indexed<double>
    {
    private:
        double _value;
        std::size_t _index;
    public:
        Indexed(double value, std::size_t index);

        operator double() const;

        std::size_t
        index() const;
    };
}
