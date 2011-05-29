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

#include <cmath>

#include <OpenSolid/Common/Error.hpp>

#include "check.hpp"

namespace OpenSolid
{
    void checkNonZeroValue(double value, double tolerance, const std::string& caller) {
        if (std::abs(value) < tolerance) {
            Error error("NonZeroValue", caller);
            error.set("value", value).set("tolerance", tolerance);
            throw error;
        }
    }
    
    void checkScalarValue(int rows, int cols, const std::string& caller) {
        if (rows != 1 || cols != 1) {
            throw Error("ScalarValue", caller).set("rows", rows).set("cols", cols);
        }
    }
    
    void checkVectorValue(int cols, const std::string& caller) {
        if (cols != 1) {throw Error("VectorValue", caller).set("cols", cols);}
    }
    
    void checkRowVectorValue(int rows, const std::string& caller) {
        if (rows != 1) {throw Error("RowVectorValue", caller).set("rows", rows);}
    }
    
    void checkVectorOrRowVectorValue(int rows, int cols, const std::string& caller) {
        if (rows != 1 && cols != 1) {
            Error error("VectorOrRowVectorValue", caller);
            error.set("rows", rows);
            error.set("cols", cols);
            throw error;
        }
    }
    
    void checkSameDimensions(int first_size, int second_size, const std::string& caller) {
        if (first_size != first_size) {
            Error error("SameDimension", caller);
            error.set("first_size", first_size).set("second_size", second_size);
            throw error;
        }
    }
    
    void checkSameSize(
        int first_rows,
        int first_cols,
        int second_rows,
        int second_cols,
        const std::string& caller
    ) {
        if (first_rows != second_rows || first_cols != second_cols) {
            Error error("SameSize", caller);
            error.set("first_rows", first_rows).set("first_cols", first_cols);
            error.set("second_rows", second_rows).set("second_cols", second_cols);
            throw error;
        }
    }
    
    void checkSquareMatrix(int rows, int cols, const std::string& caller) {
        if (rows != cols) {
            Error error("SquareMatrix", caller);
            error.set("rows", rows).set("cols", cols);
            throw error;
        }
    }
    
    void checkSpecificMatrixSize(
        int rows,
        int cols,
        int expected_rows,
        int expected_cols,
        const std::string& caller
    ) {
        if (rows != expected_rows || cols != expected_cols) {
            Error error("SpecificMatrixSize", caller);
            error.set("rows", rows).set("cols", cols);
            error.set("expected_rows", expected_rows).set("expected_cols", expected_cols);
            throw error;
        }
    }
    
    void checkValidProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    ) {
        if (first_dimensions != 1 && second_dimensions != 1) {
            Error error("ProductDimensions", caller);
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void checkValidCrossProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    ) {
        if (first_dimensions != 3 || second_dimensions != 3) {
            Error error("CrossProductDimensions", caller);
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void checkValidMatrixProductDimensions(
        int first_cols,
        int second_rows,
        const std::string& caller
    ) {
        if (first_cols != second_rows) {
            Error error("MatrixProductDimensions", caller);
            error.set("first_cols", first_cols).set("second_rows", second_rows);
            throw error;
        }
    }
    
    void checkComponentIndexInRange(int component_index, int size, const std::string& caller) {
        if (component_index < -size || component_index >= size) {
            Error error("ComponentIndexInRange", caller);
            error.set("component_index", component_index).set("size", size);
            throw error;
        }
    }
    
    void checkComponentBlockInRange(
        int block_start,
        int block_size,
        int size, const
        std::string& caller
    ) {
        bool valid;
        if (block_start < 0) {
            valid = block_size > 0 && block_start >= -size && block_start + block_size <= 0;
        } else {
            valid = block_size > 0 && block_start + block_size <= size;
        }
        if (!valid) {
            Error error("ComponentBlockInRange", caller);
            error.set("block_start", block_start);
            error.set("block_size", block_size);
            error.set("size", size);
            throw error;
        }
    }
    
    void checkNoMatrixIndexStep(bool step_is_none, const std::string& caller) {
        if (!step_is_none) {throw Error("NoMatrixIndexStep", caller);}
    }
    
    void checkCorrectNumberOfCoefficients(
        int coefficients,
        int expected,
        const std::string& caller
    ) {
        if (coefficients != expected) {
            Error error("CorrectNumberOfCoefficients", caller);
            error.set("coefficients", coefficients).set("expected", expected);
            throw error;
        }
    }
}
