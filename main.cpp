
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include <stdlib.h>
#include "RGBpixmap.cpp"
float degreeX = 0.0 ;
float degreeY = 0.0 ;
float degreeZ = 0.0 ;
float degreeX1 = 0.0 ;
float degreeY1 = 0.0 ;
float degreeZ1 = 0.0 ;
float alpha=0.0;
float beta=0.0;
float gamma=0.0;
float theta=(22.0/7.0)/180.0;
float d=1.0;
int CLight,lflag=-1,lcount;
static int slices = 16;
static int stacks = 16;
int width=1500;
int height=750;
double eyeX = 0 ;
double eyeY = 0 ;
double eyeZ = -25 ;
double centerX = 0 ;
double centerY = 0 ;
double centerZ = 0 ;
double upX = 0 ;
double upY = 1 ;
double upZ = 0 ;
float zoom=1;
float oX=0; float oY=0; float oZ=-2;
float oxx=0; float oyy=0; float ozz=0;
float Pp=0; float Yy=0; float Rr=0;
float scale=0;
float scale1=0;
float tranx=0; float trany=0; float tranz=0;

float hx=0;float hy=1;float hz=0;
/* GLUT callback Handlers */
RGBpixmap pics[10];
const GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 2.0f, 0.3f, 0.0f };

