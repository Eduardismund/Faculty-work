#include "repo/Repo.h"
#include "service/Service.h"
#include "ui/UI.h"
#include "tests/testEstate.h"
#include "tests/testService.h"
#include <crtdbg.h>

int main()
{
    testEstateAll();
    testAllService();
    int typeOfUndoRedo = 2;
    Repo *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
    UI *ui = createUI(service);
    start(ui);
    destroyUI(ui);
    _CrtDumpMemoryLeaks();
    return 0;
}