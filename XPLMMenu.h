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
// XPLM menu abstraction.

#ifndef XPLMPP_XPLMMENU_H
#define XPLMPP_XPLMMENU_H

#include "xplmpp/Base.h"

#include "XPLMMenus.h"

namespace xplmpp {

// Represents XPLM Menu.
class XPLMMenu {
 public:

  struct Handler {
    virtual void OnMenuCommand(XPLMMenu& menu, void* item_ref) = 0;
  };

  XPLMMenu(Handler* handler = nullptr);
  ~XPLMMenu();

  XPLMMenuID id() const { return id_; }

  Handler* handler() const { return handler_; }
  void set_handler(Handler* handler) { handler_ = handler; }

  XPLMMenuID Create(const char* name,
                    XPLMMenuID parent_menu = nullptr,
                    int parent_item = 0);
  XPLMMenuID Create(const std::string& name,
                    XPLMMenuID parent_menu = nullptr,
                    int parent_item = 0) {
    return Create(name.c_str(), parent_menu, parent_item);
  }

  // XPLM Menu API wrappers
  static XPLMMenuID FindPluginsMenu();
  static XPLMMenuID FindAircraftMenu();

  static XPLMMenuID CreateMenu(const char* name,
                               XPLMMenuID parent_menu,
                               int parent_item,
                               XPLMMenuHandler_f handler,
                               void* menuRef);
  static XPLMMenuID CreateMenu(const std::string& name,
                               XPLMMenuID parent_menu,
                               int parent_item,
                               XPLMMenuHandler_f handler,
                               void* menu_ref) {
    return CreateMenu(name.c_str(), parent_menu, parent_item,
                      handler, menu_ref);
  }

  void DestroyMenu();

  void ClearAllMenuItems();

  int AppendMenuItem(const char* name, void* item_ref);
  int AppendMenuItem(const std::string& name, void* item_ref) {
    return AppendMenuItem(name.c_str(), item_ref);
  }

  int AppendMenuItemWithCommand(const char* name, XPLMCommandRef cmd_ref);
  int AppendMenuItemWithCommand(const std::string& name, XPLMCommandRef cmd_ref) {
    return AppendMenuItemWithCommand(name.c_str(), cmd_ref);
  }

  void AppendMenuSeparator();

  void SetMenuItemName(int index, const char* name, bool force_english = false);
  void SetMenuItemName(int index, const std::string& name, bool force_english = false) {
    SetMenuItemName(index, name.c_str(), force_english);
  }

  void CheckMenuItem(int index, XPLMMenuCheck check);

  XPLMMenuCheck CheckMenuItemState(int index);

  void EnableMenuItem(int index, bool enable = true);

  void RemoveMenuItem(int index);

 private:
  static void Callback(void* menu_ref, void* item_ref);
  void OnCallback(void* item_ref);

  XPLMMenuID id_ = nullptr;
  Handler* handler_ = nullptr;
};

}  // namespace xplmpp

#endif  // #ifndef XPLMPP_XPLMMENU_H
