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

#ifndef OPENSOLID__OPERATORS_HPP
#define OPENSOLID__OPERATORS_HPP

#include <algorithm>

#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/Matrix.hpp>
#include <OpenSolid/Value/Box.hpp>

namespace OpenSolid
{
    using std::min;
    using std::max;
    using boost::numeric::min;
    using boost::numeric::max;

    class Double;
    class Interval;

    bool operator==(Double first_argument, Double second_argument);
    bool operator==(Double first_argument, Interval second_argument);
    bool operator==(Double first_argument, int second_argument);
    bool operator==(int first_argument, Double second_argument);
    bool operator==(Double first_argument, float second_argument);
    bool operator==(float first_argument, Double second_argument);
    bool operator==(Double first_argument, double second_argument);
    bool operator==(double first_argument, Double second_argument);

    bool operator==(Interval first_argument, Interval second_argument);
    bool operator==(Interval first_argument, Double second_argument);
    bool operator==(Interval first_argument, int second_argument);
    bool operator==(int first_argument, Interval second_argument);
    bool operator==(Interval first_argument, float second_argument);
    bool operator==(float first_argument, Interval second_argument);
    bool operator==(Interval first_argument, double second_argument);
    bool operator==(double first_argument, Interval second_argument);

    bool operator!=(Double first_argument, Double second_argument);
    bool operator!=(Double first_argument, Interval second_argument);
    bool operator!=(Double first_argument, int second_argument);
    bool operator!=(int first_argument, Double second_argument);
    bool operator!=(Double first_argument, float second_argument);
    bool operator!=(float first_argument, Double second_argument);
    bool operator!=(Double first_argument, double second_argument);
    bool operator!=(double first_argument, Double second_argument);

    bool operator!=(Interval first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, Double second_argument);
    bool operator!=(Interval first_argument, int second_argument);
    bool operator!=(int first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, float second_argument);
    bool operator!=(float first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, double second_argument);
    bool operator!=(double first_argument, Interval second_argument);

    bool operator<(Double first_argument, Double second_argument);
    bool operator<(Double first_argument, Interval second_argument);
    bool operator<(Double first_argument, int second_argument);
    bool operator<(int first_argument, Double second_argument);
    bool operator<(Double first_argument, float second_argument);
    bool operator<(float first_argument, Double second_argument);
    bool operator<(Double first_argument, double second_argument);
    bool operator<(double first_argument, Double second_argument);

    bool operator<(Interval first_argument, Interval second_argument);
    bool operator<(Interval first_argument, Double second_argument);
    bool operator<(Interval first_argument, int second_argument);
    bool operator<(int first_argument, Interval second_argument);
    bool operator<(Interval first_argument, float second_argument);
    bool operator<(float first_argument, Interval second_argument);
    bool operator<(Interval first_argument, double second_argument);
    bool operator<(double first_argument, Interval second_argument);

    bool operator>(Double first_argument, Double second_argument);
    bool operator>(Double first_argument, Interval second_argument);
    bool operator>(Double first_argument, int second_argument);
    bool operator>(int first_argument, Double second_argument);
    bool operator>(Double first_argument, float second_argument);
    bool operator>(float first_argument, Double second_argument);
    bool operator>(Double first_argument, double second_argument);
    bool operator>(double first_argument, Double second_argument);

    bool operator>(Interval first_argument, Interval second_argument);
    bool operator>(Interval first_argument, Double second_argument);
    bool operator>(Interval first_argument, int second_argument);
    bool operator>(int first_argument, Interval second_argument);
    bool operator>(Interval first_argument, float second_argument);
    bool operator>(float first_argument, Interval second_argument);
    bool operator>(Interval first_argument, double second_argument);
    bool operator>(double first_argument, Interval second_argument);

    bool operator<=(Double first_argument, Double second_argument);
    bool operator<=(Double first_argument, Interval second_argument);
    bool operator<=(Double first_argument, int second_argument);
    bool operator<=(int first_argument, Double second_argument);
    bool operator<=(Double first_argument, float second_argument);
    bool operator<=(float first_argument, Double second_argument);
    bool operator<=(Double first_argument, double second_argument);
    bool operator<=(double first_argument, Double second_argument);

