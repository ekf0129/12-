#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> // Windows에서 Sleep 함수 사용
#include <conio.h>   // 키 입력 함수 (_kbhit, _getch) 사용

#define WIDTH 40       // 화면의 너비 설정
#define HEIGHT 24      // 화면의 높이 설정
#define M_PI 3.14159265358979323846 // 파이 값을 정의 (C 표준에 포함되지 않음)

// 화면 내용을 저장하는 2D 배열
char screenBuffer[HEIGHT][WIDTH * 2 + 1]; // 픽셀당 2칸 + null 문자

// 스크린 버퍼를 초기화 (모두 공백으로 설정)
void initializeScreenBuffer() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH * 2; j++) {
            screenBuffer[i][j] = ' '; // 빈칸으로 초기화
        }
        screenBuffer[i][WIDTH * 2] = '\0'; // 문자열 종료 문자 추가
    }
}

// 특정 위치에 문자 2개를 표시 (x, y 좌표에 따라)
void drawPixel(int x, int y, char c1, char c2) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return; // 범위를 벗어난 경우 아무 작업도 하지 않음
    }
    screenBuffer[y][x * 2] = c1;     // 첫 번째 문자
    screenBuffer[y][x * 2 + 1] = c2; // 두 번째 문자
}

// 학번과 이름을 화면 중앙에 표시
void displayStudentInfo() {
    const char* studentId = "20231358"; // 학번
    const char* studentName = "고은진";   // 이름

    int idLength = strlen(studentId); // 학번 문자열 길이
    int nameLength = strlen(studentName) * 2; // 한글은 2칸 차지

    // 학번과 이름의 출력 시작 위치를 중앙에 맞춤
    int idStartX = (WIDTH * 2 - idLength) / 2;
    int nameStartX = (WIDTH * 2 - nameLength) / 2;

    int idY = HEIGHT / 2 - 1; // 학번은 화면의 약간 위쪽에 표시
    int nameY = HEIGHT / 2;   // 이름은 화면의 중앙에 표시

    // 학번 출력
    for (int i = 0; i < idLength; i++) {
        drawPixel(idStartX / 2 + i, idY, studentId[i], ' '); // 학번의 각 문자 표시
    }

    // 이름 출력 (한글은 2칸씩 차지하므로 2개 단위로 표시)
    for (int i = 0; i < nameLength / 2; i++) {
        drawPixel(nameStartX / 2 + i, nameY, studentName[i * 2], studentName[i * 2 + 1]);
    }
}

// 태양, 지구, 달을 표시하는 함수
void displaySun(int x, int y) {
    drawPixel(x, y, 'S', 'S'); // 태양
}
void displayEarth(int x, int y) {
    drawPixel(x, y, 'E', 'E'); // 지구
}
void displayMoon(int x, int y) {
    drawPixel(x, y, 'M', 'M'); // 달
}

// 현재 화면을 출력
void displayScreen() {
    system("cls"); // 화면을 지우고 새로 표시
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]); // 버퍼 내용을 출력
    }
}

// 2D 회전 행렬 (각도에 따라 좌표를 회전)
void rotate(float* x, float* y, float angle) {
    float tempX = *x;
    *x = cos(angle) * tempX - sin(angle) * (*y);
    *y = sin(angle) * tempX + cos(angle) * (*y);
}

// 메인 함수
int main() {
    initializeScreenBuffer(); // 스크린 버퍼 초기화

    float sunAngle = 0.0;   // 태양의 회전각
    float earthAngle = 0.0; // 지구의 회전각
    float moonAngle = 0.0;  // 달의 회전각

    // 초기 화면: 학번과 이름 표시
    displayStudentInfo();
    displayScreen();

    // 스페이스바가 눌릴 때까지 대기
    while (1) {
        if (_kbhit()) { // 키 입력 체크
            if (_getch() == ' ') { // 스페이스바를 누르면
                break; // 대기 종료
            }
        }
        Sleep(100); // 잠시 대기
    }

    // 애니메이션 시작
    while (1) {
        if (_kbhit()) { // 키 입력 체크
            if (_getch() == 27) { // ESC 키를 누르면
                return 0; // 프로그램 종료
            }
        }

        initializeScreenBuffer(); // 화면 초기화

        // 각도 업데이트
        sunAngle += (M_PI / 180.0f) * 6.0f;    // 태양 회전 (속도 설정)
        earthAngle += (M_PI / 180.0f) * 3.0f; // 지구 공전
        moonAngle += (M_PI / 180.0f) * 10.0f; // 달 공전

        // 태양 위치 고정
        int sunX = WIDTH / 2;
        int sunY = HEIGHT / 2;

        // 지구의 위치 계산
        int earthX = (int)(sunX + 10 * cos(earthAngle));
        int earthY = (int)(sunY + 6 * sin(earthAngle));

        // 달의 위치 계산
        int moonX = (int)(earthX + 4 * cos(moonAngle));
        int moonY = (int)(earthY + 3 * sin(moonAngle));

        // 태양, 지구, 달 표시
        displaySun(sunX, sunY);
        displayEarth(earthX, earthY);
        displayMoon(moonX, moonY);

        // 화면 출력
        displayScreen();
        Sleep(100); // 애니메이션 속도 조정 (0.1초 대기)
    }

    return 0;
}
