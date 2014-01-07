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
#include <OpenSolid/Core/Position/BoxVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Box1d::Box() {
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
    Box1d::Box(Interval x) :
        detail::BoxBase<1>(IntervalMatrix1d(x)) {        
    }
    
    inline
    const Interval
    Box1d::value() const {
        return component(0);
    }

    inline
    Interval&
    Box1d::value() {
        return component(0);
    }
    
    inline
    const Interval
    Box1d::x() const {
        return value();
    }

    inline
    Interval&
    Box1d::x() {
        return value();
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
    const Box1d
    Box1d::Unit() {
        return Box1d(Interval::Unit());
    }

    inline
    const Box1d
    Box1d::Hull(const Point1d& firstPoint, const Point1d& secondPoint) {
        return firstPoint.hull(secondPoint);
    }

    inline
    const Box1d
    Box1d::Empty() {
        return Box1d(Interval::Empty());
    }

    inline
    const Box1d
    Box1d::Whole() {
        return Box1d(Interval::Whole());
    }

    inline
    Box2d::Box() {
    }

    inline
    Box2d::Box(const ColumnIntervalMatrix2d& components) :
        detail::BoxBase<2>(components) {
    }

    inline
    Box2d::Box(const Interval* sourcePtr) :
        detail::BoxBase<2>(sourcePtr) {
    }

    inline
    Box2d::Box(Interval x, Interval y) :
        detail::BoxBase<2>(ColumnIntervalMatrix2d(x, y)) {        
    }
    
    inline
    const Interval
    Box2d::x() const {
        return component(0);
    }

    inline
    Interval&
    Box2d::x() {
        return component(0);
    }
    
    inline
    const Interval
    Box2d::y() const {
        return component(1);
    }

    inline
    Interval&
    Box2d::y() {
        return component(1);
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
    const Box2d
    Box2d::Unit() {
        return Box2d(Interval::Unit(), Interval::Unit());
    }

    inline
    const Box2d
    Box2d::Hull(const Point2d& firstPoint, const Point2d& secondPoint) {
        return firstPoint.hull(secondPoint);
    }

    inline
    const Box2d
    Box2d::Empty() {
        return Box2d(Interval::Empty(), Interval::Empty());
    }

    inline
    const Box2d
    Box2d::Whole() {
        return Box2d(Interval::Whole(), Interval::Whole());
    }

    inline
    Box3d::Box() {
    }

    inline
    Box3d::Box(const ColumnIntervalMatrix3d& components) :
        detail::BoxBase<3>(components) {
    }

    inline
    Box3d::Box(const Interval* sourcePtr) :
        detail::BoxBase<3>(sourcePtr) {
    }

    inline
    Box3d::Box(Interval x, Interval y, Interval z) :
        detail::BoxBase<3>(ColumnIntervalMatrix3d(x, y, z)) {        
    }
    
    inline
    const Interval
    Box3d::x() const {
        return component(0);
    }

    inline
    Interval&
    Box3d::x() {
        return component(0);
    }
    
    inline
    const Interval
    Box3d::y() const {
        return component(1);
    }

    inline
    Interval&
    Box3d::y() {
        return component(1);
    }
    
    inline
    const Interval
    Box3d::z() const {
        return component(2);
    }

    inline
    Interval&
    Box3d::z() {
        return component(2);
    }

    inline
    const Point3d
    Box3d::interpolated(double xValue, double yValue, double zValue) const {
        Vector3d vector(xValue * x().width(), yValue * y().width(), zValue * z.width());
        return minVertex() + vector;
    }

    inline
    const Box3d
    Box3d::interpolated(Interval xInterval, Interval yInterval, zInterval) const {
        IntervalVector3d intervalVector(
            xInterval * x().width(),
            yInterval * y().width(),
            zInterval * z().width()
        );
        return minVertex() + intervalVector;
    }

    inline
    const Box3d
    Box3d::Unit() {
        return Box3d(Interval::Unit(), Interval::Unit(), Interval::Unit());
    }

    inline
    const Box3d
    Box3d::Hull(const Point3d& firstPoint, const Point3d& secondPoint) {
        return firstPoint.hull(secondPoint);
    }

    inline
    const Box3d
    Box3d::Empty() {
        return Box3d(Interval::Empty(), Interval::Empty(), Interval::Empty());
    }

    inline
    const Box3d
    Box3d::Whole() {
        return Box3d(Interval::Whole(), Interval::Whole(), Interval::Whole());
    }

    template <int iNumDimensions, class TVector>
    inline
    Box<iNumDimensions>
    operator+(const Box<iNumDimensions>& box, const Vector<iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions, class TVector>
    inline
    Box<iNumDimensions>
    operator+(
        const Box<iNumDimensions>& box,
        const IntervalVector<iNumDimensions>& intervalVector
    ) {
        return Box<iNumDimensions>(box.components() + intervalVector.components());
    }

    template <int iNumDimensions, class TVector>
    inline
    Box<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Vector<iNumDimensions>& vector) {
        return Box<iNumDimensions>(box.components() - vector.components());
    }

    template <int iNumDimensions, class TVector>
    inline
    Box<iNumDimensions>
    operator-(
        const Box<iNumDimensions>& box,
        const IntervalVector<iNumDimensions>& intervalVector
    ) {
        return Box<iNumDimensions>(box.components() - intervalVector.components());
    }

    template <int iNumDimensions>
    inline
    const IntervalVector<iNumDimensions>
    operator-(const Box<iNumDimensions>& box, const Point<iNumDimensions>& point) const {
        return IntervalVector<iNumDimensions>(box.components() - point.components());
    }

    template <int iNumDimensions>
    inline
    const IntervalVector<iNumDimensions>
    operator-(const Box<iNumDimensions>& firstBox, const Box<iNumDimensions>& secondBox) const {
        return IntervalVector<iNumDimensions>(firstBox.components() - secondBox.components());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Box<iNumDimensions>& box) {
        stream << "Box" << iNumDimensions << "d";
        stream << "(";
        for (std::int64_t index = 0; index < iNumDimensions; ++index) {
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
        const Vector<iNumDimensions>& vector
    ) const {
        return Box<iNumDimensions>(box.components() + vector.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    Box<iNumResultDimensions>
    TransformationFunction<Box<iNumDimensions>, iNumResultDimensions>::operator()(
        const Box<iNumDimensions>& box,
        const Matrix<iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return Box<iNumResultDimensions>(matrix * box.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    Box<iNumResultDimensions>
    MorphingFunction<Box<iNumDimensions>, iNumResultDimensions>::operator()(
        const Box<iNumDimensions>& box,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Box<iNumResultDimensions>(morphingExpression.evaluate(box.components()));
    }
}
