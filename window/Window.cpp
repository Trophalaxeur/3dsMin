/*!
  \file Window.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief 
  \date 13/05/2008
  \version 1.0
*/

#include "Window.hpp"

Window::Window() : QWidget()
{
	//On définit le titre de la fenètre
	setWindowTitle(tr("3dSMin"));
	
	//initialisation d'area_view à NULL	ce dernier sera redéfini lors du chargement
	area_view=NULL;	
	
	//Création et paramètrage du mainLayout qui est une grille de Widget 
	//dont la taille varie en fonction de al taille de la fenètre
	Window_param_mainLayout();
	
	//on créer et affiche l'interface général du bouton (ex: bouton a propos)
	Window_interface_general();
  	
	//on créer le panneau objet
	Window_panneau_objet();
	
	//on créer le panneau lumière
	Window_panneau_lumiere();
  	
  	//On désactive les panneau objet et lumière (les explications sont données dans la fonction
  	Window_desactive_panneaux();
	
	//Il nous faut maintenant connecter les signaux pour que les boutons puissent lancer des méthodes
	//Connection des signaux avec les slots
	//dans cette fonction on retrouve les signaux qui doivent être reconnectés à chaque chargement
	connect_signaux_scene();

	//fenètre a propos de Qt	
	QObject::connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));		
	//Lorsqu'on click sur "Charger"
	QObject::connect(actionCharger, SIGNAL(triggered()),this, SLOT(charger()));
	//Lorsqu'on click sur "Sauvegarder"
	QObject::connect(actionSauvegarder, SIGNAL(triggered()),this, SLOT(dialog_save_object()));
	//Lorsqu'on click sur "Aide"
	QObject::connect(actionHelp, SIGNAL(triggered()),this, SLOT(dialog_help()));
	//Lorsqu'on click sur "A propos de nous"
	QObject::connect(actionAbout_us, SIGNAL(triggered()), this, SLOT(dialog_about()));
	//Lorsqu'on click sur "Adoucir"
	QObject::connect(actionAdoucir, SIGNAL(triggered()),this, SLOT(dialog_polish()));
	//Lorsqu'on click sur "Subdiviser"
	QObject::connect(actionSubdiviser, SIGNAL(triggered()),this, SLOT(dialog_subdivide()));
	//Lorsqu'on click sur "Peindre"
	QObject::connect(actionPeindre, SIGNAL(triggered()),this, SLOT(dialog_paint_object()));
	//Lorsqu'on click sur "Infos objets"
	QObject::connect(actionInfoObjet, SIGNAL(triggered()),this, SLOT(dialog_info_object()));
}

