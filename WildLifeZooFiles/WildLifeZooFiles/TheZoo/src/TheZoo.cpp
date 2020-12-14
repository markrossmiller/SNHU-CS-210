#include <iostream>
#include <jni.h>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include "TheZoo.h"
using namespace std;

// Helper function to compare two strings for equality
bool iequals(const string& a, const string& b)
{
    return std::equal(a.begin(), a.end(), b.begin(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

// AddAnimal: prompt for Animal info and add to vector
// Since it requires modification, we need to pass as a pointer
void AddAnimal(vector <Animal *> *animal_v)
{
	Animal *a;
	string track;
	string name;
	string type;
	string subType;

	cout << "Track #: ";
	cin >> track;

	cout << "Name: ";
	cin >> name;

	cout << "Type (Oviparous / Mammal): ";
	cin >> type;

	if (iequals("Oviparous", type)) {
		Oviparous *o = new Oviparous();
		a = o;

		a->setTrack((char *)track.c_str());
		a->setName((char *)name.c_str());
		a->setType("Oviparous");

	} else if (iequals("Mammal", type)) {
		Mammal *m = new Mammal();
		a = m;

		a->setTrack((char *)track.c_str());
		a->setName((char *)name.c_str());
		a->setType("Mammal");
	} else { // Error

	}

	cout << "Subtype: ";
	cin >> subType;
	a->setSubType((char *)subType.c_str());

	if (iequals("Oviparous", type)) {
		Oviparous *o = (Oviparous *)a;
		int eggs;
		cout << "Eggs: ";
		cin >> eggs;
		o->setEggs(eggs);
	} else { // must be Mammal now
		Mammal *m = (Mammal *)a;
		int nurse;
		cout << "Nursing: ";
		cin >> nurse;
		m->setNurse(nurse);
	}

	animal_v->push_back(a);
}

// RemoveAnimal: delete an animal from our vector...
// Since it requires modification, we need to pass as a pointer
void RemoveAnimal(vector <Animal *> *animal_v, string track)
{
	// search for element(s) with Track # "track" and remove it.
     for (unsigned int i=0;i<animal_v->size();i++) {
    	 Animal *a = animal_v->at(i);
         if (iequals(a->getTrack(), track)) {
        	 cout << "Removing: " << a->getTrack() << endl;

        	 animal_v->erase(animal_v->begin()+i);
         }
     }
}

vector<Animal *> LoadDataFromFile()
{
	vector<Animal *> animal_v;
	cout << "Loading from file \"zoodata.txt\"..." << endl << endl;

	// load data from "zoodata.txt"
	ifstream zoodata_txt("zoodata.txt");

	// declare input line that we will parse from
	string line;

	// while read a line from "zoodata.txt":
	while (getline(zoodata_txt, line))
	{
		// For each line, create an Animal object.
		Animal *animal = nullptr;

		//cout << "Reading line from file \"zoodata.txt\"..." << endl;
		//cout << line << endl;

	    istringstream iss(line);

	    // Now that type(mammal/oviparous) is set, do the rest...
	    char trackstr[7];
	    char namestr[16];
	    char typestr[16];
	    char subtypestr[16];

	    // TRACK:
	    line.copy(trackstr, 6, 0);
	    trackstr[6] = 0;

	    // NAME:
	    line.copy(namestr, 15, 6);
	    namestr[15] = 0;

	    // TYPE:
	    line.copy(typestr, 15, 6+15);
	    typestr[15] = 0;

	    // Check for our two defined types:
	    if (iequals("oviparous", typestr)) {
		    //cout << typestr << " is oviparous!" << endl;
	    	Oviparous *o = new Oviparous();
	    	o->setType("Oviparous");
	    	animal = o;
	    } else if (iequals("mammal", typestr)) {
		    //cout << typestr << " is a mammal!" << endl;
	    	Mammal *m = new Mammal();
	    	m->setType("Mammal");
	    	animal = m;
	    }

	    // invoke animal creation...
	    animal->setTrack(trackstr);
	    animal->setName(namestr);
	    animal->setType(typestr);

	    //cout << "animal->getTrack(): " << animal->getTrack() << endl;
	    //cout << "animal->getName(): " << animal->getName() << endl;
	    //cout << "animal->getType(): " << animal->getType() << endl;

	    line.copy(subtypestr, 15, 6+15+15);
	    subtypestr[15] = 0;
	    animal->setSubType(subtypestr);

	    //cout << "animal->getSubType(): " << animal->getSubType() << endl;


	    // Magic to get last two integers:
	    // assume track, eggs, nurse are the only integers...
	    int track=-1, eggs=-1;
	    while (!iss.eof()) {
	        string temp;
	        int found;

	        iss >> temp;
	    	if (stringstream(temp) >> found) {
	    		    if (track == -1) { // TRACK
	    		    	track = 0;
	    		    } else if (eggs == -1) { // EGGS
	    	    		eggs = found;
	    	    		if (iequals("oviparous", animal->getType())) {
	    	    			Oviparous *o = (Oviparous *) animal;
	    	    			o->setEggs(found);

	    	    			//cout << "o->getEggs(): " << o->getEggs() << endl;
	    	    		}
	    	    	}
	    	    	else { // NURSING
	    	    		if (iequals("mammal", animal->getType())) {
	    	    			Mammal *m = (Mammal *) animal;
	    	    			m->setNurse(found);

	    	    			//cout << "m->getNurse(): " << m->getNurse() << endl;
	    	    		}
	    	    	}
	    	}
	    }

	    animal_v.push_back(animal);
	}

	return(animal_v);
}

void SaveDataToFile(vector <Animal *> animal_v)
{
	// file for writing output to..
	ofstream zoodata_txt;
	zoodata_txt.open ("zoodata2.txt");

     // Iterate over the entire vector
	for (unsigned int i=0;i<animal_v.size();i++) {
		Animal *a = animal_v.at(i);
		char tmp[16];
		string tmpstr;

		// track #
		tmpstr = a->getTrack();
		for (int i=0;i<6;i++)
			tmp[i] = tmpstr.at(i);
		tmp[6] = 0;
		zoodata_txt << tmp;

		// name
		tmpstr = a->getName();
		for (int i=0;i<15;i++)
			if (tmpstr.size() < i+1)
				tmp[i] = ' ';
			else
				tmp[i] = tmpstr.at(i);
		tmp[15] = 0;
		zoodata_txt << tmp;

		// type
		tmpstr = a->getType();
		for (int i=0;i<15;i++)
			if (tmpstr.size() < i+1)
				tmp[i] = ' ';
			else
				tmp[i] = tmpstr.at(i);
		tmp[15] = 0;
		zoodata_txt << tmp;

		// subtype
		tmpstr = a->getSubType();
		for (int i=0;i<15;i++)
			if (tmpstr.size() < i+1)
				tmp[i] = ' ';
			else
				tmp[i] = tmpstr.at(i);
		tmp[15] = 0;
		zoodata_txt << tmp;

		if (iequals("Oviparous", a->getType()))
			zoodata_txt << ((Oviparous *)a)->getEggs();
		else
			zoodata_txt << 0;

		// space between eggs and nursing
		zoodata_txt << " ";

		if (iequals("Mammal", a->getType()))
			zoodata_txt << ((Mammal *)a)->getNurse();
		else
			zoodata_txt << 0;

		zoodata_txt << endl;

	}
	zoodata_txt.close();
}

void DisplayMenu()
{
     cout << "(L)oad Animal Data\t(A)dd Record" << endl;
     cout << "(G)enerate Data\t\t(D)elete Record" << endl;
     cout << "Displa(Y) Animal Data\t(S)ave Animal Data" << endl;
     cout << "e(X)it" << endl;
     cout << endl << ">>>> ";
}

void DisplayAnimalData(vector <Animal *> animal_v) {

	// Display header info
	cout << endl << endl;
	cout << "Track#\tName\t\tType\t\tSub-Type\tEggs\tNursing" << endl << endl;

	// Iterate over Animals in vector
	for (unsigned int i=0;i<animal_v.size();i++) {
		Animal *a = animal_v.at(i);

		cout << a->getTrack() << " ";
		cout << a->getName() << "\t";
		if (a->getName().length() < 8)
			cout << "\t";
		cout << a->getType() << "\t";
		cout << a->getSubType() << "\t";
		if (a->getSubType().length() < 8)
			cout << "\t";

		//cout << iequals("Oviparous", a->getType()) ? ((Oviparous *)a)->getEggs() : 0;
		if (iequals("Oviparous", a->getType())) {
			Oviparous *o = (Oviparous *) a;
			cout << o->getEggs();
		} else { cout << "0"; }

		cout << "\t";
		cout << iequals("Mammal", a->getType()) ? ((Mammal *)a)->getNurse() : 0;
		cout << endl;
	}
	cout << endl << endl;
}


int main()
{
	vector <Animal *> av;

	while (true) {
		char c;
		DisplayMenu();

		cin >> c;

		switch(c) {
		case 'L':
			av = LoadDataFromFile();
			break;
		case 'G':
			GenerateData();
			break;
		case 'Y':
			DisplayAnimalData(av);
			break;
		case 'A':
			AddAnimal(&av);
			break;
		case 'D':
		{
			string track;
			cout << "Track #: ";
			cin >> track;
			RemoveAnimal(&av, track);
		}
			break;
		case 'S':
			SaveDataToFile(av);
			break;
		case 'X':
			return(1);
			break;
		default:
			break;
		}
	}
}
