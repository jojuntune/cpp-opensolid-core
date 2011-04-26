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

#include <OpenSolid/Common/Error.hpp>

#include "check.hpp"

namespace opensolid
{
    void checkConstantFunction(int parameters, const std::string& caller) {
        if (parameters != 0) {
            throw Error("ConstantFunction", caller).set("parameters", parameters);
        }
    }
    
    void checkScalarFunction(int dimensions, const std::string& caller) {
        if (dimensions != 1) {throw Error("ScalarFunction", caller).set("dimensions", dimensions);}
    }
    
    void checkParameterIndexInRange(int index, int parameters, const std::string& caller) {
        if (parameters != 0 && (index < 0 || index >= parameters)) {
            Error error("ParameterIndexInRange", caller);
            error.set("index", index).set("parameters", parameters);
            throw error;
        }
    }
        
    void checkConsistentFunctionParameters(
        int first_parameters,
        int second_parameters,
        const std::string& caller
    ) {
        if (
            first_parameters != second_parameters &&
            first_parameters != 0 &&
            second_parameters != 0
        ) {
            Error error("ConsistentFunctionParameters", caller);
            error.set("first_parameters", first_parameters);
            error.set("second_parameters", second_parameters);
            throw error;
        }
    }
}
