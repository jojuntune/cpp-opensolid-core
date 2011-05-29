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

#include "Error.hpp"
#include "check.hpp"

namespace OpenSolid
{
    void checkErrorHasData(bool has_data, const std::string& name, const std::string& caller) {
        if (!has_data) {throw Error("ErrorHasData", caller).set("name", name);}
    }
    
    void checkNonEmptyContainer(bool empty, const std::string& caller) {
        if (empty) {throw Error("NonEmptyContainer", caller);}
    }
    
    void checkSingleItemContainer(int size, const std::string& caller) {
        if (size != 1) {throw Error("SingleItemContainer", caller);}
    }
}
