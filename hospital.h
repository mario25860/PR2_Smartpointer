#ifndef HOSPITAL_H
#define HOSPITAL_H

#include<iostream>
#include<stdexcept>
#include<set>
#include<memory>
#include<map>
#include "illness.h"
#include "patient.h"
#include "hcp.h"



class Hospital{
	std::string name;
	std::map<std::string, std::shared_ptr<Health_Care_Provider>> hcps; //key is the name of a HPC
	std::map<std::string, std::weak_ptr<Patient>> patients; //Key is the name of a Patient.

public:
	/*Initializes member variables.name must not be empty.If at least one of the parameters is 
	not matching the requirements, an exception of type std::runtime_error must be thrown.*/
	Hospital(std::string name);

	// If m is not present in hcps, m is inserted into hcps and true is returned, otherwise false
	bool sign_hcp(std::shared_ptr<Health_Care_Provider> m);

	//If m is not present in patients, or is present but expired, m is inserted into patients and true is returned, otherwise false.
	bool admit_patient(std::shared_ptr<Patient> m);

	// Removes entry with key n from hcps.If at least one entry is removed, return true, otherwise false
	bool dismiss_hcp(std::string n);

	//If no HCP with name n is found, a runtime_error is thrown.Otherwise the shared_ptr is returned.
	std::shared_ptr<Health_Care_Provider> get_hcp(std::string n) const;

	//If no Patient with name n is found, or the weak_ptr is expired, a runtime_error is thrown.Otherwise a shared_ptr is returned
	std::shared_ptr<Patient> get_patient(std::string n) const;

	//Removes entry with key n from patients.If at least one entry of a not expired patient is removed, return true, otherwise false.
	bool dismiss_patient(std::string n); 

	std::ostream& print(std::ostream& o) const;
};
// Puts a string representation of p into ostream o. Format: [name, hcps{ hcp0, ..., hcpn }, patients{ patient0,..., patientn }]
std::ostream& operator<<(std::ostream& o, const Hospital& p);



#endif