const GLfloat light_ambient1[]  = { 0.1f, 0.2f, 0.2f, 1.0f };
const GLfloat light_diffuse1[]  = { 0.8f, 0.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = {-25.0f, 200.0f, -25.0f, 0.0f };

const GLfloat no_mat_light[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
const GLfloat no_shininess[] = { 0.0f };
const GLfloat low_shininess[] = { 5.0f };

const GLfloat mat_ambient[]    = {0.7f, 0.0f, 0.7f, 1.0f};
const GLfloat mat_ambient_color[]    = {0.0f, 0.0f, 8.0f, 1.0f};
const GLfloat mat_diffuse[]    = {0.0f, 0.0f, 0.8f, 1.0f};
const GLfloat mat_specular[]   = { 0.0f, 1.0f, 1.0f, 1.0f };

const GLfloat mat_ambient2[]    = { 0.3f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_ambient_color2[]    = {0.5f, 0.0f, 0.5f, 1.0f};
const GLfloat mat_diffuse2[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular2[]   = { 1.0f, 0.0f, 1.0f, 1.0f };

const GLfloat mat_ambient3[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_ambient_color3[]    = {0.8f, 0.8f, 0.2f, 1.0f};
const GLfloat mat_diffuse3[]    = {0.1f, 0.5f, 0.8f, 1.0f};
const GLfloat mat_specular3[]   = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat mat_ambient_color1[]    = { 0.0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse1[]    = { 0.0f, 0.8f, 0.0f, 1.0f };
const GLfloat mat_specular1[]   = { 0.0f, 1.0f, 0.0f, 1.0f };

void scaleIt(GLfloat sx, GLfloat sy, GLfloat sz){
    GLfloat s[16]={sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1};
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(s);


}


static float fovy = 60;
static void cameraProjectionMatrix()
{
    GLfloat ar = (GLfloat) width / (GLfloat) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, ar, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
}

void init(){
    pics[0].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\wood floor 2.bmp");
    pics[0].setTexture(2);
    pics[1].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\brick.bmp");
    pics[1].setTexture(3);
    pics[5].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\brick short.bmp");
    pics[5].setTexture(7);
    pics[6].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\brick up.bmp");
    pics[6].setTexture(8);
    pics[2].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\table top.bmp");
    pics[2].setTexture(4);
    pics[3].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\brushed.bmp");
    pics[3].setTexture(5);
    pics[4].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\art.bmp");
    pics[4].setTexture(6);
    pics[7].readBMPFile("I:\\4-2\\graphics lab\\final_project1\\scene1.bmp");
    pics[7].setTexture(9);

}

GLfloat xComplexMin = -0.25, xComplexMax = 1.25;
GLfloat yComplexMin = -0.75, yComplexMax = 0.75;

GLfloat oldx = -0.7, oldy = 0.5;
GLfloat lftx = oldx - 0.1, lfty = oldy - 0.1;
GLfloat rhtx = oldx + 0.1, rhty = oldy + 0.1;

int Depth=2;

void drawkoch(GLfloat dir, GLfloat len, GLint iter)
{
	GLdouble dirRad = 0.0174533 * dir;
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);


	lftx = (newX - 0.1)<lftx ? newX - 0.1 : lftx;
	lfty = (newY - 0.1)<lfty ? newY - 0.1 : lfty;
	rhtx = (newX + 0.1)>rhtx? newX + 0.1:rhtx;
	rhty = (newY + 0.1)>rhty ? newY + 0.1 : rhty;


	if (iter == 0) {
		glVertex2f(oldx, oldy);
		glVertex2f(newX, newY);
		oldx = newX;
		oldy = newY;
	}
	else {
		iter--;


        drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
		dir -= 120.0;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
	}
}
//
//
//
void KochCurve(int depth) {
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);

	drawkoch(0.0, 0.05, depth);
	//glColor3f(.0, 1.0, 0.0);
	drawkoch(+72.0, 0.05, depth);
	//glColor3f(0.0, 0.0, 1.0);
	drawkoch(+144.0, 0.05, depth);
	//glColor3f(1.0, 1.0, 0.0);
	drawkoch(216.0, 0.05, depth);
	//glColor3f(0.0, 1.0, 1.0);
	drawkoch(288.0, 0.05, depth);

	glEnd();
	glFlush();
}


double r = 5;
int level=0;
/* GLUT callback Handlers */

double cal_h()
{
    double s = (3.0*r) / 2.0;
    double temp = s *(s-r)*(s-r)*(s-r);
    temp = sqrt(temp);
    temp = (temp*2.0)/r;
    return temp;
}

static void _tsquare_recursive( GLdouble r,int level)
{
    double h = cal_h();


    if (level <= 0)
        glVertex3d(-r/2.0, h, 0);        /// right top vertex
        glVertex3d(-r, 0, 0);        /// left top vertex
        glVertex3d(-r/2.0, -h, 0);        /// left bottom vertex
        glVertex3d(r/2.0, -h, 0);
        glVertex3d(r,0.0, 0);
        glVertex3d(r/2.0, h, 0);         /// right bottom vertex
        return;

    _tsquare_recursive(r/3,level-1);
   /* GLdouble hBy4 = (top-down)/4.0;
    GLdouble wBy4 = (right-left)/4.0;

    GLdouble x[2] = {left,right};
    GLdouble y[2] =  {down,top};

    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            _tsquare_recursive(y[i]+hBy4, y[i]-hBy4, x[j]-wBy4, x[j]+wBy4,level-1);
        }
    }*/
}
void bottom(){
    glBegin(GL_QUADS);
    //glColor3d(1,0,0);

    glTexCoord2f(0.0, 0.0);glVertex3f(0.0,0.0,2.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(2.0,0.0,2.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(2.0,2.0,2.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(0.0,2.0,2.0);

    //glColor3d(0,1,0);
    glTexCoord2f(0.0, 0.0);glVertex3f(2.0,0.0,2.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(2.0,0.0,0.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(2.0,2.0,0.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(2.0,2.0,2.0);

    //glColor3d(0,0,1);
    glTexCoord2f(0.0, 0.0);glVertex3f(2.0,0.0,0.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(0.0,2.0,0.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(2.0,2.0,0.0);


    //glColor3d(0,1,1);
    glTexCoord2f(0.0, 0.0);glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(0.0,0.0,2.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(0.0,2.0,2.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(0.0,2.0,0.0);

    //glColor3d(1,1,0);
    glTexCoord2f(0.0, 0.0);glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(2.0,0.0,0.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(2.0,0.0,2.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(0.0,0.0,2.0);


    //glColor3d(1,0,1);
    glTexCoord2f(0.0, 0.0);glVertex3f(0.0,2.0,0.0);
    glTexCoord2f(0.0, 1.0);glVertex3f(0.0,2.0,2.0);
    glTexCoord2f(1.0, 1.0);glVertex3f(2.0,2.0,2.0);
    glTexCoord2f(1.0, 0.0);glVertex3f(2.0,2.0,0.0);
    glEnd();

}
void rounded_side(float n,float r){/*width*/
    float k=0;
    for(int i=0;i<20*n;i++){
    glPushMatrix();
    glTranslated(k ,0,0);
    glutSolidSphere(r,30,30);
    glPopMatrix();
    k+=0.05;
    }
}
void font_piece(){
    glPushMatrix();

    glRotated(-90,0,0,1);
    rounded_side(.5,.3);
    glPopMatrix();
    }
void room(){
    glPushMatrix();
        glTranslated(-2.5,-2,0);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        scaleIt(1.5,2,.2);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
        glTranslated(4.5,-2,0);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        scaleIt(1.5,2,.2);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-9.5,-3,6);
        glBindTexture(GL_TEXTURE_2D,9);
        glEnable(GL_TEXTURE_2D);
        scaleIt(11,4,.2);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslated(.5,-2,0);

        glBindTexture(GL_TEXTURE_2D,7);
        glEnable(GL_TEXTURE_2D);
        scaleIt(2,.6,.2);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
        glTranslated(.5,1,0);
        scaleIt(2,.5,.2);
        glBindTexture(GL_TEXTURE_2D,8);
        glEnable(GL_TEXTURE_2D);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    /**/glPushMatrix();
        glTranslated(7.5,-2,0);
        glRotated(90,0,1,0);
        scaleIt(3,2,.2);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
        glTranslated(7.445,-1,-2);
        glRotated(90,0,1,0);
        scaleIt(1,1,.2);
        glBindTexture(GL_TEXTURE_2D,6);
        glEnable(GL_TEXTURE_2D);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.5,-2 ,-6);
        glRotated(90,01,0,0);
        scaleIt(5,3,.1);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-2.5,1.2 ,-1.8);
        glRotated(90,01,0,0);
        scaleIt(2,1,.05);
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        bottom();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-1,1.5 ,-1.8);
        //glRotated(90,01,0,0);
        //scaleIt(2,1,.05);
        glBindTexture(GL_TEXTURE_2D,5);
        glEnable(GL_TEXTURE_2D);
        glutSolidTeapot(.5);
    glPopMatrix();

glPushMatrix();

        glTranslated(2.5,-1.8 ,-5);
        glRotated(90,1,0,0);
        scaleIt(.5,.5,2);
        KochCurve(Depth);
        //glBegin(GL_POLYGON);

        //_tsquare_recursive(r, level);
    glEnd();
    glPopMatrix();
}
void legs(){
    glPushMatrix();
        glTranslated(-3,-5,-6.5);
        scaleIt(.2,4,.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        //glColor3d(.1,1,.3);
        glTranslated(-3,-5,-3.5);
        scaleIt(.2,4,.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-3,-6.9,-5);
        scaleIt(.2,.2,3);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(3,-5,-3.5);
        scaleIt(.2,4,.2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(3,-6.9,-5);
        scaleIt(.2,.2,3);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        //glColor3d(.1,1,.3);
        glTranslated(3,-5,-6.5);
        scaleIt(.2,4,.2);
        glutSolidCube(1);
    glPopMatrix();
}
void table(){
    glPushMatrix();
        glTranslated(0.5,-.5,-5);
        glBindTexture(GL_TEXTURE_2D,4);
        glEnable(GL_TEXTURE_2D);
        scaleIt(2,.05,1.5);
        bottom();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.5,0.45,-.5);
        glBindTexture(GL_TEXTURE_2D,5);
        glEnable(GL_TEXTURE_2D);
        scaleIt(.5,.3,.6);
        legs();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void jack(){
    glPushMatrix();
    scaleIt(6,1,1);
    glutSolidSphere(1,30,30);
    glPopMatrix();

    glPushMatrix();
    scaleIt(1,6,1);
    glutSolidSphere(1,30,30);
    glPopMatrix();

    glPushMatrix();
    scaleIt(1,1,6);
    glutSolidSphere(1,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.5,0,0);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6.5,0,0);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,6.5,0);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-6.5,0);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,6.5);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,-6.5);
    glutSolidSphere(1.2,30,30);
    glPopMatrix();
}

void rounded_edge(){/*height,width,depth*/
    glPushMatrix();
    glTranslated(0,-3,0);
    scaleIt(12,2.7,1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();

    glTranslated(6,-1.6,0);
    glRotated(-90,0,0,1);
    rounded_side(2.9,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,-1.6,0);
    rounded_side(12,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,-4.5,0);
    rounded_side(12,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,-1.6,0);
    glRotated(-90,0,0,1);
    rounded_side(2.9,.5);
    glPopMatrix();

}

void carside(){

    glPushMatrix();
    glTranslated(0,-3,0);
    scaleIt(12,2.7,1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2,-.4,0);
    scaleIt(5,2.5,.95);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.55,-.5,0);
    glRotated(-10,0,0,1);
    scaleIt(.25,1.35,.5);
    glutSolidCube(1.9);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,-3,0);
    glRotated(-10,0,0,1);
    scaleIt(.25,1.35,.5);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.75,-1.75,0);
    glRotated(50,0,0,1);
    scaleIt(1.9,2.1,.5);
    glutSolidCube(1.9);
    glPopMatrix();/**/

    glPushMatrix();
    glTranslated(6,-1.6,0);
    glRotated(-90,0,0,1);
    rounded_side(2.9,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,-1.6,0);
    rounded_side(12,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6.6,-4.5,0);
    rounded_side(12.6,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.6,1,0);
    rounded_side(5,.5);
    glPopMatrix();/**/

    glPushMatrix();
    glTranslated(-6.6,-4.5,0);
    glRotated(79,0,0,1);
    rounded_side(3,.5);
    glPopMatrix();

}

void darkness(int a){
    glBegin(GL_TRIANGLE_FAN);
    //glColor3d(1,1,0);
    for(int i=0; i<360; i++)
    {
        float t=i*theta*a;
        glVertex3f(cos(t),sin(t),2.5);
    }
    glEnd();
    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(0,0,2.5);
    glScaled(1,.1,.1);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(0,0,2.5);
    glScaled(.1,1,.1);
    glutSolidCube(1);
    glPopMatrix();
}

double angle=0.0;
double n=0;
void car(){
    glPushMatrix();
    glColor3d(.5,.2,.5);
    glTranslated(0,0,-1);
    glScaled(1,1,6.5);
    carside();
    glPopMatrix();

    glPushMatrix();
    glColor3d(.5,.2,.5);
    glTranslated(-5.0,-1.5,2);
    glRotated(79,0,0,1);
    rounded_side(2.5,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5.0,-1.5,-4);
    glRotated(79,0,0,1);
    rounded_side(2.5,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.2,.9,2);
    glRotated(-40,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.2,.9,-4);
    glRotated(-40,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.2,-2.8,2);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5,-2.8,2);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.5,-2.8,2);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.2,-2.8,-4);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5,-2.8,-4);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.5,-2.8,-4);
    glRotated(90,0,0,1);
    rounded_side(3.7,.2);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.15,0.15,0.15);
    glTranslated(3,-4.5,2);
    glScaled(1,1,1.5);
    glutSolidTorus(.5,1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(3,-4.5,2.5);
    glScaled(.5,.5,.5);
    glutSolidTorus(.2,1.1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.15,0.15,0.15);
    glTranslated(3,-4.5,-4);
    glScaled(1,1,1.5);
    glutSolidTorus(.5,1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(3,-4.5,-4.5);
    glScaled(.5,.5,.5);
    glutSolidTorus(.2,1.1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.15,0.15,0.15);
    glTranslated(-4,-4.5,2);
    glScaled(1,1,1.5);
    glutSolidTorus(.5,1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(-4,-4.5,2.5);
    glScaled(.5,.5,.5);
    glutSolidTorus(.2,1.1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.15,0.15,0.15);
    glTranslated(-4,-4.5,-4);
    glScaled(1,1,1.5);
    glutSolidTorus(.5,1,10,30);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.3,0.3,0.3);
    glTranslated(-4,-4.5,-4.5);
    glScaled(.5,.5,.5);
    glutSolidTorus(.2,1.1,10,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,-4.5,0);
    glColor3d(0,0,0);
    n=glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        angle=n*90;
        glRotated(-angle,0,0,1);
    darkness(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4,-4.5,0);
    glColor3d(0,0,0);
    n=glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    angle=n*90;
    glRotated(-angle,0,0,1);
    darkness(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,-4.5,-7);
    glColor3d(0,0,0);
    n=glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    angle=n*90;
    glRotated(-angle,0,0,1);
    darkness(-1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4,-4.5,-7);
    glColor3d(0,0,0);
    n=glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    angle=n*90;
    glRotated(-angle,0,0,1);
    darkness(-1);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.2,0.2,0.2);
    glTranslated(6.25,-4,-1);
    glScaled(1,.7,10);
    font_piece();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6.6,-2.5,-1);
    glRotated(-11,0,0,1);
    glScaled(1,1.5,6);
    font_piece();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6.8,-4,-1);
    glRotated(-11,0,0,1);
    glScaled(1,.7,10);
    font_piece();
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.3,-2,-3);
    glRotated(90,0,1,0);
    glScaled(1,1,2);
    glutSolidTorus(.1,.5,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.3,-2,1);
    glRotated(90,0,1,0);
    glScaled(1,1,2);
    glutSolidTorus(.1,.5,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.2,-2,-3);
    glutSolidSphere(.5,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6.2,-2,1);
    glutSolidSphere(.5,30,30);
    glPopMatrix();


}

