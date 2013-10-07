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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Set.hpp>

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

Vector3I
randomVector() {
    return Vector3I(randomInterval(), randomInterval(), randomInterval());
}

void
testConstructionTime() {
    typedef std::pair<std::int64_t, std::int64_t> TestCase;

    std::vector<TestCase> testCases;
    testCases.push_back(TestCase(10, 100000));
    testCases.push_back(TestCase(100, 10000));
    testCases.push_back(TestCase(1000, 1000));
    testCases.push_back(TestCase(10000, 100));
    testCases.push_back(TestCase(100000, 10));
    testCases.push_back(TestCase(1000000, 1));

    std::cout << std::endl;
    std::cout << "===== Set construction time =====" << std::endl;
    std::cout << std::endl;

    for (std::size_t testIndex = 0; testIndex < testCases.size(); ++testIndex) {
        std::int64_t numElements = testCases[testIndex].first;
        std::int64_t numIterations = testCases[testIndex].second;

        std::cout << "Elements: " << numElements << ", Iterations: " << numIterations << std::endl;

        std::vector<Vector3I> vectors(numElements);
        for (auto i = vectors.begin(); i != vectors.end(); ++i) {
            *i = randomVector();
        }
    
        boost::timer timer;
        for (std::int64_t i = 0; i < numIterations; ++i) {
            Set<Vector3I> set(vectors.begin(), vectors.end());
        }
        double time = timer.elapsed();
        std::cout << "Time: " << time << " s" << std::endl;

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void
testQueryTime() {
    typedef std::pair<std::int64_t, std::int64_t> TestCase;

    std::vector<TestCase> testCases;
    testCases.push_back(TestCase(10, 10000000));
    testCases.push_back(TestCase(100, 10000000));
    testCases.push_back(TestCase(1000, 1000000));
    testCases.push_back(TestCase(10000, 1000000));
    testCases.push_back(TestCase(100000, 100000));
    testCases.push_back(TestCase(1000000, 10000));
    
    std::cout << std::endl;
    std::cout << "===== Set query time =====" << std::endl;
    std::cout << std::endl;

    for (std::size_t testIndex = 0; testIndex < testCases.size(); ++testIndex) {
        std::int64_t numElements = testCases[testIndex].first;
        std::int64_t numQueries = testCases[testIndex].second;

        std::cout << "Elements: " << numElements << ", Queries: " << numQueries << std::endl;

        std::vector<Vector3I> elements(numElements);
        std::for_each(
            elements.begin(),
            elements.end(),
            [] (Vector3I& element) {
                element = randomVector();
            }
        );
    
        std::vector<Vector3I> queryBoxes(numQueries);
        std::for_each(
            queryBoxes.begin(),
            queryBoxes.end(),
            [] (Vector3I& queryBox) {
                queryBox = randomVector();
            }
        );

        Set<Vector3I> set(elements.begin(), elements.end());
        std::int64_t checksum = 0;
        boost::timer timer;
        for (std::int64_t i = 0; i < numQueries; ++i) {
            set.forEachOverlapping(
                queryBoxes[i],
                [&checksum] (const Vector3I& element) {
                    ++checksum;
                }
            );
        }
        double time = timer.elapsed();
        std::cout << "Time: " << time << "s, checksum: " << checksum << std::endl;

        std::cout << std::endl;
    }
}

void
main() {
    testConstructionTime();
    testQueryTime();
}
