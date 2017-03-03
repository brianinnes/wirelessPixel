#include <stdint.h>
#include <string.h>
#include <pwd.h>
//#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include "raspberryPiPersist.h"
using namespace std;

uint16_t defaultGid = 0;
uint8_t defaultStdColours[8][3] = {
  {0, 0, 0},
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {255,0, 255},
  {0, 255, 255},
  {255, 255, 255}};
StdSequence defaultStdSequences = {
    {4, 4, 0, 0, 0, 0, 0, 0},
    {(1<<5)+5, (2<<5)+5, (3<<5)+5, (0<<5)+1, (4<<5)+2, (5<<5)+2, (6<<5)+2, (7<<5)+2}};
// RGBSequence defaultRgbSequences = {{0, 0, 0, 0, 0, 0, 0, 0}, {}};


raspberryPiPersist::raspberryPiPersist() {
  passwd* pw = getpwuid(getuid());
  path = (pw->pw_dir);
  path += "/.wirelessPixel";
  this->gIDPath = path + "/gID.bin";
  this->stdColourPath = path + "/stdColour.bin";
  this->stdSeqPath = path + "/stdSeq.bin";
//  this->rgbSeqPath = path + "/rgbSeq.bin";
}

uint16_t raspberryPiPersist::getGID() {
  uint16_t guid = defaultGid;
  ifstream myfile(this->gIDPath.c_str(), ios::in|ios::binary);
  if (myfile.is_open()) {
    myfile.seekg(0, ios::beg);
    myfile.read((char *)&guid, sizeof(guid));
    myfile.close();
  } else {
    this->setGID(defaultGid);
  }
  return guid;
}

void raspberryPiPersist::setGID(uint16_t col) {
  cout << "Saving gID to file " << col << endl;
  mkdir(this->path.c_str(), 0777);
  ofstream myfile(this->gIDPath.c_str(), ios::binary);
  myfile.write((char *)&col, sizeof(col));
  myfile.close();
}

void raspberryPiPersist::getStandardColours(uint8_t *buff) {
  ifstream myfile(this->stdColourPath.c_str(), ios::in|ios::binary);
  if (myfile.is_open()) {
    myfile.seekg(0, ios::beg);
    myfile.read((char *)buff, 24);
    myfile.close();
  } else {
    this->setStandardColours((uint8_t *)defaultStdColours);
    memcpy(buff, defaultStdColours, 24);
  }
}

void raspberryPiPersist::setStandardColours(uint8_t *buff) {
  cout << "Saving standard colours to file " << endl;
  ofstream myfile(this->stdColourPath.c_str(), ios::binary);
  myfile.write((char *)buff, 24);
  myfile.close();
}

//void raspberryPiPersist::getSequences(StdSequence *std, RGBSequence *rgb) {
void raspberryPiPersist::getSequences(StdSequence *std) {
  ifstream myfile(this->stdSeqPath.c_str(), ios::in|ios::binary);
  if (myfile.is_open()) {
    myfile.seekg(0, ios::beg);
    myfile.read((char *)std, sizeof(StdSequence));
    myfile.close();
//    ifstream myfile(this->rgbSeqPath.c_str(), ios::in|ios::binary);
//    myfile.seekg(0, ios::beg);
//    myfile.read((char *)rgb, sizeof(RGBSequence));
//    myfile.close();
  } else {
//    this->setSequences(&defaultStdSequences, &defaultRgbSequences);
    this->setSequences(&defaultStdSequences);
    memcpy(std, &defaultStdSequences, sizeof(StdSequence));
//    memcpy(rgb, &defaultRgbSequences, sizeof(RGBSequence));
  }
}

//void raspberryPiPersist::setSequences(StdSequence *std, RGBSequence *rgb) {
void raspberryPiPersist::setSequences(StdSequence *std) {
  ofstream myfile1(this->stdSeqPath.c_str(), ios::binary);
  myfile1.write((char *)std, sizeof(StdSequence));
  myfile1.close();
//  ofstream myfile2(this->rgbSeqPath.c_str(), ios::binary);
//  myfile2.write((char *)rgb, sizeof(RGBSequence));
//  myfile2.close();
}
