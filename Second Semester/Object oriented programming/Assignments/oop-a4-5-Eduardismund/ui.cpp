#include <iostream>
#include "ui.h"
#include "Exception.h"
#include "AdminService.h"
#include <thread>
#include <chrono>

using namespace std;
//constructor
UI::UI(AdminService &serviceForAdminToBeSet, UserService &serviceForUserToBeSet): serviceForAdmin{serviceForAdminToBeSet}, serviceForUser{serviceForUserToBeSet} {
}

//destructor
UI::~UI()= default;

//run the app
void UI::run(){
    this->chooseMode();
}

//main menu
void UI::printMenu() {
    cout<<"_________________________________________________________________\n";
    cout<<"\tWelcome to 'Keep calm and adopt a pet' Shelter\t"<<endl;
    cout<<"Press (1) for Admin Mode"<<endl;
    cout<<"Press (2) for User Mode"<<endl;
    cout<<"Press (3) to Exit"<<endl;
    cout<<"_________________________________________________________________\n";
}

//choose mode
void UI::chooseMode() {
    char choice = 'a';
    while (choice != '3')
    {
        cout<<endl;
        UI::printMenu();
        cout<<"Insert an option: ";
        cin>>choice;
        switch(choice){
            case '1': //admin mode
            {
                this->generateEntries();
                this->startAdmin();
            }
                break;
            case '2'://user mode
            {
                this->generateEntries();
                this->startUser();
                break;
            }
            case '3'://exit
            {
                cout<<"Thank you for using my application! Bye!"<<endl;
                break;
            }
            default:
                cout<<"incorrect option! try again!"<<endl;
                break;
        }
    }
}

void UI::printAdminMenu() {
    cout<<"_________________________________________________________________\n";
    cout<<"\tOptions:\t"<<endl;
    cout<<"Press (1) to add a Dog to the Shelter"<<endl;
    cout<<"Press (2) to update a Dog from the Shelter"<<endl;
    cout<<"Press (3) to delete a Dog from the Shelter"<<endl;
    cout<<"Press (4) to list all Dogs from the Shelter"<<endl;
    cout<<"Press (5) to Exit"<<endl;
    cout<<"_________________________________________________________________\n";
}
void UI::startAdmin() {
    char choice = 'a';
    while (choice != '5')
    {
        UI::printAdminMenu();
        cout<<"Insert an option: ";
        cin>>choice;
        switch(choice){
            case '1': //add a dog
            {
                string name, breed, photo, stringAge;
                int age;
                cout<<"Name(unique): ";
                cin>>name;
                cout<<"Breed: ";
                cin>>breed;
                cout<<"Age: ";
                cin>>stringAge;
                if(stringAge.find_first_not_of("0123456789")!= std::string::npos)
                {
                    cout<<"Age must be a positive number!";
                    break;
                }

                age = stoi(stringAge);
                cout<<"Photograph: ";
                cin>>photo;
                try{
                    this->serviceForAdmin.addDog(breed, name, photo, age);
                    cout<<"Dog added successfully!\n";
                } catch (Exception &exception) {
                    cout << exception.what() <<endl;
                }
                break;
            }
            case '3'://remove a dog
            {
                string name;
                cout<<"Name for the dog to be deleted: ";
                cin>>name;
                try{
                    this->serviceForAdmin.deleteDog(name);
                    cout<<"Dog deleted successfully!\n";
                } catch (Exception &exception) {
                    cout << exception.what() <<endl;
                }
                break;
            }
            case '2': // update a dog
            {
                string name, breed, photo, stringAge;
                int age;
                cout<<"Name of the dog to be updated(unique): ";
                cin>>name;
                cout<<"New breed: ";
                cin>>breed;
                cout<<"New age: ";
                cin>>stringAge;
                if(stringAge.find_first_not_of("0123456789")!= std::string::npos)
                {
                    cout<<"Age must be a positive number!";
                    break;
                }

                age = stoi(stringAge);
                cout<<"New photograph: ";
                cin>>photo;
                try{
                    this->serviceForAdmin.updateDog(name, breed, photo, age);
                    cout<<"Dog updated successfully!\n";
                } catch (Exception &exception) {
                    cout << exception.what() <<endl;
                }
                break;
            }
            case '4': //list all dogs
            {
                int delayMilliseconds = 500;
                for(int i=0; i<this->serviceForAdmin.getDogs().getSize();i++)
                {
                    cout<<" ------- Dog "<<i+1<<"--------"<<endl;
                    cout<<"Name: "<<this->serviceForAdmin.getDogs()[i].getName()<<endl;
                    cout<<"Breed: "<<this->serviceForAdmin.getDogs()[i].getBreed()<<endl;
                    cout<<"Age: "<<this->serviceForAdmin.getDogs()[i].getAge()<<endl;
                    cout<<"Photograph: "<<this->serviceForAdmin.getDogs()[i].getPhotograph()<<endl<<endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
                }
                break;
            }
            case '5'://exit
            {
                break;
            }
            default:
                cout<<"incorrect option! try again!"<<endl;
                break;
        }
    }

}
void UI::generateEntries() {
    if( this->serviceForAdmin.getDogs().getSize() == 0)
    {
        this->serviceForAdmin.addDog("Labrador Retriever", "Max", "https://i.pinimg.com/564x/0d/23/62/0d236297adb04e3d6acaa180307a5a5a.jpg", 2);
        this->serviceForAdmin.addDog("Siberian Husky", "Luna", "https://cdn.rescuegroups.org/6062/pictures/animals/6561/6561163/78770305.jpg", 3);
        this->serviceForAdmin.addDog("German Shepard", "Bella", "https://gsrescue1.org/wp-content/uploads/2020/11/IMG_2057-scaled.jpg", 4);
        this->serviceForAdmin.addDog("Golden Retriever", "Cooper", "https://www.zooland.ro/data/articles/39/4867/golden-0n.jpg", 5);
        this->serviceForAdmin.addDog("Beagle", "Daisy", "https://ts2.mm.bing.net/th?q=Beagle%20Puppies%20In%20Ohio", 2);
        this->serviceForAdmin.addDog("Boxer", "Rocky", "https://www.boxerrescueontario.com/wp-content/uploads/2018/06/Boxer-pic2.jpg", 6);
        this->serviceForAdmin.addDog("Poodle", "Charlie", "https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2023/02/09141023/Diana-the-Poodle.jpg", 3);
        this->serviceForAdmin.addDog("Shih Tzu", "Bailey", "https://www.purina.ro/sites/default/files/styles/ttt_image_510/public/2020-12/Shih%20Tzu2.jpg?itok=hv3bDAtB", 7);
        this->serviceForAdmin.addDog("Dachshund", "Sadie", "https://i.pinimg.com/564x/2f/a2/6d/2fa26d2082e48cd42dabbca17ce242e0.jpg", 2);
        this->serviceForAdmin.addDog("Bulldog", "Lolita", "https://i.pinimg.com/736x/40/5a/02/405a025172f9317cb962b01018f7a836.jpg", 5);
    }
}

