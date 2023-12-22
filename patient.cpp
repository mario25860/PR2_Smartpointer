#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include "illness.h"
#include "hospital.h"
#include "hcp.h"
#include "patient.h"



	/*Initializes member variables.name must not be empty.age must not be less than 0. Patient must
	suffer from at least one Illness at the beginning.If at least one of the parameters
	is not matching the requirements, an exception of type std::runtime_error must be
	thrown.*/
Patient::Patient(std::string name, int age, const std::set<Illness>& illnesses, unsigned wealth) : name(name), age(age), illnesses(illnesses), wealth(wealth) {
	if (name.empty())
		throw std::runtime_error("Patient - no name");
	if (age < 0)
		throw std::runtime_error("Patient - age less than 0");
	if (illnesses.empty())
		throw std::runtime_error("Patient - doesn't suffering from a illness");
}

std::string Patient::get_name() const{
	return name;
}


	//Increases wealth by x
void Patient::increase_wealth(unsigned x) {
	wealth += x;
}

	//If possible, decreases wealth by x and returns true. Otherwise returns false.
bool Patient::pay_procedure(unsigned x) {
	if (wealth >= x) {
		wealth -= x;
		return true;
	}

	else
		return false;

}

	//Adds x to the set of illnesses.
void Patient::catch_disease(const Illness& x) {
	illnesses.insert(x);
}

	//Returns true if patient suffers from at least 1 Illness with specialty x, otherwise false.
bool Patient::requires_treatment_in(Medical_Specialty x) const {
	auto it = find_if(illnesses.begin(), illnesses.end(), [&](const Illness& i) {
		return i.get_specialty() == x;
		});
	return it != illnesses.end();//any_of?

}

	//Returns true if patient suffers from no illnesses, otherwise false.
bool Patient::healthy() const {
	return illnesses.empty();
}

	//Removes all Illness objects with the specialty x. Returns number of removed objects
unsigned Patient::cure(Medical_Specialty x) {
    std::vector<Illness> toRemove;
    for (const Illness& i : illnesses) {
        if (i.get_specialty() == x) {
            toRemove.push_back(i);
        }
    }

    for (const Illness& i : toRemove) {
        illnesses.erase(i);
    }

    return toRemove.size();
}

	/*Compares two Patient objects.Returns true if all member variables of
	the left operand are equal to all the member variables of the right operand.It is your
	choice if you want to implement it in the global namespace or as a member function.*/
bool Patient::operator==(const Patient& rop) const {
	return (name == rop.name) && (age == rop.age) && (illnesses == rop.illnesses) && (wealth == rop.wealth);
}

std::ostream& Patient::print(std::ostream& o) const{
	
	o << "[" << name << ", " << age << " years, {";

	for (auto it = illnesses.begin(); it != illnesses.end(); it++) {
		if (it != std::prev(illnesses.end()))
			o << *it << ", ";
		else
			o << *it << "}, " << wealth << " moneyz]";
	}
	
	return o;
}

/* Puts a string representation of p into ostream o.
Format: [name, age years, { illness0, ..., illnessn }, wealth moneyz]*/
std::ostream& operator<<(std::ostream& o, const Patient& p){
	return p.print(o);
}
