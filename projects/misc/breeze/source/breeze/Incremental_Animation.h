#pragma once

#include <promising/Promise.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "dllexport.h"
#include "Animation_Delegate.h"
#include "Animation.h"

namespace breeze {

  typedef std::function<bool(float)> Animation_Update;

  class Position_Animation : public Animation {
      promising::Empty_Promise &promise;
      glm::vec3 start;
      glm::vec3 destination;
      glm::vec3 &target;
      float speed;
      float total_distance;

  public:
      Position_Animation(glm::vec3 &target, glm::vec3 destination, float speed) :
        speed(speed), destination(destination), target(target),
        promise(promising::Promise<void>::defer()) {
        total_distance = glm::distance(start, destination);
      }

      virtual ~Position_Animation() override { }

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