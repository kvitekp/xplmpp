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
// Scoped file object interface.

#ifndef XPLMPP_FILE_H
#define XPLMPP_FILE_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cerrno>

#include "xplmpp/Common.h"

namespace xplmpp {

// Scoped file object.
class File {
public:
  File(FILE* file_ = nullptr);
  ~File();

  bool Open(const char* file_name, const char * mode);
  bool Open(const std::string& file_name, const char * mode) {
    return Open(file_name.c_str(), mode);
  }

  void Close();

  operator FILE*() { return file_; }

  std::ifstream& ifstream();

private:
  FILE* file_ = nullptr;
  std::unique_ptr<std::ifstream> ifstream_;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_FILE_H
