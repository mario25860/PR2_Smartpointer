#ifndef PATIENT_H
#define PATIENT_H

#include<iostream>
#include<stdexcept>
#include<set>
#include "illness.h"


class Patient{

	std::string name;
	int age;
	std::set<Illness> illnesses;
	unsigned wealth;

public:
	/*Initializes member variables.name must not be empty.age must not be less than 0. Patient must
	suffer from at least one Illness at the beginning.If at least one of the parameters
	is not matching the requirements, an exception of type std::runtime_error must be
	thrown.*/
	Patient(std::string name, int age, const std::set<Illness>& illnesses, unsigned wealth = 200);

	std::string get_name() const;

	//Increases wealth by x
	void increase_wealth(unsigned x);
	
	//If possible, decreases wealth by x and returns true. Otherwise returns false.
	bool pay_procedure(unsigned x);

	//Adds x to the set of illnesses.
	void catch_disease(const Illness& x);
		
	//Returns true if patient suffers from at least 1 Illness with specialty x, otherwise false.
	bool requires_treatment_in(Medical_Specialty x) const;
		
	//Returns true if patient suffers from no illnesses, otherwise false.
	bool healthy() const;
	
	//Removes all Illness objects with the specialty x. Returns number of removed objects
	unsigned cure(Medical_Specialty x);

	/*Compares two Patient objects.Returns true if all member variables of
	the left operand are equal to all the member variables of the right operand.It is your
	choice if you want to implement it in the global namespace or as a member function.*/
	bool operator==(const Patient& rop) const;

	std::ostream& print(std::ostream& o) const;
};
/* Puts a string representation of p into ostream o.
Format: [name, age years, { illness0, ..., illnessn }, wealth moneyz]*/
std::ostream& operator<<(std::ostream& o, const Patient& p);



#endif
