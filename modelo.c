/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"

/**	void initModel()

Inicializa el modelo y de las variables globales


**/

int modo=GL_FILL;
bool ilum=false;

void
initModel ()
{

}

void setModo(int M)
{
  modo=M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
  Dibuja();
}

void setIlum()
{
  if(ilum==false)
    ilum=true;
  else
    ilum=false;
    
}

class Piramide:Objeto3D
{
  public:
    float lado=5.0;

    void draw()
    {
      glBegin(GL_QUADS);
      {
        glNormal3f (0.0, -1.0, 0.0);
        
        glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (lado, 0.0, 0.0);
        glVertex3f (lado, 0.0, lado);
        glVertex3f (0.0, 0.0, lado);

      }
      glEnd();

      glBegin(GL_TRIANGLE_FAN);
      {
        glNormal3f(-1.0, 0.0 , 0.0);
        glVertex3f(lado/2, lado+4, lado/2 );
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, lado);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(lado, 0.0, lado);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(lado, 0.0, 0.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0,0.0,0.0);
      }
      glEnd();
    }
    
};

class Cubo:Objeto3D
{

	public:
    float lado=5.0;

    Cubo (float l)
    {
      lado=l;
    }

	  void draw()
    {
      glBegin(GL_QUAD_STRIP);
      {
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, lado, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, lado, lado);
        glVertex3f(0.0, 0.0, lado);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(lado, lado , lado);
        glVertex3f(lado, 0.0, lado);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(lado, lado, 0.0);
        glVertex3f(lado, 0.0, 0.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, lado, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
      }
      glEnd();
      
      glBegin(GL_QUADS);
      {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, lado, 0.0);
        glVertex3f(lado, lado, lado);
        glVertex3f(0.0, lado, lado);
        glVertex3f(lado, lado, 0.0);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(lado, 0.0, 0.0);
        glVertex3f(lado, 0.0, lado);
        glVertex3f(0.0, 0.0, lado);
      }
      glEnd();
    }

};

class Teseracto:Objeto3D
{
  public:
    float lado=10;

    void draw()
    {
      float color[4] = { 0.2, 0.5, 1, 1};                    // ES RGB y el último es el transparente
      glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
      glBegin (GL_QUAD_STRIP);
      {				
        glNormal3f (0.0, 0.0, 1.0);	
        glVertex3f (lado/2, lado/2, lado/2);
        glVertex3f (0, lado/2, lado/2);
        glVertex3f (lado/2, 0, lado/2);
        glVertex3f (0, 0, lado/2);
        glNormal3f (0.0, -1.0, 0.0);	
        glVertex3f (lado/2, 0, 0);
        glVertex3f (0, 0, 0);
        glNormal3f (0.0, 0.0, -1.0);	
        glVertex3f (lado/2, lado/2, 0);
        glVertex3f (0, lado/2, 0);
        glNormal3f (0.0, 1.0, 0.0);	
        glVertex3f (lado/2, lado/2, lado/2);
        glVertex3f (0, lado/2, lado/2);
      }
      glEnd ();
      glBegin (GL_QUADS);
      {				
        glNormal3f (1.0, 0.0, 0.0);
        glVertex3f (lado/2, 0, 0);
        glVertex3f (lado/2, lado/2, 0);
        glVertex3f (lado/2, lado/2, lado/2);
        glVertex3f (lado/2, 0, lado/2);
        glNormal3f (-1.0, 0.0, 0.0);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, lado/2);
        glVertex3f (0, lado/2, lado/2);
        glVertex3f (0, lado/2, 0);
      }
      glEnd ();

      float color1[4] = { 1, 1, 1, 1 };                    // ES RGB y el último es el transparente
      glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);

      glBegin(GL_LINES);
      {
        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);

        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(lado/2, 0.0 ,lado/2);

        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f( 0.0, 0.0, lado/2);

        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );

        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(lado/2,0.0,0.0);

        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );

        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(0.0, 0.0 ,0.0 );

        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2 );

        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2 );
        glVertex3f (0.0, 0.0, lado/2);


        
        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);

        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(lado/2, lado/2 ,lado/2);

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f( 0.0, lado/2, lado/2);

        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );

        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(lado/2,lado/2,0.0);

        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(0.0, lado/2 ,0.0 );

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2 );

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2 );
        glVertex3f (0.0, lado/2, lado/2);

        
        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,lado/2+(lado/2)/2);
        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,lado/2+(lado/2)/2);

        glVertex3f(lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );

        glVertex3f(-lado/2+(lado/2)/2,lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
        glVertex3f(-lado/2+(lado/2)/2,-lado/2+(lado/2)/2,-lado/2+(lado/2)/2 );
      }
      glEnd();

    }

    float getAltura()
    {
      return lado/2 - (lado/2)/2;
    }
};

class Malla:Objeto3D
{
  private:
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> normales;
    std::vector<std::vector<float>> normales_vert;
    std::vector<std::vector<int>> caras;

  public:

