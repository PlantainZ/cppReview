


///【3.MP算法，T(m+n)】
void preMp(const char *x,int m,int mpNext[]){
//          模式串指针   模式串长   指引该到地方的数组Next
    int i,j;
    i=0;            //模式串指针
    j=mpNext[0]-1;  //Next指针,j首先要等于-1;

    while(i<m){//当模式串的指针还没走到尽头的时候
        //初始状态:i=0,j=-1->i=1,j=0
        //第二轮：不匹配,i=1,j=0 -> j=mpNext[0]=-1 -> i=2,j=0
        //第三轮：不匹配，i=2,j=0 -> j=mpNext[0]=-1 -> i=3,j=0

        while(j>-1 && x[i]!=x[j] )  j=mpNext[j];
        //遇到不同，转舵，但是不会立刻写上数组
        //这里有个错误！！！x[i]&x[j]全都只会输出地址
        //如果已经开始匹配，并且当前模式字和next指针指向的模式字不等
        //j只有不读这一行的时候，也就是匹配到的时候，才会长进
        //那么现在Next指针就等于。。。
        mpNext[++i]=++j;    //首次的时候呢，它会让i=1,=j=0
        //这是正常匹配状体
        //那么j当前应该移动到。。。
    }

    cout<<"Next初始化完成："<<endl;
    for(i=0;i<m;i++) cout<<mpNext[i];
    cout<<endl;
}

void MP(string p,string t){
//传入： 模式串 ，长串
    int m=p.length();   //(p是模式串)m:模式串长
    int n=t.length();   //(t是长串)n:长串长
    if(m>n){    //模式串大于长串的话是绝对匹配不到的
        cerr<<"Unsuccessful match!"<<endl;
        return;
    }

    //=========================知识点：c_str()
    //返回一个指向正规C字符串的指针常量, 内容与本string串相同.
    //为了不破坏数组，为了世界和平~!!注意全是char!!
    const char* x=p.c_str();    //模式串指针
    const char* y=t.c_str();    //长串指针

    int i=0,j=0,mpNext[m+1];//这里的m+1
    //是因为在最后要预留出多一个空位，防止出现匹配多次的情况出现
    memset(mpNext,0,sizeof(int)*(m+1));
    preMp(x,m,mpNext);      //这里开始搞Next数组

    while(j<n){//假如长串指针已经开始匹配又没到最后
        while(i>-1 && x[i]!=y[j]) i=mpNext[i];
        //模式串字!=长串字：提取mpNext，让模式串字到该到的位置
        i++;
        j++;    //否则匹配的话，两者指针共同移动
    }//和next数组同一个操作。。。

    if(i>=m){
        cout<<"Matching index found at:"<<j-i<<endl;
        i=mpNext[i];
    }
}

int main(int argc,char** argv){
    cout<<"now,begin"<<endl;
    string long1="ctcaatcaaatcat";
    string short1="caatcat";
    MP(short1,long1);
}
