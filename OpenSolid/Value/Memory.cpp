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

#include <OpenSolid/Value/Eigen.hpp>
#include <OpenSolid/Value/Memory.hpp>

namespace OpenSolid
{
    static boost::singleton_pool<void, 16> pool16;
    static boost::singleton_pool<void, 32> pool32;
    static boost::singleton_pool<void, 64> pool64;
    static boost::singleton_pool<void, 128> pool128;
    static boost::singleton_pool<void, 256> pool256;
    
    void* Memory::allocate(std::size_t size) {
        if (size & 16 == size) {
            return pool16.malloc();
        } else if (size & 32 == size) {
            return pool32.malloc();
        } else if (size & 64 == size) {
            return pool64.malloc();
        } else if (size & 128 == size) {
            return pool128.malloc();
        } else if (size & 256 == size) {
            return pool256.malloc();
        } else {
            return Eigen::internal::aligned_malloc(size);
        }
    }
    
    void* Memory::free(void* pointer, std::size_t size) {
        if (size & 16 == size) {
            pool16.free(pointer);
        } else if (size & 32 == size) {
            pool32.free(pointer);
        } else if (size & 64 == size) {
            pool64.free(pointer);
        } else if (size & 128 == size) {
            pool128.free(pointer);
        } else if (size & 256 == size) {
            pool256.free(pointer);
        } else {
            return Eigen::internal::aligned_free(pointer);
        }
    }
}
