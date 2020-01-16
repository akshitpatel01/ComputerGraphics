#include<stdio.h>
#include<GL/glut.h>
//#include<math.h>
float x1,x2,y1,y2;
void MyInit(){
	glClearColor(0,0,0,1);
	gluOrtho2D(0,500,0,500);
}

void draw_pixel(float x,float y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void dda(){
	float step,incx,incy;
	float dx,dy;
	float x,y;

	dx=x2-x1;
	dy=y2-y1;

	step=(abs(dx)>abs(dy))?abs(dx):abs(dy);

	incx=dx/step;
	incy=dy/step;

	x=x1;y=y1;
//	draw_pixel((int)floor(x1),(int)floor(y1));
	draw_pixel(x,y);

	for(int i=0;i<=step;i++){
		x+=incx;
		y+=incy;
		draw_pixel(x,y);
	}
	glFlush();

}

//void chess(){
//	int x=100,y=100;
//	float x1,
//}

int main(int argc, char** argv){
//	float x1,x2,y1,y2;
//	cin >> x1 >> x2 >> y1 >> y2;
	x1=1;x2=40;y1=19;y2=43;
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("chess");
	MyInit();
	glutDisplayFunc(dda);
	glutMainLoop();
}
