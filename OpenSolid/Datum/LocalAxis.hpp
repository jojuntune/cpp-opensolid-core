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

#ifndef OPENSOLID__LOCALAXIS_HPP
#define OPENSOLID__LOCALAXIS_HPP

namespace OpenSolid
{
    class LocalAxis
    {
    private:
        int _index;
    public:
        LocalAxis(int index);
        
        int index() const;

        static LocalAxis X();
        static LocalAxis Y();
        static LocalAxis Z();
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline LocalAxis::LocalAxis(int index) : _index(index) {}

    inline int LocalAxis::index() const {return _index;}

    inline LocalAxis LocalAxis::X() {return LocalAxis(0);}

    inline LocalAxis LocalAxis::Y() {return LocalAxis(1);}

    inline LocalAxis LocalAxis::Z() {return LocalAxis(2);}
}

#endif
