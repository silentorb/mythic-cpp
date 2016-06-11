package com.silentorb.mythic;

import android.app.NativeActivity;
import android.os.Bundle;
import android.media.AudioManager;
import android.content.Context;

public class MythicActivity extends NativeActivity {
    private android.media.AudioManager.OnAudioFocusChangeListener audioFocusChangeListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        AudioManager audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        this.audioFocusChangeListener = new android.media.AudioManager.OnAudioFocusChangeListener() {

            @Override
            public void onAudioFocusChange(int focusChange) {

            }
        };

        setVolumeControlStream(AudioManager.STREAM_MUSIC);
        audioManager.requestAudioFocus(audioFocusChangeListener,
                AudioManager.STREAM_MUSIC, AudioManager.AUDIOFOCUS_GAIN);

        super.onCreate(savedInstanceState);
    }
}
