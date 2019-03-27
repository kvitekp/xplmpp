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
// Log implementation.

#include "xplmpp/Log.h"

namespace xplmpp {

Log g_log;

Log::Logger::Logger(LogLevel log_level)
: log_level_(log_level) {
  if (g_log.ShouldLog(log_level)) {
    stream_ << g_log.prefix_;
  }
}

Log::Logger::~Logger() {
  if (g_log.ShouldLog(log_level_)) {
    stream_ << std::endl;
    g_log.WriteString(stream_.str());
  }
}

Log::Log(LogLevel log_level)
: log_level_(log_level) {
}

void Log::WriteString(const char* string) {
  if (log_writer_) {
    log_writer_(string);
  }
}

}  // namespace xplmpp
