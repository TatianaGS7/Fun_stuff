
// 1) Текстуру .tga загружаем  "вручную", а .bmp  -  с использованием
// библиотеки glaux.
// 2) Использование текстур в качестве фона и на кубе.
//	Подключаем библиотеки: opengl32.dll, glu32.dll, glut32.dll, glaux.dll
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")


#include	<windows.h>
#include	<gl/glut.h>
#include	<gl/glaux.h>
#include	<stdio.h>


float delta=3.0;

                     //Захватываем и чистим место под текстуры.
unsigned	      fontextureId    =-1; 
AUX_RGBImageRec * fonTex = NULL;
unsigned	      textureId    =-1; 
AUX_RGBImageRec * Tex = NULL;


typedef struct									// Create A Structure
{
	GLubyte	*imageData;							// Image Data (Up To 32 Bits)
	GLuint	bpp;								// Image Color Depth In Bits Per Pixel.
	GLuint	width;								// Image Width
	GLuint	height;								// Image Height
	GLuint	texID;								// Texture ID Used To Select A Texture
} TextureImage;	

TextureImage textura;							// Storage For Texture (Storage For 10 Textures)
TextureImage textura1;



bool LoadTGA(TextureImage *texture, char *filename)				// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		// Uncompressed TGA Header
	GLubyte		TGAcompare[12];						// Used To Compare TGA Header
	GLubyte		header[6];						// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;						// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;						// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;							// Temporary Variable
	GLuint		type=GL_RGBA;						// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");					// Open The TGA File

	if(	file==NULL ||							// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0 ||		// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))		// If So Read Next 6 Header Bytes
	{
		if (file == NULL)						// Does The File Even Exist? *Added Jim Strong*
			return FALSE;						// Return False
		else								// Otherwise
		{
			fclose(file);						// If Anything Failed, Close The File
			return FALSE;						// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];				// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];				// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0 ||						// Is The Width Less Than Or Equal To Zero
		texture->height	<=0 ||						// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))				// Is The TGA 24 or 32 Bit?
	{
		fclose(file);							// If Anything Failed, Close The File
		return FALSE;							// Return False
	}

	texture->bpp	= header[4];						// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;					// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);			// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||					// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)					// Was Image Data Loaded
			free(texture->imageData);				// If So, Release The Image Data

		fclose(file);							// Close The File
		return FALSE;							// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)			// Loop Through The Image Data
	{									// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];					// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];		// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;				// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);								// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);				// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)							// Was The TGA 24 Bits
	{
		type=GL_RGB;							// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;								// Texture Building Went Ok, Return True
}


void    drawBox ( GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2 )
{
        glBegin ( GL_POLYGON );         // front face
          glNormal3f   ( 0.0, 0.0, 1.0 );

		  glTexCoord2f ( 0, 0 );
          glVertex3f   ( x1, y1, z2 );

		  glTexCoord2f ( 1, 0 );
          glVertex3f   ( x2, y1, z2 );

		  glTexCoord2f ( 1, 1 );
          glVertex3f   ( x2, y2, z2 );

		  glTexCoord2f ( 0, 1 );
          glVertex3f   ( x1, y2, z2 );
        glEnd ();

        

        glBegin ( GL_POLYGON );         // left face
          glNormal3f ( -1.0, 0.0, 0.0 );

		  glTexCoord2f ( 0, 0 );
          glVertex3f   ( x1, y1, z1 );

		  glTexCoord2f ( 1, 0 );
          glVertex3f   ( x1, y1, z2 );

		  glTexCoord2f ( 1, 1 );
          glVertex3f   ( x1, y2, z2 );

		  glTexCoord2f ( 0, 1 );
          glVertex3f   ( x1, y2, z1 );
        glEnd ();

        
        
}

void    drawBox2 ( GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2 )
{
        glBindTexture   ( GL_TEXTURE_2D, textura.texID );
		glBegin ( GL_POLYGON );         // front face
          glNormal3f   ( 0.0, 0.0, 1.0 );

		  glTexCoord2f ( 0, 0 );
          glVertex3f   ( x1, y1, z2 );

		  glTexCoord2f ( 1, 0 );
          glVertex3f   ( x2, y1, z2 );

		  glTexCoord2f ( 1, 1 );
          glVertex3f   ( x2, y2, z2 );

		  glTexCoord2f ( 0, 1 );
          glVertex3f   ( x1, y2, z2 );
        glEnd ();

		

		glBindTexture   ( GL_TEXTURE_2D, textura1.texID );
        glBegin ( GL_POLYGON );         // left face
          glNormal3f ( -1.0, 0.0, 0.0 );

		  glTexCoord2f ( 0, 0 );
          glVertex3f   ( x1, y1, z1 );

		  glTexCoord2f ( 1, 0 );
          glVertex3f   ( x1, y1, z2 );

		  glTexCoord2f ( 1, 1 );
          glVertex3f   ( x1, y2, z2 );

		  glTexCoord2f ( 0, 1 );
          glVertex3f   ( x1, y2, z1 );
        glEnd ();

		

}

void init ()
{
	LoadTGA(&textura,"1.tga");
	LoadTGA(&textura1,"2.tga");
	
	
	fonTex = auxDIBImageLoad ( L"0.bmp" );

	glGenTextures   ( 1, &fontextureId );
	glBindTexture   ( GL_TEXTURE_2D, fontextureId );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			

	glTexImage2D  ( GL_TEXTURE_2D, 0, 3, fonTex -> sizeX, 
                    fonTex -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    fonTex -> data );

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */

	     
	delete[] fonTex; // Освобождаем память, в которой хранилась текстура

	Tex = auxDIBImageLoad ( L"1.bmp" );

	glGenTextures   ( 1, &textureId );
	glBindTexture   ( GL_TEXTURE_2D, textureId );

	glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei   ( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment

	glTexImage2D  ( GL_TEXTURE_2D, 0, 3, Tex -> sizeX, 
                    Tex -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    Tex -> data );

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */

	     
	delete[] Tex; // Освобождаем память, в которой хранилась текстура

	glEnable     ( GL_DEPTH_TEST );
}


void display ()
{


glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearDepth(1.0f);							// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);							// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);						// Enable Depth Testing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
	glEnable(GL_BLEND);							// Enable Blending       (disable alpha testing)
	//glAlphaFunc(GL_GREATER,0.1f);						// Set Alpha Testing     (disable blending)
	//glEnable(GL_ALPHA_TEST);						// Enable Alpha Testing  (disable blending)
	glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping
	glEnable(GL_CULL_FACE);							// Remove Back Face


	// Рисуем фон
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	// Устанавливаем режимы OpenGL
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* Это все     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* по умолчанию   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* Но без этого не работает   */


	glBindTexture(GL_TEXTURE_2D,fontextureId);

	// Рисуем прямоугольльник
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

    glMatrixMode   ( GL_MODELVIEW );
    glLoadIdentity ();
	glTranslatef ( 0, 0, -4); 
	glRotatef    ( delta, 0, 1, 0 ); 


    glMatrixMode   ( GL_PROJECTION );
    glLoadIdentity ();
    glFrustum(-0.8, 0.8, -0.8, 0.8, 3.0, 80.0); 

	glEnable(GL_TEXTURE_2D);

	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );       // set texture to repeat mode 
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     // Это все     
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // по умолчанию   	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); // Но без этого не работает   

	glEnable(GL_BLEND);

	
	glBindTexture   ( GL_TEXTURE_2D, textureId );

drawBox ( -0.5, 0.5, -0.5, 0.5, -0.5, 0.5 );

drawBox2 ( -0.55, 0.55, -0.55, 0.55, -0.55, 0.55 );

  	glutSwapBuffers ();
}


void	idle ()
{
    delta=delta+0.9; 
 
  display ();      
}

                      // Перерисовка окна
void reshape ( int w, int h ) 
{
   glViewport     ( 0, 0, (GLsizei)w, (GLsizei)h );

   glMatrixMode   ( GL_PROJECTION );
   glLoadIdentity ();
    glFrustum(-0.8, 0.8, -0.8, 0.8, 3.0, 80.0); 
}

                      
void key ( unsigned char key, int x, int y )
{
  if ( key == 27 || key == 'q' || key == 'Q' )		//quit requested
    exit ( 0 );
}

                                 // главная
int main ( int argc, char ** argv )
{
								
	glutInit            ( &argc, argv );//initialise glut
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );   
	glutInitWindowSize  ( 400, 400 );

								
    glutCreateWindow ( "bmp с исп. glaux, .tga - вручную" );// create window

							
	glutDisplayFunc  ( display );
	glutReshapeFunc  ( reshape );
    glutKeyboardFunc ( key );
	glutIdleFunc     ( idle);

	init();
	glutMainLoop ();

	return 0;
}
