#include<bits/stdc++.h>
using namespace std;

struct point{
    double x,y;
};

struct box{
    double x1,y1,x2,y2;
};
bool isInside(point x, box s){
    return s.x1<=x.x && x.x<=s.x2 && s.y1<=x.y && x.y<=s.y2;
}
bool work1(point s, point t, box a, point& ans_s, point& ans_t){
    ans_s = s;
    ans_t = t;
    int flag = 0;
    point now = s;
    int unit = 30000;
    double add_x = (t.x - s.x) / unit, add_y = (t.y - s.y) / unit;
    for(int i=0;i<unit;i++){
        now.x += add_x;
        now.y += add_y;
        if(flag ==0 && isInside(now, a)){
            ans_s = now;
            flag = 1;
        }
        if(flag == 1 && !isInside(now, a)){
            ans_t = now;
            break;
        }
    }
    if(flag == 0){
        return false;
    }
    else{
        return true;
    }
}
int main(){
    point s,t;
    box a;
    scanf("%lf%lf%lf%lf",&a.x1, &a.y1, &a.x2, &a.y2);
    scanf("%lf%lf%lf%lf",&s.x, &s.y, &t.x, &t.y);
    point ans_s, ans_t;
    bool flag = work1(s, t, a, ans_s, ans_t);
    if(flag == true){
        printf("(%.2lf,%.2lf)\n(%.2lf,%.2lf)\n",ans_s.x,ans_s.y,ans_t.x,ans_t.y);
    }
    else{
        printf("-1\n");
    }
    return 0;
}
