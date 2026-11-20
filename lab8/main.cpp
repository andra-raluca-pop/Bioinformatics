
#include <iostream>
using namespace std;

const int MATCH = 1;
const int MISMATCH = -1;
const int GAP = -2;

const int MAXLEN = 50;

int length(const char s[]) {
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

int score(char a, char b) {
    if (a == b)
        return MATCH;
    return MISMATCH;
}

int maximum(int a, int b, int c) {
    int m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    return m;
}

void printNumber(int x) {
    int digits = 0;
    int temp = x;
    if (temp <= 0) digits = 1;
    if (temp < 0) temp = -temp;
    while (temp > 0) {
        digits++;
        temp = temp / 10;
    }
    for (int k = digits; k < 4; k++)
        cout << ' ';
    cout << x;
}

void reverseArray(char s[], int len) {
    int left = 0;
    int right = len - 1;
    while (left < right) {
        char t = s[left];
        s[left] = s[right];
        s[right] = t;
        left++;
        right--;
    }
}

int main() {
    char s1[] = "ATCCGTTAC";
    char s2[] = "CGAT";

    int n = length(s1);
    int m = length(s2);

    int mat[MAXLEN][MAXLEN];

    for (int i = 0; i <= n; i++)
        mat[i][0] = i * GAP;
    for (int j = 0; j <= m; j++)
        mat[0][j] = j * GAP;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int diag = mat[i - 1][j - 1] + score(s1[i - 1], s2[j - 1]);
            int up   = mat[i - 1][j] + GAP;
            int left = mat[i][j - 1] + GAP;
            mat[i][j] = maximum(diag, up, left);
        }
    }


    cout << "Score matrix:\n\n";
    cout << "      ";
    for (int j = 0; j < m; j++)
        cout << "   " << s2[j];
    cout << "\n";

    for (int i = 0; i <= n; i++) {
        if (i == 0)
            cout << "  ";
        else
            cout << s1[i - 1] << " ";
        for (int j = 0; j <= m; j++)
            printNumber(mat[i][j]);
        cout << "\n";
    }


    char a1[2 * MAXLEN];
    char a2[2 * MAXLEN];
    int len = 0;
    int i = n;
    int j = m;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && mat[i][j] == mat[i - 1][j - 1] + score(s1[i - 1], s2[j - 1])) {
            a1[len] = s1[i - 1];
            a2[len] = s2[j - 1];
            i--;
            j--;
        } else if (i > 0 && mat[i][j] == mat[i - 1][j] + GAP) {
            a1[len] = s1[i - 1];
            a2[len] = '-';
            i--;
        } else {
            a1[len] = '-';
            a2[len] = s2[j - 1];
            j--;
        }
        len++;
    }


    reverseArray(a1, len);
    reverseArray(a2, len);


    cout << "\nOptimal global alignment:\n\n";

    cout << "S1: ";
    for (int k = 0; k < len; k++)
        cout << a1[k];
    cout << "\n";

    cout << "    ";
    for (int k = 0; k < len; k++) {
        if (a1[k] == a2[k])
            cout << '|';
        else
            cout << ' ';
    }
    cout << "\n";

    cout << "S2: ";
    for (int k = 0; k < len; k++)
        cout << a2[k];
    cout << "\n";

    cout << "\nAlignment score: " << mat[n][m] << "\n";

    return 0;
}
