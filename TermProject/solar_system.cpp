#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//----- �߰� ��� -----
//�� �༺ Ŭ�� �� ���� ������ ����

//�༺�� ���� �ֱ�
float mercuryYear = 0.0;    //����
float venusYear = 0.0;		//�ݼ�
float earthYear = 0.0;		//����
float moonYear = 0.0;		//��
float marsyear = 0.0;		//ȭ��
float jupiterYear = 0.0;		//��
float saturnYear = 0.0;		//�伺
float uranusYear = 0.0;		//õ�ռ�
float neptuneYear = 0.0;		//�ؿռ�

//�༺�� ���� �ֱ�
float sunDay = 0.0f;		//�¾�
float mercuryDay = 0.0f;		//����
float venusDay = 0.0f;		//�ݼ�
float earthDay = 0.0f;		//����
float moonDay = 0.0f;		//��
float marsDay = 0.0f;		//ȭ��
float jupiterDay = 0.0f;		//��
float saturnDay = 0.0f;		//�伺
float uranusDay = 0.0f;		//õ�ռ�
float neptuneDay = 0.0f;		//�ؿռ�

//���� ������ ���� ����/�ƿ� ��ǥ�� �������� ����
bool up = false;
bool front = true;
bool side = false;

//ī�޶��� ������ ��ȯ�ϴ� ����
float camAngle = 0.0;
float camX = 0.0;
float camY = 0.0;
float camZ = 0.0;

//�༺�� ȸ���� �����ϴ� ����
float yearSpeed = 1.0f;		//ȸ�� �ӵ�
float spin = 1.0f;		//ȸ�� on/off

//ī�޶� ��ġ�� �����ϴ� ����
float ex = 0.1f, ey = 0.1f, ez = 0.1f;

//������ ���� �ȷ�Ʈ
GLint index = 0;
GLfloat Red = 0.0f;
GLfloat Green = 0.0f;
GLfloat Blue = 0.0f;

unsigned char PALETTE[9][3] =
{
	{ 255, 255, 255 },
	{ 0, 255, 255 },
	{ 255, 0, 255 },
	{ 192, 192, 192 },
	{ 128, 128, 128 },
	{ 128, 0, 0 },
	{ 0, 128, 0 },
	{ 0, 0, 128 },
	{ 0, 0, 0 },
};

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);		//���� ���۸� �ʱ�ȭ
	glShadeModel(GL_SMOOTH);		//���̵� ���� SMOOTH�� ����
}

