/*!
  \file Window.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief header de la class Window
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_WINDOW_HPP__
#define __PROJET_3D_WINDOW_HPP__

#include "../headers.hpp"
#include "../areaview/AreaView.hpp"

class Window : public QWidget
{
	Q_OBJECT
	
	private:
		///> Zone d'affichage où s'affiche les Object_3D
		AreaView* area_view;
		
		///> Grille pour ordonner l'affichage sur la fenètre
		QGridLayout * mainLayout;
		
		///>Message qui s'affiche au départ qui demande à l'utilisateur de charger un fichier
		QLabel* ch_label;
		///>Image de départ affichée au dessus du message précedent
  		QLabel* ch_image;
		
	/////////////////////////////////////////////////////////////////////////
  	////                                                                  ///
  	////                         OBJET                                    ///
  	////                                                                  ///
  	/////////////////////////////////////////////////////////////////////////
		
		///>Bouton de remise a zéro des paramètre de l'objet
		QPushButton* bt_raz;
		
		///>Intituler pour le slider sld_r : "Zoom"
		QLabel* lab_r;
		///>Intituler pour le slider sld_theta : "Theta"
		QLabel* lab_theta;
		///>Intituler pour le slider sld_phi : "Phi"
		QLabel* lab_phi;
		
		///>Légende de sld_theta : "-180"
		QLabel* lab_moins_180_1;
		///>Légende de sld_theta : "-0"
		QLabel* lab_0_1;
		///>Légende de sld_theta : "180"
		QLabel* lab_180_1;
		
		///>Légende de sld_phi : "-180"
		QLabel* lab_0_2;
		///>Légende de sld_phi : "0"
		QLabel* lab_180_2;
		///>Légende de sld_phi : "180"
		QLabel* lab_moins_180_2;
		
		///>Barre horizontale permettant de modifier la valeur du zoom
		QSlider* sld_r;
		///>Barre horizontale permettant de modifier la valeur de theta
		QSlider* sld_theta;
		///>Barre horizontale permettant de modifier la valeur de phi
		QSlider* sld_phi;
		
		///>Intitulé "Vitesse Zoom"
		QLabel* lab_vitesse_zoom;
		///>Menu déroulant permettant de modifier la vitesse du zoom
		QComboBox* cbb_vitesse_zoom;
		
		///>Intitulé "Vitesse de déplacement"
		QLabel* lab_vitesse_deplacement;
		///>Menu déroulant permettant de modifier la vitesse de déplacement
		QComboBox* cbb_vitesse_deplacement;
		
		///>Menu déroulant permettant de modfier le style de rendu des lignes
		QComboBox* cbb_line;
		///>Menu déroulant permettant de modfier le style de rendu de la texture
		QComboBox* cbb_texture;
		
	/////////////////////////////////////////////////////////////////////////
  	////                                                                  ///
  	////                         LUMIERE                                  ///
  	////                                                                  ///
  	/////////////////////////////////////////////////////////////////////////

		///>Bouton permettant de remettre à zero les paramètres de la lumière  	
		QPushButton* bt_raz_lum;
		
		///>Intituler pour le slider sld_r : "Intensité"
		QLabel* lab_r_lum;
		///>Intituler pour le slider sld_theta : "Theta"
		QLabel* lab_theta_lum;
		///>Intituler pour le slider sld_phi : "Phi"
		QLabel* lab_phi_lum;
		
		///>Légende de sld_theta : "-180"
		QLabel* lab_moins_180_1_lum;		
		///>Légende de sld_theta : "0"
		QLabel* lab_0_1_lum;
		///>Légende de sld_theta : "180"
		QLabel* lab_180_1_lum;

		///>Légende de sld_phi : "-180"
		QLabel* lab_moins_180_2_lum;
		///>Légende de sld_phi : "0"
		QLabel* lab_0_2_lum;
		///>Légende de sld_phi : "180"
		QLabel* lab_180_2_lum;
		
		///>Barre horizontale permettant de modifier la valeur de l'intensité
		QSlider* sld_r_lum;
		///>Barre horizontale ermettant de modifier la valeur de theta
		QSlider* sld_theta_lum;
		///>Barre horizontale permettant de modifier la valeur de phi
		QSlider* sld_phi_lum;
		
		///>Barre de Menu permettant entre autre de charger, sauvegarder, avoir l'aide .....
		QToolBar* tool_bar;
		
		///>Bouton de la barre de Menu permattant de charger
		QAction *actionCharger;
		///>Bouton de la barre de Menu permattant de sauvegarder
		QAction *actionSauvegarder;
		///>Bouton de la barre de Menu permattant d'obtenir des informations sur le programme
		QAction *actionAbout_us;
		///>Bouton de la barre de Menu permattant d'obtenir des informations sur Qt
		QAction *actionAbout_Qt;
		///>Bouton de la barre de Menu permattant d'obtenir de l'aide
		QAction *actionHelp;	
		///>Bouton de la barre de Menu permattant d'adoucir
		QAction *actionAdoucir;
		///>Bouton de la barre de Menu permattant de changer la couleur de l'objet
		QAction *actionPeindre;
		///>Bouton de la barre de Menu permattant de subdiviser l'objet
		QAction *actionSubdiviser;
		///>Bouton de la barre de Menu permattant d'obtenir des informations sur l'objet
		QAction *actionInfoObjet;
		
		/*!
		  \fn void resizeEvent ()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief fonction qui détermine l'action a effectuer si la fenètre change de taille

		  \version 1.0
		  \return rien
		*/
		void resizeEvent ();
	
	public slots:
		/*!
		  \fn void charger(void);

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief slot qui défini les actions a fair lors du chargement d'un fichier

		  \version 1.0
		  \return rien
		*/
		void charger(void);
		
		/*!
		  \fn void reset_view(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief remet les paramètre de la vue à zero

		  \version 1.0
		  \return rien
		*/
		void reset_view(void);
		
		/*!
		  \fn void reset_lum(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief remet les paramètre de la lumiere à zero

		  \version 1.0
		  \return rien
		*/
		void reset_lum(void);
		
		/*!
		  \fn void signal_set_mode_line(int mode)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief modifie le mode de rendu des lignes
		  
		   \param mode type de rendu voulu

		  \version 1.0
		  \return rien
		*/
		void signal_set_mode_line(int mode);
		
		/*!
		  \fn void signal_set_mode_surface(int mode)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief modifie le mode de rendu de la texture
		  
		   \param mode type de rendu voulu

		  \version 1.0
		  \return rien
		*/
		void signal_set_mode_surface(int mode);
		
		/*!
		  \fn void dialog_help(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message d'aide

		  \version 1.0
		  \return rien
		*/
		void dialog_help(void);
		
		/*!
		  \fn void dialog_about(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message à propos du logiciel

		  \version 1.0
		  \return rien
		*/
		void dialog_about(void);
		
		/*!
		  \fn void dialog_polish(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message pour polir la figure

		  \version 1.0
		  \return rien
		*/
		void dialog_polish(void);
		
		/*!
		  \fn void dialog_paint_object(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message pour modifier la couleur de l'objet

		  \version 1.0
		  \return rien
		*/
		void dialog_paint_object(void);
		
		/*!
		  \fn void dialog_save_object(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message pour sauvegarder l'objet modifier

		  \version 1.0
		  \return rien
		*/
		void dialog_save_object(void);
		
		/*!
		  \fn void dialog_subdivide(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message pour subdiviser l'objet

		  \version 1.0
		  \return rien
		*/
		void dialog_subdivide(void);
		
		/*!
		  \fn void void dialog_info_object(void)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief affiche le message qui donne des informations sur l'objet

		  \version 1.0
		  \return rien
		*/
		void dialog_info_object(void);
		
	public:		
		//////////////////////////////////////////
		//			Fonction de class			//
		//////////////////////////////////////////
		
		/*!
		  \fn Window()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief constructeur par defaut de la classe Window

		  \version 1.0
		  \return rien
		*/
		Window();
		
		/*!
		  \fn void Window_panneau_objet()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief initialise le panneau d'affichage en rapport avec les mouvements de l'objet

		  \version 1.0
		  \return rien
		*/
		void Window_panneau_objet();
		
		/*!
		  \fn void Window_panneau_lumiere();

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief initialise le panneau d'affichage en rapport avec les mouvements de la lumière

		  \version 1.0
		  \return rien
		*/		
		void Window_panneau_lumiere();
		
		/*!
		  \fn void Window_interface_general()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief initialise les boutons généraux de l'interface

		  \version 1.0
		  \return rien
		*/	
		void Window_interface_general();
		
		/*!
		  \fn void Window_param_mainLayout()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief paramètre le mainLayout pour obtenir l'affichage voulu

		  \version 1.0
		  \return rien
		*/
		void Window_param_mainLayout();
		
		/*!
		  \fn void Window_desactive_panneaux()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief désactive les Widgets qu'il ne faut pas utiliser au début

		  \version 1.0
		  \return rien
		*/
		void Window_desactive_panneaux();
		
		/*!
		  \fn ~Window()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief destructeur par defaut

		  \version 1.0
		  \return rien
		*/
		~Window();
		
		//////////////////////////////////////////
		//		  		Accesseurs				//
		//////////////////////////////////////////
		
		/*!
		  \fn AreaView* get_area_view(void) const

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief accesseur du membre area_view

		  \version 1.0
		  \return area_view de la fenètre
		*/
		AreaView* get_area_view(void) const;
		
		//////////////////////////////////////////
		//		  Fonction d'interaction		//
		//////////////////////////////////////////
		
		/*!
		  \fn bool init_qt()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief Initialise le module Qt

		  \version 1.0
		  \return un booléen qui indique si l'initialisation s'est bien passé
		*/
		bool init_qt();
		
		/*!
		  \fn bool create_window()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief Création de la fenètre

		  \version 1.0
		  \return rien
		*/
		bool create_window();
		
		/*!
		  \fn void keyPressEvent(QKeyEvent* event)

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief Définit les actions lors de l'utilisation des touches

		  \version 1.0
		  \return rien
		*/
		void keyPressEvent(QKeyEvent* event);
		
		/*!
		  \fn void connect_signaux_scene()

		  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
		  \brief Connecte les signaux qui sont liés à l'objet en cours

		  \version 1.0
		  \return rien
		*/
		void connect_signaux_scene();
};

#endif
