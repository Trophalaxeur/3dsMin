/*!
  \file Polygon.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief header de la class Polygon
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_POLYGON_HPP__
#define __PROJET_3D_POLYGON_HPP__

#include "../headers.hpp"
#include "../areaview/AreaView.hpp"
#include "../point3D/Point3D.hpp"

class AreaView;
class Point_3D;

class Polygon
{
	private:
		///> Couleur du polygone
		QColor* color_polygon;
		///> Liste des vertices
		vector<Point_3D*> vect_vertice;
		///> Barycentre du polygone
		Point_3D* pt_barycentre;
		///> Booléen indiquat si on utilise ou non une couleur par défaut ou prédéfini
		bool bool_default_color;
		
	public:
		
		//////////////////////////////////////////
		//			Fonction de classe			//
		//////////////////////////////////////////
	
		/*!
			\fn void Polygon(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par défaut
			\version 1.0
			\return rien
		*/
		Polygon();
		
		/*!
			\fn void Polygon(Polygon & other_polygon)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par copie
			\param other_polygon polygone à copier
			\version 1.0
			\return rien
		*/
		Polygon(Polygon & other_polygon);
		
		/*!
			\fn void Polygon(vector<Point_3D*> vertices)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètre
			\param vertices liste de sommets définissant le polygone
			\version 1.0
			\return rien
		*/
		Polygon(vector<Point_3D*> vertices);
		
		/*!
			\fn void Polygon(vector<Point_3D*> vertices, QColor* color)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètres
			\param vertices liste de sommets définissant le polygone
			\param color couleur initiale du polygone
			\version 1.0
			\return rien
		*/
		Polygon(vector<Point_3D*> vertices, QColor* color);
		
		/*!
			\fn void ~Polygon(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Destructeur
			\version 1.0
			\return rien
		*/
		~Polygon(void);
		
		//////////////////////////////////////////
		//				Accesseurs				//
		//////////////////////////////////////////
		
		/*!
			\fn Point_3D* get_vertice(int int_n) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du sommet n
			\param int_n numéro du sommet à récupérer
			\version 1.0
			\return nième sommet
		*/
		Point_3D* get_vertice(int int_n) const;
		
		/*!
			\fn int get_nb_vertice(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération du nombre de vertice
			\version 1.0
			\return le nombre de vertice composant du polygone
		*/
		int get_nb_vertice(void) const;
		
		/*!
			\fn QColor* get_color(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la couleur
			\version 1.0
			\return couleur du polygone
		*/
		QColor* get_color(void);
		
		/*!
			\fn bool is_default_color(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction indiquant si on utilise ou non une couleur par défaut
			\version 1.0
			\return true s'il s'agit de la couleur par défaut
		*/
		bool is_default_color(void);
		
		/*!
			\fn void set_is_default_color(bool state)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction permettant de modifier le statut du couleur par défaut
			\param state nouveau statut d'utilisation de la couleur par défaut
			\version 1.0
			\return rien
		*/
		void set_is_default_color(bool state);
		
		//////////////////////////////////////////
		//		  Fonction d'intéraction		//
		//////////////////////////////////////////
		
		/*!
			\fn bool show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction d'affichage du polygone
			\param area zone d'affichage
			\param origin_view origine de la vue
			\param origin_light origine de la lumière
			\param int_mode_surface mode d'affichage des surfaces
			\param int_mode_line mode d'affichage des lignes
			\param pt_screen centre de l'écran
			\version 1.0
			\return Booléen indiquant si tout s'est bien passé
		*/
		bool show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen);
		
		/*!
			\fn bool project(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de projection du polygone
			\param origin_view origine de la vue
			\version 1.0
			\return rien
		*/
		bool project(struct_point_sphere* origin_view);
		
		/*!
			\fn bool project(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de calcul du barycentre du polygone
			\version 1.0
			\return barycentre du polygone
		*/
		Point_3D* barycentre(void);
		
		/*!
			\fn void move(Point_3D* origin)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de déplacement du polygone par rapport à un point
			\param origin origine du nouveau repère
			\version 1.0
			\return rien
		*/
		void move(Point_3D* origin);
		
		/*!
			\fn void scale(int int_coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à l'échelle du polygone
			\param int_coef Coefficient de mise à l'échelle
			\version 1.0
			\return rien
		*/
		void scale(int int_coef);
		
		/*!
			\fn void paint(QColor color)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de coloriage du polygone
			\param color nouvelle couleur du polygone
			\version 1.0
			\return rien
		*/
		void paint(QColor color);
		
		/*!
			\fn void add_point(Point_3D* pt_to_add)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Ajout d'un point en fin de liste
			\param pt_to_add point à ajouter
			\version 1.0
			\return rien
		*/
		void add_point(Point_3D* pt_to_add);
		
		/*!
			\fn void add_point_after(Point_3D* pt_to_add, Point_3D* pt_ref)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction d'ajout d'un point dans la liste après le point de référence
			\param pt_to_add Point à ajouter
			\param pt_ref Point de référence
			\version 1.0
			\return rien
		*/
		void add_point_after(Point_3D* pt_to_add, Point_3D* pt_ref);

		/*!
			\fn void add_point_before(Point_3D* pt_to_add, Point_3D* pt_ref)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction d'ajout d'un point dans la liste avant le point de référence
			\param pt_to_add Point à ajouter
			\param pt_ref Point de référence
			\version 1.0
			\return rien
		*/
		void add_point_before(Point_3D* pt_to_add, Point_3D* pt_ref);
		
		/*!
			\fn void rem_point(Point_3D* pt_to_rem)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de suppression d'un point de la liste
			\param pt_to_rem point à supprimer
			\version 1.0
			\return rien
		*/
		void rem_point(Point_3D* pt_to_rem);
		
		/*!
			\fn int get_id(Point_3D* pt_ref)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de recherche d'un point en fonction de son identifiant
			\param pt_ref Point de référence
			\version 1.0
			\return identifiant de point de référence dans la liste
		*/
		int get_id(Point_3D* pt_ref);
		
		/*!
			\fn void clean(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de nettoyage du polygone
			\version 1.0
			\return rien
		*/
		void clean(void);
		
		/*!
			\fn void order(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de tri des points du polygone
			\version 1.0
			\return rien
		*/
		void order(void);

		/*!
			\fn vector<Polygon*> subdivide_byref(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de subdivision du polygone en triangle (sommet : un des points)
			\version 1.0
			\return tableau de triangle
		*/
		vector<Polygon*> subdivide_byref(void);

		/*!
			\fn vector<Polygon*> subdivide_byref(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de subdivision du polygone en triangle (sommet : barycentre)
			\version 1.0
			\return tableau de triangle
		*/
		vector<Polygon*> subdivide_bybarycentre(void);
		
		/*!
			\fn void reset_polygon(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de réinitialisation du polygone
			\version 1.0
			\return rien
		*/
		void reset_polygon(void);
		
		/*!
			\fn void reset_polygon(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'équation du plan formé par les trois premier points
			\version 1.0
			\return équation du plan
		*/
		struct_eq_plan* equation_plan(void);
};

#endif
