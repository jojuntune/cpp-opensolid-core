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
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>

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

        bool isDuplicateOf(const Function& other) const;
        Function deduplicated(DeduplicationCache& deduplicationCache) const;
        
        void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const;
        
        void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const;

        Function derivative(int index) const;
        
        Function scaled(double scale) const;
        Function transformed(const MatrixXd& transformationMatrix) const;
        Function translated(const VectorXd& vector) const;
        
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
    bool LinearFunction<iNumDimensions, iNumAxes>::isDuplicateOf(const Function& function) const {
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
    Function LinearFunction<iNumDimensions, iNumAxes>::deduplicated(std::vector<Function>&) const {
        return this;
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results = (datum().basisMatrix() * parameterValues).colwise() +
            datum().originPoint().vector();
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results = (datum().basisMatrix().template cast<Interval>() * parameterBounds).colwise() +
            datum().originPoint().vector().template cast<Interval>();
    }

    template <int iNumDimensions, int iNumAxes>
    Function LinearFunction<iNumDimensions, iNumAxes>::derivative(int index) const {
        return Function::Constant(datum().basisVector(index), numParameters());
    }

    template <int iNumDimensions, int iNumAxes>
    Function LinearFunction<iNumDimensions, iNumAxes>::scaled(double scale) const {
        return new LinearFunction<iNumDimensions, iNumAxes>(
            Datum<iNumDimensions, iNumAxes>::scaling(datum(), scale)
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    Function LinearFunction<iNumDimensions, iNumAxes>::transformed(
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
            return Function();
        }
    }

    template <int iNumDimensions, int iNumAxes>
    Function LinearFunction<iNumDimensions, iNumAxes>::translated(const VectorXd& vector) const {
        return new LinearFunction<iNumDimensions, iNumAxes>(datum().translated(vector));
    }
    
    template <int iNumDimensions, int iNumAxes>
    void LinearFunction<iNumDimensions, iNumAxes>::debug(std::ostream& stream, int indent) const {
        stream << "LinearFunction<" << iNumDimensions << "," << iNumAxes << ">" << std::endl;
    }
}
