#include "eagleFile.h"

void eagleFile::readIn(vector <string> *str_vec, string addr){
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
void eagleFile::createFile(ledRing * r){
  ring=r;
  //load in static things
  readIn(&header, "stat/brd_header.txt");
  readIn(&mid_file, "stat/brd_mid_file.txt");
  readIn(&libraries, "stat/ring_lib.txt");
  readIn(&footer, "stat/brd_footer.txt");
}

void writeOut(vector <string> str_vec, string addr){

}
void eagleFile::writeHeader(){
  int count=0;
  for(vector<string>::iterator it = header.begin(); it != header.end(); ++it){
    if(count<140){
      write_buff.append(*it);
    }
  }
}
void eagleFile::writePlain(){
  write_buff.append("<plain>\n");
  for(vector<wire>::iterator it=ring->outlines.begin(); it !=ring->outlines.end(); ++it){
    write_buff.append(it->toString());
  }
  write_buff.append("</plain>\n");
}
void eagleFile::writeLib(){
  write_buff.append("<libraries>\n");
  write_buff.append("</libraries>\n");
  //for(vector<string>::iterator it = libraries.begin(); it!=libraries.end(); ++it){
  //  write_buff.append(*it);
  //}

}
void eagleFile::writeMidFile(){
  for(vector<string>::iterator it = mid_file.begin(); it!=mid_file.end(); ++it){
    write_buff.append(*it);
  }
}
void eagleFile::writeElem(){
  write_buff.append("<elements>\n");

  write_buff.append("</elements>\n");
}
void eagleFile::writeSig(){
  write_buff.append("<signals>\n");

  write_buff.append("</signals>\n");
}
void eagleFile::writeFooter(){
  for(vector<string>::iterator it = footer.begin(); it!=footer.end(); ++it){
    write_buff.append(*it);
  }

}
int eagleFile::saveFile(string path){
  
  ring->basicOutline();

  writeHeader();
  writePlain();
  writeLib();
  writeMidFile();
  writeElem();
  writeSig();
  writeFooter();

  int fileWritten = ofBufferToFile(path, write_buff);
  return fileWritten;

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
