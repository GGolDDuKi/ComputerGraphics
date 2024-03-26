#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14

void DrawCircle(float radius, float r, float g, float b, int half) {    //���׸����Լ� 
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	if (half == 0) {        //�� 
		for (int i = 0; i < 360; i++) {
			float degInRad = i * PI / 180;
			glVertex3f(cos(degInRad) * radius, sin(degInRad) * radius, 0);
		}
	}
	else if (half == 1) {        //�ݿ� 
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
	DrawCircle(1 / 2., 0.894, 0.114, 0.2, 0);    //������ū��(panton 186C���� rgb�� �ٲۻ�����) 
	glPushMatrix();
	glRotated(180.0f, 1.0, 0, 0);            //�ݿ��� �ؿ������� �׸������� x������ 180��ȸ�� 
	glRotated(33.690068f, 0, 0, 1.0);		 //z������ 33.690068�� ȸ�� 
	DrawCircle(1 / 2., 0.0, 0.201, 0.502, 1);		//�Ʒ��� �Ķ���ū�ݿ�
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.218f, 0.125f, 0.0);
	DrawCircle(1/4., 0.894, 0.114, 0.2, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.218f, -0.125f, 0.0);
	DrawCircle(1/4., 0.0, 0.201, 0.502, 0);
	glPopMatrix();

	glPushMatrix();        //�� 
	glRotated((-33.690068), 0, 0, 1);            //�߽����� 33.690068�� ȸ�� 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //�������� �߽�(0.0)���� 0.75��ŭ ������ ������ �̵�
	glRotated(90, 0, 0, 1);                    //�߽��࿡�� ���� ���η� �׷����ϱ⶧���� 90�� ȸ��
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //�������� ������ �̵� 
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //�� 
	glRotated(33.690068, 0, 0, 1);            //�߽����� 33.690068�� ȸ�� 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //�������� �߽�(0.0)���� 0.75��ŭ ������ ������ �̵�
	glRotated(90, 0, 0, 1);                    //�߽��࿡�� ���� ���η� �׷����ϱ⶧���� 90�� ȸ��
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //�������� ������ �̵� 
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //�� 
	glRotated(-146.309932, 0, 0, 1);            //�߽����� 33.690068�� ȸ�� 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //�������� �߽�(0.0)���� 0.75��ŭ ������ ������ �̵�
	glRotated(90, 0, 0, 1);                    //�߽��࿡�� ���� ���η� �׷����ϱ⶧���� 90�� ȸ��
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //�������� ������ �̵� 
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //�� 
	glRotated(146.309932, 0, 0, 1);            //�߽����� 33.690068�� ȸ�� 
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);    //�������� �߽�(0.0)���� 0.75��ŭ ������ ������ �̵�
	glRotated(90, 0, 0, 1);                    //�߽��࿡�� ���� ���η� �׷����ϱ⶧���� 90�� ȸ��
	DrawTwoLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);        //�������� ������ �̵� 
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