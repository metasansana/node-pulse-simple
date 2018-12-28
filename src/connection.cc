
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse_simple.h>
#include <connection.h>

namespace NodePulseSimple 
{

  //makes the famous Object.constructor property available as
  //a persitent handle so it is never garbage collected.
  Nan::Persistent<v8::Function> Connection::constructor;

  Connection::Connection(pa_simple *h) : handle(h) {}

  //Used by v8 to create runtime instances.
  void Connection::Init(v8::Local<v8::Object> exports) {

    //Create a new scope that tracks all the handles created.
    Nan::HandleScope scope; 

    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> cons = 
      Nan::New<v8::FunctionTemplate>(New);

    cons->SetClassName(Nan::New("Connection").ToLocalChecked());
    cons->InstanceTemplate()->SetInternalFieldCount(0);

    // Configure the object's runtime prototype.
    ///Nan::SetPrototypeMethod(tpl, "write", Write);
    //Nan::SetPrototypeMethod(tpl, "read", Read);
    //
    Nan::SetMethod(cons, "connect", Connect);

    // Make the constructor use the function from the template we created.
    constructor.Reset(cons->GetFunction());

    // Add the function to the module's scope.
    exports->Set(Nan::New("Connection").ToLocalChecked(), 
        cons->GetFunction());

  }

  //New is used to create new instances of a Connection.
  //However we do not allow the Connection to be instantiated in ES land.
  void Connection::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    Nan::ThrowTypeError(Nan::New("Connection: use connect() instead!")
        .ToLocalChecked());

  }

   void Connection::Connect(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    Nan::EscapableHandleScope scope;

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
    
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    c->Wrap(obj);

    info.GetReturnValue().Set(obj);


  }

}
