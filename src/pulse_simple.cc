#include <nan.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse_simple.h>
#include <connection.h>

namespace NodePulseSimple
{

  void Connect(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    int flag = 0;
    pa_simple *handle = NULL;

    pa_sample_spec ss = {
      .format = PA_SAMPLE_S16LE,
      .rate = 44100,
      .channels = 2
    };

    if(info.Length() != 1) {

      Nan::ThrowTypeError("connect(): incorrect number of arguments!");
      return;

    } 

    if (!info[0]->IsString()) {

      Nan::ThrowTypeError("connect(): argument name must be a string!");
      return;

    }

    //Nan::Utf8String* str = new Nan::Utf8String(info[0]);
    Nan::Utf8String str(info[0]);
    int len = str.length();

    if(len > NODE_PULSE_SIMPLE_MAX_NAME_LENGTH) {

      Nan::ThrowTypeError("connect(): Name too long!");
      return;

    }

    std::string strc(*str, len);
  
    const char* name = strc.c_str();

    handle = pa_simple_new(NULL, name, PA_STREAM_PLAYBACK, NULL, 
        "sound", &ss, NULL, NULL, &flag);

    if(!handle) {

      std::string msg = std::string(__FILE__) +
                        std::string(": pa_simple_new() failed: %s\n") +
                        std::string(pa_strerror(flag));

      Nan::ThrowTypeError(msg.c_str());

      return;

    }

    Connection* c = new Connection(handle);

    c->doWrap(info);

    info.GetReturnValue().Set(info.This());

  }

}
