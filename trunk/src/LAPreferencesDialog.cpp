/******************************************************************************
 * LAPreferencesDialog.cpp                                                    *
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

#include "LAPreferencesDialog.h"

/* Qt includes */
#include <QDir>
#include <QFileDialog>

/* LA4 includes */
#include "LA4Namespace.h"
#include "LALogger.h"
#include "LASettings.h"

/* Debugging levels */
#undef DEBUG

/************************************************** Constructors/Destructor */
LAPreferencesDialog::LAPreferencesDialog(QWidget * parent)
	: QDialog(parent)
{
	/* First, let Qt do its stuff */
	m_ui.setupUi(this);

  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}

LAPreferencesDialog::~LAPreferencesDialog()
{
  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/************************************************************* Public slots */
void LAPreferencesDialog::ResetToDefault()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Some useful paths */
	QString homePath = QDir::toNativeSeparators(QDir::homePath());
	QString tempPath = QDir::toNativeSeparators(QDir::tempPath());
	QString applicationPath = QApplication::applicationDirPath();

	/* General tab */
	LA4_Global_Settings.SetValue(LA4::MAX_RECENT_FILES_COUNT_KEY, LA4::MAX_RECENT_FILES_COUNT_DEFAULT_VALUE);

	/* Save tab */ 
	LA4_Global_Settings.SetValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY, LA4::BACKUP_FILE_SAVING_OPTION_DEFAULT_VALUE);
	LA4_Global_Settings.SetValue(LA4::SECURITY_SAVE_PATH_KEY, tempPath);
	LA4_Global_Settings.SetValue(LA4::SECURITY_SAVE_INTERVAL_KEY, LA4::SECURITY_SAVE_INTERVAL_DEFAULT_VALUE);

	/* Folder tab */
	LA4_Global_Settings.SetValue(LA4::DEFAULT_SAVE_PATH_KEY, homePath);
	LA4_Global_Settings.SetValue(LA4::DEFAULT_OPEN_PATH_KEY, homePath);
	LA4_Global_Settings.SetValue(LA4::PLATFORMS_PATH_KEY, applicationPath + QDir::separator() + LA4::PLATFORMS_DEFAULT_DIRECTORY);

	/* File association tab */

	/* Display tab */
	LA4_Global_Settings.SetValue(LA4::DISPLAY_TOOLS_KEY, LA4::DISPLAY_TOOLS_DEFAULT_VALUE);
	LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_BAR_KEY, LA4::DISPLAY_STATUS_BAR_DEFAULT_VALUE);
	LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_TIPS_KEY, LA4::DISPLAY_STATUS_TIPS_DEFAULT_VALUE);

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::show()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Initialise fields */

	/*! Note: We use LA4::SettingValue to read values as it is more generic */

	/* General tab options */
	/***********************/
	m_ui.maxRecentFilesCount->setValue(QString(LA4::SettingValue(LA4::MAX_RECENT_FILES_COUNT_KEY)).toInt());

	/* Save tab options */
	/********************/
	if (LA4::SettingValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY) == LA4::BACKUP_REPLACE_EXTENSION)
		{
			m_ui.replaceExtRadio->setChecked(true);
		}
	else if (LA4::SettingValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY) == LA4::BACKUP_ADD_EXTENSION)
		{
			m_ui.addExtRadio->setChecked(true);
		}
	else
		{
			/* Default value will be "nosave" when it will be saved */
			m_ui.noSaveRadio->setChecked(true);
		}
	m_ui.securitySavePath->setText(LA4::SettingValue(LA4::SECURITY_SAVE_PATH_KEY));
	m_ui.securitySaveInterval->setText(LA4::SettingValue(LA4::SECURITY_SAVE_INTERVAL_KEY));

	/* Folder tab options */
	/**********************/
	m_ui.savePath->setText(LA4::SettingValue(LA4::DEFAULT_SAVE_PATH_KEY));
	m_ui.openPath->setText(LA4::SettingValue(LA4::DEFAULT_OPEN_PATH_KEY));
	m_ui.xmldefPath->setText(LA4::SettingValue(LA4::PLATFORMS_PATH_KEY));

	/* File associations tab options */
	/*********************************/

	/* Display options */
	/*******************/
	if (LA4::SettingValue(LA4::DISPLAY_TOOLS_KEY) == LA4::TRUE_STRING)
		{
			m_ui.toolsCheck->setChecked(true);
		}
	if (LA4::SettingValue(LA4::DISPLAY_STATUS_BAR_KEY) == LA4::TRUE_STRING)
		{
			m_ui.statusCheck->setChecked(true);
		}
	if (LA4::SettingValue(LA4::DISPLAY_STATUS_TIPS_KEY) == LA4::TRUE_STRING)
		{
			m_ui.helpCheck->setChecked(true);
		}

	/* Show the dialog */
	QDialog::show();

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

