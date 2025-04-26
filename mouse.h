#ifndef _mouse_h_
#define _mouse_h_
int mouse_press(int x1, int y1, int x2, int y2);
void mouse(int,int);
void mouseinit(void);
void mou_pos(int*,int*,int*);
void mread(int *,int *,int*);
void save_bk_mou(int x,int y);
void clrmous(int x,int y);
void drawmous(int x,int y);


extern int MouseX;
extern int MouseY;
extern int press;
#endif
