/*************************************************************************************
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
 *************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Point :
        public Transformable<Point<iNumDimensions>>
    {
    private:
        Matrix<double, iNumDimensions, 1> _vector;
    public:
        Point();

        template <class TVector>
        explicit Point(const EigenBase<TVector>& vector);

        Point(double x, double y);
        Point(double x, double y, double z);

        const double* data() const;
        double* data();

        Matrix<double, iNumDimensions, 1>& vector();
        const Matrix<double, iNumDimensions, 1>& vector() const;

        double& x();
        double x() const;

        double& y();
        double y() const;

        double& z();
        double z() const;

        double& operator()(int index);
        double operator()(int index) const;

        Matrix<double, iNumDimensions, 1> operator-(const Point<iNumDimensions>& other) const;

        static Point Origin();
    };

    typedef Point<2> Point2d;
    typedef Point<3> Point3d;

    template <int iNumDimensions>
    Point<iNumDimensions> operator*(double scale, const Point<iNumDimensions>& point);

    template <class TMatrix, int iNumDimensions>
    Point<TMatrix::RowsAtCompileTime> operator*(
        const EigenBase<TMatrix>& matrix,
        const Point<iNumDimensions>& point
    );

    template <int iNumDimensions, class TVector>
    Point<iNumDimensions> operator+(
        const Point<iNumDimensions>& point,
        const EigenBase<TVector>& vector
    );

    template <int iNumDimensions>
    std::ostream& operator<<(std::ostream& stream, const Point<iNumDimensions>& point);
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iTransformedDimensions>
    struct Transformed<Point<iNumDimensions>, iTransformedDimensions>
    {
        typedef Point<iTransformedDimensions> Type;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions>
    inline Point<iNumDimensions>::Point() :
        _vector(Matrix<double, iNumDimensions, 1>::Zero()) {
    }

    template <int iNumDimensions> template <class TVector>
    inline Point<iNumDimensions>::Point(const EigenBase<TVector>& vector) :
        _vector(vector) {
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>::Point(double x, double y) :
        _vector(x, y) {        
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>::Point(double x, double y, double z) :
        _vector(x, y, z) {        
    }

    template <int iNumDimensions>
    inline const double*
    Point<iNumDimensions>::data() const {
        return _vector.data();
    }

    template <int iNumDimensions>
    inline double*
    Point<iNumDimensions>::data() {
        return _vector.data();
    }

    template <int iNumDimensions>
    inline Matrix<double, iNumDimensions, 1>&
    Point<iNumDimensions>::vector() {
        return _vector;
    }

    template <int iNumDimensions>
    inline const Matrix<double, iNumDimensions, 1>&
    Point<iNumDimensions>::vector() const {
        return _vector;
    }

    template <int iNumDimensions>
    inline double&
    Point<iNumDimensions>::x() {
        return _vector.x();
    }
    
    template <int iNumDimensions>
    inline double
    Point<iNumDimensions>::x() const {
        return _vector.x();
    }

    template <int iNumDimensions>
    inline double&
    Point<iNumDimensions>::y() {
        return _vector.y();
    }
    
    template <int iNumDimensions>
    inline double
    Point<iNumDimensions>::y() const {
        return _vector.y();
    }

    template <int iNumDimensions>
    inline double&
    Point<iNumDimensions>::z() {
        return _vector.z();
    }
    
    template <int iNumDimensions>
    inline double
    Point<iNumDimensions>::z() const {
        return _vector.z();
    }

    template <int iNumDimensions>
    inline double&
    Point<iNumDimensions>::operator()(int index) {
        return _vector(index);
    }
    
    template <int iNumDimensions>
    inline double
    Point<iNumDimensions>::operator()(int index) const {
        return _vector(index);
    }

    template <int iNumDimensions>
    inline Matrix<double, iNumDimensions, 1>
    Point<iNumDimensions>::operator-(const Point<iNumDimensions>& other) const {
        return _vector - other._vector;
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>
    Point<iNumDimensions>::Origin() {
        return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::Zero());
    }

    template <int iNumDimensions>
    inline Point<iNumDimensions>
    operator*(double scale, const Point<iNumDimensions>& point) {
        return Point<iNumDimensions>(scale * point.vector());
    }

    template <class TMatrix, int iNumDimensions>
    Point<TMatrix::RowsAtCompileTime>
    operator*(const EigenBase<TMatrix>& matrix, const Point<iNumDimensions>& point) {
        return Point<iNumDimensions>(matrix.derived() * point.vector());
    }

    template <int iNumDimensions, class TVector>
    Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) {
        return Point<iNumDimensions>(point.vector() + vector.derived());
    }

    template <int iNumDimensions>
    std::ostream& operator<<(std::ostream& stream, const Point<iNumDimensions>& point) {
        stream << point.vector();
        return stream;
    }
}
