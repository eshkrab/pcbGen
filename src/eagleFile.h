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
class part{
  public:
    string name;
    string library;
    string deviceset;
    string device;

    string toString(){
      string str = "<part name=\"" + name + "\" library=\"" + library + "\" deviceset=\"";
      str += deviceset + "\" device=\"" + device + "\"/>\n";
      return str;
    }
};
class instance{
  public:
    part *p;
    string gate;
    float x;
    float y;

    string toString(){
      string str = "<instance part=\"" + p->name + "\" gate=\"" + gate + "\" x=\"";
      str += ofToString(x) + "\" y=\"" + ofToString(y) + "\"/>\n";
    }
};
class ledRing{
  public:
    float irad, orad, mrad;
    float width;
    int seg;
    int led;
    int led_type;
    int two_side;
    vector <wire> outlines;
    vector <part> parts;

    void basicOutline();
    void createParts();
};


class brdFile{
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
    void writeHeader(string path);
    void writePlain(string path);
    void writeLib(string path);
    void writeMidFile(string path);
    void writeElem(string path);
    void writeSig(string path);
    void writeFooter(string path);

};

class schFile{
  public:
    ofBuffer write_buff;
    ledRing *ring;

    //file componenets
    vector <string> header;
    vector <string> libraries;
    
    vector <string> attr_var_class; //holds attr, var, classes, designrules, autorouter
    vector <string> parts;
    vector <string> instances;
    vector <string> nets;
    vector <string> footer;

    //functs

    void readIn(vector <string> *str_vec, string addr);
    void createFile(ledRing *ring);

    int saveFile(string path);
    void writeHeader(string path);
    void writeLib(string path);
    void writeAttrVar(string path);
    void writeParts(string path);
    void writeInst(string path);
    void writeNet(string path);
    void writeFooter(string path);

};
