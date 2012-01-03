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

#include <OpenSolid/Python/check.hpp>
#include <OpenSolid/Scalar/Comparison.hpp>

namespace OpenSolid
{
    void Check<2>::NonZero(double value) {
        if (value == Zero()) {
            Error error((Check()));
            error.set("value", value);
            throw error;
        }
    }
    
    void Check<3>::EqualSizes(int first_size, int second_size) {
        if (first_size != second_size) {
            Error error((Check()));
            error.set("first_size", first_size);
            error.set("second_size", second_size);
            throw error;
        }
    }
    
    void Check<4>::EqualDimensions(int first_dimensions, int second_dimensions) {
        if (first_dimensions != second_dimensions) {
            Error error((Check()));
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void Check<12>::ValidProductDimensions(int first_dimensions, int second_dimensions) {
        if (first_dimensions != 1 && second_dimensions != 1) {
            Error error((Check()));
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void Check<14>::ComponentIndexInRange(int component_index, int size) {
        if (component_index < -size || component_index >= size) {
            Error error((Check()));
            error.set("component_index", component_index);
            error.set("size", size);
            throw error;
        }
    }
    
    void Check<15>::ComponentBlockInRange(int block_start, int block_size, int size) {
        bool valid;
        if (block_start < 0) {
            valid =
                block_size > 0 &&
                block_start >= -int(size) &&
                block_start + block_size <= 0;
        } else {
            valid = block_size > 0 && block_start + block_size <= size;
        }
        if (!valid) {
            Error error((Check()));
            error.set("block_start", block_start);
            error.set("block_size", block_size);
            error.set("size", size);
            throw error;
        }
    }
    
    void Check<16>::NoMatrixIndexStep(const boost::python::slice& indices) {
        if (indices.step() != boost::python::object()) {throw Error((Check()));}
    }
    
    void Check<17>::ConstantFunction(const Function& function) {
        if (!function.isConstant()) {throw Error((Check()));}
    }
    
    void Check<18>::ScalarFunction(const Function& function) {
        if (function.dimensions() > 1) {
            Error error((Check()));
            error.set("dimensions", function.dimensions());
            throw error;
        }
    }
    
    void Check<19>::ParameterIndexInRange(int index, const Function& function) {
        if (index < 0 || index > function.parameters()) {
            Error error((Check()));
            error.set("index", index);
            error.set("parameters", function.parameters());
            throw error;
        }
    }
    
    void Check<20>::ConsistentFunctionParameters(
        const Function& first_function,
        const Function& second_function
    ) {
        if (
            !first_function.isConstant() &&
            !second_function.isConstant() &&
            first_function.parameters() != second_function.parameters()
        ) {
            Error error((Check()));
            error.set("first_parameters", first_function.parameters());
            error.set("second_parameters", second_function.parameters());
            throw error;
        }
    }
}
