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

#include <OpenSolid/Core/Generic/TypeName.hpp>

namespace opensolid
{
    std::string TypeName<bool>::operator()() const {return "Bool";}

    std::string TypeName<short>::operator()() const {return "Short";}

    std::string TypeName<unsigned short>::operator()() const {return "UnsignedShort";}

    std::string TypeName<int>::operator()() const {return "Int";}

    std::string TypeName<unsigned>::operator()() const {return "Unsigned";}

    std::string TypeName<long>::operator()() const {return "Long";}

    std::string TypeName<unsigned long>::operator()() const {return "UnsignedLong";}

    std::string TypeName<long long>::operator()() const {return "LongLong";}

    std::string TypeName<unsigned long long>::operator()() const {return "UnsignedLongLong";}

    std::string TypeName<float>::operator()() const {return "Float";}

    std::string TypeName<double>::operator()() const {return "Double";}

    std::string TypeName<long double>::operator()() const {return "LongDouble";}

    std::string TypeName<std::string>::operator()() const {return "String";}
}
