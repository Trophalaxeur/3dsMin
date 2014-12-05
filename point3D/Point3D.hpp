/*!
  \file Point3D.hpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief header de la classe Point_3D
  \date 13/05/2008
  \version 1.0
*/

#ifndef __PROJET_3D_POINT3D_HPP__
#define __PROJET_3D_POINT3D_HPP__

#include "../headers.hpp"
#include "../areaview/AreaView.hpp"

class AreaView;

class Point_3D
{
	private:
		///> Abscisse du point
		double dbl_x;
		///> Ordonnée du point
		double dbl_y;
		///> Profondeur du point
		double dbl_z;
		///> Abcisse d'origine
		double dbl_x_origin;
		///> Ordonnée d'origine
		double dbl_y_origin;
		///> Profondeur d'origine
		double dbl_z_origin;
		///> Etat du point (true=validé, false=temporaire)
		bool bool_etat;
		
	public:
		
		//////////////////////////////////////////
		//			Fonction de classe			//
		//////////////////////////////////////////
	
		/*!
			\fn void Point_3D(void);
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par défaut
			\version 1.0
			\return rien
		*/
		Point_3D();
		
		/*!
			\fn void Point_3D(const Point_3D & other_point);
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par copie
			\param other_point point à copier
			\version 1.0
			\return rien
		*/
		Point_3D(const Point_3D & other_point);
		
		/*!
			\fn void Point_3D(double x, double y, double z)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètres
			\param x abcisse du point
			\param y ordonnée du point
			\param z profondeur du point
			\version 1.0
			\return rien
		*/
		Point_3D(double x, double y, double z);
		
		/*!
			\fn void Point_3D(double x, double y, double z, bool etat)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Constructeur par paramètres
			\param x abcisse du point
			\param y ordonnée du point
			\param z profondeur du point
			\param etat etat du point
			\version 1.0
			\return rien
		*/
		Point_3D(double x, double y, double z, bool etat);
		
		/*!
			\fn void ~Point_3D(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Destructeur
			\version 1.0
			\return rien
		*/
		~Point_3D();
		
		//////////////////////////////////////////
		//				Accesseurs				//
		//////////////////////////////////////////
		
		/*!
			\fn double get_x_origin(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'abcisse d'origine
			\version 1.0
			\return abcisse d'origine (double)
		*/
		double get_x_origin(void) const;
		
		/*!
			\fn double get_y_origin(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'ordonnée d'origine
			\version 1.0
			\return ordonnée d'origine (double)
		*/
		double get_y_origin(void) const;
		
		/*!
			\fn double get_z_origin(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la profondeur d'origine
			\version 1.0
			\return profondeur d'origine (double)
		*/
		double get_z_origin(void) const;
		
		/*!
			\fn double get_x(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'abcisse
			\version 1.0
			\return abcisse (double)
		*/
		double get_x(void) const;
		
		/*!
			\fn double get_y(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'ordonnée
			\version 1.0
			\return ordonnée (double)
		*/
		double get_y(void) const;
		
		/*!
			\fn double get_z(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de la profondeur
			\version 1.0
			\return profondeur (double)
		*/
		double get_z(void) const;
		
		/*!
			\fn void set_x(double x)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'abcisse
			\param x nouvelle abcisse
			\version 1.0
			\return rien
		*/
		void set_x(double x);
		
		/*!
			\fn void set_y(double y)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'ordonnée
			\param y nouvelle ordonnée
			\version 1.0
			\return rien
		*/
		void set_y(double y);
		
		/*!
			\fn void set_z(double z)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de la profondeur
			\param z nouvelle profondeur
			\version 1.0
			\return rien
		*/
		void set_z(double z);
		
		///>Fonction de récupération de l'état du point
		/*!
			\fn bool get_statut(void) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de récupération de l'état du point
			\version 1.0
			\return état actuel du point
		*/
		bool get_statut(void) const;
		
