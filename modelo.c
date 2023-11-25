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
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "lector-jpg.h"

/**	void initModel()

Inicializa el modelo y de las variables globales


**/

int modo=GL_FILL;
bool ilum=true;


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


class Malla:Objeto3D
{
  protected:
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> normales;
    std::vector<std::vector<float>> normales_vert;
    std::vector<std::vector<int>> caras;
    GLfloat colorDifusa[4];
    GLfloat colorEspecular[4];
    float factor;
    

  public:

  Malla(){}

  Malla(char * fichero,float fact)
  {
    std::vector<float> vert,tmp;
    std::vector<int> po,car;

    factor=fact;
    ply::read(fichero,vert,po);
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
      tmp.push_back(factor*vert[i]);
      
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
        for(int j=0; j<caras[i].size();j++)
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

  void setReflecDifusa(float r, float g, float b)
  {
    colorDifusa[0]=r;
    colorDifusa[1]=g;
    colorDifusa[2]=b;
    colorDifusa[3]=1.0;
  }

  void setReflecEspecular(float r, float g, float b)
  {
    colorEspecular[0]=r;
    colorEspecular[1]=g;
    colorEspecular[2]=b;
    colorEspecular[3]=1.0;
  }


  float getFactor()
  {
    return factor;
  }

  
};

class Dado:public Malla
{
  private:
    unsigned char * texels;
    unsigned int ancho;
    unsigned int alto;
    std::vector<std::vector<float>> textura;
    GLuint texId;

  public:
  
    Dado() 
    {
      glBindTexture(GL_TEXTURE_2D, texId);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
      vertices.push_back({0.0,0.0,0.0}); //0
      textura.push_back({0,0.74707031});

      vertices.push_back({0.0,0.0,1.0}); //1
      textura.push_back({0.24804688,0.74707031});

      vertices.push_back({0.0,1.0,1.0}); //2 
      textura.push_back({0.24804688,0.50195313});

      caras.push_back({0,1,2});
      
      vertices.push_back({0.0,1.0,0.0});  //3
      textura.push_back({0,0.50195313});
      
      caras.push_back({0,2,3});

      vertices.push_back({1.0,0.0,1.0}); //4
      textura.push_back({0.49609375,0.74707031});

      caras.push_back({1,4,2});

      vertices.push_back({1.0,1.0,1.0});  //5 
      textura.push_back({0.494140625,0.50195313});

      caras.push_back({2,4,5});

      vertices.push_back({1.0,0.0,0.0}); //6
      textura.push_back({0.7431606,0.74707031});

      vertices.push_back({1.0,1.0,0.0});  //7
      textura.push_back({0.7431606,0.50195313});

      caras.push_back({5,4,7});
      caras.push_back({7,4,6});

      vertices.push_back({0.0,0.0,0.0});//0
      textura.push_back({0.99316406,0.74707031});

      vertices.push_back({0.0,1.0,0.0});//3
      textura.push_back({0.99316406,0.50195313});

      caras.push_back({6,8,9});
      caras.push_back({6,9,7});
      
      vertices.push_back({0.0,1.0,0.0});//3
      textura.push_back({0.74023438,0.25390625});
      
      caras.push_back({10,5,7});

      vertices.push_back({0.0,1.0,1.0});//2
      textura.push_back({0.49609375,0.25390625});

      caras.push_back({10,11,5});

      vertices.push_back({0.0,0.0,0.0});
      textura.push_back({0.7421875,0.99609375});
      
      vertices.push_back({0.0,0.0,1.0});
      textura.push_back({0.495117188,0.99609375});

      caras.push_back({12,4,13});
      caras.push_back({12,6,4});

      setReflecDifusa(0.8,0.8,0.8);
      setReflecEspecular(0,0,0);

      for(int i=0; i<caras.size(); i++)
        normales.push_back({0,0,0});
    }


    void draw_text()
    {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, colorDifusa);
      glMaterialfv(GL_FRONT, GL_SPECULAR, colorEspecular);

