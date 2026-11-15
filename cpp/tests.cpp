#include "core.hpp"
#include <cassert>
int main(){using namespace embedded_feedback;
 Topic t[]={{"battery","battery",0},{"heat","hot",0}};
 assert(classify("HOT battery",t,2)==Ok);
 assert(t[0].count==1&&t[1].count==1);
 assert(classify(nullptr,t,2)==InvalidInput);
 assert(classify("long",t,2,2)==CapacityExceeded);
 Topic bad[]={{"bad","",0}};assert(classify("abc",bad,1)==InvalidInput);
}