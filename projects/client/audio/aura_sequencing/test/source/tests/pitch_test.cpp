#include <aura/sequencing/Pitch.h>
#include "gtest/gtest.h"

using namespace std;
using namespace aura::sequencing;

namespace aura {
  namespace sequencing {

    std::ostream& operator<<(::std::ostream& os, const Pitch & pitch) {
      return os << pitch.get_name();  // whatever needed to print bar to os
    }
  }
}
TEST(Pitch_Test, test_test) {
  const static Key keys[] = {
    Key::C,
    Key::E,
    Key::G,
  };

//  EXPECT_EQ(pitches::C5, pitches::G4.traverse(keys, 3, 1));
  EXPECT_EQ(pitches::E5, pitches::G4.traverse(keys, 3, 2));
  EXPECT_EQ(pitches::E5, pitches::G5.traverse(keys, 3, -1));

//  EXPECT_EQ(30, second->get_cache().y.near);
//  EXPECT_EQ(60, third->get_cache().y.near);
}