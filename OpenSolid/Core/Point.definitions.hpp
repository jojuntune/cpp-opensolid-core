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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Point.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Position.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <ostream>

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
        explicit
        Point(const EigenBase<TVector>& vector);

        explicit
        Point(double x);

        Point(double x, double y);

        Point(double x, double y, double z);

        Matrix<double, iNumDimensions, 1>&
        vector();
        
        const Matrix<double, iNumDimensions, 1>&
        vector() const;

        const double*
        data() const;
        
        double*
        data();

        double&
        x();
        
        double
        x() const;

        double&
        y();
        
        double
        y() const;

        double&
        z();
        
        double
        z() const;

        double&
        operator()(int index);
        
        double
        operator()(int index) const;

        Box<iNumDimensions>
        hull(const Point<iNumDimensions>& other) const;

        bool
        isOrigin(double precision = 1e-12) const;

        bool
        operator==(const Point<iNumDimensions>& other) const;

        Matrix<double, iNumDimensions, 1>
        operator-(const Point<iNumDimensions>& other) const;

        Matrix<Interval, iNumDimensions, 1>
        operator-(const Box<iNumDimensions>& box) const;

        static Point
        Origin();
    };

    typedef Point<1> Point1d;
    typedef Point<2> Point2d;
    typedef Point<3> Point3d;

    template <int iNumDimensions, class TVector>
    typename Position<typename TVector::Scalar, iNumDimensions>::Type
    operator+(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector);

    template <int iNumDimensions, class TVector>
    typename Position<typename TVector::Scalar, iNumDimensions>::Type
    operator-(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point);
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct ScalingFunction<Point<iNumDimensions>>
    {
        Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Point<iNumDimensions>>
    {
        template <class TVector>
        Point<iNumDimensions>
        operator()(const Point<iNumDimensions>& point, const EigenBase<TVector>& vector) const;
    };

    template <int iNumDimensions, int iTransformedDimensions>
    struct TransformationFunction<Point<iNumDimensions>, iTransformedDimensions>
    {
        typedef Point<iTransformedDimensions> ResultType;

        template <class TMatrix>
        Point<iTransformedDimensions>
        operator()(
            const Point<iNumDimensions>& point,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumDestinationDimensions>
    struct MappingFunction<Point<iNumDimensions>, iNumDestinationDimensions>
    {
        typedef Point<iNumDestinationDimensions> ResultType;

        Point<iNumDestinationDimensions>
        operator()(const Point<iNumDimensions>& point, const Function& function) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Point<iNumDimensions>>
    {
        typedef Box<iNumDimensions> ResultType;

        Box<iNumDimensions>
        operator()(const Point<iNumDimensions>& point) const;
    };
}
