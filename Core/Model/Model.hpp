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

#ifndef OPENSOLID__MODEL_HPP
#define OPENSOLID__MODEL_HPP

#include <unordered_map>

#include <boost/any.hpp>

#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Support/STL.hpp>

namespace OpenSolid
{
    class Model
    {
    private:
        std::unordered_map<std::string, boost::any> _elements;
    public:
        OPENSOLID_CORE_EXPORT Model();
        
        template <class Type>
        OPENSOLID_CORE_EXPORT Model& set(const std::string& name, const Type& argument);
        
        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;

        OPENSOLID_CORE_EXPORT const std::type_info& type(const std::string& name) const;

        template <class Type>
        OPENSOLID_CORE_EXPORT Type get(const std::string& name) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    
}

#endif
