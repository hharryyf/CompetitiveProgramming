#include <bits/stdc++.h>
const double Pi = acos(-1.0);
#define MAX_SIZE 10011
using namespace std;
const double eps = 1e-9;
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

double Length(Vector A){
    return sqrt(Dot(A, A));
}

double Dist(point x, point y) {
    return Length(x-y);
}

double Angle(Vector A, Vector B){
    return acos(Dot(A, B)/Length(A)/Length(B));
}

Vector Rotate(Vector A, double rad){ // rotation anti-clockwise with rad
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Vector Normal(Vector A){ // left rotation 90 degree
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
// if c is on the left of a,b
bool ToLeftTest(point a, point b, point c){
    return Cross(b - a, c - b) > 0;
}

double DistanceToLine(point P, point A, point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)/Length(v1));
}

double DistanceToSegment(point P, point A, point B){
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(sgn(Dot(v1, v2)) < 0)
        return Length(v2);
    if(sgn(Dot(v1, v3)) > 0)
        return Length(v3);
    return DistanceToLine(P, A, B);
}

// line l1 and line l2 interection
vector<point> GetLineIntersection(Line l1, Line l2){
    vector<point> ret;
    point P = l1.v, Q = l2.v;
    Vector v = l1.p, w = l2.p;
    if (sgn(Cross(v, w)) == 0) return ret; 
    Vector u = P-Q;
    double t = Cross(w, u)/Cross(v, w);
    point pp = P+v*t;
    ret.push_back(pp);
    return ret;
}
// check whether p is on the segment a1, a2
// the second equal sign is added only if p is the same as a1/a2 is allowed
bool OnSegment(point p, point a1, point a2){
    return sgn(Cross(a1-p, a2-p)) == 0 && sgn(Dot(a1-p, a2-p)) < 0;
}

vector<point> GetSegmentIntersection(segment s1, segment s2) {
    Line l1 = Line(s1.v1, s1.v2 - s1.v1), l2 = Line(s2.v1, s2.v2 - s2.v1);
    auto vc = GetLineIntersection(l1, l2);
    if (vc.empty()) return vc;
    if (!OnSegment(vc.front(), s1.v1, s1.v2) 
     || !OnSegment(vc.front(), s2.v1, s2.v2)) return vector<point>();
    return vc;
}

bool SegmentProperIntersection(point a1, point a2, point b1, point b2){
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    //if?????????????????????????????????????????????????????????????????????
    if(!sgn(c1) || !sgn(c2) || !sgn(c3) || !sgn(c4)){
        bool f1 = OnSegment(b1, a1, a2);
        bool f2 = OnSegment(b2, a1, a2);
        bool f3 = OnSegment(a1, b1, b2);
        bool f4 = OnSegment(a2, b1, b2);
        bool f = (f1|f2|f3|f4);
        return f;
    }
    return (sgn(c1)*sgn(c2) < 0 && sgn(c3)*sgn(c4) < 0);
}

bool cmp(point a, point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<point>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    point p1 = a[0], p2 = a.back();
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == (int) a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == (int) a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

double area(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}

double polarangle(double y, double x) {
    return atan2(y, x);
}


point p[MAX_SIZE];
int n;
double u, v, w;
bool check() {
    for(int i = 0; i < n; i++){
        if(p[i].x / v < p[i].y / u)return 0;
    }
    return 1;
}

bool ok(double x) {
    for(int i=0;i<n;i++){
        if(p[i].x / v > p[i].y / u + x)return 0;
    }
    return 1;
}

int main() {
    scanf("%d%lf%lf%lf",&n,&w,&v,&u);
    for(int i=0;i < n; ++i)scanf("%lf%lf",&p[i].x,&p[i].y);
    if(check()) {
        printf("%.10lf\n",w/u);
        return 0;
    }   
    double l = 0, r = 2e9, ans = 2e9;
    for (int i = 0 ; i < 100; ++i) {
        double mid = (l + r) / 2;
        if(ok(mid)) {
            r = mid;
            ans = mid;
        } else {
            l=mid;
        }
    }

    printf("%.10lf\n",w / u + ans);
    return 0;
}
