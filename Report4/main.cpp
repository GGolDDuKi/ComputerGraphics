#include "loadpng.h"
#include <iostream>
#include <vector>
#include <GL/glut.h>

/*
����
1. ������Ʈ ���Ƿ� ����(2D, 3D)
2. ������ png ���� �ش� ������Ʈ�� ������
3. Ŭ�� �� �ٸ� png�� ����

�ڵ�, �ڵ� �ּ�, ����ȭ�� ĸó, ����ȭ�� ������� �й�_�̸�
*/

using namespace std;

int imageNum = 0;		//�̹����� �����ϱ� ���� �ε����� ����� ����
float rotation = 0.0f;
float angularVelocity = 1.5f;
GLuint textureID[2];		//�ؽ�óid�� ������ �迭
vector<unsigned char> image2;
void loadTexture(GLuint* texture, char* path);

void render() {		//������Ʈ�� �׸��� �Լ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//���� ���ۿ� ���� ���۸� �ʱ�ȭ
	glEnable(GL_TEXTURE_2D);		//2D �ؽ�ó ������ ���

	glMatrixMode(GL_PROJECTION);		//��� ��� ����
	glLoadIdentity();		//������ķ� �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW);		//��� ��� ����
	glLoadIdentity();		//������ķ� �ʱ�ȭ

	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);		//��� ��ǥ�迡�� ���� ��ǥ��� ����
	glViewport(0, 0, 500, 500);		//����Ʈ ����

	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);		//������Ʈ ȸ��

	glBindTexture(GL_TEXTURE_2D, textureID[imageNum]);		//������Ʈ�� �ؽ�ó�� ����
	glBegin(GL_QUADS);		//�簢�� ������Ʈ�� �ؽ�ó�� ����
	glTexCoord2f(0.0, 1.0); glVertex2f(-25, -20);		
	glTexCoord2f(1.0, 1.0); glVertex2f(25, -20);
	glTexCoord2f(1.0, 0.0); glVertex2f(25, 25);
	glTexCoord2f(0.0, 0.0); glVertex2f(-25, 25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureID[imageNum]);		//������Ʈ�� �ؽ�ó�� ����
	glBegin(GL_QUADS);		//�簢�� ������Ʈ�� �ؽ�ó�� ����
	glTexCoord2f(1.0, 1.0); glVertex2f(25, -20);
	glTexCoord2f(0.0, 1.0); glVertex2f(-25, -20);
	glTexCoord2f(0.0, 0.0); glVertex2f(-25, 25);
	glTexCoord2f(1.0, 0.0); glVertex2f(25, 25);
	glEnd();

	glPopMatrix();		//�ֻ��� ��� ����

	glutSwapBuffers();		//���۸� ��ü
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);		//��� ��� ����
	glLoadIdentity();		//������ķ� �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW);		//��� ��� ����
	glLoadIdentity();		//������ķ� �ʱ�ȭ

	glViewport(0, 0, 500, 500);		//����Ʈ ����
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);		//��� ��ǥ�迡�� ���� ��ǥ��� ����
	glutPostRedisplay();		//ȭ���� �籸��
}

void rotate(int value) {
	rotation += angularVelocity;
	glutTimerFunc(10, rotate, 0);		//���� �ð����� rotateȣ��
	glutPostRedisplay();		//ȭ�� �籸��
}

void swap(unsigned char* a, unsigned char* b) {		//a�� b�� �����ϴ� �Լ�
	const unsigned char temp = *a;
	*a = *b;
	*b = temp;
}

void loadTexture(GLuint* texture, const char* path) {
	vector<unsigned char> image;		//�ؽ�ó �̹��� �����͸� ������ ����
	unsigned width, height;		//�ؽ�ó �̹����� �ʺ�� ���̸� ������ ����
	unsigned error = lodepng::decode(image, width, height, path);

	if (!error) {
		cout << "error " << error << ": " << lodepng_error_text(error) << endl;		//���� �˻�
	}
	size_t u2 = 1; while (u2 < width) u2 *= 2;		//�̹����� ���� ũ�⸦ 2�� �������� ����
	size_t v2 = 1; while (v2 < height) v2 *= 2;		//�̹����� ���� ũ�⸦ 2�� �������� ����
	image2 = vector<unsigned char>(u2 * v2 * 4);	//u2 * v2 * 4ũ���� ���� ����	
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			for (size_t c = 0; c < 4; c++) {
				image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];		//�ؽ�ó �̹����� image���Ϳ��� image2���ͷ� ����
			}
		}
	}
	glGenTextures(1, texture);		//�ؽ�ó ��ü�� ����, ��ȯ, ����
	glBindTexture(GL_TEXTURE_2D, *texture);		//�ؽ�ó �Լ� ȣ�� ��� ����
	glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);		//�ؽ�ó ��ü�� �̹��� ������ ���ε�
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		//�ؽ�ó ���͸� ����
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);		//�ؽ�ó ���͸� ����
}

void initialize() {
	glEnable(GL_CULL_FACE);		//�޸� ���� ��� Ȱ��ȭ
	glCullFace(GL_BACK);		//�޸��� �����ϵ��� �����ϴ� �Լ�
	loadTexture(&textureID[0], "sky1.png");		//�̹��������� �ؽ�ó�� ����
	loadTexture(&textureID[1], "sky2.png");		//�̹��������� �ؽ�ó�� ����
}

void mouse(int button, int state, int x, int y) {		//���콺 �ݹ� �Լ�
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (imageNum == 0)
			imageNum = 1;
		else
			imageNum = 0;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glClearColor(0, 0, 0, 0);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("20194339_��ο�");

	initialize();

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutTimerFunc(10, rotate, 0);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 1;
}