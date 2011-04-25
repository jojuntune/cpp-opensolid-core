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

#include "BinaryFunction.hpp"

namespace opensolid
{
    BinaryFunction::BinaryFunction(const Function& first_operand, const Function& second_operand) :
        _first_operand(first_operand), _second_operand(second_operand) {
        bool equal_parameters = first_operand.parameters() == second_operand.parameters();
        bool first_is_constant = first_operand.isA<ConstantFunction>();
        bool second_is_constant = second_operand.isA<ConstantFunction>();
        assert(equal_parameters || first_is_constant || second_is_constant);
    }
    
    int BinaryFunction::parameters() const {
        return max(firstOperand().parameters(), secondOperand().parameters());
    }
}
