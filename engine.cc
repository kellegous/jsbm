#include "engine.h"

#include "timer.h"

Engine::Engine() : context_(v8::Context::New()),
                   scope_(context_) {
}

Engine::~Engine() {
  context_.Dispose();
}

bool Engine::Execute(const std::string& code, double* elapsed) {
  Timer timer;
  v8::Handle<v8::Script> script = v8::Script::Compile(
      v8::String::New(code.c_str()),
      NULL);
  if (script.IsEmpty())
    return false;
  script->Run();
  *elapsed = timer.GetElapsed();
  return true;
}
