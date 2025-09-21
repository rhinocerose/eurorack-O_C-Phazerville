#include "OC_core.h"

volatile std::vector<std::function<void()>> fn_queue;

void OC::CORE::DeferTask(std::function<void()> func) {
  fn_queue.push_back(func);
}
void OC::CORE::FlushTasks() {
  for (auto &&func : fn_queue) {
    func();
  }
  fn_queue.clear();
}
