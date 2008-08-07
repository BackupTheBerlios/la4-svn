/******************************************************************************
 * main.cpp                                                                   *
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

/* Qt includes */
#include <QApplication>
#include <QtGui>
#include <QTranslator>

/* LA4 includes */
#include "LA4Namespace.h"
#include "LAPlatformManager.h"
#include "LAProject.h"
#include "LASettings.h"

/* Debugging levels */
#undef DEBUG

int main(int argc, char *argv[])
{
  int returnCode = -1;

  QApplication app(argc, argv);

  /* i18n handling */
  QLocale currentLocale;
  QString language = currentLocale.name();
  language.truncate(2); /* Keep only the two first letters */

#ifdef DEBUG
  qDebug("main(): Language is " + language);
#endif /* DEBUG */
	
  /* Translation file for Qt */
  QTranslator qt(0);
  if (qt.load(QString("i18n/") + language + QString("/qt_") + language, "."))
    {
      app.installTranslator(&qt);
    }
  else
    {
#ifdef DEBUG
      qDebug("main(): File for qt strings in language " + language + " not found.");
#endif /* DEBUG */
    }

  /* Translation file for la4 strings */
  QTranslator la4app(0);  
  if (la4app.load(QString("i18n/") + language + QString("/la4_") + language, "."))
    {
      app.installTranslator(&la4app);
    }
  else
    {
#ifdef DEBUG
      qDebug("main(): File for la4 strings in language" + language + " not found, you should perhaps rerun lrelease.");
#endif /* DEBUG */
        }

  /* Configure the application */
  LA4_Global_Settings.ConfigureApplication();
  app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

  /* Load platforms */
  LAPlatformManager::Load(LA4::SettingValue(LA4::PLATFORMS_PATH_KEY));

  /* Start project */
  LAProject::LAProjectMode mode = LAProject::NEW_PROJECT;
  LAProject* theMainProject = new LAProject();
  if (theMainProject->StartProject(mode, ""))
    {
      /* Execute the application */
      returnCode = app.exec();
    }

  /* Delete the project */
  delete theMainProject;

  /* Delete the platform manager */
  LAPlatformManager::clearPlatforms();

  return returnCode;

}
