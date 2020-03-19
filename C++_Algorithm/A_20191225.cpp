
///【1.Prim算法】

#define MAX 10
#define INF 32767
void prim(int* map,int n){
    int next=0,ans=0;
    int dis[MAX];

    mst(vis,0);
    for(int i=0;i<MAX;i++){
        dis[i]=map[1][i];
    }
    vis[1]=1;
    //initiate DONE

    for(int i=1;i<n-1;i++){
        mindist=INF;
        for(int j=1;j<n-1;j++){
            if(!vis[j] && dis[j]<mindist){
                mindist=dis[j];
                next =j;
            }
        }

        if(mindist==INF){
            printf('?\n');
            return;
        }
        for(int j=1;j<n;j++){
            if(!vis[j] && dis[j]>map[next][j]){
                dis[j]=map[next][j];
            }
        }
        printf("%d",ans)
    }

}
