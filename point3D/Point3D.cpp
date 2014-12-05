/*!
  \file Point3D.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief code de la classe Point_3D
  \date 13/05/2008
  \version 1.0
*/

#include "Point3D.hpp"

Point_3D::Point_3D()
{
	//Initialisation des coordonnées du point aux valeurs par défaut (0, 0, 0)
	dbl_x=0;
	dbl_y=0;
	dbl_z=0;
	dbl_x_origin=0;
	dbl_y_origin=0;
	dbl_z_origin=0;
	
	bool_etat=true;
}

Point_3D::Point_3D(const Point_3D & other_point)
{
	//Copie des coordonnées de l'ancien point vers le nouveau
	dbl_x=other_point.get_x();
	dbl_y=other_point.get_y();
	dbl_z=other_point.get_z();
	dbl_x_origin=other_point.get_x();
	dbl_y_origin=other_point.get_y();
	dbl_z_origin=other_point.get_z();
	
	bool_etat=other_point.get_statut();
}

Point_3D::Point_3D(double x, double y, double z)
{
	//Sauvegarde des coordonnées passé en parametre
	dbl_x=x;
	dbl_y=y;
	dbl_z=z;
	dbl_x_origin=x;
	dbl_y_origin=y;
	dbl_z_origin=z;
	
	bool_etat=true;
}

Point_3D::Point_3D(double x, double y, double z, bool etat)
{
	//Sauvegarde des coordonnées passé en parametre
	dbl_x=x;
	dbl_y=y;
	dbl_z=z;
	dbl_x_origin=x;
	dbl_y_origin=y;
	dbl_z_origin=z;
	
	bool_etat=etat;
}


Point_3D::~Point_3D()
{
	//Destructeur du point 3D
}

void Point_3D::reset_point(void)
{
	//Remise à zéro des coordonnées
	dbl_x=dbl_x_origin;
	dbl_y=dbl_y_origin;
	dbl_z=dbl_z_origin;
}

double Point_3D::get_x_origin(void) const
{
	//Retourne l'abscisse d'origine du point
	return(dbl_x_origin);
}

double Point_3D::get_y_origin(void) const
{
	//Retourne l'ordonnée d'origine du point
	return(dbl_y_origin);
}

double Point_3D::get_z_origin(void) const
{
	//Retourne la profondeur d'origine du point
	return(dbl_z_origin);
}

double Point_3D::get_x(void) const
{
	//Retourne l'abscisse du point
	return(dbl_x);
}


void Point_3D::set_x(double x)
{
	//Sauvegarde l'abcisse du point
	dbl_x=x;
}


double Point_3D::get_y(void) const
{
	//Retourne l'ordonnée du point
	return(dbl_y);
}


void Point_3D::set_y(double y)
{
	//Sauvegarde l'ordonnée du point
	dbl_y=y;
}


double Point_3D::get_z(void) const
{
	//Retourne la profondeur du point
	return(dbl_z);
}


void Point_3D::set_z(double z)
{
	//Sauvegarde de la profondeur du point
	dbl_z=z;
}

bool Point_3D::get_statut(void) const
{
	//Retourne l'état du point
	return(bool_etat);
}

void Point_3D::set_statut(bool etat)
{
	//Sauvegarde de l'état du point
	bool_etat=etat;
}

bool Point_3D::project(struct_point_sphere* origin_view)
{
	//Booléen de retour
	bool bool_retour;
	
	//Initialisation du booléen de retour
	bool_retour=true;
	
	//Projection suivant l'angle phi
	bool_retour=bool_retour && project_phi(origin_view);
	//Projection suivant l'angle theta
	bool_retour=bool_retour && project_theta(origin_view);
	
	//Retourne le booléen de retour
	return(bool_retour);
	
}
bool Point_3D::project_theta(struct_point_sphere* origin_view)
{
	//Porjection du point sur le plan xOz
	double pa;
	//Angle theta du point V
	double theta;
	//Ancienne ordonnée du point
	double y;
	//Ancienne profondeur du point
	double z;
	
	//Sauvegarde des coordonnées x, y et z du point
	y=dbl_y;
	z=dbl_z;
	
	//Récupération de l'angle theta
	theta=origin_view->dbl_theta;
	
	//Calcul de la projection du point sur le plan
	pa=sqrt(z*z+y*y);
	
	//Calcul de la nouvelle abcsisse du point
	dbl_z=z*cos(theta)-y*sin(theta);
	//Calcul de la nouvelle profondeur du point
	dbl_y=y*cos(theta)+z*sin(theta);
	
	//Tout s'est bien passé
	return(true);
}

bool Point_3D::project_phi(struct_point_sphere* origin_view)
{
	//Porjection du point sur le plan xOz
	double pa;
	//Angle phi du point V
	double phi;
	//Ancienne abcsisse du point
	double x;
	//Ancienne profondeur du point
	double z;
	
	//Sauvegarde des coordonnées x, y et z du point
	x=dbl_x_origin;
	z=dbl_z_origin;
	
	//Récupération de l'angle phi
	phi=origin_view->dbl_phi;
	
	//Calcul de la projection du point sur le plan
	pa=sqrt(x*x+z*z);
	
	//Calcul de la nouvelle abcsisse du point
	dbl_x=(x*cos(phi)-z*sin(phi));
	//Calcul de la nouvelle ordonnée du point
	dbl_y=dbl_y_origin;
	//Calcul de la nouvelle profondeur du point
	dbl_z=(z*cos(phi)+x*sin(phi));
	
	//Tout s'est bien passé
	return(true);
}


