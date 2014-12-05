/*!
  \file AreaView.cpp
  \author Franck Trey <franck.trey@eisti.fr> , Florian Lefevre <florian.lefevre@eisti.fr>
  \brief 
  \date 13/05/2008
  \version 1.0
*/

#include "AreaView.hpp"

AreaView::AreaView(QWidget *parent, Scene_3D* scene3D):QWidget(parent)
{
	scene=scene3D;
	int_height=600;
	int_width=600;
}

AreaView::~AreaView(void)
{
	cout << "Destruction de la zone d'affichage" << endl;
	//Destruction de la scène 3D
	delete scene;
}

QSize AreaView::get_minimum_size() const
{
	return QSize(600, 600);
}
QSize AreaView::get_size() const
{
	return QSize(600, 600);
}

void AreaView::paintEvent(QPaintEvent *)
{
	//on affiche l'objet i
	scene->show(this, Point_3D(width(), height(), 0));
	//on les dessine sur la zone d'affichage
	QPainter painter(this);
}

Scene_3D* AreaView::get_scene(void)
{
	//On retourne la scène 3d
	return(scene);
}

void AreaView::set_new_scene(Scene_3D* new_scene)
{
	if (scene) delete scene;
	
	scene=new_scene;
}
