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
    template <int iNumDimensions>
    inline
    Point<iNumDimensions>::Point() :
        _vector(Matrix<double, iNumDimensions, 1>::Zero()) {
    }

    template <int iNumDimensions> template <class TVector>
    inline
    Point<iNumDimensions>::Point(const EigenBase<TVector>& vector) :
        _vector(vector) {
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>::Point(double x) :
        _vector(Matrix1d::Constant(x)) {    
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>::Point(double x, double y) :
        _vector(x, y) {        
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>::Point(double x, double y, double z) :
        _vector(x, y, z) {        
    }

    template <int iNumDimensions>
    inline
    Matrix<double, iNumDimensions, 1>&
    Point<iNumDimensions>::vector() {
        return _vector;
    }

    template <int iNumDimensions>
    inline
    const Matrix<double, iNumDimensions, 1>&
    Point<iNumDimensions>::vector() const {
        return _vector;
    }

    template <int iNumDimensions>
    inline
    const double*
    Point<iNumDimensions>::data() const {
        return vector().data();
    }

    template <int iNumDimensions>
    inline
    double*
    Point<iNumDimensions>::data() {
        return vector().data();
    }

    template <int iNumDimensions>
    inline
    double&
    Point<iNumDimensions>::x() {
        return vector().x();
    }
    
    template <int iNumDimensions>
    inline
    double
    Point<iNumDimensions>::x() const {
        return vector().x();
    }

    template <int iNumDimensions>
    inline
    double&
    Point<iNumDimensions>::y() {
        return vector().y();
    }
    
    template <int iNumDimensions>
    inline
    double
    Point<iNumDimensions>::y() const {
        return vector().y();
    }

    template <int iNumDimensions>
    inline
    double&
    Point<iNumDimensions>::z() {
        return vector().z();
    }
    
    template <int iNumDimensions>
    inline
    double
    Point<iNumDimensions>::z() const {
        return vector().z();
    }

    template <int iNumDimensions>
    inline
    double&
    Point<iNumDimensions>::operator()(int index) {
        return vector()(index);
    }
    
    template <int iNumDimensions>
    inline
    double
    Point<iNumDimensions>::operator()(int index) const {
        return vector()(index);
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    Point<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
        return Box<iNumDimensions>(vector().hull(other.vector()));
    }

    template <int iNumDimensions>
    inline
    bool
    Point<iNumDimensions>::isOrigin(double precision) const {
        return vector().isZero(precision);
    }

    template <int iNumDimensions>
    inline
    bool
    Point<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
        return vector() == other.vector();
    }

    template <int iNumDimensions>
    inline
    Matrix<double, iNumDimensions, 1>
    Point<iNumDimensions>::operator-(const Point<iNumDimensions>& other) const {
        return vector() - other.vector();
    }

    template <int iNumDimensions>
    inline
    Matrix<Interval, iNumDimensions, 1>
    Point<iNumDimensions>::operator-(const Box<iNumDimensions>& box) const {
        return vector().template cast<Interval>() - box.vector();
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    Point<iNumDimensions>::Origin() {
        return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::Zero());
    }

    template <int iNumDimensions, class TVector>
    inline
    typename Position<typename TVector::Scalar, iNumDimensions>::Type
    operator+(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) {
        return typename Position<typename TVector::Scalar, iNumDimensions>::Type(
            point.vector().template cast<typename TVector::Scalar>() + vector.derived()
        );
    }

    template <int iNumDimensions, class TVector>
    inline
    typename Position<typename TVector::Scalar, iNumDimensions>::Type
    operator-(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) {
        return typename Position<typename TVector::Scalar, iNumDimensions>::Type(
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
