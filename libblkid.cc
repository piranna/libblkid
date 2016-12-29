#include <nan.h>

#include <blkid.h>


/**
 * @param {string} token
 *        token name (e.g "LABEL" or "UUID") or unparsed tag (e.g. "LABEL=foo")
 * @param {string} value
 *        token data (e.g. "foo")
 *
 * @returns {string}
 *          allocated string with a device name.
 */
void evaluate_tag(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  // Check arguments
  if(info.Length() < 1)
    return Nan::ThrowTypeError("Token is missing");

  if(!info[0]->IsString())
    return Nan::ThrowTypeError("Token must be a string");

  if(info.Length() > 1 && !info[1]->IsString())
    return Nan::ThrowTypeError("Token must be a string or undefined");

  // Extract arguments data
  Nan::Utf8String token(info[0]);
  Nan::Utf8String value(info[1]);

  // Get the device path
  char* device = blkid_evaluate_tag(*token, *value, NULL);
  if(device == NULL)
    return Nan::ThrowTypeError("Device not found");

  // Return the device path
  v8::Local<v8::String> result = Nan::New(device).ToLocalChecked();
  info.GetReturnValue().Set(result);
}


void Init(v8::Local<v8::Object> exports)
{
  exports->Set(Nan::New("evaluate_tag").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(evaluate_tag)->GetFunction());
}

NODE_MODULE(libblkid, Init)
