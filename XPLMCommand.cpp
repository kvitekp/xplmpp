// Copyright (c) 2019 Peter Kvitek.
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

#include "xplmpp/XPLMCommand.h"

namespace xplmpp {

/*
 * XPLM Command abstraction implementation.
 */
XPLMCommand::XPLMCommand(XPLMCommandRef ref)
: ref_(ref) {
}

XPLMCommand::XPLMCommand(Handler* handler)
: handler_(handler) {
}

XPLMCommand::~XPLMCommand() {
  Destroy();
}

XPLMCommandRef XPLMCommand::Create(const char* name,
                                   const char* description,
                                   bool before) {
  ref_ = CreateCommand(name, description);
  if (!ref_)
    return nullptr;

  RegisterCommandHandler(Callback, before, this);

  handler_registration_ = before ? HandlerRegistration::before : HandlerRegistration::after;

  return ref_;
}

int XPLMCommand::Callback(XPLMCommandRef ref, XPLMCommandPhase phase, void* refcon) {
  return static_cast<XPLMCommand*>(refcon)->OnCallback(ref, phase) ? 1 : 0;
}

bool XPLMCommand::OnCallback(XPLMCommandRef ref, XPLMCommandPhase phase) {
  return handler_ ? handler_->OnCommand(ref, phase) : true;
}

void XPLMCommand::Destroy() {
  if (handler_registration_ != HandlerRegistration::none) {
    bool before = handler_registration_ == HandlerRegistration::before;
    UnregisterCommandHandler(Callback, before, this);
    handler_registration_ = HandlerRegistration::none;
  }
}

// API wrappers
XPLMCommandRef XPLMCommand::FindCommand(const char* name) {
  return ::XPLMFindCommand(name);
}

void XPLMCommand::CommandBegin() {
  assert(ref_ != nullptr);

  return ::XPLMCommandBegin(ref_);
}

void XPLMCommand::CommandEnd() {
  assert(ref_ != nullptr);

  return ::XPLMCommandEnd(ref_);
}

void XPLMCommand::CommandOnce() {
  assert(ref_ != nullptr);

  return ::XPLMCommandOnce(ref_);
}

XPLMCommandRef XPLMCommand::CreateCommand(const char* name, const char* description) {
  return ::XPLMCreateCommand(name, description);
}

void XPLMCommand::RegisterCommandHandler(XPLMCommandCallback_f handler,
                                         bool before,
                                         void* refcon) {
  assert(ref_ != nullptr);

  return ::XPLMRegisterCommandHandler(ref_, handler, before, refcon);
}

void XPLMCommand::UnregisterCommandHandler(XPLMCommandCallback_f handler,
                                           bool before,
                                           void* refcon) {
  assert(ref_ != nullptr);

  return ::XPLMUnregisterCommandHandler(ref_, handler, before, refcon);
}

}  // namespace xplmpp
