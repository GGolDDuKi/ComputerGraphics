#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//----- 추가 기능 -----
//각 행성 클릭 시 색상 무작위 변경

//행성별 공전 주기
float mercuryYear = 0.0;    //수성
float venusYear = 0.0;		//금성
float earthYear = 0.0;		//지구
float moonYear = 0.0;		//달
float marsyear = 0.0;		//화성
float jupiterYear = 0.0;		//목성
float saturnYear = 0.0;		//토성
float uranusYear = 0.0;		//천왕성
float neptuneYear = 0.0;		//해왕성

//행성별 자전 주기
float sunDay = 0.0f;		//태양
float mercuryDay = 0.0f;		//수성
float venusDay = 0.0f;		//금성
float earthDay = 0.0f;		//지구
float moonDay = 0.0f;		//달
float marsDay = 0.0f;		//화성
float jupiterDay = 0.0f;		//목성
float saturnDay = 0.0f;		//토성
float uranusDay = 0.0f;		//천왕성
float neptuneDay = 0.0f;		//해왕성

//현재 시점에 따라 줌인/아웃 좌표를 조절위한 변수
bool up = false;
bool front = true;
bool side = false;

//카메라의 각도를 변환하는 변수
float camAngle = 0.0;
float camX = 0.0;
float camY = 0.0;
float camZ = 0.0;

//행성의 회전을 관리하는 변수
float yearSpeed = 1.0f;		//회전 속도
float spin = 1.0f;		//회전 on/off

//카메라 위치를 지정하는 변수
float ex = 0.1f, ey = 0.1f, ez = 0.1f;

//무작위 색상 팔레트
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
	glClearColor(0.0, 0.0, 0.0, 0.0);		//색상 버퍼를 초기화
	glShadeModel(GL_SMOOTH);		//셰이딩 모델을 SMOOTH로 설정
}

