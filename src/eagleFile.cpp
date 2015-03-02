#include "eagleFile.h"

//--------------------------------------------------BRD FILE FUNCTIONS
void brdFile::readIn(vector <string> *str_vec, string addr){
  ofBuffer buff = ofBufferFromFile(addr);

  if(buff.size()){
    while(!buff.isLastLine()) {
      // move on to the next line
      string line = buff.getNextLine();
      if(line.empty() == false) {
        str_vec->push_back(line+"\n");
      }
    }
  }

}
void brdFile::createFile(ledRing * r){
  ring=r;
  //load in static things
  readIn(&header,     "stat/brd_header.txt");
  readIn(&mid_file,   "stat/brd_mid_file.txt");
  readIn(&libraries,  "stat/brd_libs.txt");
  readIn(&footer,     "stat/brd_footer.txt");
}

void brdFile::writeHeader(string path){
  int count=0;
  for(vector<string>::iterator it = header.begin(); it != header.end(); ++it){
    if(count<140){
      write_buff.append(*it);
    }
  }

}
void brdFile::writePlain(string path){
  write_buff.append("<plain>\n");
  for(vector<wire>::iterator it=ring->outlines.begin(); it !=ring->outlines.end(); ++it){
    write_buff.append(it->toString());
  }
  write_buff.append("</plain>\n");

}
void brdFile::writeLib(string path){
  write_buff.append("<libraries>\n");
  for(vector<string>::iterator it = libraries.begin(); it!=libraries.end(); ++it){
    write_buff.append(*it);
  }
  write_buff.append("</libraries>\n");

}
void brdFile::writeMidFile(string path){
  for(vector<string>::iterator it = mid_file.begin(); it!=mid_file.end(); ++it){
    write_buff.append(*it);
  }

}
void brdFile::writeElem(string path){
  write_buff.append("<elements>\n");

  write_buff.append("</elements>\n");

}
void brdFile::writeSig(string path){
  write_buff.append("<signals>\n");

  write_buff.append("</signals>\n");

}
void brdFile::writeFooter(string path){
  for(vector<string>::iterator it = footer.begin(); it!=footer.end(); ++it){
    write_buff.append(*it);
  }

}
int brdFile::saveFile(string path){
  

  writeHeader(path);
  writePlain(path);
  writeLib(path);
  writeMidFile(path);
  writeElem(path);
  writeSig(path);
  writeFooter(path);

  int fileWritten = ofBufferToFile(path, write_buff);
  write_buff.clear();
  return fileWritten;

}
//--------------------------------------------------SCH FILE FUNCTIONS
void schFile::readIn(vector <string> *str_vec, string addr){
  ofBuffer buff = ofBufferFromFile(addr);

  if(buff.size()){
    while(!buff.isLastLine()) {
      // move on to the next line
      string line = buff.getNextLine();
      if(line.empty() == false) {
        str_vec->push_back(line+"\n");
      }
    }
  }

}
void schFile::createFile(ledRing * r){
  ring=r;
  //load in static things
  readIn(&header,     "stat/sch_header.txt");
  readIn(&libraries,  "stat/sch_libs.txt");
  readIn(&footer,     "stat/sch_footer.txt");
}

