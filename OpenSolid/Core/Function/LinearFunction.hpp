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

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Function.hpp>
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
        
        void getValues(const MapXcd& parameter_values, MapXd& results) const;
        void getBounds(const MapXcI& parameter_bounds, MapXI& results) const;

        void getDerivative(int index, Function& result) const;
        
        void getTransformed(
            const MatrixXd& matrix,
            const VectorXd& vector,
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
        const MapXcd& parameter_values,
        MapXd& results
    ) const {
        results = datum() * parameter_values;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::getBounds(
        const MapXcI& parameter_bounds,
        MapXI& results
    ) const {
        results = datum() * parameter_bounds;
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
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {
        assert(matrix.rows() == vector.size());
        assert(matrix.cols() == iNumDimensions);

        int numTransformedDimensions = matrix.rows();

        if (numTransformedDimensions == 1) {
            result = new LinearFunction<1, iNumAxes>(
                matrix.topLeftCorner<1, iNumDimensions>() * datum() + vector
            );
        } else if (numTransformedDimensions == 2) {
            result = new LinearFunction<2, iNumAxes>(
                matrix.topLeftCorner<2, iNumDimensions>() * datum() + vector
            );
        } else if (numTransformedDimensions == 3) {
            result = new LinearFunction<3, iNumAxes>(
                matrix.topLeftCorner<3, iNumDimensions>() * datum() + vector
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
