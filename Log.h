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
// Log interface.

#ifndef XPLMPP_LOG_H
#define XPLMPP_LOG_H

#include <sstream>

#include "xplmpp/Common.h"

// Windows stupidly pollutes global namespace.
#ifdef ERROR
#undef ERROR
#endif

namespace xplmpp {

enum LogLevel {
  INFO,
  WARNING,
  ERROR,
  FATAL,
  VERBOSE = INT_MAX
};

#ifdef _DEBUG
const LogLevel kDefaultLogLevel = INFO;
#else
const LogLevel kDefaultLogLevel = ERROR;
#endif

// Log object.
class Log {
public:

  // Log streamer helper
  class Logger {
  public:
    Logger(LogLevel log_level);
    ~Logger();

    std::ostream& stream() { return stream_;  }

  private:
    LogLevel log_level_;
    std::stringstream stream_;
  };

  typedef void(*LogWriter)(const char* string);
  typedef std::string(*PrefixProvider)();

  Log(LogLevel log_level, LogWriter log_writer = nullptr);
  ~Log() = default;

  LogLevel log_level() const { return log_level_; }
  void set_log_level(LogLevel log_level) {
    log_level_ = log_level;
  }

  LogWriter log_writer() const { return log_writer_;  }
  void set_log_writer(LogWriter log_writer) {
    log_writer_ = log_writer;
  }

  PrefixProvider prefix_provider() const { return prefix_provider_;  }
  void set_prefix_provider(PrefixProvider prefix_provider) {
    prefix_provider_ = prefix_provider;
  }

  void WriteString(const char* string);
  void WriteString(const std::string& string) {
    WriteString(string.c_str());
  }

  bool ShouldLog(LogLevel log_level) const {
    return log_level >= log_level_;
  }

 private:
  friend Logger;
  LogLevel log_level_;
  LogWriter log_writer_ = nullptr;
  PrefixProvider prefix_provider_ = nullptr;
};

extern Log g_log;

#define LOG(level) Log::Logger(level).stream()

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_LOG_H
