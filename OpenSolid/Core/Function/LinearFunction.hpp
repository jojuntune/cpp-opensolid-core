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
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Function.hpp>
 
// Internal headers
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class LinearFunction : public FunctionImplementation
    {
    private:
        Datum<iNumDimensions, iNumAxes> _datum;
    public:
        LinearFunction(const Datum<iNumDimensions, iNumAxes>& datum);
        
        const Datum<iNumDimensions, iNumAxes>& datum() const;
        
        int numParameters() const;
        int numDimensions() const;
        
        void getValues(const MapXcd& parameterValues, MapXd& results) const;
        void getBounds(const MapXcI& parameterBounds, MapXI& results) const;

        void getDerivative(int index, Function& result) const;
        
        void getTransformed(
            const MatrixXd& transformationMatrix,
            const VectorXd& translationVector,
            Function& result
        ) const;
        
        void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    LinearFunction<iNumDimensions, iNumAxes>::LinearFunction(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) : _datum(datum) {
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Datum<iNumDimensions, iNumAxes>&
    LinearFunction<iNumDimensions, iNumAxes>::datum() const {
        return _datum;
    }

    template <int iNumDimensions, int iNumAxes>
    int LinearFunction<iNumDimensions, iNumAxes>::numParameters() const {
        return iNumAxes;
    }
    
    template <int iNumDimensions, int iNumAxes>
    int LinearFunction<iNumDimensions, iNumAxes>::numDimensions() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::getValues(
        const MapXcd& parameterValues,
        MapXd& results
    ) const {
        results = datum() * parameterValues;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::getBounds(
        const MapXcI& parameterBounds,
        MapXI& results
    ) const {
        results = datum() * parameterBounds;
    }

    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::getDerivative(
        int index,
        Function& result
    ) const {
        result = datum().basisVector(index);
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::getTransformed(
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector,
        Function& result
    ) const {
        assert(transformationMatrix.rows() == translationVector.size());
        assert(transformationMatrix.cols() == iNumDimensions);

        int numTransformedDimensions = transformationMatrix.rows();

        if (numTransformedDimensions == 1) {
            result = new LinearFunction<1, iNumAxes>(
                transformationMatrix.topLeftCorner<1, iNumDimensions>() * datum() +
                    translationVector
            );
        } else if (numTransformedDimensions == 2) {
            result = new LinearFunction<2, iNumAxes>(
                transformationMatrix.topLeftCorner<2, iNumDimensions>() * datum() +
                    translationVector
            );
        } else if (numTransformedDimensions == 3) {
            result = new LinearFunction<3, iNumAxes>(
                transformationMatrix.topLeftCorner<3, iNumDimensions>() * datum() +
                    translationVector
            );
        } else {
            assert(false);
            result = Function();
        }
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::debug(std::ostream& stream, int indent) const {
        stream << "LinearFunction<" << iNumDimensions << "," << iNumAxes << ">" << std::endl;
    }
}
