/*
* Copyright (c) 2014 Clark Cianfarini
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _PLATFORM_DEFS_H_
#define _PLATFORM_DEFS_H_

#include <string>
#include <vector>
#include <tuple>
#include "PluginRegistry.h"

namespace FlakedTuna
{
	
/*******************************************************
 * Win32 platform specific
 *******************************************************/
#ifdef WIN32

#include <Windows.h>

#define PLUG_HANDLE		HMODULE

/*******************************************************
* *NIX platform specific
*******************************************************/
#else

#include <dlfcn.h>
#include <dirent.h>

#define PLUG_HANDLE		void*

#endif

/*******************************************************
* Non-platform specific code
*******************************************************/
	typedef PluginRegistry* (*RegFuncPtr)();
	typedef void (*CloseFuncPtr)();
	typedef int (*VersionFuncPtr)();

	std::pair<std::vector<PLUG_HANDLE>, std::vector<std::pair<int, PluginRegistry*>>> GetPluginHandles(std::string directory, std::string extension);

	void ClosePluginHandles(std::vector<PLUG_HANDLE> handles);

}

#endif