/*!
  \file Object3D.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr
  \brief code de la class Object_3D
  \date 13/05/2008
  \version 1.0
*/

#include "Object3D.hpp"

Object_3D::Object_3D(Object_3D & other_object)
{
	//Variable de boucle
	int i;
	//Nombre de polygone
	int nbre_polygon;
	//Polygone temporaire
	Polygon* poly_temp;
	
	//Récupération du nombre de polygone
	nbre_polygon=other_object.get_nb_polygon();
	
	//Pour chacun des polygones
	for(i=0; i<nbre_polygon; i++)
	{
		//Création par copie d'un nouveau polygone
		poly_temp=new Polygon(*(other_object.get_polygon(i)));
		//Ajout du polygone à la liste actuelle
		list_polygon.push_back(poly_temp);
	}
	
	//Copie du barycentre
	pt_barycentre=new Point_3D(*(other_object.barycentre()));
}


Object_3D::Object_3D(string file_off)
{	
	cout << "Création de l'objet 3D à partir du fichier " << file_off << endl;
	
	//Initialisation du coefficient de grossissement
	flt_coef=1;
	
	//Sauvegarde du chemin du fichier
	str_path=file_off;
	
	//S'il y a un problème lors de la lecture du fichier
	if(!load_from_file(file_off, NULL, true))
	{
		cout << "Chargement du fichier " << file_off << " impossible." << endl;
		//Suppression de l'instance
		delete this;
	}
	
	//Déplacement de l'objet pour le centrer sur son centre de gravité
	move(pt_barycentre);
}


Object_3D::Object_3D(string file_off, Point_3D* origin, float coef)
{
	cout << "Création de l'objet 3D à partir du fichier " << file_off << endl;
	cout << "et du point (" << origin->get_x() << " ; " << origin->get_y() << " ; " << origin->get_z() << ")" << endl;
	
	//Initialisation du coefficient de grossissement
	flt_coef=coef;
	
	//Sauvegarde du chemin du fichier
	str_path=file_off;
	
	//S'il y a un problème lors de la lecture du fichier
	if(!load_from_file(file_off, origin, false))
	{
		cout << "Chargement du fichier " << file_off << " impossible." << endl;
		cout << "Destruction de l'objet 3D" << endl;
		//Suppression de l'instance
		delete this;
	}
	//Création du barycentre
	barycentre();
}


Object_3D::~Object_3D()
{
	cout << "Destruction de l'objet 3D." << endl;
	//Iterateur
	list<Polygon*>::iterator it;

	//S'il n'y a aucun polygone à supprimer
	if(list_polygon.empty()) cout << "Aucun polygone à supprimer" << endl;
	//Autrement
	else
	{
		//Destruction de chacun des polygones de la liste
		for(it=list_polygon.begin();it!=list_polygon.end();it++) delete *it;
	}
	
	//Destruction du barycentre
	delete pt_barycentre;
}

bool Object_3D::operator<(Object_3D & other_object)
{
	//Retourne True si le point à comparer est plus proche des l'origine que le point actuels
	return(!(pt_barycentre->get_z()<other_object.barycentre()->get_z()));
}


Polygon* Object_3D::get_polygon(int int_n) const
{
	//Iterateur
	list<Polygon*>::const_iterator it;
	//Variable de boucle
	int i;
	
	//Initialisation de la variable de boucle
	i=0;
	//Initialisation de l'itérateur
	it=list_polygon.begin();
	//On parcours la liste jusqu'à l'élément int_n
	while(i++<int_n) it++;
	
	//On retourne le int_n ième élement de la liste
	return(*it);
}

int Object_3D::get_nb_polygon(void) const
{
	//Retourne la taille de la liste de polygone
	return(list_polygon.size());
}

double Object_3D::get_distance_med(void)
{
	//Retourne la distance moyenne
	return(dbl_distance_med);
}

