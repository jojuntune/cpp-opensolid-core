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

#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

#include <boost/timer.hpp>

#include <iostream>
#include <cstdint>

using namespace opensolid;

Interval
randomInterval() {
    double mid = 10 * double(rand()) / RAND_MAX;
    double width = double(rand()) / RAND_MAX;
    return Interval(mid - width / 2, mid + width / 2);
}

IntervalVector3d randomVector() {
    return IntervalVector3d(randomInterval(), randomInterval(), randomInterval());
}

void
testConstructionTime() {
    typedef std::pair<std::size_t, std::size_t> TestCase;

    std::vector<TestCase> testCases;
    testCases.push_back(TestCase(10, 100000));
    testCases.push_back(TestCase(100, 10000));
    testCases.push_back(TestCase(1000, 1000));
    testCases.push_back(TestCase(10000, 100));
    testCases.push_back(TestCase(100000, 10));
    testCases.push_back(TestCase(1000000, 1));

    std::cout << std::endl;
    std::cout << "===== SpatialSet construction time =====" << std::endl;
    std::cout << std::endl;

    for (std::size_t testIndex = 0; testIndex < testCases.size(); ++testIndex) {
        std::size_t numItems = testCases[testIndex].first;
        std::size_t numIterations = testCases[testIndex].second;

        std::cout << "Items: " << numItems << ", Iterations: " << numIterations << std::endl;

        std::vector<IntervalVector3d> vectors(numItems);
        for (auto i = vectors.begin(); i != vectors.end(); ++i) {
            *i = randomVector();
        }
    
        boost::timer timer;
        for (std::size_t i = 0; i < numIterations; ++i) {
            SpatialSet<IntervalVector3d> set(vectors.begin(), vectors.end());
        }
        double time = timer.elapsed();
        std::cout << "Time: " << time << " s" << std::endl;

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void
testQueryTime() {
    typedef std::pair<std::size_t, std::size_t> TestCase;

    std::vector<TestCase> testCases;
    testCases.push_back(TestCase(10, 10000000));
    testCases.push_back(TestCase(100, 10000000));
    testCases.push_back(TestCase(1000, 1000000));
    testCases.push_back(TestCase(10000, 1000000));
    testCases.push_back(TestCase(100000, 100000));
    testCases.push_back(TestCase(1000000, 10000));
    
    std::cout << std::endl;
    std::cout << "===== SpatialSet query time =====" << std::endl;
    std::cout << std::endl;

    for (std::size_t testIndex = 0; testIndex < testCases.size(); ++testIndex) {
        std::size_t numItems = testCases[testIndex].first;
        std::size_t numQueries = testCases[testIndex].second;

        std::cout << "Items: " << numItems << ", Queries: " << numQueries << std::endl;

        std::vector<IntervalVector3d> items(numItems);
        std::for_each(
            items.begin(),
            items.end(),
            [] (IntervalVector3d& item) {
                item = randomVector();
            }
        );
    
        std::vector<IntervalVector3d> queryBoxes(numQueries);
        std::for_each(
            queryBoxes.begin(),
            queryBoxes.end(),
            [] (IntervalVector3d& queryBox) {
                queryBox = randomVector();
            }
        );

        SpatialSet<IntervalVector3d> set(items.begin(), items.end());
        std::size_t checksum = 0;
        boost::timer timer;
        for (std::size_t i = 0; i < numQueries; ++i) {
            checksum += std::size_t(set.overlapping(queryBoxes[i]).size());
        }
        double time = timer.elapsed();
        std::cout << "Time: " << time << "s, checksum: " << checksum << std::endl;

        std::cout << std::endl;
    }
}

int
main() {
    testConstructionTime();
    testQueryTime();
    return 0;
}
