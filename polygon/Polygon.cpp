/*!
\file Polygon.cpp
\author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
\brief code de la class Polygon
\date 13/05/2008
\version 1.0
*/

#include "Polygon.hpp"

Polygon::Polygon()
{
	//Point temporaire
	Point_3D* pt_temp;
	
	//Construction du polygone par défaut (triangle)
	//Initialisation des 3 sommets et ajout dans la liste des vertices
	pt_temp=new Point_3D;
	vect_vertice.push_back(pt_temp);
	pt_temp=new Point_3D;
	vect_vertice.push_back(pt_temp);
	pt_temp=new Point_3D;
	vect_vertice.push_back(pt_temp);
	
	//Itialisation du barycentre
	pt_barycentre=new Point_3D;
	
	//Utilisation de la couleur par défaut
	bool_default_color=true;
}

Polygon::Polygon(Polygon & other_polygon)
{
	//Point temporaire
	Point_3D* pt_temp;
	//Nombre de sommets à copier
	int nbre_vertice;
	//Variable de boucle
	int i;
	
	//Récupération du nombre de sommet à copier
	nbre_vertice=other_polygon.get_nb_vertice();
	
	//Pour chacun des sommets
	for(i=0;i<nbre_vertice;i++)
	{
		//Création par copie du point 3D
		pt_temp=new Point_3D(*(other_polygon.get_vertice(i)));
		//Ajout du point à la liste des vertices
		vect_vertice.push_back(pt_temp);
	}
	
	//Récupération du booléen indiquant si on utilise la couleur par défaut
	bool_default_color=other_polygon.is_default_color();
	
	//Copie de la couleur
	color_polygon=new QColor(*(other_polygon.get_color()));
	
	//Copie du barycentre
	pt_barycentre=new Point_3D(*(other_polygon.barycentre()));
}

Polygon::Polygon(vector<Point_3D*> vertices)
{	
	//Sauvegarde de la liste des vertices
	vect_vertice=vertices;
	//Création de la couleur
	color_polygon=new QColor(90,135,255);
	//Utilisation de la couleur par défaut
	bool_default_color=true;
	//Initialisation du barycentre
	pt_barycentre=NULL;
	//Calcul du barycentre
	barycentre();
}

Polygon::Polygon(vector<Point_3D*> vertices, QColor* color)
{
	//Sauvegarde de la liste des vertices
	vect_vertice=vertices;
	//Sauvegarde de la couleur
	color_polygon=color;
	//On n'utilise pas la couleur par défaut
	bool_default_color=false;
	//Initialisation du barycentre
	pt_barycentre=NULL;
	
	//Calcul du barycentre
	barycentre();
}

Polygon::~Polygon(void)
{
	//Variable de boucle
	int i;
	//Nombre de sommets
	int nbre_sommets;
	
	//Récupération du nombre de sommet
	nbre_sommets=get_nb_vertice();
	
	//On détruit chacun des points composant le polygone
	for(i=0;i<nbre_sommets;i++) delete vect_vertice[i];
	
	//Destruction du barycentre
	delete pt_barycentre;
	//Destruction de la couleur
	delete color_polygon;
}

Point_3D* Polygon::get_vertice(int int_n) const
{
	//Si le sommet demandé n'existe pas
	if(int_n>get_nb_vertice()) return(NULL);
	
	//Retourne le vertice numéro int_n
	return(vect_vertice[int_n]);
}

int Polygon::get_nb_vertice(void) const
{
	//On retourne le nombre de vertices composant la liste
	return(vect_vertice.size());
}

QColor* Polygon::get_color(void)
{
	//On retourne la couleur
	return(color_polygon);
}

bool Polygon::is_default_color(void)
{
	//Renvoit le booléen d'utilisation de la couleur par défaut
	return(bool_default_color);
}

void Polygon::set_is_default_color(bool state)
{
	//Mise à jour du booléen d'utilisation de la couleur par défaut
	bool_default_color=state;
}

