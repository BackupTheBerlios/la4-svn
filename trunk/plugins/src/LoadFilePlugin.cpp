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
 * Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

//qt includes
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfile.h>

//lacatre includes
#include "LACATRE_Plugin.h"
#include "LACATRE_PluginPool.h"

//other includes
#include "LoadFilePlugin.h"
#include "LA4Namespace.h"

#undef DEBUG

static LoadFilePlugin p;

LoadFilePlugin::LoadFilePlugin() : LACATRE_Plugin(LACATRE_PluginPool::WRITE, LA4::PLUGIN_LOAD_FILE)
{
	localDoc = NULL;
}


LoadFilePlugin::~LoadFilePlugin()
{
// 	if (localDoc)
// 		delete localDoc;
}


LoadFilePlugin::LoadFilePlugin(const LoadFilePlugin& p ):LACATRE_Plugin(p)
{
	localDoc = NULL;
}


LACATRE_Plugin *LoadFilePlugin::Clone(LACATRE_Doc * d)
{
    (void)d;
    LACATRE_Plugin * nP = new LoadFilePlugin(*this);
// 	nP->SetDoc(d);
// 	QObject::connect(nP, SIGNAL(modified(LACATRE_Plugin *)), d , SLOT(modified(LACATRE_Plugin *)));

    return nP;
}


QWidget * LoadFilePlugin::Action(QWidget *w, int ActionType, const char * parameter)
{
	(void)ActionType;
	(void)w;
	(void)parameter;

// 	#ifdef DEBUG
// 	qDebug("LoadFilePlugin : Action.");
// 	#endif

// 	if (!(doc->getDocumentFileName().isEmpty()))
// 	{
// 		fileName = doc->getDocumentFileName();

// 		#ifdef DEBUG
// 		qDebug("LoadFilePlugin : Loading directly the file " + fileName);
// 		#endif

// 		loadDoc(fileName);
// 	}
// 	else
// 	{
// 		fileName = QFileDialog::getOpenFileName(LA4::SettingValue(LA4::KEY_DEFAULT_OPEN_PATH),
// 																						QWidget::tr("La4 project file(*.la4)"));
// 		if ( !fileName.isNull() )
// 		{
// 			#ifdef DEBUG
// 			qDebug("LoadFilePlugin : Loading the file " + fileName);
// 			#endif

// 			loadDoc(fileName);
// 		}
// 	}

	return NULL;
}


