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

  // Add a string member
  d.AddMember("yes", "we can", d.GetAllocator());

  // Add an int member
  d.AddMember("meaning of life, the universe, and everything",
    42, d.GetAllocator());

  // Add an object member
  {
    Value obj(kObjectType);
    obj.AddMember("code", "lyoko", d.GetAllocator());
    d.AddMember("this is an object", obj.Move(), d.GetAllocator());
  }

  // print d
  {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    printf("\n%s\n", buffer.GetString());
  }


  // d2 is an array
  Document d2(rapidjson::kArrayType);
  d2.PushBack("hello", d2.GetAllocator());
  d2.PushBack("world", d2.GetAllocator());

  // print d2
  {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d2.Accept(writer);
    printf("\n%s\n", buffer.GetString());
  }

  // print d2 using ValueIterator
  {
    auto arr = d2.GetArray();
    for (auto it = arr.begin(); it != arr.end(); it++)
      printf("%s\n", it->GetString());
  }
}
