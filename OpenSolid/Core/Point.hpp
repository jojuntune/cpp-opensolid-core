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

#include <OpenSolid/Core/Point.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Position/PointBase.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Point1d::Point() {
    }

    inline
    Point1d::Point(double value) :
        detail::PointBase<1>(Matrix1d(value)) {
    }

    inline
    Point1d::Point(const Vector1d& vector) :
        detail::PointBase<1>(vector.components()) {
    }

    inline
    Point1d::Point(const Matrix1d& matrix) :
        detail::PointBase<1>(matrix) {
    }

    inline
    Point1d::Point(const double* sourcePtr) :
        detail::PointBase<1>(sourcePtr) {
    }

    inline
    const double
    Point1d::value() const {
        return component(0);
    }

    inline
    double&
    Point1d::value() {
        return component(0);
    }

    inline
    const double
    Point1d::x() const {
        return value();
    }

    inline
    double&
    Point1d::x() {
        return value();
    }

    inline
    const Point1d
    Point1d::Origin() {
        return Point1d();
    }

    inline
    Point2d::Point() {
    }

    inline
    Point2d::Point(double x, double y) :
        detail::PointBase<2>(ColumnMatrix2d(x, y)) {
    }

    inline
    Point2d::Point(const Vector2d& vector) :
        detail::PointBase<2>(vector.components()) {
    }

    inline
    Point2d::Point(const ColumnMatrix2d& components) :
        detail::PointBase<2>(components) {
    }

    inline
    Point2d::Point(const double* sourcePtr) :
        detail::PointBase<2>(components) {
    }

    inline
    const double
    Point2d::x() const {
        return component(0);
    }

    inline
    double&
    Point2d::x() {
        return component(0);
    }

    inline
    const double
    Point2d::y() const {
        return component(1);
    }

    inline
    double&
    Point2d::y() {
        return component(1);
    }

    inline
    const double
    Point2d::distanceTo(const Axis<2>& axis) const {
        return (*this - axis.originPoint()).dot(axis.normalVector());
    }

    inline
    const Point2d
    Point2d::Origin() {
        return Point2d();
    }

    inline
    const Point2d
    Point2d::Polar(double radius, double angle) {
        return Point2d(radius * cos(angle), radius * sin(angle));
    }

    inline
    Point3d::Point() {
    }

    inline
    Point3d::Point(double x, double y, double z) :
        detail::PointBase<3>(ColumnMatrix3d(x, y, z)) {
    }

    inline
    Point3d::Point(const Vector3d& vector) :
        detail::PointBase<3>(vector.components()) {
    }

    inline
    Point3d::Point(const ColumnMatrix3d& components) :
        detail::PointBase<3>(components) {
    }

    inline
    Point3d::Point(const double* sourcePtr) :
        detail::PointBase<3>(sourcePtr) {
    }

    inline
    const double
    Point3d::x() const {
        return component(0);
    }

    inline
    double&
    Point3d::x() {
        return component(0);
    }

    inline
    const double
    Point3d::y() const {
        return component(1);
    }

    inline
    double&
    Point3d::y() {
        return component(1);
    }

    inline
    const double
    Point3d::z() const {
        return component(2);
    }

    inline
    double&
    Point3d::z() {
        return component(2);
    }

    inline
    const double
    Point3d::distanceTo(const Plane3d& plane) const {
        return (*this - plane.originPoint()).dot(plane.normalVector());
    }

    inline
    const Point3d
    Point3d::Origin() {
        return Point3d();
    }

    inline
    Point3d
    Point3d::Cylindrical(double radius, double angle, double height) {
        return Point3d(radius * cos(angle), radius * sin(angle), height);
    }

    inline
    Point3d
    Point3d::Spherical(double radius, double polarAngle, double elevationAngle) {
        double sinElevation = sin(elevationAngle);
        double cosElevation = cos(elevationAngle);
        double sinPolar = sin(polarAngle);
        double cosPolar = cos(polarAngle);
        return Point3d(
            radius * cosElevation * cosPolar,
            radius * cosElevation * sinPolar,
            radius * sinElevation
        );
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    const Vector<iNumDimensions>
    operator-(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint) {
        return Vector<iNumDimensions>(firstPoint.components() - secondPoint.components());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point) {
        stream << "Point" << iNumDimensions << "d";
        stream << "(";
        for (std::int64_t index = 0; index < iNumDimensions; ++index) {
            stream << point.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& firstPoint,
        const Point<iNumDimensions>& secondPoint,
        double precision
    ) const {
        return firstPoint - secondPoint == Zero(precision);
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    BoundsFunction<Point<iNumDimensions>>::operator()(const Point<iNumDimensions>& point) const {
        return Box<iNumDimensions>(
            point.components().map(
                [] (double component) {
                    return Interval(component);
                }
            )
        );
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    ScalingFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        double scale
    ) const {
        return Point<iNumDimensions>(scale * point.components());
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    TranslationFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        const Vector<iNumDimensions>& vector
    ) const {
        return point + vector;
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    Point<iNumResultDimensions>
    TransformationFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const Matrix<iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return Point<iNumResultDimensions>(matrix * point.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    Point<iNumResultDimensions>
    MorphingFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Point<iNumResultDimensions>(morphingExpression.evaluate(point.components()));
    }
}
