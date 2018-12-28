
#ifndef NODE_PULSE_SIMPLE_CONNECTION_H
#define NODE_PULSE_SIMPLE_CONNECTION_H

#include <nan.h>
#include <pulse/simple.h>

namespace NodePulseSimple
{

  /**
   * Connection to a pulse audio server.
   *
   * The Connection is either one for reading or writing, never both.
   */
  class Connection : public Nan::ObjectWrap {

    public:
      explicit Connection(pa_simple *h);
      static void Init(v8::Local<v8::Object> exports);
      void Write(const Nan::FunctionCallbackInfo<v8::Value>& info);

    private:
      pa_simple *handle;
      ~Connection(){};

      static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
      static Nan::Persistent<v8::Function> constructor;
      static Nan::Persistent<v8::Function> real_constructor;


 //     static void write(void data);
 //     static void close();

  };

}

#endif
