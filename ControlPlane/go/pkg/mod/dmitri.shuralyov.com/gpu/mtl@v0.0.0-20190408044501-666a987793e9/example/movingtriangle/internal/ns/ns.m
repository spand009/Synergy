// +build darwin

#import <Cocoa/Cocoa.h>
#include "ns.h"

void * Window_ContentView(void * window) {
	return ((NSWindow *)window).contentView;
}

void View_SetLayer(void * view, void * layer) {
	((NSView *)view).layer = (CALayer *)layer;
}

void View_SetWantsLayer(void * view, BOOL wantsLayer) {
	((NSView *)view).wantsLayer = wantsLayer;
}
