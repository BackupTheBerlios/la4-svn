/******************************************************************************
 * LAWindow.h                                                                 *
 ******************************************************************************
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; either version 2 of the       *
 *   License, or (at your option) any later version.                          *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
 *                                                                            *
 ******************************************************************************
 * LA4: Tool for real-time systems design                                     *
 * Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#ifndef LA_WINDOW_H_
#define LA_WINDOW_H_

/* Qt includes */
#include <QtGui/QMainWindow>

/* LA4 includes */
#include "ui_LAWindow.h"

/* Forward declarations */
class Ui_LAAboutDialog;

/*!
 * A LAWindow is responsible of the displaying of one project only.
 *
 * It has a menu, handles it, handles key pressing and manages the views of
 * the document.
 */
class LAWindow : public QMainWindow
{
    Q_OBJECT

  /****************************************************** Friend declarations */
public:
  friend class LAProject;

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default constructor
   *
   * \param project_ Project the window must handle.
   */
  LAWindow(QWidget * parent = 0); //LAProject * project_);

  /*!
   * Default destructor
   */
  virtual ~LAWindow();

  /************************************************************* Public slots */
public slots:
  /*!
   * Reset preferences to default values
   */
  void ResetPreferences();

  /****************************************************************** Signals */
signals:

  /******************************************************** Protected methods */
protected:

  /********************************************************** Protected slots */
protected slots:
  /*!
   * This slot performs the action of the Edit/Preferences menu item
   */
  void editPreferences();

  /*!
   * This slot performs the action of the Help/About menu item
   */
  void helpAbout();

  /******************************************************** Protected members */
protected:

  /********************************************************** Private members */
private:
  /*! About dialog (not null if it has been showed at least once) */
  QDialog * m_aboutDialog;

  /*! Ui instance for the about dialog setup */
  Ui_LAAboutDialog * m_LAAboutDialog_Ui;

  /*! Options dialog */
  QDialog * m_optionsDialog;

  /*! Private UI actual window */
  Ui::LAWindowClass m_ui;

};

#endif /* LA_WINDOW_H_ */