void CreateCircle(float radius) {		//반지름에 따라 공전 궤도를 그려주는 함수
	float angle = 0.0f;
	glLineWidth(1.0);		//선의 굵기 지정
	glColor3f(0.2f, 0.2f, 0.2f);		//궤도 색상 지정
	glBegin(GL_LINE_LOOP);		//연속되는 선 그리기
	for (int i = 0; i < 100; i++) {		//선이 부드럽게 연결되도록 여러 횟수 반복
		angle = 2 * 3.14 * i / 100;
		glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));		//radius* cos(angle), 0.0, radius* sin(angle) 지점에 연속적인 점을 찍어 선으로 연결
	}
	glEnd();		//선 그리기 종료
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//색상 버퍼와, 깊이 버퍼 초기화

	//행성 색상 설정에 사용할 RGB변수 설정
	Red = PALETTE[index][0] / 255.0f;
	Green = PALETTE[index][1] / 255.0f;
	Blue = PALETTE[index][2] / 255.0f;

	glEnable(GL_DEPTH_TEST);		//깊이 테스트를 활성화
	glClearDepth(1.0f);		//깊이 버퍼의 초기값을 1.0으로 초기화
	//glInitNames();		

	//행성 공전 궤도 그리기
	CreateCircle(1.5);		//수성의 공전 궤도
	CreateCircle(2.25);		//금성의 공전 궤도
	CreateCircle(3.0);		//지구의 공전 궤도
	CreateCircle(3.9);		//화성의 공전 궤도
	CreateCircle(5.0);		//목성의 공전 궤도
	CreateCircle(6.5);		//토성의 공전 궤도
	CreateCircle(7.5);		//천왕성의 공전 궤도
	CreateCircle(8.5);		//해왕성의 공전 궤도

	glPushMatrix();		//변환 행렬 스택에 저장
	glColor3f(Red, Green, Blue);  //태양의 색상 설정
	glRotatef(sunDay, 0.0, 1.0, 0.0);		//태양의 자전
	glutWireSphere(1.0, 40, 32);  //태양 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(mercuryYear, 0.0, 1.0, 0.0);		//수성의 공전
	glTranslatef(1.5, 0.0, 0.0);		//태양으로부터 1.5만큼 떨어져 있음
	glRotatef(mercuryDay, 0.0, 1.0, 0.0);		//수성의 공전
	glColor3f(0.0, 0.0, 1.0);  //수성의 색상 설정
	glutWireSphere(0.1, 20, 16);  //수성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(venusYear, 0.0, 1.0, 0.0);		//금성의 공전
	glTranslatef(2.25, 0.0, 0.0);		//태양으로부터 2.25만큼 떨어져 있음
	glRotatef(venusDay, 0.0, 1.0, 0.0);		//금성의 자전
	glColor3f(0.0, 0.0, 1.0);  //금성의 색상 설정
	glutWireSphere(0.25, 20, 16);  //금성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(earthYear, 0.0, 1.0, 0.0);		//지구의 공전
	glTranslatef(3.0, 0.0, 0.0);		//태양으로부터 3.0만큼 떨어져 있음
	glRotatef(earthDay, 0.0, 1.0, 0.0);			//지구의 자전
	glColor3f(0.0, 0.0, 1.0);  //지구의 색상 설정
	glutWireSphere(0.25, 20, 16);  //지구 그리기
	//달은 지구를 기준으로 공전하기 때문에 여기서 glPopMatrix()를 해주지 않음

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(moonYear, 0.0, 1.0, 0.0);		//달의 공전
	glTranslatef(0.4, 0.0, 0.0);		//지구로부터 0.4만큼 떨어져 있음
	glRotatef(moonDay, 0.0, 1.0, 0.0);		//달의 자전
	glColor3f(0.7, 0.7, 0.7);  //달의 색상 설정
	glutWireSphere(0.06, 10, 8);  //달 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(marsyear, 0.0, 1.0, 0.0);		//화성의 공전
	glTranslatef(3.9, 0.0, 0.0);		//태양으로부터 3.9만큼 떨어져 있음
	glRotatef(marsDay, 0.0, 1.0, 0.0);		//화성의 자전
	glColor3f(0.0, 0.0, 1.0);  //화성의 색상 설정
	glutWireSphere(0.125, 20, 16);  //화성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(jupiterYear, 0.0, 1.0, 0.0);		//목성의 공전
	glTranslatef(5.0, 0.0, 0.0);		//태양으로부터 5.0만큼 떨어져 있음
	glRotatef(jupiterDay, 0.0, 1.0, 0.0);		//목성의 자전
	glColor3f(0.0, 0.0, 1.0);  //목성의 색상 설정
	glutWireSphere(0.6, 20, 16);  //목성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(saturnYear, 0.0, 1.0, 0.0);		//토성의 공전
	glTranslatef(6.5, 0.0, 0.0);		//태양으로부터 6.5만큼 떨어져 있음
	glRotatef(saturnDay, 0.0, 1.0, 0.0);		//토성의 자전
	glColor3f(0.0, 0.0, 1.0);  //토성의 색상 설정
	glutWireSphere(0.45, 20, 16);  //토성 그리기
	gluQuadricDrawStyle(gluNewQuadric(), GLU_FILL);		//Quadric 객체를 생성, 스타일은 채우기로 설정
	glRotatef(90.0, 1.0, 0.0, 0.0);		//x축으로 90도만큼 회전
	gluDisk(gluNewQuadric(), 0.55, 0.7, 20, 15);		//좁은 폭이 0.55, 넓은 폭이 0.7인 디스크 오브젝트 생성
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(uranusYear, 0.0, 1.0, 0.0);		//천왕성의 공전
	glTranslatef(7.5, 0.0, 0.0);		//태양으로부터 7.5만큼 떨어져 있음
	glRotatef(uranusDay, 0.0, 1.0, 0.0);		//천왕성의 자전
	glColor3f(0.0, 0.0, 1.0);  //천왕성의 색상 설정
	glutWireSphere(0.3, 20, 16);  //천왕성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glPushMatrix();		//변환 행렬 스택에 저장
	glRotatef(neptuneYear, 0.0, 1.0, 0.0);		//해왕성의 공전
	glTranslatef(8.5, 0.0, 0.0);		//태양으로부터 8.5만큼 떨어져 있음
	glRotatef(neptuneDay, 0.0, 1.0, 0.0);		//해왕성의 자전
	glColor3f(0.0, 0.0, 1.0);  //해왕성의 색상 설정
	glutWireSphere(0.3, 20, 16);  //해왕성 그리기
	glPopMatrix();		//이전 변환 행렬로 복귀

	glutSwapBuffers();		//버퍼를 교체
}

