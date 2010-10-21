#ifndef ENGINE_H__
#define ENGINE_H__

#include <string>

#include "v8.h"

class Engine {
 public:
  Engine();

  ~Engine();

  bool Execute(const std::string& code, double* elapsed);
 private:
  v8::Persistent<v8::Context> context_;

  v8::Context::Scope scope_;

  v8::HandleScope handle_scope_;
};

#endif // ENGINE_H__
