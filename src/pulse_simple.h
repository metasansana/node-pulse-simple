#ifndef NODE_PULSE_SIMPLE_H
#define NODE_PULSE_SIMPLE_H 
#define NODE_PULSE_SIMPLE_MAX_NAME_LENGTH  1024 * 4

#include <nan.h>

namespace NodePulseSimple {

  void Connect(const Nan::FunctionCallbackInfo<v8::Value>& info);

}

#endif
