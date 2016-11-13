#pragma once

#include "commoner/dllexport.h"
#include "Sequence.h"

namespace aura {
  namespace sequencing {

  typedef vector<Pitch> Arpeggio;

  void create_arpeggio(Sequence &sequence, initializer_list<Pitch> initializer, float scale = 1);
//  Arpeggio *create_arpeggio(initializer_list<Pitch> initializer);


//  class Arpeggio {
//      vector<Pitch> notes;
//
//  public:
//      Arpeggio(initializer_list<Pitch> initializer);
//
//  };
}}