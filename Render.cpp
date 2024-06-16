#include <iostream>
#include <string.h>
#include <math.h>
#include <unistd.h>
using namespace std;

const float ROTATION_SPEED_A_DEFAULT = 0.00004;
const float ROTATION_SPEED_B_DEFAULT = 0.00002;

int main() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    float rotation_speed_A = ROTATION_SPEED_A_DEFAULT; // Default rotation speed for A
    float rotation_speed_B = ROTATION_SPEED_B_DEFAULT; // Default rotation speed for B

    // Prompt user for rotation speeds
    cout << "Enter rotation speed for A (default is 0.00004): ";
    cin >> rotation_speed_A;

    cout << "Enter rotation speed for B (default is 0.00002): ";
    cin >> rotation_speed_B;

    printf("\x1b[2J");
    for(;;) {
        memset(b,32,1760); // Fill character buffer with spaces
        memset(z,0,7040);  // Fill depth buffer with zeros
        for(j = 0; j < 6.28; j += 0.07) {
            for(i = 0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = "PiotrChaberka" [N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
        }
        fflush(stdout);

        A += rotation_speed_A;
        B += rotation_speed_B;

        usleep(30000);
    }
    return 0;
}
