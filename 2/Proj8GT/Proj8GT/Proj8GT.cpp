// "c  и v" - старт для изменения вида (цвета фигуры)


#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <al/al.h>
//#include <al/alc.h>
#include <al/alut.h>

#include <conio.h>

//	Подключает сами библиотеки: opengl32.dll, glu32.dll, glut32.dll, glaux.dll, OpenAL32.dll.
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib") 

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
//#pragma comment(lib, "OpenAL32.lib")
//#pragma comment(lib, "alut.lib") 

int flag1=0;



// параметры материала шара 
/* освещение может быть разделено на 4 компонента: фоновое (ambient), диффузное (diffuse), зеркальное (specular) и исходящее (эмиссионное – emissive). 
Все 4 компонента рассчитываются независимо и только затем суммируются.*/

float mat1_dif[]={0.5f,0.3f,0.7f}; //Интенсивность диффузного света (значение по умолчанию для 0-го источника - белый свет, для остальных - черный)
float mat1_amb[]= {0.5f,0.5f,0.5f}; //Интенсивность фонового света
float mat1_spec[]={0.5f,0.5f,0.5f}; // Интенсивность зеркального света
float mat1_shininess=0.3f*128; //кол-во света

// параметры материала диска
float mat2_dif[]={0.2f,0.4f,0.8f};
float mat2_amb[]= {0.3f,0.3f,0.3f};
float mat2_spec[]={0.6f,0.6f,0.6f};
float mat2_shininess=0.9f*128;

// Инициализируем параметры материалов и источника света
 
void init (void)
{
 
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };  //Интенсивность диффузного света
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //Интенсивность фонового света
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Интенсивность зеркального света
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 }; //Положение источника света (x,y,z,w)

   // устанавливаем параметры источника света 
   glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);

   // включаем освещение и источник света 
   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);

   // включаем z-буфер 
   glEnable(GL_DEPTH_TEST);

}

/* Функция вызывается при необходимости перерисовки изображения. В ней осуществляется
  весь вывод геометрии.*/
void display (void)
{
   // очищаем буфер кадра и буфер глубины 
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //фон

   glPushMatrix ();
   glRotatef (20.0, 1.0, 0.0, 0.0); //то есть поворот на 20 градусов вокруг оси x



   //отображаем диск   
   GLUquadricObj *qobj; 
   qobj=gluNewQuadric();
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat2_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat2_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat2_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat2_shininess);

   glPushMatrix ();
   glTranslatef (-0.1, -0.1, 0.0);  //перенос (x,y,z)    
   glRotatef (270.0, 1.0, 0.0, 0.0); // поворот на 270 вокруг  оси x
   if(flag1==0)
      {
     gluQuadricDrawStyle(qobj,GLU_LINE);
     gluDisk (qobj,0.1, 1.9, 50, 50);
      }
     else
     {
      gluDisk (qobj,0.1, 1.5, 50, 50);
      }
      glPopMatrix ();



   // отображаем шар 
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat1_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat1_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat1_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat1_shininess);

     glPushMatrix ();
     glTranslatef (-0.1, -0.1, 0.0);  //перенос (x,y,z)    
	 glRotatef (270.0, 1.0, 0.0, 0.0); // поворот на 270 вокруг  оси x
       if(flag1==0)
      {
      glutSolidSphere (1.5, 50, 50);
      }
     else
     {
     glutWireSphere (1.5, 50, 50);
      }
      glPopMatrix ();


      glPopMatrix ();

   /* выводим сцену на экран */
   glFlush ();
}

// Вызывается при изменении пользователем размеров окна  
 
void reshape(int w, int h)
{
  // устанавливаем размер области вывода равным размеру окна
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  // задаем матрицу проекции с учетом размеров окна 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  gluPerspective(
    40.0, /* угол зрения в градусах */
    (GLfloat)w/h, /* коэффициент сжатия окна */
    1,100.0);  /* расстояние до плоскостей отсечения */
  glMatrixMode (GL_MODELVIEW);

  glLoadIdentity ();
  gluLookAt(
   0.0f,0.0f,8.0f, /* положение камеры */
   0.0f,0.0f,0.0f, /* центр сцены */
   0.0f,1.0f,0.0f); /* положительное направление оси y */
}

/* Вызывается при нажатии клавиши на клавиатуре */
void keyboard(unsigned char key, int x, int y)
{
  if ( key == 27  )		
    exit ( 0 );
      if ( key == 'C' || key == 'c' )	//Изменение фигуры	
flag1=1;
        
      if ( key == 'V' || key == 'v' )
flag1=0;
       
   		 
         
 //   glutPostRedisplay();
display();       	  
  
}

/* Главный цикл приложения.
  Создается окно, устанавливается режим
  экрана с буфером глубины */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
                      | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutCreateWindow (argv[0]);
   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc (display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
