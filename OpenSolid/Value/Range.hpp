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

namespace OpenSolid
{
    class Range
    {
    private:
        int _start;
        int _size;
    public:
        Range(int index);
        Range(int start, int size)
        
        int start(int indexed_size) const;
        int size(int indexed_size) const;
    };
    
    class First : public Range
    {
    public:
        First(int size);
    };
    
    class Last : public Range
    {
    public:
        Last(int size);
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
    inline Range::Range(int index) : _start(index), _size(1) {}
    
    inline Range::Range(int start, int size) : _start(start), _size(size) {}
    
    inline int Range::start(int indexed_size) const {
        return _start == -1 ? indexed_size - _size : _start;
    }
    
    inline int Range::size(int indexed_size) const {
        return _size == -1 ? indexed_size - _start : _size;
    }
    
    inline First::First(int size) : Range(0, size) {}
    
    inline Last::Last(int size) : Range(-1, size) {}
    
    inline All::All() : Range(0, -1) {}
}

#endif
