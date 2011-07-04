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

#include "check.hpp"

namespace OpenSolid
{
    void checkNonZeroValue(Double value, const std::string& caller) {
        if (value.isZero()) {
            Error error("NonZeroValue", caller);
            error.set("value", value);
            throw error;
        }
    }
    
    void checkSameSize(int first_size, int second_size, const std::string& caller) {
        if (first_size != second_size) {
            Error error("SameSize", caller);
            error.set("first_size", first_size);
            error.set("second_size", second_size);
            throw error;
        }
    }
    
    void checkSameDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    ) {
        if (first_dimensions != second_dimensions) {
            Error error("SameDimensions", caller);
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void checkValidProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    ) {
        if (first_dimensions != 1u && second_dimensions != 1u) {
            Error error("ValidProductDimensions", caller);
            error.set("first_dimensions", first_dimensions);
            error.set("second_dimensions", second_dimensions);
            throw error;
        }
    }
    
    void checkComponentIndexInRange(
        int component_index,
        int size,
        const std::string& caller
    ) {
        if (component_index < -size || component_index >= size) {
            Error error("ComponentIndexInRange", caller);
            error.set("component_index", component_index);
            error.set("size", size);
            std::cout << error << std::endl;
            throw error;
        }
    }
    
    void checkComponentBlockInRange(
        int block_start,
        int block_size,
        int size,
        const std::string& caller
    ) {
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
            Error error("ComponentBlockInRange", caller);
            error.set("block_start", block_start);
            error.set("block_size", block_size);
            error.set("size", size);
            throw error;
        }
    }
    
    void checkNoMatrixIndexStep(
        boost::python::slice indices,
        const std::string& caller
    ) {if (indices.step() != boost::python::object()) {throw Error("NoMatrixIndexStep", caller);}}
    
    void checkConstantFunction(
        const Function& function,
        const std::string& caller
    ) {if (!function.isA<ConstantFunction>()) {throw Error("ConstantFunction", caller);}}
    
    void checkScalarFunction(
        const Function& function,
        const std::string& caller
    ) {
        if (function.dimensions() > 1) {
            Error error("ScalarFunction", caller);
            error.set("dimensions", function.dimensions());
            throw error;
        }
    }
    
    void checkParameterIndexInRange(
        int index,
        const Function& function,
        const std::string& caller
    ) {
        if (index < 0 || index > function.parameters()) {
            Error error("ParameterIndexInRange", caller);
            error.set("index", index);
            error.set("parameters", function.parameters());
            throw error;
        }
    }
    
    void checkConsistentFunctionParameters(
        const Function& first_function,
        const Function& second_function,
        const std::string& caller
    ) {
        if (
            !first_function.isA<ConstantFunction>() &&
            !second_function.isA<ConstantFunction>() &&
            first_function.parameters() != second_function.parameters()
        ) {
            Error error("ConsistentFunctionParameters", caller);
            error.set("first_parameters", first_function.parameters());
            error.set("second_parameters", second_function.parameters());
            throw error;
        }
    }
}