  Malla(char * st)
  {
    std::vector<float> vert,tmp;
    std::vector<int> po,car;

    ply::read(st,vert,po);
    std::vector<int>::iterator it=po.begin();


    for(it; it!=po.end(); ++it)
    {
      car.push_back((*it));

      if(car.size()==3)
      {
        caras.push_back(car);
        car.clear();
      }
    }

    for(int i=0; i<vert.size(); i++)
    {
      tmp.push_back(vert[i]);
      
      if(tmp.size()==3)
      {
        vertices.push_back(tmp);
        tmp.clear();
      }
    } 

    for(int i=0; i<caras.size(); i++)
      normales.push_back({0,0,0});
    
    for(int i=0; i<vertices.size(); i++)
      normales_vert.push_back({0,0,0});
   
  }


  void draw()
  {

      glBegin(GL_TRIANGLES);
      {
        for(int i=0; i<caras.size(); i++)
        {
            normalCaras(vertices[caras[i][0]],vertices[caras[i][1]],vertices[caras[i][2]],i);
            glNormal3f(normales[i][0],normales[i][1],normales[i][2]);
            
            for(int j=0; j<3; j++)
              glVertex3f(vertices[caras[i][j]][0],vertices[caras[i][j]][1],vertices[caras[i][j]][2]);
        }

      }
      glEnd();
  }

  void draw_smooth()
  {
    glShadeModel(GL_SMOOTH);
   
    for(int i=0; i<caras.size(); i++)
      normalCaras(vertices[caras[i][0]],vertices[caras[i][1]],vertices[caras[i][2]],i);

    normalVertices();
    glBegin(GL_TRIANGLES);
    {
      
      for(int i=0; i<caras.size();i++)
      { 
        for(int j=0; j<3; j++)
        {
          glNormal3f(normales_vert[caras[i][j]][0],normales_vert[caras[i][j]][1],normales_vert[caras[i][j]][2]);  
          glVertex3f(vertices[caras[i][j]][0],vertices[caras[i][j]][1],vertices[caras[i][j]][2]);
        }
      }
    }
    glEnd();
       
  }

  void normalCaras (std::vector<float> punto1,std::vector<float> punto2,std::vector<float> punto3, int cara)
  {
      std::vector<float> vector0;
      std::vector<float> vector1;
      std::vector<float> norm;
      float i,j,k;

      for(int i=0; i<3; i++)
      {  
        vector0.push_back(punto2[i]-punto1[i]);
        vector1.push_back(punto3[i]-punto1[i]);
      }
      i=vector0[1]*vector1[2]-vector0[2]*vector1[1];
      j=vector0[2]*vector1[0]-vector0[0]*vector1[2];
      k=vector0[0]*vector1[1]-vector0[1]*vector1[0];

      
    
      normales[cara][0]=i;
      normales[cara][1]=j;
      normales[cara][2]=k;


      float mod=sqrt(pow(normales[cara][0],2)+pow(normales[cara][1],2)+pow(normales[cara][2],2));

      if(mod>0)
      {
        normales[cara][0]=normales[cara][0]/mod;
        normales[cara][1]=normales[cara][1]/mod;
        normales[cara][2]=normales[cara][2]/mod;
      }
  }

  void normalVertices()
  {

      for(int i=0; i<caras.size();i++)
      {
        for(int j=0; j<3;j++)
        {
          normales_vert[caras[i][j]][0]+=normales[i][0];
          normales_vert[caras[i][j]][1]+=normales[i][1];
          normales_vert[caras[i][j]][2]+=normales[i][2];
        }
      }  

      for(int i=0; i<normales_vert.size(); i++)
      {
        float mod=sqrt(pow(normales_vert[i][0],2)+pow(normales_vert[i][1],2)+pow(normales_vert[i][2],2));

        if(mod>0)
        {
          normales_vert[i][0]=normales_vert[i][0]/mod;
          normales_vert[i][1]=normales_vert[i][1]/mod;
          normales_vert[i][2]=normales_vert[i][2]/mod;
        }
      }

  }

  
};

class Ejes:Objeto3D 
{ 
  public: 
    float longitud = 30;
    // Dibuja el objeto
    void draw()
    {
      glDisable (GL_LIGHTING);
      glBegin (GL_LINES);
      {
        glColor3f (0, 1, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (0, longitud, 0);

        glColor3f (1, 0, 0);
        glVertex3f (0, 0, 0);
        glVertex3f (longitud, 0, 0);

        glColor3f (0, 0, 1);
        glVertex3f (0, 0, 0);
        glVertex3f (0, 0, longitud);
      }
      glEnd ();
      glEnable (GL_LIGHTING);
    }
}; 



char * beeth="./beethoven.ply";
Ejes ejesCoordenadas;
Cubo cubo(5);
Piramide piramide;
Teseracto teseracto;
Malla bety(beeth);


/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };
  float  color2[4] = { 0.0, 1.0, 1.0, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  //glShadeModel(GL_FLAT);

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  switch (ilum)
  {
    case true:
      glEnable(GL_LIGHTING);
      break;
    default:
      glDisable(GL_LIGHTING);
      break;
  }
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)  

  bety.draw_smooth();   

  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color2);
  
  //glTranslatef(10, 0, 0);
  //piramide.draw();

  
  //glTranslatef(10, teseracto.getAltura(),teseracto.getAltura());
  //teseracto.draw();

  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
