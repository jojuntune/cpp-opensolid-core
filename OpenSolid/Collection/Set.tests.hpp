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

template <class DerivedType>
bool isFixedSize(const CollectionBase<DerivedType>& collection) {return false;}

template <class DerivedType>
bool isFixedSize(const FixedSizeCollection<DerivedType>& collection) {return true;}

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
        List<int> list(5);
        list[0] = 3;
        list[1] = 1;
        list[2] = 7;
        list[3] = 2;
        list[4] = 5;
        Set<int> set(list);
        std::cout << set << std::endl;
        testSet(set.rootNode());
        List<int> sorted(set);
        list.sort();
        TS_ASSERT_EQUALS(sorted, list);
    }
    
    void testInterval() {
        List<Interval> list(2);
        list[0] = Interval(1, 2);
        list[1] = Interval(0, 2);
        Set<Interval> set(iteratorRange(list.begin(), list.end()));
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testInterval2() {
        List<Interval> list;
        list.append(Interval(0, 2));
        list.append(Interval(1, 2));
        Set<Interval> set(list);
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testInterval3() {
        List<Interval> list(
            Interval(0, 1),
            Interval(0, 4),
            Interval(0, 2)
        );
        Set<Interval> set(list);
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testVector2I() {
        List<Vector2I> list(5);
        list[0] = Vector2I(Interval(1, 6), Interval(4, 5));
        list[1] = Vector2I(Interval(2, 5), Interval(5, 7));
        list[2] = Vector2I(Interval(4, 7), Interval(3, 6));
        list[3] = Vector2I(Interval(6, 9), Interval(5, 8));
        list[4] = Vector2I(Interval(8, 10), Interval(2, 6));
        Set<Vector2I> set(list);
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testDoubleOverlapping() {
        std::vector<double> list(5);
        list[0] = 5;
        list[1] = 3;
        list[2] = 1;
        list[3] = 4;
        list[4] = 2;
        Set<double> set(iteratorRange(list.begin(), list.end()));
        std::cout << set << std::endl;
        List<double> overlapping = set.overlapping(Interval(2.5, 4.5));
        TS_ASSERT_EQUALS(overlapping.size(), 2);
        TS_ASSERT_EQUALS(overlapping[0], 3);
        TS_ASSERT_EQUALS(overlapping[1], 4);
    }
    
    void testVector2dOverlapping() {
        List<Vector2d> list(4);
        list[0] = Vector2d(1, 1);
        list[1] = Vector2d(5, 1);
        list[2] = Vector2d(1, 3);
        list[3] = Vector2d(5, 3);
        Set<Vector2d> set(list);
        List<Vector2d> overlapping = set.overlapping(Vector2I(Interval(1, 5), Interval(2, 4)));
        TS_ASSERT_EQUALS(overlapping.size(), 2);
        TS_ASSERT_EQUALS(overlapping[0], Vector2d(1, 3));
        TS_ASSERT_EQUALS(overlapping[1], Vector2d(5, 3));
    }
    
    void testIntegerInsertion() {
        Set<int> set;
        set.add(3).add(1).add(7).add(2).add(5);
        std::cout << set << std::endl;
        testSet(set.rootNode());
        set.remove(3);
        std::cout << "3 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.rootNode());
        set.remove(5);
        std::cout << "5 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.rootNode());
        set.remove(7);
        std::cout << "7 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testRebalance() {
        Set<int> set;
        for (int i = 1; i <= 12; ++i) {
            set.add(i);
            std::cout << set << std::endl;
            testSet(set.rootNode());
        }
        for (int i = 12; i >= 1; --i) {
            set.remove(i);
            std::cout << set << std::endl;
            testSet(set.rootNode());
        }
    }
    
    void testMerge() {
        Set<int> parent;
        parent.add(1).add(3).add(5).add(7).add(9).add(11);
        std::cout << parent << std::endl;
        testSet(parent.rootNode());
        Set<int> child;
        child.add(6).add(8).add(10);
        std::cout << child << std::endl;
        testSet(child.rootNode());
        parent.update(child);
        std::cout << parent << std::endl;
        testSet(parent.rootNode());
    }
    
    void testLeafParentBug() {
        Set<Interval> set;
        set.add(Interval(-2, 2)).add(Interval(2, 6));
        std::cout << set << std::endl;
        testSet(set.rootNode());
        set.add(Interval(-1, 1));
        std::cout << set << std::endl;
        testSet(set.rootNode());
    }
    
    void testIntervalConstructionTime() {
        List<Interval> intervals(30000);
        for (List<Interval>::Iterator i = intervals.begin(); i != intervals.end(); ++i) {
            *i = randomInterval();
        }
        
        boost::timer iterator_timer;
        Set<Interval> iterator_set(intervals);
        double iterator_time = iterator_timer.elapsed();
        testSet(iterator_set.rootNode());
        std::cout << "Iterator: " << ", " << iterator_time << " s" << std::endl;
        
        boost::timer insertion_timer;
        Set<Interval> insertion_set;
        for (List<Interval>::Iterator i = intervals.begin(); i != intervals.end(); ++i) {
            insertion_set.add(*i);
        }
        double insertion_time = insertion_timer.elapsed();
        testSet(insertion_set.rootNode());
        std::cout << "Insertion: " << ", " << insertion_time << " s" << std::endl;
        
        std::cout << "Iterator " << insertion_time / iterator_time << " times faster" << std::endl;
    }
    
    void testVectorConstructionTime() {
        List<Vector3I> vectors(30000);
        for (List<Vector3I>::Iterator i = vectors.begin(); i != vectors.end(); ++i) {
            *i = randomVector();
        }
        
        boost::timer iterator_timer;
        Set<Vector3I> iterator_set(vectors);
        double iterator_time = iterator_timer.elapsed();
        testSet(iterator_set.rootNode());
        std::cout << "Iterator: " << ", " << iterator_time << " s" << std::endl;
        
        boost::timer insertion_timer;
        Set<Vector3I> insertion_set;
        for (List<Vector3I>::Iterator i = vectors.begin(); i != vectors.end(); ++i) {
            insertion_set.add(*i);
        }
        double insertion_time = insertion_timer.elapsed();
        testSet(insertion_set.rootNode());
        std::cout << "Insertion: " << ", " << insertion_time << " s" << std::endl;
        
        std::cout << "Iterator " << insertion_time / iterator_time << " times faster" << std::endl;
    }
    
    void testFixedSize() {
        MatrixXd random_vectors = MatrixXd::Random(3, 5);
        IteratorRange<MatrixXd::ConstColIterator> iterator_range(
            random_vectors.colBegin(),
            random_vectors.colEnd()
        );
        TS_ASSERT(isFixedSize(iterator_range));
        Set<Vector3d> set(iterator_range);
        TS_ASSERT(isFixedSize(set));
        TS_ASSERT(!isFixedSize(set.overlapping(randomVector())));
    }
    
    void testItem() {
        Set<Vector3d> set;
        set.add(Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(set.item(), Vector3d(1, 2, 3));
    }
    
    void testSharing() {
        Set<double> set1;
        set1.update(List<double>(1, 2, 4, 5));
        Set<double> set2 = set1;
        TS_ASSERT_EQUALS(set1.rootNode(), set2.rootNode());
        set2.add(3);
        TS_ASSERT_DIFFERS(set1.rootNode(), set2.rootNode());
        std::cout << set1 << std::endl;
        std::cout << set2 << std::endl;
        
        const SetNode<double>* root_node;
        {
            Set<double> set3(List<double>(10, 11, 12));
            root_node = set3.rootNode();
            set1 = set3;
            set2 = set3;
            TS_ASSERT_EQUALS(set1.rootNode(), root_node);
            TS_ASSERT_EQUALS(set2.rootNode(), root_node);
        }
        set1.add(13);
        TS_ASSERT_DIFFERS(set1.rootNode(), root_node);
        set2.add(14);
        TS_ASSERT_EQUALS(set2.rootNode(), root_node);
    }
    
    void testIterator() {
        Set<double> set(List<double>(5, 1, 3, 2, 4));
        Set<double>::Iterator i = set.begin();
        TS_ASSERT_EQUALS(*i, 1);
        ++i;
        TS_ASSERT_EQUALS(*i, 2);
        ++i;
        TS_ASSERT_EQUALS(*i, 3);
        --i;
        TS_ASSERT_EQUALS(*i, 2);
        ++i;
        ++i;
        TS_ASSERT_EQUALS(*i, 4);
        ++i;
        TS_ASSERT_EQUALS(*i, 5);
        ++i;
        TS_ASSERT_EQUALS(i, set.end());
    }
    
    void testTraversalTime() {
        List<Vector3I> list(200000);
        for (List<Vector3I>::Iterator i = list.begin(); i != list.end(); ++i) {*i = randomVector();}
        Set<Vector3I> set(list);
        
        boost::timer visitation_timer;
        TestVisitor visitor;
        set.visit(visitor);
        double visitation_time = visitation_timer.elapsed();
        std::cout << "Visitation: " << visitor.total_sum;
        std::cout << " in " << visitation_time << " s" << std::endl;
        
        
        boost::timer iteration_timer;
        double total_sum = 0.0;
        for (Set<Vector3I>::Iterator i = set.begin(); i != set.end(); ++i) {
            total_sum += i->cwiseWidth().sum();
        }
        double iteration_time = iteration_timer.elapsed();
        std::cout << "Iteration: " << total_sum << " in " << iteration_time << " s" << std::endl;
        
        std::cout << "Visitation " << iteration_time / visitation_time;
        std::cout << " times faster" << std::endl;
    }
    
    void testFilteredTraversal() {
        Set<double> set(List<double>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
        FilteredSetIterator<double, TestFilter> i = set.filtered(TestFilter()).begin();
        TS_ASSERT_EQUALS(*i, 2.0);
        ++i;
        TS_ASSERT_EQUALS(*i, 3.0);
        ++i;
        TS_ASSERT_EQUALS(*i, 4.0);
        --i;
        TS_ASSERT_EQUALS(*i, 3.0);
        ++i;
        ++i;
        TS_ASSERT_EQUALS(*i, 7.0);
        ++i;
        TS_ASSERT_EQUALS(*i, 8.0);
        ++i;
        TS_ASSERT_EQUALS(*i, 9.0);
        ++i;
        TS_ASSERT_EQUALS(*i, 10.0);
        ++i;
        TS_ASSERT_EQUALS(i, set.filtered(TestFilter()).end());
    }
};
