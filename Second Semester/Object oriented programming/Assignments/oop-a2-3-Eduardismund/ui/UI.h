//
// Created by User on 3/5/2024.

#ifndef A2_3_EDUARDISMUND_UI_H
#define A2_3_EDUARDISMUND_UI_H
#pragma once
//
#endif //A2_3_EDUARDISMUND_UI_H

#include "../service/Service.h"

typedef struct{
    Service* service;
}UI;

UI *createUI(Service *);
void start(UI *);
void destroyUI(UI *);
void addEstateUI(UI *);
void deleteEstateUI(UI *);
void listEstatesWithSurface(UI *);
void listEstatesUIBasedOnStringRequirement(UI *);
void updateEstateUI(UI *);
void undoEstateUI(UI *ui);
void redoEstateUI(UI *ui);
