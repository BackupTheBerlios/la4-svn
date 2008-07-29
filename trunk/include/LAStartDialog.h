/******************************************************************************
 * LAStartDialog.h                                                            *
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
 * Copyright (C) 2002-2008 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#ifndef LA_START_DIALOG_H_
#define LA_START_DIALOG_H_

/* Qt includes */
#include <QtGui/QDialog>

/* LA4 includes */
#include "ui_LAStartDialog.h"

/* Forward declarations */

/*!
 * This dialog displays the start dialog used to create a new document.
 */
class LAStartDialog : public QDialog
{
  Q_OBJECT

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default constructor
   *
   * \param parent Parent of the window
   */
  LAStartDialog(QWidget * parent = 0);

  /*!
   * Default destructor
   */
  ~LAStartDialog();

  /************************************************************* Public slots */
public slots:
	/*!
	 * Opens browse dialog
	 * 
	 * This slot will update the filename field if the dialog is accepted.
	 */
	void openBrowseDialog();

  /*!
   * This slot reinitialises the dialog and calls the parent show method. 
   */
  void show();

  /****************************************************************** Signals */
signals:

  /********************************************************** Private members */
private:
  /*! Private UI actual window */
  Ui::LAStartDialog m_ui;

};

#endif /* LA_START_DIALOG_H_ */
