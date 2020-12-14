#include <iostream>
#include <jni.h>
#include "Animal.h"
using namespace std;

void Animal::setTrack(char *track) {
	this->track = std::string { track };

	// Limit to 6 characters.
	if (this->track.length() > 6)
		this->track = this->track.substr(0, 6);

	// Pad with zeroes
	if (this->track.length() < 6)
		this->track = std::string( 6-this->track.length(), '0').append( this->track );
}

string Animal::getTrack() {
	return this->track;
}

void Animal::setName(char *name) {
	// remove trailing whitespace
		for (int i=14;i>=0;i--)
			if (name[i] != ' ')
				break;
			else
				name[i] = 0;
	this->name = std::string { name };
}

string Animal::getName() {
	return this->name;
}

void Animal::setType(char *type) {
	this->type = std::string { type };
}

string Animal::getType() {
	return this->type;
}

void Animal::setSubType(char *subType) {
	// remove trailing whitespace
		for (int i=14;i>=0;i--)
			if (subType[i] != ' ')
				break;
			else
				subType[i] = 0;
	this->subType = std::string { subType };
}

string Animal::getSubType() {
	return this->subType;
}

void Oviparous::setEggs(int eggs) {

	// limit to 2 digits
	this->eggs = eggs>99?99:eggs;
}

int Oviparous::getEggs() {
	return this->eggs;
}

void Mammal::setNurse(int nurse) {
	this->nurse = nurse;
}

int Mammal::getNurse() {
	return this->nurse;
}
