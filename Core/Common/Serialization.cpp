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

#include <OpenSolid/Core/Common/Serialization.hpp>
#include <OpenSolid/Core/Common/SerializedInt.pb.h>
#include <OpenSolid/Core/Common/SerializedDouble.pb.h>

namespace OpenSolid
{
    std::string Serialization<int>::operator()(int argument) const {
        SerializedInt temp;
        temp.set_value(argument);
        return temp.SerializeAsString();
    }

    std::string Serialization<double>::operator()(double argument) const {
        SerializedDouble temp;
        temp.set_value(argument);
        return temp.SerializeAsString();
    }

    std::string Serialization<std::string>::operator()(const std::string& argument) const {
        return argument;
    }
}
