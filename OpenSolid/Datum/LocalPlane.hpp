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

#ifndef OPENSOLID__LOCALPLANE_HPP
#define OPENSOLID__LOCALPLANE_HPP

namespace OpenSolid
{
    class LocalPlane
    {
    private:
        int _first_index;
        int _second_index;
    public:
        LocalPlane(int first_index, int second_index);
        
        int firstIndex() const;
        int secondIndex() const;

        static LocalPlane XY();
        static LocalPlane XZ();
        static LocalPlane YX();
        static LocalPlane YZ();
        static LocalPlane ZX();
        static LocalPlane ZY();
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline LocalPlane::LocalPlane(int first_index, int second_index) :
        _first_index(first_index), _second_index(second_index) {}

    inline int LocalPlane::firstIndex() const {return _first_index;}

    inline int LocalPlane::secondIndex() const {return _second_index;}

    inline LocalPlane LocalPlane::XY() {return LocalPlane(0, 1);}

    inline LocalPlane LocalPlane::XZ() {return LocalPlane(0, 2);}

    inline LocalPlane LocalPlane::YX() {return LocalPlane(1, 0);}

    inline LocalPlane LocalPlane::YZ() {return LocalPlane(1, 2);}

    inline LocalPlane LocalPlane::ZX() {return LocalPlane(2, 0);}

    inline LocalPlane LocalPlane::ZY() {return LocalPlane(2, 1);}
}

#endif
