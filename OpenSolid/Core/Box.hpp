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

#include <OpenSolid/Core/Box.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Position/BoxBase.hpp>
#include <OpenSolid/Core/Position/BoxVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Box2d::Box() {
    }

    inline
    Box2d::Box(Interval x, Interval y) :
        detail::BoxBase<2>(x, y) {        
    }

    inline
    Box2d::Box(const IntervalVector2d& intervalVector) :
        detail::BoxBase<2>(intervalVector.components()) {
    }

    inline
    Box2d::Box(const IntervalColumnMatrix2d& components) :
        detail::BoxBase<2>(components) {
    }

    inline
    Point2d
    Box2d::interpolated(double x, double y) const {
        return minVertex() + Vector2d(x * this->x().width(), y * this->y().width());
    }

    inline
    Box2d
    Box2d::interpolated(Interval x, Interval y) const {
        return minVertex() + IntervalVector2d(x * this->x().width(), y * this->y().width());
    }

    inline
    Box2d
    Box2d::scaledAbout(const Point2d& point, double scale) const {
        return Box2d(point + scale * (*this - point));
    }

    inline
    Box2d
    Box2d::translatedBy(const Vector2d& vector) const {
        return *this + vector;
    }

    inline
    Box3d::Box() {
    }

    inline
    Box3d::Box(Interval x, Interval y, Interval z) :
        detail::BoxBase<3>(x, y, z) {        
    }

    inline
    Box3d::Box(const IntervalVector3d& intervalVector) :
        detail::BoxBase<3>(intervalVector.components()) {
    }

    inline
    Box3d::Box(const IntervalColumnMatrix3d& components) :
        detail::BoxBase<3>(components) {
    }

    inline
    Point3d
    Box3d::interpolated(double x, double y, double z) const {
        Vector3d vector(x * this->x().width(), y * this->y().width(), z * this->z().width());
        return minVertex() + vector;
    }

    inline
    Box3d
    Box3d::interpolated(Interval x, Interval y, Interval z) const {
        IntervalVector3d intervalVector(
            x * this->x().width(),
            y * this->y().width(),
            z * this->z().width()
        );
        return minVertex() + intervalVector;
    }

    inline
    Box3d
    Box3d::scaledAbout(const Point3d& point, double scale) const {
        return Box3d(point + scale * (*this - point));
    }

    inline
    Box3d
    Box3d::translatedBy(const Vector3d& vector) const {
        return *this + vector;
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Box<iNumDimensions>& box) {
        return Vector<Interval, iNumDimensions>(point.components() - box.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point) {
        return Vector<Interval, iNumDimensions>(box.components() - point.components());
    }

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& firstBox, const Box<iNumDimensions>& secondBox) {
        return Vector<Interval, iNumDimensions>(firstBox.components() - secondBox.components());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box) {
        stream << "Box" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << box.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>&
    BoundsFunction<Box<iNumDimensions>>::operator()(const Box<iNumDimensions>& box) const {
        return box;
    }
}
