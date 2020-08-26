// кнопки мышки


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




// параметры материала додекаэдра
/* освещение может быть разделено на 4 компонента: фоновое (ambient), диффузное (diffuse), зеркальное (specular) и исходящее (эмиссионное – emissive). 
Все 4 компонента рассчитываются независимо и только затем суммируются.*/

float mat1_dif[]={0.7f,0.9f,0.2f}; //Интенсивность диффузного света (значение по умолчанию для 0-го источника - белый свет, для остальных - черный)
float mat1_amb[]= {0.5f,0.5f,0.5f}; //Интенсивность фонового света
float mat1_spec[]={0.5f,0.5f,0.5f}; // Интенсивность зеркального света
float mat1_shininess=0.2f*128; //кол-во света

// параметры икосаэдра 
float mat3_dif[]={0.7f,0.1f,0.9f};
float mat3_amb[]= {0.3f,0.3f,0.3f};
float mat3_spec[]={0.6f,0.6f,0.6f};
float mat3_shininess=0.9f*128;

// Инициализируем параметры материалов и источника света
 
void init (void)
{
 
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };  //Интенсивность диффузного света
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //Интенсивность фонового света
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Интенсивность зеркального света
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.2 }; //Положение источника света (x,y,z,w)

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
  //glTranslatef (-0.1, -0.1, 0.0);  //перенос (x,y,z)

      // отображаем икосаэдр 
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat3_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat3_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat3_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat3_shininess);

     glPushMatrix ();         
	 glRotatef (270, 0.0, 1.0, 0.0); // поворот на 270 вокруг  оси y 
	 glTranslatef (-0.1, -0.1, 1.0);			   
       if(flag1==1)
      { glutSolidIcosahedron ();        
      }
          glPopMatrix ();




   // отображаем додекаэдр 
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat1_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat1_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat1_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat1_shininess);

     glPushMatrix ();
   	 glRotatef (100, 0.0, 1.0, 0.0); 
	 glTranslatef (-0.1, -0.1, 0.0);	
		   
       if(flag1==0)
      { glutSolidDodecahedron ();	         
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

/* Обрабатывает сообщения от мыши */

void mouse(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN ) 
  {
    switch( button ) 
	{
      case GLUT_LEFT_BUTTON:
flag1=1;

        break;
      case GLUT_RIGHT_BUTTON:
flag1=0;
        break;
    }
display();
//   glutPostRedisplay();
  }
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
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
