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

/**	void initModel()

Inicializa el modelo y de las variables globales


**/

int modo=GL_FILL;
bool ilum=true;
bool rebobinar=false;
bool tomar_fecha=true;
bool preder=false;
bool sigue_gato=false;
int factor_rebobinado=0;
int hour_global;
int min_global;
int sec_global;
float tras_gato=0.5;

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


  float getFactor()
  {
    return factor;
  }

  
};


class Revolucion:public Malla
{
    private:
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


char * cilindro="./ply/cilindro.ply";
char * posa_agujas="./ply/posa_agujas.ply";
char * aguja_min="./ply/flecha1.ply";
char * aguja_hora="./ply/flecha2.ply";
char * aguja_segundos="./ply/flecha3.ply";
char * gato="./ply/fatcat.ply";

Ejes ejesCoordenadas;
Revolucion cilindro_obj (cilindro,(int)30);
Malla reposa (posa_agujas,1);
Malla aguja_min_obj (aguja_min,0.05);
Malla aguja_hora_obj (aguja_hora,0.05);
Malla aguja_sec_obj (aguja_segundos,1);
Malla cat (gato,0.025);

int get_seconds()
{
  std::time_t time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm local_time = *std::localtime(&time_now);
  int seconds = local_time.tm_sec;
  return seconds;
}

int get_minutes()
{
  std::time_t time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm local_time = *std::localtime(&time_now);
  int minutes = local_time.tm_min;
  return minutes;
}
int get_hour()
{
  std::time_t time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm local_time = *std::localtime(&time_now);
  int hour = local_time.tm_hour;
  return hour;
} 

void setRebobinar(bool modo)
{
  if(!rebobinar)
  { 
    tomar_fecha=true;
  }
  rebobinar=modo;

  if(factor_rebobinado<=3)
    factor_rebobinado++;

}

void setPreder(bool modo)
{
  if(modo==true)
    factor_rebobinado=0;
  preder=modo;
}



std::vector<int> hora_rebobinado()
{
  std::vector<int> la_hora;
  if(tomar_fecha)
  {
    hour_global=get_hour();
    min_global=get_minutes();
    sec_global=get_seconds();
    tomar_fecha=false;
  }

  if(min_global<=0 && sec_global<=0)
  {
    min_global=59;
    sec_global=59;
    hour_global-=1;
  }
  else if(sec_global<=0)
  {
    min_global-=1;
    sec_global=59;
  }
  else
  {
    sec_global=sec_global-(10*factor_rebobinado);
  }

  la_hora.push_back(hour_global);
  la_hora.push_back(min_global);
  la_hora.push_back(sec_global);

  return la_hora;
}

std::vector<int> volver_hora_preder()
{
  std::vector<int> la_hora;
  
  if(hour_global!=get_hour() || min_global!=get_minutes() || sec_global!=get_seconds())
  {
    if(sec_global!=get_seconds())
      sec_global=(sec_global+1)%60;

    if(min_global!=get_minutes()) 
        min_global=(min_global+1)%60;

    if(hour_global!=get_hour())
    {
      if(abs(hour_global-get_hour())>=1)
        hour_global=hour_global+1%24;
      else
        hour_global+=(360/60*get_minutes())/12;
    }
    la_hora.push_back(hour_global);
    la_hora.push_back(min_global);
    la_hora.push_back(sec_global);
  }
  else
  {
    preder=false;
    la_hora.push_back(get_hour());
    la_hora.push_back(get_minutes());
    la_hora.push_back(get_seconds());
  }

  return la_hora;
}

std::vector<int> devuelve_hora()
{
  std::vector<int> la_hora;
  if (rebobinar)
    la_hora=hora_rebobinado();
  else if (preder)
    la_hora=volver_hora_preder();
  else
  {
    la_hora.push_back(get_hour());
    la_hora.push_back(get_minutes());
    la_hora.push_back(get_seconds());
  }

  if(la_hora[1]==0)
  { 
    sigue_gato=true;
  }

  if(tras_gato>0 || sigue_gato)
  {
    if(tras_gato<2 && sigue_gato)
      tras_gato+=0.5;
    else if(tras_gato>0.5 && !sigue_gato)
      tras_gato-=0.5;

    if (tras_gato==2)
      sigue_gato=false;
  }


  
  return la_hora;
}

void Base()
{
  float color[4] = { 0.0, 0.5, 0.7, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  cilindro_obj.draw();
}

void Reposa_Agujas()
{ 
  float color[4] = { 0.0, 0.5, 0.15, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  reposa.draw();
}

void Aguja_min()
{
  float color[4] = { 0.0, 0.9, 0.9, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  aguja_min_obj.draw();
}

void Aguja_hora()
{
  float color[4] = { 0.9, 0.0, 0.9, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  aguja_hora_obj.draw();
}

void Aguja_segundos()
{
  float color[4] = { 0.9, 0.0, 0.0, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  aguja_sec_obj.draw();
}

void Gato()
{
  float color[4] = { 0.9, 0.0, 0.0, 1 };
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
  cat.draw();
}

void Reloj()
{
  std::vector<int> la_hora=devuelve_hora();

  glPushMatrix();
    glRotatef(90,1,0,0);
    Base();
  glPopMatrix();
 
  glPushMatrix();
    glPushMatrix();
      glTranslatef(-0.5,3.5,0.5);
      Reposa_Agujas();
    glPopMatrix();
  
    glPushMatrix();
      glRotatef(-90,0,0,1);
      glTranslatef(-0.5,3.5,0.5);
      Reposa_Agujas();
    glPopMatrix();

    glPushMatrix();
      glRotatef(-180,0,0,1);
      glTranslatef(-0.5,3.5,0.5);
      Reposa_Agujas();
    glPopMatrix();

    glPushMatrix();
      glRotatef(-270,0,0,1);
      glTranslatef(-0.5,3.5,0.5);
      Reposa_Agujas();
    glPopMatrix();
    
    glPushMatrix();

      glPushMatrix();
        glTranslatef(0.0,3.0,tras_gato);
        glRotatef(90,0.0,1.0,0.0);
        Gato();
      glPopMatrix();  

      glTranslatef(0,0,1.25);
      glRotatef(-90,1,0,0);
     
      glPushMatrix();
        glRotatef(360/60*la_hora[1]+(360/60*la_hora[2])/60,0,1,0);
        glTranslatef(-10.30*aguja_min_obj.getFactor(),-0.02,-18.94*aguja_min_obj.getFactor());
        Aguja_min();
      glPopMatrix();
      
      glPushMatrix();
        glRotatef(360/12*la_hora[0]+(360/60*la_hora[1])/12,0,1,0);
        glTranslatef(-8.23*aguja_hora_obj.getFactor(),0,-99.2*aguja_hora_obj.getFactor());
        Aguja_hora();
      glPopMatrix();
    
      glPushMatrix();
        glRotatef(360/60*la_hora[2],0,1,0);
        glTranslatef(-0.015,0,0);
        Aguja_segundos();
      glPopMatrix();
    
    glPopMatrix();

    
  glPopMatrix();
}

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

  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color2);
  Reloj();
  
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
