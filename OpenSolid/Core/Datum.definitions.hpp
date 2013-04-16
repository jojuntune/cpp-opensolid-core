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

#include <OpenSolid/Core/Datum.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Datum/TransformedDatum.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class Datum :
        public Transformable<Datum<iNumDimensions, iNumAxes>>,
        public Convertible<Datum<iNumDimensions, iNumAxes>>
    {
    private:
        Point<iNumDimensions> _originPoint;
        Matrix<double, iNumDimensions, iNumAxes> _basisMatrix;
        Matrix<double, iNumAxes, iNumDimensions> _inverseMatrix;

        void initialize(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        void initialize(const Datum<iNumDimensions, iNumAxes>& otherDatum );
    public:
        Datum();

        Datum(const Point<iNumDimensions>& originPoint);

        Datum(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        Datum(const Datum<iNumDimensions, iNumAxes>& otherDatum);
        
        Datum<iNumDimensions, iNumAxes>& operator=(
            const Datum<iNumDimensions, iNumAxes>& otherDatum
        );

        // Defined in Function.hpp
        template <int iArgumentDimensions>
        Datum(const TransformedDatum<iArgumentDimensions, iNumAxes>& transformedDatum);
        
        const Point<iNumDimensions>&
        originPoint() const;
        
        const Matrix<double, iNumDimensions, iNumAxes>&
        basisMatrix() const;
        
        const Matrix<double, iNumDimensions, iNumAxes>&
        basisVector() const;
        
        const Matrix<double, iNumAxes, iNumDimensions>&
        inverseMatrix() const;
        
        Point<iNumDimensions>
        point(double x) const;
        
        Point<iNumDimensions>
        point(double x, double y) const;

        Point<iNumDimensions>
        point(double x, double y, double z) const;

        Matrix<double, iNumDimensions, 1>
        vector(double x) const;
        
        Matrix<double, iNumDimensions, 1>
        vector(double x, double y) const;
        
        Matrix<double, iNumDimensions, 1>
        vector(double x, double y, double z) const;

        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
        xBasisVector() const;
        
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
        yBasisVector() const;
        
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
        zBasisVector() const;
        
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
        basisVector(int axisIndex) const;

        Matrix<double, iNumDimensions, 1>
        normalVector() const;
        
        Datum<iNumDimensions, 1>
        xAxis() const;
        
        Datum<iNumDimensions, 1>
        yAxis() const;
        
        Datum<iNumDimensions, 1>
        zAxis() const;
        
        Datum<iNumDimensions, 1>
        axis(int axisIndex) const;
        
        Datum<iNumDimensions, 1>
        normalAxis() const;

        Datum<3, 2>
        xyPlane() const;
        
        Datum<3, 2>
        xzPlane() const;
        
        Datum<3, 2>
        yxPlane() const;
        
        Datum<3, 2>
        yzPlane() const;
        
        Datum<3, 2>
        zxPlane() const;
        
        Datum<3, 2>
        zyPlane() const;
        
        Datum<3, 2>
        plane(int firstAxisIndex, int secondAxisIndex) const;
        
        Datum<3, 2>
        normalPlane() const;

        Datum<iNumDimensions, iNumAxes>
        reversed() const;
        
        Datum<iNumDimensions, iNumAxes>
        xReversed() const;
        
        Datum<iNumDimensions, iNumAxes>
        yReversed() const;
        
        Datum<iNumDimensions, iNumAxes>
        zReversed() const;
        
        Datum<iNumDimensions, iNumAxes>
        reversed(int index) const;

        Datum<iNumDimensions, iNumAxes>
        offset(double distance) const;
        
        Datum<iNumDimensions, iNumAxes>
        normalized() const;
        
        TransformedDatum<iNumDimensions, iNumAxes>
        mapped(const Function& function) const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    struct ScalingFunction<Datum<iNumDimensions, iNumAxes>>
    {
        Datum<iNumDimensions, iNumAxes>
        operator()(const Datum<iNumDimensions, iNumAxes>& datum, double scale) const;
    };

    template <int iNumDimensions, int iNumAxes>
    struct TranslationFunction<Datum<iNumDimensions, iNumAxes>>
    {
        template <class TVector>
        Datum<iNumDimensions, iNumAxes>
        operator()(
            const Datum<iNumDimensions, iNumAxes>& datum,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumAxes, int iTransformedDimensions>
    struct TransformationFunction<Datum<iNumDimensions, iNumAxes>, iTransformedDimensions>
    {
        typedef Datum<iTransformedDimensions, iNumAxes> ResultType;

        template <class TMatrix>
        Datum<iTransformedDimensions, iNumAxes>
        operator()(
            const Datum<iNumDimensions, iNumAxes>& datum,
            const EigenBase<TMatrix>& transformationMatrix
        ) const;
    };
}