bool Object_3D::load_from_file(string str_file, Point_3D* pt_origin, bool bool_auto_scale)
{
	//Tableau des sommets
	vector<Point_3D*> vect_vertice;
	//Tableau de point temporaire
	vector<Point_3D*>vect_pt_temp;
	//Couleur temporaire
	QColor* color_temp;
	//Point temporaire
	Point_3D* point_temp;
	//Polygone temporaire
	Polygon* polygon_temp;
	//Chaine de caractere temporaire
	string str_temp;
	//Nombre de vertices
	int int_vertices;
	//Nombre de polygones
	int int_polygones;
	//Vecteur temporaire de flottant
	vector<string> vect_str_temp;
	//Tableau temporaire d'entier
	int tab_int_temp[2];
	//Variables de boucle
	int i;
	int j;
	//Emplacement du dernier espace
	int int_old_space;
	//Nombre de caractère de la sous chaine
	int nbre_carac;
	//Abcisse du point
	float flt_x;
	//Ordonnée du point
	float flt_y;
	//Profondeur du point
	float flt_z;
	//Somme des abcisses
	double dbl_sum_x;
	//Somme des ordonnées
	double dbl_sum_y;
	//Somme des profondeurs
	double dbl_sum_z;
	
	cout << "Chargement de l'objet 3D à partir du fichier " << str_file << endl;

	//Si le test du fichier n'est pas bon
	if(!test_file(str_file))
	{
		cout << "Impossible de charger l'objet 3D à partir du fichier " << str_file << endl;
		//On retourne une erreur
		return(false);
	}

	//Ouverture du fichier en lecture
	ifstream fichier(str_file.c_str());
	//Lecture de l'entete
	fichier >> str_temp;

	//Initialisation de la variable de boucle
	i=0;
	
	//Initialisation de la distance moyenne
	dbl_distance_med=0;
	
	//Initialisation des sommes
	dbl_sum_x=0;
	dbl_sum_y=0;
	dbl_sum_z=0;

	//Tant qu'on a pas atteint la fin du fichier, on lit les deux premières
	while(!fichier.eof() && i<2)
	{
		//Lecture du debut de la ligne
		fichier >> str_temp;
		//Si la ligne commence par un commentaire, toute la suite de la ligne est considéré comme étant un commentaire
		if(str_temp.find("#")!=string::npos) getline(fichier, str_temp);
		//Autrement
		else
		{
			//On met l'entier lu dans le tableau
			tab_int_temp[i++]=atoi(str_temp.c_str());
		}
	}

	//Récupération du nombre de sommets
	int_vertices=tab_int_temp[0];
	//Récupération du nombre de polygones
	int_polygones=tab_int_temp[1];
	//On termine de lire la ligne sans importance
	getline(fichier, str_temp);
	
	cout << "Chargement de la liste des sommets des " << int_vertices << " à partir du fichier" << endl;
	
	//Pour chaque vertices
	for(i=0;i<int_vertices; i++)
	{
		//Lecture du debut de ligne
		fichier >> str_temp;
		//Si la ligne commence par un comentaire
		if(str_temp.find("#")!=string::npos)
		{
			//On remonte de 1 le curseur
			i--;
			//On lit tout la suite de la ligne
			getline(fichier, str_temp);
		}
		//Autrement
		else
		{
			//Récupération de l'abcisse
			flt_x=atof(str_temp.c_str());
			//Lecture du second entier
			fichier >> str_temp;
			//Récupération de l'ordonnée
			flt_y=atof(str_temp.c_str());
			//Lecture du troisième entier
			fichier >> str_temp;
			//Récupération de la profondeur
			flt_z=atof(str_temp.c_str());
			//Lecture de la fin de lign pour passer à la suivante
			getline(fichier, str_temp);
			//Création du point 3d avec les coordonnées
			point_temp=new Point_3D(flt_x, flt_y, flt_z);
			//Si l'origine est définie, on déplace le point
			if(pt_origin) point_temp->move(pt_origin);
			//Ajout de la distance
			dbl_distance_med+=point_temp->distance(Point_3D(0,0,0));
			//Ajout du point nouvellement créer dans le tableau de sommets
			vect_vertice.push_back(point_temp);
		}
	}
	
	//Calcul du coefficient multiplicatif
	dbl_distance_med=dbl_distance_med/(int_vertices*1.0);
	
	cout << "Coefficient multiplicatif :" << (int)(250/dbl_distance_med) << endl;
	
	//Si l'auto scale est activé
	if(bool_auto_scale)
	{
		//Pour chacun des points, on zoom sur le point
		for(i=0;i<int_vertices;i++) vect_vertice[i]->scale((int)(250/dbl_distance_med));
	}

	cout << "Chargement des " << int_polygones << " polygones à partir de la liste des fichiers" << endl;

	//Pour chaque polygone
	for(i=0;i<int_polygones; i++)
	{
		//Lecture de la ligne
		getline(fichier, str_temp);
		//Si la ligne commence par un commentaire, on remonte de 1 le curseur
		if(str_temp.find("#")!=string::npos) i--;
		//Autrement
		else
		{
			//Initialisation de la position du dernier espace
			int_old_space=0;
			//Récupération du nombre de caractère
			j=str_temp.size()-1;
			//Tant que l'on a pas un caratère correct en partant du fin de la ligne, on passe au caractère précédent
			while((int)str_temp[j]<33 && j>0) j--;
			//Calul du nombre de caractère à lire
			nbre_carac=j+1;
			//Pour chacun des caractères
			for(j=0;j<nbre_carac;j++)
			{
				//Si on a un espace
				if(str_temp[j]==' ')
				{
					//Si il y avait moins de 1 caractère avant le précédent espace, on stocke la postion du nouvel espace
					if(j-int_old_space<2) int_old_space=j;
					//Autrement
					else
					{
						//On stocke la chaine découpé convertit en flottant
						vect_str_temp.push_back(str_temp.substr(int_old_space, j-int_old_space));
						//On stocke la nouvelle position de l'espace
						int_old_space=j;
					}
				}
				//Si on a pas d'espace et qu'on se situe en début de ligne
				else if(int_old_space==0)
				{
					//On calcul la position du premier espace
					while(str_temp[j]!=' ' && j<nbre_carac) j++;
					//Si on a pas atteint la fin de la ligne
					if(j<nbre_carac)
					{
						//On stocke la chaine découpé convertit en flottant
						vect_str_temp.push_back(str_temp.substr(0, j));
						//On stocke la nouvelle position de l'espace
						int_old_space=j;
					}
				}
			}
			//S'il existe, on stocke le dernier flottant
			if(j!=int_old_space) vect_str_temp.push_back(str_temp.substr(int_old_space, j-int_old_space));
		}

		//Si on a une information sur la couleur avec transparence
		if(vect_str_temp.size()==(unsigned int)atoi(vect_str_temp[0].c_str())+5)
		{
			//Pour chacun des sommets correspondant
			for(j=0;j<((int)vect_str_temp.size()-5);j++)
			{
				//On créer un point temporaire par copie de celui que l'on vas utiliser
				point_temp=new Point_3D(*(vect_vertice[atoi(vect_str_temp[j+1].c_str())]));
				//On inclut le sommet dans la liste de points temporaire
				vect_pt_temp.push_back(point_temp);
			}
			//On créer l'élément couleur
			color_temp=new QColor((int)(atof(vect_str_temp[vect_str_temp.size()-4].c_str())*255), (int)(atof(vect_str_temp[vect_str_temp.size()-3].c_str())*255), (int)(atof(vect_str_temp[vect_str_temp.size()-2].c_str())*255),(int)(atof(vect_str_temp[vect_str_temp.size()-1].c_str())*255));
			//Création du polygone
			polygon_temp=new Polygon(vect_pt_temp, color_temp);
		}
		//Si on a une information sur la couleur sans transparence
		else if(vect_str_temp.size()==(unsigned int)atoi(vect_str_temp[0].c_str())+4)
		{
			//Pour chacun des sommets correspondant
			for(j=0;j<((int)vect_str_temp.size()-4);j++)
			{
				//On créer un point temporaire par copie de celui que l'on vas utiliser
				point_temp=new Point_3D(*(vect_vertice[atoi(vect_str_temp[j+1].c_str())]));
				//On inclut le sommet dans la liste de points temporaire
				vect_pt_temp.push_back(point_temp);
			}
			//On créer l'élément couleur
			color_temp=new QColor((int)(atof(vect_str_temp[vect_str_temp.size()-3].c_str())*255), (int)(atof(vect_str_temp[vect_str_temp.size()-2].c_str())*255), (int)(atof(vect_str_temp[vect_str_temp.size()-1].c_str())*255));
			//Création du polygone
			polygon_temp=new Polygon(vect_pt_temp, color_temp);
		}
		//Autrement, s'il n'y a pas d'information sur la couleur
		else if(vect_str_temp.size()==(unsigned int)atoi(vect_str_temp[0].c_str())+1)
		{
			//Pour chacun des sommets correspondant
			for(j=0;j<((int)vect_str_temp.size()-1);j++)
			{
				//On créer un point temporaire par copie de celui que l'on vas utiliser
				point_temp=new Point_3D(*(vect_vertice[atoi(vect_str_temp[j+1].c_str())]));
				//On inclut le sommet requis dans la liste des points temporaire
				vect_pt_temp.push_back(point_temp);
			}
			//Création du polygone
			polygon_temp=new Polygon(vect_pt_temp);
		}
		//Autrement, il n'y a pas assez d'information
		else
		{	
			//On vide le vecteur de chaine temporaire
			vect_str_temp.clear();
			
			//Vidage du vecteur de point temporaire
			vect_pt_temp.clear();
			
			//Fermeture du fichier
			fichier.close();
			
			//Suppression de la liste des points
			for(j=0;j<(int)vect_vertice.size();j++) delete vect_vertice[j];
			
			//Message d'erreur
			cout << "Erreur sur le structure du fichier OFF... Abandon de la lecture du fichier OFF." << endl;
			
			//On retourne une erreur
			return(false);
		}
		
		dbl_sum_x+=polygon_temp->barycentre()->get_x();
		dbl_sum_y+=polygon_temp->barycentre()->get_y();
		dbl_sum_z+=polygon_temp->barycentre()->get_z();
		
		//On ajoute le polygone à la liste des polygones
		list_polygon.push_back(polygon_temp);
		
		//Vidage du vecteur de point temporaire
		vect_pt_temp.clear();
		
		//On vide le vecteur temporaire
		vect_str_temp.clear();
	}

	//Fermeture du fichier
	fichier.close();
	
	//Suppression de la liste des points
	for(j=0;j<(int)vect_vertice.size();j++) delete vect_vertice[j];
	
	//Création du barycentre
	pt_barycentre=new Point_3D(dbl_sum_x/int_polygones, dbl_sum_y/int_polygones, dbl_sum_z/int_polygones);
		
	cout << "Chargement du fichier OFF terminé..." << endl;
		
	//Tout s'est bien passé
	return(true);
}