void scene(){
    glPushMatrix();
        //glTranslated(-5,0,-32);
        //scaleIt(5,5,5);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_light);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat_light);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_light);
        glMaterialfv(GL_FRONT, GL_SHININESS,no_mat_light);
        room();
    glPopMatrix();

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_light);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat_light);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_light);
        glMaterialfv(GL_FRONT, GL_SHININESS,no_mat_light);
        glTranslated(0,-.2,0);
        table();
    glPopMatrix();

    glPushMatrix();
        glTranslated(3.2,-.15,-3.8);
        scaleIt(.07,.07,.07);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
        glMaterialfv(GL_FRONT, GL_SHININESS,low_shininess);
        car();
    glPopMatrix();
    glPushMatrix();
        glTranslated(2,-.21,-3.8);
        glRotated(55,1,0,1);
        scaleIt(.07,.07,.07);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
        glMaterialfv(GL_FRONT, GL_SHININESS,high_shininess);
        //glutSolidSphere(1,50,50);
        jack();
    glPopMatrix();
}
void room1(){
    glPushMatrix();
        glTranslated(-2.5,-2,0);
        scaleIt(1.5,2,.2);
        bottom();
    glPopMatrix();
    glPushMatrix();
        glTranslated(4.5,-2,0);
        scaleIt(1.5,2,.2);
        bottom();
    glPopMatrix();
    glPushMatrix();
        glTranslated(.5,-2,0);
        scaleIt(2,.5,.2);
        bottom();
    glPopMatrix();
    glPushMatrix();
        glTranslated(.5,1,0);
        scaleIt(2,.5,.2);
        bottom();
    glPopMatrix();

    glPushMatrix();
        glTranslated(7.5,-2,0);
        glRotated(90,0,1,0);
        scaleIt(3,2,.2);
        bottom();
    glPopMatrix();

    glPushMatrix();
        glTranslated(7.5,-2,0);
        glRotated(90,0,1,0);
        scaleIt(3,2,.2);
        bottom();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.5,-2 ,-6);
        glRotated(90,01,0,0);
        scaleIt(5,3,.1);
        bottom();
    glPopMatrix();

    glPushMatrix();

        glTranslated(2.5,-1.8 ,-5);
        glRotated(90,1,0,0);
        scaleIt(.5,.5,2);
        KochCurve(Depth);
        //glBegin(GL_POLYGON);

        //_tsquare_recursive(r, level);
    glEnd();
    glPopMatrix();
}

