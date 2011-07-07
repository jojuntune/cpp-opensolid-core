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

#ifndef OPENSOLID__PYTHONMATRIXXD_HPP
#define OPENSOLID__PYTHONMATRIXXD_HPP

#include <boost/shared_ptr.hpp>

#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Python/BoostPython.hpp>

namespace OpenSolid
{
    class PythonMatrixXI;
    
    class PythonMatrixXD
    {
    private:
        boost::shared_ptr<MatrixXD> _matrix;
    public:
        PythonMatrixXD();
        
        template <class DerivedType>
        PythonMatrixXD(const DenseBase<DerivedType>& argument);
        
        int rows() const;
        int cols() const;
        int size() const;
        
        
    };
}

#endif