void UI::printUserMenu() {
    cout<<"_________________________________________________________________\n";
    cout<<"\tOptions:\t"<<endl;
    cout<<"Press (1) to see the current Dog in the Shelter"<<endl;
    cout<<"Press (2) to if you choose to adopt the current dog"<<endl;
    cout<<"Press (3) to go to the next Dog in the Shelter"<<endl;
    cout<<"Press (4) to display the adoption list"<<endl;
    cout<<"Press (5) to display and filter the Dogs by breed and age"<<endl;
    cout<<"Press (x) to Exit"<<endl;
    cout<<"_________________________________________________________________\n";
}

void UI::printFilteredDogs() {
    cout<<"_________________________________________________________________\n";
    cout<<"\tOptions:\t"<<endl;
    cout<<"Press (2) to if you choose to adopt the current dog"<<endl;
    cout<<"Press (3) to go to the next Dog in the Shelter"<<endl;
    cout<<"Press (4) to display the adoption list"<<endl;
    cout<<"Press (x) to Exit"<<endl;
    cout<<"_________________________________________________________________\n";

}

void UI::startUser() {
    char cmd ='0';
    while(cmd!='6')
    {
        this->printUserMenu();
        cout<<"Insert your command here: ";
        cin>>cmd;
        switch(cmd){
            case '1': {
                if (this->serviceForUser.getDogShelter().getSize() == 0) {
                    cout << "There are no more dogs to display!\n";
                    break;
                }
                Dog d = this->serviceForUser.getCurrentDog();
                cout << "--------Current dog--------\n";
                cout << "Name: " << d.getName() << endl;
                cout << "Breed: " << d.getBreed() << endl;
                cout << "Age: " << d.getAge() << endl;
                cout << "Photograph: " << d.getPhotograph() << endl;
            }
                break;
            case '2':
            {
                if (this->serviceForUser.getDogShelter().getSize() == 0) {
                    cout << "There are no more dogs to display!\n";
                    break;
                }
                Dog d = this->serviceForUser.getCurrentDog();
                this->serviceForUser.adoptDog(d);}
                break;
            case '3': {
                if (this->serviceForUser.getDogShelter().getSize() == 0) {
                    cout << "There are no more dogs to display!\n";
                    break;
                }
                this->serviceForUser.nextDog();
            };
                break;
            case '4': {
                DynamicVector<Dog> adoptionList = this->serviceForUser.getDogsAdopted();
                if (adoptionList.getSize() == 0)
                    cout << "You haven't adopted any dogs yet!\n";
                else {
                    cout << "You have adopted the following dogs:\n";
                    int delayMilliseconds = 500;
                    for (int i = 0; i < adoptionList.getSize(); i++) {
                        cout << " ------- Dog " << i + 1 << "--------" << endl;
                        cout << "Name: " << adoptionList[i].getName() << endl;
                        cout << "Breed: " << adoptionList[i].getBreed() << endl;
                        cout << "Age: " << adoptionList[i].getAge() << endl;
                        cout << "Photograph: " << adoptionList[i].getPhotograph() << endl << endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
                    }
                    break;
                }
            }
                break;
            case '5':
            {
                string breed;
                int age;
                cout<<"Breed of the dog you desire to filter(if not, write 'no'): ";
                cin>>breed;
                if(breed == "no")
                    breed = "";
                string stringAge;
                cout<<"The maximum age of the dogs: ";
                cin>> stringAge;
                if(stringAge.find_first_not_of("0123456789") != std::string::npos)
                {
                    cout<<"Age must be a positive integer number! "<<endl;
                    break;
                }

                age = stoi(stringAge);
                DynamicVector<Dog> filteredDogs = this->serviceForUser.getDogsFiltered(breed, age);
                if(filteredDogs.getSize() == 0) {
                    cout << "There are no Dogs with this breed and having an age smaller than " << age << endl;
                    break;
                }

                int i = 0;
                while(i < filteredDogs.getSize()){
                    cout << " ------- Dog " << i + 1 << "--------" << endl;
                    cout << "Name: " << filteredDogs[i].getName() << endl;
                    cout << "Breed: " << filteredDogs[i].getBreed() << endl;
                    cout << "Age: " << filteredDogs[i].getAge() << endl;
                    cout << "Photograph: " << filteredDogs[i].getPhotograph() << endl << endl;
                    printFilteredDogs();
                    char choice = '0';
                    while(choice != 'x'){
                        cout<<"Insert your choice: ";
                        cin>>choice;
                        switch(choice){
                            case '2':
                            {
                                if(this->serviceForUser.getDogShelter().getSize()== 0) {
                                    cout << "There are no more dogs to adopt!\n";
                                    break;
                                }
                                Dog currentDog = filteredDogs[i];
                                this->serviceForUser.adoptDog(currentDog.getName());
                                filteredDogs.removeElement1(currentDog);
                                cout<<"Dog adopted successfully!\n";
                                if(filteredDogs.getSize() == 0)
                                {
                                    cout<<"There are no more dogs left!\n";
                                    goto outOfThis;
                                }
                                i = (i+1) % filteredDogs.getSize();
                                choice = 'x';
                            }
                                break;
                            case '3':
                            {
                                i = (i+1) % filteredDogs.getSize();
                                choice = 'x';
                            }
                                break;
                            case '4':{
                                DynamicVector<Dog> adoptionList = this->serviceForUser.getDogsAdopted();
                                if (adoptionList.getSize() == 0)
                                    cout << "You haven't adopted any dogs yet!\n";
                                else {
                                    cout << "You have adopted the following dogs:\n";
                                    int delayMilliseconds = 500;
                                    for (int i = 0; i < adoptionList.getSize(); i++) {
                                        cout << " ------- Dog " << i + 1 << "--------" << endl;
                                        cout << "Name: " << adoptionList[i].getName() << endl;
                                        cout << "Breed: " << adoptionList[i].getBreed() << endl;
                                        cout << "Age: " << adoptionList[i].getAge() << endl;
                                        cout << "Photograph: " << adoptionList[i].getPhotograph() << endl << endl;
                                        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
                                    }
                                    break;
                                }
                            }
                                break;
                            case 'x':
                                goto outOfThis;
                            default:
                                cout<<"Invaild Choice! Please try again! \n";
                                break;

                        }
                    }

                }

            }
                outOfThis:
                break;
            default:
                cout<<"Invalid choice!\n";
                break;

        }
    }
    cout<<"thank you for using my app!\n";
}
