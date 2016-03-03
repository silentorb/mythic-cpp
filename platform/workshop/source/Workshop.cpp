#include "mythic/Mythic_Engine.h"
#include <iostream>
#include <desktop/Desktop.h>
#include "laboratory/Lab.h"

using namespace mythic;
using namespace std;
using namespace laboratory;

int main(int argc, char *const argv[]) {

  try {

    desktop::Desktop desk("Mythic Workshop", 800, 600);
    auto& engine = desk.get_engine();

    engine.get_myth<Lab>("lab");
    engine.loop();
  }
  catch (exception &e) {
    auto message = e.what();
    std::cout << message;
  }

  return 0;
}
