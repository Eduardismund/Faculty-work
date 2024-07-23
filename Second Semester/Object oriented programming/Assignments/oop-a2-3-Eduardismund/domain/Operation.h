//
// Created by User on 3/14/2024.
//

#ifndef A2_3_EDUARDISMUND_OPERATION_H
#define A2_3_EDUARDISMUND_OPERATION_H

#endif //A2_3_EDUARDISMUND_OPERATION_H
#include "RealEstateAgency.h"
typedef struct
{
    /*
    ** typeOfOperation: 1 - Add, 2 - Delete, 3 - Update
    ** 1) Add Estate1, Estate2 = NULL
    ** 2) Delete Estate1, Estate2 = NULL
    ** 3) Update Estate1, Estate2
    */
    int typeOfOperation;
    Estate *Estate1, *Estate2;
}Operation;

Operation *createOperation(int typeOfOperation, Estate *Estate1, Estate *Estate2);
void destroyOperation(Operation *operation);
int getTypeOfOperation(Operation *operation);
Estate *getEstate1(Operation *operation);
Estate *getEstate2(Operation *operation);