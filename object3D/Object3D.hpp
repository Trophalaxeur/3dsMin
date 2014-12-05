/*!
  \file Object3D.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief header de la class Object_3D
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_OBJECT3D_HPP__
#define __PROJET_3D_OBJECT3D_HPP__

#include "../headers.hpp"
#include "../polygon/Polygon.hpp"
#include "../point3D/Point3D.hpp"
#include "../areaview/AreaView.hpp"

class Polygon;
class Point_3D;
class AreaView;

using namespace std;

//Fonction de tri des polygones
bool sort_polygon(Polygon* poly_first, Polygon* poly_second);

class Object_3D
{
	private:
		///> Liste de polygones
		list<Polygon*> list_polygon;
		///> Barycentre de l'objet 3d
		Point_3D* pt_barycentre;
		///>Distance moyenne des points
		double dbl_distance_med;
		///>Coefficient de grossissement
		float flt_coef;
		///>Chemin d'accès au fichier
		string str_path;
		
	public:
		
		//////////////////////////////////////////
		//			Fonction de classe			//
		//////////////////////////////////////////
	
		/*!
			\fn void Object_3D(Object_3D & other_object)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par copie
			\param other_object objet 3d à copier
			\version 1.0
			\return rien
		*/
		Object_3D(Object_3D & other_object);
		
		/*!
			\fn void Object_3D(string file_off)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètre
			\param file_off chemin d'accès au fichier
			\version 1.0
			\return rien
		*/
		Object_3D(string file_off);
		
		/*!
			\fn void Object_3D(string file_off, Point_3D* origin, float coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètre
			\param file_off chemin d'accès au fichier
			\param origin point d'origine du repère de référence
			\param coef coefficient de grossissement de l'objet
			\version 1.0
			\return rien
		*/
		Object_3D(string file_off, Point_3D* origin, float coef);
		
		/*!
			\fn void ~Object_3D(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Destructeur
			\version 1.0
			\return rien
		*/
		~Object_3D();
		
		//////////////////////////////////////////
		//				Opérateurs				//
		//////////////////////////////////////////
		
		/*!
			\fn bool operator<(Object_3D & other_object)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Surcharge de l'opérateur d'infériorité
			\param other_object objet de comparaison
			\version 1.0
			\return true si l'objet est inférieur à l'objet de comparaiso
		*/
		bool operator<(Object_3D & other_object);
		
		//////////////////////////////////////////
		//				Accesseurs				//
		//////////////////////////////////////////
		
		/*!
			\fn Polygon* get_polygon(int int_n) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du nième polygone
			\param int_n numéro du polygone à récupérer
			\version 1.0
			\return nième polygone
		*/
		Polygon* get_polygon(int int_n) const;
		
		/*!
			\fn int get_nb_polygon(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du nombre de polygone
			\version 1.0
			\return nombre polygone
		*/
		int get_nb_polygon(void) const;
		
		/*!
			\fn Point_3D* barycentre(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du barycentre
			\version 1.0
			\return barycentre du polygone
		*/
		Point_3D* barycentre(void);
		
		/*!
			\fn double get_distance_med(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la distance moyenne
			\version 1.0
			\return distance moyenne des points au centre
		*/
		double get_distance_med(void);
		
		/*!
			\fn void paint(QColor color)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de coloriage de l'objet
			\param color nouvelle couleur de l'objet
			\version 1.0
			\return rien
		*/
		void paint(QColor color);
		
		/*!
			\fn string get_path(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du chemin du fichier
			\version 1.0
			\return chemin d'accès au fichier
		*/
		string get_path(void);
		
		//////////////////////////////////////////
		//		  Fonction d'intéraction		//
		//////////////////////////////////////////
		
		/*!
			\fn bool load_from_file(string str_file, Point_3D* pt_origin, bool bool_auto_scale)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Lecture du fichier OFF
			\param str_file chemin d'accès au fichier
			\param pt_origin point d'origine du repère de la scène
			\param bool_auto_scale mise à l'échelle automatique de l'obje
			\version 1.0
			\return Booléen indiquant si tou s'est bien passé
		*/
		bool load_from_file(string str_file, Point_3D* pt_origin, bool bool_auto_scale);
		
		/*!
			\fn void save_in_file(string str_file)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Sauvegarde dans un fichier OFF
			\param str_file fichier dans lequel l'objet OFF doit être sauvegardé
			\version 1.0
			\return rien
		*/
		void save_in_file(string str_file);
		
		/*!
			\fn bool test_file(string str_file) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de test du fichier OFF
			\param str_file ficheir à tester
			\version 1.0
			\return Vrai si le fichier est OK
		*/
		bool test_file(string str_file) const;
		
		/*!
			\fn bool project(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de projection de l'objet
			\param origin_view point d'origine de la vue
			\version 1.0
			\return Vrai si tout s'est bien passé
		*/
		bool project(struct_point_sphere* origin_view);
		
		/*!
			\fn bool show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction d'affichage de l'objet
			\param area zone d'affichage
			\param origin_view point d'origine de la vue
			\param origin_light point d'origine de la lumière
			\param int_mode_surface mode d'affichage des surfaces
			\param int_mode_line mode d'affichage des lignes
			\param pt_screen centre de l'écran
			\version 1.0
			\return Vai si l'affichage s'est bien passé
		*/
		bool show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen);
		
		/*!
			\fn Point_3D* calc_barycentre(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de calcul du barycentre
			\version 1.0
			\return barycentre de l'objet
		*/
		Point_3D* calc_barycentre(void);
		
		/*!
			\fn void move(Point_3D* origin)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de déplacement de l'objet 3D par rapport à un point
			\param origin orgine du nouveau repère
			\version 1.0
			\return rien
		*/
		void move(Point_3D* origin);
		
		/*!
			\fn void scale(int int_coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à l'échelle de l'objet
			\param int_coef coefficient de mise à l'échelle
			\version 1.0
			\return rien
		*/
		void scale(int int_coef);
		
		/*!
			\fn void concat_with(Object_3D* object1)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction qui permet de concaténer deux objets
			\param object1 objet à ajouter
			\version 1.0
			\return rien
		*/
		void concat_with(Object_3D* object1);
		
		/*!
			\fn void add_polygon(Polygon* poly_to_add)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Ajoute un polygone à l'objet
			\param poly_to_add polygone à ajouter
			\version 1.0
			\return rien
		*/
		void add_polygon(Polygon* poly_to_add);
		
		/*!
			\fn void subdivide_byref(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Subdivise les polygones de l'objet par point de référence
			\version 1.0
			\return rien
		*/
		void subdivide_byref(void);
		
		/*!
			\fn void polish(float flt_puiss)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de polissage de l'objet 3d
			\param flt_puiss puissance du polissage
			\version 1.0
			\return rien
		*/
		void polish(float flt_puiss);
		
		/*!
			\fn int get_nb_vertices(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du nombre de point total de l'objet
			\version 1.0
			\return nombre de points total de l'objet
		*/
		int get_nb_vertices(void);
		
		/*!
			\fn int get_nb_single_vertices(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du nombre de points uniques de l'objet
			\version 1.0
			\return nombre de points unique de l'objet
		*/
		int get_nb_single_vertices(void);
		
		/*!
			\fn void reset_object(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de réinitialisation de l'objet
			\version 1.0
			\return rien
		*/
		void reset_object(void);
		
	private:
		/*!
			\fn Point_3D* create_point(Polygon** polygon, Point_3D* point, int int_pos, float flt_puiss)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction complémentaire de la fonction de polissage
			\param polygon pointeur sur le polygone à modifier
			\param point point de référence
			\param int_pos direction de la modification
			\param flt_puiss puissance du polissage
			\version 1.0
			\return nouveau point à ajouter
		*/
		Point_3D* create_point(Polygon** polygon, Point_3D* point, int int_pos, float flt_puiss);
};

#endif
