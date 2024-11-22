#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> // Windows���� Sleep �Լ� ���
#include <conio.h>   // Ű �Է� �Լ� (_kbhit, _getch) ���

#define WIDTH 40       // ȭ���� �ʺ� ����
#define HEIGHT 24      // ȭ���� ���� ����
#define M_PI 3.14159265358979323846 // ���� ���� ���� (C ǥ�ؿ� ���Ե��� ����)

// ȭ�� ������ �����ϴ� 2D �迭
char screenBuffer[HEIGHT][WIDTH * 2 + 1]; // �ȼ��� 2ĭ + null ����

// ��ũ�� ���۸� �ʱ�ȭ (��� �������� ����)
void initializeScreenBuffer() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH * 2; j++) {
            screenBuffer[i][j] = ' '; // ��ĭ���� �ʱ�ȭ
        }
        screenBuffer[i][WIDTH * 2] = '\0'; // ���ڿ� ���� ���� �߰�
    }
}

// Ư�� ��ġ�� ���� 2���� ǥ�� (x, y ��ǥ�� ����)
void drawPixel(int x, int y, char c1, char c2) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return; // ������ ��� ��� �ƹ� �۾��� ���� ����
    }
    screenBuffer[y][x * 2] = c1;     // ù ��° ����
    screenBuffer[y][x * 2 + 1] = c2; // �� ��° ����
}

// �й��� �̸��� ȭ�� �߾ӿ� ǥ��
void displayStudentInfo() {
    const char* studentId = "20231358"; // �й�
    const char* studentName = "������";   // �̸�

    int idLength = strlen(studentId); // �й� ���ڿ� ����
    int nameLength = strlen(studentName) * 2; // �ѱ��� 2ĭ ����

    // �й��� �̸��� ��� ���� ��ġ�� �߾ӿ� ����
    int idStartX = (WIDTH * 2 - idLength) / 2;
    int nameStartX = (WIDTH * 2 - nameLength) / 2;

    int idY = HEIGHT / 2 - 1; // �й��� ȭ���� �ణ ���ʿ� ǥ��
    int nameY = HEIGHT / 2;   // �̸��� ȭ���� �߾ӿ� ǥ��

    // �й� ���
    for (int i = 0; i < idLength; i++) {
        drawPixel(idStartX / 2 + i, idY, studentId[i], ' '); // �й��� �� ���� ǥ��
    }

    // �̸� ��� (�ѱ��� 2ĭ�� �����ϹǷ� 2�� ������ ǥ��)
    for (int i = 0; i < nameLength / 2; i++) {
        drawPixel(nameStartX / 2 + i, nameY, studentName[i * 2], studentName[i * 2 + 1]);
    }
}

// �¾�, ����, ���� ǥ���ϴ� �Լ�
void displaySun(int x, int y) {
    drawPixel(x, y, 'S', 'S'); // �¾�
}
void displayEarth(int x, int y) {
    drawPixel(x, y, 'E', 'E'); // ����
}
void displayMoon(int x, int y) {
    drawPixel(x, y, 'M', 'M'); // ��
}

// ���� ȭ���� ���
void displayScreen() {
    system("cls"); // ȭ���� ����� ���� ǥ��
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]); // ���� ������ ���
    }
}

// 2D ȸ�� ��� (������ ���� ��ǥ�� ȸ��)
void rotate(float* x, float* y, float angle) {
    float tempX = *x;
    *x = cos(angle) * tempX - sin(angle) * (*y);
    *y = sin(angle) * tempX + cos(angle) * (*y);
}

// ���� �Լ�
int main() {
    initializeScreenBuffer(); // ��ũ�� ���� �ʱ�ȭ

    float sunAngle = 0.0;   // �¾��� ȸ����
    float earthAngle = 0.0; // ������ ȸ����
    float moonAngle = 0.0;  // ���� ȸ����

    // �ʱ� ȭ��: �й��� �̸� ǥ��
    displayStudentInfo();
    displayScreen();

    // �����̽��ٰ� ���� ������ ���
    while (1) {
        if (_kbhit()) { // Ű �Է� üũ
            if (_getch() == ' ') { // �����̽��ٸ� ������
                break; // ��� ����
            }
        }
        Sleep(100); // ��� ���
    }

    // �ִϸ��̼� ����
    while (1) {
        if (_kbhit()) { // Ű �Է� üũ
            if (_getch() == 27) { // ESC Ű�� ������
                return 0; // ���α׷� ����
            }
        }

        initializeScreenBuffer(); // ȭ�� �ʱ�ȭ

        // ���� ������Ʈ
        sunAngle += (M_PI / 180.0f) * 6.0f;    // �¾� ȸ�� (�ӵ� ����)
        earthAngle += (M_PI / 180.0f) * 3.0f; // ���� ����
        moonAngle += (M_PI / 180.0f) * 10.0f; // �� ����

        // �¾� ��ġ ����
        int sunX = WIDTH / 2;
        int sunY = HEIGHT / 2;

        // ������ ��ġ ���
        int earthX = (int)(sunX + 10 * cos(earthAngle));
        int earthY = (int)(sunY + 6 * sin(earthAngle));

        // ���� ��ġ ���
        int moonX = (int)(earthX + 4 * cos(moonAngle));
        int moonY = (int)(earthY + 3 * sin(moonAngle));

        // �¾�, ����, �� ǥ��
        displaySun(sunX, sunY);
        displayEarth(earthX, earthY);
        displayMoon(moonX, moonY);

        // ȭ�� ���
        displayScreen();
        Sleep(100); // �ִϸ��̼� �ӵ� ���� (0.1�� ���)
    }

    return 0;
}
