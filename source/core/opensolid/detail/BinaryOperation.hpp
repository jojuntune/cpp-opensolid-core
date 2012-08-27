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

#pragma once

#include <opensolid/detail/FunctionImplementation.hpp>
#include <opensolid/Function.hpp>

namespace opensolid
{
    class BinaryOperation : public FunctionImplementation
    {
    private:
        Function _first_operand;
        Function _second_operand;
    public:
        BinaryOperation(const Function& first_operand, const Function& second_operand);
        
        const Function& firstOperand() const;
        const Function& secondOperand() const;
        
        int parameters() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const Function& BinaryOperation::firstOperand() const {return _first_operand;}
    
    inline const Function& BinaryOperation::secondOperand() const {return _second_operand;}
}