		/*!
			\fn void set_statut(bool etat)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de modification de l'état du point
			\param etat nouvel état du point
			\version 1.0
			\return rien
		*/
		void set_statut(bool etat);
		
		//////////////////////////////////////////
		//		  Fonction d'intéraction		//
		//////////////////////////////////////////
		
		/*!
			\fn bool project(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de projection du point
			\param origin_view point d'origine de la vue
			\version 1.0
			\return booléen indiquant si tout s'est bien passé
		*/
		bool project(struct_point_sphere* origin_view);
		
		/*!
			\fn double distance(const Point_3D & point_compare) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de calcul d'une distance entre deux points
			\param point_compare second point
			\version 1.0
			\return distance entre le second point et le point actuel
		*/
		double distance(const Point_3D & point_compare) const;
		
		/*!
			\fn void move(Point_3D* origin)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de déplacement du point
			\param origin point d'origine du nouveau repère
			\version 1.0
			\return rien
		*/
		void move(Point_3D* origin);
		
		/*!
			\fn void show(AreaView* area, struct_point_sphere* origin_view, Point_3D pt_screen) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de d'affichage du point
			\param area zone d'affichage
			\param origin_view point d'origine de la vue
			\param pt_screen position du centre de l'objet sur l'écran
			\version 1.0
			\return rien
		*/
		void show(AreaView* area, struct_point_sphere* origin_view, Point_3D pt_screen) const;
		
		/*!
			\fn double angle(const Point_3D & pt_a, const Point_3D & pt_b)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de calcul d'angle entre deux points (sommet = this)
			\param pt_a premier point de la base opposé au sommet
			\param pt_b second point de la base opposé au sommet
			\version 1.0
			\return angle du triangle de sommet this et de base pt_a et pt_b
		*/
		double angle(const Point_3D & pt_a, const Point_3D & pt_b);
		
		/*!
			\fn void scale(int coef)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de mise à l'échelle du point
			\param coef coefficient de mise à l'échelle
			\version 1.0
			\return rien
		*/
		void scale(int coef);
		
		/*!
			\fn void reset_point(void)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de remise à zéro des coordonnées du point
			\version 1.0
			\return rien
		*/
		void reset_point(void);
		
		//////////////////////////////////////////
		//		  		Opérateurs				//
		//////////////////////////////////////////
		
		/*!
			\fn bool operator==(const Point_3D & pt_other) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Surcharge de l'opérateur d'égalité entre deux points
			\param pt_other point de comparaison
			\version 1.0
			\return Vrai si le deux points sont égaux
		*/
		bool operator==(const Point_3D & pt_other) const;
		
		/*!
			\fn bool operator<(const Point_3D & pt_other) const
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Surcharge de l'opérateur d'infériorité entre deux points
			\param pt_other point de comparaison
			\version 1.0
			\return Vrai si le point actuel est inférieur au point de comparaison
		*/
		bool operator<(const Point_3D & pt_other) const;
		
		//////////////////////////////////////////
		//		  Fonction d'intéraction		//
		//////////////////////////////////////////
		
		/*!
			\fn double eq_in_plan(struct_eq_plan* eq_plan)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Calcul de la distance entre le plan et le point
			\param eq_plan Equation du plan
			\version 1.0
			\return distance entre le plan et le point
		*/
		double eq_in_plan(struct_eq_plan* eq_plan);
		
	private:
		/*!
			\fn bool project_theta(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de projection du point selon l'angle theta
			\param origin_view origine de la vue
			\version 1.0
			\return booléen indiquant si le projection s'est bien passé
		*/
		bool project_theta(struct_point_sphere* origin_view);
		
		/*!
			\fn bool project_phi(struct_point_sphere* origin_view)
			\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
			\brief Fonction de projection du point selon l'angle phi
			\param origin_view origine de la vue
			\version 1.0
			\return booléen indiquant si le projection s'est bien passé
		*/
		bool project_phi(struct_point_sphere* origin_view);
		
		
};

#endif
