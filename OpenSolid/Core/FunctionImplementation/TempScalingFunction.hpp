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

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/FunctionImplementation/UnaryOperation.hpp>

namespace opensolid
{
    class TempScalingFunction :
        public UnaryOperation
    {
    private:
        double _scale;
        
        OPENSOLID_CORE_EXPORT
        int
        numDimensionsImpl() const;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        derivativeImpl(int parameterIndex) const;

        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        scaledImpl(double scale) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        transformedImpl(const MatrixXd& transformationMatrix) const;
        
        OPENSOLID_CORE_EXPORT
        void
        debugImpl(std::ostream& stream, int indent) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        withNewOperandImpl(const FunctionImplementationPtr& newOperand) const;
    public:
        OPENSOLID_CORE_EXPORT
        TempScalingFunction(double scale, const FunctionImplementationPtr& operand);

        double
        scale() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline double
    TempScalingFunction::scale() const {
        return _scale;
    }
}
