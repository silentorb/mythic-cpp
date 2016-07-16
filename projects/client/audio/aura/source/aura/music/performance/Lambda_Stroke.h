#pragma once

#include "dllexport.h"
#include "aura/music/performance/Stroke.h"
#include <functional>

//namespace aura {
//  class Note;
//
////  typedef std::function<void(Buffer&, float)> Stroke_Updater;
//  typedef std::function<float(float)> Stroke_Updater;
//
//  class MYTHIC_EXPORT Lambda_Stroke : public Stroke {
//      Stroke_Updater updater;
//
//  public:
//      Lambda_Stroke(const Note &note, Stroke_Updater updater) : Stroke(note),
//      updater(updater){
//
//      }
//
//      virtual float update(float delta) override {
//        Stroke::update(delta);
//        return updater(delta);
//      }
//  };
//}