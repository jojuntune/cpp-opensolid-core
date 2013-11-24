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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <cxxtest/TestSuite.h>

#include <typeinfo>
#include <vector>

using namespace opensolid;

template <class Type>
void printDirectAccess(const Type& argument) {
    std::cout << typeid(Type).name();
    if (internal::has_direct_access<Type>::ret) {
        std::cout << " has direct access" << std::endl;
    } else {
        std::cout << " does not have direct access" << std::endl;
    }
}

struct MyVector
{
    MyVector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {
    }

    double x;
    double y;
    double z;
};

namespace opensolid
{
    template <>
    struct ConversionFunction<MyVector, Vector3d>
    {
        Vector3d operator()(const MyVector& argument) const {
            return Vector3d(argument.x, argument.y, argument.z);
        }
    };

    template <>
    struct ConversionFunction<Vector3d, MyVector>
    {
        MyVector operator()(const Vector3d& argument) const {
            return MyVector(argument.x(), argument.y(), argument.z());
        }
    };
}

class MatrixTests : public CxxTest::TestSuite
{
private:
    double a;
    Interval b;
    Vector3d u;
    Vector3I v;
public:
    void setUp() {
        a = 2;
        b = Interval(2, 3);
        u = Vector3d(1, 2, 3);
        v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4));
    }

    void testOverlap() {
        TS_ASSERT(u.cast<Interval>().overlaps(v));
        TS_ASSERT(v.overlaps(u.cast<Interval>()));
        TS_ASSERT(!v.overlaps((3 * u).cast<Interval>()));
    }
    
    void testHull() {
        Vector3I result = (3 * u).cast<Interval>().hull(v);
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3d(3, 6, 9));
        result = v.hull((3 * u).cast<Interval>());
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3d(3, 6, 9));
        result = Vector3I::Hull(Vector3d(4, 2, 6), Vector3d(1, 5, 3));
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3d(4, 5, 6));
    }
    
    void testIntersection() {
        Vector3I x = (u.array() + 0.5).matrix().cast<Interval>().intersection(v);
        Vector3I y = (u.array() + 0.5).matrix().cast<Interval>();
        TS_ASSERT_EQUALS(x.cwiseLower(), y.cwiseLower());
        TS_ASSERT_EQUALS(x.cwiseUpper(), y.cwiseUpper());
        x = (v.array() + Interval(0.5)).matrix().intersection(v);
        y = Vector3I(Interval(1.5, 2), Interval(2.5, 3), Interval(3.5, 4));
        TS_ASSERT_EQUALS(x.cwiseLower(), y.cwiseLower());
        TS_ASSERT_EQUALS(x.cwiseUpper(), y.cwiseUpper());
    }
    
    void testIsZero() {
        Vector3d zero(0, 0, 0);
        TS_ASSERT(zero.isZero());
        TS_ASSERT(!u.isZero());
    }
    
    void testLinSpaced() {
        VectorXd x = VectorXd::LinSpaced(3, 1, 2);
        VectorXd y = VectorXd::LinSpaced(3, Interval(1, 2));
        TS_ASSERT_EQUALS(x, Vector3d(1, 1.5, 2));
        TS_ASSERT_EQUALS(y, Vector3d(1, 1.5, 2));
        
        RowVectorXd a = RowVectorXd::LinSpaced(3, 1, 2);
        RowVectorXd b = RowVectorXd::LinSpaced(3, Interval(1, 2));
        TS_ASSERT_EQUALS(a, RowVector3d(1, 1.5, 2));
        TS_ASSERT_EQUALS(b, RowVector3d(1, 1.5, 2));
        
        Vector4d c = Vector4d::LinSpaced(Interval(1, 4));
        TS_ASSERT_EQUALS(c, Vector4d(1, 2, 3, 4));
    }
    
    void testDirectAccess() {
        Matrix3d matrix = Matrix3d::Random();
        printDirectAccess(matrix);
        printDirectAccess(3 * matrix);
        printDirectAccess(matrix.replicate(2, 2));
        printDirectAccess(matrix.row(0));
        printDirectAccess(matrix.block(1, 1, 2, 2));
    }
    
    void testIteration() {
        RowVectorXd vector;
        std::vector<double> list;
        list.push_back(1);
        list.push_back(2);
        vector.resize(list.size());
        std::copy(list.begin(), list.end(), begin(vector));
        TS_ASSERT_EQUALS(vector, RowVector2d(1, 2));
        TS_ASSERT_EQUALS(*begin(vector), 1);
        TS_ASSERT_EQUALS(*(end(vector) - 1), 2);
    }
    
    void testBlockIteration() {
        Matrix3d a = Matrix3d::Random();
        int j = 0;
        for (auto i = begin(a.rowwise()); i != end(a.rowwise()); ++i) {
            TS_ASSERT_EQUALS(*i, a.row(j++));
        }
        j = 0;
        for (auto i = begin(a.colwise()); i != end(a.colwise()); ++i) {
            TS_ASSERT_EQUALS(*i, a.col(j++));
        }
        Matrix3d b;
        std::copy(begin(a.colwise()), end(a.colwise()), begin(b.colwise()));
        TS_ASSERT_EQUALS(a, b);
        Matrix3d c;
        std::copy(begin(a.rowwise()), end(a.rowwise()), begin(c.rowwise()));
        TS_ASSERT_EQUALS(a, c);
        std::vector<Vector3d> input(3);
        input[0] = Vector3d::UnitX();
        input[1] = Vector3d::UnitY();
        input[2] = Vector3d::UnitZ();
        Matrix3d d;
        std::copy(input.begin(), input.end(), begin(d.colwise()));
        TS_ASSERT(d.isIdentity());
        std::vector<RowVector3d> output(3);
        std::copy(begin(a.rowwise()), end(a.rowwise()), output.begin());
        for (std::size_t i = 0; i < output.size(); ++i) {
            TS_ASSERT_EQUALS(output[i], a.row(i));
        }
    }
    
    void testPointerAccess() {
        Matrix3d a = Matrix3d::Zero();
        double* writePtr;
        writePtr = &a.coeffRef(0, 0);
        *writePtr = 3;
        writePtr = &a.row(1).coeffRef(0, 0);
        *(writePtr + 1) = 4;
        const Matrix3d b = a;
        const double* readPtr;
        readPtr = b.data();
        TS_ASSERT_EQUALS(*readPtr, 3);
        readPtr = b.row(1).data();
        TS_ASSERT_EQUALS(*(readPtr + 1), 4);
    }

    void testBoostGeometryPoint() {
        #if BOOST_VERSION >= 104700
        Point2d point(3, 4);
        TS_ASSERT_EQUALS(boost::geometry::get<0>(point), 3);
        TS_ASSERT_EQUALS(boost::geometry::get<1>(point), 4);
        Point2d origin = Point2d::Origin();
        TS_ASSERT(boost::geometry::distance(origin, point) - 5 == Zero());
        #endif
    }

    void testBoostGeometryBox() {
        #if BOOST_VERSION >= 104700
        Box2d first_box(Interval(1, 3), Interval(1, 3));
        TS_ASSERT(boost::geometry::area(first_box) - 4 == Zero());
        Box2d second_box(Interval(2, 4), Interval(2, 4));
        TS_ASSERT(boost::geometry::intersects(first_box, second_box));
        Box2d intersection;
        boost::geometry::intersection(first_box, second_box, intersection);
        TS_ASSERT(boost::geometry::area(intersection) - 1 == Zero());
        TS_ASSERT(intersection.cwiseLower().isApprox(Vector2d::Constant(2)));
        TS_ASSERT(intersection.cwiseUpper().isApprox(Vector2d::Constant(3)));
        #endif
    }

    void testTransformed() {
        Point3d point(3, 2, 1);
        TS_ASSERT((point.rotatedAbout(Axis3d::Z(), M_PI / 2) - Point3d(-2, 3, 1)).isZero());
        TS_ASSERT((point.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(3, -1, 2)).isZero());
        TS_ASSERT((point.mirroredAbout(Plane3d::YZ()) - Point3d(-3, 2, 1)).isZero());
    }

    void testRandom() {
        Vector3I bounds = Vector3I::Random();
        TS_ASSERT(bounds.cwiseWidth().minCoeff() > 0);
        for (int i = 0; i < 10; ++i) {
            Vector3d random = bounds.cwiseRandom();
            TS_ASSERT(bounds.contains(random.cast<Interval>()));
        }
    }

    void testConversion() {
        MyVector my_vector = MyVector(1, 2, 3);
        Vector3d from = Vector3d::From(my_vector);
        TS_ASSERT_EQUALS(from, Vector3d(1, 2, 3));
        MyVector to = Vector3d::Ones().to<MyVector>();
        TS_ASSERT_EQUALS(to.x, 1.0);
        TS_ASSERT_EQUALS(to.y, 1.0);
        TS_ASSERT_EQUALS(to.z, 1.0);
    }

    void testPoint() {
        Point3d point1(1, 2, 3);
        Point3d point2(Vector3d(1, 2, 3));
        Point3d point3(4, 5, 6);
        Point3d origin = Point3d::Origin();
        TS_ASSERT((point1 - point2).isZero());
        TS_ASSERT(origin.vector().isZero());
        TS_ASSERT(origin.isOrigin());
        TS_ASSERT((point1 + Vector3d::Constant(3) - point3).isZero());
        TS_ASSERT((point1.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(1, -3, 2)).isZero());
    }

    void testBox() {
        Box3d box1(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        Box3d projected = box1.projectedOnto(Plane3d::YZ());
        TS_ASSERT(projected.x().lowerBound() == Zero());
        TS_ASSERT(projected.x().upperBound() == Zero());
        TS_ASSERT(projected.y().lowerBound() - box1.y().lowerBound() == Zero());
        TS_ASSERT(projected.y().upperBound() - box1.y().upperBound() == Zero());
        TS_ASSERT(projected.z().lowerBound() - box1.z().lowerBound() == Zero());
        TS_ASSERT(projected.z().upperBound() - box1.z().upperBound() == Zero());
    }

    void testMixedOperations() {
        Point3d point(1, 2, 3);
        Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        Vector3I difference1 = point - box;
        Vector3I difference2 = box - point;
        Box3d reconstructed1 = point - difference1;
        Box3d reconstructed2 = point + difference2;
        for (int i = 0; i < 3; ++i) {
            TS_ASSERT(reconstructed1(i).lowerBound() - box(i).lowerBound() == Zero());
            TS_ASSERT(reconstructed1(i).upperBound() - box(i).upperBound() == Zero());
            TS_ASSERT(reconstructed2(i).lowerBound() - box(i).lowerBound() == Zero());
            TS_ASSERT(reconstructed2(i).upperBound() - box(i).upperBound() == Zero());
        }
    }
};
