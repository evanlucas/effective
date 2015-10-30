#include <nan.h>
#include <node.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // setuid, getuid
#include <pwd.h>  // getpwnam()
#include <grp.h>  // getgrnam()

using v8::String;
using v8::FunctionTemplate;
using v8::Value;
using v8::Handle;
using v8::Local;
using Nan::Utf8String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

static const uid_t uid_not_found = static_cast<uid_t>(-1);
static const gid_t gid_not_found = static_cast<gid_t>(-1);

static gid_t gid_by_name(const char* name) {
  struct group pwd;
  struct group* pp;
  char buf[8192];

  errno = 0;
  pp = NULL;

  if (getgrnam_r(name, &pwd, buf, sizeof(buf), &pp) == 0 && pp != NULL) {
    return pp->gr_gid;
  }

  return gid_not_found;
}

static gid_t gid_by_name(Local<Value> value) {
  if (value->IsUint32()) {
    return static_cast<gid_t>(value->Uint32Value());
  } else {
    Utf8String name(value);
    return gid_by_name(*name);
  }
}

static uid_t uid_by_name(const char* name) {
  struct passwd pwd;
  struct passwd* pp;
  char buf[8192];

  errno = 0;
  pp = NULL;

  if (getpwnam_r(name, &pwd, buf, sizeof(buf), &pp) == 0 && pp != NULL) {
    return pp->pw_uid;
  }

  return uid_not_found;
}

static uid_t uid_by_name(Local<Value> value) {
  if (value->IsUint32()) {
    return static_cast<uid_t>(value->Uint32Value());
  } else {
    Utf8String name(value);
    return uid_by_name(*name);
  }
}

NAN_METHOD(GetEUid) {
  info.GetReturnValue().Set(static_cast<uint32_t>(geteuid()));
}

NAN_METHOD(GetEGid) {
  info.GetReturnValue().Set(static_cast<uint32_t>(getegid()));
}

NAN_METHOD(SetEUid) {
  if (!info[0]->IsUint32() && !info[0]->IsString()) {
    return Nan::ThrowTypeError("seteuid argument must be a number or string");
  }

  uid_t uid = uid_by_name(info[0]);

  if (uid == uid_not_found) {
    return Nan::ThrowError("seteuid user id does not exist");
  }

  if (seteuid(uid)) {
    return Nan::ThrowError(Nan::ErrnoException(errno, "seteuid", "", NULL));
  }
}

NAN_METHOD(SetEGid) {
  if (!info[0]->IsUint32() && !info[0]->IsString()) {
    return Nan::ThrowTypeError("setguid argument must be a number or string");
  }

  gid_t gid = gid_by_name(info[0]);

  if (gid == gid_not_found) {
    return Nan::ThrowError("setegid user id does not exist");
  }

  if (setegid(gid)) {
    return Nan::ThrowError(Nan::ErrnoException(errno, "setegid", "", NULL));
  }
}

NAN_MODULE_INIT(Init) {
  Set(target, New<String>("geteuid").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetEUid)).ToLocalChecked());
  Set(target, New<String>("getegid").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetEGid)).ToLocalChecked());
  Set(target, New<String>("seteuid").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(SetEUid)).ToLocalChecked());
  Set(target, New<String>("setegid").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(SetEGid)).ToLocalChecked());
}

NODE_MODULE(effective, Init)
