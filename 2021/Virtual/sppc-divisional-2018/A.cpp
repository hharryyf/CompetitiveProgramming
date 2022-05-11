#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

int N, i;
int a[MAX_SIZE][3];
int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// check YY/DD/MM
bool check_1() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][2] > 12 || a[i][2] <= 0) return false;
        int ret = (a[i][0] % 4 == 0 && a[i][2] == 2) + days[a[i][2]];
        if (ret < a[i][1] || a[i][1] <= 0) return false;        
    }
    return true;
}

// check YY/MM/DD
bool check_2() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][1] > 12 || a[i][1] <= 0) return false;
        int ret = (a[i][0] % 4 == 0 && a[i][1] == 2) + days[a[i][1]];
        if (ret < a[i][2] || a[i][2] <= 0) return false;        
    }
    return true;
}

// check MM/YY/DD
bool check_3() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][0] > 12 || a[i][0] <= 0) return false;
        int ret = ((a[i][1] % 4 == 0) && a[i][0] == 2) + days[a[i][0]];
        if (ret < a[i][2] || a[i][2] <= 0) return false;        
    }
    return true;
}

// check MM/DD/YY
bool check_4() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][0] > 12 || a[i][0] <= 0) return false;
        int ret = (a[i][2] % 4 == 0 && a[i][0] == 2) + days[a[i][0]];
        if (ret < a[i][1] || a[i][1] <= 0) return false;        
    }
    return true;
}

// check DD/MM/YY
bool check_5() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][1] > 12 || a[i][1] <= 0) return false;
        int ret = (a[i][2] % 4 == 0 && a[i][1] == 2) + days[a[i][1]];
        if (ret < a[i][0] || a[i][0] <= 0) return false;        
    }
    return true;
}

// check DD/YY/MM
bool check_6() {
    for (i = 0 ; i < N; ++i) {
        if (a[i][2] > 12 || a[i][2] <= 0) return false;
        int ret = (a[i][1] % 4 == 0 && a[i][2] == 2) + days[a[i][2]];
        if (ret < a[i][0] || a[i][0] <= 0) return false;        
    }
    return true;
}

char ss[7][12] = {"", "YY/DD/MM", "YY/MM/DD", "MM/YY/DD", "MM/DD/YY", "DD/MM/YY", "DD/YY/MM"};

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%d/%d/%d", &a[i][0], &a[i][1], &a[i][2]);
    }   
    
    int idx = -1, score = 0;
    if (check_1()) {
        score++, idx = 1;
    }
    if (check_2()) {
        score++, idx = 2;
    }
    if (check_3()) {
        score++, idx = 3;
    }
    if (check_4()) {
        score++, idx = 4;
    }
    if (check_5()) {
        score++, idx = 5;
    }
    if (check_6()) {
        score++, idx = 6;
    }
    if (score == 0) {
        printf("IMPOSSIBLE\n");
    } else if (score > 1) {
        printf("UNSURE\n");
    } else {
        printf("%s\n", ss[idx]);
    }
    return 0;
}