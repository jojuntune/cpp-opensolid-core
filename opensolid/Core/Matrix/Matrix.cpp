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
#include <OpenSolid/Core/Common/List.hpp>

namespace opensolid
{
    TypeDescription TypeDescriptionFunction<MatrixXd>::operator()() const {
        TypeDescription result;
        result.appendInt("Rows");
        result.appendInt("Cols");
        result.appendListOfDoubles("Data");
        return result;
    }

    List Conversion<MatrixXd, List>::operator()(const MatrixXd& argument) const {
        List result;
        result.append(argument.rows());
        result.append(argument.cols());
        result.append(List(begin(argument), end(argument)));
        return result;
    }

    MatrixXd Conversion<List, MatrixXd>::operator()(const List& argument) const {
        int rows = argument[0].as<int>();
        int cols = argument[1].as<int>();
        List data = argument[2].as<List>();
        MatrixXd result(rows, cols);
        for (int i = 0; i < data.size(); ++i) {result(i) = data[i].as<double>();}
        return result;
    }

    TypeDescription TypeDescriptionFunction<MatrixXI>::operator()() const {
        TypeDescription result;
        result.appendInt("Rows");
        result.appendInt("Cols");
        result.appendListOfObjects<Interval>("Data");
        return result;
    }

    List Conversion<MatrixXI, List>::operator()(const MatrixXI& argument) const {
        List result;
        result.append(argument.rows());
        result.append(argument.cols());
        result.append(List(begin(argument), end(argument)));
        return result;
    }

    MatrixXI Conversion<List, MatrixXI>::operator()(const List& argument) const {
        int rows = argument[0].as<int>();
        int cols = argument[1].as<int>();
        List data = argument[2].as<List>();
        MatrixXI result(rows, cols);
        for (int i = 0; i < data.size(); ++i) {result(i) = data[i].as<Interval>();}
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