void table1(){
    glPushMatrix();
        glTranslated(0.5,-.5,-5);
        scaleIt(2,.05,1.5);
        bottom();
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.5,0.45,-.5);
        scaleIt(.5,.3,.6);
        legs();
    glPopMatrix();
}

void scene1(){
    glPushMatrix();
        //glTranslated(-5,0,-32);
        //glScaled(5,5,5);
        room1();
    glPopMatrix();

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient_color1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular1);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glTranslated(0,-.2,0);
        table1();
    glPopMatrix();

    glPushMatrix();
        glTranslated(3.2,-.15,-3.8);
        scaleIt(.07,.07,.07);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
        glMaterialfv(GL_FRONT, GL_SHININESS,low_shininess);
        car();
    glPopMatrix();
    glPushMatrix();
        glTranslated(2,-.21,-3.8);
        glRotated(55,1,0,1);
        scaleIt(.07,.07,.07);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
        glMaterialfv(GL_FRONT, GL_SHININESS,high_shininess);
        jack();
    glPopMatrix();
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    //glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    cameraProjectionMatrix();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();
        glViewport(0,0,width/2,height);
        glLoadIdentity();
        //gluLookAt(0 ,0,-25,0,0,0,0,1,0);
        gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
        glTranslated(-2.5+tranx,0+trany,-10+tranz);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS,no_shininess);
        glRotated(degreeY,0,1,0);
        glRotated(degreeX,1,0,0);
        glRotated(degreeZ,0,0,1);
        scaleIt(1+scale,1+scale,1+scale);
        scene();
    glPopMatrix();
