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
#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class EllipticalFunction :
        public FunctionImplementation
    {
    private:
        Datum<iNumDimensions, iNumAxes> _datum;
        Matrix<bool, 1, iNumAxes - 1> _convention;
        
        int
        numDimensionsImpl() const;
        
        int
        numParametersImpl() const;
        
        void
        evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const;
        
        void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const;

        FunctionImplementationPtr
        derivativeImpl(int parameterIndex) const;

        bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const;
        
        FunctionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const;
        
        FunctionImplementationPtr
        scaledImpl(double scale) const;
        
        FunctionImplementationPtr
        transformedImpl(const MatrixXd& transformationMatrix) const;
        
        FunctionImplementationPtr
        translatedImpl(const VectorXd& vector) const;
        
        void
        debugImpl(std::ostream& stream, int indent) const;
    public:
        EllipticalFunction(
            const Datum<iNumDimensions, iNumAxes>& datum,
            const Matrix<bool, 1, iNumAxes - 1>& convention
        );
        
        const Datum<iNumDimensions, iNumAxes>&
        datum() const;
        
        const Matrix<bool, 1, iNumAxes - 1>&
        convention() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    int
    EllipticalFunction<iNumDimensions, iNumAxes>::numDimensionsImpl() const {
        return iNumDimensions;
    }

    template <int iNumDimensions, int iNumAxes>
    int
    EllipticalFunction<iNumDimensions, iNumAxes>::numParametersImpl() const {
        return iNumAxes - 1;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    EllipticalFunction<iNumDimensions, iNumAxes>::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        Matrix<double, iNumAxes, Dynamic> localCoordinates =
            Matrix<double, iNumAxes, Dynamic>::Ones(iNumAxes, parameterValues.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                localCoordinates.row(i).array() *= cos(parameterValues.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    sin(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                localCoordinates.row(i).array() *= sin(parameterValues.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    cos(parameterValues.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = (datum().basisMatrix() * localCoordinates).colwise() +
            datum().originPoint().vector();
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    EllipticalFunction<iNumDimensions, iNumAxes>::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Matrix<Interval, iNumAxes, Dynamic> localCoordinates =
            Matrix<Interval, iNumAxes, Dynamic>::Ones(iNumAxes, parameterBounds.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                localCoordinates.row(i).array() *= cos(parameterBounds.row(i).array());
                localCoordinates.bottomRows(numParameters()- i).array() *=
                    sin(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                localCoordinates.row(i).array() *= sin(parameterBounds.row(i).array());
                localCoordinates.bottomRows(numParameters() - i).array() *=
                    cos(parameterBounds.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = (datum().basisMatrix().template cast<Interval>() * localCoordinates).colwise() +
            datum().originPoint().vector().template cast<Interval>();
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    EllipticalFunction<iNumDimensions, iNumAxes>::derivativeImpl(int parameterIndex) const {
        Matrix<double, iNumDimensions, iNumAxes> derivativeBasisMatrix = datum().basisMatrix();

        Matrix<bool, 1, iNumAxes - 1> derivativeConvention = convention();
        derivativeConvention(index) = !derivativeConvention(index);

        if (convention()(index)) {
            derivativeBasisMatrix.col(index) *= -1;
        } else {
            int numFlipped = numParameters() - index;
            derivativeBasisMatrix.rightCols(numFlipped) *= -1;
        }
        return new EllipticalFunction<iNumDimensions, iNumAxes>(
            Datum<iNumDimensions, iNumAxes>(
                Point<iNumDimensions>::Origin(),
                derivativeBasisMatrix
            ),
            derivativeConvention
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    bool
    EllipticalFunction<iNumDimensions, iNumAxes>::isDuplicateOfImpl(
        const FunctionImplementationPtr& other
    ) const {
        const EllipticalFunction<iNumDimensions, iNumAxes>* otherElliptical =
            other->cast<EllipticalFunction<iNumDimensions, iNumAxes>>();

        return (this->datum().originPoint() - otherElliptical->datum().originPoint()).isZero() &&
            (this->datum().basisMatrix() - otherElliptical->datum().basisMatrix()).isZero() &&
            this->convention() == otherElliptical->convention();
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    EllipticalFunction<iNumDimensions, iNumAxes>::deduplicatedImpl(
        DeduplicationCache& deduplicationCache
    ) const {
        return this;
    }
    
    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    EllipticalFunction<iNumDimensions, iNumAxes>::scaledImpl(double scale) const {
        return new EllipticalFunction<iNumDimensions, iNumAxes>(
            Datum<iNumDimensions, iNumAxes>::scaling(datum(), scale),
            convention()
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    EllipticalFunction<iNumDimensions, iNumAxes>::transformedImpl(
        const MatrixXd& transformationMatrix
    ) const {
        int numTransformedDimensions = transformationMatrix.rows();
        if (numTransformedDimensions == 1) {
            return new EllipticalFunction<1, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<1, iNumDimensions>()
                ),
                convention()
            );
        } else if (numTransformedDimensions == 2) {
            return new EllipticalFunction<2, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<2, iNumDimensions>()
                ),
                convention()
            );
        } else if (numTransformedDimensions == 3) {
            return new EllipticalFunction<3, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<3, iNumDimensions>()
                ),
                convention()
            );
        } else {
            assert(false);
            return FunctionImplementationPtr();
        }
    }
    
    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    EllipticalFunction<iNumDimensions, iNumAxes>::translatedImpl(
        const VectorXd& vector
    ) const {
        return new EllipticalFunction<iNumDimensions, iNumAxes>(
            datum().translated(vector),
            convention()
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    EllipticalFunction<iNumDimensions, iNumAxes>::debugImpl(
        std::ostream& stream,
        int indent
    ) const {
        stream << "EllipticalFunction<" << iNumDimensions << "," << iNumAxes << ">" << std::endl;
    }

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
}
