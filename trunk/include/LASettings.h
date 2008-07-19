/******************************************************************************
 * LASettings.h                                                               *
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

#ifndef LA_SETTINGS_H_
#define LA_SETTINGS_H_

/* Qt includes */
#include <QSettings>
#include <QVariant>

/* LA4 includes */

/* Forward declarations */

/*!
 * This class is responsible of the LA4 application settings.
 * 
 * It should NOT be used directly. All classes that need to
 * handle settings value should use the functions defined
 * in the namespace class to ensure independence between
 * this class and the rest of the application.
 * 
 * It should also be noted that LASettings is a customized
 * frontend to a QSettings object. Using a QSettings object
 * outside this class should not be done except if settings
 * are not meant to be associated to this application. This
 * class does only support string values contrary to QSettings
 * to avoid the use of the (too here) powerful mechanism
 * of QVariant. This design decision may be taken out in the
 * future.
 * 
 * Each setting is a QString value that is associated to a
 * unique key. The classes using a setting should ensure that
 * the key is unique and not used by others.
 * 
 * Only one method is allowed to use it directly: main() because
 * it will know the execution path that is needed for initial
 * configuration and only one class for now may use it as well: the
 * option dialog class.
 * 
 * The name of the setting file is hardcoded (as a const) in
 * the LA4Namespace class and may therefore not be changed unless
 * the application is recompiled. The setting file is saved 
 * by default under the home directory. For more information
 * about the exact filename and directory that will be used,
 * see LA4Namespace.
 * 
 * This class must not be instantiated by any other class of the
 * application as it handles global information.
 * 
 * If the configuration file does not exist, defaults values are
 * set. As the actual keys should not be known by this class (QA),
 * it "asks" for the default values by sending a GetDefaultValues()
 * signal. During the retreiving of the default values, a temporary
 * value associated with the key LA4::LA4_BIN_DIR_KEY is accessible for 
 * the classes that may need it to compute a default value. This
 * value contains the execution path of the LA4 executable.
 * 
 * Setting a value to a key triggers by default an saving (sync in
 * QSettings language) of the setting file. This default behavior 
 * provides a light-weight mechanism that could be used by any 
 * class to set a single value.
 */
class LASettings : public QObject
{

	Q_OBJECT	

  	/************************************************** Constructors/Destructor */
public:
	/*!
	 * Default constructor
	 */
	LASettings();

	/*!
	 * Default destructor
	 */
	virtual ~LASettings();

	/*********************************************************** Public methods */
public:
	/*!
	 * Configures the application.
	 * 
	 * If the preference file is not valid (version not set), this
	 * method asks for default values. The default values and keys are provided
	 * by answering to the GetDefaultValues() signal that is
	 * emitted by this method. The method then stores the preferences.
	 * 
	 * If the preference file is valid, it simply loads it.
	 * 
	 * It should be noted that this method empties ALL preceeding
	 * value/key pairs that may have been set before setting default
	 * values if the file does not exist.
	 * 
	 * As this class delegates the storing of the values to Qt, there
	 * is no mean to know if it actually work. However, it can be trusted
	 * that all went right. If not, the application settings will have at each
	 * startup the default values.
	 */
	void ConfigureApplication();

	/*!
	 * Returns the value associated to a key.
	 * 
	 * If the key does not exist in the database, then an empty value
	 * is returned. Removing a key is in consequence achieved
	 * by setting an empty value associated to this key.
	 * 
	 * The key "" will always return "".
	 * 
	 * This method is not meant to return NULL at any moment.
	 * 
	 * \param key Key of the value that should be retreived.
	 */
	QString GetValue(QString key);

	/*!
	 * Sets the value associated to the given key.
	 * 
	 * This class uses only strings to represent values.
	 * 
	 * The value can then be retreived when needed by using the key
	 * with the GetValue method.
	 * 
	 * When the key does not exist, the key/value pair is added in
	 * the setting database.
	 * 
	 * The key "" can not be associated to a value. Any attempt
	 * will be silently discarded and will not trigger any database
	 * update.
	 * 
	 * The key LA4::LASETTINGS_VERSION_KEY is reserved and no
	 * value can be set to it by using this method.
	 * 
	 * Using this function triggers a save of the complete database
	 * of settings unless the disableAutosave() slot has been activated.
	 * The save is then postponed to the next enableAutosave() slot call.
	 * 
	 * Setting an empty ("") value to a key removes the key from the
	 * database. It has no consequence as GetValue will return ""
	 * on non-existing keys.
	 * 
	 * \param key Key associated to the value
	 * \param value Value associated to the key
	 */
	void SetValue(const QString & key, const QString & value);

  	/************************************************************* Public slots */
public slots:
	/*!
	 * Disables the automatic saving of settings when they are set.
	 * 
	 * The EnableAutosave() slot must then be called to save the setting
	 * if they must be kept.
	 * 
	 * Note that autosave is enabled by default.
	 */
	void DisableAutosave();

	/*!
	 * Enables the automatic saving of settings when they are set.
	 * 
	 * Calling this slot WILL trigger a saving of the preferences.
	 * 
	 * Note that autosave is enabled by default.
	 */
	void EnableAutosave();

  	/****************************************************************** Signals */
signals:
	/*!
	 * Emitted to ask for default values
	 */
	 void GetDefaultValues();

	/******************************************************** Protected methods */
protected:
	/*!
	 * Load settings from the setting file.
	 */
	void loadSettings();

	/*!
	 * Saves settings to the setting file.
	 */
	void saveSettings();

	/******************************************************** Protected members */
protected:
	/*! Used to determine if a set value should trigger a saving into file or not */
	bool m_autosaveActivated;

	/*! QSettings containing all preferences */
	QSettings m_preferences;

};

/*! Global instance */
extern LASettings LA4_Global_Settings;

#endif /* LA_SETTINGS_H_ */
