//Objetos geometricos 
#include <GL/glut.h> //Windows
#include <math.h>
#include <stdlib.h>

typedef enum
{
	NEGRO, AZUL, VERDE, CYAN, ROJO, MAGENTA, AMARILLO, BLANCO, GRIS, 
	NARANJA, AMARILLOVERDE, VERDECLARO,  VERDEDARK,ARENA, LIMA, DORADO, 
	SALMON,CAFE, MARRON, PURPURA, OLIVA, AGUA, CORAL, CIefedcfefefeeLO, MILITAR, ROSA, SILVER
}COLOR;

const float PALETA_COLORES[27][3]={	0,0,0,			//negro
									0,0,1,			//Azul
									0,1,0,			//Verde
									0,1,1,			//Cyan
									1,0,0,			//Rojo
									1,0,1,			//Magenta 
									1,1,0,			//Amarillo
									1,1,1,			//Blanco
									0.5,0.5,0.5,	//GRIS
									1,0.5,0,		//Naranja
									0.5,1,0, 		//Amarilloverde
									0.5,1,0.5,		//VergeClaro
									0,0.5,0,		//Verdeoscuro
									0.95,0.64,0.37,	//ARENA 
									0.19,0.8,0.19,	//LIMA
									1, 0.84,0, 		//DORADO
									0.98,0.5,0.44,	//SALMON
									0.64,0.16,0.16,	//CAFE
									0.54,0.41,0.29,	//MARRON
									0.68,0.32,0.83,	//PURPURA
									0.33,0.41,0.18,	//OLIVA
									0.49,1,0.83, 	//AGUA
									1,0.5,0.31,		//CORAL
									0.59,0.96,1,	//CIELO
									0.09,0.34,0.13, //MILITAR
									0.73, 0.56, 0.56,	//ROSA
									0.90, 0.91,0.98		//SILVER
									};
									typedef struct{
              float x; 
              float y;
              }PUNTO;

typedef struct{
              float Xi; 
              float Yi;
              float Xf; 
              float Yf;
              }LINEA;

typedef struct{ 
              float X; 
              float Y;
              float L; 
             }CUADRADO;

typedef struct{
              float x; 
              float y;
              float b; 
              float a;
              }RECTANGULO;

typedef struct{
              float x; 
              float y;
              float b; 
              float a;
              }TRIANGULO;

typedef struct{
              unsigned int NL;
              PUNTO *Vx;
              }POLIGONO;

typedef struct
            { float Xc; 
              float Yc;
              float r;
             }CIRCULO;

typedef struct
            { float Xc; 
              float a;
              float yc;
              float b;
              float th;
             }ELIPSE;

const float PI=3.141596;
COLOR Colorseleccionado=0;
char Coordenadas[40]="(0,0)";
//unsigned char Presionado=0;
unsigned int IdCirculo=0;
CIRCULO Vcirculo[100];
LINEA Vlinea[100];
unsigned int IdLinea=0;
float tx=0,ty=0;
float sx=0,sy=0;

