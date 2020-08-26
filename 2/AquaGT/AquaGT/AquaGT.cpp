/* ���������� �� ������������: ����� ������� �� ���� "�����", ������� ����������� ������ ����, 
����� ���������� �������� ������, ������� ������, ����� ��������� ����, ������� ������� "O" � ����. ���������*/
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include	<gl/glaux.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <al/alut.h>
#include <conio.h>
#include"Mod.h"
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib") 
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
//#pragma comment(lib, "OpenAL32.lib")
//#pragma comment(lib, "alut.lib") 

int rotat=1; //�������� �� ��������� ������
float t1=0; // ��������� ���������� �����  (�������)
float xs1[6]={26,16,10,10,16,10};
float ys1[6]={46,33,22,12,19,6};
float xn1[6]={26,36,28,25,36,47};
float yn1[6]={46,32,16,1,20,2};
int tt1=1;
float x11[6],y11[6]; //�������
float sp1=0;
int flag1=0;//����

//�����
ALuint bufferFon;                            // buffer for sound data
ALuint sourceFon;                            // source of sound
ALfloat  sourcePosFon[] = { 0, 0, 0 };  //2          // source position
ALfloat  sourceVelFon[] = { 0, 0, 0 };          // source velocity (used for Doppler effect)
ALuint buffer;                            // buffer for sound data
ALuint source;                            // source of sound
ALfloat  sourcePos[] = { 0, 0, 0 };  //2          // source position
ALfloat  sourceVel[] = { 0, 0, 0 };          // source velocity (used for Doppler effect)
ALfloat  listenerPos[] = { 0, 0, 0 };        // listeners position
ALfloat  listenerVel[] = { 0, 0, 0 };        // listern's velocity
float 		listenerOri [] = { 0, 0, -1,  0, 1, 0 }; 


float delta=0.0;
int zastavka=1;
float s=0.0;
float s1=0.1;



GLUquadricObj* Quadric ;
GLUquadricObj* Q;
AUX_RGBImageRec* image;
unsigned	      texture1Id    =-1; 
unsigned	      texture2Id    =-1; 
unsigned	      texture3Id    =-1; 
unsigned	      texture4Id    =-1; 
unsigned	      texture5Id    =-1; 
unsigned	      texture6Id    =-1; 
unsigned	      texture7Id    =-1; 
unsigned	      texture8Id    =-1; 
unsigned	      texture9Id    =-1; 
unsigned	      texture11Id    =-1; 
unsigned	      texture12Id    =-1; 
unsigned	      texture13Id    =-1; 



float mat1_dif[]={0.7f,0.9f,0.2f}; //������������� ���������� ����� (�������� �� ��������� ��� 0-�� ��������� - ����� ����, ��� ��������� - ������)
float mat1_amb[]= {0.5f,0.5f,0.5f}; //������������� �������� �����
float mat1_spec[]={0.5f,0.5f,0.5f}; // ������������� ����������� �����
float mat1_shininess=0.2f*128; //���-�� �����




GLint koefSizeFont=1; 
unsigned	      fontextureId    =-1; 
AUX_RGBImageRec * fonTex = NULL;

unsigned	      fon1textureId    =-1; 
AUX_RGBImageRec * fon1Tex = NULL;



typedef struct									// Create A Structure
{
	GLubyte	*imageData;							// Image Data (Up To 32 Bits)
	GLuint	bpp;								// Image Color Depth In Bits Per Pixel.
	GLuint	width;								// Image Width
	GLuint	height;								// Image Height
	GLuint	texID;								// Texture ID Used To Select A Texture
} TextureImage;	

TextureImage texturaAlphaFont;							// Storage For Texture (Storage For 10 Textures)

TextureImage textura;							// Storage For Texture (Storage For 10 Textures)
TextureImage textura2;



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




GLuint	base;				// �������� ������ ����������� ��� ������
GLuint	loop;				// ����� ���������� ��� ������


//�����
GLvoid BuildFontBMP(GLvoid)								// ������� ������ ����������� ������ ������
{
	float	cx;											// �������� X ���������� �������
	float	cy;											// �������� Y ���������� �������

	base=glGenLists(256);								// ������� ������
	//glBindTexture(GL_TEXTURE_2D, fonttextureId);			// �������� �������� ������
	glBindTexture   ( GL_TEXTURE_2D, texturaAlphaFont.texID );

	for (loop=0; loop<256; loop++)						// ���� �� ���� 256 �������
	{
		cx=float(loop%16)/16.0f;						// X ���������� �������� ������� 
		cy=float(loop/16)/16.0f;						// Y ���������� �������� ������� 

		glNewList(base+loop,GL_COMPILE);				// �������� ������ ������
			glBegin(GL_QUADS);							// ���������� ���������������, ��� ������� �������
				glTexCoord2f(cx,1-cy-0.0625f);			// ����� � �������� (����� ������)
				glVertex2i(0,0);						// ���������� ������� (����� ������)
				glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// ����� �� �������� (������ ������)
				glVertex2i(10,0);						// ���������� ������� (������ ������)
				glTexCoord2f(cx+0.0625f,1-cy);			// ����� �������� (������� ������)
				glVertex2i(10,10);						// ���������� ������� (������� ������)
				glTexCoord2f(cx,1-cy);					// ����� �������� (������� �����)
				glVertex2i(0,10);						// ���������� ������� (������� �����)
			glEnd();									// ����� ���������� ���������������� (�������)
			glTranslated(12,0,0);						// �������� ������ �� �������
		glEndList();									// ����������� ��������� ������ �����������
	}													// ���� ��� �������� ���� 256 ��������
}

