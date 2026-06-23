#pragma once
#include "player.h"
#include "company.h"

void companyDataRead(int slot, struct Company* c);
void companyDataWrite(int slot, struct Company* c);
void playerDataRead(int slot, Human* p, ownStock* o);
void playerDataWrite(int slot, Human* p, ownStock* o);