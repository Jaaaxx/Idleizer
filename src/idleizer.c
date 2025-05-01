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
    mouseButtonsHandler(core, &mouseBtn);
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSections(core);
    drawLabels(core);
    drawCurrencies(core);
    drawButtons(core);
   
    // handles the logic for and draws tickers
    handleTickers(core);
		
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
                           const int* parent_indices, const bool* hiddens, int count) {
  core->sections = malloc(sizeof(Section) * count);
  core->sections_size = count;
  for (int i = 0; i < count; i++) {
    core->sections[i].rec = rects[i];
    core->sections[i].bg = colors[i];
    core->sections[i].parent = parent_indices[i];
    core->sections[i].hidden = hiddens[i];
  }
}

int addSection(Core* core, const VrRec rect, const Color color, const bool hidden, int parent) {
  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + 1));

  Section* s = &core->sections[core->sections_size];
  s->rec = rect;
  s->bg = color;
  s->parent = parent;
  s->hidden = hidden;

  return core->sections_size++;
}

void createCurrencies(Core* core, const char** names, const VrVec* positions, int* parents, bool* hiddens, int count) {
  Currency* currencies = malloc(sizeof(Currency) * count);
  for (int i = 0; i < count; i++) {
    currencies[i].name = names[i];
    currencies[i].amount = 0.0;
    currencies[i].pos = positions[i];
    currencies[i].sec = parents[i];
    currencies[i].hidden = hiddens[i];
  }
  core->currencies = currencies;
  core->currencies_size = count;
}

int addCurrency(Core* core, const char* name, const VrVec position, bool hidden, int parent) {
  core->currencies = realloc(core->currencies, sizeof(Currency) * (core->currencies_size + 1));

  Currency* c = &core->currencies[core->currencies_size];
  c->name = name;
  c->amount = 0.0;
  c->pos = position;
  c->sec = parent;
  c->hidden = hidden;

  return core->currencies_size++;
}

void createButtons(Core* core, const char** texts, const VrRec* recs,
                   void (**handlers)(void *), void** ctxs, int* secs, bool* hiddens, int count) {
  Button* buttons = malloc(sizeof(Button) * count);
  for (int i = 0; i < count; i++) {
    buttons[i].text = texts[i];
    buttons[i].rec = recs[i];
    buttons[i].handler = handlers[i];
    buttons[i].ctx = ctxs[i];
    buttons[i].hidden = hiddens[i];
    buttons[i].sec = secs[i];
  }
  core->buttons = buttons;
  core->buttons_size = count;
}

int addButton(Core* core, char* text, VrRec rec, void (*handler)(void*), void* ctx, bool hidden, int sec) {
  core->buttons = realloc(core->buttons, sizeof(Button) * (core->buttons_size + 1));

  Button* b = &core->buttons[core->buttons_size];
  b->text = text;
  b->rec = rec;
  b->handler = handler;
  b->ctx = ctx;
  b->hidden = hidden;
  b->sec = sec;

  return core->buttons_size++;
}

void createLabels(Core* core, char** texts, VrVec* vecs, Color* colors,
                  bool* hiddens, int* parents, int count) {
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

int addLabel(Core* core, char* text, VrVec pos, Color color, bool hidden, int parent) {
  core->labels = realloc(core->labels, sizeof(Label) * (core->labels_size + 1));

  Label* l = &core->labels[core->labels_size];
  l->text = text;
  l->pos = pos;
  l->fontSize = 20;
  l->color = color;
  l->hidden = hidden;
  l->sec = parent;

  return core->labels_size++;
}

void createTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void *), 
                   void** ctxs, int* parents, bool* hiddens, int count) {
  Ticker* tickers = malloc(sizeof(Ticker) * count);
  for (int i = 0; i < count; i++) {
    tickers[i].name = texts[i];
    tickers[i].pos = secs[i];
    tickers[i].frequency = frequencies[i];
    tickers[i].tick = 0;
    tickers[i].displayTick = 0;
    tickers[i].handler = handlers[i];
    tickers[i].ctx = ctxs[i];
    tickers[i].sec = parents[i];
    tickers[i].hidden = hiddens[i];
  }
  core->tickers = tickers;
  core->tickers_size = count;
}

int addTicker(Core* core, char* name, VrVec pos, int frequency, 
                void (*handler)(void*), void* ctx, bool hidden, int sec) {
  // Expand existing array
  core->tickers = realloc(core->tickers, sizeof(Ticker) * (core->tickers_size + 1));
  
  Ticker* t = &core->tickers[core->tickers_size];
  t->name = name;
  t->pos = pos;
  t->frequency = frequency;
  t->tick = 0;
  t->displayTick = 0;
  t->handler = handler;
  t->ctx = ctx;
  t->sec = sec;
  t->hidden = hidden;

  return core->tickers_size++;
}
