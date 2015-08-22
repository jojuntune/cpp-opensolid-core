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
#include <OpenSolid/Core/Handedness.definitions.hpp>
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
        public Transformable<Frame<2>, Point<2>>,
        public Convertible<Frame<2>>
    {
    private:
        Handedness _handedness;
    public:
        Frame();

        explicit
        Frame(const Point<2>& originPoint);

        Frame(const Point<2>& originPoint, const Matrix<double, 2, 2>& basisMatrix);

        Frame(const Point<2>& originPoint, const Quaternion<2>& orientation);

        Frame(
            const Point<2>& originPoint,
            const UnitVector<2>& xDirectionVector,
            const UnitVector<2>& yDirectionVector
        );

        Frame(
            const Point<2>& originPoint,
            const UnitVector<2>& xDirectionVector,
            const UnitVector<2>& yDirectionVector,
            Handedness handedness
        );

        Handedness
        handedness() const;

        UnitVector<2>
        xDirectionVector() const;
        
        UnitVector<2>
        yDirectionVector() const;
        
        Axis<2>
        xAxis() const;
        
        Axis<2>
        yAxis() const;

        template <class TTransformation>
        Frame<2>
        transformedBy(const TTransformation& transformation) const;

        Plane3d
        placedOnto(const Plane3d& plane) const;

        ParametricExpression<Point<2>, Point<2>>
        expression() const;
    };

    typedef Frame<2> Frame2d;

    template <>
    class Frame<3> :
        public FrameBase<3, 3>,
        public Transformable<Frame<3>, Point<3>>,
        public Convertible<Frame<3>>
    {
    private:
        Handedness _handedness;
    public:
        Frame();

        explicit
        Frame(const Point<3>& originPoint);

        Frame(const Point<3>& originPoint, const Matrix<double, 3, 3>& basisMatrix);

        Frame(const Point<3>& originPoint, const Quaternion<3>& orientation);

        Frame(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            const UnitVector<3>& zDirectionVector
        );

        Frame(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            const UnitVector<3>& zDirectionVector,
            Handedness handedness
        );

        Handedness
        handedness() const;

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

        template <class TTransformation>
        Frame<3>
        transformedBy(const TTransformation& transformation) const;

        ParametricExpression<Point<3>, Point<3>>
        expression() const;
    };

    typedef Frame<3> Frame3d;
}
