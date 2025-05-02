#include <stdio.h>
#include "section.h"
#include "core.h"
#include <string.h>
#include <stdlib.h>

Section* getSection(Core *core, int idx) {
  return idx >= 0 ? &core->sections[idx] : NULL;
}

float getSecWidth(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 1;
  }
  if (sec->parent == -1) {
    // equivalent to GAME_WIDTH
    return sec->rec.w;
  }

  return (sec->rec.w / 100) * getSecWidth(core, &secs[sec->parent]);
}

float getSecHeight(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 1;
  }
   if (sec->parent == -1) {
    // equivalent to GAME_HEIGHT
    return sec->rec.h;
  }

  return (sec->rec.h / 100) * getSecHeight(core, &secs[sec->parent]);
}
float getSecX(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == -1) {
    return sec->rec.x;
  }

  return (sec->rec.x / 100) * getSecWidth(core, &secs[sec->parent]) + getSecX(core, &secs[sec->parent]);
}

float getSecY(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == -1) {
    return sec->rec.y;
  }

  return (sec->rec.y / 100) * getSecHeight(core, &secs[sec->parent]) + getSecY(core, &secs[sec->parent]);
}

static bool sectionIsAncestor(Core* core, int child, int parent) {
  if (child == parent) {
    return true;
  }
  Section* ptr = getSection(core, child);
  while (ptr->parent >= 0) {
    if (ptr->parent == parent) {
      return true;
    }
    ptr = getSection(core, ptr->parent);
  }
  return false;
}

static void restoreSectionHiddens(Core* core, int section, bool* hiddens, int count) {
  for (int i = 0; i < count; i++) {
    // don't restore irrelevant sections
    if (sectionIsAncestor(core, i, section)) {
      getSection(core, i)->hidden = hiddens[i];
    }
  }
}

static void saveSectionHiddens(Core* core, BoolArr* vals) {
  int count = core->sections_size;
  for (int i = 0; i < count; i++) {
    vals->arr[i] = getSection(core, i)->hidden;
  }
  vals->size = count;
}

// Static variables for toggleSectionHide
static BoolArr* hiddenVals;
static bool* displayHiddens;
static int secSize = -1;

void cleanupSectionHideResources() {
  if (hiddenVals != NULL && secSize > 0) {
    for (int i = 0; i < secSize; i++) {
      if (hiddenVals[i].arr != NULL) {
        free(hiddenVals[i].arr);
      }
      hiddenVals[i].size = 0;
      hiddenVals[i].arr = NULL;
    }
    free(hiddenVals);
  }

  if (displayHiddens != NULL) {
    free(displayHiddens);
  }

  hiddenVals = NULL;
  displayHiddens = NULL;
  secSize = -1;
}

void toggleSectionHide(Core* core, int section) {
  if (secSize != core->sections_size) {
    secSize = core->sections_size;
    if (hiddenVals == NULL) {
      hiddenVals = (BoolArr*) calloc(core->sections_size, sizeof(BoolArr));
      displayHiddens = (bool*) calloc(core->sections_size, sizeof(bool));
    } else {
      hiddenVals = (BoolArr*) realloc(hiddenVals, core->sections_size * sizeof(BoolArr));
      displayHiddens = (bool*) realloc(displayHiddens, core->sections_size * sizeof(bool));
    }
  }

  BoolArr* savedVals = &hiddenVals[section];
  if (!displayHiddens[section]) {
    if (savedVals->arr == NULL) {
      savedVals->arr = malloc(secSize * sizeof(bool));
    } else if (savedVals->size != secSize) {
      savedVals->arr = realloc(savedVals->arr, secSize * sizeof(bool));
    }
    savedVals->size = secSize;
    saveSectionHiddens(core, savedVals);
    core->sections[section].hidden = !core->sections[section].hidden;
    displayHiddens[section] = !core->sections[section].hidden;
  } else {
    restoreSectionHiddens(core, section, savedVals->arr, savedVals->size);
    displayHiddens[section] = !displayHiddens[section];
  }
}



void drawSections(Core* core) {
  for (int i = 0; i < core->sections_size; i++) {
    const Section* s = &core->sections[i];

    // ensure that hidden parents also hide all children
    Section* ptr = s;
    while (ptr->parent >= 0 && ptr->hidden != getSection(core, ptr->parent)->hidden) {
      bool parentHidden = getSection(core, ptr->parent)->hidden;
      ptr->hidden = parentHidden ? true : ptr->hidden;
      ptr = getSection(core, ptr->parent);
    }

    if (!s->hidden) {
      Rectangle rec = getSectionRec(core, s);  
      DrawRectangleRec(rec, s->bg); 
      DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, BLACK);
    }
  }
}

// todo for this and all data types: improve defaults by giving users a createSection() function?
// it would populate with sentinel values to determine what the user actually set and improve defaults
// could be more trouble for the user though adding complexity per object created
static void setDefaultSection(Section section, Section* ptr) {
  ptr->rec = section.rec;
  ptr->bg = section.bg;
  ptr->parent = section.parent >= 0 ? section.parent : -1;
  ptr->hidden = section.hidden;
}

int addSections(Core* core, Section* sections, int count) {
  if (core->sections == NULL) {
    core->sections_size = 0;
  }

  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultSection(sections[i], &core->sections[i+core->sections_size]);
  }

  int index = core->sections_size;
  core->sections_size += count;
  return index;
}

int addSection(Core* core, Section section) {
  if (core->sections == NULL) {
    core->sections_size = 0;
  }

  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + 1));
  setDefaultSection(section, &core->sections[core->sections_size]);

  return core->sections_size++;
}