void Window::Window_panneau_objet()
{
	/* On crée ici toute l'interface pour la manipulation d'un objet
  	 * Il permet :
  	 * 	la rotation
  	 * 	le zoom
  	 * 	le chargement
  	 * la modification du rendu
  	 */
  	
  	
  	//////////////////// BOUTON ////////////////////
    
    //création du bouton reset
  	bt_raz = new QPushButton("Reset", this);

    
    //////////////////// LABEL //////////////////////
    
    //Création des encadrés de texte
    lab_r = new QLabel("Zoom :",this);
    lab_theta = new QLabel("Theta",this);
    lab_phi = new QLabel("Phi",this);    
    
    //Création de la légende pour le slide de  theta
    lab_0_1 = new QLabel("0",this);
    lab_180_1 = new QLabel("180",this);
    lab_moins_180_1 = new QLabel("-180",this);   
    //modification de la la taille et du style de police de la légende de théta
    lab_0_1->setFont(QFont("Comic Sans MS", 6));
    lab_180_1->setFont(QFont("Comic Sans MS", 6));
    lab_moins_180_1->setFont(QFont("Comic Sans MS", 6));
    
    //Création de la légende pour le slide de phi
    lab_180_2 = new QLabel("180",this);
    lab_moins_180_2 = new QLabel("-180",this);
    lab_0_2 = new QLabel("0",this);
    //modification de la la taille et du style de police de la légende de phi
    lab_0_2->setFont(QFont("Comic Sans MS", 6));
    lab_180_2->setFont(QFont("Comic Sans MS", 6));
    lab_moins_180_2->setFont(QFont("Comic Sans MS", 6));
    
    //////////////////// SLIDERS ////////////////////
    
    //Création des Slider
    	//slider modifiant le zoom
    	sld_r = new QSlider(Qt::Horizontal);
    	//slider modifiant l'angle de vue theta
    	sld_theta = new QSlider(Qt::Horizontal);
    	//slider modifiant l'angle de vue phi
    	sld_phi = new QSlider(Qt::Horizontal);
    //Définition des LIMITES des Slider
    	//le Zoom peut aller de 11% à 2000%
    	sld_r->setMaximum(3000);
    	sld_r->setMinimum(1);
    	//sa valeur d'origine est 100%
    	sld_r->setValue(1500);
    	
    	//les angles peuvent aller de -180° à 180°
    	sld_theta->setMaximum(180);
    	sld_theta->setMinimum(-180);
		sld_phi->setMaximum(180);
    	sld_phi->setMinimum(-180);

	//création du texte Vitesse Zoom
	lab_vitesse_zoom=new QLabel("Vitesse Zoom :");
	
	//Création d'un menu déroulant pour modifier la vitesse du zoom
	cbb_vitesse_zoom = new QComboBox(this);
	cbb_vitesse_zoom->addItem("x1");
	cbb_vitesse_zoom->addItem("x2");
	cbb_vitesse_zoom->addItem("x4");
	cbb_vitesse_zoom->addItem("x8");
	cbb_vitesse_zoom->addItem("x16");
	
	//création du texte Vitesse Déplacement
	lab_vitesse_deplacement=new QLabel("Vitesse de déplacement :");
	
	//Création d'un menu déroulant pour modifier la vitesse du déplacement
	cbb_vitesse_deplacement = new QComboBox(this);
	cbb_vitesse_deplacement->addItem("x1");
	cbb_vitesse_deplacement->addItem("x2");
	cbb_vitesse_deplacement->addItem("x4");
	cbb_vitesse_deplacement->addItem("x8");
    
    //comboBox permettant à l'utilisateur de modifier le rendu de la scene
    //Pour le rendu des ligne
	cbb_line = new QComboBox(this);
	//il peut afficher les lignes avec une couleur atténuée des faces qu'elles entourent
	cbb_line->addItem("Ligne discrètes");
	//ou les afficher en noir
	cbb_line->addItem("Ligne pleines");
	//ou ne pas les afficher
	cbb_line->addItem("Sans Ligne");
	
	//Pour le rendu de la texture
	cbb_texture = new QComboBox(this);
	//Il peut afficher les couleur avec le rendu de lumière
	cbb_texture->addItem("Mode Solide avec lumière");
	//Ou afficher seulement les couleurs
	cbb_texture->addItem("Mode Solide");
	//Ou n'afficher que les lignes
	cbb_texture->addItem("Mode Filaire");
	
	//Pour l'affichage on a besoin de conteneur pour organiser la fenètre
	//création d'un encadré avec l'intitulé objet
	QGroupBox *groupbox = new QGroupBox("Objet");
	//création d'une boite verticale
    QVBoxLayout *vbox = new QVBoxLayout;

	//on ajoute chaque widget au mainLayout par ordre d'affichage pour le panneau objet
	
	/////////////////////////////// PANNEAU OBJET //////////////////////////////////
	//on indique à l'encadré qu'il contient la boite verticale vbox contenant les item modifiant l'objet
    groupbox->setLayout(vbox);
    //on affiche l'encadré et tout ce qu'il contient sur le mainLayout
	mainLayout->addWidget(groupbox,1,1);

	//on ajoute chaque widget au mainLayout par ordre d'affichage pour le panneau objet
	
	
	/////////////////////////////// PANNEAU OBJET //////////////////////////////////
	////////////////////////// ZOOM ////////////////////////////////////////////
		//ajout de l'intitulé
		vbox->addWidget(lab_r);
		//ajout de la barre de slide	
		vbox->addWidget(sld_r);
		//ajout de l'intitulé  pour la modificationde la vitesse du zoom à la boite verticale
		vbox->addWidget(lab_vitesse_zoom);
		//ajout de la liste déroulante pour la modificationde la vitesse du zoom à la boite verticale
		vbox->addWidget(cbb_vitesse_zoom);
		
		////////////////////////// MODIFICATION DE THETA ////////////////////////////////////////////
		vbox->addWidget(lab_theta);
		vbox->addWidget(sld_theta);
		
		QHBoxLayout *hbox1 = new QHBoxLayout;
		hbox1->addWidget(lab_moins_180_1);
		hbox1->addSpacing(80);
		hbox1->addWidget(lab_0_1);
		hbox1->addSpacing(70);
		hbox1->addWidget(lab_180_1);
		vbox->addLayout(hbox1);
		
    	////////////////////////// MODIFICATION DE PHI ////////////////////////////////////////////
		vbox->addWidget(lab_phi);
		vbox->addWidget(sld_phi);
		QHBoxLayout *hbox2 = new QHBoxLayout;
		hbox2->addWidget(lab_moins_180_2);
		hbox2->addSpacing(80);
		hbox2->addWidget(lab_0_2);
		hbox2->addSpacing(70);
		hbox2->addWidget(lab_180_2);
		
		vbox->addLayout(hbox2);
		
		vbox->addWidget(lab_vitesse_deplacement);
		vbox->addWidget(cbb_vitesse_deplacement);

		//ajout de la liste de selection permettant à l'utilisateur de choisir le mode d'affichage de la texture
		vbox->addWidget(cbb_texture);
		//ajout de la liste de selection permettant à l'utilisateur de choisir le mode d'affichage des lignes
		vbox->addWidget(cbb_line);
		//ajout du bouton reset
  		vbox->addWidget(bt_raz);
}

