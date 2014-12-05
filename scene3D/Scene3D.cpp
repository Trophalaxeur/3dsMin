/*!
  \file Scene3D.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief code source de la classe Scene_3D
  \date 13/05/2008
  \version 1.0
*/

#include "Scene3D.hpp"

Scene_3D::Scene_3D(const Scene_3D & other_scene) :QWidget()
{
	cout << "Création de la scène 3d par copie" << endl;
	
	obj_scene=new Object_3D(*(other_scene.get_object3d()));
	
	//Création du point d'origine de la vue
	origin_view=new struct_point_sphere;
	
	//Initialisation des coordonnées du point d'origine de la vue
	set_pov_r(1000);
	set_pov_theta(0);
	set_pov_phi(0);
	
	//Création du point d'origine de la lumière
	origin_light=new struct_point_sphere;
	
	//Initialisation des coordonnées du point d'origine de la lumière
	origin_light->dbl_r=50;
	origin_light->dbl_theta=0.785398163;
	origin_light->dbl_phi=0.785398163;
	
	//Initialisation du mode d'affichage
	int_mode_surface=MODE_SURFACE_SOLID_LIGHT;
	int_mode_line=MODE_LINE_MIDDLE;
}

Scene_3D::Scene_3D(void)
{
	cout << "Création de la scène 3D ..." << endl;
	
	//Initialisation de l'objet de la scène
	obj_scene=NULL;
	//Initialisation de l'origine de la vue
	origin_view=NULL;
	//Initialisation de l'origine de la lumière
	origin_light=NULL;
	
	//Création du point d'origine de la vue
	origin_view=new struct_point_sphere;
	
	//Initialisation des coordonnées du point d'origine de la vue
	set_pov_r(1000);
	set_pov_theta(0);
	set_pov_phi(0);
	
	//Création du point d'origine de la lumière
	origin_light=new struct_point_sphere;
	
	//Initialisation des coordonnées du point d'origine de la lumière
	origin_light->dbl_r=50;
	origin_light->dbl_theta=0.785398163;
	origin_light->dbl_phi=0.785398163;
	
	//Initialisation du mode d'affichage
	int_mode_surface=MODE_SURFACE_SOLID_LIGHT;
	int_mode_line=MODE_LINE_MIDDLE;
	
	//Initialisation du centre de la scène
	int_x=0;
	int_y=0;
	
	//Initialisation de la vitesse de déplacement
	int_drag_speed=0;
	//Initialisation de la vitesse de zoom
	int_zoom_speed=0;
}

Scene_3D::~Scene_3D()
{
	cout << "Destruction de la scène 3D" << endl;
	
	//Destruction de chacun de l'objet de la scène
	if(obj_scene) delete obj_scene;
	//Destruction du point de vue
	if(origin_view) delete origin_view;
	//Destruction du point lumineux
	if(origin_light) delete origin_light;
}

void Scene_3D::set_zoom_speed(int coef)
{
	//Mise à jour du coefficient de zoom
	int_zoom_speed=coef;
}

int Scene_3D::get_zoom_speed(void)
{
	//Retourne la vitesse de zoom
	return(int_zoom_speed);
}

void Scene_3D::set_drag_speed(int coef)
{
	//Mise à jour du coefficient de déplacement
	int_drag_speed=coef;
}

int Scene_3D::get_drag_speed(void)
{
	//Retourne la vitesse de déplacement
	return(int_drag_speed);
}

Object_3D* Scene_3D::get_object3d(void) const
{
	//On retourne l'objet 3d
	return(obj_scene);
}

double Scene_3D::get_pov_r(void) const
{
	//Retourne le paramatre r du point de vue
	return(origin_view->dbl_r);
}

void Scene_3D::set_pov_r(double r)
{
	//Mise à jour du parametre r du point de vue
	origin_view->dbl_r=r;
}

double Scene_3D::get_pov_theta(void) const
{
	//Retourne l'angle theta
	return(origin_view->dbl_theta);
}

void Scene_3D::set_pov_theta(double theta)
{
	//Mise à jour de l'angle theta
	origin_view->dbl_theta=theta;
}

double Scene_3D::get_pov_phi(void) const
{
	//Retourne l'angle phi du point de vue
	return(origin_view->dbl_phi);
}

