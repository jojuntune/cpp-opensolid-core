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
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase() :
            _vector(Matrix<double, iNumDimensions, 1>::Zero()) {
        }

        template <int iNumDimensions> template <class TVector>
        inline
        PointBase<iNumDimensions>::PointBase(const EigenBase<TVector>& vector) :
            _vector(vector.derived()) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double value) :
            _vector(Matrix<double, iNumDimensions, 1>::Constant(value)) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y) :
            _vector(x, y) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y, double z) :
            _vector(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        const Matrix<double, iNumDimensions, 1>&
        PointBase<iNumDimensions>::vector() const {
            return _vector;
        }

        template <int iNumDimensions>
        inline
        Matrix<double, iNumDimensions, 1>&
        PointBase<iNumDimensions>::vector() {
            return _vector;
        }

        template <int iNumDimensions>
        inline
        const double*
        PointBase<iNumDimensions>::data() const {
            return vector().data();
        }

        template <int iNumDimensions>
        inline
        double*
        PointBase<iNumDimensions>::data() {
            return vector().data();
        }

        template <int iNumDimensions>
        inline
        double&
        PointBase<iNumDimensions>::operator()(int index) {
            return vector()(index);
        }
        
        template <int iNumDimensions>
        inline
        double
        PointBase<iNumDimensions>::operator()(int index) const {
            return vector()(index);
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointBase<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
            return Box<iNumDimensions>(vector().hull(other.vector()));
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::isOrigin(double precision) const {
            return vector().isZero(precision);
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
            return vector() == other.vector();
        }

        template <int iNumDimensions>
        inline
        Matrix<double, iNumDimensions, 1>
        PointBase<iNumDimensions>::operator-(const Point<iNumDimensions>& other) const {
            return vector() - other.vector();
        }

        template <int iNumDimensions>
        inline
        Matrix<Interval, iNumDimensions, 1>
        PointBase<iNumDimensions>::operator-(const Box<iNumDimensions>& box) const {
            return vector().template cast<Interval>() - box.vector();
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::Origin() {
            return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::Zero());
        }
    }

    inline
    Point1d::Point() {
    }

    inline
    Point1d::Point(double value) :
        detail::PointBase<1>(value) {
    }

    template <class TVector>
    inline
    Point1d::Point(const EigenBase<TVector>& vector) :
        detail::PointBase<1>(vector.derived()) {
    }

    inline
    double
    Point1d::value() const {
        return vector()(0);
    }

    inline
    double&
    Point1d::value() {
        return vector()(0);
    }

    inline
    Point2d::Point() {
    }

    inline
    Point2d::Point(double x, double y) :
        detail::PointBase<2>(x, y) {
    }

    template <class TVector>
    inline
    Point2d::Point(const EigenBase<TVector>& vector) :
        detail::PointBase<2>(vector.derived()) {
    }

    inline
    double
    Point2d::x() const {
        return vector().x();
    }

    inline
    double&
    Point2d::x() {
        return vector().x();
    }

    inline
    double
    Point2d::y() const {
        return vector().y();
    }

    inline
    double&
    Point2d::y() {
        return vector().y();
    }

    inline
    double
    Point2d::distanceTo(const Axis<2>& axis) {
        Vector2d normalVector(-axis.directionVector().y(), axis.directionVector().x());
        return (*this - axis.originPoint()).dot(normalVector);
    }

    inline
    Point2d
    Point2d::Polar(double radius, double angle) {
        return Point2d(radius * cos(angle), radius * sin(angle));
    }

    inline
    Point3d::Point() {
    }

    inline
    Point3d::Point(double x, double y, double z) :
        detail::PointBase<3>(x, y, z) {
    }

    template <class TVector>
    inline
    Point3d::Point(const EigenBase<TVector>& vector) :
        detail::PointBase<3>(vector.derived()) {
    }

    inline
    double
    Point3d::x() const {
        return vector().x();
    }

    inline
    double&
    Point3d::x() {
        return vector().x();
    }

    inline
    double
    Point3d::y() const {
        return vector().y();
    }

    inline
    double&
    Point3d::y() {
        return vector().y();
    }

    inline
    double
    Point3d::z() const {
        return vector().z();
    }

    inline
    double&
    Point3d::z() {
        return vector().z();
    }

    inline
    double
    Point3d::distanceTo(const Plane3d& plane) {
        return (*this - plane.originPoint()).dot(plane.normalVector());
    }

    inline
    Point3d
    Point3d::Cylindrical(double radius, double angle, double height) {
        return Point3d(radius * cos(angle), radius * sin(angle), height);
    }

    inline
    Point3d
    Point3d::Spherical(double radius, double polarAngle, double elevationAngle) {
        double cosElevation = cos(elevationAngle);
        return Point3d(
            radius * cosElevation * cos(polarAngle),
            radius * cosElevation * sin(polarAngle),
            radius * sin(elevationAngle)
        );
    }

    template <int iNumDimensions, class TVector>
    inline
    typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type
    operator+(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) {
        return typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type(
            point.vector().template cast<typename TVector::Scalar>() + vector.derived()
        );
    }

    template <int iNumDimensions, class TVector>
    inline
    typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type
    operator-(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) {
        return typename detail::Position<typename TVector::Scalar, iNumDimensions>::Type(
            point.vector().template cast<typename TVector::Scalar>() - vector.derived()
        );
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point) {
        stream << point.vector().transpose();
        return stream;
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    ScalingFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        double scale
    ) const {
        return Point<iNumDimensions>(scale * point.vector());
    }

    template <int iNumDimensions> template <class TVector>
    inline
    Point<iNumDimensions>
    TranslationFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        const EigenBase<TVector>& vector
    ) const {
        return Point<iNumDimensions>(point.vector() + vector.derived());
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    inline
    Point<iNumResultDimensions>
    TransformationFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Point<iNumResultDimensions>(matrix.derived() * point.vector());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    Point<iNumResultDimensions>
    MorphingFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Point<iNumResultDimensions>(morphingExpression.evaluate(point.vector()));
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    BoundsFunction<Point<iNumDimensions>>::operator()(const Point<iNumDimensions>& point) const {
        return Box<iNumDimensions>(point.vector().template cast<Interval>());
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& firstPoint,
        const Point<iNumDimensions>& secondPoint,
        double precision
    ) const {
        return (firstPoint - secondPoint).isZero(precision);
    }
}
