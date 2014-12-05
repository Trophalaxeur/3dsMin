/*!
  \file projet3D.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief code du main
  \date 13/05/2008
  \version 1.0
*/

#include "projet3D.hpp"

void terminate (int int_param)
{
	cout << endl << endl;
	cout << "Une erreur inconnue est arrivé ( code : " << int_param << " )" << endl;
	cout << "Processus de fin de programme..." << endl;
	delete window;
	cout << "Processus de fin de programme... terminé" << endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
	//Structure action du signal
	struct sigaction action;
	//Définition de la fonction appelé en cas de récupération du signal
	action.sa_handler=terminate;
	//Récupération des signaux de seg fault
	sigaction(SIGSEGV, &action, NULL);
  
	//Nom du fichier à charger
	string str_file;
	
	//Initialisation de Qt
	Q_INIT_RESOURCE(basicdrawing);	

	//Initialisation de l'application Qt
	QApplication app(argc, argv);


	//Création de la fenetre
	window=new Window;
	cout << "fenetre : " << window << endl;

	//Affichage de la fenetre
	window->show();

	//Exécution de l'application
	return(app.exec());
}
