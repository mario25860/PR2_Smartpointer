#include<iostream>
#include<stdexcept>
#include<map>
#include<vector>
#include<memory>
#include<algorithm>
#include "hcp.h"
#include "illness.h"
#include "patient.h"
#include "hospital.h"


/*Initializes member variables.name must not be empty.If at least one of the parameters is
not matching the requirements, an exception of type std::runtime_error must be thrown.*/
Hospital::Hospital(std::string name): name(name) {
	if (name.empty())
		throw std::runtime_error("Hospital - no name");
}

// If m is not present in hcps, m is inserted into hcps and true is returned, otherwise false
bool Hospital::sign_hcp(std::shared_ptr<Health_Care_Provider> m) {
    auto it = hcps.find(m->get_name());

    if (it == hcps.end()) {
        hcps[m->get_name()] = m;
        return true;
    }
    else 
        return false;

}

//If m is not present in patients, or is present but expired, m is inserted into patients and true is returned, otherwise false.
bool Hospital::admit_patient(std::shared_ptr<Patient> m) {
    auto it = patients.find(m->get_name());

    if (it == patients.end() || it->second.expired()) {
        patients[m->get_name()] = m;
        return true;
    }
    else
        return false;

}

// Removes entry with key n from hcps.If at least one entry is removed, return true, otherwise false
bool Hospital::dismiss_hcp(std::string n) {
    size_t removedEntries = hcps.erase(n);
    return removedEntries > 0;
}

//If no HCP with name n is found, a runtime_error is thrown.Otherwise the shared_ptr is returned.
std::shared_ptr<Health_Care_Provider> Hospital::get_hcp(std::string n) const {
    auto it = hcps.find(n);
    if (it == hcps.end()) {
        throw std::runtime_error("HCP with name " + n + " not found.");
    }

    return it->second;
}

//If no Patient with name n is found, or the weak_ptr is expired, a runtime_error is thrown.Otherwise a shared_ptr is returned
std::shared_ptr<Patient> Hospital::get_patient(std::string n) const {
    auto it = patients.find(n);
    if (it == patients.end() || it->second.expired()) {
        throw std::runtime_error("Patient with name " + n + " not found or expired.");
    }

    return it->second.lock();
}

//Removes entry with key n from patients.If at least one entry of a not expired patient is removed, return true, otherwise false.
bool Hospital::dismiss_patient(std::string n) {
    auto it = patients.find(n);
    if (it != patients.end() && !it->second.expired()) {
        patients.erase(it);
        return true;
    }

    return false;
}



std::ostream& Hospital::print(std::ostream& o) const {
    o << "[" << name << ", hcps {";
    bool first_elem = true;
    for (const auto& [name, hcp_ptr] : hcps){
        if (first_elem){
            o << *hcp_ptr;
            first_elem = false;
        }
        else
            o << ", " << *hcp_ptr;
    }

    first_elem = true;
    o << "}, patients {";
    for (const auto &[name, patient_ptr] : patients){
        auto patient_pointer = patient_ptr.lock();
        if (first_elem){
            if (!patient_ptr.expired())
                o << *patient_pointer;
          
            first_elem = false;
        }
        else
            if (!patient_ptr.expired())
                o << ", " << *patient_pointer;
    }
    o << "}]";
    return o;
}

// Puts a string representation of p into ostream o. Format: [name, hcps{ hcp0, ..., hcpn }, patients{ patient0,..., patientn }]
std::ostream& operator<<(std::ostream& o, const Hospital& p) {
    return p.print(o);
}

