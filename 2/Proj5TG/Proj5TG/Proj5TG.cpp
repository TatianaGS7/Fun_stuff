//Сначала: какое-то время - черное окно. Затем: картинка на мигающем фоне.
//glutTimerFunc, Sleep.

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")


#include <stdlib.h>
#include <windows.h>

#include <gl/glut.h>  // подключаем библиотеку GLUT 

GLint Width = 600, Height = 400;  

                                  
GLint a=0;



void Display(void)  // эта функция управляет всем выводом на экран 
{   
	if (a==0) 
	{
    glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);  //очищает окно.
    //	Сбросить все данные на обработку в конвейер преобразования OpenGL
	//	без ожидания завершения предыдущих инструкций
	glFlush();
	//	Меняем местами задний и передний буферы
	glutSwapBuffers();	

   Sleep(1000);
	}
	else
	{
    

	glLineWidth(3); // небо
	glBegin(GL_QUADS); 
    glColor3ub(176, 196, 222);	
    glVertex2i(0,400);
	glColor3ub(135, 206, 235); 
	glVertex2i(0,120);
	glColor3ub(255, 192, 203);
	glVertex2i(600,120); 
	glColor3ub(100, 149, 237);
	glVertex2i(600,400); 	 
    glEnd();

		
	glBegin(GL_QUADS);  // трава
    glColor3ub(179, 238, 58);	
    glVertex2i(0,0);
	glColor3ub(124, 252, 0); 
	glVertex2i(0,120);
	glColor3ub(60, 179, 113);
	glVertex2i(600,120); 
	glColor3ub(0, 255, 127);
	glVertex2i(600,0); 	 
    glEnd();


	glBegin(GL_TRIANGLE_FAN);  //  радуга д
    glColor3ub((char)rand(), (char)rand(), (char)rand());	
    glVertex2i(300,120);
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(70,120);
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(150,230); 
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(200,260); 
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(300,270); 
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(400,260); 
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(450,230); 
	glColor3ub((char)rand(), (char)rand(), (char)rand());
	glVertex2i(530,120); 
    glEnd();

	glBegin(GL_TRIANGLE_FAN);  //  радуга с
    glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);	
    glVertex2i(300,120);
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(100,120);
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(170,210); 
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(210,240); 
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(300,250); 
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(390,240); 
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(430,210); 
	glColor3ub((char)rand()%256, (char)rand()%256, (char)rand()%256);
	glVertex2i(500,120); 
    glEnd();


    glBegin(GL_TRIANGLE_FAN);  //  радуга б
    glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);	
    glVertex2i(300,120);
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(130,120);
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(180,190); 
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(220,220); 
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(300,230); 
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(380,220); 
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(420,190); 
	glColor3ub((char)rand()%200, (char)rand()%200, (char)rand()%200);
	glVertex2i(470,120); 
    glEnd();


	glBegin(GL_TRIANGLE_FAN);  //  радуга а
    glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);	
    glVertex2i(300,120);
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(160,120);
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(190,170); 
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(230,200); 
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(300,210); 
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(370,200); 
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(410,170); 
	glColor3ub((char)rand()%100, (char)rand()%100, (char)rand()%100);
	glVertex2i(440,120); 
    glEnd();

	glBegin(GL_TRIANGLE_FAN);  // небо - радуга 
    glColor3ub(135, 206, 235);	
    glVertex2i(300,120);	
	glVertex2i(190,120);
	glVertex2i(210,160); 
	glVertex2i(240,180);
	glColor3ub(255, 192, 203); 
	glVertex2i(300,190); 
	glVertex2i(370,180); 
	glVertex2i(390,160); 
	glVertex2i(410,120); 
    glEnd();
    

	glBegin(GL_TRIANGLE_STRIP);  // дорога  
    glColor3ub(238, 203, 173);	
    glVertex2i(220,120);
	glColor3ub(255, 140, 0);
	glVertex2i(390,120);
	glColor3ub(255, 127, 80);
    glVertex2i(205,80); 
	glColor3ub(255, 160, 122);
	glVertex2i(410,30); 
	glColor3ub(255, 140, 0);
	glVertex2i(180,0); 
	glColor3ub(238, 207, 161);
    glVertex2i(420,0);
    glEnd();
 
	
	//	Сбросить все данные на обработку в конвейер преобразования OpenGL
	//	без ожидания завершения предыдущих инструкций
	glFlush();
	//	Меняем местами задний и передний буферы
	glutSwapBuffers();

	}
}



void initAW(void)
  {
  glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);  //очищает окно.

 //glFlush();   Single buffered, so needs a flush. 
 //  glFinish(); 
Display();
    }

void Reshape(GLint w, GLint h)  // Функция вызывается 
                                // при изменении размеров окна 
{
    Width = w;
    Height = h;

    
    glViewport(0, 0, w, h); // устанавливаем размеры 
                         	// области отображения 
  glMatrixMode(GL_PROJECTION);  // Start modifying the 
                                //projection matrix. 
  glLoadIdentity();             // Reset project matrix. 
  glOrtho(0, w, 0, h, -1, 1);   // Map abstract coords directly 
                                //to window coords.
 //glScalef(1, -1, 1);            // Invert Y axis so increasing Y 
                                //goes down. 
 // glTranslatef(0, -h, 0);       // Shift origin up to upper-left 
                                //corner. 
}


 
void Keyboard( unsigned char key, int x, int y ) // Функция 
                      //обрабатывает сообщения от клавиатуры.
{
#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);
}
/*
{
   switch (key) {
      case 27: // escape 
         exit(0);
         break;
   }
}
*/



void timAW(int value) // Timer function
{
	a=1;

    glutTimerFunc(400, timAW, 0); // Setup next timer
// glutPostRedisplay();  // Redraw windows

 Display();
}

void main(int argc, char *argv[])  // Главный цикл приложения 
{
    glutInit(&argc, argv);   //производит начальную инициализацию 
	                         //библиотеки GLUT. 

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //настраивает полноцветный 
	                                            //(непалитровый) режим  RGB.
	                         //и инициализирует двойную буферизацию кадра 
 
    glutInitWindowSize(Width, Height);  //используется для задания 
	                                    //начальных размеров окна. 
    glutCreateWindow("timerAW");  
	                                    // задает 
	                                    //заголовок окна и визуали- 
	                                    //зирует само окно на экране.


    glutDisplayFunc(Display);  //регистрирует функцию Display(), 
                               // которая будет вызвана  
                           //при перерисовке окна. 

	initAW();
    glutReshapeFunc(Reshape);  //регистрирует функцию Reshape(), 
	                           //которая будет вызвана 
		                       //при изменении размеров окна. 


    glutKeyboardFunc(Keyboard);  //регистрирует функцию Keyboard(), 
                            	 //которая будет вызвана при 
	                             //нажатии клавиши на клавиатуре.
	

	
  glutTimerFunc(200, timAW, 0);//	a=1;	

    glutMainLoop();  //Внутри бесконечного цикла в этой функции 
	                 //происходит контроль  всех событий и вызов 
	                 //нужных функций.

}

/*
void glutTimerFunc(unsigned int millis, void (*func)(int value), int value); 

Эта функция устанавливает таймер. Первый параметр 
millis задает время в миллисекундах, по истечении которых 
вызывается функция, которая указана как второй параметр. 
Третий параметр value указывает индентификатор таймера, 
т.е. таймеров может быть одновременно запущено несколько. 
То же самое значение value есть и в функции, которая вызывается 
таймером. Это нужно для того, чтобы определить, какой таймер 
сработал, т.е. если ваша функция обрабатывает несколько таймеров.
*/



  