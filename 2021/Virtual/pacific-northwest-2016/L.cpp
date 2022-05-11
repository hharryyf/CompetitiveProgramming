#include <bits/stdc++.h>
#define MAX_SIZE 52
#define double long double
using namespace std;
const double eps = 1e-10;
const double Pi = acos(-1.0);
int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point {
    double x, y;
    point(double x=0, double y=0) : x(x), y(y) {}
    point operator -(point other) {
        return point(x - other.x, y - other.y);
    }
    
    point operator +(point other) {
        return point(x + other.x, y + other.y);
    }
    
    bool operator < (point other) {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    point operator *(double p) {
        return point(x*p, y*p);
    }
};

typedef point Vector;

struct segment {
    point v1, v2;
};

struct Line {
    // v is the point, p is the direction vector
    point v, p;
    Line(point v, point p):v(v), p(p) {}
};

double Dot(Vector A, Vector B){
    return A.x*B.x + A.y*B.y;
}

double Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

int N, ans[MAX_SIZE];
point pt[MAX_SIZE];
char s[MAX_SIZE];

int main() {
    int i, j, id = 0;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%Lf%Lf", &pt[i].x, &pt[i].y);
        ans[i] = i;
    }

    scanf("%s", s);
    
    for (i = 0 ; i < N; ++i) {
        if (pt[i].x < pt[id].x || (pt[i].x == pt[id].x && pt[i].y < pt[id].y)) id = i;
    }

    swap(ans[id], ans[0]);
    swap(pt[0], pt[id]);

    for (i = 1; i < N - 1; ++i) {
        id = i;
        for (j = i + 1; j < N; ++j) {
            if (s[i-1] == 'L') {
                if (sgn(Cross(pt[id] - pt[i - 1], pt[j] - pt[i - 1])) < 0) id = j;
            } else {
                if (sgn(Cross(pt[id] - pt[i - 1], pt[j] - pt[i - 1])) > 0) id = j;
            }
        }
        swap(pt[i], pt[id]);
        swap(ans[i], ans[id]);
    }

    for (i = 0 ; i < N; ++i) {
        printf("%d", ans[i] + 1);
        if (i != N - 1) printf(" ");
    }
    printf("\n");
    return 0;
}