bool Polygon::show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen)
{	
	//Variable de boucle
	int i;
	//Nombre de sommet du polygone
	int nbre_sommet;
	//Abcisse du point à afficher
	int int_x;
	//Ordonnée du point à afficher
	int int_y;
	//Coefficient temporaire
	double dbl_coef;
	//Coefficient de luminosité
	double dbl_coef_light;
	//Abcisse du point lumineux
	double dbl_lx;
	//Ordonnée du point lumineux
	double dbl_ly;
	//Profondeur du point lumineux
	double dbl_lz;
	//Nouvelle quantité de rouge
	int int_red;
	//Nouvelle quantité de vert
	int int_green;
	//Nouvelle quantité de bleu
	int int_blue;
	//Point temporaire
	Point_3D* pt_temp;
	//Coefficient de rayon de la lumière
	double dbl_light_circle;
	//Centre de la scene
	Point_3D pt_centre;
	
	//Initialisation du coefficient de la lumière
	dbl_light_circle=1.0;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	
	//Création d'une zone de dessin QT
	QPainter painter(area);
	//Création d'un polygone QT
	QPolygon poly(nbre_sommet);
	
	//Pour chacun des sommets
	for(i=0;i<nbre_sommet;i++)
	{
		//Sauvegarde du point temporaire
		pt_temp=vect_vertice[i];
		dbl_coef=(PLAN_X+origin_view->dbl_r)/(PLAN_X-pt_temp->get_z());
		//Calcul de l'abcisse du point
		int_x=(int)(pt_temp->get_x()*dbl_coef+(pt_screen.get_x())/2);
		//Calcul de l'ordonnée du point
		int_y=(int)((pt_screen.get_y())/2-pt_temp->get_y()*dbl_coef);
		//On stocke les coordonnées du point dans le polygone QT
		poly.setPoint(i, int_x, int_y);
	}
	
	//Si on affiche la surface en mode solide
	if(int_mode_surface==MODE_SURFACE_SOLID_LIGHT)
	{
		//Calcul de l'abcisse du point lumineux
		dbl_lx=PLAN_X*sin(origin_light->dbl_theta)*sin(origin_light->dbl_phi);
		//Calcul de l'ordonnée du point lumineux
		dbl_ly=PLAN_X*cos(origin_light->dbl_theta);
		//Calcul de la profondeur du point lumineux
		dbl_lz=PLAN_X*sin(origin_light->dbl_theta)*cos(origin_light->dbl_phi);
		
		//Calcul du coefficient de luminosité
		dbl_coef_light=(((origin_light->dbl_r*10.0)/(6.28318531))*acos((pt_barycentre->get_x()*dbl_lx+pt_barycentre->get_y()*dbl_ly+pt_barycentre->get_z()*dbl_lz)/(dbl_light_circle*(pt_barycentre->distance(pt_centre))*sqrt(dbl_lx*dbl_lx+dbl_ly*dbl_ly+dbl_lz*dbl_lz)))-50)/100.0;
		
		//Vérification de la composante rouge
		if((int_red=color_polygon->red()-(int)(color_polygon->red()*dbl_coef_light))>255) int_red=255;
		if(int_red<0) int_red=0;
		
		//Vérification de la composante verte
		if((int_green=color_polygon->green()-(int)(color_polygon->green()*dbl_coef_light))>255) int_green=255;
		if(int_green<0) int_green=0;
		
		//Vérification de la composante bleue
		if((int_blue=color_polygon->blue()-(int)(color_polygon->blue()*dbl_coef_light))>255) int_blue=255;
		if(int_blue<0) int_blue=0;
		
		//Création de la brosse de couleur
		painter.setBrush(QColor(int_red, int_green, int_blue,color_polygon->alpha()));
		//Si on est en mode ligne discrete
		if(int_mode_line==MODE_LINE_MIDDLE) painter.setPen(QColor(abs(int_red-10), abs(int_green-10), abs(int_blue-10)));
		//Si on est en mode sans ligne
		if(int_mode_line==MODE_LINE_NONE) painter.setPen(QColor(int_red, int_green, int_blue));
	}
	else if(int_mode_surface==MODE_SURFACE_SOLID)
	{
		//Création de la brosse de couleur
		painter.setBrush(*color_polygon);
		//Si on est en mode ligne discrete
		if(int_mode_line==MODE_LINE_MIDDLE) painter.setPen(QColor(abs(color_polygon->red()-10), abs(color_polygon->green()-10), abs(color_polygon->blue()-10)));
		//Si on est en mode sans ligne
		if(int_mode_line==MODE_LINE_NONE) painter.setPen(*color_polygon);
	}
	
	//Affichage du polygone
	painter.drawPolygon(poly);
	
	//Tout s'est bien passé
	return(true);
}

