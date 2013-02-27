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
    class UnaryOperation : public FunctionImplementation
    {
    private:
        Function _operand;
    public:
        OPENSOLID_CORE_EXPORT UnaryOperation(const Function& operand);
        
        const Function& operand() const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
    protected:
        template <class TDerived>
        static bool IsDuplicate(const TDerived* derived, const Function& function);
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const Function& UnaryOperation::operand() const {
        return _operand;
    }

    // Performs a simple duplication check by checking whether both arguments have the same type
    // and duplicate operands. Note that this is only valid for simple unary operations with no
    // additional associated data, e.g., it is valid for SineFunction but not ScalingFunction (since
    // ScalingFunction contains a scaling factor in addition to its Function operand).
    template <class TDerived>
    bool UnaryOperation::IsDuplicate(const TDerived* derived, const Function& function) {
        const TDerived* other = dynamic_cast<const TDerived*>(function.implementation());
        if (other) {
            return derived->operand().isDuplicate(other->operand());
        } else {
            return false;
        }
    }
}
