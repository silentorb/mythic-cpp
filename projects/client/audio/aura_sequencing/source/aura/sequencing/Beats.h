#pragma once

namespace aura {
  namespace sequencing {

    using Beats = double;

//    class Beats {
//        int count;
//        float division;
//
//    public:
//        Beats(int count, float division = 1) : count(count), division(division) {}
//
//        int get_count() const {
//          return count;
//        }
//
//        float get_division() const {
//          return division;
//        }
//
//        Beats operator+(const Beats &other) const {
//          return {count + other.count, division + other.division};
//        }
//
//        bool operator>(const Beats &other) const {
//          if (count > other.count)
//            return true;
//
//          if (count == other.count)
//            return division > other.division;
//
//          return false;
//        }
//    };
  }
}