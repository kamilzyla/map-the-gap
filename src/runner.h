#ifndef RUNNER_H_
#define RUNNER_H_

#include <string>
#include <utility>
#include <vector>


class Runner {
 public:
  typedef void (*Func)();

  Runner(std::string env_var_name, Func default_func);
  void registerFunc(std::string when, Func what);
  void run() const;

 private:
  typedef std::pair<std::string, Func> Entry;

  const std::string env_;
  const Func default_;
  std::vector<Entry> actions_;
};

#endif  // RUNNER_H_
