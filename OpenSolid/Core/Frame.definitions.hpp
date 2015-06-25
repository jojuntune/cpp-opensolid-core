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

#include <OpenSolid/Core/Frame.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/FrameBase.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Quaternion.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Frame<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Frame<2> :
        public FrameBase<2, 2>,
        public Transformable<Frame<2>, 2>,
        public Convertible<Frame<2>>
    {
    public:
        Frame();

        Frame(const Point<2>& originPoint);

        Frame(const Point<2>& originPoint, const Matrix<double, 2, 2>& basisMatrix);

        Frame(const Point<2>& originPoint, const Quaternion<2>& orientation);

        Frame(
            const Point<2>& originPoint,
            const UnitVector<2>& xDirectionVector,
            const UnitVector<2>& yDirectionVector
        );

        UnitVector<2>
        xDirectionVector() const;
        
        UnitVector<2>
        yDirectionVector() const;
        
        Axis<2>
        xAxis() const;
        
        Axis<2>
        yAxis() const;

        Frame<2>
        scaledAbout(const Point<2>& point, double scale) const;

        Frame<2>
        rotatedAbout(const Point<2>& point, const Matrix<double, 2, 2>& rotationMatrix) const;

        using Transformable<Frame<2>, 2>::rotatedAbout;

        Frame<2>
        translatedBy(const Vector<double, 2>& vector) const;

        Frame<2>
        toLocalIn(const Frame<2>& frame) const;

        Frame<2>
        toGlobalFrom(const Frame<2>& frame) const;

        Frame<2>
        mirroredAbout(const Point<2>& point, const UnitVector<2>& direction) const;

        using Transformable<Frame<2>, 2>::mirroredAbout;

        ParametricExpression<Point<2>, Point<2>>
        expression() const;
    };

    typedef Frame<2> Frame2d;

    template <>
    class Frame<3> :
        public FrameBase<3, 3>,
        public Transformable<Frame<3>, 3>,
        public Convertible<Frame<3>>
    {
    public:
        Frame();

        Frame(const Point<3>& originPoint);

        Frame(const Point<3>& originPoint, const Matrix<double, 3, 3>& basisMatrix);

        Frame(const Point<3>& originPoint, const Quaternion<3>& orientation);

        Frame(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            const UnitVector<3>& zDirectionVector
        );

        UnitVector<3>
        xDirectionVector() const;
        
        UnitVector<3>
        yDirectionVector() const;
        
        UnitVector<3>
        zDirectionVector() const;
        
        Axis<3>
        xAxis() const;
        
        Axis<3>
        yAxis() const;
        
        Axis<3>
        zAxis() const;

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

        Frame<3>
        scaledAbout(const Point<3>& point, double scale) const;

        Frame<3>
        rotatedAbout(const Point<3>& point, const Matrix<double, 3, 3>& rotationMatrix) const;

        using Transformable<Frame<3>, 3>::rotatedAbout;

        Frame<3>
        translatedBy(const Vector<double, 3>& vector) const;

        Frame<3>
        toLocalIn(const Frame<3>& frame) const;

        Frame<3>
        toGlobalFrom(const Frame<3>& frame) const;

        Frame<3>
        mirroredAbout(const Point<3>& point, const UnitVector<3>& direction) const;

        using Transformable<Frame<3>, 3>::mirroredAbout;

        ParametricExpression<Point<3>, Point<3>>
        expression() const;
    };

    typedef Frame<3> Frame3d;
}
