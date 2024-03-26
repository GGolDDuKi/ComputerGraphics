#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14

void DrawCircle(float radius, float r, float g, float b, int half) {    //원그리는함수 
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	if (half == 0) {        //원 
		for (int i = 0; i < 360; i++) {
			float degInRad = i * PI / 180;
			glVertex3f(cos(degInRad) * radius, sin(degInRad) * radius, 0);
		}
	}
	else if (half == 1) {        //반원 
		for (int i = 0; i < 180; i++) {
			float degInRad = i * PI / 180;
			glVertex3f(cos(degInRad) * radius, sin(degInRad) * radius, 0);
		}
	}
	glEnd();
}

void DrawLine() {
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f(1 / 4., 0, 0);
	glVertex3f(1 / 4., 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();
}

void DrawTwoLine() {
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f(1 / 4., 0, 0);
	glVertex3f(1 / 4., 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f((-1 / 50.), 0, 0);
	glVertex3f(1 / 50., 0, 0);
	glVertex3f(1 / 50., 1 / 12., 0);
	glVertex3f((-1 / 50.), 1 / 12., 0);
	glEnd();
}

void display() {
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle(1 / 2., 0.894, 0.114, 0.2, 0);    //빨간색큰원(panton 186C값을 rgb로 바꾼색적용) 
	glPushMatrix();
	glRotated(180.0f, 1.0, 0, 0);            //반원을 밑에쪽으로 그리기위해 x축으로 180도회전 
	glRotated(33.690068f, 0, 0, 1.0);		 //z축으로 33.690068도 회전 
	DrawCircle(1 / 2., 0.0, 0.201, 0.502, 1);		//아래쪽 파란색큰반원
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.218f, 0.125f, 0.0);
	DrawCircle(1/4., 0.894, 0.114, 0.2, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.218f, -0.125f, 0.0);
	DrawCircle(1/4., 0.0, 0.201, 0.502, 0);
	glPopMatrix();

	glPushMatrix();        //건 
	glRotated((-33.690068), 0, 0, 1);            //중심축을 33.690068도 회전 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //기준점을 중심(0.0)에서 0.75만큼 떨어진 곳으로 이동
	glRotated(90, 0, 0, 1);                    //중심축에서 부터 가로로 그려야하기때문에 90도 회전
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //위쪽으로 기준점 이동 
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //건 
	glRotated(33.690068, 0, 0, 1);            //중심축을 33.690068도 회전 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //기준점을 중심(0.0)에서 0.75만큼 떨어진 곳으로 이동
	glRotated(90, 0, 0, 1);                    //중심축에서 부터 가로로 그려야하기때문에 90도 회전
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //위쪽으로 기준점 이동 
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //건 
	glRotated(-146.309932, 0, 0, 1);            //중심축을 33.690068도 회전 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //기준점을 중심(0.0)에서 0.75만큼 떨어진 곳으로 이동
	glRotated(90, 0, 0, 1);                    //중심축에서 부터 가로로 그려야하기때문에 90도 회전
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //위쪽으로 기준점 이동 
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //건 
	glRotated(146.309932, 0, 0, 1);            //중심축을 33.690068도 회전 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //기준점을 중심(0.0)에서 0.75만큼 떨어진 곳으로 이동
	glRotated(90, 0, 0, 1);                    //중심축에서 부터 가로로 그려야하기때문에 90도 회전
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //위쪽으로 기준점 이동 
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glFlush();
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void reshape(int new_w, int new_h) {
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 400.0;
	float HeightFactor = (float)new_h / 400.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Korean Flag");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}