void SetColor();
void DibujarPantalla(void);
void DibujarTexto(char*Text, float x, float y);
void Raton(int Boton, int Estado, int x, int y);
void RatonPasivo(int x, int y);
void RatonActivo(int x, int y);
void DLinea(LINEA *l);
void DCirculo(CIRCULO *l);
void DibujarPantalla(void);
void DCuadrado(CUADRADO *C);
void DRectangulo(RECTANGULO *R);
void DTriangulo(TRIANGULO *T);
void DPoligono(POLIGONO *P);
void DElipse(ELIPSE *E);
void SetColor(COLOR c);
void TeclaEspecial(int tecla,int x, int y);
void TeclaNormal(unsigned char tecla,int x, int y);

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);				//&Paso por referencia 
	glutInitWindowPosition(100,100);	//posicion de la ventana (x,y)
	glutInitWindowSize(400, 400);		//Tamaño de la ventana (width, height)
	glutCreateWindow("PALETA DE COLORES!");//crear la ventana--El mensaje que aparece en la ventana 

	glClearColor(1,1,1,0); // Definir el color(RGB,),solo sirve con 0 o 1 y con decimales---color de fondo

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10.0, 10.0, -10.0,10.0);

	//ASIGNACION DE CALLBACKS (FUNCIONES DE SERVICIO A EVENTOS)
 	glutDisplayFunc(&DibujarPantalla);	//Funcion display-Recibe(&referencia a funcion)
 	//glutMouseFunc(&Raton);
 	//glutPassiveMotionFunc(&RatonPasivo);
 	//glutMotionFunc(&RatonActivo);
 	glutSpecialFunc(&TeclaEspecial);
 	glutKeyboardFunc(&TeclaNormal);
 	//glutReshapeFunc(&CambiarTamanoVista);//Para ajustar a cierto Tamaño

 	//ESTADO DE ESPERA DE EVENTOS
 	glutMainLoop(); //Entra en el Bucle de procesamientos de datos
 	return 0;
}

