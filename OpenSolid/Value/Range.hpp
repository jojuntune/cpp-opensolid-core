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

#ifndef OPENSOLID__RANGE_HPP
#define OPENSOLID__RANGE_HPP

#include <OpenSolid/Value/ValueBase.hpp>

namespace OpenSolid
{
    class Range
    {
    private:
        Index _start;
        Index _size;
    public:
        Range(Index start, Index size)
        
        Index start() const;
        Index size() const;
    };
    
    class First : public Range
    {
    public:
        First(Index size);
    };
    
    class Last : public Range
    {
    public:
        Last(Index size);
    };
    
    class All : public Range
    {
    public:
        All();
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Range::Range(Index start, Index size) : _start(start), _size(size) {}
    
    inline Index Range::start() const {return _start;}
    
    inline Index Range::size() const {return _size;}
    
    inline First::First(Index size) : Range(0, size) {}
    
    inline Last::Last(Index size) : Range(-1, size) {}
    
    inline All::All() : Range(0, -1) {}
}

#endif
