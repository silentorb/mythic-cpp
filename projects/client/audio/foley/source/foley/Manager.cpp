//#include "Manager.h"
//
//namespace foley {
//
//  Manager::Manager(Library &library, aura::Engineer &engineer) :
//    player(engineer), library(library) {}
//
//  void Manager::play(int id, float volume) {
//    auto sound = library.get_sound(id);
//    sound->set_volume(volume);
//  }
//}