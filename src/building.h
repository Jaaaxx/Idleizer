#ifndef BUILDING_H
#define BUILDING_H
#include "vr_vec.h"
#include "vr_rec.h"
#include "text_buffer.h"
#include "core.h"
#include "section.h"
#include "ticker.h"
#include "button.h"
#include "label.h"

typedef struct BuildingPositionVec {
  VrVec pos;
  int sec;
} BuildingPositionVec;

typedef struct BuildingPositionRec {
  VrRec pos;
  int sec;
} BuildingPositionRec;

typedef struct BuildingPositions {
  BuildingPositionVec* ticker;
  BuildingPositionVec* amountLabel;
  BuildingPositionVec* cpsLabel;
  BuildingPositionRec* button;
  BuildingPositionRec* section;
} BuildingPositions;

typedef struct BuildingLabels {
  int amountLabel;
  int cpsLabel;
} BuildingLabels;

typedef struct BuildingTickers {
  int mTicker;
} BuildingTickers;

typedef struct BuildingTexts {
  TextBuffer amount;
  TextBuffer cps;
  TextBuffer button;
} BuildingTexts;

typedef struct BuildingVals {
  int amount;
  double cps;
  double cost;
} BuildingVals;

typedef struct Building{
  Core* core;
  char* name;
  BuildingVals* bv;
  int bCurr;
  int gCurr;
  BuildingLabels* labels;
  BuildingTickers* tickers;
  BuildingTexts* texts;
  int displaySect;
  // Any extra information to pass in about the game state
  void* data;
} Building;

VrVec calcBuildingOffsetPos(int buildings_size, int startX, int startY, int yOffset);
int setupBuilding(Core* core, char* name, double cps, double cost, 
                          int bCurr, int gCurr, BuildingPositions bps, void* gameData);
 

#endif
