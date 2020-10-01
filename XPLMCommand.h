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
// XPLM command abstraction.

#ifndef XPLMPP_XPLMCOMMAND_H
#define XPLMPP_XPLMCOMMAND_H

#include "xplmpp/Base.h"

#include "XPLMUtilities.h"

namespace xplmpp {

// Represents XPLM Command.
class XPLMCommand {
 public:

  struct Handler {
    virtual bool OnCommand(XPLMCommandRef cmd_ref, XPLMCommandPhase phase) = 0;
  };

  XPLMCommand() {}
  explicit XPLMCommand(XPLMCommandRef ref_);
  explicit XPLMCommand(Handler* handler);
  ~XPLMCommand();

  XPLMCommandRef ref() const { return ref_; }

  Handler* handler() const { return handler_; }
  void set_handler(Handler* handler) { handler_ = handler; }

  XPLMCommandRef Create(const char* name,
                        const char* description,
                        bool before = true);
  XPLMCommandRef Create(const std::string& name,
                        const char* description,
                        bool before = true) {
    return Create(name.c_str(), description, before);
  }
  XPLMCommandRef Create(const char* name,
                        const std::string& description,
                        bool before = true) {
    return Create(name, description.c_str(), before);
  }
  XPLMCommandRef Create(const std::string& name,
                        const std::string& description,
                        bool before = true) {
    return Create(name.c_str(), description.c_str(), before);
  }

  void Destroy();

  // XPLM Command API wrappers
  static XPLMCommandRef FindCommand(const char* name);
  static XPLMCommandRef FindCommand(const std::string& name) {
    return FindCommand(name.c_str());
  }

  void CommandBegin();
  void CommandEnd();
  void CommandOnce();

  static XPLMCommandRef CreateCommand(const char* name,
                                      const char* description);
  static XPLMCommandRef CreateCommand(const std::string& name,
                                      const char* description) {
    return CreateCommand(name.c_str(), description);
  }
  static XPLMCommandRef CreateCommand(const char* name,
                                      const std::string& description) {
    return CreateCommand(name, description.c_str());
  }
  static XPLMCommandRef CreateCommand(const std::string& name,
                                      const std::string& description) {
    return CreateCommand(name.c_str(), description.c_str());
  }

  void RegisterCommandHandler(XPLMCommandCallback_f handler,
                              bool before,
                              void* refcon);

  void UnregisterCommandHandler(XPLMCommandCallback_f handler,
                                bool before,
                                void* refcon);

 private:
  static int Callback(XPLMCommandRef ref, XPLMCommandPhase phase, void* refcon);
  bool OnCallback(XPLMCommandRef ref, XPLMCommandPhase phase);

  XPLMCommandRef ref_ = nullptr;
  Handler* handler_ = nullptr;

  enum class HandlerRegistration {
    none,
    before,
    after
  } handler_registration_ = HandlerRegistration::none;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMCOMMAND_H
