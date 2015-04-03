/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include <OpenSolid/Scripting/ScriptEngine.hpp>

extern "C"
{
#include <wren.h>
}

namespace opensolid
{
    char*
    loadModule(WrenVM* wrenVM, const char* moduleName) {
        // TODO
        return nullptr;
    }

    WrenForeignMethodFn
    bindForeignMethod(
        WrenVM* wrenVM,
        const char* module,
        const char* className,
        bool isStatic,
        const char* signature
    ) {
        // TODO
        return nullptr;
    }

    ScriptEngine::ScriptEngine() :
        _wrenVM(nullptr) {

        WrenConfiguration config;

        config.reallocateFn = nullptr;
        config.loadModuleFn = loadModule;
        config.bindForeignMethodFn = bindForeignMethod;
        config.initialHeapSize = 0;
        config.minHeapSize = 0;
        config.heapGrowthPercent = 0;

        _wrenVM = wrenNewVM(&config);
    }

    ScriptEngine::~ScriptEngine() {
        wrenFreeVM(_wrenVM);
    }

    void
    ScriptEngine::run(const std::string& script) {
        wrenInterpret(_wrenVM, "run()", script.c_str());
    }
}
