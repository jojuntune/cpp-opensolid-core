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

#include <OpenSolid/Datum/CoordinateSystem.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Function/FunctionImplementation/EllipticalFunction.hpp>

namespace OpenSolid
{
    EllipticalFunction::EllipticalFunction(const DatumXd& datum, const VectorXb& convention) :
        _datum(datum), _convention(convention) {
        assert(convention.size() == _datum.axes() - 1);
    }
    
    int EllipticalFunction::parameters() const {return datum().axes() - 1;}
    
    int EllipticalFunction::dimensions() const {return datum().dimensions();}
    
    void EllipticalFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd local = MatrixXd::Ones(parameters() + 1, parameter_values.cols());
        for (int i = 0; i < parameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameter_values.row(i).array());
                local.bottomRows(parameters() - i).array() *=
                    sin(parameter_values.row(i).array()).replicate(parameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameter_values.row(i).array());
                local.bottomRows(parameters() - i).array() *=
                    cos(parameter_values.row(i).array()).replicate(parameters() - i, 1);
            }
        }
        results = local * datum();
    }
    
    void EllipticalFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI local = MatrixXI::Ones(parameters() + 1, parameter_bounds.cols());
        for (int i = 0; i < parameters(); ++i) {
            if (convention()(i)) {
                local.row(i).array() *= cos(parameter_bounds.row(i).array());
                local.bottomRows(parameters() - i).array() *=
                    sin(parameter_bounds.row(i).array()).replicate(parameters() - i, 1);
            } else {
                local.row(i).array() *= sin(parameter_bounds.row(i).array());
                local.bottomRows(parameters() - i).array() *=
                    cos(parameter_bounds.row(i).array()).replicate(parameters() - i, 1);
            }
        }
        results = local * datum();
    }

    void EllipticalFunction::getDerivative(int index, Function& result) const {
        VectorXd new_origin = VectorXd::Zero(dimensions());
        MatrixXd new_basis = datum().basis();
        VectorXb new_convention = convention();
        new_convention(index) = !new_convention(index);
        if (convention()(index)) {
            new_basis.col(index) = -new_basis.col(index);
        } else {
            int num_flipped = parameters() - index;
            new_basis.rightCols(num_flipped) = -new_basis.rightCols(num_flipped);
        }
        result = new EllipticalFunction(CoordinateSystemXd(new_origin, new_basis), new_convention);
    }
    
    void EllipticalFunction::getTransformed(
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {result = new EllipticalFunction(datum().transformed(matrix, vector), convention());}
    
    void EllipticalFunction::debug(std::ostream& stream, int indent) const {
        stream << "EllipticalFunction" << std::endl;
    }
}
