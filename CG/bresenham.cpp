#include<stdio.h>
#include<GL/glut.h>
//#include<math.h>

int x1,x2,y1,y2;

void MyInit(){
	glClearColor(0,0,0,1);
	gluOrtho2D(0,1000,0,1000);
}

void draw_pixel(int x,int y){
//	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void line(int x1,int x2,int y1,int y2){

	glClear(GL_COLOR_BUFFER_BIT);
	int x,y,e;
	int incx,incy,inc1,inc2,dx,dy;
	
	dx=x2-x1;
	dy=y2-y1;

	if(dx<0)dx=-dx;
	if(dy<0)dy=-dy;

	x=x1;y=y1;

	incx=1;
	if(x2<x1)incx=-1;

	incy=1;
	if(y2<y1)incy=-1;

	if(dx>dy){
		draw_pixel(x,y);
		e=2*dy-dx;
		inc1=2*(dy-dx);
		inc2=2*dy;
		for(int i=0;i<dx;i++){
			if(e>=0){
				y+=incy;
				e+=inc1;
			}
			else 
				e+=inc2;
			x+=incx;
			draw_pixel(x,y);
		}
	}

	else{
		draw_pixel(x,y);
		e=2*dx-dy;
		inc1=2*(dx-dy);
		inc2=2*dx;
		for(int i=0;i<dy;i++){
			if(e>=0){
				x+=incx;
				e+=inc1;
			}
			else 
				e+=inc2;
			y+=incy;
			draw_pixel(x,y);
		}
	}
}

void display(){
	line(x1,x2,y1,y2);
	glFlush();
}

int main(int argc,char** argv){
	scanf("%d %d %d %d", &x1,&x2,&y1,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("bresenham");
	MyInit();
	glutDisplayFunc(display);
	glutMainLoop();
}
