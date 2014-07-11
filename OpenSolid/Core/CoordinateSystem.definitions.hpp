/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

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
            const Vector<double, iNumDimensions>& basisVector
        );

        CoordinateSystem(
            const Point<iNumDimensions>& originPoint,
            const Vector<double, iNumDimensions>& xBasisVector,
            const Vector<double, iNumDimensions>& yBasisVector
        );

        CoordinateSystem(
            const Point<iNumDimensions>& originPoint,
            const Vector<double, iNumDimensions>& xBasisVector,
            const Vector<double, iNumDimensions>& yBasisVector,
            const Vector<double, iNumDimensions>& zBasisVector
        );
        
        const Point<iNumDimensions>&
        originPoint() const;
        
        const Matrix<double, iNumDimensions, iNumAxes>&
        basisMatrix() const;
        
        const Vector<double, iNumDimensions>
        basisVector() const;
        
        const Matrix<double, iNumAxes, iNumDimensions>&
        inverseMatrix() const;
        
        const Point<iNumDimensions>
        point(double value) const;
        
        const Point<iNumDimensions>
        point(double x, double y) const;

        const Point<iNumDimensions>
        point(double x, double y, double z) const;

        const Vector<double, iNumDimensions>
        vector(double value) const;
        
        const Vector<double, iNumDimensions>
        vector(double x, double y) const;
        
        const Vector<double, iNumDimensions>
        vector(double x, double y, double z) const;

        const Vector<double, iNumDimensions>
        xBasisVector() const;
        
        const Vector<double, iNumDimensions>
        yBasisVector() const;
        
        const Vector<double, iNumDimensions>
        zBasisVector() const;
        
        const Vector<double, iNumDimensions>
        basisVector(int axisIndex) const;
        
        const Axis<iNumDimensions>
        xAxis() const;
        
        const Axis<iNumDimensions>
        yAxis() const;
        
        const Axis<iNumDimensions>
        zAxis() const;
        
        const Axis<iNumDimensions>
        axis(int axisIndex) const;

        const Plane3d
        xyPlane() const;
        
        const Plane3d
        xzPlane() const;
        
        const Plane3d
        yxPlane() const;
        
        const Plane3d
        yzPlane() const;
        
        const Plane3d
        zxPlane() const;
        
        const Plane3d
        zyPlane() const;
        
        const Plane3d
        plane(int firstAxisIndex, int secondAxisIndex) const;
        
        const CoordinateSystem<iNumDimensions, iNumAxes>
        normalized() const;

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        x();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        y();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        z();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        xy();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        xz();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        yx();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        yz();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        zx();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        zy();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        xyz();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        xzy();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        yxz();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        yzx();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        zxy();

        static const CoordinateSystem<iNumDimensions, iNumAxes>
        zyx();
    };

    typedef CoordinateSystem<1, 1> CoordinateSystem1d;

    typedef CoordinateSystem<2, 1> AxialCoordinateSystem2d;
    typedef CoordinateSystem<2, 2> CoordinateSystem2d;

    typedef CoordinateSystem<3, 1> AxialCoordinateSystem3d;
    typedef CoordinateSystem<3, 2> PlanarCoordinateSystem3d;
    typedef CoordinateSystem<3, 3> CoordinateSystem3d;

    template <int iNumDimensions, int iNumAxes>
    struct ScalingFunction<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
        const CoordinateSystem<iNumDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            double scale
        ) const;
    };

    template <int iNumDimensions, int iNumAxes>
    struct TranslationFunction<CoordinateSystem<iNumDimensions, iNumAxes>>
    {
        const CoordinateSystem<iNumDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct TransformationFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        const CoordinateSystem<iNumResultDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    struct MorphingFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>
    {
        const CoordinateSystem<iNumResultDimensions, iNumAxes>
        operator()(
            const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
