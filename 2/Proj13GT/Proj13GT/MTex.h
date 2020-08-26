class myRGB
{
public: unsigned char r,g,b;
};

class RGBpixmap
{


public:
	int nRows, nCols;  //ðàçìåðû ïèêñåëüíîé êàðòû
	myRGB* pixel;  //ìàññèâ ïèêñåëîâ
public:
	RGBpixmap() {nRows = nCols = 0; pixel = 0;}
	RGBpixmap(int r, int c)   //êîíñòðóêòîð
	{
		nRows = r;
		nCols = c;
		pixel = new myRGB[r*c];
	}
	void setPixel(int x, int y, myRGB color)
	{
		if(x >= 0 && x < nCols && y >= 0 && y < nRows)
			pixel[nCols * y + x] = color;
	}

	void makeCheckerboard(int c1,int c2,int c3,int c4,int c5,int c6); //!!! ñîçäàåì ìîä. òåêñòóðó

	// ... äðóãèå ôóíêöèè 
};

void RGBpixmap::makeCheckerboard(int c1,int c2,int c3,int c4,int c5,int c6) //!!!
{	
	
	nRows = nCols = 100; // ÓÑËÎÂÍÎ ÃÎÂÎÐß - ÊÎË-ÂÎ ÏÈÊÑÅËÅÉ (ÐÀÇÌÛÒÎÑÒÜ\×ÅÒÊÎÑÒÜ)
	pixel = new myRGB[3*nRows*nCols];
	if(!pixel){/*cout << "out of memory";*/return;}
	long count = 0;
	for(int i=0; i<nRows; i++)
		for(int j=0; j<nCols; j++)
		{	if (i%2==0&&j%2==0)  //!!!
			{	pixel[count].r=c1;
				pixel[count].g=c2;
				pixel[count++].b=c3;
			} else {
				pixel[count].r=c4;
				pixel[count].g=c5;
				pixel[count++].b=c6;
			}
		}  
      }




	


