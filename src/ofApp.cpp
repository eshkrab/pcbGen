#include "ofApp.h"

brdFile *bFile;
schFile *sFile;
ledRing *ring;
//--------------------------------------------------------------
void ofApp::setup(){

  ofBackground(ofColor::lightGray);

  bFile = new brdFile;
  sFile = new schFile;
  ring = new ledRing;
  ring->orad = ring->irad = ring->mrad = 0;
  ring->led = 0;
  ring->width = 0;
  ring->seg = 0;
  ring->led_type = 0;

  setGui();
  text.loadFont("sans-serif", 8);
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofSetColor(78, 78, 78);

  text.drawString("Two Sided? "+ ofToString(ring->two_side), 100, ofGetHeight()-85); 
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

  vector<string> leds;
  leds.push_back("NEOPIXEL");
  leds.push_back("DOTSTAR");
  vector<string> back_front;
  back_front.push_back("ONE SIDE");
  back_front.push_back("BOTH SIDES");
  gui = new ofxUISuperCanvas("RING GENERATOR");
  gui->addSpacer();
  gui->addTextInput("OD", "outer diameter " + ofToString(ring->orad*2))->setAutoClear(true);
  gui->addTextInput("WD", "width "+ ofToString(ring->width))->setAutoClear(true);
  gui->addTextInput("SEG", "how many segments "+ ofToString(ring->seg))->setAutoClear(true);
  gui->addTextInput("LED", "how many leds "+ ofToString(ring->led))->setAutoUnfocus(true);
  gui->addRadio("LED_TYPE", leds, OFX_UI_ORIENTATION_VERTICAL);
  gui->addSpacer();
  gui->addRadio("LED_SIDE", back_front, OFX_UI_ORIENTATION_VERTICAL);
  gui->addSpacer();
  gui->addLabelButton("GENERATE", false);
  gui->addLabelButton("SAVE", false);
  gui->autoSizeToFitWidgets();  

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
    else if (radio->getActiveName() == "DOTSTAR") ring->led_type = DOT;

  }else if (name == "LED_SIDE"){
    ofxUIRadio *radio = (ofxUIRadio *) e.widget;
    if(radio->getActiveName() == "ONE SIDE") ring->two_side = 0;
    else if (radio->getActiveName() == "BOTH SIDES") ring->two_side = 1;

  }else if (name == "GENERATE"){
    ofxUIButton *button = (ofxUIButton *) e.widget;
    if(!button->getValue()){
      ring->irad = ring->orad - ring->width;
      ring->mrad = ring->irad + ring->width/2;
      ring->LPS = floor(ring->led/ring->seg);
      ring->basicOutline();
      ring->createParts();
      ring->createInst();
    }
  }else if (name == "SAVE"){
    ofxUIButton *button = (ofxUIButton *) e.widget;
    if(!button->getValue()){
      ofFileDialogResult savbFileResult = ofSystemSaveDialog("ledRing", "Save your ring");
      if (savbFileResult.bSuccess){
        sFile->createFile(ring);
        sFile->saveFile(savbFileResult.filePath+".sch");
        bFile->createFile(ring);
        bFile->saveFile(savbFileResult.filePath+".brd");
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
