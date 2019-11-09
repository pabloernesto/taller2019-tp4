#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <fstream>
 
using namespace rapidjson;
 
//ESCRIBO EL JSON
int main() {
  std::ifstream ifs("test.json");
  IStreamWrapper isw(ifs);
  
  Document d;
  d.ParseStream(isw);

  printf("SCREEN_WIDTH: %d\n", d["SCREEN_WIDTH"].GetInt());
  printf("CAR_WIDTH: %f\n", d["CAR_WIDTH"].GetFloat());
}
