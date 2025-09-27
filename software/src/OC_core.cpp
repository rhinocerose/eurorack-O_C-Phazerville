#include "OC_core.h"

extern char _heap_end[], *__brkval;

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

int OC::CORE::FreeRam() {
#ifdef __IMXRT1062__
  auto heap = _heap_end - __brkval;
  return heap;
#else
  char top;
  return &top - __brkval;
#endif
}
