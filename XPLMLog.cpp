// Copyright 2019 Peter Kvitek.
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
// XPLM Log module.

#include "xplmpp/XPLMLog.h"

#include <sstream>

#include "XPLMUtilities.h"

namespace xplmpp {

XPLMLog g_log;

/*
 * XPLM log implementation.
 */
XPLMLog::XPLMLog(LogLevel log_level)
: log_level_(log_level) {
}

void XPLMLog::LogString(LogLevel log_level, const char* string) {
  if (log_level < log_level_) {
    std::stringstream ss;
    ss << prefix_ << string << std::endl;
    ::XPLMDebugString(ss.str().c_str());
  }
}

}  // namespace xplmpp
