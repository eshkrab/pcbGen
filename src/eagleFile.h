#pragma once

#include "ofApp.h"
#define NEO 0
#define DOT 1

//should be able to input mean radius, outer radius or inner radius, width, how many sections to break it in, number of leds
class wire{
  public: 
    float x1;
    float x2;
    float y1;
    float y2;
    float width;
    int layer;
    float curve;

    string toString(){
      string str = "<wire x1=\"" + ofToString(x1) + "\" y1= \""+ ofToString(y1) + "\" x2= \"";
      str += ofToString(x2) + "\" y2= \"" + ofToString(y2) + "\" width= \"" + ofToString(width);
      str += "\" layer= \"" + ofToString(layer);
      if(curve > 0){
        str += "\" curve= \"";
        str += ofToString(layer);
      }
      str += "\"/>\n";

      return str;
    }


};
class ledRing{
  public:
    float irad, orad, mrad;
    float width;
    int seg;
    int led;
  int led_type;
    vector <wire> outlines;

    void basicOutline();
};


class eagleFile{
  public:
    ofBuffer write_buff;
    ledRing *ring;

    //file componenets
    vector <string> header;
    vector <string> plain;
    vector <string> libraries;
    
    vector <string> mid_file; //holds attr, var, classes, designrules, autorouter
    vector <string> elements;
    vector <string> signals;
    vector <string> footer;

    //functs
    void createFile(ledRing *ring);

  void readIn(vector <string> *str_vec, string addr);

    void writeOut(vector <string> str_vec, string addr);
    int saveFile(string path);
    void writeHeader();
    void writePlain();
    void writeLib();
    void writeMidFile();
    void writeElem();
    void writeSig();
    void writeFooter();

};
