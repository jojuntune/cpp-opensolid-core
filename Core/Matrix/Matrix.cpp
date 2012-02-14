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

#include <OpenSolid/Core/opensolid.pb.h>
#include <OpenSolid/Core/Matrix/Matrix.hpp>

namespace OpenSolid
{
    std::string Serialization<MatrixXd>::serialized(const MatrixXd& argument) const {
        SerializedMatrixXd temp;
        temp.set_rows(argument.rows());
        temp.set_cols(argument.cols());
        for (int i = 0; i < argument.size(); ++i) {temp.add_data(argument(i));}
        return temp.SerializeAsString();
    }

    MatrixXd Serialization<MatrixXd>::deserialized(const std::string& argument) const {
        SerializedMatrixXd temp;
        temp.ParseFromString(argument);
        MatrixXd result(temp.rows(), temp.cols());
        for (int i = 0; i < result.size(); ++i) {result(i) = temp.data(i);}
        return std::move(result);
    }

    std::string Serialization<MatrixXI>::serialized(const MatrixXI& argument) const {
        Serialization<Interval> interval_serializer;
        SerializedMatrixXI temp;
        temp.set_rows(argument.rows());
        temp.set_cols(argument.cols());
        for (int i = 0; i < argument.size(); ++i) {
            temp.add_data(interval_serializer.serialized(argument(i)));
       }
        return temp.SerializeAsString();
    }

    MatrixXI Serialization<MatrixXI>::deserialized(const std::string& argument) const {
        Serialization<Interval> interval_serializer;
        SerializedMatrixXI temp;
        temp.ParseFromString(argument);
        MatrixXI result(temp.rows(), temp.cols());
        for (int i = 0; i < result.size(); ++i) {
            result(i) = interval_serializer.deserialized(temp.data(i));
        }
        return std::move(result);
    }
}
