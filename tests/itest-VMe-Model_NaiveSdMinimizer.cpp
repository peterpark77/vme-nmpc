#include "catch.hpp"

#include "../src/VMeNmpcEngine.hpp"
#include "../src/NmpcModels/VMeModel.hpp"
#include "../src/NmpcMinimizers/VMeNaiveSdMinimizer.hpp"
#include "../src/Loggers/JsonLogger.hpp"
#include "FakeExecutor.hpp"

#include "../src/trig.hpp"

struct TestSetup {
  std::unique_ptr<VMeNmpcEngine> eng{nullptr};
  unsigned int nmpcHorizon = 50;
  float timeInterval = 0.1f;
  float speed = .4;
  VMeNmpcInitPkg init;

  TestSetup() {
    init.horizonSize = nmpcHorizon;
    init.timeInterval = timeInterval;
    init.cruiseSpeed = speed;
    init.Q = 1;
    init.Q0 = init.Q / 2;
    init.R = init.Q / 4;
    new VMeModel{init};
    new VMeNaiveSdMinimizer{init};
    new JsonLogger(init);
    eng = std::make_unique<VMeNmpcEngine>(init);
  }

  TestSetup(std::string logFilePath) {
    init.horizonSize = nmpcHorizon;
    init.timeInterval = timeInterval;
    init.cruiseSpeed = speed;
    init.Q = 1;
    init.Q0 = init.Q / 2;
    new VMeModel{init};
    new VMeNaiveSdMinimizer{init};
    new JsonLogger(init, logFilePath);
    eng = std::make_unique<VMeNmpcEngine>(init);
  }
  auto* model() { return dynamic_cast<VMeModel*>(eng->_getModelPointer_()); }
  auto* minimizer() { return eng->_getMinimizerPointer_(); }
};

bool isStopCmd(VMeCommand* cmd) { return dynamic_cast<VMeStop*>(cmd); }
bool isNullCmd(VMeCommand* cmd) { return dynamic_cast<VMeNullCmd*>(cmd); }
bool isMoveCmd(VMeCommand* cmd) { return dynamic_cast<VMeV*>(cmd); }

TEST_CASE("Whatever") {
  TestSetup test{"itest.log.json"};
  FakeExecutor exec(test.eng.get());

  test.eng->seed(xyth{0, 0, 0}, fp_point2d{3, 4});
  while (isMoveCmd(exec.commandFromLastNotify.get())) {
    test.eng->seed(xyth{
        test.model()->getX()[1], test.model()->getY()[1],
        test.model()->getTh()[1],
    });
  }
}