    bool operator<=(Interval first_argument, Interval second_argument);
    bool operator<=(Interval first_argument, Double second_argument);
    bool operator<=(Interval first_argument, int second_argument);
    bool operator<=(int first_argument, Interval second_argument);
    bool operator<=(Interval first_argument, float second_argument);
    bool operator<=(float first_argument, Interval second_argument);
    bool operator<=(Interval first_argument, double second_argument);
    bool operator<=(double first_argument, Interval second_argument);

    bool operator>=(Double first_argument, Double second_argument);
    bool operator>=(Double first_argument, Interval second_argument);
    bool operator>=(Double first_argument, int second_argument);
    bool operator>=(int first_argument, Double second_argument);
    bool operator>=(Double first_argument, float second_argument);
    bool operator>=(float first_argument, Double second_argument);
    bool operator>=(Double first_argument, double second_argument);
    bool operator>=(double first_argument, Double second_argument);

    bool operator>=(Interval first_argument, Interval second_argument);
    bool operator>=(Interval first_argument, Double second_argument);
    bool operator>=(Interval first_argument, int second_argument);
    bool operator>=(int first_argument, Interval second_argument);
    bool operator>=(Interval first_argument, float second_argument);
    bool operator>=(float first_argument, Interval second_argument);
    bool operator>=(Interval first_argument, double second_argument);
    bool operator>=(double first_argument, Interval second_argument);

    Double operator-(Double argument);
    Interval operator-(Interval argument);

    Double operator+(Double first_argument, Double second_argument);
    Interval operator+(Double first_argument, Interval second_argument);
    Double operator+(Double first_argument, int second_argument);
    Double operator+(int first_argument, Double second_argument);
    Double operator+(Double first_argument, float second_argument);
    Double operator+(float first_argument, Double second_argument);
    Double operator+(Double first_argument, double second_argument);
    Double operator+(double first_argument, Double second_argument);

    Interval operator+(Interval first_argument, Interval second_argument);
    Interval operator+(Interval first_argument, Double second_argument);
    Interval operator+(Interval first_argument, int second_argument);
    Interval operator+(int first_argument, Interval second_argument);
    Interval operator+(Interval first_argument, float second_argument);
    Interval operator+(float first_argument, Interval second_argument);
    Interval operator+(Interval first_argument, double second_argument);
    Interval operator+(double first_argument, Interval second_argument);

    Double operator-(Double first_argument, Double second_argument);
    Interval operator-(Double first_argument, Interval second_argument);
    Double operator-(Double first_argument, int second_argument);
    Double operator-(int first_argument, Double second_argument);
    Double operator-(Double first_argument, float second_argument);
    Double operator-(float first_argument, Double second_argument);
    Double operator-(Double first_argument, double second_argument);
    Double operator-(double first_argument, Double second_argument);

    Interval operator-(Interval first_argument, Interval second_argument);
    Interval operator-(Interval first_argument, Double second_argument);
    Interval operator-(Interval first_argument, int second_argument);
    Interval operator-(int first_argument, Interval second_argument);
    Interval operator-(Interval first_argument, float second_argument);
    Interval operator-(float first_argument, Interval second_argument);
    Interval operator-(Interval first_argument, double second_argument);
    Interval operator-(double first_argument, Interval second_argument);

    Double operator*(Double first_argument, Double second_argument);
    Interval operator*(Double first_argument, Interval second_argument);
    Double operator*(Double first_argument, int second_argument);
    Double operator*(int first_argument, Double second_argument);
    Double operator*(Double first_argument, float second_argument);
    Double operator*(float first_argument, Double second_argument);
    Double operator*(Double first_argument, double second_argument);
    Double operator*(double first_argument, Double second_argument);

    Interval operator*(Interval first_argument, Interval second_argument);
    Interval operator*(Interval first_argument, Double second_argument);
    Interval operator*(Interval first_argument, int second_argument);
    Interval operator*(int first_argument, Interval second_argument);
    Interval operator*(Interval first_argument, float second_argument);
    Interval operator*(float first_argument, Interval second_argument);
    Interval operator*(Interval first_argument, double second_argument);
    Interval operator*(double first_argument, Interval second_argument);

