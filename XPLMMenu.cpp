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
// XPLM menu abstraction.

#include "xplmpp/XPLMMenu.h"

namespace xplmpp {

/*
 * XPLM Menu abstraction implementation.
 */
XPLMMenu::XPLMMenu(Handler* handler)
: handler_(handler) {
}

XPLMMenu::~XPLMMenu() {
  DestroyMenu();
}

XPLMMenuID XPLMMenu::Create(const char* name,
                            XPLMMenuID parent_menu,
                            int parent_item) {
  assert(id_ == nullptr);

  id_ = CreateMenu(name, parent_menu, parent_item, Callback, this);

  return id_;
}

void XPLMMenu::Callback(void* menu_ref, void* item_ref) {
  static_cast<XPLMMenu*>(menu_ref)->OnCallback(item_ref);
}

void XPLMMenu::OnCallback(void* item_ref) {
  if (handler_) {
    handler_->OnMenuCommand(*this, item_ref);
  }
}

// API wrappers
XPLMMenuID XPLMMenu::FindPluginsMenu() {
  return ::XPLMFindPluginsMenu();
}

XPLMMenuID XPLMMenu::FindAircraftMenu() {
  return ::XPLMFindAircraftMenu();
}

XPLMMenuID XPLMMenu::CreateMenu(const char* name,
                                XPLMMenuID parent_menu,
                                int parent_item,
                                XPLMMenuHandler_f handler,
                                void* menu_ref) {
  return ::XPLMCreateMenu(name, parent_menu, parent_item, handler, menu_ref);
}

void XPLMMenu::DestroyMenu() {
  if (id_) {
    ::XPLMDestroyMenu(id_);
    id_ = nullptr;
  }
}

void XPLMMenu::ClearAllMenuItems() {
  assert(id_ != nullptr);

  return ::XPLMClearAllMenuItems(id_);
}

int XPLMMenu::AppendMenuItem(const char* name, void* item_ref) {
  assert(id_ != nullptr);

  return ::XPLMAppendMenuItem(id_, name, (void*)item_ref, 0);
}

int XPLMMenu::AppendMenuItemWithCommand(const char* name, XPLMCommandRef cmd_ref) {
  assert(id_ != nullptr);

  return ::XPLMAppendMenuItemWithCommand(id_, name, cmd_ref);
}

void XPLMMenu::AppendMenuSeparator() {
  assert(id_ != nullptr);

  ::XPLMAppendMenuSeparator(id_);
}

void XPLMMenu::SetMenuItemName(int index, const char* name, bool force_english) {
  assert(id_ != nullptr);

  ::XPLMSetMenuItemName(id_, index, name, force_english);
}

void XPLMMenu::CheckMenuItem(int index, XPLMMenuCheck check) {
  assert(id_ != nullptr);

  ::XPLMCheckMenuItem(id_, index, check);
}

XPLMMenuCheck XPLMMenu::CheckMenuItemState(int index) {
  assert(id_ != nullptr);

  XPLMMenuCheck check = xplm_Menu_NoCheck;
  ::XPLMCheckMenuItemState(id_, index, &check);

  return check;
}

void XPLMMenu::EnableMenuItem(int index, bool enable) {
  assert(id_ != nullptr);

  ::XPLMEnableMenuItem(id_, index, enable);
}

void XPLMMenu::RemoveMenuItem(int index) {
  assert(id_ != nullptr);

  ::XPLMRemoveMenuItem(id_, index);
}

}  // namespace xplmpp
