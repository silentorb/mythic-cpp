#include "Workshop.h"
#include "lookinglass/Desktop_Frame.h"

int main(int argc, char *const argv[]) {

  auto frame = lookinglass:: Desktop_Frame("Mythic Workshop");
  while(!frame.closing){
    frame.update();
  }
  return 0;
}
