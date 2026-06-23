#pragma once
#include "player.h"

void print_frame(); // square
void main_frame(Human* player, struct Company* c, ownStock* stock, int turn, char* event, char* event2);
void main_screen(Human* player, struct Company* c, ownStock* stock, int turn, int slot, char* event, char* event2);
Human tutorial();
void study_screen();
void save_screen(int slot, Human* p, ownStock* stock, struct Company* c);
void print_stockhouse();
int title(Human* player, struct Company* c, ownStock* stock);
int slot_screen(Human* p, ownStock* stock, struct Company* c);
void stock_screen(Human* player, struct Company* c, ownStock* stock);
void sell_screen(Human* player, struct Company* c, ownStock* stock);
void howtouse();
void studying_screen();
void make_v();
void green_search();
void youtube();
void posts();
void wait_turn(Human* player, int turn);
void end_screen(Human *player);