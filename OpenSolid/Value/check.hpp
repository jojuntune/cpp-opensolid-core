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

#ifndef OPENSOLID__VALUE__CHECK_HPP
#define OPENSOLID__VALUE__CHECK_HPP

#include <OpenSolid/config.hpp>

#include <string>

namespace opensolid
{
    OPENSOLID_EXPORT void checkNonZeroValue(
        double value,
        double tolerance,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkScalarValue(int rows, int cols, const std::string& caller);
    
    OPENSOLID_EXPORT void checkVectorValue(int cols, const std::string& caller);
    
    OPENSOLID_EXPORT void checkRowVectorValue(int rows, const std::string& caller);
    
    OPENSOLID_EXPORT void checkVectorOrRowVectorValue(
        int rows,
        int cols,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkSameDimensions(
        int first_size,
        int second_size,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkSameSize(
        int first_rows,
        int first_cols,
        int second_rows,
        int second_cols,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkSquareMatrix(int rows, int cols, const std::string& caller);
    
    OPENSOLID_EXPORT void checkSpecificMatrixSize(
        int rows,
        int cols,
        int expected_rows,
        int expected_cols,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkValidProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkValidMatrixProductDimensions(
        int first_cols,
        int second_rows,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkValidCrossProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkComponentIndexInRange(
        int component_index,
        int size, const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkComponentBlockInRange(
        int block_start,
        int block_size,
        int size,
        const std::string& caller
    );
    
    OPENSOLID_EXPORT void checkNoMatrixIndexStep(bool step_is_none, const std::string& caller);
    
    OPENSOLID_EXPORT void checkCorrectNumberOfCoefficients(
        int coefficients,
        int expected,
        const std::string& caller
    );
}

#endif
