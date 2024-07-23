#include <cassert>
#include "tests.h"


void Test::testDog() {
    Dog dog("Labrador Retriever", "Max", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 2);
    Dog dog2;
    dog2 = dog;
    assert(dog2 == dog);
    assert(dog.getName() == "Max");
    assert(dog.getAge() == 2);
    assert(dog.getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");
    assert(dog.getBreed() == "Labrador Retriever");

    Dog dog3("Siberian Husky", "Luna", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 3);
    dog3.setAge(dog.getAge());
    dog3.setBreed(dog.getBreed());
    dog3.setName(dog.getName());
    dog3.setPhotograph(dog.getPhotograph());

    assert(dog3 == dog);
    assert(dog3.getName() == "Max");
    assert(dog3.getAge() == 2);
    assert(dog3.getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");
    assert(dog3.getBreed() == "Labrador Retriever");

}

void Test::testShelterRepository() {
//    RepoShelterDogs *repository;
//
//    repository.addDog("Luna", "Siberian Husky", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 3);
//    assert(repository.getDogs().size() == 1);
//    assert(repository.getDogs()[0].getName() == "Luna");
//    assert(repository.getDogs()[0].getBreed() == "Siberian Husky");
//    assert(repository.getDogs()[0].getAge() == 3);
//    assert(repository.getDogs()[0].getPhotograph() == "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg");
//
//    repository.updateDog("Luna", "Poodle", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 5);
//    assert(repository.getDogs().size() == 1);
//    assert(repository.getDogs()[0].getName() == "Luna");
//    assert(repository.getDogs()[0].getBreed() == "Poodle");
//    assert(repository.getDogs()[0].getAge() == 5);
//    assert(repository.getDogs()[0].getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");
//
//    Dog dog("Poodle", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 5);
//    assert(repository.getDogPosition(dog) == 0);
//
//    Dog dog1("Poodle", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 3);
//    assert(repository.getDogPosition(dog1) == -1);
//
//    assert(repository.getDogPositionByName("Luna") == 0);
//    assert(repository.getDogPositionByName("Moon") == -1);
//
//    Dog dog2;
//    assert(repository.getDogByName("Luna") == dog);
//    assert(repository.getDogByName("Cooper") == dog2);
//
//
//    repository.deleteDog("Luna");
//    assert(repository.getDogs().size() == 0);
}

void Test::testAdminService() {
//    RepoShelterDogs repository;
//    AdminService service(repository);
//    service.addDog("Poodle", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 5);
//    assert(service.getDogs().size() == 1);
//    try{
//        service.addDog("Poodle", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 5);
//    }catch (Exception &exception) {
//        assert(true);
//    }
//
//    service.updateDog("Luna", "Boxer", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 3);
//    try{
//        service.updateDog("Mimi", "Boxer", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 3);
//    }catch (Exception &exception) {
//        assert(true);
//    }
//
//    try{
//        service.deleteDog("Mimi");
//    }catch (Exception &exception) {
//        assert(true);
//    }
//    Dog dog("Boxer", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 3);
//    assert(service.getDogPosition(dog) == 0);
//
//    assert(service.getDogByName("Luna") == dog);
//    try{
//        service.getDogByName("Mimi");
//    }catch (Exception &exception) {
//        assert(true);
//    }
//    service.deleteDog("Luna");
//    assert(service.getDogs().size() == 0);
}

void Test::testAdoptedRepo() {
//    RepoAdoptedDogs adoptedRepo;
//
//    Dog dog("Boxer", "Luna", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 3);
//
//    adoptedRepo.addAdoption(dog);
//
//    assert(adoptedRepo.getAdoption().size() == 1);
//    assert(adoptedRepo.getAdoption()[0].getName() == "Luna");
//    assert(adoptedRepo.getAdoption()[0].getBreed() == "Boxer");
//    assert(adoptedRepo.getAdoption()[0].getAge() == 3);
//    assert(adoptedRepo.getAdoption()[0].getPhotograph() == "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg");

}

void Test::testUserService() {
//    RepoAdoptedDogs adoptedRepo;
//    RepoShelterDogs shelterRepository;
//    shelterRepository.addDog("Luna", "Siberian Husky", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 3);
//    shelterRepository.addDog("Bella", "German Shepard", "https://gsrescue1.org/wp-content/uploads/2020/11/IMG_2057-scaled.jpg", 4);
//    shelterRepository.addDog("Cooper", "Golden Retriever", "https://www.zooland.ro/data/articles/39/4867/golden-0n.jpg", 5);
//    shelterRepository.addDog("Bailey", "Shih Tzu", "https://www.purina.ro/sites/default/files/styles/ttt_image_510/public/2020-12/Shih%20Tzu2.jpg?itok=hv3bDAtB", 7);
//
//    ServiceUser userService(shelterRepository, adoptedRepo);
//    assert(userService.getDogShelter().size() == 4);
//
//    userService.adoptDog("Luna");
//    userService.adoptDog("Cooper");
//
//    assert(userService.getDogsAdopted().size() == 2);
//    assert(userService.getDogShelter().size() == 2);
//
//    Dog dog = Dog("German Shepard", "Bella", "https://gsrescue1.org/wp-content/uploads/2020/11/IMG_2057-scaled.jpg", 4);
//    Dog dog1 = Dog("Shih Tzu", "Bailey", "https://www.purina.ro/sites/default/files/styles/ttt_image_510/public/2020-12/Shih%20Tzu2.jpg?itok=hv3bDAtB", 7);
//
//    assert(userService.getCurrentDog() == dog);
//    userService.nextDog();
//    assert(userService.getCurrentDog() == dog1);
//
//    std::vector<Dog> filteredDogs1 = userService.getDogsFiltered("Shih Tzu", 10);
//    assert(filteredDogs1.size() == 1);
//    assert(filteredDogs1[0].getName() == "Bailey");
//
//    std::vector<Dog> filteredDogs2 = userService.getDogsFiltered("Shih Tzu", 4);
//    assert(filteredDogs2.size() == 0);
////    assert(filteredDogs1[0].getName() == "Bailey");
//
//    std::vector<Dog> filteredDogs3 = userService.getDogsFiltered("", 10);
//    assert(filteredDogs3.size() == 2);
//    assert(filteredDogs3[0].getName() == "Bella");
//    assert(filteredDogs3[1].getName() == "Bailey");



}
void Test::testAll() {
    testDog();
    testShelterRepository();
    testAdminService();
    testAdoptedRepo();
    testUserService();
}