GLvoid BuildFont(GLvoid)								// ������� ������ ����������� ������ ������
{
	float	cx;											// �������� X ���������� �������
	float	cy;											// �������� Y ���������� �������

	base=glGenLists(256);								// ������� ������
	//glBindTexture(GL_TEXTURE_2D, fonttextureId);			// �������� �������� ������
	glBindTexture   ( GL_TEXTURE_2D, texturaAlphaFont.texID );

	for (loop=0; loop<256; loop++)						// ���� �� ���� 256 �������
	{
		cx=float(loop%16)/16.0f;						// X ���������� �������� ������� 
		cy=float(loop/16)/16.0f;						// Y ���������� �������� ������� 

		glNewList(base+loop,GL_COMPILE);				// �������� ������ ������
			glBegin(GL_QUADS);							// ���������� ���������������, ��� ������� �������
				glTexCoord2f(cx,1-cy-0.0625f);			// ����� � �������� (����� ������)
				glVertex2i(0,0);						// ���������� ������� (����� ������)
				glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// ����� �� �������� (������ ������)
				glVertex2i(10,0);						// ���������� ������� (������ ������)
				glTexCoord2f(cx+0.0625f,1-cy);			// ����� �������� (������� ������)
				glVertex2i(10,10);						// ���������� ������� (������� ������)
				glTexCoord2f(cx,1-cy);					// ����� �������� (������� �����)
				glVertex2i(0,10);						// ���������� ������� (������� �����)
			glEnd();									// ����� ���������� ���������������� (�������)
			glTranslated(0,0,0);						// �������� ������ �� �������
		glEndList();									// ����������� ��������� ������ �����������
	}													// ���� ��� �������� ���� 256 ��������
}

GLvoid KillFont(GLvoid)									// ������� ����� �� ������
{
	glDeleteLists(base,256);							// ������� ��� 256 ������� �����������
}
GLvoid glPrint(GLint x, GLint y, char *string, int set)	// ��� ��������
{
	if (set>1)
	{
		set=1;
	}
	glBindTexture(GL_TEXTURE_2D, texturaAlphaFont.texID); // �������� ���� �������� ������
	glDisable(GL_DEPTH_TEST);							// ������ �������� �������
	glMatrixMode(GL_PROJECTION);						// �������� ������� ��������������
	glPushMatrix();										// ��������� ������� ��������������
	glLoadIdentity();									// ���������� ������� ��������
	glOrtho(0,800,0,500,-1,1);							// ������������� Ortho �����
	glMatrixMode(GL_MODELVIEW);							// �������� ������� ������ ���������
	glPushMatrix();										// ��������� ������� ������ ���������
	glLoadIdentity();									// ���������� ������� ������ ���������
	glTranslated(x,y,0);								// ������� ������ (0,0 - ������ �����)
    glScalef(koefSizeFont,koefSizeFont,0);//
	glListBase(base);//
//	glListBase(base+128*set); //-32()						// �������� ����� �������� (0 ��� 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);			// ������ ����� �� ������
	glMatrixMode(GL_PROJECTION);						// �������� ������� ��������������
	glPopMatrix();										// ��������������� ������ ������� �������������� 
	glMatrixMode(GL_MODELVIEW);							// �������� ������� ��������� ������
	glPopMatrix();										// ��������������� ������ ������� ��������������
	glEnable(GL_DEPTH_TEST);							// ��������� ���� �������
}

GLvoid glPrintBMP(GLint x, GLint y, char *string, int set)	// ��� ��������
{
	if (set>1)
	{
		set=1;
	}
	glBindTexture(GL_TEXTURE_2D, fontextureId);			// �������� ���� �������� ������
	glDisable(GL_DEPTH_TEST);							// ������ �������� �������
	glMatrixMode(GL_PROJECTION);						// �������� ������� ��������������
	glPushMatrix();										// ��������� ������� ��������������
	glLoadIdentity();									// ���������� ������� ��������
	glOrtho(0,900,0,500,-1,1);							// ������������� Ortho �����
	glMatrixMode(GL_MODELVIEW);							// �������� ������� ������ ���������
	glPushMatrix();										// ��������� ������� ������ ���������
	glLoadIdentity();									// ���������� ������� ������ ���������
	glTranslated(x,y,0);								// ������� ������ (0,0 - ������ �����)
    glScalef(koefSizeFont,koefSizeFont,0);//
	glListBase(base);//
//	glListBase(base+128*set); //-32()						// �������� ����� �������� (0 ��� 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);			// ������ ����� �� ������
	glMatrixMode(GL_PROJECTION);						// �������� ������� ��������������
	glPopMatrix();										// ��������������� ������ ������� �������������� 
	glMatrixMode(GL_MODELVIEW);							// �������� ������� ��������� ������
	glPopMatrix();										// ��������������� ������ ������� ��������������
	glEnable(GL_DEPTH_TEST);							// ��������� ���� �������
}


//����� ��������
#pragma pack(1)

struct BMPHeader {
	short type;           // File type = 0x4D42
	int size;	 	
	short reserved1;
	short reserved2;
	int offset;           // Offset from file start to bitmap data
};

struct BMPInfoHeader {
	int size;             // Size of this structure in bytes
	int width;
	int height;
	short planes;         // Should be equal to 1
	short bitsPerPixel;
	unsigned compression; // Compression flags ( 0 - no compression )
	unsigned imageSize;   // Size of image in bytes
	int xPelsPerMeter;		
	int yPelsPerMeter;	
	int clrUsed;
	int clrImportant;
};

struct BMPPaletteItem {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char unused;
};



     //   ������.    (��� ������� ��� �������� .bmp - �����.)  

