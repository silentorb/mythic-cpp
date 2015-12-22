#include "Workshop.h"
#include "desktop/Desktop_Frame.h"

int main(int argc, char *const argv[]) {

  auto frame = desktop::Desktop_Frame("Mythic Workshop");
  while (!frame.closing) {
    frame.update();
  }
  return 0;
}
