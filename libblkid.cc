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
  // Token
  if(info.Length() < 1)
    return info.GetReturnValue().Set(Nan::Null());

  if(info[0]->IsNull() || info[0]->IsUndefined())
    return info.GetReturnValue().Set(Nan::Null());

  if(!info[0]->IsString())
    return Nan::ThrowTypeError("Token must be a string");

  Nan::Utf8String token(info[0]);

  // Value
  char* ptrValue = NULL;
  if(info.Length() > 1)
  {
    if(info[1]->IsString())
    {
      Nan::Utf8String value(info[1]);
      ptrValue = *value;
    }
    else if(!info[1]->IsNull() && !info[1]->IsUndefined())
      return Nan::ThrowTypeError("Value must be a string, null or undefined");
  }

  // Get the device path
  char* device = blkid_evaluate_tag(*token, ptrValue, NULL);
  if(!device)
    return info.GetReturnValue().Set(Nan::Null());

  // Return the device path
  v8::Local<v8::String> result = Nan::New(device).ToLocalChecked();
  info.GetReturnValue().Set(result);
}

/**
 * All returned paths are canonicalized, device-mapper paths are converted to
 * the /dev/mapper/name format.
 *
 * @param {string} spec
 *        unparsed tag (e.g. "LABEL=foo") or path (e.g. /dev/dm-0)
 *
 * @returns {string}
 *          allocated string with a device name.
 */
void evaluate_spec(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  // Check arguments
  if(info.Length() < 1)
    return info.GetReturnValue().Set(Nan::Null());

  if(info[0]->IsNull() || info[0]->IsUndefined())
    return info.GetReturnValue().Set(Nan::Null());

  if(!info[0]->IsString())
    return Nan::ThrowTypeError("Spec must be a string");

  // Extract arguments data
  Nan::Utf8String spec(info[0]);

  // Get the device path
  char* device = blkid_evaluate_spec(*spec, NULL);
  if(!device)
    return info.GetReturnValue().Set(Nan::Null());

  // Return the device path
  v8::Local<v8::String> result = Nan::New(device).ToLocalChecked();
  info.GetReturnValue().Set(result);
}


void Init(v8::Local<v8::Object> exports)
{
  exports->Set(Nan::New("evaluate_tag").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(evaluate_tag)->GetFunction());
  exports->Set(Nan::New("evaluate_spec").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(evaluate_spec)->GetFunction());
}

NODE_MODULE(libblkid, Init)
