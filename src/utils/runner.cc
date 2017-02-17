#include <cstdlib>
#include "runner.h"

Runner::Runner(std::string env_var_name, Func default_func):
    env_(env_var_name), default_(default_func) {}

void Runner::registerFunc(std::string when, Func what) {
  actions_.push_back(std::make_pair(when, what));
}

void Runner::run() const {
  char *env_val = getenv(env_.c_str());
  if (!env_val) {
    default_();
    return;
  }

  for (size_t i = 0; i < actions_.size(); ++i) {
    if (actions_[i].first == env_val) {
      actions_[i].second();
      break;
    }
  }
}