void Window::Window_panneau_lumiere()
{
	/* On crée ici toute l'interface pour la manipulation de la lumière
  	 * Il permet :
  	 * 	la rotation
  	 * 	le zoom
  	 */
	
	//////////////////// BOUTON ////////////////////
    
    //création du bouton reset de la lumière
  	bt_raz_lum = new QPushButton("Reset", this);
    
    //////////////////// LABEL //////////////////////
    
    //Création des encadrés de texte
    lab_r_lum = new QLabel("Intensité :",this);
    lab_theta_lum = new QLabel("Theta",this);
    lab_phi_lum = new QLabel("Phi",this);
    
    
    //légende pour slide theta
    lab_0_1_lum = new QLabel("0",this);
    lab_180_1_lum = new QLabel("180",this);
    lab_moins_180_1_lum = new QLabel("-180",this);
    //On change le style et la taille de la police de la légende de theta
    lab_0_1_lum->setFont(QFont("Comic Sans MS", 6));
    lab_180_1_lum->setFont(QFont("Comic Sans MS", 6));
    lab_moins_180_1_lum->setFont(QFont("Comic Sans MS", 6));
    
    //légende pour slide phi
    lab_180_2_lum = new QLabel("180",this);
    lab_moins_180_2_lum = new QLabel("-180",this);
    lab_0_2_lum = new QLabel("0",this);
    //On change le style et la taille de la police de la légende de phi
    lab_0_2_lum->setFont(QFont("Comic Sans MS", 6));
    lab_180_2_lum->setFont(QFont("Comic Sans MS", 6));
    lab_moins_180_2_lum->setFont(QFont("Comic Sans MS", 6));
    
    //////////////////// SLIDERS ////////////////////
    
    //Création des Slider
    	//pour l'intensité de la lumière
   		sld_r_lum = new QSlider(Qt::Horizontal, this);
    	//pour régler l'angle theta
    	sld_theta_lum = new QSlider(Qt::Horizontal, this);
    	//pour régler l'angle phi
    	sld_phi_lum = new QSlider(Qt::Horizontal, this);
    //Définition de LIMITES des Slider
    	//l'intensité peut aller de 0 à 100%
    	sld_r_lum->setMaximum(100);
    	sld_r_lum->setMinimum(0);
    	//on l'initialise à 50%
    	sld_r_lum->setValue(50);
    	//les angles peuvent aller de -180° à 180° et sont initialisé à 45°
    	sld_theta_lum->setMaximum(180);
    	sld_theta_lum->setMinimum(-180);
		sld_phi_lum->setMaximum(180);
    	sld_phi_lum->setMinimum(-180);
    	//l'initialisation pour un slider est par défaut faite à 0
	
		/////////////////////////////// PANNEAU LUMIERE //////////////////////////////////
	QGroupBox *groupbox_lum = new QGroupBox("Lumière");

    QVBoxLayout *vbox_lum = new QVBoxLayout;
    groupbox_lum->setLayout(vbox_lum);
	mainLayout->addWidget(groupbox_lum,2,1);
	
	//on ajoute chaque widget au mainLayout par ordre d'affichage pour le panneau lumière
	
	////////////////////////// ZOOM ////////////////////////////////////////////
	//ajout de l'intitulé
	vbox_lum->addWidget(lab_r_lum);
	vbox_lum->addWidget(sld_r_lum);
	////////////////////////// MODIFICATION DE THETA ////////////////////////////////////////////
	vbox_lum->addWidget(lab_theta_lum);
	vbox_lum->addWidget(sld_theta_lum);
	QHBoxLayout *hbox1_lum = new QHBoxLayout;
	hbox1_lum->addWidget(lab_moins_180_1_lum);
	hbox1_lum->addSpacing(80);
	hbox1_lum->addWidget(lab_0_1_lum);
	hbox1_lum->addSpacing(70);
    hbox1_lum->addWidget(lab_180_1_lum);
    vbox_lum->addLayout(hbox1_lum);
    ////////////////////////// MODIFICATION DE PHI ////////////////////////////////////////////
	vbox_lum->addWidget(lab_phi_lum);
	vbox_lum->addWidget(sld_phi_lum);
	QHBoxLayout *hbox2_lum = new QHBoxLayout;
	hbox2_lum->addWidget(lab_moins_180_2_lum);
	hbox2_lum->addSpacing(80);
	hbox2_lum->addWidget(lab_0_2_lum);
	hbox2_lum->addSpacing(70);
    hbox2_lum->addWidget(lab_180_2_lum);
    vbox_lum->addLayout(hbox2_lum);
	
	//ajout du bouton reset
  	vbox_lum->addWidget(bt_raz_lum);
}

