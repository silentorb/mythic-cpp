
#include "Mythic_iOS.h"
#include "lookinglass/House.h"
#include "clienting/Client.h"
#include "mythic/Mythic_Engine.h"
#include "lookinglass/glow.h"
#include "lookinglass/glow_gl.h"
#include "iOS_Input.h"
#include "audio/Speaker.h"
#include <shading/shader_processing.h>

#import <AudioUnit/AudioUnit.h>

const char * get_resource_path() {
    return [[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/"] UTF8String];
}

const char * get_library_path() {
  return [[NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0] UTF8String];
}

AudioComponentInstance audio_unit;
audio::Speaker *speaker;

OSStatus update_audio_buffer(
                    void *inRefCon,
                    AudioUnitRenderActionFlags *ioActionFlags,
                    const AudioTimeStamp *inTimeStamp,
                    UInt32 inBusNumber,
                    UInt32 inNumberFrames,
                    AudioBufferList *ioData) {

    // auto speaker = (audio::Speaker*)userdata;
    auto buffer = ioData->mBuffers[inBusNumber];
    auto data = (float*)buffer.mData;
//    speaker->update(data, inNumberFrames);
        speaker->update(data, buffer.mDataByteSize);
    return 0;
}

class iOS_Speaker : public audio::Speaker {
public:
  virtual audio::Device_Settings start() override {
      AudioComponentDescription defaultOutputDescription;
      defaultOutputDescription.componentType = kAudioUnitType_Output;
      defaultOutputDescription.componentSubType = kAudioUnitSubType_RemoteIO;
      defaultOutputDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
      defaultOutputDescription.componentFlags = 0;
      defaultOutputDescription.componentFlagsMask = 0;

      AudioComponent defaultOutput = AudioComponentFindNext(NULL, &defaultOutputDescription);
      if (!defaultOutput)
          throw runtime_error("Cannot find default output");

      OSErr err = AudioComponentInstanceNew(defaultOutput, &audio_unit);
      if (!audio_unit)
          throw runtime_error("Error creating unit.");

      AURenderCallbackStruct input;
      input.inputProc = update_audio_buffer;
      input.inputProcRefCon = this;
      err = AudioUnitSetProperty(audio_unit,
                                 kAudioUnitProperty_SetRenderCallback,
                                 kAudioUnitScope_Input,
                                 0,
                                 &input,
                                 sizeof(input));

      if (err != noErr)
          throw runtime_error("Error setting callback.");

      //NSAssert1(err == noErr, @"Error setting callback: %ld", err);

      const int four_bytes_per_float = 4;
      const int eight_bits_per_byte = 8;
      AudioStreamBasicDescription format;
      format.mChannelsPerFrame = 1;
      format.mSampleRate = 44100;
      format.mFormatID = kAudioFormatLinearPCM;
      format.mFormatFlags =
      kAudioFormatFlagsNativeFloatPacked; // | kAudioFormatFlagIsNonInterleaved;
      format.mBytesPerPacket = four_bytes_per_float;
      format.mFramesPerPacket = 1;
      format.mBytesPerFrame = four_bytes_per_float;
      format.mBitsPerChannel = four_bytes_per_float * eight_bits_per_byte;
      err = AudioUnitSetProperty (audio_unit,
                                  kAudioUnitProperty_StreamFormat,
                                  kAudioUnitScope_Input,
                                  0,
                                  &format,
                                  sizeof(AudioStreamBasicDescription));
      if (err != noErr)
          throw runtime_error("Error creating unit.");

//      NSAssert1(err == noErr, @"Error setting stream format: %ld", err);

      err = AudioOutputUnitStart(audio_unit);
      if (err != noErr)
          throw runtime_error("Error starting unit.");

      return {
          static_cast<int>(format.mSampleRate),
          4096,
          static_cast<unsigned char>(format.mChannelsPerFrame)
      };
  }

  virtual void stop() override {
      AudioOutputUnitStop(audio_unit);
      AudioUnitUninitialize(audio_unit);
      AudioComponentInstanceDispose(audio_unit);
      audio_unit = nullptr;
  }
};

const string iOS_File_Loader(const string &path) {
    NSString *formatted_path = [[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/"]
                                stringByAppendingString:[NSString stringWithUTF8String:(path).c_str()]];
//    NSBundle * b =[NSBundle mainBundle];
//    NSString *resource_path = [[NSBundle mainBundle] pathForResource:@"solid.fragment.glsl"  ofType:nil];
    NSError *error = nil;
    NSString *content = [NSString stringWithContentsOfFile:formatted_path
                                                  encoding:NSASCIIStringEncoding
                                                     error:&error];

    if (content == nil)
        throw std::runtime_error("Could not open file \"" + path + "\"");

//    BOOL fileExists = [[NSFileManager defaultManager] fileExistsAtPath:formatted_path];
//    NSLog(@"\n%lu\n%@",(unsigned long)NSASCIIStringEncoding,error);
    return std::string([content UTF8String]);
}

iOS_Frame::iOS_Frame(EAGLContext* context, int width, int height)
    :context(context), width(width), height(height) {
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGFloat screen_scale = [[UIScreen mainScreen] scale];
    CGSize pixels = CGSizeMake(screenBounds.size.width * screen_scale, screenBounds.size.height * screen_scale);
  set_dimensions(pixels.width, pixels.height);
}

float iOS_Frame::get_pixel_scale() const {
  return [[UIScreen mainScreen] scale];
}

void iOS_Frame::create_window(const char *title, int width, int height) {

}

void  iOS_Frame::update_events() {
}


void iOS_Frame::flip_buffer() {
    [context presentRenderbuffer:GL_RENDERBUFFER];
}
void iOS_Frame::release() {

}

void iOS_Frame::initialize_window() {

}

Mythic_iOS::Mythic_iOS(EAGLContext* context, const lookinglass::Graphic_Options &graphic_options):context(context) {

    try {

        engine=unique_ptr<mythic::Mythic_Engine>{new mythic::Mythic_Engine(*this, graphic_options)};

    engine->get_client().load();

        initialize_mythic_engine(*engine);
    }
    catch(std::exception ex) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:[NSString stringWithUTF8String:ex.what()] userInfo:nil];
    }
    catch(char const* message) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:[NSString stringWithUTF8String:message] userInfo:nil];
    }
    catch(...) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:@"Unknown" userInfo:nil];
    }
}

framing::Platform_Frame *Mythic_iOS::create_frame(const lookinglass::Graphic_Options &graphic_options) {
    return new iOS_Frame(context, 0, 0);
}

haft::Input_Source *Mythic_iOS::create_input_source(haft::Input_Configuration & config) {
    return new iOS_Input(config);
}

audio::Speaker *Mythic_iOS::create_speaker() {
  speaker = new iOS_Speaker();
  return speaker;
}

void Mythic_iOS::update() {
    engine->update();
}

mythic::Shader_Processor Mythic_iOS::create_shader_processor() {
  return [](shading::Shader_Type type, const string &source) {
    auto included = shading::process_includes(source, type, resourceful::File_Loader(iOS_File_Loader));
    return string("precision highp float;\n\n") + shading::olden(included, type);

//      return "#version 430\n" + shading::process_includes(source, type, resourceful::File_Loader(Desktop_File_Loader));
  };
}

mythic::File_Loader Mythic_iOS::create_file_loader() {
  return iOS_File_Loader;
}

const string Mythic_iOS::get_storage_path() {
  return string(get_library_path()) + "/";
}