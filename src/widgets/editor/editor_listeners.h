/* ASE - Allegro Sprite Editor
 * Copyright (C) 2001-2011  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef WIDGETS_EDITOR_LISTENERS_H_INCLUDED
#define WIDGETS_EDITOR_LISTENERS_H_INCLUDED

#include "listeners.h"
#include "widgets/editor/editor_listener.h"

class Editor;

class EditorListeners
{
public:
  EditorListeners();

  void addListener(EditorListener* listener);
  void removeListener(EditorListener* listener);

  void notifyScrollChanged(Editor* editor);
  void notifyDocumentChanged(Editor* editor);

private:
  Listeners<EditorListener> m_listeners;
};

#endif	// WIDGETS_EDITOR_LISTENERS_H_INCLUDED