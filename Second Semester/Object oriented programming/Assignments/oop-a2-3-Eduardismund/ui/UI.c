#include "UI.h"
#include "UndoRedoRepository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UI *createUI(Service *service){
    UI *ui = (UI *)malloc(sizeof(UI));
    ui->service = service;
    return ui;
}
Service *getService(UI *ui)
{
    return ui->service;
}

void destroyUI(UI *ui){
    destroyService(getService(ui));
    free(ui);
}

void printMenu(){
    printf("\nChoose one of the following options:\n");
    printf("1. add an estate\n");
    printf("3. update an estate\n");
    printf("2. delete an estate\n");
    printf("4. display all estates who contain a given string\n");
    printf("5. display all estates that have a surface lower than a given one\n");
    printf("6. [BONUS] display all estates that have a certain type (e.g. house, apartment, penthouse)\n");
    printf("7. undo last performed operation\n");
    printf("8. redo last performed operation\n");
    printf("0. exit\n");
}

void addEstateUI(UI *ui){
    int price, surface;
    char type[101], address[101];
    char house[] = "house", apartment[] = "apartment", penthouse[] = "penthouse";

    printf("Insert a type, address, surface and a price:\n");
    do {
        printf("Be sure to be one of the following: house, apartment, penthouse. Type: ");
        scanf(" %[^\n]", type);
        printf("Type entered: %s\n", type); // Print the type entered for debugging
    } while (!(strcmp(house, type) == 0 || strcmp(apartment, type) == 0 || strcmp(penthouse, type) == 0));
    printf("Address: ");
    scanf(" %[^\n]", address);
    printf("Address entered: %s\n", address); // Print the address entered for debugging
    printf("Surface: ");
    scanf("%d", &surface);
    printf("Surface entered: %d\n", surface); // Print the surface entered for debugging
    printf("Price: ");
    scanf("%d", &price);
    printf("Price entered: %d\n", price); // Print the price entered for debugging

    Estate *estate = createEstate(type, address, surface, price);
    if (addEstateService(ui->service, estate) == 1)
        printf("Estate added successfully! \n");
    else
    {
        printf("You cannot add an estate that already exists! \n");
        destroyEstate(estate);
    }
}


void deleteEstateUI(UI *ui){
    char address[101];
    printf("Enter the address of the Real Estate you want to delete: ");
    scanf(" %[^\n]", address);
    Estate *estate = createEstate("house", address,0,0);
    if(deleteEstateService(ui->service, estate)==1)
        printf("Estate deleted successfully! ");
    else
        printf("Estate does not exist!");
    destroyEstate(estate);
}

void updateEstateUI(UI *ui){
    char old_address[101], new_address[101], type[101];
    char house[] = "house", apartment[] = "apartment", penthouse[] = "penthouse";
    int surface, price;

    printf("Enter the address of the estate you want to update: ");
    scanf(" %[^\n]", old_address);
    printf("Enter the new address of the estate you want to update: ");
    scanf(" %[^\n]", new_address);
    printf("Enter the new type of the estate: ");
    do {
        printf("Be sure to be one of the following: house, apartment, penthouse. Type: ");
        scanf(" %[^\n]", type);
        printf("Type entered: %s\n", type); // Print the type entered for debugging
    } while (!(strcmp(house, type) == 0 || strcmp(apartment, type) == 0 || strcmp(penthouse, type) == 0));
    printf("Enter the new surface of the estate: ");
    scanf("%d", &surface);
    printf("Enter the new price of the estate: ");
    scanf("%d", &price);

    Estate *estateBefore = createEstate("house", old_address, 0, 0),
            *estateAfter = createEstate(type, new_address, surface, price);
    if (updateEstateService(getService(ui), estateBefore, estateAfter) == 1)
        printf("Estate updated successfully!  \n");
    else
        printf("Estate does not exist! \n");
}

