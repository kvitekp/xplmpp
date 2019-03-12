// Copyright (c) 2019 Peter Kvitek. All rights reserved.
//
// Author: Peter Kvitek (pete@kvitek.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Base declarations.

#ifndef XPLMPP_BASE_H
#define XPLMPP_BASE_H

// Include X-Plane headers
#include "XPLMDefs.h"

#if kXPLM_Version < 301
#error This has to be compiled against at least the XPLM301 SDK
#endif

// Include platform headers
#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Include library headers
#include <stdio.h >
#include <string.h>
#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

// Disable annoying MSVC warnings at /W4
#ifdef _MSC_VER
#pragma warning(disable:4100) /* unreferenced formal paramete */
#endif // _MSC_VER

/*
 * Useful declarations
 */

// Number of elements in array
#ifndef numbof
#define numbof(a)  (sizeof(a)/sizeof(a[0]))
#endif

// Length of the const string
#ifndef lengof
#define lengof(s)  (numbof(s) - 1)
#endif

// Literal string length specification
#ifndef LITERAL
#define LITERAL(s) s, lengof(s)
#endif

namespace xplmpp {

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_BASE_H
