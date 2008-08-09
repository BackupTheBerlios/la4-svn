/******************************************************************************
 * LoadFilePlugin.cpp                                                         *
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

#include "LoadFilePlugin.h"

/* Qt includes */
#include <QFile>
#include <QMessageBox>

/* LA4 includes */
#include "LA4Namespace.h"
#include "LACATRE_Plugin.h"
#include "LACATRE_PluginPool.h"
#include "LALogger.h"

/*! Static instance of the plugin */
static LoadFilePlugin LOAD_FILE_PLUGIN_GLOBAL_INSTANCE;

const char* LoadFilePlugin::XML_VERSION_TAG = "version";

/************************************************** Constructors/Destructor */
LoadFilePlugin::LoadFilePlugin() :
  LACATRE_Plugin (LACATRE_PluginPool::WRITE, LA4::PLUGIN_LOAD_FILE),
  m_fileName     (""),
  m_localDocument(NULL)
{
  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}


LoadFilePlugin::~LoadFilePlugin()
{
  /* If document is NULL, delete will not hurt */
  delete m_localDocument;

  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/*********************************************************** Public methods */
LACATRE_Plugin *LoadFilePlugin::Clone(LACATRE_Doc* aDocument)
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  /* Create the new plugin */
  LACATRE_Plugin * newPlugin = new LoadFilePlugin(*this, aDocument);

  /* Nothing else to do here */

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  return newPlugin;
}

void LoadFilePlugin::UpdateDocument()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  LALogger::Trace(LALogger::ERROR,
                  LALogger::MAIN,
                  "NOT IMPLEMENTED",
                  LA_DEBUG_ARGS);

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

/************************************************************* Public slots */
QWidget* LoadFilePlugin::Action(QWidget*    aParentWidget,
                                int         aAction,
                                const char* aParameter)
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  /* We do not need the widget and the parameters at all here */
  (void)aParentWidget;
  (void)aParameter;

  /* Load action */
  if (LA4::Load == aAction)
    {
      /* If document has no filename */
      if (m_doc->getDocumentFileName().isEmpty())
        {
          /* Ask the user to provide one */
          LALogger::Trace(LALogger::ERROR,
                          LALogger::MAIN,
                          "User must provide a filename: NOT IMPLEMENTED",
                          LA_DEBUG_ARGS);
        }

      /* If the document has a filename associated to it */
      if (!(m_doc->getDocumentFileName().isEmpty()))
        {
          /* Keep filename */
          m_fileName = m_doc->getDocumentFileName();

          LALogger::Trace(LALogger::DEBUG,
                          LALogger::MAIN,
                          "Loading file " + m_fileName,
                          LA_DEBUG_ARGS);

          /* Load document now */
          loadDoc();
        }
    }
  else
    {
      LALogger::Trace(LALogger::ERROR,
                      LALogger::MAIN,
                      QString("Action not supported by plugin (%1)").arg(aAction),
                      LA_DEBUG_ARGS);
    }

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  return NULL;
}

/******************************************************** Protected methods */
LoadFilePlugin::LoadFilePlugin(const LoadFilePlugin& aPlugin, LACATRE_Doc * aDocument) :
  LACATRE_Plugin (aPlugin, aDocument),
  m_fileName     (""),
  m_localDocument(NULL)
{
  /* The copy constructor does not copy anything from original plugin      */
  /* The Clone() function is responsible for the copy of needed attributes */
  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}

int LoadFilePlugin::loadDoc()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  int success = 0;

  /* Delete old document, if it existed */
  /* There is no problem doing so as this plugin will not update the document */
  /* elsewhere and the modified() signal is not fired anywhere else           */
  if (NULL != m_localDocument)
    {
      delete m_localDocument;
    }

  /* Create XML document */
	m_localDocument = new QDomDocument("LA4Document");

  /* Try to open file */
	QFile fileDescriptor(m_fileName);
	if (!fileDescriptor.open(QIODevice::ReadOnly))
    {
      QMessageBox::warning(NULL,
                            "LA4",
                            QWidget::tr("Unable to open file %1.\nThe file is unreadable, does not exist, or you do not have the permission to open it. Loading aborted.\n").arg(m_fileName));
      success = -1;
    }

  /* If the file is opened, we can set content to document */
	if (0 == success && 
      !(m_localDocument->setContent(&fileDescriptor)))
    {
      QMessageBox::warning(NULL,
                           "LA4",
                           QWidget::tr("Unable to load project %1.\nThe file is corrupted, or does not contain a valid XML document. \nPlease note that this program is unable to load files from the old (Win 3.1) version of LA4.\nLoading aborted.\n").arg(m_fileName));
      /* Reset document */
      m_localDocument->clear();
      success = -1;
    }
	fileDescriptor.close();

  /* If file was loaded */
	if (0 == success)
    {
      /* Version checking */
      /* If the file has no version, it means it was made */
      /* with a version inferior to 0.9.3,                */
      if ("noversion" == m_localDocument->documentElement().attribute(XML_VERSION_TAG, "noversion"))
        {
          /* For now, we do nothing here */
          LALogger::Trace(LALogger::ERROR,
                          LALogger::MAIN,
                          "File version not specified, conversion from older files NOT IMPLEMENTED",
                          LA_DEBUG_ARGS);

          /* Warn the user */
          QMessageBox::warning(0,
                               "LA4",
                               QWidget::tr("<p align=\"justify\">The document seems to have been created with an earlier version of LA4 (&lt;&nbsp;0.9.4).</p><p align=\"justify\">Conversion is not functional for now. Wait for further development of the program or redo your document from beginning. Sorry.</p>"));

        }
      else
        {
          /* The version is good */
          LALogger::Trace(LALogger::DEBUG,
                          LALogger::MAIN,
                          "Loading file from XML tree",
                          LA_DEBUG_ARGS);
        }

      /* The document has been modified */
      emit modified(this);

    }

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  return success;
}