void camera() {		//카메라의 변환된 시점을 display해주는 함수
	glMatrixMode(GL_MODELVIEW);		//변환 행렬 모드를 모델뷰 행렬 모드로 설정
	glLoadIdentity();		//변환 행렬을 단위 행렬로 초기화
	gluLookAt(ex, ey, ez, 0.1, 0.0, 0.0, 1.0, 1.5, 0.0);		//카메라 위치, 시점, 머리방향 설정
	glRotatef(camAngle, camX, camY, camZ);		//카메라 회전
	glutPostRedisplay();		//화면을 다시 display함
}

void popupMenu(int value) {
	srand((unsigned int)time(NULL));		//랜덤 변수 설정
	int random = rand() % 3;		//0~2의 값이 나오도록 변수 설정
	switch (value) {		//선택한 메뉴에 따른 옵션 설정
	case 1:
		glutSetWindowTitle("기본 시점");		//메뉴 선택 시, 윈도우 타이틀이 '기본 시점'으로 변환 됨
		printf("기본 시점으로 변경합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		ex = 0.1; ey = 0.1; ez = 0.1;		//카메라 위치 설정
		side = false; up = false; front = true;		//시점에 맞춰 변수 설정
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//카메라 각도와 관련된 변수들 초기화
		camera();		//카메라 재설정
		break;		//스위치문 종료
	case 2:
		glutSetWindowTitle("위 시점");		//메뉴 선택 시, 윈도우 타이틀이 '위 시점'으로 변환 됨
		printf("위 시점으로 변경합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		ex = 0.1; ey = 10.0; ez = 0.1;		//카메라 위치 설정
		side = false; up = true; front = false;		//시점에 맞춰 변수 설정
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//카메라 각도와 관련된 변수들 초기화
		camera();		//카메라 재설정
		break;		//스위치문 종료
	case 3:
		glutSetWindowTitle("옆 시점");		//메뉴 선택 시, 윈도우 타이틀이 '옆 시점'으로 변환 됨
		printf("옆 시점으로 변경합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		ex = 10.0; ey = 0.1; ez = 0.1;		//카메라 위치 설정
		side = true; up = false; front = false;		//시점에 맞춰 변수 설정
		camAngle = 0.0; camX = 0.0; camY = 0.0; camZ = 0.0;		//카메라 각도와 관련된 변수들 초기화
		camera();		//카메라 재설정
		break;		//스위치문 종료
	case 4:
		glutSetWindowTitle("앞 시점");		//메뉴 선택 시, 윈도우 타이틀이 '앞 시점'으로 변환 됨
		printf("앞 시점으로 변경합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		ex = 0.1; ey = 0.1;	ez = 10.0;		//카메라 위치 설정
		side = false; up = false; front = true;		//시점에 맞춰 변수 설정
		camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;		//카메라 각도와 관련된 변수들 초기화
		camera();		//카메라 재설정
		break;		//스위치문 종료
	case 5:
		glutSetWindowTitle("무작위 시점");		//메뉴 선택 시, 윈도우 타이틀이 '무작위 시점'으로 변환 됨
		printf("무작위 시점으로 변경합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		//random변수의 값에 따라, 무작위로 카메라 위치, 각도 설정 및 변환된 시점을 display함
		if (random == 0) {		//옆 시점
			ex = 10.0; ey = 0.1; ez = 0.1;
			side = true; up = false; front = false;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		else if (random == 1) {		//위 시점
			ex = 0.1; ey = 10.0; ez = 0.1;
			side = false; up = true; front = false;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		else if (random == 2) {		//앞 시점
			ex = 0.1; ey = 0.1; ez = 10.0;
			side = false; up = false; front = true;
			camAngle = 0.0;	camX = 0.0;	camY = 0.0;	camZ = 0.0;
			camera();
		}
		break;		//스위치문 종료
	case 99:
		printf("OpenGL 프로그램을 종료합니다.\n");		//메뉴 선택 시, 해당 문자열 출력
		exit(0);		//프로그램 종료
		break;		//스위치문 종료
	}
}

void normal_keyboard(unsigned char key, int x, int y) {		//일반 키의 입력을 받는 함수
	switch (key) {		//입력한 키에 따라 옵션 설정
	case '=':  // '+' 키를 누를 경우 공전 속도 증가 / +는 Shift를 눌러야 하기 때문에 =로 설정하였음
		yearSpeed = yearSpeed + 0.1f;		//공전 속도가 0.1만큼 증가
		printf("공전 속도가 빨라집니다.\n");
		break;		//스위치문 종료
	case '-':  // '-' 키를 누를 경우 공전 속도 감소
		yearSpeed = yearSpeed - 0.1f;		//공전 속도가 0.1만큼 감소
		printf("공전 속도가 느려집니다.\n");
		break;		//스위치문 종료
	case 32:		//스페이스바를 누르면 회전 on/off
		if (spin == 1.0f) {		//spin변수가 1이면 0으로 바꾸며 공전 중단
			spin = 0.0f;
			printf("공전을 멈춥니다.\n");
			break;		//스위치문 종료
		}
		else if (spin == 0.0f) {		//spin변수가 0이면 1로 바꾸며 공전 시작
			spin = 1.0f;
			printf("공전을 시작합니다.\n");
			break;		//스위치문 종료
		}
	}
	glutPostRedisplay();  // 화면 다시 그리기
}

void idle() {		//유휴 상태에 재생되는 함수
	//공전 - 수성: 0.25, 금성 : 0.6, 지구 : 1.0, 화성 : 1.9, 달 : 0.07
	//지구(0.5)를 기준으로 각 비율로 공전
	//목성부터는 태양계 행성 공전주기의 비율로 공전
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

	//자전
	//참고 - https://astro.kasi.re.kr/learning/pageView/5116
	//지구(1.0)을 기준으로 비율을 선정하였습니다.
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
	
	glutPostRedisplay();		// 화면 다시 그리기
}

void reshape(int w, int h) {		//윈도우 크기가 변경될 때 호출할 함수
	glViewport(0, 0, w, h);		//뷰포트 설정
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();		//변환 행렬을 단위 행렬로 초기화
	gluPerspective(90, (GLfloat)w / (GLfloat)h, 1.0, 20.0);			//시야각, 근, 원 설정

	glMatrixMode(GL_MODELVIEW);		//변환 행렬 모드를 모델뷰 행렬 모드로 설정
	glLoadIdentity();		//변환 행렬을 단위 행렬로 초기화
	gluLookAt(0.1, 0.1, 0.1, 0.1, 0.0, 0.0, 1.0, 1.5, 0.0);		//기본 카메라 설정
	glutPostRedisplay();		//화면을 다시 display함
}		

void special_keyboard(int key, int x, int y) {		//특수키 입력을 받는 함수
	switch (key) {		//입력한 특수키에 따른 옵션 설정
	case 101:		//위 방향키 -> 줌인
		if (front == true)		//앞 시점일 경우
			ez -= 0.1f;
		else if (up == true)		//위 시점일 경우
			ey -= 0.1f;
		else if (side == true)		//옆 시점일 경우
			ex -= 0.1f;
		printf("Zoom In\n");
		camera();		//화면 재설정
		break;		//스위치문 종료
	case 103:		//아래 방향키 -> 줌아웃
		if (front == true)		//앞 시점일 경우
			ez += 0.1f;
		else if (up == true)		//위 시점일 경우
			ey += 0.1f;
		else if (side == true)		//옆 시점일 경우
			ex += 0.1f;
		printf("Zoom Out\n");
		camera();		//화면 재설정
		break;		//스위치문 종료
	case 100:		//좌측 방향키 -> 회전
		ex -= 0.01f;
		printf("Camera Angle Down\n");
		//모든 좌표에 대해서 30도만큼 회전
		camY = 1.0;
		camX = 1.0;
		camZ = 1.0;
		camAngle += 30.0;
		camera();		//화면 재설정
		break;		//스위치문 종료
	case 102:		//우측 방향키 -> 회전
		ex += 0.01f;
		printf("Camera Angle Up\n");
		//모든 좌표에 대해서 -30도만큼 회전
		camY = 1.0;
		camX = 1.0;
		camZ = 1.0;
		camAngle -= 30.0;
		camera();		//화면 재설정
		break;		//스위치문 종료
	}
	glutPostRedisplay();		//화면을 다시 display함
}

void mouse(int button, int state, int x, int y) {		//마우스 클릭 이벤트를 설정하는 함수
	srand((unsigned int)time(NULL));		//랜덤 변수 설정
	int temp = index;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {		//왼쪽 마우스 버튼이 눌렸을 때
		printf("행성 색상을 변환합니다.\n");
		while (temp == index) {		//기존의 색상과 같을 경우 색상 다시 변경
			temp = rand() % 9;
		}
		index = temp;		//색상 변경
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);		//초기화 작업
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//디스플레이 모드 설정
	glutInitWindowSize(1600, 900);		//윈도우 크기 설정
	glutInitWindowPosition(50, 50);		//윈도우 위치 설정
	glutCreateWindow("20194339_김민욱_SolarSystem");		//윈도우 타이틀 설정

	int submenu = glutCreateMenu(popupMenu);		//서브 팝업 메뉴 생성
	glutAddMenuEntry("기본 시점", 1);				//서브메뉴에 '기본 시점'추가
	glutAddMenuEntry("위 시점", 2);		//서브메뉴에 '위 시점'추가
	glutAddMenuEntry("옆 시점", 3);		//서브메뉴에 '옆 시점'추가
	glutAddMenuEntry("앞 시점", 4);		//서브메뉴에 '앞 시점'추가
	glutAddMenuEntry("무작위 시점", 5);		//서브메뉴에 '무작위 시점'추가

	glutCreateMenu(popupMenu);		//팝업 메뉴 생성
	glutAddSubMenu("시점 변환", submenu);		//팝업에 서브메뉴 '시점 변환'추가
	glutAddMenuEntry("종료하기", 99);		//팝업에 메뉴 '종료하기' 추가
	glutAttachMenu(GLUT_RIGHT_BUTTON);		//해당 팝업은 마우스 우클릭을 하면 등장

	init();		//초기화
	glutReshapeFunc(reshape);		//윈도우 크기가 변경될 때 호출되는 콜백 함수 등록
	glutDisplayFunc(display);		//화면을 그리는 콜백 함수 등록
	glutSpecialFunc(special_keyboard);		//특수키 입력을 받는 콜백 함수 등록
	glutKeyboardFunc(normal_keyboard);		//일반키 입력을 받는 콜백 함수 등록
	glutMouseFunc(mouse);		//마우스 클릭 이벤트를 받는 콜백 함수 등록
	glutIdleFunc(idle);		//평시 콜백 함수 등록

	glutMainLoop();		//이벤트 루프

	return 0;
}