bool Object_3D::test_file(string str_file) const
{
	//Chaine de caractere temporaire
	string str_temp;

	//Test de l'extension pour savoir si c'est un OFF
	if(str_file.find(".off")==string::npos) return(false);

	//Ouverture du fichier en lecture
	ifstream fichier(str_file.c_str());
	//Si l'ouverture du fichier à échoué, c'est pas bon
	if(fichier.fail()) return(false);

	//Lecture de l'entete du fichier
	fichier >> str_temp;
	//Fermeture du fichier
	fichier.close();

	//Test de l'entete
	if(str_temp!="OFF") return(false);

	//Autrement, tout s'est bien passé
	return(true);
}

bool Object_3D::project(struct_point_sphere* origin_view)
{
	//Iterateur
	list<Polygon*>::iterator it;
	//Booléen de retour
	bool bool_retour;
	
	//Initialisation du booléen de retour
	bool_retour=true;
	
	//Projection de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) bool_retour=bool_retour && (*it)->project(origin_view);
	
	//On retourne le booléen de retour
	return(bool_retour);
	
}

bool Object_3D::show(AreaView* area, struct_point_sphere* origin_view, struct_point_sphere* origin_light, int int_mode_surface, int int_mode_line, Point_3D pt_screen)
{	
	//Iterateur
	list<Polygon*>::iterator it;
	//Booléen de retour
	bool bool_retour;
	
	//Initialisation du booléen de retour
	bool_retour=true;
	
	//Projection de l'objet 3d
	project(origin_view);
	
	//Tri de la liste pour l'ordre d'affichage
	list_polygon.sort(sort_polygon);
	
	//Inversion de la liste
	list_polygon.reverse();
	
	//Affichage de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) bool_retour=bool_retour && (*it)->show(area, origin_view, origin_light, int_mode_surface, int_mode_line, pt_screen);
	
	//On retourne le booléen de retour
	return(bool_retour);
}

