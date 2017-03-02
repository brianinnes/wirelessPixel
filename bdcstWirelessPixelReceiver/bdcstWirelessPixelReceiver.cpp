#include "bdcstWirelessPixelReceiver.h"
#include <string.h>

#define SETCOLOUR 0x00
#define FADECOLOUR 0x08
#define PLAYSEQ 0x10
#define FADESEQ 0x18
#define LOOPSEQ 0x20
#define LOOPFADESEQ 0x28
#define UPDATECOLOUR 0x30
#define UPDATESEQ 0x38
#define MISCCOMMAND 0x40
#define PLAYRGBSEQ 0x50
#define FADERGBSEQ 0x58
#define LOOPRGBSEQ 0x60
#define LOOPFADERGBSEQ 0x68
#define UPDATERGBSEQ 0x70
#define UPDATERGBSEQCONT 0x71

//using namespace std;

bdcstWPRec::bdcstWPRec(Spi *sp, Gpio *gp, Persist *st, LedControl *lc)  : stdColours {
  {0, 0, 0},
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {255,0, 255},
  {0, 255, 255},
  {255, 255, 255}} {
    this->sp = sp;
    this->gp = gp;
    this->st = st;
    this->lc = lc;
    this->gID = 0;
  }

  bdcstWPRec::~bdcstWPRec() {

  }

  void bdcstWPRec::init() {
    const uint8_t s[] = {(1<<5)+5, (2<<5)+5, (3<<5)+5, (0<<5)+1};
    for (int i = 0; i < MAXSEQ; i++) {
      this->stdSequences.numItems[i] = 0;
      this->stdSequences.items[i] = 0;
    }
    this->stdSequences.numItems[0] = 4;
    this->stdSequences.items[0] = (uint8_t *)malloc(4);
    memcpy(this->stdSequences.items[0], s, sizeof(s));

    this->lc->init();
    this->rf24 = new nrf24l01(this->sp, this->gp);
    this->rf24d = new nrf24l01Data(this->rf24);
    this->rf24d->initialise();
    this->rf24d->startReceiving();
  }

  void bdcstWPRec::checkAndProcessMessages() {
    uint8_t cont = 1;
    uint8_t len = this->rf24d->isMessageAvailable();
    if (0 < len) {
      uint8_t buf[len];
      for (int i = 0; i< len; i++) {
        buf[i] = 0x00;
      }
      this->rf24d->getMessage(buf, len);
      // Check for Broadcast message and at least 2 bytes
      if ((0x00 == buf[0]) && (len >= 2)) {
        // check if group message, if so is for my group?
        if (((0x80 & buf[1]) > 0) && (len >= 4)){
          uint16_t id = (buf[2] << 8) + buf[3];
          if (id != this->gID) {
            // group ID doesn't match, so this message is ignored
            cont = 0;
          } else {
            buf[1] &= 0x7F; //remove Group bit from command
            // remove id from command buffer
            for (int i = 4; i < len; i++) {
              buf[i-2] = buf[i];
            }
            len -= 2;
          }
        }

        // if valid message - consume message
        if (1 == cont)  {
          uint8_t cmd = buf[1] & 0xF8;
          switch (cmd) {
            case SETCOLOUR:
            this->setColour(buf);
            break;
            case FADECOLOUR:
            this->fadeColour(buf, len);
            break;
            case PLAYSEQ:
            this->playSeq(buf);
            break;
            case FADESEQ:
            this->fadeSeq(buf, len);
            break;
            case LOOPSEQ:
            this->loopSeq(buf);
            break;
            case LOOPFADESEQ:
            this->loopFadeSeq(buf, len);
            break;
            case UPDATECOLOUR:
            this->updateColour(buf, len);
            break;
            case UPDATESEQ:
            this->updateSeq(buf, len);
            break;
            case MISCCOMMAND:
            this->miscCommand(buf, len);
            break;
            case PLAYRGBSEQ:
            this->playRGBSeq(buf);
            break;
            case FADERGBSEQ:
            this->fadeRGBSeq(buf, len);
            break;
            case LOOPRGBSEQ:
            this->loopRGBSeq(buf);
            break;
            case LOOPFADERGBSEQ:
            this->loopFadeRGBSeq(buf, len);
            break;
            case UPDATERGBSEQ:
            this->updateRGBSeq(buf, len);
            break;
            case UPDATERGBSEQCONT:
            this->updateRGBSeqCont(buf, len);
            break;
            default :
            ;
          }
        }
      }
    }
  }

void bdcstWPRec::_setLEDColour(uint8_t r, uint8_t g, uint8_t b) {
  this->currColours[0] = r;
  this->currColours[1] = g;
  this->currColours[2] = b;
  this->lc->setLed(0, this->currColours[0], this->currColours[1], this->currColours[2]);
}