unsigned char *LoadIndexedBMPFile(const char *path,int *width,int *height)
{
	unsigned char *result = NULL;
    FILE *in = fopen(path,"rb");
	if(!in)
		return NULL;
    BMPHeader hdr;
    fread(&hdr,sizeof(hdr),1,in);
    if(hdr.type != 0x4D42)           // Not a bitmap file at all
		return NULL;
	BMPInfoHeader	infoHdr;
	fread(&infoHdr,sizeof(infoHdr),1,in);
	if(infoHdr.bitsPerPixel != 8)
		return NULL;
	if(infoHdr.compression)
		return NULL;
	if((result = new unsigned char[infoHdr.width*infoHdr.height*3]) == NULL)
		return NULL;
	BMPPaletteItem palette[256];
	fread(palette,256,sizeof(BMPPaletteItem),in);
    fseek(in,hdr.offset-sizeof(hdr)-sizeof(infoHdr)-1024,SEEK_CUR);   
	unsigned char *dst = result;
	for(int y=0;y<infoHdr.height;y++) {
		for(int x=0;x<infoHdr.width;x++) {
			int idx = (unsigned char)fgetc(in);
			*dst++ = palette[idx].red;
			*dst++ = palette[idx].green;
			*dst++ = palette[idx].blue;
		}
        for(int x=0;x<((4-(infoHdr.width&3))&3);x++)  // Skip alignment bytes
           fgetc(in);
    }
    fclose(in);
	*width = infoHdr.width;
	*height = infoHdr.height;
	return result;
}

unsigned char *LoadTrueColorBMPFile(const char *path,int *width,int *height)
{
	unsigned char *result = NULL;
    FILE *in = fopen(path,"rb");
	if(!in)
		return NULL;
    BMPHeader hdr;
    fread(&hdr,sizeof(hdr),1,in);
    if(hdr.type != 0x4D42)           // Not a bitmap file at all
		return NULL;
	BMPInfoHeader	infoHdr;
	fread(&infoHdr,sizeof(infoHdr),1,in);
	if(infoHdr.bitsPerPixel != 24)   // Not a truecolor bitmap
		return NULL;
	if(infoHdr.compression)          // Compressed bitmap
		return NULL;
	if((result = new unsigned char[infoHdr.width*infoHdr.height*3]) == NULL)
		return NULL;
    fseek(in,hdr.offset-sizeof(hdr)-sizeof(infoHdr),SEEK_CUR);   
	unsigned char *dst = result;
	for(int y=0;y<infoHdr.height;y++) {
		for(int x=0;x<infoHdr.width;x++) {
			dst[2] = fgetc(in);
			dst[1] = fgetc(in);
			dst[0] = fgetc(in);
			dst += 3;
		}
        for(int x=0;x<((4-(infoHdr.width&3))&3);x++)  // Skip alignment bytes
           fgetc(in);
    }
    fclose(in);
	*width = infoHdr.width;
	*height = infoHdr.height;
	return result;
}                  
      //   �����.    (��� ������� ��� �������� .bmp - �����.) 


 // ������ ������ � OpenGL.
double x_angle = 0;
double y_angle = 0;
 RGBpixmap pix[2];  //������� ��� ������ ���������� �����
int tex_width;
int tex_height;
unsigned char *tex_bits = NULL;  // ����������� � ������ ����� ��� ��������.
GLuint texture = 0;
GLuint texMod = 0;
struct Vertex {

	double x,y,z;
} v[8] = { 
	{ -3.5,-3.5,3.5 },  //0
	{ 3.5,-3.5,3.5 },  //1
	{ 3.5,3.5,3.5 },  //2
	{ -3.5,3.5,3.5 },  //3
	{ -3.5,-3.5,-3.5 },  //4 
	{ 3.5,-3.5,-3.5 },  //5
	{ 3.5,3.5,-3.5 },  //6
	{ -3.5,3.5,-3.5 }  //7
};
//����� �������� �����������

void Finalize() 
{
// ������� ������ (�������)
	alDeleteBuffers ( 1, &buffer );
    alDeleteSources ( 1, &source );
    alutExit  ();
}
// ���������� ��� ��������� ������������� �������� ����  
  // 1 �����
void reshape(int w, int h)
{
  // ������������� ������ ������� ������ = ������� ����
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  // ������ ������� �������� � ������ �������� ���� 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  gluPerspective(
    40.0, /* ���� ������ � �������� */
    (GLfloat)w/h, /* ����������� ������ ���� */
    1,100.0);  /* ���������� �� ���������� ��������� */
  glMatrixMode (GL_MODELVIEW);

  glLoadIdentity ();
  gluLookAt(
 0.0f,0.0f,8.0f, /* ��������� ������ */
   0.0f,0.0f,0.0f, /* ����� ����� */
   0.0f,1.0f,0.0f); /* ������������� ����������� ��� y */
}

void display (void)
{
   /* ������� ����� ����� � ����� ������� */
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearDepth(1.0f);							// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);							// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);						// Enable Depth Testing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
	glEnable(GL_BLEND);							// Enable Blending       (disable alpha testing)
	//glAlphaFunc(GL_GREATER,0.1f);						// Set Alpha Testing     (disable blending)
	//glEnable(GL_ALPHA_TEST);						// Enable Alpha Testing  (disable blending)
	glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping
	glEnable(GL_CULL_FACE);		
	// Remove Back Face


	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); 