Point_3D* Object_3D::barycentre(void)
{
	//Retourne le barycentre
	return(pt_barycentre);
}

Point_3D* Object_3D::calc_barycentre(void)
{
	//Somme des abcisses
	double dbl_sum_x;
	//Somme des ordonnées
	double dbl_sum_y;
	//Somme des profondeurs
	double dbl_sum_z;
	//Nombre de polygones
	int nbre_poly;
	//Variable de boucle
	int i;
	
	//Initialisation des sommes
	dbl_sum_x=0;
	dbl_sum_y=0;
	dbl_sum_z=0;
	
	//Récupération du nombre de sommet
	nbre_poly=get_nb_polygon();
	
	//Calcul de la somme des abcisses de chaque points
	for(i=0;i<nbre_poly;i++) dbl_sum_x+=get_polygon(i)->barycentre()->get_x();
	
	//Calcul de la somme des ordonnées de chaque points
	for(i=0;i<nbre_poly;i++) dbl_sum_y+=get_polygon(i)->barycentre()->get_y();
	
	//Calcul de la somme des profondeurs de chaque points
	for(i=0;i<nbre_poly;i++) dbl_sum_z+=get_polygon(i)->barycentre()->get_z();
	
	//Création du barycentre s'il n'existe pas
	if(pt_barycentre!=NULL) pt_barycentre=new Point_3D(dbl_sum_x/nbre_poly, dbl_sum_y/nbre_poly, dbl_sum_z/nbre_poly);
	//Autrement
	else
	{
		//Mise à jour de l'abcisse du barycentre
		pt_barycentre->set_x(dbl_sum_x/nbre_poly);
		//Mise à jour de l'abcisse du barycentre
		pt_barycentre->set_y(dbl_sum_y/nbre_poly);
		//Mise à jour de l'abcisse du barycentre
		pt_barycentre->set_z(dbl_sum_z/nbre_poly);
	}
	
	//Retourne le barycentre fraichement crée
	return(pt_barycentre);
}

