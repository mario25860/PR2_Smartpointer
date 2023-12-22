#ifndef ILLNESS_H
#define ILLNESS_H

#include<iostream>
#include<stdexcept>
#include<string>




enum class Medical_Specialty {
	Cardiology, Dermatology, Endocrinology, Gynecology,
	Neurology, Oncology, Pathology, Pediatrics, Pulmonology, Urology
};
/*Puts a string
representation of m into ostream o. The string representation of m should reflect the
name of the constant, e.g. Medical_Specialty::Pathology should be transformed to
Pathology*/
std::ostream& operator<<(std::ostream& o, Medical_Specialty m);

class Illness{
	Medical_Specialty med;
	std::string name;

public:

	/* Initializes member variables. name must
	not be empty. If at least one of the parameters is not matching the requirements, an
	exception of type std::runtime_error must be thrown*/
	Illness(Medical_Specialty med, const std::string& name);


	//returns med
	Medical_Specialty get_specialty() const;

	//returns name
	std::string get_name() const;


  
	/*Compares two Illness objects.Returns true if name and specialty are
	equal.It is your choice if you want to implement it in the global namespace or as a
	member function.*/
	bool operator==(const Illness& rop) const;

	/* Compares two Illness objects.Returns true if specialty of the left operand
	is less than the specialty of the right operand(conforming to the order of definition).
	If the specialties are equal, the function returns true if the name of the left operand is
	less than the name of the right operand(in lexicographical order).It is your choice if
	you want to implement it in the global namespace or as a member function*/
	bool operator<(const Illness& rop) const;

	std::ostream& print(std::ostream& o) const;

};

//Puts a string representation of ill into ostream o. Format: [med, name]
std::ostream& operator<<(std::ostream& o, const Illness& ill);



#endif