if (zastavka==-1){	 //��������, ���� �������� �� �����, �� ���������� ��������
	
	// ������������� ������ OpenGL
  glMatrixMode (GL_PROJECTION);  
  glLoadIdentity ();
  gluPerspective(
    40.0, /* ���� ������ � �������� */
    (GLfloat)800/600, /* ����������� ������ ���� */
    1,100.0);  /* ���������� �� ���������� ��������� */
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt(
   0.0f,0.0f,8.0f, /* ��������� ������ */
   0.0f,0.0f,0.0f, /* ����� ����� */
   0.0f,1.0f,0.0f); /* ������������� ����������� ��� y */

    glBindTexture   ( GL_TEXTURE_2D, texture1Id );
    glPushMatrix ();
	glTranslatef (0.0, -0.5, 0.0);
	if(rotat>0)  glRotatef (delta, 0.0, 8.0, 0.0); //���� ���� �������� ��������, �� ������������� �������
    Quadric=gluNewQuadric();
    gluQuadricTexture(Quadric, GL_TRUE);
    gluQuadricDrawStyle(Quadric, GLU_FILL); 
    glBindTexture   ( GL_TEXTURE_2D, texture1Id );
    glPushMatrix();                           
    glTranslatef (0.0, 1.3, 0.0);
    glRotated(90,1,0,0);
    glPushMatrix ();

   // ������ - ��� ��������� ��������
   glFrontFace(GL_CW); 
   glDisable(GL_LIGHTING);
   glBindTexture   ( GL_TEXTURE_2D, texture7Id );
   glRotated(180,1,0,0);
   glTranslatef (0.0, 0, -12.0);
   glRotated(42,0,0,1);
   gluCylinder(Quadric,8,8,28,30,30);    //�������� ������ � ��������� ��������
   glEnable(GL_LIGHTING);
   glFrontFace(GL_CCW);


	glPopMatrix ();
	glTranslatef (0.0, 1.2, 0.5);
	glBindTexture   ( GL_TEXTURE_2D, texture12Id );
	glTranslatef (0.0, 0, 1.7);
	gluSphere(Quadric,1,30,30);    //������� ������ 
	glTranslatef (0.0, 0, -1.7);
   

   glBindTexture   ( GL_TEXTURE_2D, textura2.texID );
   for(int jj=1;jj<6;jj++) //������ 5 ������� �������
   {
	glPushMatrix(); ///��������� ������� ��������� �������������� 
	glTranslatef (-1.0, -1.2, -0.7);
	glRotated(jj*360/8,0,0,1);
	glTranslatef (0.09, 0, jj*0.01);
	glPushMatrix(); //��������������� ���������� ��������� ��������������

  for(int j=1;j<35;j++) //� ������ �������  34 ��������, � ������� ������� �� �����
  {
	glPushMatrix();
	glRotated(j*35,0,0,1);
	glTranslatef (t1/8, t1/8, -0.1-sp1+j*0.2);  //  sp1  - ��� ���������� ������� "�������" ������ �����
	if ((-sp1+j*0.2)>(0.6))gluSphere(Quadric,0.03,5,5);    //������ �������, ������ � ��� ������ ���� �� �� ������� ����������� ����
	glPopMatrix();}
	glPopMatrix();
	glPopMatrix();
	}



     //����� ������� ������� ������
	glBindTexture   ( GL_TEXTURE_2D, texture12Id );
	glPushMatrix();
	glTranslatef (0, -1.2, 1.5);
	glTranslatef (0.0, 0, -1.2);
	glPushMatrix();
	glScaled(0.5,1.5,0.12); 
	gluSphere(Quadric,1.15,9,9);   
	glPopMatrix(); 
	glPopMatrix();

    //��� ������� ����� �� �������
	glPushMatrix();
	glTranslatef (0, 0, 1.5);
	glTranslatef (0.0, 0, -0.8);
	glPushMatrix();
	glScaled(0.5,0.5,0.12); 
	gluSphere(Quadric,1.15,9,9);   
	glPopMatrix(); 
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.4,0.35,0.12);
	gluSphere(Quadric,0.9,9,9);  
	glPopMatrix();
	glPopMatrix();

    //������ ������
	glPushMatrix();
	glTranslatef (0, -2.5, 1.5);
	glTranslatef (0.0, 0, 0);
	glPushMatrix();
	glScaled(0.69,0.6,0.12); 
	gluSphere(Quadric,1.2,9,9);   
	glPopMatrix();    
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.72,0.4,0.12); 
	gluSphere(Quadric,1.2,9,9);   
	glPopMatrix();
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.69,0.3,0.12); 
	gluSphere(Quadric,1.1,9,9);   
	glPopMatrix();
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.63,0.35,0.12); 
	gluSphere(Quadric,1.15,9,9);  
	glPopMatrix();
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.64,0.3,0.12); 
	gluSphere(Quadric,1.15,9,9);   
	glPopMatrix();
	glTranslatef (0.0, 0, -0.2);
	glPushMatrix();
	glScaled(0.61,0.35,0.12);
	gluSphere(Quadric,0.9,9,9);  
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);


	glTranslatef (0.6, 0.5, 0.7);
	glRotated(90,1,0,0);
	for(int g=-10;g<5;g++)  //� ����� ������ ���������
	for(int gg=-10;gg<5;gg++)
	{
	glPushMatrix();
	glTranslatef (g*0.1, 0.4,gg*0.1);  //�� "�������" ���������� � ����������� ����� �������
	for (int i=0; i<=5; i++)  // �������
		{
		x11[i]=((1-t1)*xs1[i]+t1*xn1[i])/60;;
		y11[i]=((1-t1)*ys1[i]+t1*yn1[i])/100;;
		}
   //��������� ������ 2 ����
     glLineWidth(4);	 //1� ��� � �������� ����� 4
	glBegin(GL_LINES);
	glColor3ub(32, 250 ,170);
	glVertex2f(x11[0], y11[0]);	
	glVertex2f(x11[1], y11[1]);
	glVertex2f(x11[1], y11[1]);	
	glVertex2f(x11[2], y11[2]);
	glVertex2f(x11[2], y11[2]);
	glVertex2f(x11[3], y11[3]);
	glVertex2f(x11[1], y11[1]);	
	glVertex2f(x11[4], y11[4]);
	glVertex2f(x11[4], y11[4]);	
	glVertex2f(x11[5], y11[5]);
	glEnd();

    glLineWidth(2);	//2� ��� � �������� ����� 2
	glBegin(GL_LINES);
	glColor3ub(50, 205, 50);
	glVertex2f(x11[0], y11[0]);	
	glVertex2f(x11[1], y11[1]);
	glVertex2f(x11[1], y11[1]);	
	glVertex2f(x11[2], y11[2]);
	glVertex2f(x11[2], y11[2]);
	glVertex2f(x11[3], y11[3]);
	glVertex2f(x11[1], y11[1]);	
	glVertex2f(x11[4], y11[4]);
	glVertex2f(x11[4], y11[4]);	
	glVertex2f(x11[5], y11[5]);
	glEnd();
	glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();



	glPushMatrix (); //����
	glRotated(delta*6,0,0,1); // "��������" �����
	glTranslatef(0, 1.5,flag1*0.1);
	glRotated(90,0,0,1);

	glScaled(0.2,0.5,0.5); //������� ����
	glPushMatrix ();
	glScaled(1.4,0.67,0.67);
	glTranslatef (0.0, -0.2, -0.09); 
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING); // ��� ���� ���������
	glColor3f(0,0,0);
	gluSphere(Quadric,0.123,30,30);   
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING); // ��� ��� ���������
	glPopMatrix ();
     glRotated(90,1,0,0);   

	
   //������ ���� � ���������� �������
   glBindTexture   ( GL_TEXTURE_2D, texture1Id );
   gluCylinder (Quadric, 0.0, 0.05,0.01, 38, 38);
   glTranslatef (0.0, 0, 0.01);
   gluCylinder (Quadric, 0.05, 0.15,0.08, 38, 38);
   glTranslatef (0.0, 0, 0.08);
   gluCylinder (Quadric, 0.15, 0.2,0.1, 38, 38);
   glTranslatef (0.0, 0, 0.1);
   glBindTexture   ( GL_TEXTURE_2D, texture2Id );
   gluCylinder (Quadric, 0.2, 0.3,0.2, 38, 38);
   glTranslatef (0.0, 0, 0.2);

   glRotated(3*sin(delta),0,1,0); //�������� ����
   glBindTexture   ( GL_TEXTURE_2D, texture1Id );  
   gluCylinder (Quadric, 0.3, 0.4,0.3, 38, 38);
   glTranslatef (0.0, 0, 0.3);
   glBindTexture   ( GL_TEXTURE_2D, texture3Id );
   //glRotated(sin(delta),10,0,0);//�������� ����
   //glRotated(3*sin(delta),0,1,0);//�������� ����

   gluCylinder (Quadric, 0.4, 0.4,0.3, 38, 38);
   glTranslatef (0.0, 0, 0.3);
   glBindTexture   ( GL_TEXTURE_2D, texture4Id );
   glRotated(3*sin(delta),0,1,0);//�������� ����
   gluCylinder (Quadric, 0.4, 0.3,0.3, 38, 38);
   glTranslatef (0.0, 0, 0.3);
   glBindTexture   ( GL_TEXTURE_2D, texture5Id );   
   gluCylinder (Quadric, 0.3, 0.14,0.3, 38, 38);
   glTranslatef (0.0, 0, 0.3);
   glBindTexture   ( GL_TEXTURE_2D, texture6Id );


   gluCylinder (Quadric, 0.14, 0.14,0.1, 38, 38);
   glTranslatef (0.0, 0, 0.1);
   glBindTexture   ( GL_TEXTURE_2D, texture1Id );
   gluSphere(Quadric,0.14,38,38);

   glPushMatrix ();   //������� �� ������
   glRotated(20*sin(delta),0,1,0);//����� ���������
   glScaled(0.1,1,1);	
   glTranslatef (0.0,-0.0, 0.0);
   glBindTexture   ( GL_TEXTURE_2D, texture1Id );
   gluCylinder (Quadric, 0.14, 0.25,0.2, 18, 18);
   glTranslatef (0.0, 0, 0.25);
   glScaled(1,1,0.6);	
   glBindTexture   ( GL_TEXTURE_2D, texture9Id );
   gluSphere(Quadric,0.25,18,18);
   glPopMatrix ();

   glPushMatrix (); //�������� ������� �  ������, ������������ ����� � ������
   glScaled(0.1,1,1);	
   glTranslatef (0.0,-0.25, -0.3);
   glScaled(1,0.6,1);	
   gluSphere(Quadric,0.25,18,18);
   glTranslatef (0.0,0.8, 0.0);
   gluSphere(Quadric,0.25,18,18);
   glPopMatrix ();

   glPushMatrix (); //������ �������
   glScaled(0.1,1,1);	
   glTranslatef (0.0,0.35, -0.9);
   glRotated(-45,1,0,0);  
   glScaled(1,0.6,1);	
   gluSphere(Quadric,0.25,18,18);
   glPopMatrix ();

   glPushMatrix ();//����� �������
   glScaled(5,1,1);	
   glTranslatef (0.07,0.13, -1.1);
   glRotated(20+10*sin(delta),-1,1,0);   //����� ���������
   glScaled(0.01,1,1);	
   gluCylinder (Quadric, 0.04, 0.2,0.2, 18, 18);
   glTranslatef (0.0, 0, 0.2);
   glScaled(1,1,0.6);	
   gluSphere(Quadric,0.2,18,18);
   glPopMatrix ();

   glPushMatrix ();//������ �������
   glScaled(5,1,1);	
   glTranslatef (-0.07,0.13, -1.1);
   glRotated(-20-10*sin(delta),1,1,0);  //����� ���������
   glScaled(0.01,1,1);	
   gluCylinder (Quadric, 0.04, 0.2,0.2, 18, 18);glTranslatef (0.0, 0, 0.2);
   glScaled(1,1,0.6);	
   gluSphere(Quadric,0.2,18,18);
   glPopMatrix ();



	glPopMatrix ();
	glPopMatrix (); 
 glDisable(GL_TEXTURE_2D);
 glDisable(GL_LIGHTING);

 
 //����
	 glPushMatrix();
	glTranslatef (0.0,-4.3, 0);
	glRotated(90,1,0,0);
	 glEnable(GL_TEXTURE_2D);
 	glBindTexture(GL_TEXTURE_2D,texture);

	glBegin(GL_QUADS);
	glColor3d(1.0,1.0,1.0);
	glTexCoord2d(0,0);             
	glVertex3d(v[0].x,v[0].y,v[0].z);
	glTexCoord2d(1,0);	
	glVertex3d(v[1].x,v[1].y,v[1].z);
	glTexCoord2d(1,1);	
	glVertex3d(v[2].x,v[2].y,v[2].z);
	glTexCoord2d(0,1);	
	glVertex3d(v[3].x,v[3].y,v[3].z);

	glTexCoord2d(0,0);
	glVertex3d(v[3].x,v[3].y,v[3].z);
	glTexCoord2d(1,0);	
	glVertex3d(v[2].x,v[2].y,v[2].z);
	glTexCoord2d(1,1);
	glVertex3d(v[6].x,v[6].y,v[6].z);
	glTexCoord2d(0,1);	
	glVertex3d(v[7].x,v[7].y,v[7].z);

	glTexCoord2d(0,0);	
	glVertex3d(v[1].x,v[1].y,v[1].z);
	glTexCoord2d(1,0);	
	glVertex3d(v[5].x,v[5].y,v[5].z);
	glTexCoord2d(1,1);	
	glVertex3d(v[6].x,v[6].y,v[6].z);
	glTexCoord2d(0,1);
	glVertex3d(v[2].x,v[2].y,v[2].z);

	glTexCoord2d(0,0);	
	glVertex3d(v[4].x,v[4].y,v[4].z);
	glTexCoord2d(1,0);	
	glVertex3d(v[0].x,v[0].y,v[0].z);
	glTexCoord2d(1,1);	
	glVertex3d(v[3].x,v[3].y,v[3].z);
	glTexCoord2d(0,1);
	glVertex3d(v[7].x,v[7].y,v[7].z);
	
	glTexCoord2d(0,0);	
	glVertex3d(v[1].x,v[1].y,v[1].z);
	glTexCoord2d(1,0);	
	glVertex3d(v[0].x,v[0].y,v[0].z);
	glTexCoord2d(1,1);
	glVertex3d(v[4].x,v[4].y,v[4].z);
	glTexCoord2d(0,1);
	glVertex3d(v[5].x,v[5].y,v[5].z);
    glEnd();


    //����������� ����� ����� ������������ ��������
	glBindTexture(GL_TEXTURE_2D,texMod); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(v[5].x,v[5].y,v[5].z);
	glTexCoord2d(1,0);
	glVertex3d(v[4].x,v[4].y,v[4].z);
	glTexCoord2d(1,1);
	glVertex3d(v[7].x,v[7].y,v[7].z);
	glTexCoord2d(0,1);
	glVertex3d(v[6].x,v[6].y,v[6].z);
    glEnd();


	glTranslatef (0.0,0, -4.6);
	glScaled(0.5,0.9,0.3);
	for(int i=1;i<3;i++){ 
	if(i==1)glFrontFace(GL_CW);//������, ����� ����� ������� ��������
    if(i==2)glFrontFace(GL_CCW);

	glBindTexture( GL_TEXTURE_2D, texture11Id );
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  
	glVertex3d(v[0].x,v[0].y,v[0].z);	
	glTexCoord2d(1,0);	
	glVertex3d(v[1].x,v[1].y,v[1].z);
	glTexCoord2d(1,1);	
	glVertex3d(v[2].x,v[2].y,v[2].z);	
	glTexCoord2d(0,1);	
	glVertex3d(v[3].x,v[3].y,v[3].z);
	glEnd();

	glBindTexture( GL_TEXTURE_2D, textura.texID );
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);	
	glVertex3d(v[3].x,v[3].y,v[3].z);	
	glTexCoord2d(1,0);	
	glVertex3d(v[2].x,v[2].y,v[2].z);
	glTexCoord2d(1,1);	
	glVertex3d(v[6].x,v[6].y,v[6].z);
	glTexCoord2d(0,1);
	glVertex3d(v[7].x,v[7].y,v[7].z);
	glEnd();

    glBegin(GL_QUADS);
	glTexCoord2d(0,0);	
	glVertex3d(v[1].x,v[1].y,v[1].z);	
	glTexCoord2d(1,0);	
	glVertex3d(v[5].x,v[5].y,v[5].z);
	glTexCoord2d(1,1);
	glVertex3d(v[6].x,v[6].y,v[6].z);	
	glTexCoord2d(0,1);	
	glVertex3d(v[2].x,v[2].y,v[2].z);
    glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);	
	glVertex3d(v[4].x,v[4].y,v[4].z);
	glTexCoord2d(1,0);
	glVertex3d(v[0].x,v[0].y,v[0].z);
	glTexCoord2d(1,1);
	glVertex3d(v[3].x,v[3].y,v[3].z);
	glTexCoord2d(0,1);	
	glVertex3d(v[7].x,v[7].y,v[7].z);
	glEnd();

	glBegin(GL_QUADS);					
	glTexCoord2d(0,0);
	glVertex3d(v[1].x,v[1].y,v[1].z);	
	glTexCoord2d(1,0);	
	glVertex3d(v[0].x,v[0].y,v[0].z);
	glTexCoord2d(1,1);
	glVertex3d(v[4].x,v[4].y,v[4].z);
	glTexCoord2d(0,1);	
	glVertex3d(v[5].x,v[5].y,v[5].z);
	glEnd();

