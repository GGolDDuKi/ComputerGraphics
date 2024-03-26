#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH  600
#define HEIGHT  400
#define Point 100

GLfloat Red = 0.0f;
GLfloat Green = 0.0f;
GLfloat Blue = 0.0f;

GLboolean Spin = 0;		
GLboolean SpinDir = 1;		//스핀 방향 확인(0일 경우 시계방향)

GLint index = 0;
GLfloat angle = 0.0f;
float MousePos[Point][2];
GLint StarNum = 0;

unsigned char PALETTE[10][3] = {
	{255, 255, 0},		//YELLOW
	{255, 255, 255},	//WHITE
	{0, 255, 255},		//CYAN
	{255, 0, 255},		//PURPLE
	{192, 192, 192},		//LIGHT GRAY
	{128, 128, 128},		//DARK GRAY
	{128, 0, 0},		//DARK RED
	{0, 128, 0},		//DARK GREEN
	{0, 0, 128},		//DARK BLUE
	{0, 0, 0}		//BLACK
};

void display() {
	Red = PALETTE[index][0] / 255.0f;
	Green = PALETTE[index][1] / 255.0f;
	Blue = PALETTE[index][2] / 255.0f;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(Red, Green, Blue);

	if (StarNum > 0) {
		for (int i = 0; i < StarNum; i++) {
			glPushMatrix();
			glTranslatef(MousePos[i][0] * 4, MousePos[i][1] * 4, 0.0f);
			if (Spin == 1) {
				glRotatef(angle, 0.0f, 0.0f, 1.0f);
			}
			glTranslatef(-MousePos[i][0], -MousePos[i][1], 0.0f);
			
			glBegin(GL_TRIANGLES);
			glVertex3f(MousePos[i][0] + 0.0f, MousePos[i][1] - 0.6f, 0.0f);
			glVertex3f(MousePos[i][0] - 0.5f, MousePos[i][1] + 0.2f, 0.0f);
			glVertex3f(MousePos[i][0] + 0.5f, MousePos[i][1] + 0.2f, 0.0f);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(MousePos[i][0] + 0.0f, MousePos[i][1] + 0.5f, 0.0f);
			glVertex3f(MousePos[i][0] - 0.5f, MousePos[i][1] - 0.3f, 0.0f);
			glVertex3f(MousePos[i][0] + 0.5f, MousePos[i][1] - 0.3f, 0.0f);
			glEnd();

			glTranslatef(-MousePos[i][0], -MousePos[i][1], 0.0f);
			glPopMatrix();
		}
	}
	if (StarNum > 1) {
		glColor3f(1, 1, 1);
		for (int i = 0; i < StarNum; i++) {
			glPushMatrix();
			glBegin(GL_LINE_STRIP);
			glVertex3f(MousePos[i][0] * 4, MousePos[i][1] * 4, 0.0f);
		}
		glEnd();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void reshape() {
	glViewport(0, 0, WIDTH, HEIGHT);
	float WidthFactor = (float)WIDTH / 150.0;
	float HeightFactor = (float)HEIGHT / 100.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
}

void idleProcess() {
	if (SpinDir == 0) {
		angle += 0.5;
	}
	else {
		angle -= 0.5;
	}
	if (angle > 360.0) angle = 0.0f;
	else if (angle < -360.0) angle = 0.0f;

	glutPostRedisplay();
}

void mouseProcess(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//별 생성, 별 사이 직선거리의 선 연결
		float X = (2.0 * x / WIDTH) - 1.0;
		float Y = -((2.0 * y / HEIGHT) - 1.0);
		MousePos[StarNum][0] = X;
		MousePos[StarNum][1] = Y;
		printf("%.2f %.2f 위치에 ", MousePos[StarNum][0], MousePos[StarNum][1]);
		StarNum++;
		display();
		printf("마우스 좌클릭을 누르셨습니다.\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//모든 별이 회전, 재 클릭시마다 회전 방향 반전
		if (Spin == 0) {
			Spin = 1;
		}
		printf("마우스 우클릭을 누르셨습니다.\n");
		if (SpinDir == 0) {
			SpinDir = 1;
			angle = 0.0f;
		}
		else {
			SpinDir = 0;
			angle = 0.0f;
		}
		//TranslateCenter();
		glutIdleFunc(idleProcess);
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		printf("마우스 휠을 누르셨습니다.\n");
		//모든 별의 색 변경
		if (++index >= 9) {
			index = 0;
			glClear(GL_COLOR_BUFFER_BIT);
		}
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Mouse Star Event");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseProcess);
	glutMainLoop();

	return 0;
}