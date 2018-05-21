#include <GL/glut.h> //Windows

void DibujarPantalla(void);

int main(int argc, char** argv)
{ //CONFIGURACIONES INICIALES
	glutInit(&argc, argv); //Por regla debe ir y al principio
	glutInitWindowSize(400,400);8*
	glutInitWindowPosition(200,100);
	glutCreateWindow("Hola mundo cruel");
	glClearColor(0,0,0,0); //recibe 4 y solo usamos los 3 primeros RGB entre 0 y 1 evento display dibuja la ventana
	
	//glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-5.0, 5.5,-5.0,5.0);
	//ASIGNACION DE CALLBACKS (necesito asignar una funcion a un evento) (FUNCIONES DE SERVICIO A EVENTOS)
	glutDisplayFunc(&DibujarPantalla); //recibe un parametro, en este caso referencia o direccion a una funcion en este caso es dibujar pantalla
	//glutReshapeFunc(&CambiarTamanoVista);//Evento cambiar la forma
	
	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}
	void DibujarPantalla()
	{ /*float x,y,b,m;
		m=1;// pendiente =0 para que sea horizontal, igual a 1 de 45 grados, igual a para que sea de 90
		b=0; //b=0 para que pase por el origen
		glClear(GL_COLOR_BUFFER_BIT); //borra pantalla
		glColor3f(1,0,0);
		glBegin(GL_POINTS);//Vertices necesarios;
		
		for(x=0;x<5;x=x+0.1)
		{
			y=m*x+b;
			glVertex2f(x,y);
		}*/
		float m,b,x,y;
		m=1;// pendiente =0 para que sea horizontal, igual a 1 de 45 grados, igual a para que sea de 90
		b=0; //b=0 para que pase por el origen
		glColor3f(0,1,1);
		glBegin(GL_POINTS);//Vertices necesarios;
		
		for(x=0;x<5;x=x+0.1)
		{
			y=m*x+b;
		
		glVertex2f(x,y);
		}
		
		glEnd();
		glFlush();
		glVertex2f(0,0);
		glVertex2f(0.25,0.25);
		glVertex2f(0.5,0.5);
		
		/////glClear(GL_COLOR_BUFFER_BIT); //borra pantalla
		////glColor3f(0,1,0);
		/////glRectf(-1,1,0,0); //dibuja rectangulo
		//////glColor3f(1,1,0);
		////////glRectf(-1,1,-0.5,0.5); //dibuja rectangulo
		
		glColor3f(0,0,1);
		glRectf(0,0,5,5); //dibuja rectangulo
		glFlush(); //siempre se pone al ultimo de la funcion que tiene al evento display
	}
	
	/*void CambiarTamanoVista(GLsizei w, GLsizei h) //Nombre que queramos, los parámetros exactos
	{
		glViewport(0,0,200,200); //0x0 esquina inferior y 200x200 distancia que va a recorrer
	}*/