void schFile::writeHeader(string path){
  int count=0;
  for(vector<string>::iterator it = header.begin(); it != header.end(); ++it){
    if(count<140){
      write_buff.append(*it);
    }
  }
}
void schFile::writeLib(string path){
  write_buff.append("<libraries>\n");
  for(vector<string>::iterator it = libraries.begin(); it!=libraries.end(); ++it){
    write_buff.append(*it);
  }
  write_buff.append("</libraries>\n");

}
void schFile::writeAttrVar(string path){
  //GONNA HARDCODE CLASSES IN FOR NOW CAUSE WHY NOT
  write_buff.append("<attributes>\n");
  write_buff.append("</attributes>\n");
  write_buff.append("<variantdefs>\n");
  write_buff.append("</variantdefs>\n");
  write_buff.append("<classes>\n");
  write_buff.append("<class number=\"0\" name=\"default\" width=\"0\" drill=\"0\">\n");
  write_buff.append("</class>\n");
  write_buff.append("<class number=\"1\" name=\"power\" width=\"0.254\" drill=\"0.6096\">\n");
  write_buff.append("<clearance class=\"1\" value=\"0.254\"/>\n");
  write_buff.append("</class>\n");
  write_buff.append("<class number=\"2\" name=\"gnd\" width=\"0.254\" drill=\"0.6096\">\n");
  write_buff.append("<clearance class=\"2\" value=\"0.254\"/>\n");
  write_buff.append("</class>\n");
  write_buff.append("<class number=\"3\" name=\"usbvcc\" width=\"0.254\" drill=\"0.6096\">\n");
  write_buff.append("<clearance class=\"3\" value=\"0.254\"/>\n");
  write_buff.append("</class>\n");
  write_buff.append("<class number=\"4\" name=\"aref\" width=\"0.254\" drill=\"0.6096\">\n");
  write_buff.append("<clearance class=\"4\" value=\"0.254\"/>\n");
  write_buff.append("</class>\n");
  write_buff.append("</classes>\n");
}
void schFile::writeParts(string path){
  write_buff.append("<parts>\n");
  ofLog()<< "buffer size: "+ ofToString(write_buff.size());
  for(vector<part>::iterator it=ring->parts.begin(); it !=ring->parts.end(); ++it){
    write_buff.append(it->toString());
  }
  //for(int i=0; i<ring->parts.size(); i++){
  //  ofLog()<<"oi";
  //  write_buff.append(ring->parts[i].toString());
  //}

  write_buff.append("</parts>\n");
  write_buff.append("<sheets>\n");
  write_buff.append("<sheet>\n");
  write_buff.append("<plain>\n");
  write_buff.append("</plain>\n");
}
void schFile::writeInst(string path){
  write_buff.append("<instances>\n");

  write_buff.append("</instances>\n");
}

void schFile::writeNet(string path){
  write_buff.append("<busses>\n");
  write_buff.append("</busses>\n");
  write_buff.append("<nets>\n");
  for(vector<string>::iterator it = nets.begin(); it!=nets.end(); ++it){
    write_buff.append(*it);
  }
  write_buff.append("</nets>\n");

}