bool Polygon::project(struct_point_sphere* origin_view)
{
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	//Booléen de retour
	bool bool_retour;
	
	//Initialisation du booléen de retour
	bool_retour=true;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	
	//Pour chacun des sommets, on projete le point associé
	for(i=0; i<nbre_sommet; i++) bool_retour=bool_retour && vect_vertice[i]->project(origin_view);
	
	//On retourne le booléen de retour
	return(bool_retour);
}

Point_3D* Polygon::barycentre(void)
{
	//Somme des abcisses
	double dbl_sum_x;
	//Somme des ordonnées
	double dbl_sum_y;
	//Somme des profondeurs
	double dbl_sum_z;
	//Nombre de sommet
	int nbre_sommet;
	//Variable de boucle
	int i;
	
	//Initialisation des sommes
	dbl_sum_x=0;
	dbl_sum_y=0;
	dbl_sum_z=0;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	
	//Calcul de la somme des abcisses de chaque points
	for(i=0;i<nbre_sommet;i++) dbl_sum_x+=vect_vertice[i]->get_x();
	
	//Calcul de la somme des ordonnées de chaque points
	for(i=0;i<nbre_sommet;i++) dbl_sum_y+=vect_vertice[i]->get_y();
	
	//Calcul de la somme des profondeurs de chaque points
	for(i=0;i<nbre_sommet;i++) dbl_sum_z+=vect_vertice[i]->get_z();
	
	//Création du barycentre s'il n'existe pas
	if(pt_barycentre==NULL) pt_barycentre=new Point_3D(dbl_sum_x/nbre_sommet, dbl_sum_y/nbre_sommet, dbl_sum_z/nbre_sommet);
	//Autrement
	else
	{
		//Mise à jour de l'abcisse du barycentre
		pt_barycentre->set_x(dbl_sum_x/nbre_sommet);
		//Mise à jour de l'ordonnée du barycentre
		pt_barycentre->set_y(dbl_sum_y/nbre_sommet);
		//Mise à jour de la profondeur du barycentre
		pt_barycentre->set_z(dbl_sum_z/nbre_sommet);
	}
	
	//On retourne le barycentre
	return(pt_barycentre);
}

void Polygon::move(Point_3D* origin)
{
	//Variable de boucle
	int i;
	//Nombre de vertices
	int nbre_sommet;
	
	//Récupération du nombre de vertice
	nbre_sommet=get_nb_vertice();
	
	//Pour chacun des points du polygones, on déplace ce point
	for(i=0;i<nbre_sommet;i++) vect_vertice[i]->move(origin);
}

void Polygon::scale(int int_coef)
{
	//Variable de boucle
	int i;
	//Nombre de vertices
	int nbre_sommet;
	
	//Récupération du nombre de vertice
	nbre_sommet=get_nb_vertice();
	
	//Pour chacun des points du polygones, on change l'échelle
	for(i=0;i<nbre_sommet;i++) vect_vertice[i]->scale(int_coef);
}

void Polygon::paint(QColor color)
{
	//Si on utilise la couleur par défaut
	if(bool_default_color)
	{
		//Récupération de la composante rouge
		color_polygon->setRed(color.red());
		//Récupération de la composante verte
		color_polygon->setGreen(color.green());
		//Récupération de la composante bleu
		color_polygon->setBlue(color.blue());
	}
}

void Polygon::add_point(Point_3D* pt_to_add)
{
	//Ajout du point à la liste
	vect_vertice.push_back(pt_to_add);
}

