#include "core.hpp"
#include <cassert>
#include <climits>
int main(){
 using namespace embedded_feedback;
 Topic t[]={{"battery","battery",0},{"hot","hot",0}};
 assert(classify("BATTERY hot",t,2,96)==Ok);
 assert(t[0].count==1&&t[1].count==1);
 assert(classify("none",t,2,96)==Ok);
 assert(classify("",t,2,96)==InvalidInput);
 assert(classify("battery\n",t,2,96)==InvalidInput);
 assert(classify("hot\t",t,2,96)==InvalidInput);
 assert(t[0].count==1&&t[1].count==1);
 t[0].count=UINT_MAX;
 assert(classify("battery hot",t,2,96)==CapacityExceeded);
 assert(t[1].count==1); // atomic: no partial increments
 assert(classify("battery",t,2,0)==InvalidInput);
 assert(classify("battery",t,2,3)==CapacityExceeded);
}