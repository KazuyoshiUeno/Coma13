#include "Waves.h"

void Waves::setup(){
    shader.load("waves");
    counter = 0;
    level = 0;
    for (int i = 0; i < MAX; i++) {
        amp[i] = 0;
    }
    
    fx = new ofxSCSynth("col_closefx");
    fx->create();
}
void Waves::update(){
    for (int i = 0; i < counter; i++) {
        amp[i] += 0.001;
        if(amp[i] > 1.0){
            amp[i] = 1.0;
        }
    }
}
void Waves::draw(){
    ofBackground(0);
    float time = ofGetElapsedTimef();
    float resolution[] = {ofGetWidth(), ofGetHeight()};
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("num", counter);
    shader.setUniform1fv("amp", amp, MAX);
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
}

void Waves::mousePressed(int x, int y, int button){
    
}
void Waves::mouseReleased(int x, int y, int button){
    
}
void Waves::keyPressed(int key){
    if (key == 'a') {
        counter++;
        level = 0.0;
        
        WaveParams w;
        w.synth = new ofxSCSynth("col_closesaw");
        w.synth->create();
        float detune = ofRandom(-0.15, 0.15);
        int nth = counter;
        //startTime = ofGetElapsedTimef();
        
        w.synth->set("gate", 1);
        w.synth->set("amp", 0.75);
        w.synth->set("rq", 1.0);
        w.synth->set("n", nth);
        w.synth->set("detune", detune);
        w.synth->create();
        waveParams.push_back(w);
    }
}
string Waves::getName(){
    return "waves";
}