void Window::Window_param_mainLayout()
{
	/*
	 * création de mainLayout qui est une grille invisible permettant de positionner de façon ordonné les widgets sur la fenetre
	 * L'avantage de cette grille est qu'elle s'adapte au modification de la taille de la fenètre
	 */
	mainLayout = new QGridLayout;
  	setLayout(mainLayout);
	
	/* Le gridLayout s'adapte en fonction de la taille de la fenètre
  	 * mais il faut lui donner quelque contraintes pour obtenir le résultat
  	 * souhaité
  	 */
  	
  	//La zone de dessin fait au moins 600 de large
  	mainLayout->setColumnMinimumWidth(0,600);
  	
  	//seule la zone d'affichage change de taille lorsqu'on change la taille de la fenètre
  	mainLayout->setColumnStretch(0,1);
  	mainLayout->setRowStretch(3,1);
}

void Window::Window_desactive_panneaux()
{
		
	/* Au démarrage aucune image n'est chargée
	 * il ne faut donc pas qu'on puisse utiliser les boutons du panneau
	 * à part ceux relatif au programme
	 * donc on les désactive et ils seront réactivés lors du chargement
	 */
	cbb_line->setDisabled(true);
	cbb_texture->setDisabled(true);
	
	lab_r->setDisabled(true);
	lab_theta->setDisabled(true);
	lab_phi->setDisabled(true);
		
	lab_0_1->setDisabled(true);
	lab_180_1->setDisabled(true);
	lab_moins_180_1->setDisabled(true);
		
	lab_0_2->setDisabled(true);
	lab_180_2->setDisabled(true);
	lab_moins_180_2->setDisabled(true);
		
	bt_raz->setDisabled(true);
		
	sld_r->setDisabled(true);
	sld_theta->setDisabled(true);
	sld_phi->setDisabled(true);
		
	lab_r_lum->setDisabled(true);
	lab_theta_lum->setDisabled(true);
	lab_phi_lum->setDisabled(true);
		
	lab_0_1_lum->setDisabled(true);
	lab_180_1_lum->setDisabled(true);
	lab_moins_180_1_lum->setDisabled(true);
		
	lab_0_2_lum->setDisabled(true);
	lab_180_2_lum->setDisabled(true);
	lab_moins_180_2_lum->setDisabled(true);
	
	bt_raz_lum->setDisabled(true);
		
	sld_r_lum->setDisabled(true);
	sld_theta_lum->setDisabled(true);
	sld_phi_lum->setDisabled(true);
	
	actionSauvegarder->setDisabled(true);
	actionAdoucir->setDisabled(true);
	actionPeindre->setDisabled(true);
	actionSubdiviser->setDisabled(true);
	actionInfoObjet->setDisabled(true);
	
	lab_vitesse_deplacement->setDisabled(true);
	cbb_vitesse_deplacement->setDisabled(true);
	lab_vitesse_zoom->setDisabled(true);
	cbb_vitesse_zoom->setDisabled(true);
}


void Window::Window_interface_general()
{
	//On créer le Barre de tache
	tool_bar = new QToolBar();
	//On l'ajoute au mainLayout	
	mainLayout->addWidget(tool_bar,0,0,1,2);
	
	//On définie les boutons qui vont composer cette Barre des tâche
	//Création du bouton Charger
	actionCharger=new QAction(QPixmap("./images/charger.png"),"Charger",tool_bar);
	//Création du bouton Sauvegarder
	actionSauvegarder=new QAction(QPixmap("./images/save.gif"),"Sauvegarder",tool_bar);
	//Création du bouton A propos de nous
	actionAbout_us=new QAction(QPixmap("./images/about.png"),"A propos de nous",tool_bar);
	//Création du bouton A propos de Qt
	actionAbout_Qt=new QAction(QPixmap("./images/Qt.jpg"),"A propos de Qt",tool_bar);
	//Création du bouton d'aide
	actionHelp= new QAction(QPixmap("./images/help.png"),"Aide",tool_bar);
	//Création du bouton adoucir
	actionAdoucir= new QAction(QPixmap("./images/adoucir.png"),"Adoucir",tool_bar);
	//Création du bouton subdiviser
	actionSubdiviser= new QAction(QPixmap("./images/subdiviser.png"),"Subdiviser",tool_bar);
	//Création du bouton peindre
	actionPeindre= new QAction(QPixmap("./images/peindre.png"),"Peindre",tool_bar);
	//Création du bouton information sur les objets
	actionInfoObjet= new QAction(QPixmap("./images/info.png"),"Informations objet",tool_bar);
		
	//on ajoute tous les boutons à la barre des tâches
	tool_bar->addAction(actionCharger);
	tool_bar->addAction(actionSauvegarder);
	tool_bar->addSeparator();
	tool_bar->addAction(actionAdoucir);
	tool_bar->addAction(actionSubdiviser);
	tool_bar->addAction(actionPeindre);
	tool_bar->addAction(actionInfoObjet);
	tool_bar->addSeparator();
	tool_bar->addAction(actionAbout_us);
	tool_bar->addAction(actionAbout_Qt);
	tool_bar->addSeparator();
	tool_bar->addAction(actionHelp);

	//On défini la taille des icones
	tool_bar->setIconSize(QSize(40,40));
	
	//lors de la première ouverture il affiche une image et demande à l'utilisateur de charger un fichier
	
  	ch_label = new QLabel("Veuillez charger un fichier", this);
  	ch_image = new QLabel(this);
  	//on indique au programme quel image afficher
  	ch_image->setPixmap(QPixmap("./images/logo.jpg"));
  	//on change la police et la taille du message demandant à l'utilisateur de charger 
	ch_label->setFont(QFont("Comic Sans MS", 17));
		
	//ajout du message de départ (image + demande de chargement) au mainLayout
	//ces deux labels disparaitrons dès qu'un fichiers aura été chargé.
  	mainLayout->addWidget(ch_label,2,0,Qt::AlignHCenter);
  	mainLayout->addWidget(ch_image,1,0,Qt::AlignHCenter);
}

