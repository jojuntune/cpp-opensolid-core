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

#include <OpenSolid/Core/Rotation.declarations.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Quaternion.declarations.hpp>
#include <OpenSolid/Core/Transformation.definitions.hpp>

namespace opensolid
{
    template <>
    class Rotation<2> :
        public Transformation<Rotation<2>>
    {
    private:
        Point<2> _point;
        double _cosAngle;
        double _sinAngle;
    public:
        Rotation(const Point<2>& point, double angle);
        
        Rotation(const Point<2>& point, const Quaternion<2>& quaternion);

        Rotation(const Point<2>& point, const Matrix<double, 2, 2>& rotationMatrix);

        const Point<2>&
        point() const;

        double
        cosAngle() const;

        double
        sinAngle() const;

        double
        scale() const;

        Handedness
        transform(Handedness handedness) const;

        Point<2>
        transform(const Point<2>& point) const;

        template <class TParameter>
        ParametricExpression<Point<2>, TParameter>
        transform(const ParametricExpression<Point<2>, TParameter>& expression) const;

        Vector<double, 2>
        transform(const Vector<double, 2>& vector) const;

        template <class TParameter>
        ParametricExpression<Vector<double, 2>, TParameter>
        transform(const ParametricExpression<Vector<double, 2>, TParameter>& expression) const;

        UnitVector<2>
        transform(const UnitVector<2>& unitVector) const;

        template <class TParameter>
        ParametricExpression<UnitVector<2>, TParameter>
        transform(const ParametricExpression<UnitVector<2>, TParameter>& expression) const;
    };

    typedef Rotation<2> Rotation2d;

    template <>
    class Rotation<3> :
        public Transformation<Rotation<3>>
    {
    private:
        Point<3> _point;
        Matrix<double, 3, 3> _rotationMatrix;
    public:
        Rotation(const Point<3>& point, const Matrix<double, 3, 3>& rotationMatrix);

        Rotation(const Axis<3>& axis, double angle);
        
        Rotation(const Point<3>& point, const Quaternion<3>& quaternion);

        const Point<3>&
        point() const;

        const Matrix<double, 3, 3>&
        rotationMatrix() const;

        double
        scale() const;

        Handedness
        transform(Handedness handedness) const;

        Point<3>
        transform(const Point<3>& point) const;

        template <class TParameter>
        ParametricExpression<Point<3>, TParameter>
        transform(const ParametricExpression<Point<3>, TParameter>& expression) const;

        Vector<double, 3>
        transform(const Vector<double, 3>& vector) const;

        template <class TParameter>
        ParametricExpression<Vector<double, 3>, TParameter>
        transform(const ParametricExpression<Vector<double, 3>, TParameter>& expression) const;

        UnitVector<3>
        transform(const UnitVector<3>& unitVector) const;

        template <class TParameter>
        ParametricExpression<UnitVector<3>, TParameter>
        transform(const ParametricExpression<UnitVector<3>, TParameter>& expression) const;
    };

    typedef Rotation<3> Rotation3d;
}