int LoadFilePlugin::loadDoc(const QString & fileName)
{
    (void)fileName;
// 	if (localDoc)
// 		delete localDoc;

// 	localDoc = new QDomDocument("ala");

// 	QFile fileD( fileName );

// 	if ( !fileD.open( IO_ReadOnly ) )
// 	{
// 		QMessageBox::warning( NULL, "La4",
// 			QWidget::tr("Unable to open file %1.\nThe file is unreadable, does not exist, or you do not have the permission to open it. Loading aborted.\n").arg(fileName) );
// 		return -1;
// 	}

// 	if(!(localDoc->setContent(&fileD)))
// 	{
// 		QMessageBox::warning( NULL, "La4", QWidget::tr("Unable to load project %1.\nThe file is corrupted, or does not contain a valid XML document. \nPlease note that this program is unable to load files from the old (Win 3.1) version of La4.\nLoading aborted.\n").arg(fileName) );
// 		fileD.close();
// 		return -1;
// 	}

// 	fileD.close();

// 	/* Version checking */
// 	/* If the file has no version, it means it was made with a version inferior to 0.9.3, we should add a LA4Model node and warn the user */
// 	if (localDoc->documentElement().attribute("version", "noversion") == "noversion")
// 		{
//  			QMessageBox::warning( 0, "LA4", QWidget::tr("<p align=\"justify\">The document seems to have been created with an earlier version of LA4 (&lt; 0.9.4).</p>"
//  																									+ QString("<p align=\"justify\">It will be automatically converted to the new format. If you save it, it will not be readable by version of LA4 earlier than 0.9.4</p>")
// 																									+ QString("<p align=\"justify\"><b>Important:</b> For now, layer conversion is not functional and you will need to do some operations manually if your file is using layers. Indeed, an object and its connectors should be on the same layer. You will need to import each object to the right layer if you want to add connectors.</p>") ));

// 			/* Change version */
// 			localDoc->documentElement().setAttribute("version", "1.0");

// 			/* We put all the elements in the root element into a new LA4Model element */
// 			/* \todo We should perhaps check that this node does not exist */
// 			QDomElement modelElement = localDoc->createElement("LA4Model");

// 			/* Search for last ID used. This is useful to reattribute ID's to objects that do not have one (connectors for example) */
// 			QDomNode node = localDoc->documentElement().firstChild();
// 			QDomElement element;
// 			int objectID;
// 			int maxID = 0;
// 			while (!node.isNull())
// 				{
// 					if (node.isElement())
// 						{
// 							element = node.toElement();
// 							bool ok;
// 							/* If the ID of the object is not a valid int, we set it to -1 so that it will be renumbered */
// 							objectID = element.attribute("ID").toInt(&ok);
// 							if (!ok)
// 								{
// 									objectID = -1;
// 									element.setAttribute("ID", "-1");
// 								}
// 							if (objectID > maxID) /* maxID = max(objectID, maxID) */
// 								{
// 									maxID = objectID;
// 								}
// 						}
// 					node = node.nextSibling();
// 				}

// #ifdef DEBUG
// 			qDebug("LoadFilePlugin: maxID = %d", maxID);
// #endif /* DEBUG */

// 			/* Take each element and add layers accordingly */
// 			QDict<QDomElement> layersElements;
// 			QString layerName;
// 			int count = 0;
// 			QDomElement layerElement;
// 			while (!localDoc->documentElement().firstChild().isNull())
// 				{

// 					node = localDoc->documentElement().firstChild();
// 					if (node.isElement())
// 						{
// 							element = node.toElement();
// 							objectID = element.attribute("ID").toInt();
// 							if (objectID < 1) /* ID's of objects are for now always strictly superior to 0 */
// 								{
// 									maxID++;
// 									objectID = maxID;
// 									element.setAttribute("ID", objectID);
// 								}
// 							layerName = element.attribute("layer");

// #ifdef DEBUG
// 							qDebug("LoadFilePlugin: New object, ID is %d, layer name is " + layerName, objectID);
// #endif /* DEBUG */

// 							/* If layer already exists */
// 							if (layersElements.find(layerName) != 0)
// 								{
// 									layerElement = *(layersElements.find(layerName));

// #ifdef DEBUG
// 									qDebug("LoadFilePlugin: Layer exists: " + layerName);
// #endif /* DEBUG */

// 								}
// 							else
// 								{
// 									layerElement = localDoc->createElement("Layer");
// 									layerElement.setAttribute("name", layerName);
// 									layerElement.setAttribute("ID", count);
// 									count++;
// 									layersElements.insert(layerName, &layerElement);
// 									modelElement.appendChild(layerElement);

// #ifdef DEBUG
// 									qDebug("LoadFilePlugin: New layer: " + layerName);
// #endif /* DEBUG */

// 								}
// 							/* Add this stencil to the layer */
// 							QDomNode thisNode = layerElement.firstChild();
// 							bool found = false;
// 							while(!thisNode.isNull())
// 								{
// 									if (thisNode.isElement())
// 										{
// 											QDomElement thisElement = thisNode.toElement();
// 											if (thisElement.attribute("ID").toInt() == objectID)
// 												{
// 													found = true;

// #ifdef DEBUG
// 													qDebug("LoadFilePlugin: Stencil %d was found. Nothing to do." + layerName, objectID);
// #endif /* DEBUG */

// 												}
// 										}
// 									thisNode = thisNode.nextSibling();
// 								}
// 							if (!found)
// 								{
// 									QDomElement stencilElement = localDoc->createElement("StencilReference");
// 									stencilElement.setAttribute("ID", objectID);
// 									layerElement.appendChild(stencilElement);

// #ifdef DEBUG
// 									qDebug("LoadFilePlugin: Stencil %d was not found, we add it to " + layerName, objectID);
// #endif /* DEBUG */

// 						}

// 							/* If it is a connector, add its ends to the layer too */
// 							/* \todo This is not implemented for now, because of child/parent relationship */

// 						}

// 					/* Change nodes parent and remove layer information on element */
// 					element.removeAttribute("layer");
// 					localDoc->documentElement().removeChild(node);
// 					modelElement.appendChild(node);
// 				}

// 			/* Finally add the element to the doc */
// 			localDoc->documentElement().appendChild(modelElement);

// 		} /* End of if "noversion" = LA4 files < 0.9.3 */

// 	emit modified(this);

	return 0;
}


void LoadFilePlugin::UpdateDocument(QDomDocument & d)
{
    (void)d;
	//XXX ugh! ugly!!
// 	d.setContent(localDoc->toString());
// 	doc->setDocumentFileName(fileName);
}
