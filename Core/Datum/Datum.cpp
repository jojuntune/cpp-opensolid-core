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

#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Datum/Datum.pb.h>

namespace OpenSolid
{
    std::string Serialization<DatumXd>::operator()(const DatumXd& argument) const {
        Serialization<MatrixXd> matrix_serializer;
        SerializedDatumXd temp;
        temp.set_origin(matrix_serializer(argument.origin()));
        temp.set_basis(matrix_serializer(argument.basis()));
        return temp.SerializeAsString();
    }

    DatumXd Deserialization<DatumXd>::operator()(const std::string& argument) const {
        Deserialization<MatrixXd> matrix_deserializer;
        SerializedDatumXd temp;
        temp.ParseFromString(argument);
        MatrixXd origin = matrix_deserializer(temp.origin());
        MatrixXd basis = matrix_deserializer(temp.basis());
        return DatumXd(origin, basis);
    }

    std::string TypeName<DatumXd>::operator()() const {return "DatumXd";}
}
