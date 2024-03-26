#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void display() {
	glFlush();
}

void DrawStar() {
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.67, 0.0);
	glVertex3f(2.82, 1.62, 0.0);
	glVertex3f(1.75, 0.13, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.08, 0.32, 0.0);
	glVertex3f(1.07, 2.17, 0.0);
	glVertex3f(2.85, -0.21, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.09, -0.8, 0.0);
	glVertex3f(1.09, 2.17, 0.0);
	glVertex3f(2.17, 0.7, 0.0);
	glEnd();

	glFlush();
}

void DrawBigCircle() {    //���׸����Լ� 
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	float radius = 4.0f;
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14f / 180;
		glVertex3f(-3.1f + cos(angle) * radius, 0.5f + sin(angle) * radius, 0);
	}
	glEnd();
	glFlush();
}

void DrawSmallCircle() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	float radius = 3.2f;
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14f / 180;
		glVertex3f(-2.1f + cos(angle) * radius, 0.5f + sin(angle) * radius, 0);
	}
	glEnd();
	glFlush();
}

void DrawAll() {
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//ū �� �׸���
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	float radius = 4.0f;
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14f / 180;
		glVertex3f(-3.1f + cos(angle) * radius, 0.5f + sin(angle) * radius, 0);
	}
	glEnd();

	//���� �� �׸���
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	radius = 3.2f;
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14f / 180;
		glVertex3f(-2.1f + cos(angle) * radius, 0.5f + sin(angle) * radius, 0);
	}
	glEnd();

	//�� �׸���
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.67, 0.0);
	glVertex3f(2.82, 1.62, 0.0);
	glVertex3f(1.75, 0.13, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.08, 0.32, 0.0);
	glVertex3f(1.07, 2.17, 0.0);
	glVertex3f(2.85, -0.21, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.09, -0.8, 0.0);
	glVertex3f(1.09, 2.17, 0.0);
	glVertex3f(2.17, 0.7, 0.0);
	glEnd();

	glFlush();
}

void init() {
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void reshape(int new_w, int new_h) {
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 50.0;
	float HeightFactor = (float)new_h / 50.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
}

void keyboardProcess(unsigned char key, int x, int y) {
	switch (key){
	case '1':
		printf("1�� �����̽��ϴ�.\n");
		DrawBigCircle();
		break;
	case '2':
		printf("2�� �����̽��ϴ�.\n");
		DrawSmallCircle();
		break;
	case '3':
		printf("3�� �����̽��ϴ�.\n");
		DrawStar();
		break;
	case 13:
		printf("���͸� �����̽��ϴ�.\n");
		DrawAll();
		break;
	}
}

void mouseProcess(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("���� ���콺 ��ư�� Ŭ���Ͽ����ϴ�.\n");
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Turkiye Flag");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardProcess);
	glutMouseFunc(mouseProcess);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}