void schFile::writeFooter(string path){
  for(vector<string>::iterator it = footer.begin(); it!=footer.end(); ++it){
    write_buff.append(*it);
  }

}
int schFile::saveFile(string path){
  

  writeHeader(path);
  writeLib(path);
  writeAttrVar(path);
  writeParts(path);
  writeInst(path);
  writeNet(path);
  writeFooter(path);

  int fileWritten = ofBufferToFile(path, write_buff);
  write_buff.clear();
  return fileWritten;

}
//--------------------------------------------------OTHER SHIT
void ledRing::createParts(){

  //STATIC PARTS
  part *p = new part[8];
  p[0].name = "OUT_CXN";
  p[0].library = "spencer";
  p[0].deviceset = "LEDRINGPADS";
  p[0].device = "";
  ////
  p[1].name = "IN_CXN";
  p[1].library = "spencer";
  p[1].deviceset = "LEDRINGPADS";
  p[1].device = "";
  ////
  p[2].name = "SJ1";
  p[2].library = "SparkFun-Retired";
  p[2].deviceset = "SOLDERJUMPER";
  p[2].device = "NO";
  ////
  p[3].name = "SJ2";
  p[3].library = "SparkFun-Retired";
  p[3].deviceset = "SOLDERJUMPER";
  p[3].device = "NC";
  ////
  p[4].name = "SJ3";
  p[4].library = "SparkFun-Retired";
  p[4].deviceset = "SOLDERJUMPER";
  p[4].device = "NO";
  ////
  p[5].name = "MCU_CXN";
  p[5].library = "SparkFun-Connectors";
  p[5].deviceset = "RJ45-8";
  p[5].device = "PTH";
  ////
  p[6].name = "HAL";
  p[6].library = "SparkFun-DiscreteSemi";
  p[6].deviceset = "MOSFET-PCHANNEL";
  p[6].device = "";
  ////
  p[7].name = "S1";
  p[7].library = "SparkFun-Electromechanical";
  p[7].deviceset = "SWITCH-MOMENTARY-2";
  p[7].device = "PTH";
  ////
  for(int i=0; i<8; i++){
    parts.push_back(p[i]);
  }

  int LPS = (int)led/seg;
  ofLog()<< ofToString(LPS);
  for(int i=0; i< LPS; i++){
    part *l = new part;
    l->name = "T"+ofToString(i);
    l->library = "SparkFun-LED";
    l->deviceset = "APA102";
    l->device = "";
    parts.push_back(*l);
  }
  if(two_side){
    for(int i=0; i< LPS; i++){
      part *l1 = new part;
      l1->name = "B"+ofToString(i);
      l1->library = "SparkFun-LED";
      l1->deviceset = "APA102";
      l1->device = "";
      parts.push_back(*l1);
    }
  }
  ofLog()<<"parts size: "+ofToString(parts.size());
}
void ledRing::basicOutline(){
  wire *w = new wire[13];
  //HARDCODE ALL THE SHIT
  w[0].x1 = 164.4585625;
  w[0].y1 = 61.4885375;
  w[0].x2 = 142.04518125;
  w[0].y2 = 103.201865625;
  w[0].width = 0.002540625;
  w[0].layer = 20;
  w[0].curve = 15.5;

  w[1].x1 = 128.29189375;
  w[1].y1 = -93.209515625;
  w[1].x2 = 128.29189375;
  w[1].y2 = 93.209515625;
  w[1].width = 0.002540625;
  w[1].layer = 20;
  w[1].curve = 72;

  w[2].x1 = 142.04518125;
  w[2].y1 = -103.201865625;
  w[2].x2 = 128.29189375;
  w[2].y2 = -93.209515625;
  w[2].width = 0.002540625;
  w[2].layer = 20;
  w[2].curve = 0;

  w[3].x1 = 142.04518125;
  w[3].y1 = 103.201865625;
  w[3].x2 = 128.29189375;
  w[3].y2 = 93.209515625;
  w[3].width = 0.002540625;
  w[3].layer = 20;
  w[3].curve = 0;

  w[4].x1 = 169.191825;
  w[4].y1 = 46.921046875;
  w[4].x2 = 164.4585625;
  w[4].y2 = 61.4885375;
  w[4].width = 0.002540625;
  w[4].layer = 20;
  w[4].curve = 150;
  
  w[5].x1 = 169.191825;
  w[5].y1 = -46.921046875;
  w[5].x2 = 164.4585625;
  w[5].y2 = -61.4885375;
  w[5].width = 0.002540625;
  w[5].layer = 20;
  w[5].curve = -150;
  
  w[6].x1 = 166.0117875;
  w[6].y1 = 57.16244375;
  w[6].x2 = 167.905596875;
  w[6].y2 = 51.33389375;
  w[6].width = 0.002540625;
  w[6].layer = 20;
  w[6].curve = -150;
  
  w[7].x1 = 166.0117875;
  w[7].y1 = -57.16244375;
  w[7].x2 = 167.905596875;
  w[7].y2 = -51.33389375;
  w[7].width = 0.002540625;
  w[7].layer = 20;
  w[7].curve = 150;
  
  w[8].x1 = 142.04518125;
  w[8].y1 = -103.201865625;
  w[8].x2 = 164.4585625;
  w[8].y2 = -61.4885375;
  w[8].width = 0.002540625;
  w[8].layer = 20;
  w[8].curve = 15.5;
  
  w[9].x1 = 166.0117875;
  w[9].y1 = -57.16244375;
  w[9].x2 = 167.905596875;
  w[9].y2 = -51.33389375;
  w[9].width = 0.002540625;
  w[9].layer = 20;
  w[9].curve = 2;
  
  w[10].x1 = 166.0117875;
  w[10].y1 = 57.16244375;
  w[10].x2 = 167.905596875;
  w[10].y2 = 51.33389375;
  w[10].width = 0.002540625;
  w[10].layer = 20;
  w[10].curve = -2;
  
  w[11].x1 = 169.191825;
  w[11].y1 = -46.921046875;
  w[11].x2 = 169.191825;
  w[11].y2 = 46.921046875;
  w[11].curve = 31;
  w[11].width = 0.002540625;
  w[11].layer = 20;
  
  w[12].x1 = 164.4585625;
  w[12].y1 = 61.4885375;
  w[12].x2 = 142.04518125;
  w[12].y2 = 103.201865625;
  w[12].width = 0.002540625;
  w[12].layer = 20;
  w[12].curve = 15.5;

  for(int i=0; i<13; i++){
    outlines.push_back(w[i]);
  }
}
