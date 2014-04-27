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
    Box1d::Box() {
    }

    inline
    Box1d::Box(Interval value) :
        detail::BoxBase<1>(value) {        
    }

    inline
    Box1d::Box(const IntervalVector1d& intervalVector) :
        detail::BoxBase<1>(intervalVector.components()) {
    }

    inline
    Box1d::Box(const IntervalMatrix1d& components) :
        detail::BoxBase<1>(components) {
    }

    inline
    Box1d::Box(const Interval* sourcePtr) :
        detail::BoxBase<1>(sourcePtr) {
    }

    inline
    const Point1d
    Box1d::interpolated(double xValue) const {
        return minVertex() + Vector1d(xValue * x().width());
    }

    inline
    const Box1d
    Box1d::interpolated(Interval xInterval) const {
        return minVertex() + IntervalVector1d(xInterval * x().width());
    }

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
    Box2d::Box(const Interval* sourcePtr) :
        detail::BoxBase<2>(sourcePtr) {
    }

    inline
    const Point2d
    Box2d::interpolated(double xValue, double yValue) const {
        return minVertex() + Vector2d(xValue * x().width(), yValue * y().width());
    }

    inline
    const Box2d
    Box2d::interpolated(Interval xInterval, Interval yInterval) const {
        return minVertex() + IntervalVector2d(xInterval * x().width(), yInterval * y().width());
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
    Box3d::Box(const Interval* sourcePtr) :
        detail::BoxBase<3>(sourcePtr) {
    }

    inline
    const Point3d
    Box3d::interpolated(double xValue, double yValue, double zValue) const {
        Vector3d vector(xValue * x().width(), yValue * y().width(), zValue * z().width());
        return minVertex() + vector;
    }

    inline
    const Box3d
    Box3d::interpolated(Interval xInterval, Interval yInterval, Interval zInterval) const {
        IntervalVector3d intervalVector(
            xInterval * x().width(),
            yInterval * y().width(),
            zInterval * z().width()
        );
        return minVertex() + intervalVector;
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<double, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<Interval, iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    const Vector<Interval, iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Box<iNumDimensions>& box) {
        return Vector<Interval, iNumDimensions>(point.components() - box.components());
    }

    template <int iNumDimensions>
    inline
    const Vector<Interval, iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point) {
        return Vector<Interval, iNumDimensions>(box.components() - point.components());
    }

    template <int iNumDimensions>
    inline
    const Vector<Interval, iNumDimensions>
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

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    ScalingFunction<Box<iNumDimensions>>::operator()(
        const Box<iNumDimensions>& box,
        double scale
    ) const {
        return Box<iNumDimensions>(box.components() * scale);
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    TranslationFunction<Box<iNumDimensions>>::operator()(
        const Box<iNumDimensions>& box,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    const Box<iNumResultDimensions>
    TransformationFunction<Box<iNumDimensions>, iNumResultDimensions>::operator()(
        const Box<iNumDimensions>& box,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return Box<iNumResultDimensions>(matrix * box.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    const Box<iNumResultDimensions>
    MorphingFunction<Box<iNumDimensions>, iNumResultDimensions>::operator()(
        const Box<iNumDimensions>& box,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Box<iNumResultDimensions>(morphingExpression.evaluate(box.components()));
    }
}