void Object_3D::move(Point_3D* origin)
{
	//Iterateur
	list<Polygon*>::iterator it;

	//Déplacement de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) (*it)->move(origin);
}

void Object_3D::scale(int int_coef)
{
	//Iterateur
	list<Polygon*>::iterator it;

	//Mise à l'échelle de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) (*it)->scale((int)(int_coef*flt_coef));
}

void Object_3D::concat_with(Object_3D* object2)
{
	//Variable de boucle
	int i;
	//Nombre de polygone
	int nbre_polygon;
	//Polygone temporaire
	Polygon* poly_temp;
	
	//Récupération du nombre de polygone
	nbre_polygon=object2->get_nb_polygon();
	
	cout << "Nombre polygone OBJ 1 : " << get_nb_polygon() << endl;
	cout << "Nombre polygone OBJ 2 : " << nbre_polygon << endl;
	
	//Pour chacun des polygones
	for(i=0; i<nbre_polygon; i++)
	{
		//cout << "Ajout du polygone " << i << endl;
		//Création par copie d'un nouveau polygone
		poly_temp=new Polygon(*(object2->get_polygon(i)));
		//Ajout du polygone dans le premier objet
		list_polygon.push_back(poly_temp);
	}
	
	cout << "Nombre polygone OBJ 1 : " << get_nb_polygon() << endl;
	
	//Destruction de l'autre objet
	delete object2;
}

void Object_3D::add_polygon(Polygon* poly_to_add)
{
	//Ajout du polygone à la liste actuelle
	list_polygon.push_back(poly_to_add);
}

void Object_3D::reset_object(void)
{
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Remise à zéro de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) (*it)->reset_polygon();
}