void bdcstWPRec::_fadeLEDColour(uint8_t r, uint8_t g, uint8_t b, uint8_t time) {
  int16_t dR = r - this->currColours[0];
  int16_t dG = g - this->currColours[1];
  int16_t dB = b - this->currColours[2];
  int16_t _r, _g, _b;
  for (int i = 0; i < time; i++) {
    _r = this->currColours[0] + (dR*i/time);
    _g = this->currColours[1] + (dG*i/time);
    _b = this->currColours[2] + (dB*i/time);
    this->lc->setLed(0, (uint8_t)_r, (uint8_t)_g, (uint8_t)_b);
    this->lc->delay(10);
  }
  this->_setLEDColour(r, g, b);
}

void bdcstWPRec::_playStdSequence(uint8_t s) {
  if (this->stdSequences.numItems[s] > 0) {
    for (int i = 0; i < this->stdSequences.numItems[s]; i++) {
      uint8_t col = (this->stdSequences.items[s][i]) >> 5;
      uint8_t delay = (this->stdSequences.items[s][i]) & 0x1F;
      this->_setLEDColour(this->stdColours[col][0],
                          this->stdColours[col][1],
                          this->stdColours[col][2]);
      this->lc->delay(delay * 100);
    }
  }
}

void bdcstWPRec::_fadeStdSequence(uint8_t s, uint8_t time) {
  if (this->stdSequences.numItems[s] > 0) {
    for (int i = 0; i < this->stdSequences.numItems[s]; i++) {
      uint8_t col = (this->stdSequences.items[s][i]) >> 5;
      uint8_t delay = (this->stdSequences.items[s][i]) & 0x1F;
      this->_fadeLEDColour(this->stdColours[col][0],
                          this->stdColours[col][1],
                          this->stdColours[col][2],
                          time);
      this->lc->delay(delay * 100);
    }
  }
}

void bdcstWPRec::setColour(uint8_t *params) {
    uint8_t col = params[1] & 0x07;
    this->_setLEDColour(this->stdColours[col][0], this->stdColours[col][1], this->stdColours[col][2]);
}

void bdcstWPRec::fadeColour(uint8_t *params, uint8_t len) {
  if (3 == len) {
    uint8_t col = params[1] & 0x07;
    uint8_t time = params[2];
    this->_fadeLEDColour(this->stdColours[col][0], this->stdColours[col][1], this->stdColours[col][2], time);
  }
}

void bdcstWPRec::playSeq(uint8_t *params) {
  uint8_t seq = params[1] & 0x07;
  this->_playStdSequence(seq);
}

void bdcstWPRec::fadeSeq(uint8_t *params, uint8_t len) {
  if (3 == len) {
    uint8_t seq = params[1] & 0x07;
    uint8_t time = params[2];
    this->_fadeStdSequence(seq, time);
  }
}

void bdcstWPRec::loopSeq(uint8_t *params) {
  uint8_t seq = params[1] & 0x07;
  while (true) {
    this->_playStdSequence(seq);
    if (this->rf24d->isMessageAvailable() > 0) {
      break;
    }
  }
}

void bdcstWPRec::loopFadeSeq(uint8_t *params, uint8_t len) {
  if (3 == len) {
    uint8_t seq = params[1] & 0x07;
    uint8_t time = params[2];
    while (true) {
      this->_fadeStdSequence(seq, time);
      if (this->rf24d->isMessageAvailable() > 0) {
        break;
      }
    }
  }
}

void bdcstWPRec::updateColour(uint8_t *params, uint8_t len) {
  if (5 == len) {
    uint8_t col = params[1] & 0x07;
    uint8_t r = params[2];
    uint8_t g = params[3];
    uint8_t b = params[4];
    this->stdColours[col][0] = r;
    this->stdColours[col][1] = g;
    this->stdColours[col][2] = b;
  }
}

void bdcstWPRec::updateSeq(uint8_t *params, uint8_t len) {
  uint8_t seq = params[1] & 0x07;
  uint8_t num = params[2];
  if ((num+3) == len) {
    if (this->stdSequences.numItems[seq] > 0) {
      free(this->stdSequences.items[seq]);
      this->stdSequences.items[seq] = 0;
    }
    this->stdSequences.items[seq] = (uint8_t *)malloc(num);
    for (int i = 0; i < num; i++) {
      this->stdSequences.items[seq][i] = params[3+i];
    }
  }
}


void bdcstWPRec::miscCommand(uint8_t *params, uint8_t len) {

}

void bdcstWPRec::playRGBSeq(uint8_t *params) {

}

void bdcstWPRec::fadeRGBSeq(uint8_t *params, uint8_t len) {

}

void bdcstWPRec::loopRGBSeq(uint8_t *params) {

}

void bdcstWPRec::loopFadeRGBSeq(uint8_t *params, uint8_t len) {

}

void bdcstWPRec::updateRGBSeq(uint8_t *params, uint8_t len) {

}

void bdcstWPRec::updateRGBSeqCont(uint8_t *params, uint8_t len) {

}
