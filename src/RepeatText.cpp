#include <nan.h>
#include <iostream>

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Handle;

void RepeatText(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  
  // Check the number of arguments passed.
  if (args.Length() != 2 || !args[0]->IsString() || !args[1]->IsNumber()) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Problem with input")));
    return;
  }

  if (args[0]->IsString()) {
    String::Utf8Value tmp(args[0]->ToString());
    int num = args[1]->NumberValue();

    // Change string to c++ type
    std::string str = std::string(*tmp); 
    std::string str_ret;

    for (int i=0; i < num; i++) 
    {
      str_ret+=str;  
    }

    // Revert to v8 string and return 
    v8::Local<v8::String> v8String = v8::String::NewFromUtf8(isolate, str_ret.c_str(), v8::String::kNormalString);
    args.GetReturnValue().Set(v8String);
  }

}

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "RepeatText", RepeatText);
}

NODE_MODULE(RepeatText, Init)
