#include <iostream>
#include <vector>
using  namespace  std;

int main(){

    long long int n, m;
    cin >> n;
    cin >> m;
    if(n - m - 1 > 0){
        cout << n - m - 1 << " ";
    }
    else{
        cout << 0 << " ";
    }

    long long int ans = 3;
    if(m >= 3){
        for(int i = 2; i<10000000;i++){
            if((i * (i - 1)) / 2 >= m){
                ans = i;
                break;
            }
        }
        cout << n - ans;
    }
    else{
        if(n - m - 1 > 0){
            cout << n - m - 1 << " ";
        }
        else{
            cout << 0 << " ";
        }
    }



}