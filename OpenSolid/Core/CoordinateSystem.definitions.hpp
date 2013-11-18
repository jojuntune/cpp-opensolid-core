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

#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class CoordinateSystem :
        public Transformable<CoordinateSystem<iNumDimensions, iNumAxes>>,
        public Convertible<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
    private:
        Point<iNumDimensions> _originPoint;
        Matrix<double, iNumDimensions, iNumAxes> _basisMatrix;
        Matrix<double, iNumAxes, iNumDimensions> _inverseMatrix;
    public:
        CoordinateSystem();

        explicit
        CoordinateSystem(const Point<iNumDimensions>& originPoint);

        CoordinateSystem(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        CoordinateSystem(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, 1>& xBasisVector,
            const Matrix<double, iNumDimensions, 1>& yBasisVector
        );

        CoordinateSystem(
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumDimensions, 1>& xBasisVector,
            const Matrix<double, iNumDimensions, 1>& yBasisVector,
            const Matrix<double, iNumDimensions, 1>& zBasisVector
        );
        
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
        
        Axis<iNumDimensions>
        xAxis() const;
        
        Axis<iNumDimensions>
        yAxis() const;
        
        Axis<iNumDimensions>
        zAxis() const;
        
        Axis<iNumDimensions>
        axis(int axisIndex) const;

        Plane3d
        xyPlane() const;
        
        Plane3d
        xzPlane() const;
        
        Plane3d
        yxPlane() const;
        
        Plane3d
        yzPlane() const;
        
        Plane3d
        zxPlane() const;
        
        Plane3d
        zyPlane() const;
        
        Plane3d
        plane(int firstAxisIndex, int secondAxisIndex) const;
        
        CoordinateSystem<iNumDimensions, iNumAxes>
        normalized() const;

        static CoordinateSystem<iNumDimensions, iNumAxes>
        Global();
    };

    typedef CoordinateSystem<1, 1> CoordinateSystem1d;

    typedef CoordinateSystem<2, 1> AxialCoordinateSystem2d;
    typedef CoordinateSystem<2, 2> CoordinateSystem2d;

    typedef CoordinateSystem<3, 1> AxialCoordinateSystem3d;
    typedef CoordinateSystem<3, 2> PlanarCoordinateSystem3d;
    typedef CoordinateSystem<3, 3> CoordinateSystem3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    struct NumDimensions<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct TransformedType<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        typedef CoordinateSystem<iNumResultDimensions, iNumAxes> Type;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct MorphedType<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        typedef CoordinateSystem<iNumResultDimensions, iNumAxes> Type;
    };

    template <int iNumDimensions, int iNumAxes>
    struct ScalingFunction<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
        CoordinateSystem<iNumDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            double scale
        ) const;
    };

    template <int iNumDimensions, int iNumAxes>
    struct TranslationFunction<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
        template <class TVector>
        CoordinateSystem<iNumDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct TransformationFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        template <class TMatrix>
        CoordinateSystem<iNumResultDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const EigenBase<TMatrix>& transformationMatrix
        ) const;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct MorphingFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        CoordinateSystem<iNumResultDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
