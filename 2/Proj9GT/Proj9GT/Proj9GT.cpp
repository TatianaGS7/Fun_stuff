
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment (lib, "glaux.lib")

#include	<windows.h>
#include	<gl/glut.h>
#include	<gl/glaux.h>
#include	<stdio.h>

float delta=0.3;
float delta1=1.0;
float delta2=2.0;
GLUquadricObj *p1;
GLUquadricObj *p2;
GLUquadricObj *p3;



                     //Захватываем и чистим место под текстуру.
unsigned	      textureId    =-1; 
AUX_RGBImageRec * localTexture = NULL;

unsigned	      fontextureId    =-1; 
AUX_RGBImageRec * fonTex = NULL;  

unsigned	      fontextureId0    =-1; 
AUX_RGBImageRec * fonTex0 = NULL;  


                     

void init ()
{
	glClearColor ( 0.5, 0.3, 0.6, 0.0 );

								// загружаем текстуру
	localTexture = auxDIBImageLoad ( "ty.bmp" ); //2 камушка
    
	glGenTextures   ( 1, &textureId );
	glBindTexture   ( GL_TEXTURE_2D, textureId );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment

	glTexImage2D  ( GL_TEXTURE_2D, 0, GL_RGB, localTexture -> sizeX, 
                    localTexture -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    localTexture -> data );  //

	delete[] localTexture; // Освобождаем память, в которой хранилась текстура
    	   
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */

    p1=gluNewQuadric();
    gluQuadricTexture(p1, GL_TRUE);//GL_FALSE


		fonTex0 = auxDIBImageLoad ( "fd.bmp" ); //кольцо
    
	glGenTextures   ( 1, &fontextureId0 );
	glBindTexture   ( GL_TEXTURE_2D, fontextureId0 );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment

	glTexImage2D  ( GL_TEXTURE_2D, 0, GL_RGB, fonTex0 -> sizeX, 
                    fonTex0 -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    fonTex0 -> data );  //

	delete[] fonTex0; // Освобождаем память, в которой хранилась текстура
    	   
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */
    p3=gluNewQuadric();
    gluQuadricTexture(p3, GL_TRUE);//GL_FALSE



    fonTex = auxDIBImageLoad ( "s22-1.bmp" );//большой камень
    
	glGenTextures   ( 1, &fontextureId );
	glBindTexture   ( GL_TEXTURE_2D, fontextureId );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment

	glTexImage2D  ( GL_TEXTURE_2D, 0, GL_RGB, fonTex -> sizeX, 
                    fonTex -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    fonTex -> data );  //

	delete[] fonTex; // Освобождаем память, в которой хранилась текстура
    	   
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */


	glEnable     ( GL_DEPTH_TEST );
	glEnable     ( GL_TEXTURE_2D );

   p2=gluNewQuadric();
   gluQuadricTexture(p2, GL_TRUE);//GL_FALSE



//gluQuadricDrawStyle(p,GLU_FILL);
//gluQuadricDrawStyle(p1,GLU_LINE);// сеточка


}


void display ()
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
    glMatrixMode   ( GL_PROJECTION );
    glLoadIdentity ();
    glFrustum(-0.6, 0.6, -0.6, 0.6, 2.0, 120.0); 

    glMatrixMode   ( GL_MODELVIEW );
    glLoadIdentity ();
	

    gluLookAt(
   0.0f,0.0f,8.0f, /* положение камеры */
   0.0f,0.0f,0.0f, /* центр сцены */
   0.0f,1.0f,0.0f); /* положительное направление оси y */

	glTranslatef ( 0, 0, -3);   	
	glRotatef    ( delta, 1, 0, 0 ); 
	glRotatef    ( delta1, 0, 1, 0 );
	glRotatef    ( delta2, 0, 0, 1 );



    /*Видовая трансформация(камера)
   gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

   //Модельная трансформация
   glScalef(1.0,2.0,1.0);
   glutWireCube(1.0);*/ //!!!!!!!!!!!!!!!

  glBindTexture   ( GL_TEXTURE_2D, fontextureId0 ); // "привязываем текстуру"
  glutSolidTorus (0.18, 1.8, 50, 50);  
  glBindTexture   ( GL_TEXTURE_2D, fontextureId );
  glTranslatef ( 2, 1, 0); 
  gluSphere(p2,0.6,5,5);
  glBindTexture   ( GL_TEXTURE_2D, textureId );
  glTranslatef ( -0.53, 0.53, 0);
  gluSphere(p1,0.36,10,30);
  glTranslatef ( 0.6, -1.3, 0);
  gluSphere(p1,0.36,10,30);
  

	glutSwapBuffers ();
	
}


void	idle ()
{
       // ...
       // Здесь анимация.
    delta=0.2+delta;
    delta1=delta1+0.3;
    delta2=delta2;
       
   display ();     
}

                      // Перерисовка окна
void reshape ( int w, int h ) 
{
   glViewport     ( 0, 0, (GLsizei)w, (GLsizei)h );

 
}

                       // Обработчик "esc", "q", "Q".
void key ( unsigned char key, int x, int y )
{
  if ( key == 27 || key == 'q' || key == 'Q' )		//quit requested
    exit ( 0 );
}

                                 // главная
int main ( int argc, char ** argv )
{
								//initialise glut
	glutInit            ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );   
	glutInitWindowSize  ( 600, 600 );

								// create window
    glutCreateWindow ( "Текстура на 3d объект" );

								// register handlers
	glutDisplayFunc  ( display );
	glutReshapeFunc  ( reshape );
    glutKeyboardFunc ( key );
	glutIdleFunc     ( idle);
	init();
	glutMainLoop ();

	return 0;
}
 

