//#pragma once
//
//#include <aura/engineering/Buffer.h>
//
//#include <functional>
//#include <aura/sequencing/Note.h>
//#include "Stroke.h"
//
//using namespace aura::sequencing;
//
//namespace aura {
//  namespace sequencing {
//    class Conductor;
//  }
//
//  namespace performing {
//    class Musical_Stroke : public Stroke {
//    protected:
//        float frequency;
//        Note note;
//
//    public:
//        Musical_Stroke(const Note &note) :
//          Stroke(note.get_duration()),
//          frequency(note.get_frequency()),
//          note(note) {}
//
//        virtual ~Musical_Stroke() {}
//
//        const float &get_frequency() const {
//          return frequency;
//        }
//
//        const Note &get_note() const {
//          return note;
//        }
//    };
//  }
//}