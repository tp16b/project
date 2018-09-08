#include <iostream>

using namespace std;
#include <map>
int main( )
{ 
   map<string, int> mp;
   mp["hello"] = 2;
   mp["sort"] = 4;
   
   map<string, int>::iterator it = mp.begin();
   while(it != mp.end()){
     cout<<it->first<<": "<<it->second<<"<br>";
      ++it;
   }
   cout<<"change world！！"<<endl;
   return 0;
}
