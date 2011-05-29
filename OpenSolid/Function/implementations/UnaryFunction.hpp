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

#ifndef OPENSOLID__UNARYFUNCTION_HPP
#define OPENSOLID__UNARYFUNCTION_HPP

#include "../Function.hpp"
#include "../FunctionImplementation.hpp"

namespace OpenSolid
{
    class UnaryFunction : public FunctionImplementation
    {
    private:
        Function _operand;
    public:
        UnaryFunction(const Function& operand);
        
        const Function& operand() const;
        
        int parameters() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline const Function& UnaryFunction::operand() const {return _operand;}
}

#endif
