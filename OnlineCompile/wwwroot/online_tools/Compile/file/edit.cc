#include <iostream>
#include <set>
using namespace std;
int main()
{
    int a[]={3,12,4,5,6};
    set<int> s;
    for(int i =0; i< 5; ++i)
       s.insert(a[i]);
    set<int>::iterator it = s.begin();
    while(it != s.end()){
       cout<<*it<<"<br>"<<endl
       ++it;
    }
    return 0;
}
