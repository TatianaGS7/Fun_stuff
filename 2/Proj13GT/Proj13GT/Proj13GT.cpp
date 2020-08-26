
  //Работаем с моделируемой текстурой. (Без библиотеки glaux).

#include<gl/glut.h>
#include<tchar.h>  /**  Definitions for generic international functions, mostly defines
                   *    which map string/formatted-io/ctype functions to char, wchar_t, or
                   *    MBCS versions.  To be used for compatibility between single-byte,
                   *    multi-byte and Unicode text models.*/
#include<stdio.h>
#include<string.h>
#include <Math.h>
//#include<stdlib.h>

#include"MTex.h"

                // BMP file format definition


#pragma pack(1)
float WH = 0;  //SSSSSSSSSSSSSSSS

GLint Width = 600, Height = 600;   //SSSSSSSS
float delta = 50;  //SSSSS
float yr = 0.1;//SSSSSSS
float a,x,z; //SSSSS
float f = 90;//SSSSSSS

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



GLUquadricObj *tex; //SSSSSS

#pragma pack()

                  //   Начало.    (Две функции для загрузки .bmp - файла.) 


//ПРОДОЛЖАЕМ НИЧЕГО НЕ ТРОГАТЬ

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
                   //   Конец.    (Две функции для загрузки .bmp - файла.) 


                   // Начало работы с OpenGL.


 RGBpixmap pix[2];  //создаем две пустые пиксельные карты

int tex_width;
int tex_height;
unsigned char *tex_bits = NULL;  // захватываем и чистим место под
                                 // текстуру.



// Добавляем моделируемые текстуры
GLuint texture = 0;
GLuint texMod1 = 0;
GLuint texMod2 = 0; 




void reshape(int w, int h)   
{
	WH = (float)Width/(float)Height;
    Width = w;
    Height = h;
	glViewport(0,0,w,h);
	if(h > 0) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,WH,10,300); //перспективная проекция
	}
}

void display(void)   
{
	x = f*cos(a); 
	z = f*sin(a); 
	glClearColor(0.4,0.3,1,0.0); // цвет фона
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x,20.0f,z,0.0f,0.0f,0.0f,10.0f,1.0f,0.0f); //функция камеры 

   
	// создаем цилиндр
	glBindTexture(GL_TEXTURE_2D,texMod1);
	glPushMatrix();
    glTranslatef(0,1,-10);
   	gluCylinder(tex, 10, 10, 20, 100, 100);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texMod1);
	glPushMatrix();
    glTranslatef(0,1,-10);
   	gluDisk(tex, 0, 10,1000, 1000);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texMod1);
	glPushMatrix();
    glTranslatef(0,1,10);
    gluDisk(tex, 10, 17,1000, 1000);
	glPopMatrix();


	
    glFlush();
	glutSwapBuffers();
}

void idle (int value)
{
	a = a + 0.009; //скорость прокрутки фигуры
	
	glutTimerFunc(20,idle,0); 
	display();

}


    
bool InitAW()
{
 //Проводить удаление невидимых линий и поверхностей
 glEnable(GL_DEPTH_TEST);
 
    // Разрешаем текстурирование
 	glEnable(GL_TEXTURE_2D);

   //цвет у первой верхушки
   pix[0].makeCheckerboard(115,81,132,0,0,0);// цвет текстуры площадки, первые 3 цвета- основной цвет, вторые 3 - побочный (что-то в серединке)
	// Создаем текстурный объект
	glGenTextures(1,&texMod1);

    // Активизируем текстурный  объект
	glBindTexture(GL_TEXTURE_2D,texMod1);
  //glPixelStorei(GL_UNPACK_ALIGNMENT,1); //выравниваем на границу байта

	// Устанавливаем параметры текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		         0,                     // Mip-level
			     GL_RGB,                // Формат текстуры
			    // tex_width,tex_height,   Размер текстуры
				pix[0].nRows, pix[0].nCols,
			     0,                     // Ширина границы
			     GL_RGB,                // Формат исходных данных
			     GL_UNSIGNED_BYTE,      // Тип исходных данных
				 pix[0].pixel);             // Указатель на исходные данные 
	// Освобождаем память, в которой хранилась текстура
	delete[] pix[0].pixel;
///////////////////////////


       // цвет цилиндра
	pix[1].makeCheckerboard(80,88,81,0,0,0);
	glGenTextures(1,&texMod2);// Создаем текстурный объект

	glBindTexture(GL_TEXTURE_2D,texMod2);
//	glPixelStorei(GL_UNPACK_ALIGNMENT,1); //выравниваем на границу байта

	// Устанавливаем параметры текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		         0,                     // Mip-level
			     GL_RGB,                // Формат текстуры
			    // tex_width,tex_height,   Размер текстуры
				pix[1].nRows, pix[1].nCols,
			     0,                     // Ширина границы
			     GL_RGB,                // Формат исходных данных
			     GL_UNSIGNED_BYTE,      // Тип исходных данных
				 pix[1].pixel);             // Указатель на исходные данные 
	// Освобождаем память, в которой хранилась текстура
	delete[] pix[1].pixel;
	///////////////////


    
	///////////////////
	glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	tex = gluNewQuadric();
	gluQuadricTexture(tex,GL_TRUE);
	return true;
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (Width, Height ); 
    glutCreateWindow("Моделируемая текстура");
 	glutTimerFunc(100,idle,0);
	if(!InitAW())
		return 1;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	//glutIdleFunc(idle);
    glutMainLoop();
    return 0;          
}