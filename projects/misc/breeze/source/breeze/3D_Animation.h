#pragma once

#include <promising/Promise.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "dllexport.h"
#include "Animation_Delegate.h"
#include "Animation.h"

namespace breeze {

  typedef std::function<bool(float)> Animation_Update;

  class Position_Animation_Incremental : public Animation {
      promising::Empty_Promise &promise;
      glm::vec3 start;
      glm::vec3 destination;
      glm::vec3 &target;
      float speed;
      float total_distance;
      const Curve_Delegate curve;

  public:
      Position_Animation_Incremental(glm::vec3 &target, glm::vec3 destination, float speed,
                                     const Curve_Delegate curve) :
        speed(speed), destination(destination), target(target),
        promise(promising::Promise<void>::defer()), curve(curve) {
        total_distance = glm::distance(start, destination);
      }

      virtual ~Position_Animation_Incremental() override {}

      virtual bool update(float delta) override {
        auto angle = glm::normalize(destination - target);
        target += angle * speed * delta;
        if (glm::distance(target, start) >= total_distance) {
          target = destination;
          promise.resolve();
          return true;
        }

        return false;
      }

      promising::Empty_Promise &get_promise() const {
        return promise;
      }
  };

//  class Position_Animation_Over_Time : public Base_Timed_Animation {
//      glm::vec3 start;
//      glm::vec3 gap;
//      glm::vec3 &target;
//
//  public:
//      Position_Animation_Over_Time(glm::vec3 &target, glm::vec3 destination, float duration, Curve_Delegate curve) :
//        Base_Timed_Animation(duration, curve),
//        start(target), gap(destination - target), target(target) {
//      }
//
//      virtual ~Position_Animation_Over_Time() override {}
//
//      virtual bool update(float delta) override {
//        counter += delta * duration;
//        if (counter >= 1) {
//          target = start + gap;
//          promise.resolve();
//          return true;
//        }
//
//        target = start + gap * curve(counter);
//        return false;
//      }
//  };
//
//  class Slerp_Animation : public Base_Timed_Animation {
//      glm::quat start;
//      glm::quat destination;
//      glm::quat &target;
//
//  public:
//      Slerp_Animation(glm::quat &target, glm::quat destination, float duration, const Curve_Delegate curve) :
//        start(target), Base_Timed_Animation(duration, curve), destination(destination), target(target) {
//
//      }
//
//      virtual ~Slerp_Animation() override {}
//
//      virtual bool update(float delta) override {
//        counter += delta / duration;
//        if (counter >= 1) {
//          target = destination;
//          return true;
//        }
//
//        target = glm::slerp(start, destination, counter);
//        return false;
//      }
//
//      promising::Empty_Promise &get_promise() const {
//        return promise;
//      }
//  };

  struct Slerp_Updater {
      static glm::quat get_value(glm::quat &start_value, const glm::quat final_value, float counter) {
        return glm::slerp(start_value, final_value, counter);
      }
  };

//  class Orientation_Animation : public Animation {
//      promising::Empty_Promise &promise;
//      glm::quat start;
//      glm::quat destination;
//      glm::quat &target;
//      float speed;
//      float total_distance;
//
//  public:
//      Orientation_Animation(glm::quat &target, glm::quat destination) :
//        speed(speed), destination(destination), target(target),
//        promise(promising::Promise<void>::defer()) {
//        total_distance = glm::distance(start, destination);
//      }
//
//      virtual ~Orientation_Animation() override { }
//
//      virtual bool update(float delta) override {
//        auto angle = glm::normalize(destination - target);
//        target += angle * speed * delta;
//        if (glm::distance(target, start) >= total_distance) {
//          target = destination;
//          promise.resolve();
//          return true;
//        }
//
//        return false;
//      }
//
//      promising::Empty_Promise &get_promise() const {
//        return promise;
//      }
//  };
}