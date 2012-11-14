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

#include "repr.hpp"

#include <boost/lexical_cast.hpp>

#include <sstream>

namespace opensolid
{
    std::string __repr__(bool argument) {
        return argument ? "True" : "False";
    }

    std::string __repr__(int argument) {
        return boost::lexical_cast<std::string>(argument);
    }

    std::string __repr__(double argument) {
        return boost::lexical_cast<std::string>(argument);
    }

    std::string __repr__(const Interval& argument) {
        std::stringstream stream;
        stream << "Interval(" << __repr__(argument.lower());
        if (argument.upper() != argument.lower()) {
            stream << "," << __repr__(argument.upper());
        }
        stream << ")";
        return stream.str();
    }

    template <class MatrixType, char type_character_>
    std::string __repr__(const MatrixType& argument) {
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
            stream << type_character_;
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
            stream << type_character_;
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

    std::string __repr__(const MatrixXd& argument) {
        return __repr__<MatrixXd, 'd'>(argument);
    }

    std::string __repr__(const MatrixXI& argument) {
        return __repr__<MatrixXI, 'I'>(argument);
    }
}