void Scene_3D::set_pov_phi(double phi)
{
	//Mise à jour de l'angle phi du point de vue
	origin_view->dbl_phi=phi;
}

void Scene_3D::signal_set_pov_phi(int phi)
{
	//Mise à jour de l'angle phi du point de vue
	origin_view->dbl_phi=phi*6.28318531/360;
}

void Scene_3D::signal_set_pov_theta(int theta)
{
	//Mise à jour de l'angle theta
	origin_view->dbl_theta=theta*6.28318531/360;
}

void Scene_3D::signal_set_pov_r(int r)
{
	
	//Mise à jour du parametre r du point de vue
	origin_view->dbl_r=2*r-2000;
}

void Scene_3D::signal_set_pol_phi(int phi)
{
	//Mise à jour de l'angle phi du point lumineux
	origin_light->dbl_phi=phi*6.28318531/360;
}

void Scene_3D::signal_set_pol_theta(int theta)
{
	//Mise à jour de l'angle theta du point lumineux
	origin_light->dbl_theta=theta*6.28318531/360;
}

void Scene_3D::signal_set_pol_r(int r)
{
	//Mise à jour du parametre r du point de lumineux
	origin_light->dbl_r=abs(r-100);
}

bool Scene_3D::load_from_file(string str_file)
{
	//Chaine de caractère temporaire
	string str_temp;
	//Objet 3d temporaire
	Object_3D* obj_temp;
	//Tableau de flottant temporaire
	float tab_flt_temp[4];
	//Point temporaire
	Point_3D* pt_temp;
	//Variable de boucle
	int i;
	int j;
	//Nombre d'objet à charger
	int nbre_object;
	//Distance moyenne des points des objets
	double dbl_temp_distance;
	//Liste temporaire d'objet
	list<Object_3D*> list_object3d;
	//Iterateur
	list<Object_3D*>::iterator it;
		
	cout << "Chargement de la scène 3D à partir du fichier " << str_file << endl;
	
	//Initialisation de l'objet 3D temporaire
	obj_temp=NULL;
	//Initialisation du point 3D temporaire
	pt_temp=NULL;
	
	cout << "Test du fichier ..." << endl;
	
	//Si le test du fichier se passe mal
	if(!test_file(str_file))
	{
		cout << "Le fichier " << str_file << " n'est pas un fichier SFF valide." << endl;
		//Test de l'extension pour savoir si c'est un OFF
		if(str_file.find(".off")==string::npos)
		{
			cout << "Le fichier " << str_file << " n'est pas un fichier OFF valide." << endl;
			//On retourne une erreur
			return(false);
		}
		//S'il s'agit d'un off, on crée un seul objet 3d
		obj_scene=new Object_3D(str_file);
		
		//S'il y a un problème lors de la lecture du fichier
		if(!obj_scene->load_from_file(str_file, NULL, true))
		{
			cout << "Chargement du fichier " << str_file << " impossible." << endl;
			//Suppression de l'instance
			delete obj_scene;
			cout << "Impossible de créer l'objet 3D" << endl;
			//On retourne une erreur
			return(false);
		}
		//Déplacement de l'objet pour le centrer sur son centre de gravité
		obj_scene->move(obj_temp->barycentre());
		//Tout s'est bien passé
		return(true);
	}
	
	//Ouverture du fichier en lecture
	ifstream fichier(str_file.c_str());
	//Lecture de l'entete
	fichier >> str_temp;
	//Lecture du nombre d'objets 3d présente dans le fichier
	fichier >> str_temp;
	
	//Récupération du nombre d'objet à charger
	nbre_object=atoi(str_temp.c_str());
	
	cout << "Chargement du fichier SFF et de ses " << nbre_object << " objets." << endl;
	
	//Initialisation de la distance moyenne des points des objets
	dbl_temp_distance=0;
	
	//Tant qu'on a pas atteint la fin du fichier
	for(i=0;i<nbre_object;i++)
	{
		//Récupération du chemin vers l'objet
		fichier >> str_temp;
		//S'il n'y a pas de commentaire
		if(str_temp.find("#")==string::npos)
		{
			//On récupère les coordonnées du centre de l'objet
			for(j=0;j<4;j++) fichier >> tab_flt_temp[j];
			//On crée le point 3d
			pt_temp=new Point_3D(tab_flt_temp[0], tab_flt_temp[1], tab_flt_temp[2]);
			//On crée l'objet 3d
			obj_temp=new Object_3D(str_temp, pt_temp, tab_flt_temp[3]);
			
			//Si on a pas pu créer l'objet 3D
			if(!obj_temp->load_from_file(str_temp, pt_temp, false))
			{
				cout << "Erreur lors du chargement du fichier " << str_temp << endl;
				cout << "Impossible de créer l'objet 3d" << endl;
				//Suppression du point 3D
				delete pt_temp;
				//Destruction de l'objet
				delete obj_temp;
				//Fermeture du fichier
				fichier.close();
				//On retourne une erreur
				return(false);
			}
			//Ajout de l'objet 3d
			list_object3d.push_back(obj_temp);
			//Récupération de la distance moyenne des objets
			dbl_temp_distance+=obj_temp->get_distance_med();
		}
		//On lit le reste de la ligne
		getline(fichier, str_temp);
	}
	
	//Calcul de la distance moyenne des points
	dbl_temp_distance=250/(dbl_temp_distance/(nbre_object*1.0));
	
	cout << "Concaténation des objets..." << endl;
	
	//Déplacement de chacun des polygones
	for(it=list_object3d.begin();it!=list_object3d.end();it++)
	{
		//Mise à l'échelle de la scène
		cout << "Mise à l'échelle de l'objet..." << endl;
		(*it)->scale((int)dbl_temp_distance);
		if(it!=list_object3d.begin()) (*(list_object3d.begin()))->concat_with(*it);
	}
	
	obj_scene=*(list_object3d.begin());
	
	cout << "T = " << obj_scene->get_nb_polygon() << endl;
	
	cout << "Fin de chargement de la scène 3D" << endl;
	
	//Fermeture du fichier
	fichier.close();
	//Tout s'est bien passé
	return(true);
}

