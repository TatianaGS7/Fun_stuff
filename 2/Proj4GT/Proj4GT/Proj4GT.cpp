//  Два окна одного приложения
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h> 


GLint Width1 = 460, Height1 = 370; //экран с анимацией
GLint Width2 = 300, Height2 = 300; 
GLint x1 = 100, y1 = 200;
GLint flag=1;
GLint id1=-1;
GLint id2=-1;
float x=0;
float y=0;


void Display1(void)  // эта функция управляет всем выводом на экран 
{
    glClearColor(0.9, 0.5, 0.3, 1);  // экран с анимацией
    glClear(GL_COLOR_BUFFER_BIT);  //очищает окно

	
	//рисуем фон
    

	//небо
	glBegin(GL_QUADS); 
    glColor3ub(100, 149, 237);	
    glVertex2i(0,0);
	glColor3ub(244, 164, 96); 
	glVertex2i(0,370);
	glColor3ub(147, 112, 219);
	glVertex2i(460,370); 
	glColor3ub(188, 143, 143);
	glVertex2i(460,0); 	 
    glEnd();	
	
	
	//равнина	

	glBegin(GL_POLYGON); 
	glColor3ub(24, 116, 205);
	glVertex2i(460,0);
    glVertex2i(460,90);	
	glVertex2i(390,85);
	glVertex2i(375,85);
	glVertex2i(275,85);
	glVertex2i(210,82);
	glColor3ub(92, 172, 238);
	glVertex2i(160,80);
	glVertex2i(120,86);
	glVertex2i(90,90);
	glVertex2i(0,80);
	glVertex2i(0,0);
	glEnd();

	glBegin(GL_POLYGON); 
	glColor3ub(205, 133, 63);
	glVertex2i(460,90);//0
	glColor3ub(205, 179 ,139);
    glVertex2i(460,110);//1
	glColor3ub(210, 105, 30);
	glVertex2i(400,120);//2
	glVertex2i(380,110);//3
	glVertex2i(375,70);//4
	glEnd();
   
    glBegin(GL_POLYGON); 
	glColor3ub(210, 105, 30);
	glVertex2i(460,0);//0
	glColor3ub(244, 164, 96);
    glVertex2i(460,90);//1
	glVertex2i(390,85);//2
	glColor3ub(238, 203, 173);
	glVertex2i(375,85);//3
	glVertex2i(340,70);//4
	glColor3ub(255, 222, 173);
	glVertex2i(300,60);//5
	glVertex2i(270,0);//6
	glEnd();


	//прямоуг маяка
	glBegin(GL_QUADS); 
    glColor3ub(255, 228, 225);	
    glVertex2i(280,230);
	glVertex2i(280,250);
	glColor3ub(238, 229, 222);
	glVertex2i(220,250); 
	glVertex2i(220,230); 	 
    glEnd();
	
    
	// платформа маяка
	glBegin(GL_QUADS); 
    glColor3ub(255, 228, 225);	
    glVertex2i(230,230);
	glVertex2i(270,230);
	glColor3ub(238, 229, 222);
	glVertex2i(300,0);
	glVertex2i(200,0); 	 
    glEnd();

	//треуг маяка
	glBegin(GL_TRIANGLES); 
    glColor3ub(210, 180, 140); 
    glVertex2i(230, 250);
	glVertex2i(270, 250); 
	glVertex2i(250, 270); 
    glEnd();	
	
	
	glLineWidth(2);
	glBegin(GL_LINE_STRIP); 
    glColor3ub(210, 105, 30); 	
    glVertex2i(280,230);
	glVertex2i(280,250);
	glVertex2i(220,250); 
	glVertex2i(220,230);
    glEnd();

	glBegin(GL_LINE_STRIP); 
    glColor3ub(210, 105, 30); 	
    glVertex2i(230,230);
	glVertex2i(270,230);
	glVertex2i(300,0);
	glVertex2i(200,0); 
    glEnd();

	glBegin(GL_LINE_STRIP); 
    glColor3ub(210, 105, 30); 	
    glVertex2i(230, 250);
	glVertex2i(270, 250); 
	glVertex2i(250, 270); 
    glEnd();

	//свет маяка 
	// правый
	glBegin(GL_TRIANGLES); 
    glColor3ub(255, 215, 0); 
    glVertex2i(280, 240);
	glColor3ub(218, 165, 32);
    glVertex2i(x1+230, y1+60); 
	glColor3ub(238, 221, 130);
    glVertex2i(x1+230, y1+30); 
    glEnd();

	//левый
	glBegin(GL_TRIANGLES); 
    glColor3ub(255, 215, 0); 
    glVertex2i(220, 240);
	glColor3ub(218, 165, 32);
    glVertex2i(x1-70, y1+60); 
	glColor3ub(238, 221, 130);
    glVertex2i(x1-70, y1+30); 
    glEnd();


   











	glFinish();   
	glutSwapBuffers();
}