eyeX=0;eyeY=0;eyeZ=-25;upY=1;
    glPushMatrix();
        glViewport(width/2,0,width/2,height);
        glLoadIdentity();
        //gluLookAt(0 ,0,-25,0,0,0,0,1,0);
        gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
        glTranslated(-2.5+tranx,0+trany,-10+tranz);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS,no_shininess);
        glRotated(degreeY1,0,1,0);
        glRotated(degreeX1,1,0,0);
        glRotated(degreeZ1,0,0,1);
        scaleIt(1+scale1,1+scale1,1+scale1);
        scene1();
    glPopMatrix();



    glFlush();

    glutSwapBuffers();
}

int flag=0;
int rflag=0;
int dflag=0;
double dist=0;

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case ' ': exit(0); break;
        case 'd':lflag=1; break;
        case 'e':lflag=0; break;
        case 't': flag=2; break;
        case 'r': flag=1; break;
        case 'E': flag=3; break;
        case 's': flag=4; break;
        case 'o': flag=5; break;
        case 'p': flag=6; break;
        case 'u': flag=7; break;
        case 'k': Depth+=1; break;
        case 'h': Depth-=1; break;
        case 'f':
        fovy -= 5;
        cameraProjectionMatrix();
        break;
    case 'v':
        fovy += 5;
        cameraProjectionMatrix();
        break;
    }
    /* space for exit.
       d for disable lights.
       e for enable lights.
      (after e or d 0-7 for enabling or disabling light 0 to 7 respectively.)
       t for translating in 3 axis.
      (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       r for rotating in 3 axis.
      (0 for all following operation working on left scene, 1 for right scene.
       x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       Z for rotating in positive z axis. k for rotating in negative z axis.)
       E for eye rotation in 3 axis.
      (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       s for scaling.
      (0 for all following operation working on left scene, 1 for right scene.
       + for increasing size/zoom in.
       - for decreasing size/zoom out.)
       o for rotating keeping eye in center.
       (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       p for roll pitch yaw rotation.
      (q for roll
       p for pitch
       w for yaw)
       h for increasing depth of koch carpet on floor.
       k for decreasing depth of koch carpet on floor.
    */
    if (lflag==1){
            switch (key){
                case '0': CLight = GL_LIGHT0;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '1': CLight = GL_LIGHT1;

                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '2': CLight = GL_LIGHT2;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '3': CLight = GL_LIGHT3;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '4': CLight = GL_LIGHT4;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '5': CLight = GL_LIGHT4;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '6': CLight = GL_LIGHT6;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                case '7': CLight = GL_LIGHT7;
                glLightfv(CLight, GL_AMBIENT,  no_mat_light);
                glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
                glLightfv(CLight, GL_SPECULAR, no_mat_light);
                glLightfv(CLight, GL_POSITION, no_mat_light);
                break;
                 }}
    if (lflag==0){
            switch (key){
                case '0': CLight = GL_LIGHT0;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient1);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse1);
                glLightfv(CLight, GL_SPECULAR, light_specular1);
                glLightfv(CLight, GL_POSITION, light_position1);
                break;
                case '1': CLight = GL_LIGHT1;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;

                case '3': CLight = GL_LIGHT3;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;
                case '2': CLight = GL_LIGHT2;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;
                case '4': CLight = GL_LIGHT4;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;
                case '5': CLight = GL_LIGHT5;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;
                case '6': CLight = GL_LIGHT6;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;
                case '7': CLight = GL_LIGHT7;
                glEnable(CLight);
                glEnable(GL_NORMALIZE);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_LIGHTING);
                glLightfv(CLight, GL_AMBIENT,  light_ambient);
                glLightfv(CLight, GL_DIFFUSE,  light_diffuse);
                glLightfv(CLight, GL_SPECULAR, light_specular);
                glLightfv(CLight, GL_POSITION, light_position);
                break;


            }}

    if (flag==4){
        switch (key)
        {
            case '0': rflag =0 ; break;
            case '1': rflag=1 ; break;
        }
        if(rflag==0){
            switch (key)
            {
            case '+':
                scale+=.2;
                break;
            case '-':
                scale-=.2;
                break;
            }
        }
        if(rflag==1){
            switch (key)
            {
            case '+':
                scale1+=.2;
                break;
            case '-':
                scale1-=.2;
                break;
            }
        }
    }
    if (flag==1)
    {
        switch (key)
        {
            case '0': rflag =0 ; break;
            case '1': rflag=1 ; break;
        }
        if(rflag==0){
            switch (key){
            case 'y': degreeY +=2.5 ; break;
            case 'j': degreeY -=2.5 ; break;
            case 'x': degreeX +=2.5; break;
            case 'i': degreeX -=2.5; break;
            case 'Z': degreeZ +=2.5 ; break;
            case 'k': degreeZ -=2.5 ; break;
        }
        }
        if(rflag==1){
            switch (key)
        {
            case 'y': degreeY1 +=2.5 ; break;
            case 'j': degreeY1 -=2.5 ; break;
            case 'x': degreeX1 +=2.5; break;
            case 'i': degreeX1 -=2.5; break;
            case 'Z': degreeZ1+=2.5 ; break;
            case 'k': degreeZ1 -=2.5 ; break;
        }
        }
    }

    if (flag==2)
    {
        switch (key)
        {
            case 'y':
            trany +=.5 ;
            break;
        case 'j':
            trany -=.1 ;
            break;
        case 'x':
            tranx +=.1 ;
            break;
        case 'i':
            tranx -=.1 ;
            break;
        case 'z':
            tranz +=.1 ;
            break;
        case 'k':
            tranz -=.1 ;
            break;
        }
    }
    if (flag==3)
    {
        switch (key)
        {
            case 'x':
            eyeX+=1;
            break;
        case 'i':
            eyeX-=1;
            break;
        case 'y':
            eyeY+=1;
            break;
        case 'j':
            eyeY-=1;
            break;
        case 'z':
            eyeZ+=1;
            break;
        case 'k':
            eyeZ-=1;
            break;

        }
    }
    if (flag==5)
    {
        switch (key)
        {
            case 'x':
            centerX+=1;
            break;
        case 'i':
            centerX-=1;
            break;
        case 'y':
            centerY+=1;
            break;
        case 'j':
            centerY-=1;
            break;
        case 'z':
            centerZ+=1;
            break;
        case 'k':
            centerZ-=1;
            break;

        }
    }

    if (flag==7)
    {
        switch (key)
        {
            case 'x':
            upX+=1;
            break;
        case 'i':
            upX-=1;
            break;
        case 'y':
            upY+=1;
            break;
        case 'j':
            upY-=1;
            break;
        case 'z':
            upZ+=1;
            break;
        case 'k':
            upZ-=1;
            break;

        }
    }
    if (flag==6){
        switch (key)
        {
        case 'q':
            alpha+=5;
            upX=5*cos(alpha*theta)-5*sin(alpha*theta);
            upY=5*cos(alpha*theta)+5*sin(alpha*theta);
            break;
        case 'w':
            beta+=5;
            centerX=5*cos(beta*theta)+5*sin(beta*theta);
            centerZ=-5*cos(beta*theta)+5*sin(beta*theta);
            break;
        case 'p':
            gamma+=5;
            centerY=2*cos(gamma*theta)+2*sin(gamma*theta);
            centerZ=2*cos(gamma*theta)-2*sin(gamma*theta);
            break;
        }
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}



