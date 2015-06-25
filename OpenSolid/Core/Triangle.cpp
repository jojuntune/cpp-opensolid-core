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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Triangle.hpp>

#include <OpenSolid/Core/UnitVector.hpp>

#include <iostream>

namespace opensolid
{
    namespace detail
    {
        class EdgeMetrics2d
        {
        public:
            EdgeMetrics2d(
                const Point2d& startVertex,
                const Point2d& point,
                const Point2d& endVertex,
                double squaredTolerance
            );

            bool
            isPositive() const;

            bool
            isStrictlyPositive() const;

            bool
            isNegative() const;

            bool
            isStrictlyNegative() const;

            bool
            isBetweenEndpoints() const;
        private:
            double _squaredLength;
            double _crossProduct;
            double _perpendicularMetric;
            double _perpendicularCutoff;
            double _parallelDotProduct;
        };

        inline
        EdgeMetrics2d::EdgeMetrics2d(
            const Point2d& startVertex,
            const Point2d& point,
            const Point2d& endVertex,
            double squaredTolerance
        ) {
            double a1 = point.x() - startVertex.x();
            double a2 = point.y() - startVertex.y();
            double b1 = endVertex.x() - startVertex.x();
            double b2 = endVertex.y() - startVertex.y();
            _squaredLength = b1 * b1 + b2 * b2;
            _crossProduct = a1 * b2 - a2 * b1;
            _perpendicularMetric = _crossProduct * _crossProduct;
            _perpendicularCutoff = _squaredLength * squaredTolerance;
            _parallelDotProduct = a1 * b1 + a2 * b2;
        }

        inline
        bool
        EdgeMetrics2d::isPositive() const {
            return _crossProduct > 0.0;
        }

        inline
        bool
        EdgeMetrics2d::isStrictlyPositive() const {
            return _crossProduct > 0.0 && _perpendicularMetric > _perpendicularCutoff;
        }

        inline
        bool
        EdgeMetrics2d::isNegative() const {
            return _crossProduct < 0.0;
        }

        inline
        bool
        EdgeMetrics2d::isStrictlyNegative() const {
            return _crossProduct < 0.0 && _perpendicularMetric > _perpendicularCutoff;
        }

        inline
        bool
        EdgeMetrics2d::isBetweenEndpoints() const {
            return _parallelDotProduct >= 0.0 && _parallelDotProduct <= _squaredLength;
        }
    }

    bool
    Triangle2d::contains(const Point2d& point, double tolerance) const {
        if (tolerance == 0.0) {
            return (
                detail::crossProduct2d(vertex(0), point, vertex(1)) <= 0.0 &&
                detail::crossProduct2d(vertex(1), point, vertex(2)) <= 0.0 &&
                detail::crossProduct2d(vertex(2), point, vertex(0)) <= 0.0
            );
        } else if (tolerance > 0.0) {        
            double squaredTolerance = tolerance * tolerance;
            detail::EdgeMetrics2d firstMetrics(vertex(0), point, vertex(1), squaredTolerance);
            if (firstMetrics.isStrictlyPositive()) {
                std::cout << "first metrics strictly positive" << std::endl;
                return false;
            }
            detail::EdgeMetrics2d secondMetrics(vertex(1), point, vertex(2), squaredTolerance);
            if (secondMetrics.isStrictlyPositive()) {
                std::cout << "second metrics strictly positive" << std::endl;
                return false;
            }
            detail::EdgeMetrics2d thirdMetrics(vertex(2), point, vertex(0), squaredTolerance);
            if (thirdMetrics.isStrictlyPositive()) {
                std::cout << "third metrics strictly positive" << std::endl;
                return false;
            }
            if (
                firstMetrics.isNegative() &&
                secondMetrics.isNegative() &&
                thirdMetrics.isNegative()
            ) {
                return true;
            }
            if (
                ( firstMetrics.isPositive() && firstMetrics.isBetweenEndpoints()) ||
                (secondMetrics.isPositive() && secondMetrics.isBetweenEndpoints()) ||
                (thirdMetrics.isPositive() && thirdMetrics.isBetweenEndpoints())
            ) {
                return true;
            }
            return (
                (point - vertex(0)).squaredNorm() <= squaredTolerance ||
                (point - vertex(1)).squaredNorm() <= squaredTolerance ||
                (point - vertex(2)).squaredNorm() <= squaredTolerance
            );
        } else {
            double squaredTolerance = tolerance * tolerance;
            return (
                detail::EdgeMetrics2d(
                    vertex(0),
                    point,
                    vertex(1),
                    squaredTolerance
                ).isStrictlyNegative() &&
                detail::EdgeMetrics2d(
                    vertex(1),
                    point,
                    vertex(2),
                    squaredTolerance
                ).isStrictlyNegative() &&
                detail::EdgeMetrics2d(
                    vertex(2),
                    point,
                    vertex(0),
                    squaredTolerance
                ).isStrictlyNegative()
            );
        }
    }

    Triangle2d
    Triangle2d::unit() {
        return Triangle2d(Point2d::origin(), Point2d(1, 0), Point2d(0, 1));
    }

    double
    Triangle3d::area() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).norm() / 2.0;
    }

    UnitVector3d
    Triangle3d::normalVector() const {
        static const double epsilon = std::numeric_limits<double>::epsilon();
        Vector3d vector1 = vertex(1) - vertex(0);
        Vector3d vector2 = vertex(2) - vertex(0);
        Vector3d crossProduct = vector1.cross(vector2);
        double squaredNorm1 = vector1.squaredNorm();
        double squaredNorm2 = vector2.squaredNorm();
        double crossProductSquaredNorm = crossProduct.squaredNorm();
        if (crossProductSquaredNorm > epsilon * squaredNorm1 * squaredNorm2) {
            // Cross product is (reasonably) well conditioned - use it to
            // compute the normal vector
            return UnitVector3d((crossProduct / sqrt(crossProductSquaredNorm)).components());
        } else {
            // Cross product is poorly conditioned (i.e., triangle is degenerate
            // or nearly so) - instead of cross product, compute a unit vector
            // perpendicular to the longest of the two edges
            if (squaredNorm1 >= squaredNorm2) {
                return vector1.unitOrthogonal();
            } else {
                return vector2.unitOrthogonal();
            }
        }
    }

    Plane3d
    Triangle3d::plane() const {
        return Plane3d(vertex(0), normalVector());
    }
}
