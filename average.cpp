#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc,char *argv[]){
int sum = 0;
int count = 0;
    for(int i = 1; i < argc;i++){
        sum += atoi(argv[i]);
        count++;
    }
    cout <<"---------------------------------" << endl;
    cout <<"Average of "<< count << " numbers = "<< sum/double(count) << endl;
    cout <<"---------------------------------" << endl;
return 0;
}
