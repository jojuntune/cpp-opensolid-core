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
 **************************************************************************/

#include "EllipticalFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    EllipticalFunction::EllipticalFunction(const DatumXd& datum, const VectorXb& convention) :
        _datum(datum), _convention(convention) {
        assert(convention.size() == _datum.numAxes() - 1);
    }
    
    int EllipticalFunction::numParameters() const {
        return datum().numAxes() - 1;
    }
    
    int EllipticalFunction::numDimensions() const {
        return datum().numDimensions();
    }
    
    void EllipticalFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd local = MatrixXd::Ones(numParameters() + 1, parameter_values.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameter_values.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    sin(parameter_values.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameter_values.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    cos(parameter_values.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = datum() * local;
    }
    
    void EllipticalFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI local = MatrixXI::Ones(numParameters() + 1, parameter_bounds.cols());
        for (int i = 0; i < numParameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameter_bounds.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    sin(parameter_bounds.row(i).array()).replicate(numParameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameter_bounds.row(i).array());
                local.bottomRows(numParameters() - i).array() *=
                    cos(parameter_bounds.row(i).array()).replicate(numParameters() - i, 1);
            }
        }
        results = datum() * local;
    }

    void EllipticalFunction::getDerivative(int index, Function& result) const {
        VectorXd new_origin = VectorXd::Zero(numDimensions());
        MatrixXd new_basis = datum().basisMatrix();
        VectorXb new_convention = convention();
        new_convention(index) = !new_convention(index);
        if (convention()(index)) {
            new_basis.col(index) = -new_basis.col(index);
        } else {
            int num_flipped = numParameters() - index;
            new_basis.rightCols(num_flipped) = -new_basis.rightCols(num_flipped);
        }
        result = new EllipticalFunction(DatumXd(new_origin, new_basis), new_convention);
    }
    
    void EllipticalFunction::getTransformed(
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {
        result = new EllipticalFunction(matrix * datum() + vector, convention());
    }
    
    void EllipticalFunction::debug(std::ostream& stream, int indent) const {
        stream << "EllipticalFunction" << std::endl;
    }
}
