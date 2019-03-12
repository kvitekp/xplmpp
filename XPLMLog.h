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
// XPLM Log module.

#ifndef XPLMPP_LOG_H
#define XPLMPP_LOG_H

#include "xplmpp/Base.h"

// Windows stupidly pullutes global namespace.
#ifdef ERROR
#undef ERROR
#endif

namespace xplmpp {

// Log level declarations
typedef int LogLevel;
const LogLevel INFO = 0;
const LogLevel WARNING = 1;
const LogLevel ERROR = 2;
const LogLevel FATAL = 4;
const LogLevel VERBOSE = INT_MAX;

#ifdef _DEBUG
const LogLevel kDefaultLogLevel = VERBOSE;
#else
const LogLevel kDefaultLogLevel = ERROR;
#endif

// Implements XPLM logging.
class XPLMLog {
 public:
  XPLMLog(LogLevel log_level = kDefaultLogLevel);
  ~XPLMLog() = default;

  LogLevel log_level() const { return log_level_; }
  void set_log_level(LogLevel log_level) {
    log_level_ = log_level;
  }

  std::string prefix() const { return prefix_; }
  void set_prefix(const std::string& prefix) {
    prefix_ = prefix;
  }
  void set_prefix(const char* prefix) {
    prefix_ = prefix;
  }

  void LogString(LogLevel log_level, const char* string);
  void LogString(LogLevel log_level, const std::string& string) {
    LogString(log_level, string.c_str());
  }

 private:
  LogLevel log_level_;
  std::string prefix_;
};

extern XPLMLog g_log;

#define LOG(level, string) g_log.LogString(level, string)

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_LOG_H
