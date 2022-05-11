#include <bits/stdc++.h>

using namespace std;

const double Pi = acos(-1.0);
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

    point operator *(double p) {
        return point(x * p, y * p);
    }
};

typedef point Vector;

struct segment {
    point v1, v2;
};

struct Line {
    point v, p;
    Line(point v, point p) : v(v), p(p) {}
};

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}

double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

bool Onsegment(point p, point a1, point a2) {
    return sgn(Cross(a1-p, a2-p)) == 0 && sgn(Dot(a1-p, a2-p)) <= 0;
}


void format(Line ln,double& A,double& B,double& C) {
    A = ln.p.y;
    B = -ln.p.x;
    C = ln.v.y*ln.p.x-ln.v.x*ln.p.y;
}
 
point mirror(point P, Line ln) {
    point Q;
    double A,B,C;
    format(ln,A,B,C);
    Q.x=((B*B-A*A)*P.x-2*A*B*P.y-2*A*C)/(A*A+B*B);
    Q.y=((A*A-B*B)*P.y-2*A*B*P.x-2*B*C)/(A*A+B*B);
    return Q;
}

vector<point> GetLineIntersection(Line l1, Line l2) {
    vector<point> ret;
    Vector P = l1.v, Q = l2.v, v = l1.p, w = l2.p;
    if (sgn(Cross(v, w)) == 0) return ret;
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    point pp = P + v * t;
    ret.push_back(pp);
    return ret;
}

vector<point> GetSegmentIntersection(segment s1, segment s2) {
    Line l1 = Line(s1.v1, s1.v2 - s1.v1), l2 = Line(s2.v1, s2.v2 - s2.v1);
    auto vc = GetLineIntersection(l1, l2);
    if (vc.empty()) return vc;
    if (!Onsegment(vc.front(), s1.v1, s1.v2) || !Onsegment(vc.front(), s2.v1, s2.v2)) return vector<point>();
    return vc;
}

bool SegmentproperIntersection(point a1, point a2, point b1, point b2, bool allow=true) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    if (allow && (!sgn(c1) || !sgn(c2)  || !sgn(c3) || !sgn(c4))) {
        bool f1 = Onsegment(b1, a1, a2);
        bool f2 = Onsegment(b2, a1, a2);
        bool f3 = Onsegment(a1, b1, b2);
        bool f4 = Onsegment(a2, b1, b2);
        bool f = (f1|f2|f3|f4);
        return f;
    }

    return (sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0);
}

int N;
double W, H;
point src, target;
vector<segment> segt;

int main() {
    int i, j;
    scanf("%d%lf%lf", &N, &W, &H);
    segt.push_back(segment{point(0, 0), point(W, 0)});
    segt.push_back(segment{point(0, 0), point(0, H)});
    segt.push_back(segment{point(W, 0), point(W, H)});
    segt.push_back(segment{point(0, H), point(W, H)});
    scanf("%lf%lf%lf%lf", &src.x, &src.y, &target.x, &target.y);
    for (i = 0 ; i < N; ++i) {
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        segt.push_back(segment{point(x1, y1), point(x2, y2)});
    }

    bool valid = true;
    // check no bounce
    segment tmp = segment{src, target};
    for (auto sg : segt) {
        if (SegmentproperIntersection(sg.v1, sg.v2, tmp.v1, tmp.v2)) {
            // cout << "intersect " << sg.v1.x << " " << sg.v1.y << " " << sg.v2.x << " " << sg.v2.y << endl;
            valid = false;
            break;
        }
    }

    if (valid) {
        printf("YES\n");
        return 0;
    }

    // check one bounce

    for (i = 0 ; i < (int) segt.size(); ++i) {
        if (Cross(segt[i].v1 - src, segt[i].v1 - target) == 0 && Cross(segt[i].v2 - src, segt[i].v2 - target) == 0) continue;
        if (SegmentproperIntersection(segt[i].v1, segt[i].v2, src, target)) continue;
        point bounce = mirror(src, Line(segt[i].v1, segt[i].v2 - segt[i].v1));
        //cout << "bounce point " << bounce.x << " " << bounce.y << endl;
        vector<point> res = GetSegmentIntersection(segment{bounce, target}, segt[i]);
        if (res.empty()) continue;
        point rpt = res.front();
        if ((sgn(rpt.x - segt[i].v1.x) == 0 && sgn(rpt.y - segt[i].v1.y) == 0) || (sgn(rpt.x - segt[i].v2.x) == 0 && sgn(rpt.y - segt[i].v2.y) == 0)) continue;
        //cout << "point of reflection " << rpt.x << " " << rpt.y << endl;
        valid = true;
        for (j = 0 ; j < (int) segt.size(); ++j) {
            if (i == j) continue;
            if (SegmentproperIntersection(src, rpt, segt[j].v1, segt[j].v2) || SegmentproperIntersection(rpt, target, segt[j].v1, segt[j].v2)) {
                valid = false;
                break;
            }       
        }

        if (valid) {
            printf("YES\n");
            return 0;
        }
    }

    printf("NO\n");
    return 0;
}