// Copyright (c) 2019 Peter Kvitek.
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
// XPLM Path API wrappers.

#include "xplmpp/XPLMPath.h"

#include "XPLMUtilities.h"

namespace xplmpp {

/*
 * XPLM Path API wrappers.
 */
std::string XPLMPath::GetSystemFolder() {
  char path[512 + 1];
  ::XPLMGetSystemPath(path);
  return path;
}

std::string XPLMPath::GetPrefsFolder() {
  char path[512 + 1];
  ::XPLMGetPrefsPath(path);
  char* sep = strrchr(path, GetDirectorySeparator());
  if (sep != nullptr) {
    sep[1] = 0;
  }
  return path;
}

char XPLMPath::GetDirectorySeparator() {
  return ::XPLMGetDirectorySeparator()[0];
}

}  // namespace xplmpp
