#include <nan.h>
#include <iostream>

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Handle;

NAN_METHOD (RepeatText) {
  Isolate* isolate = info.GetIsolate();
  
  // Check the number of arguments passed.
  if (info.Length() != 2 || !info[0]->IsString() || !info[1]->IsNumber()) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Problem with input")));
    return;
  }

  if (info[0]->IsString()) {
    String::Utf8Value tmp(info[0]->ToString());
    int num = info[1]->NumberValue();

    // Change string to c++ type
    std::string str = std::string(*tmp); 
    std::string str_ret;

    for (int i=0; i < num; i++) 
    {
      str_ret+=str;  
    }

    // Revert to v8 string and return 
    v8::Local<v8::String> v8String = v8::String::NewFromUtf8(isolate, str_ret.c_str(), v8::String::kNormalString);
    info.GetReturnValue().Set(v8String);
  }

}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, RepeatText);
}

NODE_MODULE(RepeatText, Init)
