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
#include <OpenSolid/Core/Common/List.hpp>

namespace opensolid
{
    TypeSchema Schema<DatumXd>::operator()() const {
        TypeSchema result;
        result.addItem<MatrixXd>("Origin");
        result.addItem<MatrixXd>("Basis");
        return result;
    }

    List Conversion<DatumXd, List>::operator()(const DatumXd& argument) const {
        List result;
        result.append(MatrixXd(argument.origin()));
        result.append(MatrixXd(argument.basis()));
        return result;
    }

    DatumXd Conversion<List, DatumXd>::operator()(const List& argument) const {
        return DatumXd(argument[0].as<MatrixXd>(), argument[1].as<MatrixXd>());
    }

    std::string TypeName<Datum2d>::operator()() const {return "Datum2d";}

    std::string TypeName<Datum3d>::operator()() const {return "Datum3d";}

    std::string TypeName<DatumXd>::operator()() const {return "DatumXd";}
}