void Display2(void)  // эта функция управляет всем выводом на экран 
{
    glClearColor(0.3, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  //очищает окно.
    glColor3f(0.0,1.0,0.0);

	glutSwapBuffers();
}


void Reshape(GLint w, GLint h)  // Функция вызывается при изменении размеров окна 
{
    Width1 = w;
    Height1 = h;

    
    glViewport(0, 0, w, h); // устанавливаем размеры  области отображения 
	glLoadIdentity();   //!!!!!!
	glOrtho(0, w, 0, h, -1, 1); //!!!!!
}


void Reshape2(GLint w, GLint h)  // Функция вызывается  при изменении размеров окна 
{
    Width2 = w;
    Height2 = h;

    
    glViewport(0, 0, w, h); // устанавливаем размеры  области отображения 
}


 
void Keyboard( unsigned char key, int x, int y ) // Функция обрабатывает сообщения от клавиатуры.
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
   }
/*

#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);
		*/
}

void flagi(void)
{
if( flag == 2 )
{
glutSetWindow(id1);
//int rab1=x1;
//int rab2=y1;
//rab1=x1/Width2;
//rab2=y1/Height2;
flag = 1;
 //  glutPostRedisplay();
Display1();
}
}


// Обрабатывает сообщения от мыши 
void Mouse1(int button, int state, int x, int y)
{
//  ....
////display();
////   glutPostRedisplay();
}


void Mouse2(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN ) 
  {
    switch( button ) 
	{
      case GLUT_LEFT_BUTTON:
x1=x;
y1=y;
flag=2;
        break;
      case GLUT_RIGHT_BUTTON:
        break;
    }
	flagi();
   glutPostRedisplay();
  }
}

void main(int argc, char *argv[])  // Главный цикл приложения 
{

    glutInit(&argc, argv);   //производит начальную инициализацию 
	                        //библиотеки GLUT. 
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);   //и настраивает полноцветный 
	                                        //(непалитровый) режим  RGB.
    //Window 1
    glutInitWindowSize(Width1, Height1);  //используется для задания размеров окна. 
	glutInitWindowPosition(200,220); //Установка позиции окна на экране
    id1=glutCreateWindow("window 1 Маяк");
    glutReshapeFunc(Reshape);  //регистрирует функцию Reshape(), которая 	  
	glutDisplayFunc(Display1);  //регистрирует функцию Display(),  которая будет вызвана  
	                         //при перерисовке окна. 
glutMouseFunc(Mouse1);


    glutKeyboardFunc(Keyboard);  //регистрирует функцию Keyboard(), 
                            	 //которая будет вызвана при 
	                             //нажатии клавиши на клавиатуре. 

    //Window 2
    glutInitWindowSize(Width2, Height2);
    glutInitWindowPosition(800,200); //установка позиции на экране компьютера
    id2=glutCreateWindow("window 2 Творческий проект");
    glutReshapeFunc(Reshape2);  //регистрирует функцию Reshape(), 
	                   
	glutDisplayFunc(Display2);
    glutMouseFunc(Mouse2);
    glutSetWindow(id2);
	
    glutMainLoop();  //Внутри бесконечного цикла в этой функции 
	                 //происходит контроль  всех событий и вызов 
	                 //нужных функций. 	
}