void CreateCircle(float radius) {		//�������� ���� ���� �˵��� �׷��ִ� �Լ�
	float angle = 0.0f;
	glLineWidth(1.0);		//���� ���� ����
	glColor3f(0.2f, 0.2f, 0.2f);		//�˵� ���� ����
	glBegin(GL_LINE_LOOP);		//���ӵǴ� �� �׸���
	for (int i = 0; i < 100; i++) {		//���� �ε巴�� ����ǵ��� ���� Ƚ�� �ݺ�
		angle = 2 * 3.14 * i / 100;
		glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));		//radius* cos(angle), 0.0, radius* sin(angle) ������ �������� ���� ��� ������ ����
	}
	glEnd();		//�� �׸��� ����
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//���� ���ۿ�, ���� ���� �ʱ�ȭ

	//�༺ ���� ������ ����� RGB���� ����
	Red = PALETTE[index][0] / 255.0f;
	Green = PALETTE[index][1] / 255.0f;
	Blue = PALETTE[index][2] / 255.0f;

	glEnable(GL_DEPTH_TEST);		//���� �׽�Ʈ�� Ȱ��ȭ
	glClearDepth(1.0f);		//���� ������ �ʱⰪ�� 1.0���� �ʱ�ȭ
	//glInitNames();		

	//�༺ ���� �˵� �׸���
	CreateCircle(1.5);		//������ ���� �˵�
	CreateCircle(2.25);		//�ݼ��� ���� �˵�
	CreateCircle(3.0);		//������ ���� �˵�
	CreateCircle(3.9);		//ȭ���� ���� �˵�
	CreateCircle(5.0);		//���� ���� �˵�
	CreateCircle(6.5);		//�伺�� ���� �˵�
	CreateCircle(7.5);		//õ�ռ��� ���� �˵�
	CreateCircle(8.5);		//�ؿռ��� ���� �˵�

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glColor3f(Red, Green, Blue);  //�¾��� ���� ����
	glRotatef(sunDay, 0.0, 1.0, 0.0);		//�¾��� ����
	glutWireSphere(1.0, 40, 32);  //�¾� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(mercuryYear, 0.0, 1.0, 0.0);		//������ ����
	glTranslatef(1.5, 0.0, 0.0);		//�¾����κ��� 1.5��ŭ ������ ����
	glRotatef(mercuryDay, 0.0, 1.0, 0.0);		//������ ����
	glColor3f(0.0, 0.0, 1.0);  //������ ���� ����
	glutWireSphere(0.1, 20, 16);  //���� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(venusYear, 0.0, 1.0, 0.0);		//�ݼ��� ����
	glTranslatef(2.25, 0.0, 0.0);		//�¾����κ��� 2.25��ŭ ������ ����
	glRotatef(venusDay, 0.0, 1.0, 0.0);		//�ݼ��� ����
	glColor3f(0.0, 0.0, 1.0);  //�ݼ��� ���� ����
	glutWireSphere(0.25, 20, 16);  //�ݼ� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(earthYear, 0.0, 1.0, 0.0);		//������ ����
	glTranslatef(3.0, 0.0, 0.0);		//�¾����κ��� 3.0��ŭ ������ ����
	glRotatef(earthDay, 0.0, 1.0, 0.0);			//������ ����
	glColor3f(0.0, 0.0, 1.0);  //������ ���� ����
	glutWireSphere(0.25, 20, 16);  //���� �׸���
	//���� ������ �������� �����ϱ� ������ ���⼭ glPopMatrix()�� ������ ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(moonYear, 0.0, 1.0, 0.0);		//���� ����
	glTranslatef(0.4, 0.0, 0.0);		//�����κ��� 0.4��ŭ ������ ����
	glRotatef(moonDay, 0.0, 1.0, 0.0);		//���� ����
	glColor3f(0.7, 0.7, 0.7);  //���� ���� ����
	glutWireSphere(0.06, 10, 8);  //�� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(marsyear, 0.0, 1.0, 0.0);		//ȭ���� ����
	glTranslatef(3.9, 0.0, 0.0);		//�¾����κ��� 3.9��ŭ ������ ����
	glRotatef(marsDay, 0.0, 1.0, 0.0);		//ȭ���� ����
	glColor3f(0.0, 0.0, 1.0);  //ȭ���� ���� ����
	glutWireSphere(0.125, 20, 16);  //ȭ�� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(jupiterYear, 0.0, 1.0, 0.0);		//���� ����
	glTranslatef(5.0, 0.0, 0.0);		//�¾����κ��� 5.0��ŭ ������ ����
	glRotatef(jupiterDay, 0.0, 1.0, 0.0);		//���� ����
	glColor3f(0.0, 0.0, 1.0);  //���� ���� ����
	glutWireSphere(0.6, 20, 16);  //�� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(saturnYear, 0.0, 1.0, 0.0);		//�伺�� ����
	glTranslatef(6.5, 0.0, 0.0);		//�¾����κ��� 6.5��ŭ ������ ����
	glRotatef(saturnDay, 0.0, 1.0, 0.0);		//�伺�� ����
	glColor3f(0.0, 0.0, 1.0);  //�伺�� ���� ����
	glutWireSphere(0.45, 20, 16);  //�伺 �׸���
	gluQuadricDrawStyle(gluNewQuadric(), GLU_FILL);		//Quadric ��ü�� ����, ��Ÿ���� ä���� ����
	glRotatef(90.0, 1.0, 0.0, 0.0);		//x������ 90����ŭ ȸ��
	gluDisk(gluNewQuadric(), 0.55, 0.7, 20, 15);		//���� ���� 0.55, ���� ���� 0.7�� ��ũ ������Ʈ ����
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(uranusYear, 0.0, 1.0, 0.0);		//õ�ռ��� ����
	glTranslatef(7.5, 0.0, 0.0);		//�¾����κ��� 7.5��ŭ ������ ����
	glRotatef(uranusDay, 0.0, 1.0, 0.0);		//õ�ռ��� ����
	glColor3f(0.0, 0.0, 1.0);  //õ�ռ��� ���� ����
	glutWireSphere(0.3, 20, 16);  //õ�ռ� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glPushMatrix();		//��ȯ ��� ���ÿ� ����
	glRotatef(neptuneYear, 0.0, 1.0, 0.0);		//�ؿռ��� ����
	glTranslatef(8.5, 0.0, 0.0);		//�¾����κ��� 8.5��ŭ ������ ����
	glRotatef(neptuneDay, 0.0, 1.0, 0.0);		//�ؿռ��� ����
	glColor3f(0.0, 0.0, 1.0);  //�ؿռ��� ���� ����
	glutWireSphere(0.3, 20, 16);  //�ؿռ� �׸���
	glPopMatrix();		//���� ��ȯ ��ķ� ����

	glutSwapBuffers();		//���۸� ��ü
}

