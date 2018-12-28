
#include <pulse/simple.h>
#include <pulse/error.h>
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
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

    tpl->SetClassName(Nan::New("Connection").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(0);

    // Configure the object's runtime prototype.
    ///Nan::SetPrototypeMethod(tpl, "write", Write);
    //Nan::SetPrototypeMethod(tpl, "read", Read);

    // Make the constructor use the function from the template we created.
    constructor.Reset(tpl->GetFunction());

    // Add the function to the module's scope.
    exports->Set(Nan::New("Connection").ToLocalChecked(), tpl->GetFunction());

  }

  //New is used to create new instances of a Connection.
  //However we do not allow the Connection to be instantiated in ES land.
  void Connection::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    Nan::ThrowTypeError(Nan::New("Connection: use connect() instead!")
        .ToLocalChecked());

  }

  void Connection::doWrap(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    this->Wrap(info.This());

  }

}