void Polygon::add_point_after(Point_3D* pt_to_add, Point_3D* pt_ref)
{
	//Nouveau vecteur de point
	vector<Point_3D*> vect_temp;
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	//Pour chacun des sommets
	for(i=0;i<nbre_sommet;i++)
	{
		//Dans tout les cas, ajout du point de l'ancien tableau
		vect_temp.push_back(vect_vertice[i]);
		//Si le point correspond au point de référence, ajout du point à ajouter
		if((*(vect_vertice[i]))==(*pt_ref))vect_temp.push_back(pt_to_add);
	}
	//Sauvegarde du nouveau tableau
	vect_vertice=vect_temp;
}

void Polygon::add_point_before(Point_3D* pt_to_add, Point_3D* pt_ref)
{
	//Nouveau vecteur de point
	vector<Point_3D*> vect_temp;
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	//Pour chacun des sommets
	for(i=0;i<nbre_sommet;i++)
	{
		//Si le point correspond au point de référence, ajout du point à ajouter
		if((*(vect_vertice[i]))==(*pt_ref))vect_temp.push_back(pt_to_add);
		//Dans tout les cas, ajout du point de l'ancien tableau
		vect_temp.push_back(vect_vertice[i]);
	}
	//Sauvegarde du nouveau tableau
	vect_vertice=vect_temp;
}

int Polygon::get_id(Point_3D* pt_ref)
{
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	//Initialisation du compteur
	i=0;
	//Tant qu'on à pas trouver le point, on passe au suivant
	while((i<nbre_sommet) && !((*(vect_vertice[i]))==(*pt_ref))) i++;
	//On retourne la position du point dans le tableau
	return(i);
}

void Polygon::clean(void)
{
	//Variable de boucle
	int i;
	//Itérateur
	vector<Point_3D*>::iterator it;
	
	//Pour chacun des sommets
	for(i=0;i<get_nb_vertice();i++)
	{
		//Si le statut du point est valide
		if(vect_vertice[i]->get_statut())
		{
			//Initialisation de l'itérateur
			it=vect_vertice.begin()+i;
			//Destruction du point
			delete vect_vertice[i];
			//Suppression du point de la liste
			vect_vertice.erase(it);
			//On remonte de un cran dans la liste
			i--;
		}
		//Autrement, validation du statut du point
		else vect_vertice[i]->set_statut(true);
	}
}

void Polygon::rem_point(Point_3D* pt_to_rem)
{
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	//Initialisation de la variable de boucle
	i=0;
	//Tant qu'on à pas trouvé de correspondance, on passe au point suivant dans la liste
	while((i<nbre_sommet) && !((*(vect_vertice[i]))==(*pt_to_rem))) i++;
	//Si on à une correspondance
	if(i<nbre_sommet)
	{
		//Initialisation de l'itérateur
		vector<Point_3D*>::iterator it=vect_vertice.begin()+i;
		//Destruction du point
		delete vect_vertice[i];
		//Suppresion du point de la liste
		vect_vertice.erase(it);
	}
}