void camera() {		//ī�޶��� ��ȯ�� ������ display���ִ� �Լ�
	glMatrixMode(GL_MODELVIEW);		//��ȯ ��� ��带 �𵨺� ��� ���� ����
	glLoadIdentity();		//��ȯ ����� ���� ��ķ� �ʱ�ȭ
	gluLookAt(ex, ey, ez, 0.1, 0.0, 0.0, 1.0, 1.5, 0.0);		//ī�޶� ��ġ, ����, �Ӹ����� ����
	glRotatef(camAngle, camX, camY, camZ);		//ī�޶� ȸ��
	glutPostRedisplay();		//ȭ���� �ٽ� display��
}

void popupMenu(int value) {
	srand((unsigned int)time(NULL));		//���� ���� ����
	int random = rand() % 3;		//0~2�� ���� �������� ���� ����
	switch (value) {		//������ �޴��� ���� �ɼ� ����
	case 1:
		glutSetWindowTitle("�⺻ ����");		//�޴� ���� ��, ������ Ÿ��Ʋ�� '�⺻ ����'���� ��ȯ ��
		printf("�⺻ �������� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		ex = 0.1; ey = 0.1; ez = 0.1;		//ī�޶� ��ġ ����
		side = false; up = false; front = true;		//������ ���� ���� ����
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//ī�޶� ������ ���õ� ������ �ʱ�ȭ
		camera();		//ī�޶� �缳��
		break;		//����ġ�� ����
	case 2:
		glutSetWindowTitle("�� ����");		//�޴� ���� ��, ������ Ÿ��Ʋ�� '�� ����'���� ��ȯ ��
		printf("�� �������� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		ex = 0.1; ey = 10.0; ez = 0.1;		//ī�޶� ��ġ ����
		side = false; up = true; front = false;		//������ ���� ���� ����
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//ī�޶� ������ ���õ� ������ �ʱ�ȭ
		camera();		//ī�޶� �缳��
		break;		//����ġ�� ����
	case 3:
		glutSetWindowTitle("�� ����");		//�޴� ���� ��, ������ Ÿ��Ʋ�� '�� ����'���� ��ȯ ��
		printf("�� �������� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		ex = 10.0; ey = 0.1; ez = 0.1;		//ī�޶� ��ġ ����
		side = true; up = false; front = false;		//������ ���� ���� ����
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//ī�޶� ������ ���õ� ������ �ʱ�ȭ
		camera();		//ī�޶� �缳��
		break;		//����ġ�� ����
	case 4:
		glutSetWindowTitle("�� ����");		//�޴� ���� ��, ������ Ÿ��Ʋ�� '�� ����'���� ��ȯ ��
		printf("�� �������� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		ex = 0.1; ey = 0.1;	ez = 10.0;		//ī�޶� ��ġ ����
		side = false; up = false; front = true;		//������ ���� ���� ����
		camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;		//ī�޶� ������ ���õ� ������ �ʱ�ȭ
		camera();		//ī�޶� �缳��
		break;		//����ġ�� ����
	case 5:
		glutSetWindowTitle("������ ����");		//�޴� ���� ��, ������ Ÿ��Ʋ�� '������ ����'���� ��ȯ ��
		printf("������ �������� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		//random������ ���� ����, �������� ī�޶� ��ġ, ���� ���� �� ��ȯ�� ������ display��
		if (random == 0) {		//�� ����
			ex = 10.0; ey = 0.1; ez = 0.1;
			side = true; up = false; front = false;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		else if (random == 1) {		//�� ����
			ex = 0.1; ey = 10.0; ez = 0.1;
			side = false; up = true; front = false;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		else if (random == 2) {		//�� ����
			ex = 0.1; ey = 0.1; ez = 10.0;
			side = false; up = false; front = true;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		break;		//����ġ�� ����
	case 99:
		printf("OpenGL ���α׷��� �����մϴ�.\n");		//�޴� ���� ��, �ش� ���ڿ� ���
		exit(0);		//���α׷� ����
		break;		//����ġ�� ����
	}
}

void normal_keyboard(unsigned char key, int x, int y) {		//�Ϲ� Ű�� �Է��� �޴� �Լ�
	switch (key) {		//�Է��� Ű�� ���� �ɼ� ����
	case '=':  // '+' Ű�� ���� ��� ���� �ӵ� ���� / +�� Shift�� ������ �ϱ� ������ =�� �����Ͽ���
		yearSpeed = yearSpeed + 0.1f;		//���� �ӵ��� 0.1��ŭ ����
		printf("���� �ӵ��� �������ϴ�.\n");
		break;		//����ġ�� ����
	case '-':  // '-' Ű�� ���� ��� ���� �ӵ� ����
		yearSpeed = yearSpeed - 0.1f;		//���� �ӵ��� 0.1��ŭ ����
		printf("���� �ӵ��� �������ϴ�.\n");
		break;		//����ġ�� ����
	case 32:		//�����̽��ٸ� ������ ȸ�� on/off
		if (spin == 1.0f) {		//spin������ 1�̸� 0���� �ٲٸ� ���� �ߴ�
			spin = 0.0f;
			printf("������ ����ϴ�.\n");
			break;		//����ġ�� ����
		}
		else if (spin == 0.0f) {		//spin������ 0�̸� 1�� �ٲٸ� ���� ����
			spin = 1.0f;
			printf("������ �����մϴ�.\n");
			break;		//����ġ�� ����
		}
	}
	glutPostRedisplay();  // ȭ�� �ٽ� �׸���
}

void idle() {		//���� ���¿� ����Ǵ� �Լ�
	//���� - ����: 0.25, �ݼ� : 0.6, ���� : 1.0, ȭ�� : 1.9, �� : 0.07
	//����(0.5)�� �������� �� ������ ����
	//�񼺺��ʹ� �¾�� �༺ �����ֱ��� ������ ����
	mercuryYear += (0.5 * (1.0 / 0.25)) * yearSpeed * spin;
	if (mercuryYear > 360.0) mercuryYear = 0.0;
	venusYear += (0.5 * (1.0 / 0.6)) * yearSpeed * spin;
	if (venusYear > 360.0) venusYear = 0.0;
	earthYear += (0.5 * (1.0)) * yearSpeed * spin;
	if (earthYear > 360.0) earthYear = 0.0;
	moonYear += (0.5 * (1.0 / 0.07)) * yearSpeed * spin;
	if (moonYear > 360.0) moonYear = 0.0;
	marsyear += (0.5 * (1.0 / 1.9)) * yearSpeed * spin;
	if (marsyear > 360.0) marsyear = 0.0;
	jupiterYear += (0.5 * (1.0 / 11.9)) * yearSpeed * spin;
	if (jupiterYear > 360.0) jupiterYear = 0.0;
	saturnYear += (0.5 * (1.0 / 29.5)) * yearSpeed * spin;
	if (saturnYear > 360.0) saturnYear = 0.0;
	uranusYear += (0.5 * (1.0 / 84.0)) * yearSpeed * spin;
	if (uranusYear > 360.0) uranusYear = 0.0;
	neptuneYear += (0.5 * (1.0 / 165.0)) * yearSpeed * spin;
	if (neptuneYear > 360.0) neptuneYear = 0.0;

	//����
	//���� - https://astro.kasi.re.kr/learning/pageView/5116
	//����(1.0)�� �������� ������ �����Ͽ����ϴ�.
	sunDay += 0.04f;
	if (sunDay > 360.0) sunDay = 0.0;
	mercuryDay += 0.017f;
	if (mercuryDay > 360.0) mercuryDay = 0.0;
	venusDay -= 0.004f;
	if (venusDay < -360.0) venusDay = 0.0;
	earthDay += 1.0f;
	if (earthDay > 360.0) earthDay = 0.0;
	moonDay += 0.036f;
	if (moonDay > 360.0) moonDay = 0.0;
	marsDay += 1.0f;
	if (marsDay > 360.0) marsDay = 0.0;
	jupiterDay += 2.43f;
	if (jupiterDay > 360.0) jupiterDay = 0.0;
	saturnDay += 2.27f;
	if (saturnDay > 360.0) saturnDay = 0.0;
	uranusDay += 1.4f;
	if (uranusDay > 360.0) uranusDay = 0.0;
	neptuneDay += 1.6f;
	if (neptuneDay > 360.0) neptuneDay = 0.0;
	
	glutPostRedisplay();		// ȭ�� �ٽ� �׸���
}

void reshape(int w, int h) {		//������ ũ�Ⱑ ����� �� ȣ���� �Լ�
	glViewport(0, 0, w, h);		//����Ʈ ����
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();		//��ȯ ����� ���� ��ķ� �ʱ�ȭ
	gluPerspective(90, (GLfloat)w / (GLfloat)h, 1.0, 20.0);			//�þ߰�, ��, �� ����

	glMatrixMode(GL_MODELVIEW);		//��ȯ ��� ��带 �𵨺� ��� ���� ����
	glLoadIdentity();		//��ȯ ����� ���� ��ķ� �ʱ�ȭ
	gluLookAt(0.1, 0.1, 0.1, 0.1, 0.0, 0.0, 1.0, 1.5, 0.0);		//�⺻ ī�޶� ����
	glutPostRedisplay();		//ȭ���� �ٽ� display��
}		

void special_keyboard(int key, int x, int y) {		//Ư��Ű �Է��� �޴� �Լ�
	switch (key) {		//�Է��� Ư��Ű�� ���� �ɼ� ����
	case 101:		//�� ����Ű -> ����
		if (front == true)		//�� ������ ���
			ez -= 0.1f;
		else if (up == true)		//�� ������ ���
			ey -= 0.1f;
		else if (side == true)		//�� ������ ���
			ex -= 0.1f;
		printf("Zoom In\n");
		camera();		//ȭ�� �缳��
		break;		//����ġ�� ����
	case 103:		//�Ʒ� ����Ű -> �ܾƿ�
		if (front == true)		//�� ������ ���
			ez += 0.1f;
		else if (up == true)		//�� ������ ���
			ey += 0.1f;
		else if (side == true)		//�� ������ ���
			ex += 0.1f;
		printf("Zoom Out\n");
		camera();		//ȭ�� �缳��
		break;		//����ġ�� ����
	case 100:		//���� ����Ű -> ȸ��
		ex -= 0.01f;
		printf("Camera Angle Down\n");
		//��� ��ǥ�� ���ؼ� 30����ŭ ȸ��
		camY = 1.0;
		camX = 1.0;
		camZ = 1.0;
		camAngle += 30.0;
		camera();		//ȭ�� �缳��
		break;		//����ġ�� ����
	case 102:		//���� ����Ű -> ȸ��
		ex += 0.01f;
		printf("Camera Angle Up\n");
		//��� ��ǥ�� ���ؼ� -30����ŭ ȸ��
		camY = 1.0;
		camX = 1.0;
		camZ = 1.0;
		camAngle -= 30.0;
		camera();		//ȭ�� �缳��
		break;		//����ġ�� ����
	}
	glutPostRedisplay();		//ȭ���� �ٽ� display��
}

void mouse(int button, int state, int x, int y) {		//���콺 Ŭ�� �̺�Ʈ�� �����ϴ� �Լ�
	srand((unsigned int)time(NULL));		//���� ���� ����
	int temp = index;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {		//���� ���콺 ��ư�� ������ ��
		printf("�༺ ������ ��ȯ�մϴ�.\n");
		while (temp == index) {		//������ ����� ���� ��� ���� �ٽ� ����
			temp = rand() % 9;
		}
		index = temp;		//���� ����
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);		//�ʱ�ȭ �۾�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//���÷��� ��� ����
	glutInitWindowSize(1600, 900);		//������ ũ�� ����
	glutInitWindowPosition(50, 50);		//������ ��ġ ����
	glutCreateWindow("20194339_��ο�_SolarSystem");		//������ Ÿ��Ʋ ����

	int submenu = glutCreateMenu(popupMenu);		//���� �˾� �޴� ����
	glutAddMenuEntry("�⺻ ����", 1);				//����޴��� '�⺻ ����'�߰�
	glutAddMenuEntry("�� ����", 2);		//����޴��� '�� ����'�߰�
	glutAddMenuEntry("�� ����", 3);		//����޴��� '�� ����'�߰�
	glutAddMenuEntry("�� ����", 4);		//����޴��� '�� ����'�߰�
	glutAddMenuEntry("������ ����", 5);		//����޴��� '������ ����'�߰�

	glutCreateMenu(popupMenu);		//�˾� �޴� ����
	glutAddSubMenu("���� ��ȯ", submenu);		//�˾��� ����޴� '���� ��ȯ'�߰�
	glutAddMenuEntry("�����ϱ�", 99);		//�˾��� �޴� '�����ϱ�' �߰�
	glutAttachMenu(GLUT_RIGHT_BUTTON);		//�ش� �˾��� ���콺 ��Ŭ���� �ϸ� ����

	init();		//�ʱ�ȭ
	glutReshapeFunc(reshape);		//������ ũ�Ⱑ ����� �� ȣ��Ǵ� �ݹ� �Լ� ���
	glutDisplayFunc(display);		//ȭ���� �׸��� �ݹ� �Լ� ���
	glutSpecialFunc(special_keyboard);		//Ư��Ű �Է��� �޴� �ݹ� �Լ� ���
	glutKeyboardFunc(normal_keyboard);		//�Ϲ�Ű �Է��� �޴� �ݹ� �Լ� ���
	glutMouseFunc(mouse);		//���콺 Ŭ�� �̺�Ʈ�� �޴� �ݹ� �Լ� ���
	glutIdleFunc(idle);		//��� �ݹ� �Լ� ���

	glutMainLoop();		//�̺�Ʈ ����

	return 0;
}
