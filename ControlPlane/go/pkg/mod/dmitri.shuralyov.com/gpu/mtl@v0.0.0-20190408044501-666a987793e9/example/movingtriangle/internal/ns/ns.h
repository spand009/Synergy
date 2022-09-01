// +build darwin

typedef signed char BOOL;

void * Window_ContentView(void * window);

void View_SetLayer(void * view, void * layer);
void View_SetWantsLayer(void * view, BOOL wantsLayer);
