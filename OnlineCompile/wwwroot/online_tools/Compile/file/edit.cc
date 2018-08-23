#include <iostream>
#include <unistd.h>

using namespace std;
int main()
{
   int i =10;
   while(i-- > 0){
cout<<"i="<<i<<"<br>"<<endl;
 sleep(1);

}
     
  return 0;
}