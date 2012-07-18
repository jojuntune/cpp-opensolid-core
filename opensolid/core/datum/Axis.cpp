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

#include <opensolid/core/datum/Axis.hpp>

namespace opensolid
{
    std::string TypeName<Axis2d>::operator()() const {return "Axis2d";}

    std::string TypeName<Axis3d>::operator()() const {return "Axis3d";}

    Axis2dConstructionError::Axis2dConstructionError(
            const MatrixXd& origin,
            const MatrixXd& direction
    ) : _origin(origin), _direction(direction) {}

    Axis2dConstructionError::~Axis2dConstructionError() throw() {}

    const char* Axis2dConstructionError::what() const throw() {
        return "Axis2dConstructionError";
    }

    MatrixXd Axis2dConstructionError::origin() const {return _origin;}

    MatrixXd Axis2dConstructionError::direction() const {return _direction;}

    Axis2dCopyConstructionError::Axis2dCopyConstructionError(const DatumXd& argument) :
        _argument(argument) {}

    Axis2dCopyConstructionError::~Axis2dCopyConstructionError() throw() {}

    const char* Axis2dCopyConstructionError::what() const throw() {
        return "Axis2dCopyConstructionError";
    }

    DatumXd Axis2dCopyConstructionError::argument() const {return _argument;}

    Axis3dConstructionError::Axis3dConstructionError(
            const MatrixXd& origin,
            const MatrixXd& direction
    ) : _origin(origin), _direction(direction) {}

    Axis3dConstructionError::~Axis3dConstructionError() throw() {}

    const char* Axis3dConstructionError::what() const throw() {
        return "Axis3dConstructionError";
    }

    MatrixXd Axis3dConstructionError::origin() const {return _origin;}

    MatrixXd Axis3dConstructionError::direction() const {return _direction;}

    Axis3dCopyConstructionError::Axis3dCopyConstructionError(const DatumXd& argument) :
        _argument(argument) {}

    Axis3dCopyConstructionError::~Axis3dCopyConstructionError() throw() {}

    const char* Axis3dCopyConstructionError::what() const throw() {
        return "Axis3dCopyConstructionError";
    }

    DatumXd Axis3dCopyConstructionError::argument() const {return _argument;}
}
