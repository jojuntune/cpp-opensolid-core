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

#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Matrix/SerializedMatrix.pb.h>

namespace opensolid
{
    std::string Conversion<MatrixXd, std::string>::operator()(const MatrixXd& argument) const {
        SerializedMatrixXd temp;
        temp.set_rows(argument.rows());
        temp.set_cols(argument.cols());
        for (int i = 0; i < argument.size(); ++i) {temp.add_data(argument(i));}
        return temp.SerializeAsString();
    }

    MatrixXd Conversion<std::string, MatrixXd>::operator()(const std::string& argument) const {
        SerializedMatrixXd temp;
        temp.ParseFromString(argument);
        MatrixXd result(temp.rows(), temp.cols());
        for (int i = 0; i < result.size(); ++i) {result(i) = temp.data(i);}
        return result;
    }

    std::string Conversion<MatrixXI, std::string>::operator()(const MatrixXI& argument) const {
        Conversion<Interval, std::string> interval_serializer;
        SerializedMatrixXI temp;
        temp.set_rows(argument.rows());
        temp.set_cols(argument.cols());
        for (int i = 0; i < argument.size(); ++i) {
            temp.add_data(interval_serializer(argument(i)));
       }
        return temp.SerializeAsString();
    }

    MatrixXI Conversion<std::string, MatrixXI>::operator()(const std::string& argument) const {
        Conversion<std::string, Interval> interval_deserializer;
        SerializedMatrixXI temp;
        temp.ParseFromString(argument);
        MatrixXI result(temp.rows(), temp.cols());
        for (int i = 0; i < result.size(); ++i) {
            result(i) = interval_deserializer(temp.data(i));
        }
        return result;
    }

    std::string TypeName<MatrixXd>::operator()() const {return "MatrixXd";}

    std::string TypeName<MatrixXI>::operator()() const {return "MatrixXI";}

    std::string TypeName<Vector2d>::operator()() const {return "Vector2d";}

    std::string TypeName<Vector3d>::operator()() const {return "Vector3d";}

    std::string TypeName<VectorXd>::operator()() const {return "VectorXd";}

    std::string TypeName<RowVector2d>::operator()() const {return "RowVector2d";}

    std::string TypeName<RowVector3d>::operator()() const {return "RowVector3d";}

    std::string TypeName<RowVectorXd>::operator()() const {return "RowVectorXd";}

    std::string TypeName<Matrix2d>::operator()() const {return "Matrix2d";}

    std::string TypeName<Matrix3d>::operator()() const {return "Matrix3d";}

    std::string TypeName<Vector2I>::operator()() const {return "Vector2I";}

    std::string TypeName<Vector3I>::operator()() const {return "Vector3I";}

    std::string TypeName<VectorXI>::operator()() const {return "VectorXI";}

    std::string TypeName<RowVector2I>::operator()() const {return "RowVector2I";}

    std::string TypeName<RowVector3I>::operator()() const {return "RowVector3I";}

    std::string TypeName<RowVectorXI>::operator()() const {return "RowVectorXI";}

    std::string TypeName<Matrix2I>::operator()() const {return "Matrix2I";}

    std::string TypeName<Matrix3I>::operator()() const {return "Matrix3I";}
}
