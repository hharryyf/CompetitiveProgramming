/* stupid problem, cannot understand WTF it's trying to say, copy paste other's code directly */
#include<bits/stdc++.h>
using namespace std;
const int N=1E5+7;
int arr[N];
int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        memset(arr,0,sizeof(arr));
        int a,b,day;
        scanf("%d%d%d",&a,&b,&day);
        for(int j=1;j<=a;j++) scanf("%d",&arr[j]);
        int a1=a;
        int b1=b;
        while(day--){
            b1=a1;
            a1=1;
            for(int j=1;j<=a;j++){
                if(b1>arr[j]){
                    b1-=arr[j];
                    a1++;
                }
                else break;
            }
            if(a1==1&&b1==1) break;
        }
        printf("Case #%d: %d-%d\n",i,a1,b1);
    }
    return 0;
}