/******************************************************************************
 * LAProject.cpp                                                              *
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

#include "LAProject.h"

/* Qt includes */

/* LA4 includes */
#include "LA4Namespace.h"
#include "LACATRE_Plugin.h"
#include "LALogger.h"
#include "LAStartDialog.h"
#include "LAWindow.h"

/************************************************** Constructors/Destructor */
LAProject::LAProject() :
  m_document        (this),
  m_projectWindow   (NULL)
{
  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}

LAProject::~LAProject()
{
  if (m_projectWindow)
    {
      delete m_projectWindow;
    }

  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/*********************************************************** Public methods */
bool LAProject::StartProject(LAProjectMode aMode, QString aFilename)
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  bool projectStarted = false;

  bool tryToStartProject = false;

  /* If a window already exists, destroy it! */
  /* Should never happen */
  if (NULL != m_projectWindow)
    {
      /*! The window should not exist at all */
      qWarning("LAProject::StartProject: WARNING: Creating a project with an existing window");
      delete m_projectWindow;
    }

  /* Create window */
  /* Toolbars, menu and view are initialised during this creation */
  m_projectWindow = new LAWindow();

  /* Create welcome dialog */
  LAStartDialog startDialog;

  /* Retreive the load plugin */
  LACATRE_Plugin* loadfilePlugin = LACATRE_PluginPool::getInstance()->plugin(LA4::PLUGIN_LOAD_FILE);
  if (NULL != loadfilePlugin)
    {
      m_loadfilePlugin = loadfilePlugin->Clone(&m_document);
    }
  else
    {
      /* Desactivate the load button if we didn't find a load plugin */
      LALogger::Trace(LALogger::WARNING,
                      LALogger::MAIN,
                      "No load file plugin. Loading deactivated",
                      LA_DEBUG_ARGS);
      startDialog.m_ui.PushButtonBrowze->setEnabled(false);
    }

  LALogger::Trace(LALogger::DEBUG,
                  LALogger::MAIN,
                  "Initialisation of project",
                  LA_DEBUG_ARGS);

  /* If we must load a file, ask it to the user */
  if (EXISTING_FILE == aMode && "" == aFilename)
    {
      startDialog.openBrowseDialog();
      tryToStartProject = !startDialog.m_ui.filenamePath->text().isEmpty();
    }
  /* If the filename has been given, we do as if the user had selected the file */
  else if (EXISTING_FILE == aMode && !aFilename.isEmpty())
    {
      startDialog.m_ui.RadioButtonOpen->setChecked(true);
      startDialog.m_ui.filenamePath->setText(aFilename);
      tryToStartProject = true;
    }
  /* Execute the dialog if necessary */
  else if (NEW_PROJECT == aMode)
    {
      /* Show the dialog before to initialise the list */
      startDialog.show();
      tryToStartProject = startDialog.exec();
    }

  /* If the project must be started */
  if (true == tryToStartProject)
    {
			/* If we didn't find the appropriate plugins, we quit this window */
			if (m_projectWindow->connectPlugins() < 0)
				{
					projectStarted = false;
				}
			else
        {
          m_projectWindow->move(0,0);
          m_projectWindow->resize(800,600);
          m_projectWindow->show();

					/* Load file */
					if (startDialog.m_ui.RadioButtonOpen->isChecked())
						{
              LALogger::Trace(LALogger::DEBUG,
                              LALogger::MAIN,
                              QString("Loading a project from file %1").arg(startDialog.m_ui.filenamePath->text()),
                              LA_DEBUG_ARGS);

							m_document.setDocumentFileName(startDialog.m_ui.filenamePath->text());
						}
					else /* New project with selected platform */
						{
              LALogger::Trace(LALogger::DEBUG,
                              LALogger::MAIN,
                              QString("Starting an empty project for target %1").arg(startDialog.m_ui.PlatformList->currentText()),
                              LA_DEBUG_ARGS);

							m_document.setTargetPlatform(startDialog.m_ui.PlatformList->currentText());
						}

          projectStarted = true;
        }
    }
  else
    {
      /* The user cancelled the dialog */
      projectStarted = false;
    }

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  /* Clean and return result */
  return projectStarted;
}