void Polygon::order(void)
{
	//Nouveau vecteur de point
	vector<Point_3D*> vect_point;
	//Itérateur
	vector<Point_3D*>::iterator it;
	//Prochain point
	int next_point;
	//Angle
	double dbl_angle;
	//Temporaire
	double dbl_temp;
	//Variable de boucle
	unsigned int j;
	//Dernier point inséré
	Point_3D* pt_last;
	
	//Calcul du barycentre
	barycentre();
	/*
	struct_eq_plan* eq_plan;
	
	nbre_sommet=vect_vertice.size();
	
	if(nbre_sommet>3)
	{
		//cout << "Polygone de plus de trois points" << endl;
		eq_plan=equation_plan();
		j=0;
		while((j<nbre_sommet) && (vect_vertice[j]->eq_in_plan(eq_plan)==0)) j++;
		if(j<nbre_sommet)
		{
			cout << "Polygone " << this << " n'est pas un plan : " << vect_vertice[j]->eq_in_plan(eq_plan) << endl;
			cout << "	nbre sommet : " << nbre_sommet << " ; j = " << j << endl;
			cout << "	plan : " << eq_plan->dbl_a << " ; " << eq_plan->dbl_b << " ; " << eq_plan->dbl_c << " ; " << eq_plan->dbl_d << endl;
			cout << "	point : " << vect_vertice[j]->get_x() << " ; " << vect_vertice[j]->get_y() << " ; " << vect_vertice[j]->get_z() << endl;
		}
		delete eq_plan;
	}*/

	//On ajoute le point de référence à la liste des vecteurs
	vect_point.push_back(vect_vertice[0]);
	//Sauvegarde du dernier point ajouté
	pt_last=vect_vertice[0];
	//Initialisation de l'itérateur
	it=vect_vertice.begin();
	//Suppression du dernier point ajouté
	vect_vertice.erase(it);
	
	//Tant que la liste des points n'est pas vide
	while(!vect_vertice.empty())
	{
		//Angle de référence initialisé à 2 pi
		dbl_angle=6.28318531;
		//Pas de prochain point à rajouter dans la liste
		next_point=0;
		//Pour chacun des points contenus dans la liste initial
		for(j=0;j<vect_vertice.size();j++)
		{
			//On calcul l'angle entre le dernier point ajouté et le point actuel de sommet le barycentre
			dbl_temp=pt_barycentre->angle(*pt_last, *(vect_vertice[j]));
			//Si l'angle est inférieur à l'angle de référence
			if(dbl_angle>=dbl_temp)
			{
				//Nouvel angle de référence
				dbl_angle=dbl_temp;
				//Sauvegarde du prochain point à ajouté dans la liste
				next_point=j;
			}
		}
		//Ajout du point le plus proche du dernier ajouté dans la liste
		vect_point.push_back(vect_vertice[next_point]);
		//Récupération du dernier point ajouté
		pt_last=vect_vertice[next_point];
		//Initialisation de l'itérateur
		it=vect_vertice.begin()+next_point;
		//Suppression du point dernièrement ajouté
		vect_vertice.erase(it);
	}
	//Sauvegarde de la nouvelle liste de point
	vect_vertice=vect_point;
}

vector<Polygon*> Polygon::subdivide_byref(void)
{
	//Nouveau vecteur de polygon
	vector<Polygon*> vect_polygon;
	//Tableau des points associé à un des nouveau polygone
	vector<Point_3D*> vect_point;
	//Polygone temporaire
	Polygon* new_polygon;
	//Point temporaire
	Point_3D* pt_temp;
	//Variable de boucle
	int i;
	
	//Pour chacun des trois premiers point
	for(i=0;i<3;i++)
	{
		//Création de trois nouveaux points par copie
		pt_temp=new Point_3D(*(vect_vertice[i]));
		//Ajout des points nouvellement crée à la liste de points
		vect_point.push_back(pt_temp);
	}
	//Création du premier polygone
	new_polygon=new Polygon(vect_point, new QColor(*color_polygon));
	//Utilise le meme type de couleur que le polygone actuel
	new_polygon->set_is_default_color(bool_default_color);
	//Ajout du polygone à la liste des nouveaux polygones
	vect_polygon.push_back(new_polygon);

	//Pour chacun des points restant
	for(i=0;i<(int)vect_vertice.size()-3;i++)
	{
		//On vide le tableau de point
		vect_point.clear();
		//Création d'un nouveau point par copie du sommet
		pt_temp=new Point_3D(*(vect_vertice[0]));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création d'un nouveau point par copie du premier point restant
		pt_temp=new Point_3D(*(vect_vertice[i+2]));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création d'un nouveau point par copie du premier point restant
		pt_temp=new Point_3D(*(vect_vertice[i+3]));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création du nouveau polygone
		new_polygon=new Polygon(vect_point, new QColor(*color_polygon));
		//Utilise le meme type de couleur que le polygone actuel
		new_polygon->set_is_default_color(bool_default_color);
		//Ajout du polygone dans le tableau des nouveaux polygones
		vect_polygon.push_back(new_polygon);
	}
	//On retourne le nouveau tableau de polygone
	return(vect_polygon);
}

