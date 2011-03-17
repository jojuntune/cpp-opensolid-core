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

#ifndef OPENSOLID__COMMON__CHECK_HPP
#define OPENSOLID__COMMON__CHECK_HPP

#include <opensolid/config.hpp>

#include <string>

namespace opensolid
{
    OPENSOLID_EXPORT void checkErrorHasData(
        bool has_data,
        const std::string& name,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkNonEmptyContainer(bool empty, const std::string& caller);
    
    OPENSOLID_EXPORT void checkSingleItemContainer(int size, const std::string& caller);
}

#endif
