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

#ifndef OPENSOLID__COMMON__HASH_HPP
#define OPENSOLID__COMMON__HASH_HPP

#include <OpenSolid/config.hpp>

namespace OpenSolid
{
    template <class HashableType = std::size_t>
    struct Hash;

    template <>
    struct Hash<std::size_t>
    {
        std::size_t operator()(std::size_t argument) const;

        static std::size_t Combine(std::size_t first_argument, std::size_t second_argument);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline std::size_t Hash<std::size_t>::operator()(std::size_t argument) const {return argument;}

    inline std::size_t Hash<std::size_t>::Combine(
        std::size_t first_argument,
        std::size_t second_argument
    ) {
        return first_argument ^ (
            second_argument + 0x9e3779b9 + (first_argument << 6) + (first_argument >> 2)
        );
    }
}

#endif
