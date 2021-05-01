---
youtubeId:UY_dY53kszk
---

## Introduction

Division occurence is an audio visual project that aims to explore the multi definition of space through sound. Heavily insipred by experiemental music notation, the flexibility of experimental music notation enables performers to expand(vertical or horizontal), contract, or remain the space as it seems to be. Releasing nodes from two dimension to freely float to right, left, back, forward, up, down, and all points between without reading direction. Composers are regarding sound as points that scatter in the space of notation, enabling performers to start from random point and connect them freely, the space can expand, shrink or remain as defined. The commonality of connecting points as a composition is adding another dimension that beyond euclidean geometry.

Music, often defined as the science or art of ordering tones or sounds in succession, in combination, and in temporal relationships to produce a composition having unity and continuity. In my perspective, it is about how people dividing and arranging a static or non-static space and so does visual. Even just a thin string is cutting the space into half. Two parallel lines can trick your brain process the visual has a depth. In this work, I want to interprete the idea space by playing with audio and visual by using the simplest elements.

{% include youtubePlayer.html id=page.UY_dY53kszk %}

If the embeded video fail to play, here's the video link [click](https://youtu.be/UY_dY53kszk) 

### Technical and process 

This project aims to create music only with pure sine waves with sound effects like envelopes, filters, frequency modulation and so on. The biggest challenge I encountered is mapping the sound data to create visuals. I have try different numbers of mapping to see the results match the sound or not.

-ofxOsc

I use touchOsc to send accelerometer data to openframework and map the xy value(-1~1) to the position on the screen. The data is very glitchy. Without using low pass filter, the point on the screen will be very rough and irregular.

-ofxMaxim

The audio is based on sinewaves with 8 different pitches. Metronome ticks per 7 frames every so often. Iteration increase every 4 bars, the pitch will also change based on the root chords for the arpeggio. The osc messages are mapped into physical position on the screen, and also influencing the audio output, x position as the cutoff point of the lowpass filter, y position as the resonance of the filter.  

[Link](url) and ![Image]()
