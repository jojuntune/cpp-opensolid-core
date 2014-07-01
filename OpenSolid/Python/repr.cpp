/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Python/repr.hpp>

#include <boost/lexical_cast.hpp>

#include <sstream>

namespace opensolid
{
    std::string
    __repr__(bool argument) {
        return argument ? "True" : "False";
    }

    std::string
    __repr__(int argument) {
        return boost::lexical_cast<std::string>(argument);
    }

    std::string
    __repr__(double argument) {
        return boost::lexical_cast<std::string>(argument);
    }

    std::string
    __repr__(Interval argument) {
        std::stringstream stream;
        stream << "Interval(" << __repr__(argument.lowerBound());
        if (argument.upperBound() != argument.lowerBound()) {
            stream << "," << __repr__(argument.upperBound());
        }
        stream << ")";
        return stream.str();
    }

    std::string
    __repr__(Zero argument) {
        std::stringstream stream;
        stream << "Zero(" << __repr__(argument.precision()) << ")";
        return stream.str();
    }

    template <class TMatrix, char cTypeCharacter>
    std::string
    __repr__(const TMatrix& argument) {
        std::stringstream stream;
        int rows = argument.rows();
        int cols = argument.cols();
        if (rows == 1 || cols == 1) {
            int size = cols == 1 ? rows : cols;
            if (rows == 1) {stream << "Row";}
            stream << "Vector";
            bool dynamic = size > 3;
            if (dynamic) {
                stream << 'X';
            } else {
                stream << size;
            }
            stream << cTypeCharacter;
            stream << '(';
            if (dynamic) {stream << '[';}
            for (int i = 0; i < size; ++i) {
                stream << __repr__(argument(i));
                if (i < size - 1) {stream << ", ";}
            }
            if (dynamic) {stream << ']';}
            stream << ')';
        } else {
            stream << "Matrix";
            bool dynamic = rows != cols || cols > 3;
            if (dynamic) {
                stream << 'X';
            } else {
                stream << cols;
            }
            stream << cTypeCharacter;
            stream << "([";
            for (int j = 0; j < cols; ++j) {
                stream << '[';
                for (int i = 0; i < rows; ++i) {
                    stream << __repr__(argument(i, j));
                    if (i < rows - 1) {stream << ", ";}
                }
                stream << ']';
                if (j < cols - 1) {stream << ", ";}
            }
            stream << "])";
        }
        return stream.str();
    }

    std::string
    __repr__(const MatrixXd& argument) {
        return __repr__<MatrixXd, 'd'>(argument);
    }

    std::string
    __repr__(const MatrixXI& argument) {
        return __repr__<MatrixXI, 'I'>(argument);
    }
}
