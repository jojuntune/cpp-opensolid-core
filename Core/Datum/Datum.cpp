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
#include <OpenSolid/Core/Datum/Datum.hpp>

namespace OpenSolid
{
    std::string Serialization<DatumXd>::serialized(const DatumXd& argument) const {
        Serialization<MatrixXd> matrix_serializer;
        SerializedDatumXd temp;
        temp.set_origin(matrix_serializer.serialized(argument.origin()));
        temp.set_basis(matrix_serializer.serialized(argument.basis()));
        return temp.SerializeAsString();
    }

    DatumXd Serialization<DatumXd>::deserialized(const std::string& argument) const {
        Serialization<MatrixXd> matrix_serializer;
        SerializedDatumXd temp;
        temp.ParseFromString(argument);
        MatrixXd origin = matrix_serializer.deserialized(temp.origin());
        MatrixXd basis = matrix_serializer.deserialized(temp.basis());
        return DatumXd(origin, basis);
    }
}
