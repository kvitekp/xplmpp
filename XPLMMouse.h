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
// XPLM Mouse API wrappers.

#ifndef XPLMPP_XPLMMOUSE_H
#define XPLMPP_XPLMMOUSE_H

#include "xplmpp/Base.h"
#include "xplmpp/Point.h"

namespace xplmpp {

// Wraps XPLM Mouse API.
class XPLMMouse {
 public:

  static void GetLocation(Point& pt);
  static void GetLocationGlobal(Point& pt);
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMMOUSE_H
