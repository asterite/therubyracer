#include "v8.h"
#include "platform.h"
#include "v8_ref.h"
#include "v8_script.h"

using namespace v8;

namespace {
  VALUE New(VALUE self, VALUE source, VALUE source_name) {
    HandleScope scope;
    Local<String> src(rr_rb2v8(source)->ToString());
    Local<String> src_name(rr_rb2v8(source_name)->ToString());
    return rr_v8_ref_create(self, Script::Compile(src, src_name));
  }

  VALUE Compile(VALUE self, VALUE source, VALUE source_name) {
    HandleScope scope;
    Local<String> src(rr_rb2v8(source)->ToString());
    Local<String> src_name(rr_rb2v8(source_name)->ToString());
    return rr_v8_ref_create(self, Script::Compile(src, src_name));
  }

  VALUE Run(VALUE self) {
    HandleScope scope;
    Local<Script> script(V8_Ref_Get<Script>(self));
    Local<Value> result(script->Run());
    return result.IsEmpty() ? Qnil : rr_v82rb(result);
  }
}

void rr_init_script() {
  VALUE ScriptClass = rr_define_class("Script");
  rr_define_singleton_method(ScriptClass, "New", New, 2);
  rr_define_singleton_method(ScriptClass, "Compile", Compile, 2);
  rr_define_method(ScriptClass, "Run", Run, 0);
}
