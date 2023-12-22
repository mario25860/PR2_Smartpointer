#include "illness.h"
#include<vector>
#include<string>
#include<iostream>

#include <stdexcept>

	/* Initializes member variables. name must
	not be empty. If at least one of the parameters is not matching the requirements, an
	exception of type std::runtime_error must be thrown*/
Illness::Illness(Medical_Specialty med, const std::string& name) : med(med), name(name){
	if (name.empty())
		throw std::runtime_error("Illness - name empty");
}


	//returns med
Medical_Specialty Illness::get_specialty() const {
	return med;
}

	//returns name
std::string Illness::get_name() const {
	return name;
}


	/*Compares two Illness objects.Returns true if name and specialty are
	equal.It is your choice if you want to implement it in the global namespace or as a
	member function.*/
bool Illness::operator==(const Illness& rop) const {
	return (name == rop.name && med == rop.med);
}

	/* Compares two Illness objects.Returns true if specialty of the left operand
	is less than the specialty of the right operand(conforming to the order of definition).
	If the specialties are equal, the function returns true if the name of the left operand is
	less than the name of the right operand(in lexicographical order).It is your choice if
	you want to implement it in the global namespace or as a member function*/
bool Illness::operator<(const Illness& rop) const {
	if (med == rop.med)
		if (name < rop.name) //hier Fehler?
			return true;
		else
			return false;

	else
		return med < rop.med;
}

std::ostream& Illness::print(std::ostream& o) const {

	o << "[" << med << ", " << name << "]";

	return o;

}

//Puts a string representation of ill into ostream o. Format: [med, name]
std::ostream& operator<<(std::ostream& o, const Illness& ill) {
	return ill.print(o);
}