void Object_3D::polish(float flt_puiss)
{
	//Liste des points
	vector<Point_3D*> vect_point;
	//Tableau deux dimensions de polygones
	vector<vector<Polygon*> > tab_polygon;
	//Vecteur contenant les nouveaux points
	vector<Point_3D*> vect_pt_new;
	//Variable de boucle
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int l;
	//Pointeur de pointeur de polygone
	Polygon** ptr_polygon;
	//Polygone temporaire
	//Polygon* poly_temp;
	//Nouveau polygone
	Polygon* poly_new;
	//Point temporaire
	Point_3D* pt_temp;
	//Point temporaire
	Point_3D* pt_new;
	//nombre de point dans le polygone
	unsigned int nbre_sommet;
	//Vecteur temporaire
	vector<Polygon*> vect_temp;
	//Vecteur de polygone divisé
	vector<Polygon*> vect_poly_divide;
	//Couleur
	QColor* color;
	//Itérateur
	list<Polygon*>::iterator it;
	
	//struct_point_sphere* pt_view;
	//pt_view=new struct_point_sphere;
	//pt_view->dbl_r=200;
	//pt_view->dbl_theta=0;
	//pt_view->dbl_phi=0;
	//project(pt_view);
	
	reset_object();
	
	//Allocation du double pointeur sur les polygones
	ptr_polygon=new Polygon*;
	
	color=get_polygon(0)->get_color();
	
	//Pour chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//Récupération du nombre de sommet
		nbre_sommet=(*it)->get_nb_vertice();
		//Pour chacun de ces sommets
		for(j=0;j<nbre_sommet;j++)
		{
			//Création d'un point temporaire par copie
			pt_temp= new Point_3D(*((*it)->get_vertice(j)));
			//Initialisation de la variable de boucle
			k=0;
			//Tant qu'on ne rencontre pas un point semblable, on passe au suivant
			while((k<vect_point.size()) && !((*(vect_point[k]))==(*pt_temp))) k++;
			//Si on a pas rencontré de point semblable
			if(k>=vect_point.size())
			{
				//On ajoute le point au tableau de point
				vect_point.push_back(pt_temp);
				//On ajoute le polygone associé au tableau de polygone associé à ce point
				vect_temp.push_back((*it));
				//On ajoute le tableau de polygone associé à ce point au tablaeu total
				tab_polygon.push_back(vect_temp);
				//On vide le tableau de polygone associé à ce point
				vect_temp.clear();
			}
			//Autrement
			else
			{
				//On ajoute le polygone au tableau de polygone associé au point k
				tab_polygon[k].push_back((*it));
				//Suppression du point non utilisé
				delete pt_temp;
			}
		}
	}
	
	//Récupération du nombre de point unique
	nbre_sommet=vect_point.size();
	
	//Pour chacun de ces points uniques
	for(i=0;i<nbre_sommet;i++)
	{
		//Sauvegarde du tableau des polygones associés à ce point
		vect_temp=tab_polygon[i];
		//Pour chacun des polygones associé
		for(j=0;j<vect_temp.size();j++)
		{
			//Sauvegarde du polygone dans le pointeur de pointeur de polygone
			*ptr_polygon=vect_temp[j];
			
			//On fait deux fois les actions suivantes
			for(l=0;l<3;l=l+2)
			{
				//Création du point en parcours sens inverse
				pt_new=create_point(ptr_polygon, vect_point[i], l-1, flt_puiss);
				//Initialisation de la variable de boucle
				k=0;
				//Tant qu'on a pas rencontré un point semblable, on passe au suivant
				while((k<vect_pt_new.size()) && !(*(vect_pt_new[k])==*pt_new)) k++;
				//Si on a pas rencontré de point semblable
				if(k>=vect_pt_new.size())
				{
					//On ajoute le nouveau point par copie au tableau des nouveaux points
					vect_pt_new.push_back(new Point_3D(*pt_new));
				}
			}
		}
		//Création d'un nouveau polygone à partir du tableau de nouveau point
		poly_new=new Polygon(vect_pt_new, new QColor(*color));
		//Utilise le meme type de couleur que le polygone actuel
		poly_new->set_is_default_color(get_polygon(0)->is_default_color());
		//Ordonne le nouveau polygone
		poly_new->order();
		//Division des polygones en triangle
		vect_poly_divide=poly_new->subdivide_byref();
		//Ajout des nouveaux polygones à la liste des polygones
		for(j=0;j<vect_poly_divide.size();j++) list_polygon.push_back(vect_poly_divide[j]);
		//Suppresion du nouveau polygone
		delete poly_new;
		//On efface le tableau de nouveaux points
		vect_pt_new.clear();
	}
	
	//Pour chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//On supprime des polygones les points superficiels
		(*it)->clean();
	}
	
	//Destruction de chacun des points uniques
	for(i=0;i<nbre_sommet;i++) delete vect_point[i];
	
	//Suppression du pointeur de polygone
	delete ptr_polygon;
}

