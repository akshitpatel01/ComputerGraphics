
#include <GL/glut.h>
#include<stdio.h>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

typedef struct {
    GLfloat x, y;
} Point;

const GLint WIN_LEFT_BIT = 0x01;
const GLint WIN_RIGHT_BIT = 0x02;
const GLint WIN_BOTTOM_BIT = 0x04;
const GLint WIN_TOP_BIT = 0x08;

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
void init_graph(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, SCREEN_WIDTH, -500, SCREEN_HEIGHT);
}

void close_graph() {
    glutMainLoop();
}

void swap_points(Point *p1, Point *p2) {
    Point t = *p1;
    *p1 = *p2;
    *p2 = t;
}

void swap_codes(GLint *x, GLint *y) {
    GLint t = *x;
    *x = *y;
    *y = t;
}

GLint inside(GLint code) {
    return !code;
}

GLint accept(GLint code1, GLint code2) {
    return !(code1 | code2);
}

GLint reject(GLint code1, GLint code2) {
    return code1 & code2;
}

GLint encode(Point p1, Point win_min, Point win_max) {
    GLint code = 0x00;
    printf("%d %d\n", p1.x,p1.y);
    if (p1.x < win_min.x) code |= WIN_LEFT_BIT;
    if (p1.x > win_max.x) code |= WIN_RIGHT_BIT;
    if (p1.y < win_min.y) code |= WIN_BOTTOM_BIT;
    if (p1.y > win_max.y) code |= WIN_TOP_BIT;
    return code;
}

GLint round(GLfloat a) {
    return (GLint) (a + 0.5f);
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
void line_clip(Point p1, Point p2, Point win_min, Point win_max) {
    GLint code1, code2;
    GLint done = 0, plot_line = 0;
    GLfloat m = 0;
    if (p1.x != p2.x) {
        m = (p2.y - p1.y) / (p2.x - p1.x);
    }
    while (!done) {
	    code1 = encode(p1, win_min, win_max);
	    code2 = encode(p2, win_min, win_max);
	    printf("enter loop %d %d\n",code1,code2);
	    if (accept(code1, code2)) {
			printf("if\n");
		    done = 1;
		    plot_line = 1;
	    } else if (reject(code1, code2)) {
		    done = 1;
	    } else {
		    if (inside(code1)) {
			    swap_points(&p1, &p2);
			    swap_codes(&code1, &code2);
		    }
		    if (code1 & WIN_LEFT_BIT) {
			    p1.y += (win_min.x - p1.x) * m;
			    p1.x = win_min.x;
		    } else if (code1 & WIN_RIGHT_BIT) {
			    p1.y += (win_max.x - p1.x) * m;
			    p1.x = win_max.x;
		    } else if (code1 & WIN_BOTTOM_BIT) {
			    if (p1.x != p2.x)
				    p1.x += (win_min.y - p1.y) / m;
			    p1.y = win_min.y;
		    } else if (code1 & WIN_TOP_BIT) {
			    if (p1.x != p2.x)
				    p1.x += (win_max.y - p1.y) / m;
			    p1.y = win_max.y;
		    }
	    }
    }

    if (plot_line) {
	printf("exec\n");
        glColor3f(1, 0, 0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(round(p1.x), round(p1.y));
        glVertex2i(round(p2.x), round(p2.y));
        glEnd();
        glFlush();
    }
}

void draw_window(Point win_min, Point win_max) {

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(round(win_min.x), round(win_min.y));
    glVertex2i(round(win_min.x), round(win_max.y));
    glVertex2i(round(win_max.x), round(win_max.y));
    glVertex2i(round(win_max.x), round(win_min.y));
    glEnd();
    glFlush();
}

void init_clip() {
    glClear(GL_COLOR_BUFFER_BIT);

    Point win_min = {200, 200};
    Point win_max = {-200,-200};
    draw_window(win_min, win_max);
    Point p1 = {0, 0};
    Point p2 = {100, 100};
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2i(round(p1.x), round(p1.y));
    glVertex2i(round(p2.x), round(p2.y));
    glEnd();
//    line(0,300,0,300);
    line_clip(p1, p2, win_min, win_max);
   // glFlush();	
}

int main(int argc, char **argv) {
    init_graph(argc, argv);
    glutDisplayFunc(init_clip);
    close_graph();
    return EXIT_SUCCESS;
}
