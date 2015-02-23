#include "ofApp.h"

eagleFile *eFile;
ledRing *ring;
//--------------------------------------------------------------
void ofApp::setup(){

  eFile = new eagleFile;
  ring = new ledRing;
  ring->orad = ring->irad = ring->mrad = 0;
  ring->led = 0;
  ring->seg = 0;
  ring->led_type = 0;

  setGui();
  text.loadFont("sans-serif", 8);
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofSetColor(ofColor::darkGray);
  text.drawString("Outer Diameter: "+ ofToString(ring->orad*2), 100, ofGetHeight()-60); 
  text.drawString("Number of Segments: "+ ofToString(ring->seg), 100, ofGetHeight()-45); 
  text.drawString("Number of LEDs: "+ ofToString(ring->led), 100, ofGetHeight()-30); 
  text.drawString("Outer Radius: "+ ofToString(ring->orad), 300, ofGetHeight()-60); 
  text.drawString("Inner Radius: "+ ofToString(ring->irad), 300, ofGetHeight()-45); 
  text.drawString("Average Radius: "+ ofToString(ring->mrad), 300, ofGetHeight()-30); 
  ofSetColor(106, 218, 70, 100);
  ofCircle(ofGetWidth()/2,ofGetHeight()/2, ring->orad); 
}

//--------------------------------------------------------------
void ofApp::setGui(){

  vector<string> names;
  names.push_back("NEOPIXEL");
  names.push_back("DOTSTAR");
  gui = new ofxUISuperCanvas("RING GENERATOR");
  gui->addSpacer();
  
  gui->addTextInput("OD", "outer diameter")->setAutoClear(false);
  gui->addTextInput("WD", "width")->setAutoClear(false);
  gui->addTextInput("SEG", "how many segments")->setAutoClear(false);
  gui->addTextInput("LED", "how many leds")->setAutoUnfocus(false);
  gui->addRadio("LED_TYPE", names, OFX_UI_ORIENTATION_VERTICAL);
  gui->addSpacer();
  gui->addLabelButton("GENERATE", false);
  gui->addLabelButton("SAVE", false);

  ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
  string name = e.getName();
  int kind = e.getKind();
  string output;

  if(kind == OFX_UI_WIDGET_TEXTINPUT){
    ofxUITextInput *ti = (ofxUITextInput *) e.widget;
    output = ti->getTextString();
    if(name == "OD")
      ring->orad = ofToFloat(output)/2;
    else if (name == "WD")
      ring->width = ofToFloat(output);
    else if(name == "SEG")
      ring->seg = ofToInt(output);
    else if(name == "LED")
      ring->led = ofToFloat(output);
  }else if (name == "LED_TYPE"){
    ofxUIRadio *radio = (ofxUIRadio *) e.widget;
    if(radio->getActiveName() == "NEOPIXEL") ring->led_type = NEO;
    else if (radio->getActiveName() == "NEOPIXEL") ring->led_type = DOT;

  }else if (name == "GENERATE"){
    ring->irad = ring->orad - ring->width;
    ring->mrad = ring->irad + ring->width/2;
  }else if (name == "SAVE"){
    ofxUIButton *button = (ofxUIButton *) e.widget;
    if(!button->getValue()){
      ofFileDialogResult saveFileResult = ofSystemSaveDialog("ledRing.brd", "Save your ring");
      if (saveFileResult.bSuccess){
        eFile->createFile(ring);
        eFile->saveFile(saveFileResult.filePath);
      }
    }
  }

}
//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
