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

#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <OpenSolid/Value/Matrix.hpp>
#include "Set.hpp"
#include "IteratorRange.hpp"

using namespace OpenSolid;

template <class Type>
void testSet(const SetNode<Type>* node) {
    double tolerance = Tolerance::roundoff();
    if (!node || node->size() == 1) {
        return;
    } else {
        const SetNode<Type>* left = node->left();
        const SetNode<Type>* right = node->right();
        TS_ASSERT(node->bounds().contain(left->bounds(), tolerance));
        TS_ASSERT(node->bounds().contain(right->bounds(), tolerance));
        testSet(node->left());
        testSet(node->right());
    }
}

Interval randomInterval() {
    double mid = 10 * double(rand()) / RAND_MAX;
    double width = double(rand()) / RAND_MAX;
    return Interval(mid - width / 2, mid + width / 2);
}

Vector3I randomVector() {return Vector3I(randomInterval(), randomInterval(), randomInterval());}

struct TestVisitor
{
    double total_sum;
    
    inline TestVisitor() : total_sum(0.0) {}
    
    inline void operator()(const Vector3I& vector) {total_sum += vector.cwiseWidth().sum();}
};

struct TestFilter
{
    inline bool operator()(const Interval& interval) const {
        return interval.overlap(Interval(2, 4)) || interval.overlap(Interval(7, 10));
    }
};

class SetTestSuite : public CxxTest::TestSuite
{
public:
    void testInteger() {
        std::vector<int> list(5);
        list[0] = 3;
        list[1] = 1;
        list[2] = 7;
        list[3] = 2;
        list[4] = 5;
        Set<int> set(list.begin(), list.end());
        std::cout << set << std::endl;
        testSet(set.root());
        std::vector<int> sorted(set.begin(), set.end());
        std::sort(list.begin(), list.end());
        TS_ASSERT_EQUALS(sorted, list);
    }
    
