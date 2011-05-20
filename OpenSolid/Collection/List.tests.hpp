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

#include <cxxtest/TestSuite.h>

#include "List.hpp"

using namespace OpenSolid;

template <class Type>
void testSameData(const List<Type>& first_list, const List<Type>& second_list) {
    TS_ASSERT_EQUALS(&first_list.front(), &second_list.front());
}

template <class Type>
void testDifferentData(const List<Type>& first_list, const List<Type>& second_list) {
    TS_ASSERT_DIFFERS(&first_list.front(), &second_list.front());
}

class ListTestSuite : public CxxTest::TestSuite
{
public:
    void testItem() {
        List<double> list(1);
        list[0] = 3;
        TS_ASSERT_EQUALS(list.item(), 3.0);
        list.item() = 4;
        TS_ASSERT_EQUALS(list[0], 4.0);
    }
    
    void testImplicitSharing() {
        List<double> first_list(1.0, 2.0, 3.0);
        List<double> second_list(first_list);
        testSameData(first_list, second_list);
        second_list[1] = 4;
        TS_ASSERT_EQUALS(first_list[1], 2.0);
        List<double> third_list(second_list);
        testSameData(second_list, third_list);
        TS_ASSERT_EQUALS(*third_list.cbegin(), 1.0);
        testSameData(second_list, third_list);
        TS_ASSERT_EQUALS(*third_list.begin(), 1.0);
        testDifferentData(second_list, third_list);
    }
};
