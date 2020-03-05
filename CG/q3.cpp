#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <bits/stdc++.h>

int refreshMills = 1;
float angle=0;
int l=100,w=75,rot=0;
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
  glColor3f( 1 ,1, 1);
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
void semicircle(int xc,int yc,int rad){

  int xCenter=xc,yCenter=yc,r=rad;
  int x=0,y=r;
  int d = 3 - 2*r;    // = 1 - r
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 1 ,1, 1);
  while(x<=y){
    drawPixel(xCenter+x,yCenter+y);
    drawPixel(xCenter+y,yCenter+x);  //find other points by symmetry
    drawPixel(xCenter-x,yCenter+y);
//    drawPixel(xCenter+y,yCenter-x);
  //  drawPixel(xCenter-x,yCenter-y);
   // drawPixel(xCenter-y,yCenter-x);
   // drawPixel(xCenter+x,yCenter-y);
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

void line(int x1,int y1,int x2,int y2){

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
void mainsquare(int l, int w){
/*   MAIN SQUARE */
        line(-(w/2),-(l/2),-(w/2),(l/2));
        line(-(w/2),-(l/2),(w/2),-(l/2));
        line((w/2),-(l/2),(w/2),(l/2));
        line((w/2),(l/2),-(w/2),(l/2));
}
void armleft(int l, int w){
	line(-(w/2)-(w/15)-(w/5),-(l/2),-(w/2)-(w/15)-(w/5),(l/2));
        line(-(w/2)-(w/15)-(w/5),-(l/2),-(w/2)-(w/15),-(l/2));
        line(-(w/2)-(w/15),-(l/2),-(w/2)-(w/15),(l/2));
        line(-(w/2)-(w/15),(l/2),-(w/2)-(w/15)-(w/5),(l/2));
}
void armright(int l, int w){
	line((w/2)+(w/15)+(w/5),-(l/2),(w/2)+(w/15)+(w/5),(l/2));
        line((w/2)+(w/15)+(w/5),-(l/2),(w/2)+(w/15),-(l/2));
        line((w/2)+(w/15),-(l/2),(w/2)+(w/15),(l/2));
        line((w/2)+(w/15),(l/2),(w/2)+(w/15)+(w/5),(l/2));
}
void legleft(int l, int w){
	line(-(w/2)+(w/8),-(l/2)-(l/15),-(w/2)+(w/8),-(l/2)-(l/4)-(l/15));
        line(-(w/2)+(w/8),-(l/2)-(l/4)-(l/15),-(w/2)+(w/4),-(l/2)-(l/4)-(l/15));
        line(-(w/2)+(w/4),-(l/2)-(l/4)-(l/15),-(w/2)+(w/4),-(l/2)-(l/15));
        line(-(w/2)+(w/4),-(l/2)-(l/15),-(w/2)+(w/8),-(l/2)-(l/15));
}
void legright(int l, int w){
	line((w/2)-(w/8),-(l/2)-(l/15),(w/2)-(w/8),-(l/2)-(l/4)-(l/15));
        line((w/2)-(w/8),-(l/2)-(l/4)-(l/15),(w/2)-(w/4),-(l/2)-(l/4)-(l/15));
        line((w/2)-(w/4),-(l/2)-(l/4)-(l/15),(w/2)-(w/4),-(l/2)-(l/15));
        line((w/2)-(w/4),-(l/2)-(l/15),(w/2)-(w/8),-(l/2)-(l/15));
}
void semi(int l, int w){
	semicircle(0,(l/2)+(l/15),(w/2));
        line(-(w/2),(l/2)+(l/15),(w/2),(l/2)+(l/15));
}
void eyes(int l, int w){
	circle(-(w/4),(l/2)+(l/15)+(w/6),(w/16));
        circle((w/4),(l/2)+(l/15)+(w/6),(w/16));
}
void draw(int l, int w){
	/*   MAIN SQUARE */
	line(-(w/2),-(l/2),-(w/2),(l/2));
	line(-(w/2),-(l/2),(w/2),-(l/2));
	line((w/2),-(l/2),(w/2),(l/2));
	line((w/2),(l/2),-(w/2),(l/2));

	/*ARM LEFT */
	glPushMatrix();
	glTranslatef(-(w/2)-(w/15),l/2,0);
	glRotatef(angle,1,0,0);
	glTranslatef(w/2+w/15,-(l/2),0);
	line(-(w/2)-(w/15)-(w/5),-(l/2),-(w/2)-(w/15)-(w/5),(l/2));
	line(-(w/2)-(w/15)-(w/5),-(l/2),-(w/2)-(w/15),-(l/2));
	line(-(w/2)-(w/15),-(l/2),-(w/2)-(w/15),(l/2));
	line(-(w/2)-(w/15),(l/2),-(w/2)-(w/15)-(w/5),(l/2));
	//glTranslatef(w/2+w/15,-(l/2),0);
	glPopMatrix();

	/*	ARM RIGHT	*/
	glPushMatrix();
	glTranslatef(-(w/2)-(w/15),l/2,0);
        glRotatef(angle,1,0,0);
        glTranslatef(w/2+w/15,-(l/2),0);
	line((w/2)+(w/15)+(w/5),-(l/2),(w/2)+(w/15)+(w/5),(l/2));
	line((w/2)+(w/15)+(w/5),-(l/2),(w/2)+(w/15),-(l/2));
	line((w/2)+(w/15),-(l/2),(w/2)+(w/15),(l/2));
	line((w/2)+(w/15),(l/2),(w/2)+(w/15)+(w/5),(l/2));
	glPopMatrix();
	angle+=0.09;

	/* LEG LEFT  */
	line(-(w/2)+(w/8),-(l/2)-(l/15),-(w/2)+(w/8),-(l/2)-(l/4)-(l/15));
	line(-(w/2)+(w/8),-(l/2)-(l/4)-(l/15),-(w/2)+(w/4),-(l/2)-(l/4)-(l/15));
	line(-(w/2)+(w/4),-(l/2)-(l/4)-(l/15),-(w/2)+(w/4),-(l/2)-(l/15));
	line(-(w/2)+(w/4),-(l/2)-(l/15),-(w/2)+(w/8),-(l/2)-(l/15));

	/* LEG RIGHT  */
	line((w/2)-(w/8),-(l/2)-(l/15),(w/2)-(w/8),-(l/2)-(l/4)-(l/15));
	line((w/2)-(w/8),-(l/2)-(l/4)-(l/15),(w/2)-(w/4),-(l/2)-(l/4)-(l/15));
	line((w/2)-(w/4),-(l/2)-(l/4)-(l/15),(w/2)-(w/4),-(l/2)-(l/15));
	line((w/2)-(w/4),-(l/2)-(l/15),(w/2)-(w/8),-(l/2)-(l/15));

	/* SEMI-CIRCLE  */
	semicircle(0,(l/2)+(l/15),(w/2));
	line(-(w/2),(l/2)+(l/15),(w/2),(l/2)+(l/15));

	/* EYES */ 
	circle(-(w/4),(l/2)+(l/15)+(w/6),(w/16));
	circle((w/4),(l/2)+(l/15)+(w/6),(w/16));

	
	

}
void clear(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(rot==0){
	mainsquare(l,w);
	armleft(l,w);
	armright(l,w);
	legleft(l,w);
	legright(l,w);
	semi(l,w);
	eyes(l,w);}
	else{
		draw(l,w);
	}
	 glFlush();
}
/*void mouseDisplay(){
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
}*/
void keyboard(unsigned char key, int x, int y)
{
        //-------- spin --------
        if(key=='r')
        {
                //setSpin(1.0,0.0,0.0);
                //glutPostRedisplay();
		//clear();
		rot=1;
		myDisplay();
		printf("%d",2);
        }
        else if(key=='s')
        {
//                setSpin(0.0,1.0,0.0);
//                glutPostRedisplay();
                  
//		  mouseDisplay();
		rot=0;
		myDisplay();
        }
        else if(key=='i')
        {
//                setSpin(0.0,0.0,1.0);
//                glutPostRedisplay();
 	          //r1=100;r2=400;
		  //printf("%s","2");
		  //glutPostRedisplay();
		  l+=10;w+=5;
		  myDisplay();
        }
        else if(key=='d')
        {
//                setSpin(1.0,1.0,1.0);
 //               glutPostRedisplay();
        
        //-------- spin --------
        //-------- zoom --------
		l-=10;w-=5;
                  myDisplay();
	}
        else if(key=='e')
        {
  //              translate_z++;
    //            glutPostRedisplay();
    		exit(0);
        }
        else if(key=='t')
        {
      //          translate_z--;
        //        glutPostRedisplay();
		glTranslate(l+10,0,0);
		myDisplay();
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

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Android");
    init();
    glutDisplayFunc(myDisplay);
//    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0,Timer,0);
    glutMainLoop();
    return 0;
}