void DibujarTexto(char*Text, float x, float y)
{
	char *c;
	glRasterPos2f(x,y);
	for(c=Text;*c!='\0';c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void TeclaEspecial(int tecla,int x, int y)
{
	switch(tecla)
	{
		case GLUT_KEY_F1 : Colorseleccionado=ROJO;
		break;
		case GLUT_KEY_F2 : Colorseleccionado=VERDE;
		break;
		case GLUT_KEY_F3 : Colorseleccionado=AZUL;
		break;
	}
	glutPostRedisplay();
}

void TeclaNormal(unsigned char tecla,int x, int y)
{ 
	int mod;
	if(tecla=27)
		exit(0);
	if((tecla=='R')||(tecla='r'))
		tx+=-0.5;
	if((tecla=='L')||(tecla='l'))
		tx+=-0.5;
	if((tecla=='U')||(tecla='u'))
		ty+=0.5;
	if((tecla=='D')||(tecla='d'))
		ty+=0.5;
	if((tecla=='W')||(tecla='w'))
		{
			sx+=1;
			sy=sx;
		}
	if((tecla=='Q')||(tecla='q'))
		{
			sx-=1;
			sy=sx;
		}
	glutPostRedisplay();
		


/*
	int mod;
	if(tecla=27)
		exit(0);
	if(tecla=='C')
		{ mod=glutGetModiflers();
			if(mod == GLUT_ACTIVE_ALT)
		        sprintf(Coordenadas,"(%i.%i)",x,y);
	    }
	glutPostRedisplay();*/
}

void Raton(int Boton, int Estado, int x, int y)
{
	/*if((x<200)&&(y<200))
	{
	if((Boton==GLUT_LEFT_BUTTON)&&(Estado==GLUT_DOWN))
	{
		Colorseleccionado++;
		if(Colorseleccionado==27)Colorseleccionado=0;
	}
	if((Boton==GLUT_LEFT_BUTTON)&&(Estado==GLUT_UP))
	{
		Colorseleccionado++;
		if(Colorseleccionado==27)Colorseleccionado=0;
	}*/
	//CIRCULO
    /*if((Boton==GLUT_LEFT_BUTTON)&&(Estado==GLUT_DOWN))
       {
        Vcirculo[IdCirculo].Xc=((float)x-200)/20;
		Vcirculo[IdCirculo].Yc=((float)y-200)/-20;
		Vcirculo[IdCirculo].r=1;
		IdCirculo++;
	   }
	if((Boton==GLUT_RIGHT_BUTTON)&&(Estado==GLUT_DOWN))
	{
		exit(0);
	}
	glutPostRedisplay();*/
	
	if((Boton==GLUT_LEFT_BUTTON)&&(Estado==GLUT_DOWN))
       {
        Vlinea[IdLinea].Xi=((float)x-200)/20;
		Vlinea[IdLinea].Yi=((float)y-200)/-20;
		Vlinea[IdLinea].Xf=Vlinea[IdLinea].Xi;
		Vlinea[IdLinea].Yf=Vlinea[IdLinea].Yi;
		IdLinea++;
	   }
	if((Boton==GLUT_RIGHT_BUTTON)&&(Estado==GLUT_DOWN))
	{
		exit(0);
	}
	glutPostRedisplay();
}

void RatonPasivo(int x, int y)
{
	//char Texto[10];
	sprintf(Coordenadas, "(%i,%i)",x,y);
	//DibujarTexto("texto", 0,0);
	glutPostRedisplay();
}

void RatonActivo(int x, int y)
{
	Vlinea[IdLinea-1].Xf=((float)x-200)/20;
	Vlinea[IdLinea-1].Yf=((float)y-200)/-20;
	//sprintf(Coordenadas, "(%i,%i)",x,y);
	glutPostRedisplay();
}

/*void DibujarPantalla()
{
	//COLOR Color;
	glClear(GL_COLOR_BUFFER_BIT);
	SetColor(AMARILLOVERDE);	

	SetColor(Colorseleccionado);
	glRectf(0,0,10,10);

	//Modificar atributos de la primitiva punto
	//SetColor(ROJO);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	glVertex2f(0,0);
	glEnd();

	//Modificar atributos para el ancho de linea 
	//SetColor(MAGENTA);
	/*glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(-5,2);
	glVertex2f(5,-2);
	glEnd();

	//Modificar atributos pata el tipo de linea 
	//SetColor(NARANJA);
	glLineWidth(1.0); 
	glLineStipple(4,0xAAAA);//(Factor de escala como zoom, patron casi siempre en exadecimal de 16 bits ya que tiene 4 parametros de 4 bits)
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(-5,2);
	glVertex2f(5,-2);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	//Modificar atributos para el poligono
	//SetColor(AZUL);
	glPolygonMode(GL_FRONT, GL_LINE);

	glBegin(GL_POLYGON);
	glVertex2f(-5,-5);
	glVertex2f(5,-5);
	glVertex2f(0,5);
	glEnd();

	//DibujarTexto("Texto en OpenGl", 0,0);
	DibujarTexto(Coordenadas,-9.5,-9.5);

	/*glClear(GL_COLOR_BUFFER_BIT);	//Borra la pantalla(contiene el color que se seleccion
	for(i=0;i<27;i++)
	{
		SetColor(i);
		glRectf(i-15,0,i+1-15,5);
	}
	glFlush();//todo lo que aparece en la memoria lo pone en la ventana 
}*/

void SetColor(COLOR c)
{
	glColor3f(PALETA_COLORES[c][0], PALETA_COLORES[c][1], PALETA_COLORES[c][2]);
}


void DibujarPantalla()
{
	LINEA L1,L2;
	float tx,ty;

	glClear(GL_COLOR_BUFFER_BIT); //Examen
	SetColor(CYAN);
	L1.Xi=2.5;
	L1.Xf=7.5;
	L1.Yi=2.5;
	L1.Yf=7.5;
	DLinea(&L1);
	
	SetColor(MAGENTA); //Examen
	L1.Xi=-2.5;
	L1.Yi=2.5;
	L1.Xf=-7.5;
	L1.Yf=7.5;
	DLinea(&L1);
	
	/*L1.Xi=-5;
	L1.Xf=5;
	L1.Yi=5;
	L1.Yf=-5;
	DLinea(&L1);
	//traslacion

	L2.Xi=L1.Xi+tx;
	L2.Xf=L1.Xf+tx;
	L2.Yi=L1.Yi+ty;
	L2.Yf=L1.Yf+ty;

	//Escalaiento
	
	L2.Xi=L1.Xi*sx+1*(1-sx);
	L2.Xf=L1.Xf*sx+1*(1-sx);
	L2.Yi=L1.Yi*sy+1*(1-sy);
	L2.Yf=L1.Yf*sy+1*(1-sy);

	DLinea(&L2);
*/

	glFlush();
}

/*
	//FUNCIONES DE OPEN GL
	//COLOR Color;
	int i;
	glClear(GL_COLOR_BUFFER_BIT);	//Borra la pantalla(contiene el color que se seleccion
	SetColor(Colorseleccionado);
	glRectf(0,0,10,10);
	SetColor(ROJO);
	for(i=0;i<IdLinea;i++)
	{
		DLinea(&Vlinea[i]);
	}
	for(i=0;i<IdCirculo;i++)
	{
		DCirculo(&Vcirculo[i]);
	}
	
	
	//SetColor(VERDE);
    //glRectf(0,0,10,10);
	glFlush();//todo lo que aparece en la memoria lo pone en la ventana 
}*/

/*LINEA * l;  //Puntero para linea a dibujar

l = (LINEA *)malloc(sizeof(LINEA)); //Definicion del tamaño del puntero

//______________VALORES DEL PUNTERO
l->Xi = 0; //Valor inicial en x
l->Yi = 0; //Valor inicial en y
l->Xf = 10; //Valor final en x
l->Yi= 10; //Valor final en y

glClear(GL_COLOR_BUFFER_BIT); //Limpia la pantalla
glColor3f(0, 1, 0); //color verde
DLinea(l); //Llamado a la función para dibujar linea


free(l); //Liberar puntero
glFlush(); //Fuerza a que se haga el dibujo
}*/
/* unsigned int colorid;
ELIPSE *E;
 glClear(GL_COLOR_BUFFER_BIT);
 color=0;
 glColor3f(PALETA_COLORES P[colorid][0],PALETA_COLORES P[colorid][1],PALETA_COLORES P[colorid][2]);
 E=(ELIPSE *) malloc(sizeof(ELIPSE));

E->Xc=0.0;
E->a=10; 
E->yc=0.0;
E->b=5;
E->th=0.0;
DElipse(E);

free(E);
glFlush();
}/*

/*
unsigned  int ColorId;// paleta de colores
glClear(GL_COLOR_BUFFER_BIT);

for(ColorId=0;ColorId<27;ColorId++) //Dibujar un rectangulo con cada color de la paleta de colores
  {
    glColor3f(PALETA_COLORES[ColorId][0],PALETA_COLORES[ColorId][1],PALETA_COLORES[ColorId][2]); //Color rojo
    glRectf(ColorId,0,ColorId+1,2);
    glFlush();
  }
}
void SetColor(COLOR c)
{
 glColor3f(PALETA_COLORES[c][0],PALETA_COLORES[c][1],PALETA_COLORES[c][2]);

}*/
 /*unsigned int colorid;
  POLIGONO*P;
 glClear(GL_COLOR_BUFFER_BIT);
 color=0;
 glColor3f(PALETA_COLORES P[colorid][0],PALETA_COLORES P[colorid][1],PALETA_COLORES P[colorid][2]);
 P=(POLIGONO *)malloc(sizeof(POLIGONO));
 P->NL=5;
 P->Vx=(PUNTO *)malloc(P->NL*sizeof(PUNTO));
 
  P->Vx[0].x=-10;
  P->Vx[0].y=0;
  P->Vx[1].x=0;
  P->Vx[1].y=10;
  P->Vx[2].x=10;
  P->Vx[2].y=0;
  P->Vx[3].x=5;
  P->Vx[3].y=-9;
  P->Vx[4].x=-5;
  P->Vx[4].y=-9;
  DPoligono(P);
 free(P->Vx);
 free(P);
 glFlush();
 }*/
  /*TRIANGULO*T;
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 T=(TRIANGULO *) malloc(sizeof(TRIANGULO));

T->x=-5;
T->y=-5; 
T->b=10;
T->a=10;
DTriangulo(T);
free(T);
glFlush();
 }*/

  /*RECTANGULO*R;
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 R=(RECTANGULO *) malloc(sizeof(RECTANGULO));

R->x=-5;
R->y=-5; 
R->b=10;
R->a=5;
DRectangulo(R);
free(R);
glFlush();
*
}*/
/*CIRCULO *circulo;
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 circulo=(CIRCULO *) malloc(sizeof(CIRCULO));

circulo->r=4;
circulo->Xc=5; 
circulo->Yc=5;
DCirculo(circulo);

free(circulo);*/

/*CUADRADO *cuad;
 glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0);

cuad=(CUADRADO *) malloc(sizeof(CUADRADO));

cuad->X=-5;
cuad->Y=-5;
cuad->L=10;
DCuadrado(cuad);
free(cuad);
 glFlush();
}
*/




void DLinea(LINEA *l)
{
float x, y; //Variables que se utilizaran para graficar

glBegin(GL_POINTS);
for(x = l->Xi; x <= l->Xf; x+=.01) //Ciclo para incrementar X
{
y = ((l->Yf- l->Yi)/(l->Xf - l->Xi)) * (x - l->Xi) + l->Yi;
glVertex2f(x, y);
}
glEnd();
	
}


void DCirculo(CIRCULO *c)
{glBegin(GL_LINE_STRIP); 
     float x,y,theta;
        
        for(theta=0;theta<(2*PI); theta+=(PI/16.0))
{
        x=c->r*cos(theta)+c->Xc;
        y=c->r*sin(theta)+c->Yc;
        glVertex2f(x,y);
}
         glEnd();


}


/*void DCuadrado(CUADRADO *C)
{
glBegin(GL_LINE_LOOP);//Para poner un punto
        glVertex2f(C->X,C->Y);//en el vertice x,y
	glVertex2f(C->X,C->Y+C->L);
        glVertex2f(C->X+C->L,C->Y+C->L);
        glVertex2f(C->X+C->L,C->Y);
	glEnd();//Finaliza la funcion de punto

}
*/
/*
void DRectangulo(RECTANGULO *R)
{
glBegin(GL_LINE_LOOP);//Para poner un punto
        glVertex2f(R->x,R->y);//en el vertice x,y
        glVertex2f(R->x,R->y+R->a);
        glVertex2f(R->x+R->b,R->y+R->a);
        glVertex2f(R->x+R->b,R->y);
  glEnd();//Finaliza la funcion de punto
}
*/
/* void DTriangulo(TRIANGULO *T)
{
glBegin(GL_LINE_LOOP);//Para poner un punto
        glVertex2f(T->x,T->y);//en el vertice x,y
  glVertex2f(T->x,T->y);
        glVertex2f(T->x+(T->b/2.0),T->y+T->a);
        glVertex2f(T->x+T->b,T->y);
  glEnd();//Finaliza la funcion de punto
}
*/
 /*void DPoligono(POLIGONO *P)
{
  unsigned int  k;
  glBegin(GL_LINE_LOOP);//Para poner un punto
  for(k=0;k<P->NL;k++)
  {
        glVertex2f(P->Vx[k].x,P->Vx[k].y);
  }
  glEnd();//Finaliza la funcion de punto
}*/

/*void DElipse(ELIPSE *E)
{glBegin(GL_LINE_LOOP); 
     float x,y,th,xr,yr;
        
        for(th=0;th<360; th+=10)
{
        x=E->a*cos((th/180)*3.141596);
        y=E->b*sin((th/180)*3.141596);
        xr = x * cos((E->th/180) * 3.141596) - y * sin((E->th/180) * 3.141596) + E->xc;
        yr = x * sin((E->th/180) * 3.141596) + y * cos((E->th/180) * 3.141596) + E->yc; 
        glVertex2f(xr,yr);
}
         glEnd();
}*/