if(i==1)
{   //����������� ����
	glBindTexture( GL_TEXTURE_2D, textura2.texID ); 
	glBegin(GL_QUADS);	
	glTexCoord2d(0,0);	
	glVertex3d(v[5].x,v[5].y,v[5].z*0.8);	
	glTexCoord2d(1,0);	
	glVertex3d(v[4].x,v[4].y,v[4].z*0.8);
	glTexCoord2d(1,1);	
	glVertex3d(v[7].x,v[7].y,v[7].z*0.8);
	glTexCoord2d(0,1);
	glVertex3d(v[6].x,v[6].y,v[6].z*0.8);
	glEnd();}
}


glPopMatrix ();

 //���� ����������

 glPopMatrix ();
 }
 else  //�����, "����" ��������
 {
	// ������������� ������ OpenGL
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);

	glBindTexture(GL_TEXTURE_2D,texture13Id);

	// ������ ���������������
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

 
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

	glColor4f(0.7f,0.4f,0.8f,0.8f);
	koefSizeFont=3.75; 
	glPrintBMP(20,440,"�������",0);
	glPrintBMP(20,400,"� ���������� ����,",0);
	glPrintBMP(30,350,"��� - ��� �� ������,",0);
  	koefSizeFont=3.6;
	glColor3ub(190,220,240);
	glPrint(10,150,"�� ����� �� ����� ����",0);	
	glPrint(50,100,"������� �� ������!",0);	



}
//glFlush ();
 glutSwapBuffers();
}


