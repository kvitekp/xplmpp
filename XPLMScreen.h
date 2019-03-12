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
// XPLM Screen API wrappers.

#ifndef XPLMPP_XPLMSCREEN_H
#define XPLMPP_XPLMSCREEN_H

#include "xplmpp/Base.h"
#include "xplmpp/Size.h"
#include "xplmpp/Rect.h"

namespace xplmpp {

// Wraps XPLM Screen API.
class XPLMScreen {
 public:

  static void GetSize(Size& sz);
  static void GetBoundsGlobal(Rect& rc);
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMSCREEN_H