/* Program entry point */

int main(int argc, char *argv[])
{
    /*space for exit.
       d for disable lights.
       e for enable lights.
      (after e or d 0-7 for enabling or disabling light 0 to 7 respectively.)
       t for translating in 3 axis.
      (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       r for rotating in 3 axis.
      (0 for all following operation working on left scene, 1 for right scene.
       x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       Z for rotating in positive z axis. k for rotating in negative z axis.)
       E for eye rotation in 3 axis.
      (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       s for scaling.
      (0 for all following operation working on left scene, 1 for right scene.
       + for increasing size/zoom in.
       - for decreasing size/zoom out.)
       o for rotating keeping eye in center.
       (x for rotating in positive x axis. i for rotating in negative x axis.
       y for rotating in positive y axis. j for rotating in negative y axis.
       z for rotating in positive z axis. k for rotating in negative z axis.)
       p for roll pitch yaw rotation.
      (q for roll
       p for pitch
       w for yaw)
       h for increasing depth of koch carpet on floor.
       k for decreasing depth of koch carpet on floor.*/
    cout<<"TYPE\nspace for exit.\n\nd for disable lights.\ne for enable lights."
      <<"\n(after e or d 0-7 for enabling or disabling light 0 to 7 respectively.)\n"
       <<"\nt for translating in 3 axis."
      <<"\n(x for rotating in positive x axis. i for rotating in negative x axis."
       <<"\ny for rotating in positive y axis. j for rotating in negative y axis."
       <<"\nz for rotating in positive z axis. k for rotating in negative z axis.)\n"
       <<"\nr for rotating in 3 axis."
      <<"\n(0 for all following operation working on left scene, 1 for right scene."
       <<"\nx for rotating in positive x axis. i for rotating in negative x axis."
       <<"\ny for rotating in positive y axis. j for rotating in negative y axis."
       <<"\nZ for rotating in positive z axis. k for rotating in negative z axis.)\n"
       <<"\nE for eye rotation in 3 axis."
      <<"\n(x for rotating in positive x axis. i for rotating in negative x axis."
       <<"\ny for rotating in positive y axis. j for rotating in negative y axis."
       <<"\nz for rotating in positive z axis. k for rotating in negative z axis.)\n"
       <<"\ns for scaling."
      <<"\n(0 for all following operation working on left scene, 1 for right scene."
       <<"\n+ for increasing size/zoom in."
       <<"\n- for decreasing size/zoom out.)\n"
       <<"\no for rotating keeping eye in center."
       <<"\n(x for rotating in positive x axis. i for rotating in negative x axis."
       <<"\ny for rotating in positive y axis. j for rotating in negative y axis."
       <<"\nz for rotating in positive z axis. k for rotating in negative z axis.)\n"
       <<"\np for roll pitch yaw rotation."
      <<"\n(q for roll"
       <<"\np for pitch"
       <<"\nw for yaw)\n"
       <<"\nh for increasing depth of koch carpet on floor."
       <<"\nk for decreasing depth of koch carpet on floor.";
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);



    CLight = GL_LIGHT0;
    glEnable(CLight);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(CLight, GL_AMBIENT,  no_mat_light);
    glLightfv(CLight, GL_DIFFUSE,  no_mat_light);
    glLightfv(CLight, GL_SPECULAR, no_mat_light);
    glLightfv(CLight, GL_POSITION, no_mat_light);
init();


    glutMainLoop();

    return EXIT_SUCCESS;
}
