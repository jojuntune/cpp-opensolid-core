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

#include "config.hpp"

#include "ReferenceCounted.hpp"
#include "Matrix.hpp"

namespace opensolid
{
    class Function;
    
    class FunctionImplementation : public ReferenceCounted<FunctionImplementation>
    {
    public:
        virtual ~FunctionImplementation();
        
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameter_bounds, MapXI& results) const;
        
        virtual int parameters() const = 0;
        virtual int dimensions() const = 0;
        
        virtual void getValues(const MapXcd& parameter_values, MapXd& results) const = 0;
        virtual void getBounds(const MapXcI& parameter_bounds, MapXI& results) const = 0;
        
        virtual void getDerivative(int index, Function& result) const = 0;

        virtual void getComponents(int index, int num, Function& result) const;
        virtual void getComposition(const Function& inner, Function& result) const;
        
        virtual void getTransformed(
            const MatrixXd& matrix,
            const VectorXd& vector,
            Function& result
        ) const;
        
        virtual void getNorm(Function& result) const;
        virtual void getNormalized(Function& result) const;
        virtual void getSquaredNorm(Function& result) const;
        virtual void getTangent(Function& result) const;
        virtual void getCurvature(Function& result) const;
        virtual void getNormal(Function& result) const;
        virtual void getBinormal(Function& result) const;
        
        virtual void debug(std::ostream& stream, int indent) const = 0;
    };
}
