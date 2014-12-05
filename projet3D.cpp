/*!
  \file projet3D.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief code du main
  \date 13/05/2008
  \version 1.0
*/

#include "projet3D.hpp"

int main(int argc, char** argv)
{
	
	//Nom du fichier à charger
	string str_file;
	
	//Initialisation de Qt
	Q_INIT_RESOURCE(basicdrawing);	

	//Initialisation de l'application Qt
	QApplication app(argc, argv);


	//Création de la fenetre
	Window window;

	//Affichage de la fenetre
	window.show();

	//Exécution de l'application
	return(app.exec());
}