Window::~Window()
{
	cout << "Destruction de la fenetre" << endl;
	
	//Si la zone d'affichage n'existe pas, on détruit la scène directement
	if(!area_view) delete scene3d;
	//Autrement, on désalloue la zone d'affichage	
 	else delete area_view;

 	//on désalloue les boutons
 	delete bt_raz;

 	//on désalloue les labels
 	delete lab_phi;
 	delete lab_r;
 	delete lab_theta;

 	//on désalloue les Slider
 	delete sld_r;
 	delete sld_theta;
 	delete sld_phi;

 	delete lab_0_1;
	delete lab_180_1;
	delete lab_moins_180_1;

 	delete lab_0_2;
	delete lab_180_2;
	delete lab_moins_180_2;
	
	//on désalloue les comboBox
	delete cbb_line;
	delete cbb_texture;
	
	 //on désalloue les boutons
 	delete bt_raz_lum;
 	
 	//on désalloue les labels
 	delete lab_phi_lum;
 	delete lab_r_lum;
 	delete lab_theta_lum;
 	
 	//on désalloue les Slider
 	delete sld_r_lum;
 	delete sld_theta_lum;
 	delete sld_phi_lum;
 	
 	delete lab_0_1_lum;
	delete lab_180_1_lum;
	delete lab_moins_180_1_lum;
 	
 	delete lab_0_2_lum;
	delete lab_180_2_lum;
	delete lab_moins_180_2_lum;	
}

