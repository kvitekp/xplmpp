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
// Scoped file object implementation.

#include "xplmpp/File.h"

#include "assert.h"

namespace xplmpp {

File::File(FILE* file)
: file_(file) {
}

File::~File() {
  Close();
}

bool File::Open(const char* file_name, const char * mode) {
  assert(file_ == nullptr);
  file_ = fopen(file_name, mode);
  return file_ != nullptr;
}

void File::Close() {
  if (!ifstream_) {
    ifstream_->close();
    ifstream_ = nullptr;
  }
  if (file_) {
    fclose(file_);
    file_ = nullptr;
  }
}

std::ifstream& File::ifstream() {
  assert(file_ != nullptr);
  if (!ifstream_) {
    ifstream_ = std::make_unique<std::ifstream>(file_);
  }

  return *ifstream_;
}

}  // namespace xplmpp
