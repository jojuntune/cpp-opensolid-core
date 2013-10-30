/************************************************************************************
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

#include <OpenSolid/Core/FunctionImplementation.definitions.hpp>

namespace opensolid
{
    class BinaryOperation :
        public FunctionImplementation
    {
    private:
        FunctionImplementationPtr _firstOperand;
        FunctionImplementationPtr _secondOperand;
        
        OPENSOLID_CORE_EXPORT
        int
        numParametersImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        composedImpl(const FunctionImplementationPtr& innerFunction) const override;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        withNewOperandsImpl(
            const FunctionImplementationPtr& newFirstOperand,
            const FunctionImplementationPtr& newSecondOperand
        ) const = 0;
    protected:
        OPENSOLID_CORE_EXPORT
        bool
        duplicateOperands(const FunctionImplementationPtr& other, bool isCommutative) const;
    public:
        OPENSOLID_CORE_EXPORT
        BinaryOperation(
            const FunctionImplementationPtr& firstOperand,
            const FunctionImplementationPtr& secondOperand
        );
        
        const FunctionImplementationPtr&
        firstOperand() const;
        
        const FunctionImplementationPtr&
        secondOperand() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        withNewOperands(
            const FunctionImplementationPtr& newFirstOperand,
            const FunctionImplementationPtr& newSecondOperand
        ) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline
    const FunctionImplementationPtr&
    BinaryOperation::firstOperand() const {
        return _firstOperand;
    }
    
    inline
    const FunctionImplementationPtr&
    BinaryOperation::secondOperand() const {
        return _secondOperand;
    }
}
