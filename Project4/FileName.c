#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 24
#define PI 3.141592653589793 // 원주율 정의

void gotoxy(int x, int y) {
    COORD pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clearScreen() {
    system("cls");
}

void drawPixel(int x, int y, char* symbol) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        gotoxy(x, y);
        printf("%s", symbol);
    }
}

void drawFilledCircle(int cx, int cy, int r, char* symbol) {
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) { // 원의 내부 점 조건
                drawPixel(cx + x, cy + y, symbol);
            }
        }
    }
}

void drawSun() {
    drawFilledCircle(20, 12, 5, "SS");
}

void drawEarth(float x, float y) {
    drawFilledCircle((int)x, (int)y, 3, "EE");
}

void drawMoon(float x, float y) {
    drawFilledCircle((int)x, (int)y, 1, "MM");
}

void printInitialScreen() {
    gotoxy(10, 12);
    printf("20231365 정예원");
}

void startRotation() {
    float earthX = 12, earthY = 0;
    float moonX = 4, moonY = 0;
    float angleEarth = 0, angleMoon = 0;

    while (1) {
        clearScreen();
        drawSun();

        // 지구 공전
        float earthTempX = earthX * cos(angleEarth * PI / 180) - earthY * sin(angleEarth * PI / 180);
        float earthTempY = earthX * sin(angleEarth * PI / 180) + earthY * cos(angleEarth * PI / 180);
        drawEarth(20 + earthTempX, 12 + earthTempY);

        // 달 공전
        float moonTempX = moonX * cos(angleMoon * PI / 180) - moonY * sin(angleMoon * PI / 180);
        float moonTempY = moonX * sin(angleMoon * PI / 180) + moonY * cos(angleMoon * PI / 180);
        drawMoon(20 + earthTempX + moonTempX, 12 + earthTempY + moonTempY);

        Sleep(100);
        angleEarth += 6; // 지구 공전 속도
        angleMoon -= 12; // 달 공전 속도

        if (_kbhit() && _getch() == 27) // ESC
            break;
    }
}

int main() {
    char key;

    // 초기 화면 출력
    printInitialScreen();

    // 스페이스바 입력 대기
    while (1) {
        if (_kbhit()) {
            key = _getch();
            if (key == 32) { // 스페이스바
                break;
            }
            else if (key == 27) { // ESC
                return 0;
            }
        }
    }

    // 행성 초기 배치
    clearScreen();
    drawSun();
    drawEarth(20 + 12, 12);
    drawMoon(20 + 12 + 4, 12);

    // 두 번째 스페이스바 입력 대기
    while (1) {
        if (_kbhit()) {
            key = _getch();
            if (key == 32) { // 스페이스바
                startRotation();
                break;
            }
            else if (key == 27) { // ESC
                return 0;
            }
        }
    }

    return 0;
}
