/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <opensolid/config.hpp>

namespace opensolid
{
    class Interval;

    class IntervalBridge
    {
    public:
        OPENSOLID_BRIDGE_EXPORT IntervalBridge();
        OPENSOLID_BRIDGE_EXPORT IntervalBridge(double value);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge(double lower, double upper);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge(const IntervalBridge& other);

        OPENSOLID_BRIDGE_EXPORT double lower() const;
        OPENSOLID_BRIDGE_EXPORT double upper() const;
        OPENSOLID_BRIDGE_EXPORT double median() const;
        OPENSOLID_BRIDGE_EXPORT double random() const;
        OPENSOLID_BRIDGE_EXPORT double width() const;

        OPENSOLID_BRIDGE_EXPORT double clamp(double argument) const;
        OPENSOLID_BRIDGE_EXPORT IntervalBridge clamp(const IntervalBridge& argument) const;
        OPENSOLID_BRIDGE_EXPORT double interpolated(double argument) const;
        OPENSOLID_BRIDGE_EXPORT IntervalBridge interpolated(const IntervalBridge& argument) const;
        
        OPENSOLID_BRIDGE_EXPORT IntervalBridge squared() const;
        
        OPENSOLID_BRIDGE_EXPORT bool isEmpty() const;
        OPENSOLID_BRIDGE_EXPORT bool isSingleton() const;
        
        OPENSOLID_BRIDGE_EXPORT std::pair<IntervalBridge, IntervalBridge> bisected() const;
        
        OPENSOLID_BRIDGE_EXPORT IntervalBridge hull(const IntervalBridge& argument) const;
        OPENSOLID_BRIDGE_EXPORT IntervalBridge intersection(const IntervalBridge& argument) const;
        
        OPENSOLID_BRIDGE_EXPORT bool contains(
            double argument,
            double tolerance = 1e-12
        ) const;
        
        OPENSOLID_BRIDGE_EXPORT bool strictlyContains(
            double argument,
            double tolerance = 1e-12
        ) const;

        OPENSOLID_BRIDGE_EXPORT bool contains(
            const IntervalBridge& argument,
            double tolerance = 1e-12
        ) const;
        
        OPENSOLID_BRIDGE_EXPORT bool strictlyContains(
            const IntervalBridge& argument,
            double tolerance = 1e-12
        ) const;

        OPENSOLID_BRIDGE_EXPORT bool overlaps(
            const IntervalBridge& argument,
            double tolerance = 1e-12
        ) const;
        
        OPENSOLID_BRIDGE_EXPORT bool strictlyOverlaps(
            const IntervalBridge& argument,
            double tolerance = 1e-12
        ) const;
        
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator+=(double argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator+=(const IntervalBridge& argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator-=(double argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator-=(const IntervalBridge& argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator*=(double argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator*=(const IntervalBridge& argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator/=(double argument);
        OPENSOLID_BRIDGE_EXPORT IntervalBridge& operator/=(const IntervalBridge& argument);
        
        OPENSOLID_BRIDGE_EXPORT static IntervalBridge Hull(
            double first_argument,
            double second_argument
        );
        
        OPENSOLID_BRIDGE_EXPORT static IntervalBridge Empty();
        OPENSOLID_BRIDGE_EXPORT static IntervalBridge Whole();
    private:
        IntervalBridge(const Interval& argument);

        Interval* _interval;
    };   
}