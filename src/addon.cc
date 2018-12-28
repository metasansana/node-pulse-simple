#include <nan.h>
#include <pulse_simple.h>
#include <connection.h>

void InitAll(v8::Local<v8::Object> exports) {

  NodePulseSimple::Connection::Init(exports);

}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)
