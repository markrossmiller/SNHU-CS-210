#include <iostream>
#include <jni.h>
using namespace std;

class Animal {
public:
	void setTrack(char *track);
	string getTrack();
	void setName(char *name);
	string getName();
	void setType(char *type);
	string getType();
	void setSubType(char *subType);
	string getSubType();
private:
	string track;
	string name;
	string type;
	string subType;
};

class Oviparous : public Animal {
public:
	void setEggs(int eggs);
	int getEggs();
private:
	int eggs;
};

class Mammal : public Animal {
public:
	void setNurse(int nurse);
	int getNurse();
private:
	int nurse;
};

