/*
	Camara.cpp

	@author: Rolando A. Rosales J.
	@version: v1.0 15/nov/2018
	@require: freeglut

*/

#include <iostream>
#include <sstream>
//#include "gl/freeglut.h"
//#include "Tools.h"
#include "include/freeglut/include/GL/freeglut.h"
#include <ctime>
#include <math.h>

#define PROYECTO "Reloj 3D"
#define PI 3.1416

double alpha = 0;

GLuint horario, minutero, segundero, base, base2, manecillaMovCte, barra;

//Par�metros de la camara
struct Camara {
	double x = 0, y = 0, z = 5;
	double lookX = 0, lookY = 0, lookZ = 0;
}camara;

void init() {
	//Fijar color de borrado
	glClearColor(1, 1, 1, 1.0);
	glEnable(GL_DEPTH_TEST);

	//Segundero
	segundero = glGenLists(1);
	glNewList(segundero, GL_COMPILE);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 0.3, 0.03);
	glScalef(0.5*0.025, 0.9, 0.01);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();

	//Minutero
	minutero = glGenLists(1);
	glNewList(minutero, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0, 0.35, 0.0275);
	glScalef(0.5*0.05, 0.7, 0.01);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();

	//Horario
	horario = glGenLists(1);
	glNewList(horario, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(0, 0.25, 0.025);
	glScalef(0.5*0.1, 0.5, 0.01);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();

	//Base del reloj
	base = glGenLists(1);
	glNewList(base, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(0, 0, -0.1);
	glutSolidCylinder(1, 0.01, 64, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslatef(0, 0, -0.075);
	glutSolidCylinder(0.9, 0.01, 64, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(0, 0, -0.025);
	glutSolidCylinder(0.8, 0.01, 64, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCylinder(0.1, 0.01, 64, 2);
	glPopMatrix();

	glEndList();

	//Base del reloj (De manecilla con rotacion constante)
	base2 = glGenLists(1);
	glNewList(base2, GL_COMPILE);
	glPushMatrix();
	//glTranslatef(0, -0.35, 0);
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCylinder(0.2, 0.01, 64, 2);

	glTranslatef(0, 0, 0.01);
	glColor3f(0.85, 0.85, 0.85);
	glutSolidCylinder(0.175, 0.01, 64, 2);

	glTranslatef(0, 0, 0.01);
	glColor3f(0.7, 0.7, 0.7);
	glutSolidCylinder(0.02, 0.001, 64, 2);

	glPopMatrix();
	glEndList();

	//Manecilla con rotacion constante
	manecillaMovCte = glGenLists(1);
	glNewList(manecillaMovCte, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0, 0.1, 0.01);
	glScalef(0.5, 0.25, 1);
	glScalef(0.5*0.05, 0.60, 0.01);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();
	glutSetWindowTitle(PROYECTO);

	//Barra de digito para reloj digital
	barra = glGenLists(1);
	glNewList(barra, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0, 0, 0);
	glScalef(0.25, 1.25, 0.01);
	glutSolidCube(.05);
	glPopMatrix();
	glEndList();

}


void dibujarDigito(int n) {
	//Norte
	if (n == 0 || n == 2 || n == 3 || n > 4) {
		glPushMatrix();
		glTranslatef(0, 0.05, 0);
		glRotatef(90, 0, 0, 1);
		glCallList(barra);
		glPopMatrix();
	}

	//Noroeste
	if (n == 0 || n == 4 || n == 5 || n == 6 || n > 7) {
		glPushMatrix();
		glTranslatef(-0.025, 0.025, 0);
		glCallList(barra);
		glPopMatrix();
	}

	//Noreste
	if (n < 5 || n > 6) {
		glPushMatrix();
		glTranslatef(0.025, 0.025, 0);
		glCallList(barra);
		glPopMatrix();
	}

	//Centro
	if ((n > 1 && n < 7) || n > 7) {
		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glCallList(barra);
		glPopMatrix();
	}

	//Suroeste
	if (n == 0 || n == 2 || n == 6 || n == 8) {
		glPushMatrix();
		glTranslatef(-0.025, -0.025, 0);
		glCallList(barra);
		glPopMatrix();
	}

	//Sureste
	if (n < 2 || n > 2) {
		glPushMatrix();
		glTranslatef(0.025, -0.025, 0);
		glCallList(barra);
		glPopMatrix();
	}

	//Sur
	if (n == 0 || n == 2 || n == 3 || (n > 4 && n != 7)) {
		glPushMatrix();
		glTranslatef(0, -0.05, 0);
		glRotatef(90, 0, 0, 1);
		glCallList(barra);
		glPopMatrix();
	}
}

void fps() {
	//Cuenta los fotogramas por segundos
	int ahora, t;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int frame = 0;
	frame++;
	ahora = glutGet(GLUT_ELAPSED_TIME);
	t = ahora - antes;
	if (t > 1000) {
		printf("\tFPS: %d\r", frame);
		frame = 0;
		antes = ahora;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Posicion y orientacion de la camara
	gluLookAt(camara.x, camara.y, camara.z, camara.lookX, camara.lookY, camara.lookZ, 0, 1, 0);

	//Obtener hora actual
	static struct tm *t;
	static time_t ahora;
	time(&ahora);
	//localtime_s(&t, &ahora);
	t = localtime(&ahora);

	glPushMatrix();

	glTranslatef(0, 0, 0.15); //Traslacion de todo el reloj

	//Correa
	glPushMatrix();
	glColor3f(0.15, 0.15, 0.15);
	glTranslatef(0, 0, -0.1);
	glScalef(2, 6, 0.01);
	glutSolidCube(.5);
	glPopMatrix();

	//Base del reloj
	glCallList(base);

	//Color por defecto
	glColor3f(0, 0, 0);

	//Centro
	glPushMatrix();
	//glTranslatef(0, 0, 0.05);
	glutSolidCylinder(0.05, 0.05, 32, 2);
	glPopMatrix();

	//Luminosidad del color segun el tiempo
	float luminosidad;
	//Recuadros horas
	for (auto i = 0; i < 12; i++) {
		glPushMatrix();
		if (i % 3 == 0) {
			luminosidad = sin((alpha + i * 45)*PI / 180)*0.2;
			glColor3f(0.6 + luminosidad, 0.6 + luminosidad, 0.5 + luminosidad);
		}
		else {
			glColor3f(0.2, 0.2, 0.2);
		}
		glRotatef(i * 360 / 12, 0, 0, 1);
		glTranslatef(0, 0.75, 0.01);
		glScalef(0.05, 0.2, 0.01);
		glutSolidCube(1);
		glPopMatrix();
	}

	//Recuadros minutos
	for (auto i = 0; i < 60; i++) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		glRotatef(i * 360 / 60, 0, 0, 1);
		glTranslatef(0, 0.8, 0.01);
		glScalef(0.05*0.2, 0.2*0.2, 0.01);
		glutSolidCube(1);
		glPopMatrix();
	}

	//Segundo
	int segundo = t->tm_sec;
	glPushMatrix();
	glRotatef(-segundo * 360 / 60, 0, 0, 1);
	glCallList(segundero);
	glPopMatrix();

	//Minuto
	int minuto = t->tm_min;
	glPushMatrix();
	glRotatef(-minuto * 360 / 60, 0, 0, 1);
	glCallList(minutero);
	glPopMatrix();


	//Hora
	//+1: Zona horaria de Espa�a en invierno || -5: Zona Horaria de Panam�
	float hora = t->tm_hour + (float)t->tm_min / 60.0;
	glPushMatrix();
	glRotatef(-hora * 360 / 12, 0, 0, 1);
	glCallList(horario);
	glPopMatrix();

	//Base del reloj (De manecilla con rotacion constante)
	glPushMatrix();
	glTranslatef(0, 0.35, 0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(base2);
	//Manecilla con rotacion constante
	glPushMatrix();
	glTranslatef(0, 0, 0.01);
	glColor3f(0.7, 0.7, 0.7);
	glRotatef(-alpha - 90, 0, 0, 1);
	glCallList(manecillaMovCte);
	glPopMatrix();
	glPopMatrix();

	//Reloj digital
	glPushMatrix();
	glTranslatef(0, -0.35, 0);

	glPushMatrix();
	glColor3f(0.85, 0.85, 0.85);
	glTranslatef(0, 0, -0.01);
	glScalef(0.5, 0.15, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.2, 0, 0);
	dibujarDigito(int(hora) / 10);
	glTranslatef(0.075, 0, 0);
	dibujarDigito(int(hora) % 10);
	glTranslatef(0.075, 0, 0);
	glPushMatrix();
	glScalef(1, .5, 1);
	if (segundo % 2 == 0)glCallList(barra);
	glPopMatrix();
	glTranslatef(0.075, 0, 0);
	dibujarDigito(minuto / 10);
	glTranslatef(0.075, 0, 0);
	dibujarDigito(minuto % 10);
	glScalef(0.5, 0.5, 1);
	glTranslatef(0.15, -0.055, 0);
	dibujarDigito(segundo / 10);
	glTranslatef(0.08, 0, 0);
	dibujarDigito(segundo % 10);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();

	fps();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	float ra = float(w) / float(h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	float a = 2 * asin(float(1) / sqrt(pow(camara.x, 2) + pow(camara.y, 2) + pow(camara.z, 2))) * 180 / PI;
	gluPerspective(a, ra, 0.2, 10);

}

void update() {
	//Fase de actualizacion

	// Con control del tiempo
	static const float omega = 360 / 60;

	// Hora anterior inicial
	static int antes = glutGet(GLUT_ELAPSED_TIME);//Devuelve tiempo en milisegundos

	//Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	//Tiempo transcurrido
	float t = (float)(ahora - antes) / 1000.0;

	//Incremento
	alpha += omega * t * 10;

	//Actualizar la hora
	antes = ahora;

	//Evento de redibujo
	glutPostRedisplay();
}

void onTimer(int frame) {
	update();

	//Nueva cuenta
	glutTimerFunc(frame, onTimer, frame);
}

int main(int argc, char **argv) {
	printf("\n\n\tProyecto: Reloj 3D\n\n");
	printf("\tRolando A. Rosales J.\n");
	printf("\t2018\n\n");

	glutInit(&argc, argv);
	//Buffers a usar
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//Posicionar la ventana de dibujo en la pantalla
	glutInitWindowPosition(200, 0);

	//Tamanio de la pantalla
	glutInitWindowSize(500, 500);

	//Crear la ventana
	glutCreateWindow(PROYECTO);
	init();
	//Registrar las callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(update);
	glutTimerFunc(1000 / 60, onTimer, 1000 / 60);

	//Poner en march el bucle de atencion a eventos
	glutMainLoop();

	return 0;
}