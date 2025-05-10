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

// TODO Allow creators to pass in full Ticker, Label, Etc. objects instead of creating them internally

typedef struct BPosVec {
  VrVec pos;
  int sec;
} BPosVec;

typedef struct BPosRec {
  VrRec pos;
  int sec;
} BPosRec;

typedef struct BuildingPositions {
  BPosVec ticker;
  BPosRec amountLabel;
  BPosRec cpsLabel;
  BPosRec button;
  BPosRec section;
} BuildingPositions;

typedef struct BuildingLabels {
  int amountLabel;
  int cpsLabel;
} BuildingLabels;

typedef struct BuildingTickers {
  int mTicker;
} BuildingTickers;

typedef struct BuildingButtons {
  int buyButton;
} BuildingButtons;

typedef struct BuildingTexts {
  TextBuffer* amount;
  TextBuffer* cps;
  TextBuffer* button;
} BuildingTexts;

typedef struct BuildingVals {
  int amount;
  double cps;
  double cost;
} BuildingVals;

typedef struct Building {
  Core* core;
  char* name;
  BuildingVals vals;
  int bCurr;
  int gCurr;
  BuildingLabels labels;
  BuildingTickers tickers;
  BuildingTexts texts;
  BuildingButtons buttons;
  BuildingPositions positions;
  int displaySect;
  // Any extra information to pass in about the game state
  void* data;
  // For freeing memory allocated
  void* internal;
} Building;

void freeAllBuildings(Core* core);
void unloadBuildingResources(Core* core);
VrVec calcBuildingOffsetPos(int buildings_size, int startX, int startY, int yOffset);
int addBuilding(Core* core, Building building);
Building newBuilding(Core* core);
#endif