bool Scene_3D::test_file(string str_file) const
{
	//Chaine de caractere temporaire
	string str_temp;

	//Test de l'extension pour savoir si c'est un SFF
	if(str_file.find(".sff")==string::npos) return(false);

	//Ouverture du fichier en lecture
	ifstream fichier(str_file.c_str());
	//Si l'ouverture du fichier à échoué, c'est pas bon
	if(fichier.fail()) return(false);

	//Lecture de l'entete du fichier
	fichier >> str_temp;
	//Fermeture du fichier
	fichier.close();

	//Test de l'entete
	if(str_temp!="SFF") return(false);
	//Autrement, tout s'est bien passé
	return(true);
}

void Scene_3D::scale(int int_coef)
{
	//Mise à l'échelle de l'objet
	obj_scene->scale(int_coef);
}

bool Scene_3D::rotate_view(double dbl_theta, double dbl_phi)
{
	//Mise à jour de l'angle theta
	set_pov_theta(get_pov_theta()-dbl_theta);
	//Mise à jour de l'angle phi
	set_pov_phi(get_pov_phi()-dbl_phi);
	
	//Retourne la projection de l'objet
	return(obj_scene->project(origin_view));
}

bool Scene_3D::zoom(double dbl_coeff)
{
	//Mise à jour du paramètre r
	set_pov_r(get_pov_r()+dbl_coeff*pow(2, int_zoom_speed));
	
	//Retourne la projection de l'objet
	return(obj_scene->project(origin_view));
}

bool Scene_3D::show(AreaView* area, Point_3D pt_screen)
{
	//Retourne la projection de l'objet
	return(obj_scene->show(area, origin_view, origin_light, int_mode_surface, int_mode_line, Point_3D(pt_screen.get_x()+int_x, pt_screen.get_y()+int_y,0)));
}

void Scene_3D::set_mode_line(int mode)
{
	//Mise à jour du mode d'affichage des lignes
	int_mode_line=mode;
}
		
void Scene_3D::set_mode_surface(int mode)
{
	//Mise à jour du mode d'affichage des surfaces
	int_mode_surface=mode;
}

void Scene_3D::drag_scene(int x, int y)
{
	//Déplacement de l'abcisse
	int_x+=x*(int)pow(2,int_drag_speed);
	//Déplacement de l'ordonnée
	int_y+=y*(int)pow(2,int_drag_speed);
}

void Scene_3D::move_scene(int x, int y)
{
	//Mise à jour de l'abcisse
	int_x=x;
	//Mise à jour de l'ordonnée
	int_y=y;
}
