#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int year = 0;
int day = 0;

//�¾� RGB
float sunR = 1.0;
float sunG = 1.0;
float sunB = 1.0;

//�� RGB
float moonR = 1.0;
float moonG = 1.0;
float moonB = 1.0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	//�¾� ����
	glPushMatrix();
	glColor3f(sunR, sunG, sunB);
	glutSolidSphere(1.0, 20, 16);

	//�� ����
	glColor3f(moonR, moonG, moonB);
	glRotatef(year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef(day, 0.0, 1.0, 0.0);
	glutSolidSphere(0.2, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
}

void popupMenu(int value) {
	switch (value) {
	case 1:		//������
		printf("�¾� ������ ���������� �����մϴ�.\n");
		sunR = 1.0; sunG = 0.0; sunB = 0.0;
		glutPostRedisplay();
		break;
	case 2:		//�����
		printf("�¾� ������ ��������� �����մϴ�.\n");
		sunR = 1.0; sunG = 1.0; sunB = 0.0;
		glutPostRedisplay();
		break;
	case 3:		//�Ͼ��
		printf("�� ������ �Ͼ������ �����մϴ�.\n");
		moonR = 1.0; moonG = 1.0; moonB = 1.0;
		glutPostRedisplay();
		break;
	case 4:		//�Ķ���
		printf("�� ������ �Ķ������� �����մϴ�.\n");
		moonR = 0.0; moonG = 0.0; moonB = 1.0;
		glutPostRedisplay();
		break;
	case 99:
		printf("OpenGL ���α׷��� �����մϴ�.\n");
		exit(0);
		break;
	}
}

void reshape(int new_w, int new_h) {
	glViewport(0, 0, new_w, new_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)new_w / (GLfloat)new_h, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		day = (day + 10) % 360;
		break;
	case 'D':
		day = (day - 10) % 360;
		break;
	case 'y':
		year = (year + 5) % 360;
		break;
	case 'Y':
		year = (year - 5) % 360;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Planet + PopupMenu");

	init();

	//�¾� ����޴� �߰�
	int submenu1 = glutCreateMenu(popupMenu);
	glutAddMenuEntry("������", 1);
	glutAddMenuEntry("�����", 2);

	//�� ����޴� �߰�
	int submenu2 = glutCreateMenu(popupMenu);
	glutAddMenuEntry("�Ͼ��", 3);
	glutAddMenuEntry("�Ķ���", 4);

	//���θ޴��� ����޴� �߰�
	glutCreateMenu(popupMenu);
	glutAddSubMenu("SUN", submenu1);
	glutAddSubMenu("MOON", submenu2);
	glutAddMenuEntry("Exit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}