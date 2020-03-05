#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <bits/stdc++.h>

int refreshMills = 1;
float angle=5;
int r1,r2;
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-500,500,-500,500);
}

void drawPixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
     glVertex2i(x,y);
  glEnd();
}

void draw_pixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
     glVertex2i(x,y);
  glEnd();
}
void circle(int xc,int yc,int rad){
 
  int xCenter=xc,yCenter=yc,r=rad;
  int x=0,y=r;
  int d = 3 - 2*r;    // = 1 - r
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 1 ,0, 0);
  while(x<=y){
    drawPixel(xCenter+x,yCenter+y);
    drawPixel(xCenter+y,yCenter+x);  //find other points by symmetry
    drawPixel(xCenter-x,yCenter+y);
    drawPixel(xCenter+y,yCenter-x);
    drawPixel(xCenter-x,yCenter-y);
    drawPixel(xCenter-y,yCenter-x);
    drawPixel(xCenter+x,yCenter-y);
    drawPixel(xCenter-y,yCenter+x);

    if (d<0){
	  d += (4*x)+6;
    }
    else {
 	d += (4*(x-y))+10;
 	y -= 1;
    }
    x++;
  }

//  glFlush();
}

void line(int x1,int x2,int y1,int y2){

//	glClear(GL_COLOR_BUFFER_BIT);
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
void wheel(int r1,int r2){
        glClear(GL_COLOR_BUFFER_BIT);
//      angle+=0.2;
            circle(0,0,r1);
            circle(0,0,r2);
            glPushMatrix();
//          glRotatef(angle,0.0f,0.0f,1.0f);
            line(0,0,100,400);
            line(0,0,100,400);
            line(0,0,-100,-400);
            line(0,0,-100,-400);
            line(100,400,0,0);
            line(-100,-400,0,0);
            line(69,285,69,285);
            line(-69,-285,-69,-285);
            line(69,285,-69,-285);
            line(-69,-285,69,285);
            glEnd();
            glPopMatrix();
            line(-500,500,-400,-400);
            glFlush();
//              angle += 0.02f;
//              printf("%f",angle);

}
void myDisplay(){
	r1=100;r2=400;
	 glClear(GL_COLOR_BUFFER_BIT);
	 glFlush();
}
void mouseDisplay(){
	wheel(r1,r2);
}
void rightMouse(){
	exit(0);
}
void mouse(int button,int state,int x,int y)
{
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
                if(state==GLUT_DOWN)
                        glutIdleFunc(mouseDisplay);
                break;
        case GLUT_MIDDLE_BUTTON:
                if(state==GLUT_DOWN)
                {
                        glutIdleFunc(NULL);
                }
                break;
        case GLUT_RIGHT_BUTTON:
                if(state==GLUT_DOWN){
		  	glutIdleFunc(rightMouse);
                }
                break;
        default:
                break;
        }
}
void keyboard(unsigned char key, int x, int y)
{
        //-------- spin --------
        if(key=='i')
        {
                //setSpin(1.0,0.0,0.0);
                //glutPostRedisplay();
		r1+=5;r2=r2+5;
		mouseDisplay();

        }
        else if(key=='d')
        {
//                setSpin(0.0,1.0,0.0);
//                glutPostRedisplay();
                  r1-=5;r2-=5;
		  mouseDisplay();
        }
        else if(key=='c')
        {
//                setSpin(0.0,0.0,1.0);
//                glutPostRedisplay();
 	          //r1=100;r2=400;
		  printf("%s","2");
		  glutPostRedisplay();
        }
        else if(key=='a')
        {
//                setSpin(1.0,1.0,1.0);
 //               glutPostRedisplay();
        }
        //-------- spin --------
        //-------- zoom --------
        else if(key=='i')
        {
  //              translate_z++;
    //            glutPostRedisplay();
        }
        else if(key=='o')
        {
      //          translate_z--;
        //        glutPostRedisplay();
        }
        //-------- zoom --------
        //-------- reset -------
	else if(key=='r')
        {
          //      reset();
            //    glutPostRedisplay();
        }
        //-------- reset -------
}
/*void wheel(){
  	glClear(GL_COLOR_BUFFER_BIT);
//	angle+=0.2;
	    circle(0,0,100);
	    circle(0,0,400);
	    glPushMatrix();
//	    glRotatef(angle,0.0f,0.0f,1.0f);
	    line(0,0,100,400);
	    line(0,0,100,400);
	    line(0,0,-100,-400);
	    line(0,0,-100,-400);
	    line(100,400,0,0);
	    line(-100,-400,0,0);
	    line(69,285,69,285);
	    line(-69,-285,-69,-285);
	    line(69,285,-69,-285);
	    line(-69,-285,69,285);
	    glEnd();
	    glPopMatrix();
	    line(-500,500,-400,-400);
	    glFlush();
//	        angle += 0.02f;
//		printf("%f",angle);

}

*/

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham Circle");
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
//    glutTimerFunc(0,Timer,0);
    glutMainLoop();
    return 0;
}
