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

#include <OpenSolid/Common/Comparison.hpp>
#include <OpenSolid/Interval/Interval.hpp>
#include "Matrix.hpp"

using namespace OpenSolid;

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
    Double a;
    Interval b;
    Vector3D u;
    Vector3I v;
public:
    void setUp() {
        a = 2;
        b = Interval(2, 3);
        u = Vector3D(1, 2, 3);
        v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4));
    }

    void testOverlap() {
        TS_ASSERT(u.cast<Interval>().overlaps(v));
        TS_ASSERT(v.overlaps(u.cast<Interval>()));
        TS_ASSERT(!v.overlaps((3 * u).cast<Interval>()));
    }
    
    void testHull() {
        Vector3I result = (3 * u).cast<Interval>().hull(v);
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3D(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3D(3, 6, 9));
        result = v.hull((3 * u).cast<Interval>());
        TS_ASSERT_EQUALS(result.cwiseLower(), Vector3D(1, 2, 3));
        TS_ASSERT_EQUALS(result.cwiseUpper(), Vector3D(3, 6, 9));
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
        Vector3D zero(0, 0, 0);
        TS_ASSERT(zero.isZero());
        TS_ASSERT(!u.isZero());
    }
    
    void testLinSpaced() {
        VectorXd x = VectorXd::LinSpaced(3, 1, 2);
        VectorXd y = VectorXd::LinSpaced(3, Interval(1, 2));
        TS_ASSERT_EQUALS(x, Vector3D(1, 1.5, 2));
        TS_ASSERT_EQUALS(y, Vector3D(1, 1.5, 2));
        
        RowVectorXd a = RowVectorXd::LinSpaced(3, 1, 2);
        RowVectorXd b = RowVectorXd::LinSpaced(3, Interval(1, 2));
        TS_ASSERT_EQUALS(a, RowVector3D(1, 1.5, 2));
        TS_ASSERT_EQUALS(b, RowVector3D(1, 1.5, 2));
        
        Vector4D c = Vector4D::LinSpaced(Interval(1, 4));
        TS_ASSERT_EQUALS(c, Vector4D(1, 2, 3, 4));
    }
    
    void testDirectAccess() {
        Matrix3D matrix = Matrix3D::Random();
        printDirectAccess(matrix);
        printDirectAccess(3 * matrix);
        printDirectAccess(matrix.replicate(2, 2));
        printDirectAccess(matrix.row(0));
        printDirectAccess(matrix.block(1, 1, 2, 2));
    }
    
    void testIteration() {
        RowVectorXd vector;
        std::vector<Double> list;
        list.push_back(1);
        list.push_back(2);
        vector.resize(list.size());
        std::copy(list.begin(), list.end(), vector.begin());
        TS_ASSERT_EQUALS(vector, RowVector2D(1, 2));
        TS_ASSERT_EQUALS(*vector.begin(), 1);
        TS_ASSERT_EQUALS(*(vector.end() - 1), 2);
    }
    
    void testBlockIteration() {
        Matrix3D a = Matrix3D::Random();
        int j = 0;
        for (Matrix3D::ConstRowIterator i = a.rowBegin(); i != a.rowEnd(); ++i) {
            TS_ASSERT_EQUALS(*i, a.row(j++));
        }
        j = 0;
        for (Matrix3D::ConstColIterator i = a.colBegin(); i != a.colEnd(); ++i) {
            TS_ASSERT_EQUALS(*i, a.col(j++));
        }
        Matrix3D b;
        std::copy(a.colBegin(), a.colEnd(), b.colBegin());
        TS_ASSERT_EQUALS(a, b);
        Matrix3D c;
        std::copy(a.rowBegin(), a.rowEnd(), c.rowBegin());
        TS_ASSERT_EQUALS(a, c);
        std::vector<Vector3D> input(3);
        input[0] = Vector3D::UnitX();
        input[1] = Vector3D::UnitY();
        input[2] = Vector3D::UnitZ();
        Matrix3D d;
        std::copy(input.begin(), input.end(), d.colBegin());
        TS_ASSERT(d.isIdentity());
        std::vector<RowVector3D> output(3);
        std::copy(a.rowBegin(), a.rowEnd(), output.begin());
        for (std::size_t i = 0; i < output.size(); ++i) {
            TS_ASSERT_EQUALS(output[i], a.row(i));
        }
    }
    
    void testPointerAccess() {
        Matrix3D a = Matrix3D::Zero();
        Double* write;
        write = &a.coeffRef(0, 0);
        *write = 3;
        write = &a.row(1).coeffRef(0, 0);
        *(write + 1) = 4;
        const Matrix3D b = a;
        const Double* read;
        read = b.data();
        TS_ASSERT_EQUALS(*read, 3);
        read = b.row(1).data();
        TS_ASSERT_EQUALS(*(read + 1), 4);
    }
};