/********************************************************** Protected slots */
void LAPreferencesDialog::applyPreferences()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Disable autosync */
	LA4_Global_Settings.DisableAutosave();

	/* General tab */
	LA4_Global_Settings.SetValue(LA4::MAX_RECENT_FILES_COUNT_KEY, QString::number(m_ui.maxRecentFilesCount->value()));

	/* Save tab */ 
	if (m_ui.replaceExtRadio->isChecked())
		{
			LA4_Global_Settings.SetValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY, LA4::BACKUP_REPLACE_EXTENSION);
		}
	else if (m_ui.addExtRadio->isChecked())
		{
			LA4_Global_Settings.SetValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY, LA4::BACKUP_ADD_EXTENSION);
		}
	else
		{
			/* Default value is "nosave" */
			LA4_Global_Settings.SetValue(LA4::BACKUP_FILE_SAVING_OPTION_KEY, LA4::BACKUP_NO_SAVE);
		}
	LA4_Global_Settings.SetValue(LA4::SECURITY_SAVE_PATH_KEY, m_ui.securitySavePath->text());
	LA4_Global_Settings.SetValue(LA4::SECURITY_SAVE_INTERVAL_KEY, m_ui.securitySaveInterval->text());

	/* Folder tab */
	LA4_Global_Settings.SetValue(LA4::DEFAULT_SAVE_PATH_KEY, m_ui.savePath->text());
	LA4_Global_Settings.SetValue(LA4::DEFAULT_OPEN_PATH_KEY, m_ui.openPath->text());
	LA4_Global_Settings.SetValue(LA4::PLATFORMS_PATH_KEY, m_ui.xmldefPath->text());

	/* File association tab */

	/* Display tab */
	if (m_ui.toolsCheck->isChecked())
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_TOOLS_KEY, LA4::TRUE_STRING);
		}
	else
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_TOOLS_KEY, LA4::FALSE_STRING);
		}
	if (m_ui.toolsCheck->isChecked())
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_BAR_KEY, LA4::TRUE_STRING);
		}
	else
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_BAR_KEY, LA4::FALSE_STRING);
		}
	if (m_ui.toolsCheck->isChecked())
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_TIPS_KEY, LA4::TRUE_STRING);
		}
	else
		{
			LA4_Global_Settings.SetValue(LA4::DISPLAY_STATUS_TIPS_KEY, LA4::FALSE_STRING);
		}

	/* Save settings */
	LA4_Global_Settings.EnableAutosave();

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::associateFile()
{
  LALogger::Trace(LALogger::ERROR,
                  LALogger::MAIN,
                  "Function not implemented",
                  LA_DEBUG_ARGS);
}

void LAPreferencesDialog::openOpenPathDialog()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);
	m_ui.openPath->setText(QFileDialog::getExistingDirectory(this, tr("LA4 - Get default open directory"), m_ui.openPath->text()));
  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::openSavePathDialog()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);
	m_ui.savePath->setText(QFileDialog::getExistingDirectory(this, tr("LA4 - Get default save directory"), m_ui.savePath->text()));
  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::openSecuritySavePathDialog()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);
	m_ui.securitySavePath->setText(QFileDialog::getExistingDirectory(this, tr("LA4 - Get backup directory"), m_ui.securitySavePath->text()));
  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::openXMLDefinitionsPathDialog()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);
	m_ui.xmldefPath->setText(QFileDialog::getExistingDirectory(this, tr("LA4 - Get platform directory"), m_ui.xmldefPath->text()));
  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAPreferencesDialog::savePreferencesAndExit()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Apply preferences and accept dialog */
	applyPreferences();
	accept();

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}