void Window::charger()
{
	
	//Initialisation de la scène 3d
	scene3d=NULL;
	
	//Ouverture d'une boite de dialogue permettant de choisir le fichier à charger et il retourne l'adresse en QString
	QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "./OFF", "Objet 3D (*.off *.sff)");
	
	//S'il n'a pas choisi de fichier
	if (fichier==NULL) 
	{
		//il affiche un message d'avertissement et continue le traitement normalement
		QMessageBox::information(this, "ATTENTION", "Vous n'avez pas sélectionné de fichier");
	}
    else
    {
    	//Création de la scène 3d
		scene3d=new Scene_3D(fichier.toStdString());
		//Si le chargement de la scène à partir du fichier s'est bien passé
		if(scene3d->load_from_file(fichier.toStdString()))
		{
			//si la zone d'affichage existe (une image avez déjà été chargée avant)
			if (area_view)
			{
				//on met en place la nouvelle scene à l'aide de cette fonction que désallou comme il faut
				area_view->set_new_scene(scene3d);
			}
			else
			{
				//on efface le message de chargement
				ch_label->close();
				ch_image->close();
				
				//on affecte la nouvelle scene
				area_view=new AreaView(this, scene3d);
				
				/* Les widget qui servent à modifier l'image est la lumière avaient étaient désactivé lors du l'ouverture
				 * il faut donc maintenant les réactiver
				 * mais cela n'est necessaire que lors du premier chargement
				 */
				
				cbb_line->setDisabled(false);
				cbb_texture->setDisabled(false);
				
				lab_r->setDisabled(false);
				lab_theta->setDisabled(false);
				lab_phi->setDisabled(false);
					
				lab_0_1->setDisabled(false);
				lab_180_1->setDisabled(false);
				lab_moins_180_1->setDisabled(false);
					
				lab_0_2->setDisabled(false);
				lab_180_2->setDisabled(false);
				lab_moins_180_2->setDisabled(false);
					
				bt_raz->setDisabled(false);
					
				sld_r->setDisabled(false);
				sld_theta->setDisabled(false);
				sld_phi->setDisabled(false);
					
				lab_r_lum->setDisabled(false);
				lab_theta_lum->setDisabled(false);
				lab_phi_lum->setDisabled(false);
					
				lab_0_1_lum->setDisabled(false);
				lab_180_1_lum->setDisabled(false);
				lab_moins_180_1_lum->setDisabled(false);
					
				lab_0_2_lum->setDisabled(false);
				lab_180_2_lum->setDisabled(false);
				lab_moins_180_2_lum->setDisabled(false);
				
				bt_raz_lum->setDisabled(false);
					
				sld_r_lum->setDisabled(false);
				sld_theta_lum->setDisabled(false);
				sld_phi_lum->setDisabled(false);
				
				cbb_vitesse_deplacement->setDisabled(false);
				cbb_vitesse_deplacement->setDisabled(false);
				cbb_vitesse_deplacement->setDisabled(false);
				
				lab_vitesse_zoom->setDisabled(false);
				cbb_vitesse_zoom->setDisabled(false);
				lab_vitesse_deplacement->setDisabled(false);
				cbb_vitesse_deplacement->setDisabled(false);
				
				actionAdoucir->setDisabled(false);
				actionPeindre->setDisabled(false);
				actionSubdiviser->setDisabled(false);
				actionInfoObjet->setDisabled(false);
			}
			
			//on réinitialise tous les curseurs de rotation, zoom, lumière
			sld_r->setValue(1500);
			sld_theta->setValue(0);
			sld_phi->setValue(0);
			sld_r_lum->setValue(50);
			sld_theta_lum->setValue(0);
			sld_phi_lum->setValue(0);
			cbb_vitesse_deplacement->setCurrentIndex(0);
			cbb_vitesse_zoom->setCurrentIndex(0);
			cbb_line->setCurrentIndex(0);
			cbb_texture->setCurrentIndex(0);
			//on affiche la zone d'affichage sur la grille
			mainLayout->addWidget(area_view, 1,0,3,1);
			
			//on fait en sorte que tous les signaux du clavier soient récupérés par la zone d'affichage
			area_view->grabKeyboard();
			
			//on reconnecte les signaux
			connect_signaux_scene();
			
			//on actualise l'affichage de la fenètre
			update();
		}
    }
}

void Window::reset_view()
{
	//on remet le zoom à 100%
	sld_r->setValue(100);
	//on remet theta à 0°
	sld_theta->setValue(0);
	//on remet phi à 0°
	sld_phi->setValue(0);
	
}

void Window::reset_lum()
{
	//on remet l'intensité à 50%
	sld_r_lum->setValue(50);
	//on remet theta à 45°
	sld_theta_lum->setValue(45);
	//on remet phi à 45°
	sld_phi_lum->setValue(45);
}

void Window::keyPressEvent(QKeyEvent* event)
{
	if (area_view)
	{
		//Rotation phi (+)
		if((event->key()==(Qt::Key_D)) || (event->key()==Qt::Key_3))
		 {
			area_view->get_scene()->rotate_view(0, 0.05);
			sld_phi->setValue((int)(area_view->get_scene()->get_pov_phi()*360/6.28318531+180)%360-180);
		 }
		//Rotation phi (-)
		if((event->key()==Qt::Key_Q) || (event->key()==Qt::Key_1))
		{
			area_view->get_scene()->rotate_view(0, -0.05);
			sld_phi->setValue((int)(area_view->get_scene()->get_pov_phi()*360/6.28318531+180)%360-180);
		}
		//Rotation theta (+)
		if((event->key()==Qt::Key_Z) || (event->key()==Qt::Key_9))
		{
			area_view->get_scene()->rotate_view(-0.05, 0);
			sld_theta->setValue((int)(area_view->get_scene()->get_pov_theta()*360/6.28318531+180)%360-180);
		}
		//Rotation phi (-)
		if((event->key()==Qt::Key_S) || (event->key()==Qt::Key_7))
		{
			area_view->get_scene()->rotate_view(0.05, 0);
			sld_theta->setValue((int)(area_view->get_scene()->get_pov_theta()*360/6.28318531+180)%360-180);
		}
		//Zoom Arrière
		if((event->key()==Qt::Key_Minus) || (event->key()==Qt::Key_A))
		{
			if(area_view->get_scene()->get_pov_r()>-1800) area_view->get_scene()->zoom(-20);
			//sld_r->setValue((int)(area_view->get_scene()->get_pov_r()));
			update();
		}
		//Zoom Avant
		if((event->key()==Qt::Key_Plus) || (event->key()==Qt::Key_E))
		{
			area_view->get_scene()->zoom(20);
			//sld_r->setValue((int)(area_view->get_scene()->get_pov_r()));
			update();
		}
		//Déplacement haut
		if((event->key()==Qt::Key_O) || (event->key()==Qt::Key_8))
		{
			area_view->get_scene()->drag_scene(0, -10);
			update();
		}
		//Déplacement bas
		if((event->key()==Qt::Key_L) || (event->key()==Qt::Key_2))
		{
			area_view->get_scene()->drag_scene(0, 10);
			update();
		}
		//Déplacement gauche
		if((event->key()==Qt::Key_K) || (event->key()==Qt::Key_4))
		{
			area_view->get_scene()->drag_scene(-10, 0);
			update();
		}
		//Déplacement droite
		if((event->key()==Qt::Key_M) || (event->key()==Qt::Key_6))
		{
			area_view->get_scene()->drag_scene(10, 0);
			update();
		}
		//Recentrage
		if((event->key()==Qt::Key_C) || (event->key()==Qt::Key_5))
		{
			area_view->get_scene()->move_scene(0, 0);
			update();
		}
	}
}

