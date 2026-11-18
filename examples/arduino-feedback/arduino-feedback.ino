#include "../../cpp/core.hpp"
using namespace embedded_feedback;
Topic topics[]={{"battery","battery",0},{"heat","hot",0},{"network","offline",0}};
char line[97]; size_t used=0; bool overflow=false;
void setup(){Serial.begin(115200);Serial.println(F("Feedback demo: send <=96 ASCII bytes per line")); }
void loop(){
 while(Serial.available()){
  const char c=(char)Serial.read();
  if(c=='\r')continue;
  if(c=='\n'){
   if(overflow){Serial.println(F("REJECT: line too long"));}else{
    line[used]=0;
    Status s=classify(line,topics,3,96);
    if(s!=Ok)Serial.println(F("REJECT: invalid input"));
    else {for(unsigned i=0;i<3;++i){Serial.print(topics[i].name);Serial.print(':');Serial.println(topics[i].count);}}
   }
   used=0;overflow=false;
  }else if(used>=sizeof(line)-1)overflow=true;
  else if(!overflow)line[used++]=c;
 }
}