Point_3D* Object_3D::create_point(Polygon** polygon, Point_3D* point, int int_pos, float flt_puiss)
{
	//Identifiant du sommet
	int int_id;
	//Nombre de sommet dans le polygone
	int int_nbre_sommet;
	//Point temporaire
	Point_3D* pt_temp;
	//Nouveau point
	Point_3D* pt_new;
	//Abcisse du point intermédiaire
	double dbl_x;
	//Ordonnée du point intermédiaire
	double dbl_y;
	//Profondeur du point intermédiaire
	double dbl_z;
	
	//Récupération du nombre de sommet
	int_nbre_sommet=(*polygon)->get_nb_vertice();
	//Recherche de l'identifiant du point dans le polygone
	int_id=(*polygon)->get_id(point)+int_nbre_sommet;

	//Récupération du sommet situé juste avant
	pt_temp=(*polygon)->get_vertice((int_id+(int_pos))%(int_nbre_sommet));
	//S'il s'agit d'un point intermédiaire, on passe au point encore précédent
	if(!pt_temp->get_statut()) pt_temp=(*polygon)->get_vertice((int_id+2*int_pos)%(int_nbre_sommet));
	//Calcul de la nouvelle abcisse du point intermédiaire
	dbl_x=flt_puiss*(pt_temp->get_x())+(1.0-flt_puiss)*(point->get_x());
	//Calcul flt_puiss la nouvelle ordonnée du point intermédiaire
	dbl_y=flt_puiss*(pt_temp->get_y())+(1.0-flt_puiss)*(point->get_y());
	//Calcul de la nouvelle profondeur du point intermédiaire
	dbl_z=flt_puiss*(pt_temp->get_z())+(1.0-flt_puiss)*(point->get_z());
	//Création du nouveau point avec le statut intermédiaire
	pt_new=new Point_3D(dbl_x, dbl_y, dbl_z, false);

	//S'il s'agit d'un parcours sens inverse, on rajoute le nouveau point après celui étudié
	if(int_pos<0) (*polygon)->add_point_after(pt_new, (*polygon)->get_vertice((int_id+int_pos)%(int_nbre_sommet)));
	//S'il s'agit d'un parcours sens normal, on rajoute le nouveau point avant celui étudié
	else (*polygon)->add_point_before(pt_new, (*polygon)->get_vertice((int_id+int_pos)%(int_nbre_sommet)));

	//Retourne le nouveau point
	return(pt_new);
}

void Object_3D::subdivide_byref(void)
{
	//Tableau des polygones divisés
	vector<Polygon*> vect_poly_divide;
	//Liste des polygones divisés
	list<Polygon*> list_poly_divide;
	//Variables de boucle
	unsigned int j;
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Remise à zéro de l'objet
	reset_object();
	
	//Pour chacun des polygone
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//On divise le polygone
		vect_poly_divide=(*it)->subdivide_bybarycentre();
		//On supprime l'ancien polygone
		delete (*it);
		//Ajout du polygone à la liste des polygones divisé
		for(j=0;j<vect_poly_divide.size();j++) list_poly_divide.push_back(vect_poly_divide[j]);
	}
	//Sauvegarde de la nouvelle liste de polygone
	list_polygon=list_poly_divide;
}

int Object_3D::get_nb_vertices(void)
{
	//Nombre de points total
	int nbre_points;
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Initialisation du nombre de points total
	nbre_points=0;
	
	//Ajout du nombre de point de chacun des polygones à la somme total du nombre de point
	for(it=list_polygon.begin();it!=list_polygon.end();it++) nbre_points+=(*it)->get_nb_vertice();
	
	//Retourne le nombre de points
	return(nbre_points);
}

int Object_3D::get_nb_single_vertices(void)
{
	//Nombre de sommet
	int nbre_sommet;
	//Point temporaire
	Point_3D* pt_temp;
	//Variables de boucle
	int j;
	int k;
	//Tableau de point
	vector<Point_3D*> vect_point;
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Pour chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//Récupération du nombre de sommet
		nbre_sommet=(*it)->get_nb_vertice();
		//Pour chacun de ces sommets
		for(j=0;j<nbre_sommet;j++)
		{
			//Création d'un point temporaire par copie
			pt_temp= new Point_3D(*((*it)->get_vertice(j)));
			//Initialisation de la variable de boucle
			k=0;
			//Tant qu'on ne rencontre pas un point semblable, on passe au suivant
			while((k<(int)vect_point.size()) && !((*(vect_point[k]))==(*pt_temp))) k++;
			//Si on a pas rencontré de point semblable, on ajoute le point au tableau de point
			if(k>=(int)vect_point.size()) vect_point.push_back(pt_temp);
			//Autrement, on supprime le point
			else delete pt_temp;
		}
	}
	
	//On retourne le nombre point unique
	return(vect_point.size());
}

