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
// XPLM Log implementation.

#include "xplmpp/XPLMLog.h"

#include "XPLMUtilities.h"

namespace xplmpp {

XPLMLog g_log;

XPLMLog::Logger::Logger(LogLevel log_level)
: log_level_(log_level) {
  if (g_log.ShouldLog(log_level)) {
    stream_ << g_log.prefix_;
  }
}

XPLMLog::Logger::~Logger() {
  if (g_log.ShouldLog(log_level_)) {
    stream_ << std::endl;
    g_log.WriteString(stream_.str());
  }
}

XPLMLog::XPLMLog(LogLevel log_level)
: log_level_(log_level) {
}

void XPLMLog::WriteString(const char* string) {
  ::XPLMDebugString(string);
}

}  // namespace xplmpp
