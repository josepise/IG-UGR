/*

	Dpto. Lenguajes y Sistemas Inform�ticos
	E.T.S.I. Inform�tica
	Univ. de Granada

    Dibuja un cubo
    compilar con: gcc cubo.c -lglut -lGLU -lGL -o cubo
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

void
cubo (GLfloat x, GLfloat y, GLfloat z, float opacity)
//Construye una caja con un vertice en origen y otro en (x,y,z)
{
  float color[4] = { 0.2, 0.5, 1, opacity };                    // ES RGB y el último es el transparente
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glBegin (GL_QUAD_STRIP);
  {				/* Caras transversales */
          //NORMAL es un vector perpendicular a la superficie. Es importante la normal, ya que se indica que parte en la superficie se calcule la iluminación.
          //VERTEX son vertices
          //La terminación 3f, es para indicar que vamos parametros le vamos a pasar.
          //GL_QUAD_STRIP 
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (x, y, z);
    glVertex3f (0, y, z);
    glVertex3f (x, 0, z);
    glVertex3f (0, 0, z);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (x, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (x, y, 0);
    glVertex3f (0, y, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (x, y, z);
    glVertex3f (0, y, z);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {				/* Costados */
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (x, 0, 0);
    glVertex3f (x, y, 0);
    glVertex3f (x, y, z);
    glVertex3f (x, 0, z);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, z);
    glVertex3f (0, y, z);
    glVertex3f (0, y, 0);
  }
  glEnd ();
}

void lineas (float x, float cubo_x, float y, float cubo_y , float z, float cubo_z)
{

  float color[4] = { 0.0, 0.0, 0.0, 35 };                    // ES RGB y el último es el transparente
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  glBegin(GL_LINES);
  {
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(cubo_x, 0.0 ,cubo_z);

    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f( 0.0, 0.0, cubo_z);

    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(cubo_x,0.0,0.0);

    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(0.0, 0.0 ,0.0 );

    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2 );
    glVertex3f (0.0, 0.0, cubo_z);


    //Parte Arriba
    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(cubo_x, cubo_y ,cubo_z);

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f( 0.0, cubo_y, cubo_z);

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(cubo_x,cubo_y,0.0);

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(0.0, cubo_y ,0.0 );

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2 );
    glVertex3f (0.0, cubo_y, cubo_z);

    //Union
    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
  }
  glEnd();

  float color1[4]={25.0,0.0,0.0,1.0};
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glBegin(GL_POINTS);
  {
    

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,z/2+cubo_z/2);
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,z/2+cubo_z/2);

    glVertex3f(x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );

    glVertex3f(-x/2+cubo_x/2,y/2+cubo_y/2,-z/2+cubo_z/2 );
    glVertex3f(-x/2+cubo_x/2,-y/2+cubo_y/2,-z/2+cubo_z/2 );
  }
  glEnd();

}

void
Dibuja (void)
{
  GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
  glPushMatrix ();
  glClearColor (1, 1, 1, 1);                           //Borra todo
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
  glTranslatef (-0.5, -0.5, -100);  //Todo lo que se dibuje a partir de este comando va trasladado.
  glLightfv (GL_LIGHT0, GL_POSITION, pos); //Pone la fuente de luz
  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0); //hace que gire
  glRotatef (view_rotz, 0.0, 0.0, 1.0);
  cubo (10, 10, 10,255);
  lineas (20,10,20,10,20,10);
  glPopMatrix (); 
  glutSwapBuffers ();  //Intercambia las "pizarras" para no ver parpadeo.
}

/* ------------------------------------------------------------------------- */

void
Ventana (GLsizei ancho, GLsizei alto)
{				// Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
  float calto;
  glViewport (0, 0, ancho, alto);	//fija el area de dibujo en la ventana 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  if (ancho > 0)
    calto = 1 * (GLfloat) alto / (GLfloat) ancho;
  else
    calto = 1;
  glFrustum (-1, 1, -calto, calto, 5, 250);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

static void
idle ()
{
  view_roty += 0.15;
  glutPostRedisplay ();   //Funcion que indica que se ha cambiado de excena y que hay que redibujar.
}

int
main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG: cubo");
  glutDisplayFunc (Dibuja);
  glutReshapeFunc (Ventana);  //Funcion que reajusta cuando el usuario cambia el tamaño de la ventana
  glutIdleFunc (idle);   //funcion que se ejecuta continuamente
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);
  glShadeModel (GL_FLAT);
  glutMainLoop ();
  return 0;
}