void Object_3D::paint(QColor color)
{
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Coloriage de chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++) (*it)->paint(color);
}

void Object_3D::save_in_file(string str_file)
{
	//Nombre de sommet
	int nbre_sommet;
	//Point temporaire
	Point_3D* pt_temp;
	//Variables de boucle
	int i;
	int j;
	int k;
	//Tableau de point
	vector<Point_3D*> vect_point;
	//Itérateur
	list<Polygon*>::iterator it;
	
	//Ouverture du fichier en écriture
	ofstream fichier(str_file.c_str());
	
	//Ecriture de l'entete
	fichier << "OFF" << endl;
	
	//Pour chacun des polygones
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//Récupération du nombre de sommet
		nbre_sommet=(*it)->get_nb_vertice();
		//Pour chacun de ces sommets
		for(j=0;j<nbre_sommet;j++)
		{
			//Création d'un point temporaire par copie
			pt_temp= new Point_3D(*((*it)->get_vertice(j)));
			//Initialisation de la variable de boucle
			k=0;
			//Tant qu'on ne rencontre pas un point semblable, on passe au suivant
			while((k<(int)vect_point.size()) && !((*(vect_point[k]))==(*pt_temp))) k++;
			//Si on a pas rencontré de point semblable, on ajoute le point au tableau de point
			if(k>=(int)vect_point.size()) vect_point.push_back(pt_temp);
			//Autrement, on supprime le point
			else delete pt_temp;
		}
	}
	
	//Récupération du nombre de sommet unique
	nbre_sommet=vect_point.size();
	
	//Ecriture du nombre de point unique
	fichier << nbre_sommet << " ";
	
	//Ecriture du nombre de polygone
	fichier << get_nb_polygon() << " 0" << endl;
	
	//Pour chaque sommet unique
	for(i=0;i<nbre_sommet;i++)
	{
		//Ecriture de l'abcisse d'origine
		fichier << vect_point[i]->get_x_origin() << " ";
		//Ecriture de l'ordonnée d'origine
		fichier << vect_point[i]->get_y_origin() << " ";
		//Ecriture de la profondeur d'origine
		fichier << vect_point[i]->get_z_origin() << endl;
	}
	
	//Pour chaque polygone
	for(it=list_polygon.begin();it!=list_polygon.end();it++)
	{
		//Récupération du nombre de sommet du polygon
		nbre_sommet=(*it)->get_nb_vertice();
		//Ecriture du nombre de sommet du polygone
		fichier << nbre_sommet;
		//Pour chacun des sommets du polygones
		for(i=0;i<nbre_sommet;i++)
		{
			//Sauvegarde du point temporaire
			pt_temp=(*it)->get_vertice(i);
			//Initialisation du la variable de boucle
			k=0;
			//Tant qu'on ne rencontre pas un point semblable au sommet, on passe au suivant
			while((k<(int)vect_point.size()) && !((*(vect_point[k]))==(*pt_temp))) k++;
			//Ecriture de la correspondance
			fichier << " " << k;
		}
		//Ecriture de la composante rouge
		fichier << " " << (*it)->get_color()->red()/255.0;
		//Ecriture de la composante verte
		fichier << " " << (*it)->get_color()->green()/255.0;
		//Ecriture de la composante bleu
		fichier << " " << (*it)->get_color()->blue()/255.0;
		//Ecriture de la composante alpha
		fichier << " " << (*it)->get_color()->alpha()/255.0 << endl;
	}
	
	//Fermeture du fichier
	fichier.close();
	
	//Destruction de chacun des points uniques
	for(i=0;i<nbre_sommet;i++) delete vect_point[i];
}

string Object_3D::get_path(void)
{
	//Retourne le chemin d'accès vers le fichier
	return(str_path);
}

bool sort_polygon(Polygon* poly_first, Polygon* poly_second)
{
	//Retourne True si le point 2 est plus proche des l'origine que le point 1
	return(!(poly_first->barycentre()->get_z()<poly_second->barycentre()->get_z()));
}
