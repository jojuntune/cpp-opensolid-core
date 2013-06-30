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
    class LinearFunction :
        public FunctionImplementation
    {
    private:
        Datum<iNumDimensions, iNumAxes> _datum;
    public:
        LinearFunction(const Datum<iNumDimensions, iNumAxes>& datum);
        
        const Datum<iNumDimensions, iNumAxes>&
        datum() const;
        
        int
        numParametersImpl() const;
        
        int
        numDimensionsImpl() const;

        bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const;
        
        FunctionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const;
        
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
        
        FunctionImplementationPtr
        scaled(double scale) const;

        FunctionImplementationPtr
        transformed(const MatrixXd& transformationMatrix) const;
        
        FunctionImplementationPtr
        translated(const VectorXd& vector) const;
        
        void
        debugImpl(std::ostream& stream, int indent) const;
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
    int
    LinearFunction<iNumDimensions, iNumAxes>::numParametersImpl() const {
        return iNumAxes;
    }
    
    template <int iNumDimensions, int iNumAxes>
    int
    LinearFunction<iNumDimensions, iNumAxes>::numDimensionsImpl() const {
        return iNumDimensions;
    }

    template <int iNumDimensions, int iNumAxes>
    bool
    LinearFunction<iNumDimensions, iNumAxes>::isDuplicateOf(const FunctionImplementationPtr& function) const {
        const LinearFunction<iNumDimensions, iNumAxes>* other =
            dynamic_cast<const LinearFunction<iNumDimensions, iNumAxes>*>(
                function.implementation()
            );
        if (other) {
            return (this->datum().originPoint() - other->datum().originPoint()).isZero() &&
                (this->datum().basisMatrix() - other->datum().basisMatrix()).isZero();
        } else {
            return false;
        }
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    LinearFunction<iNumDimensions, iNumAxes>::deduplicated(
        DeduplicationCache& deduplicationCache
    ) const {
        return this;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    LinearFunction<iNumDimensions, iNumAxes>::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = (datum().basisMatrix() * parameterValues).colwise() +
            datum().originPoint().vector();
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    LinearFunction<iNumDimensions, iNumAxes>::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = (datum().basisMatrix().template cast<Interval>() * parameterBounds).colwise() +
            datum().originPoint().vector().template cast<Interval>();
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    LinearFunction<iNumDimensions, iNumAxes>::derivativeImpl(int parameterIndex) const {
        return new ConstantFunction(datum().basisVector(index), numParameters());
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    LinearFunction<iNumDimensions, iNumAxes>::scaled(double scale) const {
        return new LinearFunction<iNumDimensions, iNumAxes>(
            Datum<iNumDimensions, iNumAxes>::scaling(datum(), scale)
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    LinearFunction<iNumDimensions, iNumAxes>::transformed(
        const MatrixXd& transformationMatrix
    ) const {
        int numTransformedDimensions = transformationMatrix.rows();
        if (numTransformedDimensions == 1) {
            return new LinearFunction<1, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<1, iNumDimensions>()
                )
            );
        } else if (numTransformedDimensions == 2) {
            return new LinearFunction<2, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<2, iNumDimensions>()
                )
            );
        } else if (numTransformedDimensions == 3) {
            return new LinearFunction<3, iNumAxes>(
                Datum<iNumDimensions, iNumAxes>::transformation(
                    datum(),
                    transformationMatrix.topLeftCorner<3, iNumDimensions>()
                )
            );
        } else {
            assert(false);
            return FunctionImplementationPtr();
        }
    }

    template <int iNumDimensions, int iNumAxes>
    FunctionImplementationPtr
    LinearFunction<iNumDimensions, iNumAxes>::translated(const VectorXd& vector) const {
        return new LinearFunction<iNumDimensions, iNumAxes>(datum().translated(vector));
    }
    
    template <int iNumDimensions, int iNumAxes>
    void
    LinearFunction<iNumDimensions, iNumAxes>::debugImpl(std::ostream& stream, int indent) const {
        stream << "LinearFunction<" << iNumDimensions << "," << iNumAxes << ">" << std::endl;
    }
}
