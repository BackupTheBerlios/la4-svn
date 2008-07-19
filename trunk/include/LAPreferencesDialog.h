/******************************************************************************
 * LAPreferencesDialog.h                                                      *
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

#ifndef LA_PREFERENCES_DIALOG_H_
#define LA_PREFERENCES_DIALOG_H_

/* Qt includes */
#include <QtGui/QDialog>

/* LA4 includes */
#include "ui_LAPreferencesWindow.h"

/* Forward declarations */

/*!
 * This dialog displays the preferences dialog and handles the interface
 * with the setting class (LASettings).
 *
 */
class LAPreferencesDialog : public QDialog
{
    Q_OBJECT

  	/************************************************** Constructors/Destructor */
public:
	/*!
	 * Default constructor
	 *
	 * \param parent Parent of the window
	 */
	LAPreferencesDialog(QWidget * parent = 0);

	/*!
	 * Default destructor
	 */
	~LAPreferencesDialog();

  	/************************************************************* Public slots */
public slots:
	/*!
	 * Reset preferences to default values
	 * 
	 * This slot only takes care of values that are defined in the dialog.
	 */
	void ResetToDefault();

	/*!
	 * This slot reinitialises the dialog and calls the parent show method. 
	 */
	void show();

  	/****************************************************************** Signals */
signals:

	/******************************************************** Protected methods */
protected:

  	/********************************************************** Protected slots */
protected slots:
	/*!
	 * This slot saves the preferences and apply them
	 */
	void applyPreferences();

	/*!
	 * This slot associates the la4 format to the LA4 program
	 * 
	 * IMPORTANT: This slot does nothing for now.
	 * 
	 * TODO Implement file association
	 */
	void associateFile();

	/*!
	 * This slot opens a dialog to define the default open path
	 */
	void openOpenPathDialog();

	/*!
	 * This slot opens a dialog to define the default save path
	 */
	void openSavePathDialog();

	/*!
	 * This slot opens a dialog to define the default security save path
	 */
	void openSecuritySavePathDialog();

	/*!
	 * This slot opens a dialog to define the XML definitions path
	 */
	void openXMLDefinitionsPathDialog();

	/*!
	 * This slot saves the options and exits the dialog
	 */
	void savePreferencesAndExit();

	/******************************************************** Protected members */
protected:

	/********************************************************** Private members */
private:
	/*! Private UI actual window */
    Ui::LAPreferencesWindowClass m_ui;

};

#endif /* LA_PREFERENCES_DIALOG_H_ */
