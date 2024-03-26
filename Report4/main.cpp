#include "loadpng.h"
#include <iostream>
#include <vector>
#include <GL/glut.h>

/*
과제
1. 오브젝트 임의로 생성(2D, 3D)
2. 임의의 png 파일 해당 오브젝트에 입히기
3. 클릭 시 다른 png로 매핑

코드, 코드 주석, 실행화면 캡처, 실행화면 윈도우명 학번_이름
*/

using namespace std;

int imageNum = 0;		//이미지를 변경하기 위해 인덱스로 사용할 변수
float rotation = 0.0f;
float angularVelocity = 1.5f;
GLuint textureID[2];		//텍스처id를 저장할 배열
vector<unsigned char> image2;
void loadTexture(GLuint* texture, char* path);

void render() {		//오브젝트를 그리는 함수
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//색상 버퍼와 깊이 버퍼를 초기화
	glEnable(GL_TEXTURE_2D);		//2D 텍스처 매핑을 사용

	glMatrixMode(GL_PROJECTION);		//행렬 모드 변경
	glLoadIdentity();		//단위행렬로 초기화
	glMatrixMode(GL_MODELVIEW);		//행렬 모드 변경
	glLoadIdentity();		//단위행렬로 초기화

	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);		//평면 좌표계에서 직교 좌표계로 변경
	glViewport(0, 0, 500, 500);		//뷰포트 설정

	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);		//오브젝트 회전

	glBindTexture(GL_TEXTURE_2D, textureID[imageNum]);		//오브젝트에 텍스처를 입힘
	glBegin(GL_QUADS);		//사각형 오브젝트에 텍스처를 입힘
	glTexCoord2f(0.0, 1.0); glVertex2f(-25, -20);		
	glTexCoord2f(1.0, 1.0); glVertex2f(25, -20);
	glTexCoord2f(1.0, 0.0); glVertex2f(25, 25);
	glTexCoord2f(0.0, 0.0); glVertex2f(-25, 25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureID[imageNum]);		//오브젝트에 텍스처를 입힘
	glBegin(GL_QUADS);		//사각형 오브젝트에 텍스처를 입힘
	glTexCoord2f(1.0, 1.0); glVertex2f(25, -20);
	glTexCoord2f(0.0, 1.0); glVertex2f(-25, -20);
	glTexCoord2f(0.0, 0.0); glVertex2f(-25, 25);
	glTexCoord2f(1.0, 0.0); glVertex2f(25, 25);
	glEnd();

	glPopMatrix();		//최상위 행렬 제거

	glutSwapBuffers();		//버퍼를 교체
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);		//행렬 모드 변경
	glLoadIdentity();		//단위행렬로 초기화
	glMatrixMode(GL_MODELVIEW);		//행렬 모드 변경
	glLoadIdentity();		//단위행렬로 초기화

	glViewport(0, 0, 500, 500);		//뷰포트 설정
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);		//평면 좌표계에서 직교 좌표계로 변경
	glutPostRedisplay();		//화면을 재구성
}

void rotate(int value) {
	rotation += angularVelocity;
	glutTimerFunc(10, rotate, 0);		//일정 시간마다 rotate호출
	glutPostRedisplay();		//화면 재구성
}

void swap(unsigned char* a, unsigned char* b) {		//a와 b를 스왑하는 함수
	const unsigned char temp = *a;
	*a = *b;
	*b = temp;
}

void loadTexture(GLuint* texture, const char* path) {
	vector<unsigned char> image;		//텍스처 이미지 데이터를 저장할 벡터
	unsigned width, height;		//텍스처 이미지의 너비와 높이를 저장할 변수
	unsigned error = lodepng::decode(image, width, height, path);

	if (!error) {
		cout << "error " << error << ": " << lodepng_error_text(error) << endl;		//에러 검사
	}
	size_t u2 = 1; while (u2 < width) u2 *= 2;		//이미지의 가로 크기를 2의 제곱수로 만듬
	size_t v2 = 1; while (v2 < height) v2 *= 2;		//이미지의 세로 크기를 2의 제곱수로 만듬
	image2 = vector<unsigned char>(u2 * v2 * 4);	//u2 * v2 * 4크기의 벡터 생성	
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			for (size_t c = 0; c < 4; c++) {
				image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];		//텍스처 이미지를 image벡터에서 image2벡터로 복사
			}
		}
	}
	glGenTextures(1, texture);		//텍스처 객체를 생성, 반환, 저장
	glBindTexture(GL_TEXTURE_2D, *texture);		//텍스처 함수 호출 대상 설정
	glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);		//텍스처 객체에 이미지 데이터 업로드
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		//텍스처 필터링 설정
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);		//텍스처 필터링 설정
}

void initialize() {
	glEnable(GL_CULL_FACE);		//뒷면 제거 기능 활성화
	glCullFace(GL_BACK);		//뒷면을 제거하도록 설정하는 함수
	loadTexture(&textureID[0], "sky1.png");		//이미지파일을 텍스처로 생성
	loadTexture(&textureID[1], "sky2.png");		//이미지파일을 텍스처로 생성
}

void mouse(int button, int state, int x, int y) {		//마우스 콜백 함수
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
	glutCreateWindow("20194339_김민욱");

	initialize();

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutTimerFunc(10, rotate, 0);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 1;
}