/* ���������� ��� ������� ������� �� ���������� */
void keyboard(unsigned char key, int x, int y)
{
    if( key == 'o' || key == 'O' ) alSourcePlay ( source );
if( key == ' ' ) rotat=rotat*-1; //������ ��������

   switch (key) 
   {
      case 27: /* escape */
       Finalize();	
         exit(0);
         break;
display();
         break;		  
   }
}



void	idle ()
{
 delta=0.1+delta;
       
   display ();     
}

void init ()
{	
	LoadTGA(&textura,"1.tga");	
    LoadTGA(&textura2,"more89.tga");
   

	//++�������� �����������
//	pix[0].makeCheckerboard();
    pix[0].makeCheckerboard(200,100,50,100,20,12);// ���� �������� ��������, ������ 3 �����- �������� ����, ������ 3 - �������� (���-�� � ���������)
	// ������� ���������� ������
	glGenTextures(1,&texMod);

 /*                               	// ��������� ��������
	// ������� ������ � ������� �������� (������ ���� � ��������� ��� ��������)
	if((tex_bits = LoadTrueColorBMPFile("ris1.bmp",&tex_width,&tex_height)) == NULL) 
		return false;
	// ������� ���������� ������
	glGenTextures(1,&texture);*/
	// ������������ ����������  ������
	glBindTexture(GL_TEXTURE_2D,texMod);

	// ������������� ��������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		         0,                     // Mip-level
			     GL_RGB,                // ������ ��������
			    // tex_width,tex_height,   ������ ��������
				pix[0].nRows, pix[0].nCols,
			     0,                     // ������ �������
			     GL_RGB,                // ������ �������� ������
			     GL_UNSIGNED_BYTE,      // ��� �������� ������
				 pix[0].pixel);             // ��������� �� �������� ������ 
	// ����������� ������, � ������� ��������� ��������
	delete[] pix[0].pixel;

