#include "idleizer.h"

void runGame(Core* core, int game_width, int game_height, char* title) {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, title);
	SearchAndSetResourceDir("resources");

  int mouseBtn = -1;
  // game loop
	while (!WindowShouldClose()) {
    // controls
    mouseButtonsHandler(core->buttons, core->buttons_size, &mouseBtn);
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSections(core->sections, core->sections_size);
    drawLabels(core->labels, core->labels_size);
    drawCurrencies(core->currencies, core->currencies_size);
    drawButtons(core->buttons, core->buttons_size);
   
    // handles the logic for and draws tickers
    handleTickers(core->tickers, core->tickers_size);
		
		EndDrawing();
	}
  
	CloseWindow();
}

void destroyCore(Core* core) {
  free(core->sections);
  free(core->currencies);
  free(core->buttons);
  free(core->labels);
  free(core->tickers);
}

void setTextBuffer(TextBuffer* buffer, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer->text, fmt, args);
  va_end(args);
}

// todo move all init functions to engine (see below)
// Section* createSections(const Rectangle* rects, const Color* colors, Section** parents, int count);
// void addSection(const Rectangle rect, const Color color, Section* parent)
// void removeSection(Section* sec);
void createSections(Core* core, const VrRec* rects, const Color* colors, 
                           const int* parent_indices, int count) {
  Section* sections = malloc(sizeof(Section) * count);
  for (int i = 0; i < count; i++) {
      sections[i].rec = rects[i];
      sections[i].bg = colors[i];
  }
  // Second pass: assign parents
  for (int i = 0; i < count; i++) {
      if (parent_indices[i] >= 0)
          sections[i].sec = &sections[parent_indices[i]];
      else
          sections[i].sec= NULL;
  }
  core->sections = sections;
  core->sections_size = count;
}

void createCurrencies(Core* core, const char** names, const VrVec* positions, Section** parents, int count) {
  Currency* currencies = malloc(sizeof(Currency) * count);
  for (int i = 0; i < count; i++) {
      currencies[i].name = names[i];
      currencies[i].amount = 0.0;
      currencies[i].pos = positions[i];
      currencies[i].sec = parents[i];
  }
  core->currencies = currencies;
  core->currencies_size = count;
}

void createButtons(Core* core, const char** texts, const VrRec* recs,
                   void (**handlers)(void *), void* gameState, Section** secs, int count) {
  Button* buttons = malloc(sizeof(Button) * count);
  for (int i = 0; i < count; i++) {
    buttons[i].text = texts[i];
    buttons[i].rec = recs[i];
    buttons[i].handler = handlers[i];
    buttons[i].ctx = gameState;
    buttons[i].sec = secs[i];
  }
  core->buttons = buttons;
  core->buttons_size = count;
}

void createLabels(Core* core, char** texts, VrVec* vecs, Color* colors,
                  bool* hiddens, Section** parents, int count) {
  Label* labels = malloc(sizeof(Label) * count);
  for (int i = 0; i < count; i++) {
    labels[i].text = texts[i];
    labels[i].pos = vecs[i];
    labels[i].fontSize = 20;
    labels[i].color = colors[i];
    labels[i].hidden = hiddens[i];
    labels[i].sec = parents[i];
  }
  core->labels = labels;
  core->labels_size = count;
}

void createTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void *), 
                   void* gameState, Section** parents, bool* hiddens, int count) {
  Ticker* tickers = malloc(sizeof(Ticker) * count);
  for (int i = 0; i < count; i++) {
    tickers[i].name = texts[i];
    tickers[i].pos = secs[i];
    tickers[i].frequency = frequencies[i];
    tickers[i].tick = 0;
    tickers[i].displayTick = 0;
    tickers[i].handler = handlers[i];
    tickers[i].ctx = gameState;
    tickers[i].sec = parents[i];
    tickers[i].hidden = hiddens[i];
  }
  core->tickers = tickers;
  core->tickers_size = count;
}
