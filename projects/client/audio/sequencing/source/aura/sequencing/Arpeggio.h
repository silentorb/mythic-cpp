#pragma once

#include "commoner/dllexport.h"
#include "Sequence.h"

namespace aura {
  namespace sequencing {

  typedef vector<Pitch> Arpeggio;

  MYTHIC_EXPORT void create_arpeggio(Sequence &sequence, initializer_list<Pitch> initializer, float scale = 1);
//  MYTHIC_EXPORT Arpeggio *create_arpeggio(initializer_list<Pitch> initializer);


//  class MYTHIC_EXPORT Arpeggio {
//      vector<Pitch> notes;
//
//  public:
//      Arpeggio(initializer_list<Pitch> initializer);
//
//  };
}}