    Double operator/(Double first_argument, Double second_argument);
    Interval operator/(Double first_argument, Interval second_argument);
    Double operator/(Double first_argument, int second_argument);
    Double operator/(int first_argument, Double second_argument);
    Double operator/(Double first_argument, float second_argument);
    Double operator/(float first_argument, Double second_argument);
    Double operator/(Double first_argument, double second_argument);
    Double operator/(double first_argument, Double second_argument);

    Interval operator/(Interval first_argument, Interval second_argument);
    Interval operator/(Interval first_argument, Double second_argument);
    Interval operator/(Interval first_argument, int second_argument);
    Interval operator/(int first_argument, Interval second_argument);
    Interval operator/(Interval first_argument, float second_argument);
    Interval operator/(float first_argument, Interval second_argument);
    Interval operator/(Interval first_argument, double second_argument);
    Interval operator/(double first_argument, Interval second_argument);

    Double min(Double first_argument, Double second_argument);
    Interval min(Double first_argument, Interval second_argument);
    Double min(Double first_argument, int second_argument);
    Double min(int first_argument, Double second_argument);
    Double min(Double first_argument, float second_argument);
    Double min(float first_argument, Double second_argument);
    Double min(Double first_argument, double second_argument);
    Double min(double first_argument, Double second_argument);

    Interval min(Interval first_argument, Interval second_argument);
    Interval min(Interval first_argument, Double second_argument);
    Interval min(Interval first_argument, int second_argument);
    Interval min(int first_argument, Interval second_argument);
    Interval min(Interval first_argument, float second_argument);
    Interval min(float first_argument, Interval second_argument);
    Interval min(Interval first_argument, double second_argument);
    Interval min(double first_argument, Interval second_argument);

    Double max(Double first_argument, Double second_argument);
    Interval max(Double first_argument, Interval second_argument);
    Double max(Double first_argument, int second_argument);
    Double max(int first_argument, Double second_argument);
    Double max(Double first_argument, float second_argument);
    Double max(float first_argument, Double second_argument);
    Double max(Double first_argument, double second_argument);
    Double max(double first_argument, Double second_argument);

    Interval max(Interval first_argument, Interval second_argument);
    Interval max(Interval first_argument, Double second_argument);
    Interval max(Interval first_argument, int second_argument);
    Interval max(int first_argument, Interval second_argument);
    Interval max(Interval first_argument, float second_argument);
    Interval max(float first_argument, Interval second_argument);
    Interval max(Interval first_argument, double second_argument);
    Interval max(double first_argument, Interval second_argument);
}

