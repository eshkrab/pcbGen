#include "ofApp.h"

eagleFile *eFile;
ledRing *ring;
//--------------------------------------------------------------
void ofApp::setup(){

  eFile = new eagleFile;
  ring = new ledRing;
  setGui();
}

//--------------------------------------------------------------
void ofApp::setGui(){

  vector<string> names;
  names.push_back("NEOPIXEL");
  names.push_back("DOTSTAR");
  gui = new ofxUISuperCanvas("RING GENERATOR");
  gui->addSpacer();
  
  gui->addTextInput("OD", "outer diameter")->setAutoUnfocus(false);
  gui->addTextInput("WD", "width")->setAutoClear(false);
  gui->addTextInput("SEG", "how many segments")->setAutoClear(true);
  gui->addTextInput("LED", "how many leds")->setAutoUnfocus(true);
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
    if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER){
      output = ti->getTextString();
      if(name == "OD")
        ring->orad = ofToFloat(output)/2;
      else if (name == "WD")
        ring->width = ofToFloat(output);
      else if(name == "SEG")
        ring->seg = ofToInt(output);
      else if(name == "LED")
        ring->led = ofToFloat(output);
    }
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
void ofApp::draw(){

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