double Point_3D::distance(const Point_3D & point_compare) const
{
	//Coordonnée du point à comparer
	double x;
	double y;
	double z;
	
	//Récupération de l'abcisse du point à comparer
	x=point_compare.get_x();
	//Récupération de l'ordonnée du point à comparer
	y=point_compare.get_y();
	//Récupération de la profondeur du point à comparer
	z=point_compare.get_z();
	
	//Retourne la distance entre les deux points
	return(sqrt(pow(dbl_x-x, 2)+pow(dbl_y-y, 2)+pow(dbl_z-z, 2)));
}

void Point_3D::move(Point_3D* origin)
{
	//Mise à jour de l'abcisse
	set_x(get_x()-origin->get_x());
	//Mise à jour de l'ordonnée
	set_y(get_y()-origin->get_y());
	//Mise à jour de la profondeur
	set_z(get_z()-origin->get_z());
	//Mise à jour de l'abcisse d'origine
	dbl_x_origin-=origin->get_x();
	//Mise à jour de l'ordonnée d'origine
	dbl_y_origin-=origin->get_y();
	//Mise à jour de la profondeur d'origin
	dbl_z_origin-=origin->get_z();
}

void Point_3D::scale(int coef)
{
	//Mise à jour de l'abcisse
	set_x(coef*get_x());
	//Mise à jour de l'ordonnée
	set_y(coef*get_y());
	//Mise à jour de la profondeur
	set_z(coef*get_z());
	//Mise à jour de l'abcisse d'origine
	dbl_x_origin=dbl_x_origin*coef;
	//Mise à jour de l'ordonnée d'origine
	dbl_y_origin=dbl_y_origin*coef;
	//Mise à jour de la profondeur d'origin
	dbl_z_origin=dbl_z_origin*coef;
}

bool Point_3D::operator==(const Point_3D & pt_other) const
{
	//Retourne la correspondance entre les abcisses, les ordonnées et les profondeurs des deux points
	return((get_x()==pt_other.get_x()) && (get_y()==pt_other.get_y()) && (get_z()==pt_other.get_z()));
}

bool Point_3D::operator<(const Point_3D & pt_other) const
{
	//Compare les distance des deux points
	return(distance(Point_3D(0, 0, 0))<pt_other.distance(Point_3D(0, 0, 0)));
}

void Point_3D::show(AreaView* area, struct_point_sphere* origin_view, Point_3D pt_screen) const
{
	//Abcisse du point sur l'écran
	int int_x;
	//Ordonnée du point sur l'écran
	int int_y;
	//Coefficient temporaire
	double dbl_coef;
	//Création de la zone de dessin à partir de la zone d'affichage
	QPainter painter(area);
	//Calcul du coefficient temporaire
	dbl_coef=(PLAN_X+origin_view->dbl_r)/(PLAN_X-get_z());
	//Calcul de l'abcisse du point
	int_x=(int)(get_x()*dbl_coef+(pt_screen.get_x())/2.0);
	//Calcul de l'ordonnée du point
	int_y=(int)(pt_screen.get_y()/2.0-get_y()*dbl_coef);
	//Affichage du point projeté sur l'écran
	painter.drawPoint(int_x, int_y);
}

double Point_3D::angle(const Point_3D & pt_a, const Point_3D & pt_b)
{
	//Coordonnées du premier point
	double dbl_x_a;
	double dbl_y_a;
	double dbl_z_a;
	//Coordonnées du second point
	double dbl_x_b;
	double dbl_y_b;
	double dbl_z_b;
	
	//Sauvegarde des coordonnées du premier point dans le repère de centre this
	dbl_x_a=pt_a.get_x()-get_x();
	dbl_y_a=pt_a.get_y()-get_y();
	dbl_z_a=pt_a.get_z()-get_z();
	//Sauvegarde des coordonnées du second point dans le repère de centre this
	dbl_x_b=pt_b.get_x()-get_x();
	dbl_y_b=pt_b.get_y()-get_y();
	dbl_z_b=pt_b.get_z()-get_z();
	
	//Renvoit l'angle entre les deux points de sommet this
	return(acos((dbl_x_a*dbl_x_b+dbl_y_a*dbl_y_b+dbl_z_a*dbl_z_b)/(sqrt(dbl_x_a*dbl_x_a+dbl_y_a*dbl_y_a+dbl_z_a*dbl_z_a)*sqrt(dbl_x_b*dbl_x_b+dbl_y_b*dbl_y_b+dbl_z_b*dbl_z_b))));
}

double Point_3D::eq_in_plan(struct_eq_plan* eq_plan)
{
	return(eq_plan->dbl_a*get_x()+eq_plan->dbl_b*get_y()+eq_plan->dbl_c*get_z()+eq_plan->dbl_d);
}