void Window::dialog_help(void)
{
	QMessageBox::about (this, "Aide", "Raccourcis clavier :\n"
											"(touche principale / alternative\n\n"
											" Déplacement de la caméra :\n"
											" - Haut : O / 5 (pav.num.)\n"
											" - Bas : L / 2 (pav.num.)\n"
											" - Gauche : K / 4 (pav.num.)\n"
											" - Droite : M / 6 (pav.num.)\n"
											" - Centrage : C / 5 (pav.num.)\n\n"
											" Rotation de la caméra :\n"
											" - Théta (+) : Z / 9 (pav.num.)\n"
											" - Théta (-) : S / 7 (pav.num.)\n"
											" - Phi (+) : D / 3 (pav.num.)\n"
											" - Phi (-) : Q / 1 (pav.num.)\n\n"
											" Zoom de la caméra :\n"
											" - Zoom Avant : E / + (pav.num.)\n"
											" - Zoom Arrière : A / - (pav.num.)\n\n"
											"L'orientation des angles se fait dans\n"
											"le sens trigonométrique\n");

}

void Window::dialog_about(void)
{
	QMessageBox::about (this, "About ...", "Software 3dSMin\n"
													"Created by LaFesse & LoupFox\n"
													"v 1.0\n"
													"last update : may 2008\n"
													"School : E.I.S.T.I\n\n"
													"For any information, please contact \n"
													"LaFesse : trinita.andropos@gmail.com\n"
													"LoupFox : ftreyweb@hotmail.com\n\n"
													"");

}

void Window::dialog_polish(void)
{
	actionSauvegarder->setDisabled(false);
	//Valeur de retour de la boite de dialogue
	int int_retour;
	//Liste des valeurs
	QStringList slist_values;
	//Chaine retourné
	QString qstr_retour;
	//Booléen retourné
	bool bool_retour;
	//Valeur retourné
	int int_value;
	
	//Message d'avertissement
	int_retour=QMessageBox::warning(this, "Algorithme d'adoucissement des sommets", "Attention, il s'agit d'un algorithme basique dont les calculs\n"
																					"peuvent être très lourd.\n"
																					"Ces calculs peuvent engendrer un ralentissement du système si\n"
																					"le nombre de points et de surfaces de l'objet est trop élévés.\n"
																					"Cet algorithme ne s'applique que sur les surfaces polygonales.\n"
																					"Souhaitez-vous toutefois continuer ? (à vos risques et périls)", QMessageBox::Ok | QMessageBox::Cancel);
	//Si l'utilisateur à validé
	if(int_retour==QMessageBox::Ok)
	{
		//Création de la liste des valeurs possibles
		slist_values << "49" << "40" << "30" << "20" << "10";
		//Boite de dialogue vace selection d'une des valeurs
		qstr_retour=QInputDialog::getItem(this, "Algorithme d'adoucissement des sommets", "Coefficient à appliquer (en %) : ", slist_values, 0, false, &bool_retour);
		//Si l'utilisateur à validé
		if(bool_retour)
		{
			//Récupération de la valeur selectionné
			int_value=qstr_retour.toInt(&bool_retour, 10);
			//Si la conversion s'est bien passé
			if(bool_retour)
			{
				//Polissage de l'objet
				area_view->get_scene()->get_object3d()->polish(int_value/100.0);
				//Mise à jour de la scène
				update();
			}
		}
	}
}

void Window::dialog_paint_object(void)
{
	actionSauvegarder->setDisabled(false);
	//Couleur renvoyé
	QColor color;
	//Couleur prédéfini
	QColor color_default(90,135,255);
	//Boite de dialogue de choix de la couleur
	color = QColorDialog::getColor(color_default, this);
	
	//Coloriage de l'objet
	area_view->get_scene()->get_object3d()->paint(color);
	
	//Mise à jour de la fenêtre
	update();
	
}

