package com.silentorb.mythic;

import android.app.NativeActivity;
import android.os.Bundle;
import android.media.AudioManager;
import android.content.Context;
import android.util.DisplayMetrics;
import android.media.AudioManager.OnAudioFocusChangeListener;

public class MythicActivity extends NativeActivity {
    private OnAudioFocusChangeListener audioFocusChangeListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        AudioManager audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        this.audioFocusChangeListener = new OnAudioFocusChangeListener() {

            @Override
            public void onAudioFocusChange(int focusChange) {

            }
        };

        setVolumeControlStream(AudioManager.STREAM_MUSIC);
        audioManager.requestAudioFocus(audioFocusChangeListener,
                AudioManager.STREAM_MUSIC, AudioManager.AUDIOFOCUS_GAIN);

        super.onCreate(savedInstanceState);
    }

    public float get_xdpi() {
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        return metrics.xdpi;
    }

    public float get_ydpi() {
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        return metrics.ydpi;
    }
}
