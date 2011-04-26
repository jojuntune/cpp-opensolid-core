/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <typeinfo>

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Collection/List.hpp>
#include <OpenSolid/Collection/IteratorRange.hpp>
#include "Interval.hpp"
#include "Matrix.hpp"

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

class MatrixTestSuite : public CxxTest::TestSuite
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
        TS_ASSERT(u.cast<Interval>().overlap(v));
        TS_ASSERT(v.overlap(u.cast<Interval>()));
        TS_ASSERT(!v.overlap((3 * u).cast<Interval>()));
    }
    
    void testHull() {
        Vector3I result = (3 * u).cast<Interval>().hull(v);
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3d(3, 6, 9));
        result = v.hull((3 * u).cast<Interval>());
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3d(3, 6, 9));
    }
    
    void testCentered() {
        Vector3I v = Vector3d(1, 2, 3).hull(Vector3d(4, 5, 6));
        TS_ASSERT_EQUALS(v.cwiseMedian(), Vector3d(2.5, 3.5, 4.5));
        TS_ASSERT_EQUALS(v.cwiseCentered().cwiseMedian(), Vector3d::Zero());
        TS_ASSERT_EQUALS(v.cwiseCentered().cwiseLower(), Vector3d::Constant(-1.5));
        TS_ASSERT_EQUALS(v.cwiseCentered().cwiseUpper(), Vector3d::Constant(1.5));
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
    
    void testBisected() {
        Matrix2I matrix;
        matrix << Interval(1, 2), Interval(3, 4), Interval(5, 7), Interval(8, 9);
        Pair<Matrix2I> bisected = matrix.bisected();
        TS_ASSERT_EQUALS(bisected.first().cwiseLower(), (Matrix2d() << 1, 3, 5, 8).finished());
        TS_ASSERT_EQUALS(bisected.first().cwiseUpper(), (Matrix2d() << 2, 4, 6, 9).finished());
        TS_ASSERT_EQUALS(bisected.second().cwiseLower(), (Matrix2d() << 1, 3, 6, 8).finished());
        TS_ASSERT_EQUALS(bisected.second().cwiseUpper(), (Matrix2d() << 2, 4, 7, 9).finished());
        
        matrix << Interval(2, 3), Interval(4, 5), Interval(6, 8), Interval(9, 10);
        Matrix2I first, second;
        Pair<Matrix2I&>(first, second) = matrix.bisected();
        TS_ASSERT_EQUALS(first.cwiseLower(), (Matrix2d() << 2, 4, 6, 9).finished());
        TS_ASSERT_EQUALS(first.cwiseUpper(), (Matrix2d() << 3, 5, 7, 10).finished());
        TS_ASSERT_EQUALS(second.cwiseLower(), (Matrix2d() << 2, 4, 7, 9).finished());
        TS_ASSERT_EQUALS(second.cwiseUpper(), (Matrix2d() << 3, 5, 8, 10).finished());
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
        Matrix3d a = Matrix3d::Random();
        int j = 0;
        for (Matrix3d::ConstRowIterator i = a.rowBegin(); i != a.rowEnd(); ++i) {
            TS_ASSERT_EQUALS(*i, a.row(j++));
        }
        j = 0;
        for (Matrix3d::ConstColIterator i = a.colBegin(); i != a.colEnd(); ++i) {
            TS_ASSERT_EQUALS(*i, a.col(j++));
        }
        Matrix3d b;
        std::copy(a.colBegin(), a.colEnd(), b.colBegin());
        TS_ASSERT_EQUALS(a, b);
        Matrix3d c;
        std::copy(a.rowBegin(), a.rowEnd(), c.rowBegin());
        TS_ASSERT_EQUALS(a, c);
        List<Vector3d> input(Vector3d::UnitX(), Vector3d::UnitY(), Vector3d::UnitZ());
        Matrix3d d;
        std::copy(input.begin(), input.end(), d.colBegin());
        TS_ASSERT(d.isIdentity());
        List<RowVector3d> output(3);
        std::copy(a.rowBegin(), a.rowEnd(), output.begin());
        for (int i = 0; i < output.size(); ++i) {
            TS_ASSERT_EQUALS(output[i], a.row(i));
        }
        output.extend(IteratorRange<Matrix3d::ConstRowIterator>(d.rowBegin(), d.rowEnd()));
        for (int i = 3; i < output.size(); ++i) {
            TS_ASSERT_EQUALS(output[i], RowVector3d::Unit(i - 3));
        }
        std::cout << output << std::endl;
    }
    
    void testPointerAccess() {
        Matrix3d a = Matrix3d::Zero();
        double* write;
        write = &a.coeffRef(0, 0);
        *write = 3;
        write = &a.row(1).coeffRef(0, 0);
        *(write + 1) = 4;
        const Matrix3d b = a;
        const double* read;
        read = b.data();
        TS_ASSERT_EQUALS(*read, 3);
        read = b.row(1).data();
        TS_ASSERT_EQUALS(*(read + 1), 4);
    }
};
