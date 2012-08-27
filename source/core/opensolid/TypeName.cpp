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

#include <opensolid/TypeName.hpp>

namespace opensolid
{
    const std::string& TypeName<bool>::operator()() const {
        static const std::string result("Bool");
        return result;
    }

    const std::string& TypeName<int>::operator()() const {
        static const std::string result("Int");
        return result;
    }

    const std::string& TypeName<double>::operator()() const {
        static const std::string result("Double");
        return result;
    }

    const std::string& TypeName<std::string>::operator()() const {
        static const std::string result("String");
        return result;
    }
}