void undoEstateUI(UI *ui)
{
    Service *service = getService(ui);
    UndoRedoRepository *undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray *undoOperations = getUndoOperations(undoRedoRepository), *redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, undoOperations, redoOperations))
        printf("Undo performed successfully! \n");
    else
        printf("No more undos available! \n");
}

void redoEstateUI(UI *ui)
{
    Service *service = getService(ui);
    UndoRedoRepository *undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray *undoOperations = getUndoOperations(undoRedoRepository), *redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, redoOperations, undoOperations))
        printf("Redo performed successfully! \n");
    else
        printf("No more redos available! \n");
}

void listEstatesWithType(UI *ui){
    OperationOfComparison operation = &EstateTypeContainsString;
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char typeToSearchFor[101];
    printf("Enter the type you want to search for: \n");
    fgets(typeToSearchFor, 101, stdin);
    DynamicArray *estates = getEstateBasedOnType(ui->service, typeToSearchFor, operation);
    if (estates->size == 0)
    {
        printf("There are no estates that satisfy that type! \n");
        free(estates->elems);
        free(estates);
        return;
    }
    for (int i = 0; i < estates->size; ++i) {
        char * estateAsString = formattedEstate(estates->elems[i]);
        printf("%s \n", estateAsString);
        free(estateAsString);
    }
    destroyDynamicArray(estates);
}

void listEstatesUIBasedOnStringRequirement(UI *ui){
    OperationOfComparison operation = &EstateContainsString;
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char stringToSearchFor[101];
    printf("Enter the string you want to search for. For displaying all the entities, just press enter: \n");
    fgets(stringToSearchFor, 101, stdin);
    DynamicArray *estates = getEstateBasedOnFiltering(ui->service, stringToSearchFor, operation);
    if (estates->size == 0)
    {
        printf("There are no estates that satisfy your requirements! \n");
        free(estates->elems);
        free(estates);
        return;
    }
    for (int i = 0; i < estates->size; ++i) {
        char * estateAsString = formattedEstate(estates->elems[i]);
        printf("%s \n", estateAsString);
        free(estateAsString);
    }
    destroyDynamicArray(estates);
}

void listEstatesWithSurface(UI *ui){
    int surface;
    printf("Enter the minimum surface that you want the estates to be printed: ");
    scanf("%d", &surface);
    int command = -1;
    OperationOfComparisonBetweenEstates operation = &smallerSurface;
    while (command != 1 && command != 2){
        printf("In which way do you want the estates to be sorted? \n "
               "1. Increasing \n "
               "2. [BONUS] Decreasing \n");
        printf("Your option is: ");
        scanf("%d", &command);
        switch (command) {
            case 1:
                operation = &smallerSurface;
                break;
            case 2:
                operation = &greaterSurface;
                break;
            default:
                printf("Invalid command! Please try again! \n");
        }
    }
    DynamicArray *estates = getEstateWithSurface(ui->service, surface, operation);
    if (estates->size == 0)
    {
        printf("There are no estates under that surface!  \n");
        free(estates->elems);
        free(estates);
        return;
    }
    for (int i = 0; i < estates->size; ++i) {
        char * estateAsString = formattedEstate(estates->elems[i]);
        printf("%s \n", estateAsString);
        free(estateAsString);
    }
    destroyDynamicArray(estates);
}

void start(UI* ui) {
    generateEntries(getService(ui));
    int command = -1;
    while (command != 0) {
        printMenu();
        printf("Enter command: ");
        scanf("%d", &command);
        switch (command) {
            case 0:
                printf("BYE! \n");
                break;
            case 1:
                addEstateUI(ui);
                break;
            case 2:
                deleteEstateUI(ui);
                break;
            case 3:
                updateEstateUI(ui);
                break;
            case 4:
                listEstatesUIBasedOnStringRequirement(ui);
                break;
            case 5:
                listEstatesWithSurface(ui);
                break;
            case 6:
                listEstatesWithType(ui);
                break;
            case 7:
                undoEstateUI(ui);
                break;
            case 8:
                redoEstateUI(ui);
                break;
            default:
                printf("Invalid command! Please try again! \n");
        }
    }
}