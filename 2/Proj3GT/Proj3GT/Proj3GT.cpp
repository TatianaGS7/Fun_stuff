#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#include	<windows.h>
#include <stdlib.h>
#include <gl/glut.h> 


GLint Width = 720, Height = 600;  
float t=0; // координаты точки стартовые

float xs[4]={60,80,120,120};
float ys[4]={380,440,440,400};

float xn[4]={600,580,660,680};
float yn[4]={400,480,540,460};

float bxs[4]={60,60,40,40};
float bys[4]={380,360,360,340};

float bxn[4]={600,610,640,660};
float byn[4]={400,350,330,300};
int i;

float bx[4],by[4];
float x[4],y[4];
void Display(void)  
{
    glClearColor(0.5, 0.8, 0.9, 1);
    glClear(GL_COLOR_BUFFER_BIT); 



    //облака
	glLineWidth(2); // 1 облако
	glBegin(GL_POLYGON); 
    glColor3ub(176, 196, 222);
	glVertex2i(160,520);
	glVertex2i(180,530);
	glVertex2i(200,530);
	glColor3ub(100, 149, 237);
	glVertex2i(220,520);
	glVertex2i(240,500);
	glVertex2i(234,480);
	glColor3ub(70, 130, 180);
	glVertex2i(200,470);
	glVertex2i(180,470);
	glVertex2i(160,480);
    glEnd();

	glBegin(GL_POLYGON); //2 облако
    glColor3ub(100, 149, 237);
	glVertex2i(160,520);
	glVertex2i(180,510);
	glColor3ub(176, 196, 222);
	glVertex2i(190,500);
	glVertex2i(180,490);	
	glVertex2i(160,480);
	glVertex2i(140,470);
	glVertex2i(120,470);
	glVertex2i(100,480);
	glVertex2i(80,480);
	glVertex2i(60,500);
	glVertex2i(80,520);
	glVertex2i(100,520);
	glVertex2i(120,530);
	glVertex2i(140,530);
    glEnd();

    glBegin(GL_POLYGON); // 3 облако
    glColor3ub(176, 196, 222);
	glVertex2i(80,270);
	glVertex2i(100,290);    
	glVertex2i(120,298);
	glVertex2i(160,298);
	glVertex2i(166,294);
    glColor3ub(159, 182, 205);
	glVertex2i(184,298);
	glVertex2i(226,286);
	glVertex2i(266,280);
	glColor3ub(122, 103, 238);
	glVertex2i(272,260);
	glVertex2i(300,250);
	glVertex2i(316,246);
	glColor3ub(72, 118, 255);
	glVertex2i(300,230);
	glVertex2i(240,226);
	glVertex2i(254,216);
	glVertex2i(240,210);
    glVertex2i(220,206);
	glVertex2i(180,216);
	glVertex2i(140,220);
	glVertex2i(120,230);
	glVertex2i(100,240);
	glVertex2i(80,260);
    glEnd();

	glBegin(GL_POLYGON); //3 маленькое облако
    glColor3ub(176, 196, 222);
	glVertex2i(80,270);
	glVertex2i(64,250);
	glColor3ub(70, 130, 180);
	glVertex2i(64,240);
	glVertex2i(42,226);
	glVertex2i(50,215);
	glColor3ub(122, 103, 238);
	glVertex2i(100,210);
	glVertex2i(120,214);
	glVertex2i(140,218);
	glVertex2i(180,216);
    glEnd();

	glLineWidth(2); 	 //4 облако
	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2i(560,314);
	glVertex2i(594,314);
	glVertex2i(618,282);
	glColor3ub(176, 196, 222);
	glVertex2i(600,308);	
	glVertex2i(640,308);
	glVertex2i(646,300);
	glVertex2i(666,300);
	glVertex2i(660,280);
	glVertex2i(660,274);
	glVertex2i(668,264);
	glVertex2i(680,258);
	glVertex2i(640,240);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(176, 224, 230);
	glVertex2i(660,274);
	glVertex2i(500,230);
	glVertex2i(472,236);
	glColor3ub(176, 196, 222);
	glVertex2i(466,240);
	glVertex2i(478,260);
	glVertex2i(500,270);	
	glVertex2i(480,270);
	glColor3ub(176, 224, 230);
	glVertex2i(500,280);
	glVertex2i(520,288);
	glVertex2i(522,290);
    glVertex2i(560,314);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2i(660,274);
	glVertex2i(680,270);
	glVertex2i(700,260);
	glVertex2i(690,240);
	glColor3ub(176, 224, 230);
	glVertex2i(692,220);
	glVertex2i(670,214);
	glVertex2i(600,220);
	glVertex2i(580,204);
	glVertex2i(540,204);
	glVertex2i(526,214);
	glVertex2i(500,214);
	glVertex2i(480,220);
    glColor3ub(176, 196, 222);
	glVertex2i(486,230);
	glVertex2i(472,236);
	glEnd();


	

	//горы
    glBegin(GL_POLYGON); //левая большая гора
    glColor3ub(124, 205, 124);
	glVertex2i(0,0);
	glVertex2i(0,100);
	glVertex2i(20,120);
	glVertex2i(60,120);
	glVertex2i(100,150);
	glColor3ub(154, 205, 50);
	glVertex2i(130,150);
	glVertex2i(140,140);
	glVertex2i(180,140);
	glVertex2i(200,120);
	glVertex2i(220,120);
    glColor3ub(69, 139, 0);
	glVertex2i(260,80);
	glVertex2i(320,80);
	glVertex2i(340,60);
	glVertex2i(380,40);
	glVertex2i(420,0);
    glEnd();

	glBegin(GL_POLYGON); // левая мальенькая гора
    glColor3ub(192, 255 ,62);
	glVertex2i(0,60);
	glVertex2i(120,80);
	glVertex2i(180,80);
	glVertex2i(200,60);
	glColor3ub(154, 205, 50);
	glVertex2i(240,60);
	glVertex2i(260,40);
	glVertex2i(280,40);
	glColor3ub(154, 205, 50);
	glVertex2i(320,0);
	glVertex2i(0,0);
    glEnd();

	glBegin(GL_POLYGON); //правая большая гора
    glColor3ub(192, 255 ,62);
	glVertex2i(420,0);
    glVertex2i(380,40);
	glVertex2i(340,60);
	glVertex2i(360,80);
	glVertex2i(380,80);
	glColor3ub(192, 255 ,62);
	glVertex2i(400,100);
	glVertex2i(420,100);
	glColor3ub(218, 165, 32);
	glVertex2i(440,80);
	glVertex2i(500,80);
	glColor3ub(255, 127, 80);
	glVertex2i(520,100);
	glVertex2i(530,100);
	glVertex2i(540,116);
	glVertex2i(560,116);
	glVertex2i(580,100);
	glVertex2i(600,100);
	glColor3ub(244, 164, 96);
	glVertex2i(610,90);
	glVertex2i(620,90);
	glColor3ub(222, 184, 135);
	glVertex2i(660,100);
	glVertex2i(680,100);
	glVertex2i(700,90);
	glVertex2i(720,90);
	glVertex2i(720,0);
    glEnd();
    
	//воздушный змей

	for (i=0; i<=3; i++)
	{
	x[i]=(1-t)*xs[i]+t*xn[i];
	y[i]=(1-t)*ys[i]+t*yn[i];
	}
	
	
	glBegin(GL_POLYGON);
	glColor3ub(255, 50, 50);
	glVertex2i(x[0], y[0]);
	glColor3ub(176, 48, 96);
	glVertex2i(x[1], y[1]);
    glColor3ub(255, 10, 10);
	glVertex2i(x[2], y[2]);	
	glColor3ub(176, 48, 96);
	glVertex2i(x[3], y[3]);	 
	glEnd();
    
	 
	for (i=0; i<=3; i++)
	{
	bx[i]=(1-t)*bxs[i]+t*bxn[i];
	by[i]=(1-t)*bys[i]+t*byn[i];
	}
		
	glLineWidth(3); 
	glBegin(GL_LINE_STRIP);
	glColor3ub(25, 25, 112);
	glVertex2i(bx[0],by[0]); 
	glVertex2i(bx[1],by[1]); 
	glVertex2i(bx[2],by[2]); 
	glVertex2i(bx[3],by[3]);
	glEnd();


	glFinish();   
	
	glutSwapBuffers();
}



void Idle()
{
	if (t<=1)
    {
	t=t+0.003;
	}
	else
	{
		;
	}
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
}
 

void Keyboard( unsigned char key, int x, int y ) 
{
   switch (key) {
      case 27: // escape 
		exit(0);
		break;
   }
}

 
void main(int argc, char *argv[])  
{
    glutInit(&argc, argv); 
    glutInitWindowSize(Width, Height);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); 
	glutCreateWindow("Твининг анимация");  
    glutDisplayFunc(Display);  
    glutReshapeFunc(Reshape);  
    glutKeyboardFunc(Keyboard);  
	glutIdleFunc(Idle); 
    glutMainLoop();  
}
