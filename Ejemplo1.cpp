/* **************************************************************************************************************
   PROGRAMA DE EJEMPLO No. 01
   PROGRAMAS DE EJEMPLO DEL USO DE LA LIBRERIA GLUT Y OPENGL.
   NombredelArchivo: 	PE01.cpp
   Programador:		Dr. Carlos Garcia
   Fecha:		13/Junio/2017
   Descripcion:
   Muestra la Primer Primitiva de dibujo (Un Rectangulo), ademas muestracomo seleccionar un color para dibujar.
   Compilar: g++ -c Ejemplo1.c
   Enlazar:  g++ Ejemplo1.o -o run -lglut32 -opengl32
  */

#include<gl\glut.h>

void display(void);
void DisplayView(GLsizei w, GLsizei h);

int main(int argc, char **argv)
{ //Inicializa el libreria GLUT
  glutInit(&argc,argv);
  // Tamaño de Ventana
  glutInitWindowSize(600, 600);
  //Crea una ventana
  glutCreateWindow("Hello OpenGL");
  //Asigna callback para dibujar
  glutDisplayFunc(&display);
  //Selecciona Azul como color de borrado
  glClearColor(0.0,0.0,1.0,0.0);	

  //Plano de Trabajo
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.0,10.0, -10.0, 10.0, 1.0, -1.0);
  glMatrixMode(GL_MODELVIEW); 

  //Ciclo de procesado de eventos necesita de una ventana
  glutMainLoop();
  return 0;
  }
void display(void)
{ //Borrar el Buffer de dibujo
  glClear(GL_COLOR_BUFFER_BIT);
  //seleccionar el color de dibujo
  glColor3f(1.0, 1.0, 0.0);
  //Dibujar Rectangulo
  //glRectf(0.0f, 0.0f, 10.0f, 10.0f);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_POLYGON);

  glVertex2f(0.0f,0.0f);
  glVertex2f(1.0f,1.0f);
  glVertex2f(2.0f,0.0f);
  glVertex2f(1.0f,-1.0f);
  glVertex2f(0.0f,-1.0f);
  glEnd();
  //Dibujar
  glFlush();
  }

  void DisplayView(GLsizei w, GLsizei h)
  { glViewport(0,0,300,300);
	}