    void testInterval() {
        std::vector<Interval> list(2);
        list[0] = Interval(1, 2);
        list[1] = Interval(0, 2);
        Set<Interval> set(list.begin(), list.end());
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testInterval2() {
        std::vector<Interval> list;
        list.push_back(Interval(0, 2));
        list.push_back(Interval(1, 2));
        Set<Interval> set(list.begin(), list.end());
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testInterval3() {
        std::vector<Interval> list(3);
        list[0] = Interval(0, 1);
        list[1] = Interval(0, 4);
        list[2] = Interval(0, 2);
        Set<Interval> set(list.begin(), list.end());
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testVector2I() {
        std::vector<Vector2I> list(5);
        list[0] = Vector2I(Interval(1, 6), Interval(4, 5));
        list[1] = Vector2I(Interval(2, 5), Interval(5, 7));
        list[2] = Vector2I(Interval(4, 7), Interval(3, 6));
        list[3] = Vector2I(Interval(6, 9), Interval(5, 8));
        list[4] = Vector2I(Interval(8, 10), Interval(2, 6));
        Set<Vector2I> set(list.begin(), list.end());
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testDoubleOverlapping() {
        std::vector<double> list(5);
        list[0] = 5;
        list[1] = 3;
        list[2] = 1;
        list[3] = 4;
        list[4] = 2;
        Set<double> set(list.begin(), list.end());
        std::cout << set << std::endl;
        Set<double> overlapping = set.overlapping(Interval(2.5, 4.5));
        TS_ASSERT_EQUALS(overlapping.size(), 2u);
        std::cout << overlapping.front() - 3 << ", " << overlapping.back() - 4 << std::endl;
        TS_ASSERT_EQUALS(overlapping.front(), 3);
        TS_ASSERT_EQUALS(overlapping.back(), 4);
    }
    
    void testVector2dOverlapping() {
        std::vector<Vector2d> list(4);
        list[0] = Vector2d(1, 1);
        list[1] = Vector2d(5, 1);
        list[2] = Vector2d(1, 3);
        list[3] = Vector2d(5, 3);
        Set<Vector2d> set(list.begin(), list.end());
        Set<Vector2d> overlapping = set.overlapping(Vector2I(Interval(1, 5), Interval(2, 4)));
        TS_ASSERT_EQUALS(overlapping.size(), 2u);
        TS_ASSERT_EQUALS(overlapping.front(), Vector2d(1, 3));
        TS_ASSERT_EQUALS(overlapping.back(), Vector2d(5, 3));
    }
    
    void testIntegerInsertion() {
        Set<int> set;
        set.insert(3);
        set.insert(1);
        set.insert(7);
        set.insert(2);
        set.insert(5);
        std::cout << set << std::endl;
        testSet(set.root());
        set.erase(3);
        std::cout << "3 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
        set.erase(5);
        std::cout << "5 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
        set.erase(7);
        std::cout << "7 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testRebalance() {
        Set<int> set;
        for (int i = 1; i <= 12; ++i) {
            set.insert(i);
            std::cout << set << std::endl;
            testSet(set.root());
        }
        for (int i = 12; i >= 1; --i) {
            set.erase(i);
            std::cout << set << std::endl;
            testSet(set.root());
        }
    }
    
    void testLeafParentBug() {
        Set<Interval> set;
        set.insert(Interval(-2, 2));
        set.insert(Interval(2, 6));
        std::cout << set << std::endl;
        testSet(set.root());
        set.insert(Interval(-1, 1));
        std::cout << set << std::endl;
        testSet(set.root());
    }
    
    void testIntervalConstructionTime() {
        std::vector<Interval> intervals(30000);
        for (std::vector<Interval>::iterator i = intervals.begin(); i != intervals.end(); ++i) {
            *i = randomInterval();
        }
        
        boost::timer iterator_timer;
        Set<Interval> iterator_set(intervals.begin(), intervals.end());
        double iterator_time = iterator_timer.elapsed();
        testSet(iterator_set.root());
        std::cout << "Iterator: " << ", " << iterator_time << " s" << std::endl;
        
        boost::timer insertion_timer;
        Set<Interval> insertion_set;
        for (std::vector<Interval>::iterator i = intervals.begin(); i != intervals.end(); ++i) {
            insertion_set.insert(*i);
        }
        double insertion_time = insertion_timer.elapsed();
        testSet(insertion_set.root());
        std::cout << "Insertion: " << ", " << insertion_time << " s" << std::endl;
        
        std::cout << "Iterator " << insertion_time / iterator_time << " times faster" << std::endl;
    }
    
    void testVectorConstructionTime() {
        std::vector<Vector3I> vectors(30000);
        for (std::vector<Vector3I>::iterator i = vectors.begin(); i != vectors.end(); ++i) {
            *i = randomVector();
        }
        
        boost::timer iterator_timer;
        Set<Vector3I> iterator_set(vectors.begin(), vectors.end());
        double iterator_time = iterator_timer.elapsed();
        testSet(iterator_set.root());
        std::cout << "Iterator: " << ", " << iterator_time << " s" << std::endl;
        
        boost::timer insertion_timer;
        Set<Vector3I> insertion_set;
        for (std::vector<Vector3I>::iterator i = vectors.begin(); i != vectors.end(); ++i) {
            insertion_set.insert(*i);
        }
        double insertion_time = insertion_timer.elapsed();
        testSet(insertion_set.root());
        std::cout << "Insertion: " << ", " << insertion_time << " s" << std::endl;
        
        std::cout << "Iterator " << insertion_time / iterator_time << " times faster" << std::endl;
    }
    
    void testSharing() {
        std::vector<double> list(4);
        list[0] = 1;
        list[1] = 2;
        list[2] = 4;
        list[3] = 5;
        Set<double> set1(list.begin(), list.end());
        Set<double> set2 = set1;
        TS_ASSERT_EQUALS(set1.root(), set2.root());
        set2.insert(3);
        TS_ASSERT_DIFFERS(set1.root(), set2.root());
        std::cout << set1 << std::endl;
        std::cout << set2 << std::endl;
        
        const SetNode<double>* root;
        {
            std::vector<double> list2(3);
            list2[0] = 10;
            list2[1] = 11;
            list2[2] = 12;
            Set<double> set3(list2.begin(), list2.end());
            root = set3.root();
            set1 = set3;
            set2 = set3;
            TS_ASSERT_EQUALS(set1.root(), root);
            TS_ASSERT_EQUALS(set2.root(), root);
        }
        set1.insert(13);
        TS_ASSERT_DIFFERS(set1.root(), root);
        set2.insert(14);
        TS_ASSERT_EQUALS(set2.root(), root);
    }
    
    void testIterator() {
        std::vector<double> list(5);
        list[0] = 5;
        list[1] = 1;
        list[2] = 3;
        list[3] = 2;
        list[4] = 4;
        Set<double> set(list.begin(), list.end());
        Set<double>::Iterator i = set.begin();
        TS_ASSERT_EQUALS(*i, 1);
        ++i;
        TS_ASSERT_EQUALS(*i, 2);
        ++i;
        TS_ASSERT_EQUALS(*i, 3);
        ++i;
        TS_ASSERT_EQUALS(*i, 4);
        ++i;
        TS_ASSERT_EQUALS(*i, 5);
        ++i;
        TS_ASSERT_EQUALS(i, set.end());
    }
};
