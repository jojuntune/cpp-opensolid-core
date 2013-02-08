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
    class EllipticalFunction : public FunctionImplementation
    {
    private:
        Datum<iNumDimensions, iNumAxes> _datum;
        Matrix<bool, 1, iNumAxes - 1> _convention;
    public:
        EllipticalFunction(
            const Datum<iNumDimensions, iNumAxes>& datum,
            const Matrix<bool, 1, iNumAxes - 1>& convention
        );
        
        const Datum<iNumDimensions, iNumAxes>& datum() const;
        const Matrix<bool, 1, iNumAxes - 1>& convention() const;
        
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
    EllipticalFunction<iNumDimensions, iNumAxes>::EllipticalFunction(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Matrix<bool, 1, iNumAxes - 1>& convention
    ) : _datum(datum),
        _convention(convention) {
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Datum<iNumDimensions, iNumAxes>&
    EllipticalFunction<iNumDimensions, iNumAxes>::datum() const {
        return _datum;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<bool, 1, iNumAxes - 1>&
    EllipticalFunction<iNumDimensions, iNumAxes>::convention() const {
        return _convention;
    }

    template <int iNumDimensions, int iNumAxes>
    int EllipticalFunction<iNumDimensions, iNumAxes>::numParameters() const {
        return iNumAxes - 1;
    }
    
    template <int iNumDimensions, int iNumAxes>
    int EllipticalFunction<iNumDimensions, iNumAxes>::numDimensions() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void EllipticalFunction<iNumDimensions, iNumAxes>::getValues(
        const MapXcd& parameterValues,
        MapXd& results
    ) const {
        MatrixXd local = MatrixXd::Ones(iNumAxes, parameterValues.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameterValues.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    sin(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameterValues.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    cos(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = datum() * local;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void EllipticalFunction<iNumDimensions, iNumAxes>::getBounds(
        const MapXcI& parameterBounds,
        MapXI& results
    ) const {
        MatrixXI local = MatrixXI::Ones(iNumAxes, parameterBounds.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameterBounds.row(i).array());
                local.bottomRows(numParameters()- i).array() *=
                    sin(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameterBounds.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    cos(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = datum() * local;
    }

    template <int iNumDimensions, int iNumAxes>
    void EllipticalFunction<iNumDimensions, iNumAxes>::getDerivative(
        int index,
        Function& result
    ) const {
        Matrix<double, iNumDimensions, iNumAxes> derivativeBasisMatrix = datum().basisMatrix();

        Matrix<bool, 1, iNumAxes - 1> derivativeConvention = convention();
        derivativeConvention(index) = !derivativeConvention(index);

        if (convention()(index)) {
            derivativeBasisMatrix.col(index) = -derivativeBasisMatrix.col(index);
        } else {
            int numFlipped = numParameters() - index;
            derivativeBasisMatrix.rightCols(numFlipped) =
                -derivativeBasisMatrix.rightCols(numFlipped);
        }
        result = new EllipticalFunction<iNumDimensions, iNumAxes>(
            Datum<iNumDimensions, iNumAxes>(
                Matrix<double, iNumDimensions, 1>::Zero(),
                derivativeBasisMatrix
            ),
            derivativeConvention
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    void EllipticalFunction<iNumDimensions, iNumAxes>::getTransformed(
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector,
        Function& result
    ) const {
        assert(transformationMatrix.rows() == translationVector.size());
        assert(transformationMatrix.cols() == iNumDimensions);

        int numTransformedDimensions = transformationMatrix.rows();

        if (numTransformedDimensions == 2) {
            result = new EllipticalFunction<2, iNumAxes>(
                transformationMatrix.topLeftCorner<2, iNumDimensions>() * datum() +
                    translationVector,
                convention()
            );
        } else if (numTransformedDimensions == 3) {
            result = new EllipticalFunction<3, iNumAxes>(
                transformationMatrix.topLeftCorner<3, iNumDimensions>() * datum() +
                    translationVector,
                convention()
            );
        } else {
            assert(false);
            result = Function();
        }
    }
    
    template <int iNumDimensions, int iNumAxes>
    void EllipticalFunction<iNumDimensions, iNumAxes>::debug(
        std::ostream& stream,
        int indent
    ) const {
        stream << "EllipticalFunction<" << iNumDimensions << "," << iNumAxes << ">" << std::endl;
    }
}
