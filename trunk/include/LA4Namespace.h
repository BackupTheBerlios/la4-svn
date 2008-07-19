/******************************************************************************
 * LA4Namespace.h                                                             *
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

#ifndef LA4_NAMESPACE_H_
#define LA4_NAMESPACE_H_

/* Qt include */
#include "QString"

/*!
 * This namespace is used to ensure a global reference is shared between the
 * plugins an the whole application.
 *
 * It defines enums for the plugin actions. It ensures that all plugins and
 * LAWindow, LAProject can talk correctly without errors.
 *
 * It defines also the setting keys and the function to access the settings.
 * If you have to access the settings, use this function instead of importing
 * directly LASettings. It ensures a unique definition of the keys (those keys
 * will be "checked" at compilation time) and a unique access point independant
 * of the way the settings are stored or managed. This namespace avoids too the
 * inclusion of an interface (LASettings.h) that can be changed without 
 * affecting the other files. On the other hand, if one setting is added, all
 * plugins and files using the namespace will be compiled again. If you 
 * implement an option dialog, you must for the moment include directly
 * LASettings.h
 *
 * If you add a setting key, don't forget to describe it.
 *
 */

namespace LA4 {

    /*! Plugin names
     ***************/

    /*! Code generator plugin name */
    const QString PLUGIN_CODE_GENERATOR = "codegenerator";

    /*! LAkernel plugin name */
    const QString PLUGIN_LAKERNEL = "lakernel";

    /*! Load file plugin name */
    const QString PLUGIN_LOAD_FILE = "loadfile";

    /*! Print plugin name */
    const QString PLUGIN_PRINT = "print";

    /*! Save file plugin name */
    const QString PLUGIN_SAVE_FILE = "savefile";

    /*! Undo plugin name */
    const QString PLUGIN_UNDO = "undo";

    /*!
     * Plugin action definitions
     **************************/

    /*! General plugin actions
     */
    enum PluginAction {
        DefaultAction = 0
    };

    /*! Actions for Load plugin */
    enum LoadPluginAction {
        Load = 0         /* Load is default */
    };

    /*! Actions for Save plugin */
    enum SavePluginAction {
        Save = 0,        /* Save is default */
        SaveAs = 1       /* Save as */
    };

    /*! Actions for LAkernel plugin */
    enum LAKernelPluginAction {
        Init = 0,        /* Init the plugin = default */
        ZoomIn = 1,      /* Zoom in the view */
        ZoomOut = 2,     /* Zoom out the view */
        ChangeZoomTo = 3 /* Set a zoom, param = percentage */
    };

    /*! Actions for Print plugin */
    enum PrintPluginAction {
        Print = 0,       /* Print is default */
        SetupPrinter = 1 /* Setup printer */
    };

    /*! Actions for undo plugin */
    enum UndoPluginAction {
        Undo = 0, /* Undo is default */
        Redo = 1, /* Redo */
        Clear = 2 /* Clear stacks */
    };

    /*! Undo commands */
    enum UndoCommands {
        NoAction = 0,    /* Dummy command ID */
        SelectObject = 1 /* Selection of an object */
    };

    /*! Used in preferences values to denote a false value */
    const QString FALSE_STRING = "false";

    /*! Used in preferences values to denote a true value */
    const QString TRUE_STRING = "true";

    /*!
     * Setting keys and default values
     *********************************/
    /*! Alphabetically ordered! */
    /* ======================== */

    /*! Option defining the way the backup of the file is achieved. */
    const QString BACKUP_FILE_SAVING_OPTION_KEY = "fileBackup";
    /*! Possible values of the backup file saving preference */
    const QString BACKUP_NO_SAVE = "noSave";
    const QString BACKUP_REPLACE_EXTENSION = "replaceExtension";
    const QString BACKUP_ADD_EXTENSION = "addExtension";
    /*! Default is no save */
    const QString BACKUP_FILE_SAVING_OPTION_DEFAULT_VALUE = BACKUP_NO_SAVE;

    /*! When we have to open a file, this folder will be the
     * default one. */
    const QString DEFAULT_OPEN_PATH_KEY = "openPath";

    /*! When we have to save a file, this folder will be the
     * default one. */
    const QString DEFAULT_SAVE_PATH_KEY = "savePath";

    /*! Option indicating if the toolbar is to be displayed */
    const QString DISPLAY_TOOLS_KEY = "displayTools";
    /*! Default is true */
    const QString DISPLAY_TOOLS_DEFAULT_VALUE = TRUE_STRING;

    /*! Option indicating if the status bar is to be displayed */
    const QString DISPLAY_STATUS_BAR_KEY = "displayStatusBar";
    /*! Default is true */
    const QString DISPLAY_STATUS_BAR_DEFAULT_VALUE = TRUE_STRING;

    /*! Option indicating if tips should be displayed */
    const QString DISPLAY_STATUS_TIPS_KEY = "displayTips";
    /*! Default is true */
    const QString DISPLAY_STATUS_TIPS_DEFAULT_VALUE = TRUE_STRING;

    /*! Recent files maximum number */
    const QString MAX_RECENT_FILES_COUNT_KEY = "numberOfRecentFile";
    /*! Default is 5 */
    const QString MAX_RECENT_FILES_COUNT_DEFAULT_VALUE = "5";

    /*! Recent files base key
     * A number is appened to this prefix to compute recent files keys
     */
    const QString RECENT_FILES_PREFIX_KEY = "recentFile";

    /*! Interval between two consecutive security save (in minutes) */
    const QString SECURITY_SAVE_INTERVAL_KEY = "securitySaveInterval";
    /*! Default is 5 minutes */
    const QString SECURITY_SAVE_INTERVAL_DEFAULT_VALUE = "5";

    /*! Security save path. Regular backups are to be saved here */
    const QString SECURITY_SAVE_PATH_KEY = "securitySavePath";

    /*!
     * Stencils definitions will be found in this path
     * Typically, this path is PATH_TO_LA4/xmldefs, but can
     * be changed by the user.
     */
    const QString STENCILS_PATH_KEY = "stencilsPath";
    /*! This is the default subdirectory for XML definitions */
    const QString STENCILS_DEFAULT_DIRECTORY = "xmldefs"; 

    /*!
     * Preference/Setting file naming
     *******************************/

    /*! Default directory for preference (setting) file under Unix */
     const QString PREFERENCE_DEFAULT_UNIX_PATH = ".LA4";

    /*! LA4 product name */
    /* This value should not be changed as it serves as identifiers in settings */
    const QString LA4_PRODUCT_NAME = "LA4";

    /*! LA4 organisation name */
    /* This value should not be changed as it serves as identifiers in settings */
    const QString LA4_ORGANISATION_NAME = "LA4 team";

    /*! Key used to store the setting version */
    /*! May be used if key names evolve */
    const QString LASETTINGS_VERSION_KEY = "ConfigurationFileVersion";

    /*! Current configuration file version */
    const QString LASETTINGS_CURRENT_CONF_VERSION = "1";

    /*!
     * Setting function declarations
     *******************************/
    /*! Returns the value of the setting <key> */
    QString SettingValue(const QString key);

};

#endif /* LA4_NAMESPACE_H_ */