////////// Implementation //////////

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    inline bool operator==(Double first_argument, Double second_argument) {
        return first_argument.value() == second_argument.value();
    }

    inline bool operator==(Double first_argument, Interval second_argument) {
        return first_argument.value() == second_argument.value().lower() &&
            first_argument.value() == second_argument.value().upper();
    }

    inline bool operator==(Double first_argument, int second_argument) {
        return first_argument.value() == second_argument;
    }

    inline bool operator==(int first_argument, Double second_argument) {
        return first_argument == second_argument.value();
    }
    inline bool operator==(Double first_argument, float second_argument) {
        return first_argument.value() == second_argument;
    }

    inline bool operator==(float first_argument, Double second_argument) {
        return first_argument == second_argument.value();
    }
    inline bool operator==(Double first_argument, double second_argument) {
        return first_argument.value() == second_argument;
    }

    inline bool operator==(double first_argument, Double second_argument) {
        return first_argument == second_argument.value();
    }

    inline bool operator==(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() == second_argument.value().lower() &&
            first_argument.value().upper() == second_argument.value().upper();
    }

    inline bool operator==(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() == second_argument.value() &&
            first_argument.value().upper() == second_argument.value();
    }

    inline bool operator==(Interval first_argument, int second_argument) {
        return first_argument.value().lower() == second_argument &&
            first_argument.value().upper() == second_argument;
    }

    inline bool operator==(int first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() &&
            first_argument == second_argument.value().upper();
    }
    inline bool operator==(Interval first_argument, float second_argument) {
        return first_argument.value().lower() == second_argument &&
            first_argument.value().upper() == second_argument;
    }

    inline bool operator==(float first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() &&
            first_argument == second_argument.value().upper();
    }
    inline bool operator==(Interval first_argument, double second_argument) {
        return first_argument.value().lower() == second_argument &&
            first_argument.value().upper() == second_argument;
    }

    inline bool operator==(double first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() &&
            first_argument == second_argument.value().upper();
    }

    inline bool operator!=(Double first_argument, Double second_argument) {
        return first_argument.value() != second_argument.value();
    }

    inline bool operator!=(Double first_argument, Interval second_argument) {
        return first_argument.value() != second_argument.value().lower() ||
            first_argument.value() != second_argument.value().upper();
    }

    inline bool operator!=(Double first_argument, int second_argument) {
        return first_argument.value() != second_argument;
    }

    inline bool operator!=(int first_argument, Double second_argument) {
        return first_argument != second_argument.value();
    }
    inline bool operator!=(Double first_argument, float second_argument) {
        return first_argument.value() != second_argument;
    }

    inline bool operator!=(float first_argument, Double second_argument) {
        return first_argument != second_argument.value();
    }
    inline bool operator!=(Double first_argument, double second_argument) {
        return first_argument.value() != second_argument;
    }

    inline bool operator!=(double first_argument, Double second_argument) {
        return first_argument != second_argument.value();
    }

    inline bool operator!=(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() != second_argument.value().lower() ||
            first_argument.value().upper() != second_argument.value().upper();
    }

    inline bool operator!=(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() != second_argument.value() ||
            first_argument.value().upper() != second_argument.value();
    }

    inline bool operator!=(Interval first_argument, int second_argument) {
        return first_argument.value().lower() != second_argument ||
            first_argument.value().upper() != second_argument;
    }

    inline bool operator!=(int first_argument, Interval second_argument) {
        return first_argument != second_argument.value().lower() ||
            first_argument != second_argument.value().upper();
    }
    inline bool operator!=(Interval first_argument, float second_argument) {
        return first_argument.value().lower() != second_argument ||
            first_argument.value().upper() != second_argument;
    }

    inline bool operator!=(float first_argument, Interval second_argument) {
        return first_argument != second_argument.value().lower() ||
            first_argument != second_argument.value().upper();
    }
    inline bool operator!=(Interval first_argument, double second_argument) {
        return first_argument.value().lower() != second_argument ||
            first_argument.value().upper() != second_argument;
    }

    inline bool operator!=(double first_argument, Interval second_argument) {
        return first_argument != second_argument.value().lower() ||
            first_argument != second_argument.value().upper();
    }

    inline bool operator<(Double first_argument, Double second_argument) {
        return first_argument.value() < second_argument.value();
    }

    inline bool operator<(Double first_argument, Interval second_argument) {
        return first_argument.value() == second_argument.value().lower() ?
            first_argument.value() < second_argument.value().upper() :
            first_argument.value() < second_argument.value().lower();
    }

    inline bool operator<(Double first_argument, int second_argument) {
        return first_argument.value() < second_argument;
    }

    inline bool operator<(int first_argument, Double second_argument) {
        return first_argument < second_argument.value();
    }
    inline bool operator<(Double first_argument, float second_argument) {
        return first_argument.value() < second_argument;
    }

    inline bool operator<(float first_argument, Double second_argument) {
        return first_argument < second_argument.value();
    }
    inline bool operator<(Double first_argument, double second_argument) {
        return first_argument.value() < second_argument;
    }

    inline bool operator<(double first_argument, Double second_argument) {
        return first_argument < second_argument.value();
    }

    inline bool operator<(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() == second_argument.value().lower() ?
            first_argument.value().upper() < second_argument.value().upper() :
            first_argument.value().lower() < second_argument.value().lower();
    }

    inline bool operator<(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() == second_argument.value() ?
            first_argument.value().upper() < second_argument.value() :
            first_argument.value().lower() < second_argument.value();
    }

    inline bool operator<(Interval first_argument, int second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() < second_argument :
            first_argument.value().lower() < second_argument;
    }

    inline bool operator<(int first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument < second_argument.value().upper() :
            first_argument < second_argument.value().lower();
    }
    inline bool operator<(Interval first_argument, float second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() < second_argument :
            first_argument.value().lower() < second_argument;
    }

    inline bool operator<(float first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument < second_argument.value().upper() :
            first_argument < second_argument.value().lower();
    }
    inline bool operator<(Interval first_argument, double second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() < second_argument :
            first_argument.value().lower() < second_argument;
    }

    inline bool operator<(double first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument < second_argument.value().upper() :
            first_argument < second_argument.value().lower();
    }

    inline bool operator>(Double first_argument, Double second_argument) {
        return first_argument.value() > second_argument.value();
    }

    inline bool operator>(Double first_argument, Interval second_argument) {
        return first_argument.value() == second_argument.value().lower() ?
            first_argument.value() > second_argument.value().upper() :
            first_argument.value() > second_argument.value().lower();
    }

    inline bool operator>(Double first_argument, int second_argument) {
        return first_argument.value() > second_argument;
    }

    inline bool operator>(int first_argument, Double second_argument) {
        return first_argument > second_argument.value();
    }
    inline bool operator>(Double first_argument, float second_argument) {
        return first_argument.value() > second_argument;
    }

    inline bool operator>(float first_argument, Double second_argument) {
        return first_argument > second_argument.value();
    }
    inline bool operator>(Double first_argument, double second_argument) {
        return first_argument.value() > second_argument;
    }

    inline bool operator>(double first_argument, Double second_argument) {
        return first_argument > second_argument.value();
    }

    inline bool operator>(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() == second_argument.value().lower() ?
            first_argument.value().upper() > second_argument.value().upper() :
            first_argument.value().lower() > second_argument.value().lower();
    }

    inline bool operator>(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() == second_argument.value() ?
            first_argument.value().upper() > second_argument.value() :
            first_argument.value().lower() > second_argument.value();
    }

    inline bool operator>(Interval first_argument, int second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() > second_argument :
            first_argument.value().lower() > second_argument;
    }

    inline bool operator>(int first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument > second_argument.value().upper() :
            first_argument > second_argument.value().lower();
    }
    inline bool operator>(Interval first_argument, float second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() > second_argument :
            first_argument.value().lower() > second_argument;
    }

    inline bool operator>(float first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument > second_argument.value().upper() :
            first_argument > second_argument.value().lower();
    }
    inline bool operator>(Interval first_argument, double second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() > second_argument :
            first_argument.value().lower() > second_argument;
    }

    inline bool operator>(double first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument > second_argument.value().upper() :
            first_argument > second_argument.value().lower();
    }

    inline bool operator<=(Double first_argument, Double second_argument) {
        return first_argument.value() <= second_argument.value();
    }

    inline bool operator<=(Double first_argument, Interval second_argument) {
        return first_argument.value() == second_argument.value().lower() ?
            first_argument.value() <= second_argument.value().upper() :
            first_argument.value() <= second_argument.value().lower();
    }

    inline bool operator<=(Double first_argument, int second_argument) {
        return first_argument.value() <= second_argument;
    }

    inline bool operator<=(int first_argument, Double second_argument) {
        return first_argument <= second_argument.value();
    }
    inline bool operator<=(Double first_argument, float second_argument) {
        return first_argument.value() <= second_argument;
    }

    inline bool operator<=(float first_argument, Double second_argument) {
        return first_argument <= second_argument.value();
    }
    inline bool operator<=(Double first_argument, double second_argument) {
        return first_argument.value() <= second_argument;
    }

    inline bool operator<=(double first_argument, Double second_argument) {
        return first_argument <= second_argument.value();
    }

    inline bool operator<=(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() == second_argument.value().lower() ?
            first_argument.value().upper() <= second_argument.value().upper() :
            first_argument.value().lower() <= second_argument.value().lower();
    }

    inline bool operator<=(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() == second_argument.value() ?
            first_argument.value().upper() <= second_argument.value() :
            first_argument.value().lower() <= second_argument.value();
    }

    inline bool operator<=(Interval first_argument, int second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() <= second_argument :
            first_argument.value().lower() <= second_argument;
    }

    inline bool operator<=(int first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument <= second_argument.value().upper() :
            first_argument <= second_argument.value().lower();
    }
    inline bool operator<=(Interval first_argument, float second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() <= second_argument :
            first_argument.value().lower() <= second_argument;
    }

    inline bool operator<=(float first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument <= second_argument.value().upper() :
            first_argument <= second_argument.value().lower();
    }
    inline bool operator<=(Interval first_argument, double second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() <= second_argument :
            first_argument.value().lower() <= second_argument;
    }

    inline bool operator<=(double first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument <= second_argument.value().upper() :
            first_argument <= second_argument.value().lower();
    }

    inline bool operator>=(Double first_argument, Double second_argument) {
        return first_argument.value() >= second_argument.value();
    }

    inline bool operator>=(Double first_argument, Interval second_argument) {
        return first_argument.value() == second_argument.value().lower() ?
            first_argument.value() >= second_argument.value().upper() :
            first_argument.value() >= second_argument.value().lower();
    }

    inline bool operator>=(Double first_argument, int second_argument) {
        return first_argument.value() >= second_argument;
    }

    inline bool operator>=(int first_argument, Double second_argument) {
        return first_argument >= second_argument.value();
    }
    inline bool operator>=(Double first_argument, float second_argument) {
        return first_argument.value() >= second_argument;
    }

    inline bool operator>=(float first_argument, Double second_argument) {
        return first_argument >= second_argument.value();
    }
    inline bool operator>=(Double first_argument, double second_argument) {
        return first_argument.value() >= second_argument;
    }

    inline bool operator>=(double first_argument, Double second_argument) {
        return first_argument >= second_argument.value();
    }

    inline bool operator>=(Interval first_argument, Interval second_argument) {
        return first_argument.value().lower() == second_argument.value().lower() ?
            first_argument.value().upper() >= second_argument.value().upper() :
            first_argument.value().lower() >= second_argument.value().lower();
    }

    inline bool operator>=(Interval first_argument, Double second_argument) {
        return first_argument.value().lower() == second_argument.value() ?
            first_argument.value().upper() >= second_argument.value() :
            first_argument.value().lower() >= second_argument.value();
    }

    inline bool operator>=(Interval first_argument, int second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() >= second_argument :
            first_argument.value().lower() >= second_argument;
    }

    inline bool operator>=(int first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument >= second_argument.value().upper() :
            first_argument >= second_argument.value().lower();
    }
    inline bool operator>=(Interval first_argument, float second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() >= second_argument :
            first_argument.value().lower() >= second_argument;
    }

    inline bool operator>=(float first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument >= second_argument.value().upper() :
            first_argument >= second_argument.value().lower();
    }
    inline bool operator>=(Interval first_argument, double second_argument) {
        return first_argument.value().lower() == second_argument ?
            first_argument.value().upper() >= second_argument :
            first_argument.value().lower() >= second_argument;
    }

    inline bool operator>=(double first_argument, Interval second_argument) {
        return first_argument == second_argument.value().lower() ?
            first_argument >= second_argument.value().upper() :
            first_argument >= second_argument.value().lower();
    }

    inline Double operator-(Double argument) {return -argument.value();}

    inline Interval operator-(Interval argument) {return -argument.value();}

    inline Double operator+(Double first_argument, Double second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator+(Double first_argument, Interval second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Double operator+(Double first_argument, int second_argument) {
        return first_argument.value() + second_argument;
    }

    inline Double operator+(int first_argument, Double second_argument) {
        return first_argument + second_argument.value();
    }
    inline Double operator+(Double first_argument, float second_argument) {
        return first_argument.value() + second_argument;
    }

    inline Double operator+(float first_argument, Double second_argument) {
        return first_argument + second_argument.value();
    }
    inline Double operator+(Double first_argument, double second_argument) {
        return first_argument.value() + second_argument;
    }

    inline Double operator+(double first_argument, Double second_argument) {
        return first_argument + second_argument.value();
    }

    inline Interval operator+(Interval first_argument, Interval second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator+(Interval first_argument, Double second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator+(Interval first_argument, int second_argument) {
        return first_argument.value() + double(second_argument);
    }

    inline Interval operator+(int first_argument, Interval second_argument) {
        return double(first_argument) + second_argument.value();
    }
    inline Interval operator+(Interval first_argument, float second_argument) {
        return first_argument.value() + double(second_argument);
    }

    inline Interval operator+(float first_argument, Interval second_argument) {
        return double(first_argument) + second_argument.value();
    }
    inline Interval operator+(Interval first_argument, double second_argument) {
        return first_argument.value() + second_argument;
    }

    inline Interval operator+(double first_argument, Interval second_argument) {
        return first_argument + second_argument.value();
    }

    inline Double operator-(Double first_argument, Double second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator-(Double first_argument, Interval second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Double operator-(Double first_argument, int second_argument) {
        return first_argument.value() - second_argument;
    }

    inline Double operator-(int first_argument, Double second_argument) {
        return first_argument - second_argument.value();
    }
    inline Double operator-(Double first_argument, float second_argument) {
        return first_argument.value() - second_argument;
    }

    inline Double operator-(float first_argument, Double second_argument) {
        return first_argument - second_argument.value();
    }
    inline Double operator-(Double first_argument, double second_argument) {
        return first_argument.value() - second_argument;
    }

    inline Double operator-(double first_argument, Double second_argument) {
        return first_argument - second_argument.value();
    }

    inline Interval operator-(Interval first_argument, Interval second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator-(Interval first_argument, Double second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator-(Interval first_argument, int second_argument) {
        return first_argument.value() - double(second_argument);
    }

    inline Interval operator-(int first_argument, Interval second_argument) {
        return double(first_argument) - second_argument.value();
    }
    inline Interval operator-(Interval first_argument, float second_argument) {
        return first_argument.value() - double(second_argument);
    }

    inline Interval operator-(float first_argument, Interval second_argument) {
        return double(first_argument) - second_argument.value();
    }
    inline Interval operator-(Interval first_argument, double second_argument) {
        return first_argument.value() - second_argument;
    }

    inline Interval operator-(double first_argument, Interval second_argument) {
        return first_argument - second_argument.value();
    }

    inline Double operator*(Double first_argument, Double second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator*(Double first_argument, Interval second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Double operator*(Double first_argument, int second_argument) {
        return first_argument.value() * second_argument;
    }

    inline Double operator*(int first_argument, Double second_argument) {
        return first_argument * second_argument.value();
    }
    inline Double operator*(Double first_argument, float second_argument) {
        return first_argument.value() * second_argument;
    }

    inline Double operator*(float first_argument, Double second_argument) {
        return first_argument * second_argument.value();
    }
    inline Double operator*(Double first_argument, double second_argument) {
        return first_argument.value() * second_argument;
    }

    inline Double operator*(double first_argument, Double second_argument) {
        return first_argument * second_argument.value();
    }

    inline Interval operator*(Interval first_argument, Interval second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator*(Interval first_argument, Double second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator*(Interval first_argument, int second_argument) {
        return first_argument.value() * double(second_argument);
    }

    inline Interval operator*(int first_argument, Interval second_argument) {
        return double(first_argument) * second_argument.value();
    }
    inline Interval operator*(Interval first_argument, float second_argument) {
        return first_argument.value() * double(second_argument);
    }

    inline Interval operator*(float first_argument, Interval second_argument) {
        return double(first_argument) * second_argument.value();
    }
    inline Interval operator*(Interval first_argument, double second_argument) {
        return first_argument.value() * second_argument;
    }

    inline Interval operator*(double first_argument, Interval second_argument) {
        return first_argument * second_argument.value();
    }

    inline Double operator/(Double first_argument, Double second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval operator/(Double first_argument, Interval second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Double operator/(Double first_argument, int second_argument) {
        return first_argument.value() / second_argument;
    }

    inline Double operator/(int first_argument, Double second_argument) {
        return first_argument / second_argument.value();
    }
    inline Double operator/(Double first_argument, float second_argument) {
        return first_argument.value() / second_argument;
    }

    inline Double operator/(float first_argument, Double second_argument) {
        return first_argument / second_argument.value();
    }
    inline Double operator/(Double first_argument, double second_argument) {
        return first_argument.value() / second_argument;
    }

    inline Double operator/(double first_argument, Double second_argument) {
        return first_argument / second_argument.value();
    }

    inline Interval operator/(Interval first_argument, Interval second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval operator/(Interval first_argument, Double second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval operator/(Interval first_argument, int second_argument) {
        return first_argument.value() / double(second_argument);
    }

    inline Interval operator/(int first_argument, Interval second_argument) {
        return double(first_argument) / second_argument.value();
    }
    inline Interval operator/(Interval first_argument, float second_argument) {
        return first_argument.value() / double(second_argument);
    }

    inline Interval operator/(float first_argument, Interval second_argument) {
        return double(first_argument) / second_argument.value();
    }
    inline Interval operator/(Interval first_argument, double second_argument) {
        return first_argument.value() / second_argument;
    }

    inline Interval operator/(double first_argument, Interval second_argument) {
        return first_argument / second_argument.value();
    }

    inline Double min(Double first_argument, Double second_argument) {
        return min(first_argument.value(), second_argument.value());
    }

    inline Interval min(Double first_argument, Interval second_argument) {
        return min(first_argument.value(), second_argument.value());
    }

    inline Double min(Double first_argument, int second_argument) {
        return min(first_argument.value(), double(second_argument));
    }

    inline Double min(int first_argument, Double second_argument) {
        return min(double(first_argument), second_argument.value());
    }
    inline Double min(Double first_argument, float second_argument) {
        return min(first_argument.value(), double(second_argument));
    }

    inline Double min(float first_argument, Double second_argument) {
        return min(double(first_argument), second_argument.value());
    }
    inline Double min(Double first_argument, double second_argument) {
        return min(first_argument.value(), second_argument);
    }

    inline Double min(double first_argument, Double second_argument) {
        return min(first_argument, second_argument.value());
    }

    inline Interval min(Interval first_argument, Interval second_argument) {
        return min(first_argument.value(), second_argument.value());
    }

    inline Interval min(Interval first_argument, Double second_argument) {
        return min(first_argument.value(), second_argument.value());
    }

    inline Interval min(Interval first_argument, int second_argument) {
        return min(first_argument.value(), double(second_argument));
    }

    inline Interval min(int first_argument, Interval second_argument) {
        return min(double(first_argument), second_argument.value());
    }
    inline Interval min(Interval first_argument, float second_argument) {
        return min(first_argument.value(), double(second_argument));
    }

    inline Interval min(float first_argument, Interval second_argument) {
        return min(double(first_argument), second_argument.value());
    }
    inline Interval min(Interval first_argument, double second_argument) {
        return min(first_argument.value(), second_argument);
    }

    inline Interval min(double first_argument, Interval second_argument) {
        return min(first_argument, second_argument.value());
    }

    inline Double max(Double first_argument, Double second_argument) {
        return max(first_argument.value(), second_argument.value());
    }

    inline Interval max(Double first_argument, Interval second_argument) {
        return max(first_argument.value(), second_argument.value());
    }

    inline Double max(Double first_argument, int second_argument) {
        return max(first_argument.value(), double(second_argument));
    }

    inline Double max(int first_argument, Double second_argument) {
        return max(double(first_argument), second_argument.value());
    }
    inline Double max(Double first_argument, float second_argument) {
        return max(first_argument.value(), double(second_argument));
    }

    inline Double max(float first_argument, Double second_argument) {
        return max(double(first_argument), second_argument.value());
    }
    inline Double max(Double first_argument, double second_argument) {
        return max(first_argument.value(), second_argument);
    }

    inline Double max(double first_argument, Double second_argument) {
        return max(first_argument, second_argument.value());
    }

    inline Interval max(Interval first_argument, Interval second_argument) {
        return max(first_argument.value(), second_argument.value());
    }

    inline Interval max(Interval first_argument, Double second_argument) {
        return max(first_argument.value(), second_argument.value());
    }

    inline Interval max(Interval first_argument, int second_argument) {
        return max(first_argument.value(), double(second_argument));
    }

    inline Interval max(int first_argument, Interval second_argument) {
        return max(double(first_argument), second_argument.value());
    }
    inline Interval max(Interval first_argument, float second_argument) {
        return max(first_argument.value(), double(second_argument));
    }

    inline Interval max(float first_argument, Interval second_argument) {
        return max(double(first_argument), second_argument.value());
    }
    inline Interval max(Interval first_argument, double second_argument) {
        return max(first_argument.value(), second_argument);
    }

    inline Interval max(double first_argument, Interval second_argument) {
        return max(first_argument, second_argument.value());
    }
}

#endif
