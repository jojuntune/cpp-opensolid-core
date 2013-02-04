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
#include <OpenSolid/Core/Datum.hpp>

// Internal headers
#include <OpenSolid/Core/Function/UnaryOperation.hpp>

namespace opensolid
{
    class TransformedFunction : public UnaryOperation
    {
    private:
        MatrixXd _transformationMatrix;
        VectorXd _translationVector;
    public:
        OPENSOLID_CORE_EXPORT TransformedFunction(
            const Function& function,
            const MatrixXd& transformationMatrix,
            const VectorXd& translationVector
        );
        
        const MatrixXd& transformationMatrix() const;
        const VectorXd& translationVector() const;
        
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        
        OPENSOLID_CORE_EXPORT void getValues(const MapXcd& parameterValues, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void getBounds(const MapXcI& parameterBounds, MapXI& results) const;
        
        OPENSOLID_CORE_EXPORT void getDerivative(int index, Function& result) const;
        
        OPENSOLID_CORE_EXPORT void getComposition(
            const Function& innerFunction,
            Function& result
        ) const;

        OPENSOLID_CORE_EXPORT void getTransformed(
            const MatrixXd& transformationMatrix,
            const VectorXd& translationVector,
            Function& result
        ) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const MatrixXd& TransformedFunction::transformationMatrix() const {
        return _transformationMatrix;
    }

    inline const VectorXd& TransformedFunction::translationVector() const {
        return _translationVector;
    }
}
