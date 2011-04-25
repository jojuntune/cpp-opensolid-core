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

#include "../Function.hpp"
#include "EllipticalFunction.hpp"

namespace opensolid
{
    EllipticalFunction::EllipticalFunction(
        const VectorXd& point,
        const MatrixXd& vectors,
        const VectorXb& convention
    ) : _point(point), _vectors(vectors), _convention(convention) {
        assert(point.rows() == _vectors.rows());
        assert(convention.size() == vectors.cols() - 1);
    }
    
    int EllipticalFunction::parameters() const {return vectors().cols() - 1;}
    
    int EllipticalFunction::dimensions() const {return point().size();}
    
    void EllipticalFunction::getValues(const MapXd& parameter_values, MapXd& results) const {
        MatrixXd temp = MatrixXd::Ones(parameters() + 1, parameter_values.cols());
        for (int i = 0; i < parameters(); ++i) {
            if (convention()(i)) {
                temp.row(i).array() *= cos(parameter_values.row(i).array());
                temp.bottomRows(parameters() - i).array() *=
                    sin(parameter_values.row(i).array()).replicate(parameters() - i, 1);
            } else {
                temp.row(i).array() *= sin(parameter_values.row(i).array());
                temp.bottomRows(parameters() - i).array() *=
                    cos(parameter_values.row(i).array()).replicate(parameters() - i, 1);
            }
        }
        results = (vectors() * temp).colwise() + point();
    }
    
    void EllipticalFunction::getBounds(const MapXI& parameter_bounds, MapXI& results) const {
        MatrixXI temp = MatrixXI::Ones(parameters() + 1, parameter_bounds.cols());
        for (int i = 0; i < parameters(); ++i) {
            if (convention()(i)) {
                temp.row(i).array() *= cos(parameter_bounds.row(i).array());
                temp.bottomRows(parameters() - i).array() *=
                    sin(parameter_bounds.row(i).array()).replicate(parameters() - i, 1);
            } else {
                temp.row(i).array() *= sin(parameter_bounds.row(i).array());
                temp.bottomRows(parameters() - i).array() *=
                    cos(parameter_bounds.row(i).array()).replicate(parameters() - i, 1);
            }
        }
        results = (vectors().cast<Interval>() * temp).colwise() + point().cast<Interval>();
    }

    void EllipticalFunction::getDerivative(int index, Function& result) const {
        VectorXd new_point = VectorXd::Zero(dimensions());
        MatrixXd new_vectors = vectors();
        VectorXb new_convention = convention();
        new_convention(index) = !new_convention(index);
        if (convention()(index)) {
            new_vectors.col(index) = -new_vectors.col(index);
        } else {
            int num_flipped = parameters() - index;
            new_vectors.rightCols(num_flipped) = -new_vectors.rightCols(num_flipped);
        }
        result = new EllipticalFunction(new_point, new_vectors, new_convention);
    }
    
    void EllipticalFunction::debug(std::ostream& stream, int indent) const {
        stream << "EllipticalFunction" << std::endl;
    }
}
