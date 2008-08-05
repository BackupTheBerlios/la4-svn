/******************************************************************************
 * LAWindow.cpp                                                               *
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

#include "LAWindow.h"

/* Qt includes */

/* LA4 includes */
#include "LAPreferencesDialog.cpp"
#include "ui_LAAboutWindow.h"

/************************************************** Constructors/Destructor */
LAWindow::LAWindow(QWidget * parent)
    : QMainWindow(parent)
{

	/* First, let Qt do its stuff */
	m_ui.setupUi(this);

	/* Some variables have to be initialised to NULL to make it clear */
	/* (QA) All variables must be indeed initialised */
	m_aboutDialog = NULL;
	m_LAAboutDialog_Ui = NULL;
	/*! This dialog must be instantiated for configuration of default values */
	/* in case preferences have not yet been set */
	m_optionsDialog = new LAPreferencesDialog();

	/* Connect menu actions */
	connect(m_ui.action_Preferences, SIGNAL(triggered()), this, SLOT(editPreferences()));
	connect(m_ui.action_About, SIGNAL(triggered()), this, SLOT(helpAbout()));

  /* Connect other slots */
  connect(&LA4_Global_Settings, SIGNAL(GetDefaultValues()), this, SLOT(ResetPreferences()));

}

LAWindow::~LAWindow()
{

	/* Delete about dialog if it has been created */
	if (m_aboutDialog != NULL)
		{
			delete m_aboutDialog;
		}

	/* Delete options dialog if it has been created */
	if (m_optionsDialog != NULL)
		{
			delete m_optionsDialog;
		}

}

/************************************************************* Public slots */
void LAWindow::ResetPreferences()
{
	if (m_optionsDialog != NULL)
		{
			((LAPreferencesDialog *)m_optionsDialog)->ResetToDefault();
		}
}

/********************************************************** Protected slots */
void LAWindow::editPreferences()
{

	/* Create dialog if necessary (this should no be the case but anyway) */
	if (m_optionsDialog == NULL)
		{
			m_optionsDialog = new LAPreferencesDialog();
		}

	/* If the dialog is already visible, we just raise it, otherwise, we show it. */
	if (m_optionsDialog->isVisible())
		{
			m_optionsDialog->raise();
		}
	else
		{
			/*
			 * As we have purposely set the type of the m_optionsDialog
			 * member to QDialog and as the options dialog has special
			 * stuff to do on show, we must cast.
			 */
			((LAPreferencesDialog *)m_optionsDialog)->show();
		}

}

void LAWindow::helpAbout()
{

	/* Create dialog if necessary */
	if (m_aboutDialog == NULL)
		{
			m_aboutDialog = new QDialog();
			m_LAAboutDialog_Ui = new Ui_LAAboutDialog();
			m_LAAboutDialog_Ui->setupUi(m_aboutDialog);
		}

	/* If the dialog is already visible, we just raise it, otherwise, we show it. */
	if (m_aboutDialog->isVisible())
		{
			m_aboutDialog->raise();
		}
	else
		{
			m_aboutDialog->show();
		}

}
