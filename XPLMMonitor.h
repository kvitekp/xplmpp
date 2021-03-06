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
// XPLM Monitor API wrappers.

#ifndef XPLMPP_XPLMMONITOR_H
#define XPLMPP_XPLMMONITOR_H

#include <vector>

#include "xplmpp/Base.h"
#include "xplmpp/Rect.h"

namespace xplmpp {

// Wraps XPLM Monitor API.
class XPLMMonitor {
 public:

  static bool GetAllMonitorBoundsGlobal(std::vector<Rect>& monitors);
  static bool GetAllMonitorBoundsOS(std::vector<Rect>& monitors);
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMMONITOR_H
