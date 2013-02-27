/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
 *  ian.e.mackenzie@gmail.com                                                        *
 *                                                                                   *
 *  This library is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU Lesser General Public                       *
 *  License as published by the Free Software Foundation; either                     *
 *  version 2.1 of the License, or (at your option) any later version.               *
 *                                                                                   *
 *  This library is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 *  Lesser General Public License for more details.                                  *
 *                                                                                   *
 *  You should have received a copy of the GNU Lesser General Public                 *
 *  License along with this library; if not, write to the Free Software              *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 *                                                                                   *
 *************************************************************************************/

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
        OPENSOLID_CORE_EXPORT BinaryOperation(
            const Function& firstOperand,
            const Function& secondOperand
        );
        
        const Function& firstOperand() const;
        const Function& secondOperand() const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
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
