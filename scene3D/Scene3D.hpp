/*!
  \file Scene3D.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief header de la classe Scene_3D
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_SCENE3D_HPP__
#define __PROJET_3D_SCENE3D_HPP__

#include "../headers.hpp"
#include "../areaview/AreaView.hpp"
#include "../object3D/Object3D.hpp"
#include "../point3D/Point3D.hpp"

class Object_3D;
class AreaView;
class Point_3D;

class Scene_3D : public QWidget
{
	Q_OBJECT
	private:
		///> Coordonnée sphérique du point de vue V
		struct_point_sphere* origin_view;
		///> Coordonnées sphérique du point lumineux
		struct_point_sphere* origin_light;
		///>Objet_3D contenu dans la scene
		Object_3D* obj_scene;
		///>Mode d'affichage des surfaces
		int int_mode_surface;
		///>Mode d'affichage des lignes
		int int_mode_line;
		///>Abcisse du centre de la scene
		int int_x;
		///>Ordonnée du centre de la scène
		int int_y;
		///>Vitesse de zoom
		int int_zoom_speed;
		///>Vitesse de déplacement
		int int_drag_speed;
		
	public slots:
		
		/*!
			\fn void signal_set_pov_theta(int theta)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle theta du point de vue
			\param theta angle theta
			\version 1.0
			\return rien
		*/
		void signal_set_pov_theta(int theta);

		/*!
			\fn void signal_set_pov_r(int r)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de paramètre r du point de vue
			\param r paramètre r
			\version 1.0
			\return rien
		*/
		void signal_set_pov_r(int r);

		/*!
			\fn void signal_set_pov_phi(int phi)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle phi du point de vue
			\param phi angle phi
			\version 1.0
			\return rien
		*/
		void signal_set_pov_phi(int phi);
		
		/*!
			\fn void signal_set_pol_theta(int theta)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle theta
			\param theta angle theta
			\version 1.0
			\return rien
		*/
		void signal_set_pol_theta(int theta);

		/*!
			\fn void signal_set_pol_r(int r)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification du coefficient du point de lumière
			\param r coefficient du point de lumière
			\version 1.0
			\return rien
		*/
		void signal_set_pol_r(int r);

		/*!
			\fn void signal_set_pol_phi(int phi)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle phi du point de lumière
			\param phi angle phi
			\version 1.0
			\return rien
		*/
		void signal_set_pol_phi(int phi);
		
		/*!
			\fn void set_drag_speed(int coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de la vitesse de déplacement
			\param coef coefficient de déplacement
			\version 1.0
			\return rien
		*/
		void set_drag_speed(int coef);
		
		/*!
			\fn void set_zoom_speed(int coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de la vitesse de zoom
			\param coef coefficient de zoom
			\version 1.0
			\return rien
		*/
		void set_zoom_speed(int coef);
		
		
	public:
		
		//////////////////////////////////////////
		//			Fonctions de classe			//
		//////////////////////////////////////////
		
		/*!
			\fn void Scene_3D(const Scene_3D & other_scene)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par copie
			\param other_scene scène 3d à copier
			\version 1.0
			\return rien
		*/
		Scene_3D(const Scene_3D & other_scene);
		
		/*!
			\fn void Scene_3D(string file)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètre
			\param file fichier contenant la scène 3d
			\version 1.0
			\return rien
		*/
		Scene_3D(void);
		
		/*!
			\fn void ~Scene_3D(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Destructeur
			\version 1.0
			\return rien
		*/
		~Scene_3D();
		
		//////////////////////////////////////////
		//		  		Accesseurs				//
		//////////////////////////////////////////
		
		/*!
			\fn Object_3D* get_object3d(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'objet 3d
			\version 1.0
			\return objet 3d contenu dans la scène
		*/
		Object_3D* get_object3d(void) const;
		
		/*!
			\fn double get_pov_r(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du paramètre r
			\version 1.0
			\return coefficient r du point de vue
		*/
		double get_pov_r(void) const;
		
		/*!
			\fn double get_pov_phi(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'angle phi
			\version 1.0
			\return angle phi du point de vue
		*/
		double get_pov_phi(void) const;
		
		/*!
			\fn double get_pov_theta(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'angle theta
			\version 1.0
			\return angle theta du point de vue
		*/
		double get_pov_theta(void) const;
		
		/*!
			\fn void set_pov_theta(double theta)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle theta
			\param theta nouvel theta angle du point de vue
			\version 1.0
			\return rien
		*/
		void set_pov_theta(double theta);
		
		/*!
			\fn void set_pov_r(double r)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification du paramètre r
			\param r nouveau coefficent r du point de vue
			\version 1.0
			\return rien
		*/
		void set_pov_r(double r);
		
		/*!
			\fn void set_pov_phi(double phi)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'angle phi
			\param phi nouvel phi du point de vue
			\version 1.0
			\return rien
		*/
		void set_pov_phi(double phi);
		
		/*!
			\fn void set_mode_line(int mode)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification du mode d'affichage des lignes
			\param mode mode d'affichage des lignes
			\version 1.0
			\return rien
		*/
		void set_mode_line(int mode);
		
		/*!
			\fn void set_mode_surface(int mode)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification du mode d'affichage des surfaces
			\param mode mode d'affichage des surfaces
			\version 1.0
			\return rien
		*/
		void set_mode_surface(int mode);
		
		
		
		/*!
			\fn int get_zoom_speed(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la vitesse de zoom
			\version 1.0
			\return vitesse de zom
		*/
		int get_zoom_speed(void);
		
		
		
		/*!
			\fn int get_drag_speed(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la vitesse de déplacement
			\version 1.0
			\return vitesse de déplacement
		*/
		int get_drag_speed(void);
		
		/*!
			\fn void move_scene(int x, int y)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à jour du centre de la scène
			\param x abcisse du nouveau centre
			\param y ordonnée du nouveau centre
			\version 1.0
			\return rien
		*/
		void move_scene(int x, int y);
		
		/*!
			\fn void drag_scene(int x, int y)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de déplacement du centre de la scène
			\param x décalage de l'abcisse du centre
			\param y décalage de l'ordonnée du centre
			\version 1.0
			\return rien
		*/
		void drag_scene(int x, int y);
		
		//////////////////////////////////////////
		//		  Fonction d'interaction		//
		//////////////////////////////////////////
		
		/*!
			\fn bool load_from_file(string str_file)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de chargement du fichier
			\param str_file fichier à charger
			\version 1.0
			\return Vrai si tout s'est bien passé
		*/
		bool load_from_file(string str_file);
		
		/*!
			\fn bool test_file(string str_file) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de test du fichier
			\param str_file fichier à tester
			\version 1.0
			\return Vrai si le fichier est correct
		*/
		bool test_file(string str_file) const;

		/*!
			\fn bool rotate_view(double dbl_theta, double dbl_phi)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de rotation
			\param dbl_theta angle theta
			\param dbl_phi angle phi
			\version 1.0
			\return Vrai si tout s'est bien passé
		*/
		bool rotate_view(double dbl_theta, double dbl_phi);
		
		/*!
			\fn void scale(int int_coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à l'échelle de la scène
			\param int_coef coefficient de mide à l'échelle
			\version 1.0
			\return rien
		*/
		void scale(int int_coef);
		
		/*!
			\fn bool zoom(double dbl_coeff)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de zoom
			\param dbl_coeff coefficient de zoom
			\version 1.0
			\return Vrai si tout s'est bien passé
		*/
		bool zoom(double dbl_coeff);
		
		//////////////////////////////////////////
		//		  Fonction d'affichage			//
		//////////////////////////////////////////
		
		/*!
			\fn bool show(AreaView* area, Point_3D pt_screen)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction d'affichage de la scène
			\param area zone d'affichage
			\param pt_screen centre de l'écran
			\version 1.0
			\return Vrai si tout s'est bien passé
		*/
		bool show(AreaView* area, Point_3D pt_screen);
};

#endif
