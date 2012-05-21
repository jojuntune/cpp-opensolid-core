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

#include <OpenSolid/Core/Common/Conversion.hpp>
#include <OpenSolid/Core/Common/SerializedDouble.pb.h>

#include <boost/lexical_cast.hpp>

namespace opensolid
{
    std::string Conversion<bool, std::string>::operator()(bool argument) const {
        return boost::lexical_cast<std::string>(argument);
    }

    bool Conversion<std::string, bool>::operator()(const std::string& argument) const {
        return boost::lexical_cast<bool>(argument);
    }

    std::string Conversion<int, std::string>::operator()(int argument) const {
        return boost::lexical_cast<std::string>(argument);
    }

    int Conversion<std::string, int>::operator()(const std::string& argument) const {
        return boost::lexical_cast<int>(argument);
    }

    std::string Conversion<double, std::string>::operator()(double argument) const {
        SerializedDouble temp;
        temp.set_value(argument);
        return temp.SerializeAsString();
    }

    double Conversion<std::string, double>::operator()(const std::string& argument) const {
        SerializedDouble temp;
        temp.ParseFromString(argument);
        return temp.value();
    }
}
