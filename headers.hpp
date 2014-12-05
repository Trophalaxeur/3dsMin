#ifndef __PROJET_3D_HEADERS_HPP__
#define __PROJET_3D_HEADERS_HPP__

//Headers pour la stl
#include <list>
#include <vector>
#include <string>
#include <map>

//Headers C++
#include <sstream>
#include <fstream>
#include <iostream>

//Headers divers
#include <math.h>
#include <signal.h>

//Headers QT
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QColor>
#include <QEvent>
#include <QDoubleSpinBox>
#include <QPolygon>
#include <QString>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>

//Espace de nommage std
using namespace std;

//Définition des constantes
#define HALF_WIDTH 300
#define HALF_HEIGHT 300
#define PLAN_X 2000.0

//Constantes du mode d'affichage
#define MODE_SURFACE_SOLID_LIGHT 0
#define MODE_SURFACE_SOLID 1
#define MODE_SURFACE_FIL 2

#define MODE_LINE_MIDDLE 0
#define MODE_LINE_SOLID 1
#define MODE_LINE_NONE 2

//Structure Point sphérique
typedef struct struct_point
{
	///> Distance du point à l'origine
	double dbl_r;
	///> Angle theta
	double dbl_theta;
	///> Angle phi
	double dbl_phi;
} struct_point_sphere;

//Structure equation plan (Ax+By+Cz+D=0)
typedef struct struct_plan
{
	///> Coefficient A
	double dbl_a;
	///> Coefficient B
	double dbl_b;
	///> Coefficient C
	double dbl_c;
	///> Coefficient D
	double dbl_d;
} struct_eq_plan;

#endif

