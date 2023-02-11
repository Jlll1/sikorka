#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xft/Xft.h>

int
main(int argc, char *argv[])
{
  Display *dpy = XOpenDisplay(NULL);
  int screen = DefaultScreen(dpy);
  int root = RootWindow(dpy, screen);

  XWindowAttributes wa;
  if (!XGetWindowAttributes(dpy, root, &wa))
    return 1;

  int w = wa.width;
  int h = wa.height;
  Drawable drawable = XCreatePixmap(dpy, root, w, h, DefaultDepth(dpy, screen));
  GC gc = XCreateGC(dpy, root, 0, NULL);
  XSetLineAttributes(dpy, gc, 1, LineSolid, CapButt, JoinMiter);

  XSetWindowAttributes swa;
  swa.override_redirect = True;

  XftColor bg;
  XftColorAllocName(dpy, DefaultVisual(dpy, screen), DefaultColormap(dpy, screen),
                    "#000000", &bg);
  XftColor fg;
  XftColorAllocName(dpy, DefaultVisual(dpy, screen), DefaultColormap(dpy, screen),
                    "#FFFFFF", &fg);

  swa.background_pixel = bg.pixel;
  swa.event_mask = ExposureMask | KeyPressMask | VisibilityChangeMask;
  int x = 50;
  int y = 50;
  int win_w = 200;
  int win_h = 200;
  XClassHint ch = {"sikorka", "sikorka"};
  int win = XCreateWindow(dpy, root, x, y, win_w, win_h, 0,
                          CopyFromParent, CopyFromParent, CopyFromParent,
                          CWOverrideRedirect | CWBackPixel | CWEventMask, &swa);
  XSetClassHint(dpy, win, &ch);
  XMapRaised(dpy, win);

  XSetForeground(dpy, gc, fg.pixel);
  XFillRectangle(dpy, drawable, gc, 150, 150, 150, 150);
  XSync(dpy, False);

  XftDraw *xftdraw = XftDrawCreate(dpy, drawable, DefaultVisual(dpy, screen), DefaultColormap(dpy, screen));
  XftFont *font = XftFontOpen(dpy, screen, XFT_FAMILY, XftTypeString, "monospace", XFT_SIZE, XftTypeDouble, 10.0, NULL);

  XftDrawString8(xftdraw, &bg, font, 80, 80, "test test", 9);
  while (True)
  {
  }

  return 0;
}
