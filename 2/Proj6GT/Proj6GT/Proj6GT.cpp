
// 1) �������� ��������� �� "�������", � � ��������������
// ���������� glaux.
// 2) ������������� ������� � �������� ���� � �� ����.
//	���������� ���� ����������: opengl32.dll, glu32.dll, glut32.dll, glaux.dll
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")


#include	<windows.h>
#include	<gl/glut.h>
#include	<gl/glaux.h>
#include	<stdio.h>

                     //����������� � ������ ����� ��� ��������.
unsigned	      fontextureId    =-1; 
AUX_RGBImageRec * fonTex = NULL;  //������� ���������� glaux ��� � �������� ��������

                     

void init ()
{
								
								//��������� �������� ��� ����
	
	fonTex = auxDIBImageLoad (L"058.bmp" );

	glGenTextures   ( 1, &fontextureId );
	glBindTexture   ( GL_TEXTURE_2D, fontextureId );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment

	glTexImage2D  ( GL_TEXTURE_2D, 0, 3, fonTex -> sizeX, 
                    fonTex -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    fonTex -> data );

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */

	     
	delete[] fonTex; // ����������� ������, � ������� ��������� ��������



	glEnable     ( GL_DEPTH_TEST );

}


void display ()
{
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



	// ������ ���
	glMatrixMode(GL_MODELVIEW); // ��������-������� �������
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); //  ������� ��������
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	// ������������� ������ OpenGL
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */


	glBindTexture(GL_TEXTURE_2D,fontextureId);

	// ������ �������������
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex2d(-1,-1);
	glTexCoord2d(1,0);
	glVertex2d(1,-1);
	glTexCoord2d(1,1);
	glVertex2d(1,1);
	glTexCoord2d(0,1);
	glVertex2d(-1,1);
	glEnd();
	glDisable(GL_TEXTURE_2D);



    glMatrixMode   ( GL_PROJECTION ); //  ������� ��������
    glLoadIdentity ();
    glFrustum(-0.8, 0.8, -0.8, 0.8, 3.0, 80.0); 

	glEnable(GL_TEXTURE_2D);

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */


   glBindTexture   ( GL_TEXTURE_2D, fontextureId );

	glutSwapBuffers ();
}



                      // ����������� ����
void reshape ( int w, int h ) 
{
   glViewport     ( 0, 0, (GLsizei)w, (GLsizei)h );

   glMatrixMode   ( GL_PROJECTION );
   glLoadIdentity ();
    glFrustum(-0.8, 0.8, -0.8, 0.8, 3.0, 80.0); 
}

                       // ���������� "esc", "q", "Q".
void key ( unsigned char key, int x, int y )
{
  if ( key == 27 || key == 'q' || key == 'Q' )		//quit requested
    exit ( 0 );
}

                                 // �������
int main ( int argc, char ** argv )
{
								//initialise glut
	glutInit            ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );   
	glutInitWindowSize  ( 400, 400 );

								// create window
    glutCreateWindow ( "������ 6 - ��������. �����" );

								// register handlers
	glutDisplayFunc  ( display );
	glutReshapeFunc  ( reshape );
    glutKeyboardFunc ( key );
	init();
	glutMainLoop ();

	return 0;
}