///////////////////////
                                	// ��������� ��������
	// ������� ������ � ������� �������� (������ ���� � ��������� ��� ��������)
	if((tex_bits = LoadTrueColorBMPFile("stol.bmp",&tex_width,&tex_height)) == NULL) ;

	// ������� ���������� ������
	glGenTextures(1,&texture);
	// ������������ ����������  ������
	glBindTexture(GL_TEXTURE_2D,texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1); //����������� �� ������� �����

	// ������������� ��������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D,
		         0,                     // Mip-level
			     GL_RGB,                // ������ ��������
			     tex_width,tex_height,  // ������ ��������
			     0,                     // ������ �������
			     GL_RGB,                // ������ �������� ������
			     GL_UNSIGNED_BYTE,      // ��� �������� ������
				 tex_bits);             // ��������� �� �������� ������ 
	// ����������� ������, � ������� ��������� ��������
	delete[] tex_bits;

////////////////////////
	// �������� ������������� ���������������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	
//���������� ����
	    ALenum      format;
    ALsizei     size;
    ALvoid    * data;
    ALsizei     freq;
    ALboolean   loop;
    ALboolean   loopFon;
///////////////////////////����-������
    alGenBuffers ( 1, &buffer );          // create buffer

   alutLoadWAVFile ( "A_BAB_BR.WAV", &format, &data, &size, &freq, &loop );
 
	alBufferData    ( buffer, format, data, size, freq );
    alutUnloadWAV   ( format, data, size, freq );

    alGenSources ( 1, &source );          // create source
                                        // setup source params
    alSourcei ( source, AL_BUFFER,   buffer    );
    alSourcef ( source, AL_PITCH,    1.0f      );
    alSourcef ( source, AL_GAIN,     1.0f      );
    alSourcefv( source, AL_POSITION, sourcePos );
    alSourcefv( source, AL_VELOCITY, sourceVel );
    alSourcei ( source, AL_LOOPING,  loop      );


	//+�����
	fonTex = auxDIBImageLoad ("F.bmp" );
	glGenTextures( 1, &fontextureId );
	glBindTexture( GL_TEXTURE_2D, fontextureId );
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );			// set 1-byte alignment
	glTexImage2D( GL_TEXTURE_2D, 0, 3, fonTex -> sizeX, 
                    fonTex -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                    fonTex -> data );
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
	delete[] fonTex;
	glEnable     ( GL_DEPTH_TEST );
	LoadTGA(&texturaAlphaFont,"F1.tga");
	BuildFont();
	BuildFontBMP();
	//�����

   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };  //������������� ���������� �����
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //������������� �������� �����
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // ������������� ����������� �����
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.2 }; //��������� ��������� ����� (x,y,z,w)

   // ������������� ��������� ��������� ����� 
   glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);

   // �������� ��������� � �������� ����� 
   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);

   
	
	glEnable(GL_DEPTH_TEST);glEnable(GL_TEXTURE_2D);
	image = auxDIBImageLoad( "1.bmp" );
	glGenTextures   ( 1, &texture1Id );
	glBindTexture   ( GL_TEXTURE_2D, texture1Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

    glEnable(GL_DEPTH_TEST);	glEnable(GL_TEXTURE_2D);
	image = auxDIBImageLoad( "2.bmp" );
	glGenTextures   ( 1, &texture2Id );
	glBindTexture   ( GL_TEXTURE_2D, texture2Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

    glEnable(GL_DEPTH_TEST);glEnable(GL_TEXTURE_2D);
	image = auxDIBImageLoad( "3.bmp" );
	glGenTextures   ( 1, &texture3Id );
	glBindTexture   ( GL_TEXTURE_2D, texture3Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;
 
	glEnable(GL_DEPTH_TEST);	glEnable(GL_TEXTURE_2D);
	image = auxDIBImageLoad( "4.bmp" );
	glGenTextures   ( 1, &texture4Id );
	glBindTexture   ( GL_TEXTURE_2D, texture4Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
     delete[] image;

    image = auxDIBImageLoad( "5.bmp" );
	glGenTextures   ( 1, &texture5Id );
	glBindTexture   ( GL_TEXTURE_2D, texture5Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
     delete[] image;

image = auxDIBImageLoad( "6.bmp" );
	glGenTextures   ( 1, &texture6Id );
	glBindTexture   ( GL_TEXTURE_2D, texture6Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
     delete[] image;


image = auxDIBImageLoad( "sfera.bmp" );
	glGenTextures   ( 1, &texture7Id );
	glBindTexture   ( GL_TEXTURE_2D, texture7Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

image = auxDIBImageLoad( "8.bmp" );
	glGenTextures   ( 1, &texture8Id );
	glBindTexture   ( GL_TEXTURE_2D, texture8Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

image = auxDIBImageLoad( "9.bmp" );
	glGenTextures   ( 1, &texture9Id );
	glBindTexture   ( GL_TEXTURE_2D, texture9Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;


image = auxDIBImageLoad( "galk13.bmp" );
	glGenTextures   ( 1, &texture11Id );
	glBindTexture   ( GL_TEXTURE_2D, texture11Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

image = auxDIBImageLoad( "pz.bmp" );
	glGenTextures   ( 1, &texture13Id );
	glBindTexture   ( GL_TEXTURE_2D, texture13Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;

image = auxDIBImageLoad( "kampl10.bmp" );
	glGenTextures   ( 1, &texture12Id );
	glBindTexture   ( GL_TEXTURE_2D, texture12Id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei   ( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 		         image->sizeX,				 image->sizeY,				 0, GL_RGB, GL_UNSIGNED_BYTE,				 image->data);
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT );  /*       // set texture to repeat mode */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT );     /* ��� ���     */
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* �� ���������   */	
	glTexParameteri ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* �� ��� ����� �� ��������   */
    delete[] image;
flag1=8;
}
void mouse(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN ) 
  {
    switch( button ) 
	{
      case GLUT_LEFT_BUTTON:if(flag1<12)flag1++;
        break;
      case GLUT_RIGHT_BUTTON:if(flag1>-2)flag1--;
        break;
		case GLUT_MIDDLE_BUTTON: zastavka=zastavka*-1;
			break;

    }
display();
//   glutPostRedisplay();
  }
}

void timAW(int value) // Timer function
{
if (t1>1) tt1=-1;
if (t1<0) tt1=1;
t1=t1+0.004*tt1;

if(sp1>1.8)sp1=0;
sp1=sp1+0.03;

  glutTimerFunc(10, timAW, 0); // Setup next timer

// Display();
}

int main(int argc, char** argv)
{
	
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
                      | GLUT_DEPTH);
   glutInitWindowSize (800, 600);
   glutCreateWindow (argv[0]);
   glutReshapeFunc (reshape);
   glutDisplayFunc (display);
   glutKeyboardFunc (keyboard);
   glutMouseFunc(mouse);
   alutInit( NULL, 0 );             // initialize OpenAL and clear the error bit.
   glutTimerFunc(200, timAW, 0);
   alGetError();
   glutIdleFunc     ( idle);
   init();
   glutMainLoop();
   return 0;
}