vector<Polygon*> Polygon::subdivide_bybarycentre(void)
{
	//Nouveau vecteur de polygon
	vector<Polygon*> vect_polygon;
	//Tableau des points associé à un des nouveau polygone
	vector<Point_3D*> vect_point;
	//Polygone temporaire
	Polygon* new_polygon;
	//Point temporaire
	Point_3D* pt_temp;
	//Variable de boucle
	int i;
	
	//Calcul du barycentre
	barycentre();

	//Création d'un nouveau point par copie du barycentre
	pt_temp=new Point_3D(*(pt_barycentre));
	//Ajout du point à la liste des points
	vect_point.push_back(pt_temp);
	//Création d'un nouveau point par copie du premier point restant
	pt_temp=new Point_3D(*(vect_vertice[0]));
	//Ajout du point à la liste des points
	vect_point.push_back(pt_temp);
	//Création d'un nouveau point par copie du premier point restant
	pt_temp=new Point_3D(*(vect_vertice[vect_vertice.size()-1]));
	//Ajout du point à la liste des points
	vect_point.push_back(pt_temp);
	//Création du nouveau polygone
	new_polygon=new Polygon(vect_point, new QColor(*color_polygon));
	//Utilise le meme type de couleur que le polygone actuel
	new_polygon->set_is_default_color(bool_default_color);
	//Ajout du polygone dans le tableau des nouveaux polygones
	vect_polygon.push_back(new_polygon);
		
	//Pour chacun des points de la liste
	for(i=0;i<(int)vect_vertice.size()-1;i++)
	{
		//On vide le tableau de point
		vect_point.clear();
		//Création d'un nouveau point par copie du sommet
		pt_temp=new Point_3D(*(pt_barycentre));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création d'un nouveau point par copie du premier point restant
		pt_temp=new Point_3D(*(vect_vertice[i]));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création d'un nouveau point par copie du premier point restant
		pt_temp=new Point_3D(*(vect_vertice[i+1]));
		//Ajout du point à la liste des points
		vect_point.push_back(pt_temp);
		//Création du nouveau polygone
		new_polygon=new Polygon(vect_point, new QColor(*color_polygon));
		//Utilise le meme type de couleur que le polygone actuel
		new_polygon->set_is_default_color(bool_default_color);
		//Ajout du polygone dans le tableau des nouveaux polygones
		vect_polygon.push_back(new_polygon);
	}
	//On retourne le nouveau tableau de polygone
	return(vect_polygon);
}

void Polygon::reset_polygon(void)
{
	//Variable de boucle
	int i;
	//Nombre de sommet
	int nbre_sommet;
	
	//Récupération du nombre de sommet
	nbre_sommet=get_nb_vertice();
	//Pour chacun des sommets
	for(i=0;i<nbre_sommet;i++) vect_vertice[i]->reset_point();
}

struct_eq_plan* Polygon::equation_plan(void)
{
	struct_eq_plan* eq_plan;
	Point_3D* pt1;
	Point_3D* pt2;
	Point_3D* pt3;
	
	pt1=vect_vertice[0];
	pt2=vect_vertice[1];
	pt3=vect_vertice[2];
	
	eq_plan=new struct_eq_plan;
	
	eq_plan->dbl_a = pt1->get_y()*(pt2->get_z()-pt3->get_z()) + pt2->get_y()*(pt3->get_z()-pt1->get_z()) + pt3->get_y()*(pt1->get_z()-pt2->get_z());
	eq_plan->dbl_b = pt1->get_z()*(pt2->get_x()-pt3->get_x()) + pt2->get_z()*(pt3->get_x()-pt1->get_x()) + pt3->get_z()*(pt1->get_x()-pt2->get_x());
	eq_plan->dbl_c = pt1->get_x()*(pt2->get_y()-pt3->get_y()) + pt2->get_x()*(pt3->get_y()-pt1->get_y()) + pt3->get_x()*(pt1->get_y()-pt2->get_y());
	eq_plan->dbl_d = -(pt1->get_x()*(pt2->get_y()*pt3->get_z()-pt3->get_y()*pt2->get_z()) + pt2->get_x()*(pt3->get_y()*pt1->get_z()-pt1->get_y()*pt3->get_z()) + pt3->get_x()*(pt1->get_y()*pt2->get_z() - pt2->get_y()*pt1->get_z()));

	return(eq_plan);	
}
