#include <nan.h>
#include <node_pulse_simple.h>

void InitAll(v8::Local<v8::Object> exports) {

  NodePulseSimple::Connection::Init(exports);

}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)
