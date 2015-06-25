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

#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    bool
    Point2d::isOn(const LineSegment2d& lineSegment, double precision) const {
        Vector2d parallelVector = lineSegment.vector();
        Vector2d startVector = *this - lineSegment.startVertex();
        double parallelMetric = startVector.dot(parallelVector);
        double squaredPrecision = precision * precision;
        if (parallelMetric <= 0.0) {
            // Point is before start - check if it is within given precision of
            // start point
            return startVector.squaredNorm() <= squaredPrecision;
        } else {
            double squaredNorm = parallelVector.squaredNorm();
            if (parallelMetric >= squaredNorm) {
                // Point is after end - check if it is within given precision of
                // end point
                Vector2d endVector = *this - lineSegment.endVertex();
                return endVector.squaredNorm() <= squaredPrecision;
            } else {
                // Point is between start and end - check if it is within given
                // precision of its projection onto the line
                Point2d projected = (
                    lineSegment.startVertex() + parallelMetric * parallelVector / squaredNorm
                );
                return (*this - projected).squaredNorm() <= squaredPrecision;
            }
        }
    }

    Point2d
    Point2d::polar(double radius, double angle) {
        return Point2d(radius * cos(angle), radius * sin(angle));
    }

    bool
    Point3d::isOn(const LineSegment3d& lineSegment, double precision) const {
        Vector3d parallelVector = lineSegment.vector();
        Vector3d startVector = *this - lineSegment.startVertex();
        double parallelMetric = startVector.dot(parallelVector);
        double squaredPrecision = precision * precision;
        if (parallelMetric <= 0.0) {
            // Point is before start - check if it is within given precision of
            // start point
            return startVector.squaredNorm() <= squaredPrecision;
        } else {
            double squaredNorm = parallelVector.squaredNorm();
            if (parallelMetric >= squaredNorm) {
                // Point is after end - check if it is within given precision of
                // end point
                Vector3d endVector = *this - lineSegment.endVertex();
                return endVector.squaredNorm() <= squaredPrecision;
            } else {
                // Point is between start and end - check if it is within given
                // precision of its projection onto the line
                Point3d projected = (
                    lineSegment.startVertex() + parallelMetric * parallelVector / squaredNorm
                );
                return (*this - projected).squaredNorm() <= squaredPrecision;
            }
        }
    }

    bool
    Point3d::isOn(const Triangle3d& triangle, double precision) const {
        if (precision < 0.0) {
            // Negative precision is meaningless for 3D point/triangle check
            throw Error(new PlaceholderError());
        }

        Vector3d firstEdgeVector = triangle.vertex(1) - triangle.vertex(0);
        Vector3d secondEdgeVector = triangle.vertex(2) - triangle.vertex(1);
        Vector3d thirdEdgeVector = triangle.vertex(0) - triangle.vertex(2);
        
        // Check whether point is on the plane defined by the triangle
        Vector3d perpendicularVector = firstEdgeVector.cross(secondEdgeVector);
        Vector3d displacement = *this - triangle.vertex(0);
        double perpendicularDotProduct = displacement.dot(perpendicularVector);
        if (
            perpendicularDotProduct * perpendicularDotProduct >
            perpendicularVector.squaredNorm() * precision * precision
        ) {
            return false;
        }

        // Check if point is entirely contained within the triangle interior
        if (
            displacement.dot(perpendicularVector.cross(firstEdgeVector)) >= 0.0 &&
            displacement.dot(perpendicularVector.cross(thirdEdgeVector)) >= 0.0 &&
            (*this - triangle.vertex(1)).dot(perpendicularVector.cross(secondEdgeVector)) >= 0.0
        ) {
            return true;
        }

        return (
            isOn(triangle.edge(0), precision) ||
            isOn(triangle.edge(1), precision) ||
            isOn(triangle.edge(2), precision)
        );
    }
    
    Point3d
    Point3d::cylindrical(double radius, double angle, double height) {
        return Point3d(radius * cos(angle), radius * sin(angle), height);
    }

    Point3d
    Point3d::spherical(double radius, double polarAngle, double elevationAngle) {
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

    std::ostream&
    operator<<(std::ostream& stream, const Point2d& point) {
        stream << "Point2d(" << point.x() << "," << point.y() << ")";
        return stream;
    }

    std::ostream&
    operator<<(std::ostream& stream, const Point3d& point) {
        stream << "Point3d(" << point.x() << "," << point.y() << "," << point.z() << ")";
        return stream;
    }
}