      glEnable(GL_TEXTURE_2D);
      
      glBegin(GL_TRIANGLES);
      {
        for(int i=0; i<caras.size(); i++)
        {
          normalCaras(vertices[caras[i][0]],vertices[caras[i][1]],vertices[caras[i][2]],i);
            
          glNormal3f(normales[i][0],normales[i][1],normales[i][2]);
          for(int j=0; j<3; j++)
          {
            glTexCoord2f(textura[caras[i][j]][0],textura[caras[i][j]][1]);
            glVertex3f(vertices[caras[i][j]][0],vertices[caras[i][j]][1],vertices[caras[i][j]][2]);
          }
        }
      }
      glEnd();

      glDisable(GL_TEXTURE_2D);

    }

    
  void aniadirTextura(unsigned int anch, unsigned int alt, const char * fichero_textura)
  {
    texels=LeerArchivoJPEG(fichero_textura, anch,alt);
    glGenTextures(1,&texId);
    alto=alt;
    ancho=anch;
  }
};

class Revolucion:public Malla
{
    protected:
      std::vector<std::vector<float>> vertices_iniciales;
      int revoluciones;

    public:

    Revolucion(const char * fichero, int n)
    {
      std::vector<std::vector<float>> vertices_tmp;
      std::vector<float> punt_iniciales, puntos_tmp;
      
      revoluciones=n;
    
      ply::read_vertices(fichero,punt_iniciales);
      for(int i=0; i<punt_iniciales.size(); i++)
      {
        puntos_tmp.push_back(punt_iniciales[i]);
        
        if(puntos_tmp.size()==3)
        {
          vertices_tmp.push_back(puntos_tmp);
          puntos_tmp.clear();
        }
      }
      vertices_iniciales=vertices_tmp;

      for(int i=0; i<n; i++)
      {
        for(int j=0; j<vertices_iniciales.size(); j++)
        {
          float radio=sqrt(pow(vertices_iniciales[j][0],2)+pow(vertices_iniciales[j][2],2));
          float angulo_giro=(2*M_PI*i)/(n-1);
          for (int k=0; k<vertices_iniciales[j].size(); k++)
          {
            switch (k)
            {
              case 0:
                puntos_tmp.push_back(radio*cos(angulo_giro));
                break;
              case 1:
                puntos_tmp.push_back(vertices_iniciales[j][k]);
                break;
              case 2:
                puntos_tmp.push_back(radio*sin(angulo_giro));
                break;
            }
          }
          vertices.push_back(puntos_tmp);
          puntos_tmp.clear();
        }
      }
      
      calculoCaras();

      for(int i=0; i<caras.size(); i++)
          normales.push_back({0,0,0});
    }



    void calculoCaras()
    {
        std::vector<int> cara_tmp1, cara_tmp2;

        for(int i=0; i<revoluciones-1;i++)
        {
          for(int j=0; j<vertices_iniciales.size()-1;j++)
          {
            int k=i*vertices_iniciales.size()+j;

            cara_tmp1.push_back(k+vertices_iniciales.size()+1);
            cara_tmp1.push_back(k+vertices_iniciales.size());
            cara_tmp1.push_back(k);
            
            cara_tmp2.push_back(k+1);
            cara_tmp2.push_back(k+vertices_iniciales.size()+1);
            cara_tmp2.push_back(k);
            
            caras.push_back(cara_tmp1);
            caras.push_back(cara_tmp2);
            cara_tmp1.clear();
            cara_tmp2.clear();
          }
        }
    }
};

class Lata:public Revolucion
{
  
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


const char * lect="./texturas/dado.jpg";
Dado dado;
Ejes ejesCoordenadas;





/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  
  float color1[4] = { 0.5, 0 ,0.4 ,1};
  float color2[4] = { 0.0, 1.0, 1.0, 1};
  float color3[4]={0.1,0.6,0.4,1};

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  		// Apila la transformacion geometrica actual


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

  dado.aniadirTextura(1024,1024,lect);
  dado.draw_text();
  
  
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
