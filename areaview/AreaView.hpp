/*!
  \file AreaView.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
  \brief 
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_AREAVIEW_HPP__
#define __PROJET_3D_AREAVIEW_HPP__

#include "../headers.hpp"
#include "../scene3D/Scene3D.hpp"

class Scene_3D;

class AreaView : public QWidget
{
	protected:
		///> Scene d'Object_3D qui sera affichée dans la zone d'affichage
		Scene_3D* scene;	
		
		///> Largeur de la zone d'affichage
		int int_width;
		///> Hauteur de la zone d'affichage
		int int_height;
		
		//////////////////////////////////////////
		//		  Fonction d'affichage			//
		//////////////////////////////////////////
		
		/*!
			\fn void paintEvent(QPaintEvent* event)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de dessin de la fenêtre et de son contenu
			\param event événement
			\version 1.0
			\return rien
		*/
		void paintEvent(QPaintEvent* event);
		
	public:
		//////////////////////////////////////////
		//		  Fonction de class				//
		//////////////////////////////////////////
		
		/*!
			\fn void AreaView(QWidget* parent, Scene_3D* scene3D)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètres
			\param parent fenêtre parente
			\param scene3D scène 3d
			\version 1.0
			\return rien
		*/
		AreaView(QWidget* parent, Scene_3D* scene3D);
		
		/*!
			\fn void ~AreaView(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Destructeur
			\version 1.0
			\return rien
		*/
		~AreaView(void);
		
		//////////////////////////////////////////
		//		  Fonction accesseurs			//
		//////////////////////////////////////////
		
		/*!
			\fn int get_width(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la largeur de la zone d'affichage
			\version 1.0
			\return largeur de la zone d'affichage
		*/
		int get_width(void) const;
		
		/*!
			\fn int get_height(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la hauteur de la zone d'affichage
			\version 1.0
			\return hauteur de la zone d'affichage
		*/
		int get_height(void) const;
		
		/*!
			\fn void set_new_scene(Scene_3D* new_scene)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à jour de la scène 3d
			\param new_scene nouvelle scène 3d
			\version 1.0
			\return rien
		*/
		void set_new_scene(Scene_3D* new_scene);
		
		/*!
			\fn QSize get_size(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la taille de la zone d'affichage
			\version 1.0
			\return taille de la zone d'affichage
		*/
		QSize get_size(void) const;
		
		/*!
			\fn QSize get_minimum_size(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la taille minimum de la zone d'affichage
			\version 1.0
			\return taille minimum de la zone d'affichage
		*/
		QSize get_minimum_size(void) const;
		
		/*!
			\fn Scene_3D* get_scene(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la scène
			\version 1.0
			\return scène 3d
		*/
		Scene_3D* get_scene(void);
};

#endif