void Window::dialog_save_object(void)
{
	//Nom du fichier de sauvegarde
	QString file_name;
	//Boite de dialogue de sauvegarde de fichier
	file_name = QFileDialog::getSaveFileName(this, "Enregistrer l'objet 3d", "./OFF", "Objet 3D (*.off)");

	//S'il l'utilisateur n'a pas choisi de fichier
	if (file_name==NULL) QMessageBox::information(this, "ATTENTION", "Vous n'avez pas spécifié de fichier");
    //Autrement, on enregistre l'objet 3d
    else area_view->get_scene()->get_object3d()->save_in_file(file_name.toStdString());
}

void Window::dialog_info_object(void)
{
    //Texte à afficher
    string str_texte;
    //Texte temporaire pour la conversion d'entier
    stringstream str_int;
   
    //Création du texte de la boite de dialogue
    str_texte="Objet OFF 3d\n\n";
    str_texte+="Chemin d'accès :\n";
    str_texte+=area_view->get_scene()->get_object3d()->get_path();
    str_texte+="\n\n";
    str_texte+="Nombre de polygone : ";
    str_int << area_view->get_scene()->get_object3d()->get_nb_polygon();
    str_texte+=str_int.str();
    str_int.seekp(0);
    str_texte+="\n";
    str_texte+="Nombre de points : ";
    str_int << area_view->get_scene()->get_object3d()->get_nb_vertices() << '\0';
    str_texte+=str_int.str();
    str_texte+="\n";
    str_texte+="Nombre de points uniques : ";
    str_int.seekp(0);
    str_int << area_view->get_scene()->get_object3d()->get_nb_single_vertices() << '\0';
    str_texte+=str_int.str();
    str_texte+="\n";
    //Boite de dialogue
    QMessageBox::about (this, area_view->get_scene()->get_object3d()->get_path().c_str(), str_texte.c_str());
}

void Window::dialog_subdivide(void)
{
	actionSauvegarder->setDisabled(false);
	//Fonction de subdivision de l'objet
	area_view->get_scene()->get_object3d()->subdivide_byref();
	//Mise à jour de l'affichage
	update();
}
void Window::connect_signaux_scene()
{
	//Si la zone d'affichage existe
	if (area_view)
	{
		//modification de r
		QObject::connect(sld_r, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pov_r(int)));
		QObject::connect(sld_r, SIGNAL(valueChanged(int)),this, SLOT(update()));
		
		//modification de theta
		QObject::connect(sld_theta, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pov_theta(int)));
		QObject::connect(sld_theta, SIGNAL(valueChanged(int)),this, SLOT(update()));
		
		//modification de phi
		QObject::connect(sld_phi, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pov_phi(int)));
		QObject::connect(sld_phi, SIGNAL(valueChanged(int)),this, SLOT(update()));
		
		//modification de r
		QObject::connect(sld_r_lum, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pol_r(int)));
		QObject::connect(sld_r_lum, SIGNAL(valueChanged(int)),this, SLOT(update()));
		
		//modification de theta
		QObject::connect(sld_theta_lum, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pol_theta(int)));
		QObject::connect(sld_theta_lum, SIGNAL(valueChanged(int)),this, SLOT(update()));
	
		//modification de phi
		QObject::connect(sld_phi_lum, SIGNAL(valueChanged(int)), area_view->get_scene(), SLOT(signal_set_pol_phi(int)));
		QObject::connect(sld_phi_lum, SIGNAL(valueChanged(int)),this, SLOT(update()));
		
		QObject::connect(cbb_vitesse_deplacement, SIGNAL(highlighted(int)),area_view->get_scene(), SLOT(set_drag_speed(int)));
		QObject::connect(cbb_vitesse_zoom, SIGNAL(highlighted(int)),area_view->get_scene(), SLOT(set_zoom_speed(int)));
	}
	
	//Lorsqu'on click sur "Reset de l'objet"
	QObject::connect(bt_raz, SIGNAL(clicked()), this, SLOT(reset_view()));
	
	//Lorsqu'on click sur "Reset de la lumière"
	QObject::connect(bt_raz_lum, SIGNAL(clicked()), this, SLOT(reset_lum()));
	
	//lorsqu'on change de mode de visualisation
	QObject::connect(cbb_line, SIGNAL(highlighted(int)), this , SLOT(signal_set_mode_line(int)));
	QObject::connect(cbb_texture, SIGNAL(highlighted(int)), this, SLOT(signal_set_mode_surface(int)));
	
}

void Window::signal_set_mode_line(int mode)
{
	//Mise à jour du mode d'affichage des lignes
	area_view->get_scene()->set_mode_line(mode);
	//Mise à jour de la fenêtre
	update();
}
		
void Window::signal_set_mode_surface(int mode)
{
	//Mise à jour du mode d'affichage des surfaces
	area_view->get_scene()->set_mode_surface(mode);
	//Mise à jour de la fenêtre
	update();
}

void Window::resizeEvent (void)
{
	//Mise à jour de la fenetre
	update();
}


