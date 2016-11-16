#pragma once

#include "Interactive.h"

namespace bloom {
  namespace flowers {

    template<int Event_Count>
    class Interactive_Template : public Interactive {
        const Event_Id *events[Event_Count];
        Event_Delegate delegates[Event_Count];

    public:
        virtual const string get_class_name() const override {
          return "Interactive_Template";
        }

//        Interactive_Template(initializer_list<const Event_Id *> initializer) {
//          int i = 0;
//          for (auto delegate : initializer) {
//            events[i++] = delegate;
//          }
//        }
        template<typename ... Events>
        Interactive_Template(Events ... event_arguments):
          events{event_arguments...} {
        }

        virtual bool check_event(const Event &event) override {
          for (int i = 0; i < Event_Count; ++i) {
            if (&event.get_id() == events[i]) {
              delegates[i](event);
              return true;;
            }
          }
          return false;
        }

        void on(const Event_Id &id, const Event_Delegate &delegate) {
          for (int i = 0; i < Event_Count; ++i) {
            if (&id == events[i]) {
              delegates[i] = delegate;;
            }
          }
        }

        bool is_inside(const Event &event) const {
          return Interactive:: point_is_inside(this, event.get_point());
        }
    };
  }
}