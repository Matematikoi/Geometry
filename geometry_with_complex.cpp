#include <bits/stdc++.h>
using namespace std;
typedef double value;
typedef complex<value> pto;
typedef long long ll;
#define X real()
#define Y imag()
#define INF 10000000000
#define EPS 0.0000001
namespace std {
  bool operator < (pto a, pto b) { // bottom-left
    return a.Y != b.Y ? a.Y < b.Y : a.X < b.X;
  }
}
value dot(pto a, pto b)   { return (conj(a)*b).X; }
//module of the cross product
// if a is less than 180 clockwise from b cross(a,b)>0
value cross(pto a, pto b) { return (conj(a)*b).Y; }
value dist2(pto a, pto b) { return dot(a-b, a-b); }
value dist (pto a, pto b){return sqrt(dist2(a,b));}
//returns angle in radians
double angle (pto a, pto o, pto b){
    pto oa=a-o,ob=b-o;
    return atan2((double)cross(oa,ob), (double)dot(oa,ob));
}
//for convex hull. bottom-left
int ccw(pto a, pto b, pto c) {
  b -= a; c -= a;
  if (cross(b,c) > 0)      return +1; // counter clockwise
  if (cross(b,c) < 0)      return -1; // clockwise
  if (dot(b,c) < 0)        return +2; // c--a--b on line
  if (dot(b,b) < dot(c,c)) return -2; // a--b--c on lne
  return 0;
}
//ordena counterclockwise
struct CMP{
    pto r;
    CMP(pto r):r(r){}
    int cuad(const pto& a)const{
        if (a.X>0 and a.Y>=0)return 0;
        if (a.X<=0 and a.Y>0)return 1;
        if (a.X<0 and a.Y<=0)return 2;
        if (a.X>=0 and a.Y<0)return 3;
        return -1;
    }
    bool cmp(const pto& a, const pto& b)const {
        int c= cuad(a), d= cuad(b);
        if (c==d)return a.Y*b.X<a.X*b.Y;
        else return c<d;
    }
    bool operator() (const pto& a, const pto&b){
        return cmp(pto (a.X-r.X,a.Y-r.Y), pto(b.X-r.X, b.Y-r.Y));
    }
};


//x<0->-1; x=0->0; x>0->1
int sgn(ll x){return x<0? -1:!!x;}
struct line {
    line(){}
    //Ax+By=C
    value a,b, c;
    line (value a, value b, value c):a(a),b(b),c(c){}
    line (pto p, pto q):a(q.Y-p.Y), b (p.X-q.X), c (a*p.X+b*p.Y){}
    //A que lado de la linea esta p.
    //No funciona para ver si p está en la linea
    int side(pto p){return sgn( ll(a)*p.X + ll(b)*p.Y *p.Y-c);}
};
//En caso de que se manejen doubles return abs(l1.a*l2.b-l2.a*l1.b)<EPS;
bool paralelas (line l1, line l2){return l1.a*l2.b-l2.a*l1.b==0;}
//Solo con double
pto inter ( line l1, line l2){
    value det =l1.a*l2.b-l2.a*l1.b;
    if(abs(det)<EPS)return pto(INF, INF);//paralelas
    return pto(l2.b*l1.c-l1.b*l2.c, l1.a*l2.c-l2.a*l1.c)/det;
}



struct segm{
    pto s, f;
    segm(pto s, pto f):s(s), f(f){}
    pto closest(pto p){
        value l = dist2(s, f);
        if(l==0.)return s;
        value t = dot((p-s),(f-s))/l;
        if ( t<0.)return s;//don't write if is a line
        if (t>1.)return f;//don't write if is a line
        return s+(f-s)* t;//works best with double
    }
    //doesn't work in int, because sqrt of dist
    bool inside (pto p){return abs(dist(s,p)+dist(p,f)-dist(s,f))<EPS;}
};
pto inter (segm s1 , segm s2){
    pto r= inter (line (s1.s, s1.f), line (s2.s, s2.f));
    if (s1.inside(r) and s2.inside(r))return r;
    return pto(INF, INF);
}

struct rect{
    //lower-left and upper-right corners.
    pto lw ,up;
    rect():lw(pto(0,0)), up(pto(1,1)){}
    rect(pto lw, pto up): lw(lw), up(up){}
};
//returns if there's an intersection and stores it in r
bool inter(rect a, rect b, rect &r){
    r.lw=pto(max(a.lw.X, b.lw.X), max(a.lw.Y, b.lw.Y));
    r.up=pto (min(a.up.X, b.up.X), min (a.up.Y, b.up.Y));
    //chech case when only and edge is common
    return r.lw.X<r.up.X and r.lw.Y<r.up.Y;
}

//area of polygon
value area (vector<pto>& p){
    value area=0;
    int n=p.size();
    for (int i=0;i<n;++i)area+=cross(p[i], p[(i+1)%n]);
    return abs(area)/2;
}




int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    CMP too (pto(0,0));
    value a, b;
    vector<pto> foo;
    while (cin>>a>>b){
        foo.push_back(pto(a,b));
    }
    cout<<area(foo);

}
