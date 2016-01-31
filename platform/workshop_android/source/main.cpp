#include "Mythic_Android.h"
#include <android_native_app_glue.h>
#include <iostream>
#include "laboratory/Lab.h"
#include "logger.h"

#include "android_utility.h"

using namespace mythic;
using namespace std;
using namespace laboratory;

void initialize_workshop(Mythic_Engine &engine) {
  engine.get_myth<Lab>("lab");
}

void android_main(android_app *app) {
  log_info("Workbench is starting.");
  auto mythic = new Mythic_Android(app);
  mythic->set_initializer(initialize_workshop);
  app_dummy();
  mythic->run();
  delete mythic;
}
