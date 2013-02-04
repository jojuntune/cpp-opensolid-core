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

#include <OpenSolid/config.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

// Internal headers
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>

namespace opensolid
{
    class BinaryOperation : public FunctionImplementation
    {
    private:
        Function _firstOperand;
        Function _secondOperand;
    public:
        BinaryOperation(const Function& firstOperand, const Function& secondOperand);
        
        const Function& firstOperand() const;
        const Function& secondOperand() const;
        
        int numParameters() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const Function& BinaryOperation::firstOperand() const {
        return _firstOperand;
    }
    
    inline const Function& BinaryOperation::secondOperand() const {
        return _secondOperand;
    }
}
