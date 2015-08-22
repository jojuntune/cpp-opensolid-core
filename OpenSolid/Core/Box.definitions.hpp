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

#include <OpenSolid/Core/Box.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Position/BoxBase.definitions.hpp>
#include <OpenSolid/Core/Position/BoxVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Box<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Box<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Box<2> :
        public detail::BoxBase<2>,
        public Convertible<Box<2>>
    {
    public:
        Box();

        Box(Interval x, Interval y);

        explicit
        Box(const Vector<Interval, 2>& intervalVector);

        explicit
        Box(const Matrix<Interval, 2, 1>& components);

        Point<2>
        interpolated(double x, double y) const;

        Box<2>
        interpolated(Interval x, Interval y) const;

        Box<2>
        scaledAbout(const Point<2>& point, double scale) const;

        Box<2>
        translatedBy(const Vector<double, 2>& vector) const;
    };

    typedef Box<2> Box2d;

    template <>
    class Box<3> :
        public detail::BoxBase<3>,
        public Convertible<Box<3>>
    {
    public:
        Box();

        Box(Interval x, Interval y, Interval z);

        explicit
        Box(const Vector<Interval, 3>& intervalVector);

        explicit
        Box(const Matrix<Interval, 3, 1>& components);

        Point<3>
        interpolated(double x, double y, double z) const;

        Box<3>
        interpolated(Interval x, Interval y, Interval z) const;

        Box<3>
        scaledAbout(const Point<3>& point, double scale) const;

        Box<3>
        translatedBy(const Vector<double, 3>& vector) const;
    };

    typedef Box<3> Box3d;

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector);

    template <int iNumDimensions>
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector);

    template <int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Box<iNumDimensions>& box);

    template <int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point);

    template <int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& firstBox, const Box<iNumDimensions>& secondBox);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box);
}
