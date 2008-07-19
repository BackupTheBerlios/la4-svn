/******************************************************************************
 * LA4Settings.cpp                                                            *
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

#include "LASettings.h"

/* Qt includes */
#include <QFile>

/* LA4 includes */
#include "LA4Namespace.h"

/* Debugging levels */
#undef DEBUG

/* Global variable */
LASettings LA4_Global_Settings;

/************************************************** Constructors/Destructor */
LASettings::LASettings()
	: QObject(),
		m_preferences(LA4::LA4_ORGANISATION_NAME, LA4::LA4_PRODUCT_NAME)
{

	/* QSettings uses by default a native format and a user wide scope
	 * which is what we want, so nothing has to be configured at all.
	 */

	/*! Values setting and saving are synchronous */
	m_autosaveActivated = true;

	/*! TODO Add a singleton here? */

}

LASettings::~LASettings()
{

	/* Just in case, save settings */
	m_preferences.sync();

}

/*********************************************************** Public methods */
void LASettings::ConfigureApplication()
{

	/* Check version, if it exists, assume it is ok */
	if (m_preferences.value(LA4::LASETTINGS_VERSION_KEY).toString() != "")
		{

			/* TODO If setting file format version changes, add a conversion mechanism here */
			/* Settings are ok, no need to do anything */

#ifdef DEBUG
			qDebug("LASettings::ConfigureApplication: Settings loaded.");
#endif /* DEBUG */

		}
	else
		{

			/* Reaching this point means that the settings do not exist
			 * we have to create a new ones.
			 */
			/* Empty settings (precaution) */
			m_preferences.clear();

			/* Set version */
			m_preferences.setValue(LA4::LASETTINGS_VERSION_KEY, LA4::LASETTINGS_CURRENT_CONF_VERSION);

			/* Disable autosave of course */
			DisableAutosave();

			/* Retreive values */
			emit GetDefaultValues();

			/* Hopefully, we now have the values as signals are synchronous calls */

			/* Now reenable autosaving which will trigger a synchronisation */
			saveSettings();

#ifdef DEBUG
			qDebug("LASettings::ConfigureApplication: No existing configuration. Default settings have been applied.");
#endif /* DEBUG */

		}

}

QString LASettings::GetValue(QString key)
{

	QString retVal = "";		
	if (key != "")
		{
			/* As Qt will return an empty string if the key does not exist 
			 * there is no more things to do.
			 */
			retVal = m_preferences.value(key).toString();
		}
	return retVal;

}

void LASettings::SetValue(const QString & key, const QString & value)
{

	if (key != "")
		{
			/* Empty values are removed */
			if (value != "")
				{
					m_preferences.setValue(key, value);
				}
			else
				{
					m_preferences.remove(key);
				}

			/* Save value if autosave is enabled */
			if (m_autosaveActivated)
			{
				saveSettings();
			}

		}

}

/************************************************************* Public slots */
void LASettings::DisableAutosave()
{
	m_autosaveActivated = false;
}

void LASettings::EnableAutosave()
{
	m_autosaveActivated = true;
	/* This trigger a setting save in any case */
	saveSettings();
}

/******************************************************** Protected methods */
void LASettings::loadSettings()
{
	/* Just synchronise data */
	m_preferences.sync();
}

void LASettings::saveSettings()
{
	/* Just synchronise data */
	m_preferences.sync();
}
