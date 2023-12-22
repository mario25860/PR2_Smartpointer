#include<iostream>
#include<stdexcept>
#include<map>
#include<vector>
#include<memory>
#include<algorithm>
#include "hcp.h"
#include "illness.h"
#include "patient.h"



/*Initializes member variables. name must not be empty. If at least one of the parameters
is not matching the requirements, an exception of type std::runtime_error must be thrown*/
Health_Care_Provider::Health_Care_Provider(std::string name, const std::set <Medical_Specialty>& topics, unsigned wealth) : name(name), topics(topics), wealth(wealth) {
	if (name.empty())
		throw std::runtime_error("HCP - no name");
}

// Returns name
std::string Health_Care_Provider::get_name() const {
	return name;
}



// Increases wealth by x
void Health_Care_Provider::increase_wealth(unsigned x) {
	wealth += x;
}

// If possible, wealth is decreased by x and true is returned. Otherwise false.
bool Health_Care_Provider::pay_license(unsigned x) {
	if (wealth >= x) {
		wealth -= x;
		return true;
	}

	else
		return false;

}


// Return true if m is present in topics
bool Health_Care_Provider::eligible_for(Medical_Specialty m) {
	return any_of(topics.begin(), topics.end(), [&](const auto& med_spec){
    return med_spec == m;
  });

}

std::ostream& Health_Care_Provider::print(std::ostream& o) const {
	o << "[" << name << ", {";
	
  int size = topics.size();
  int counter {0};
  if(size != counter){
    for_each(topics.begin(), topics.end(), [&](const auto& topic){
      counter++;
      if(size!=counter)
        o << topic << ", ";
      else
        o << topic << "}, " << wealth << " moneyz, " << hcp_type() << "]";
    });
  }
  else
    o << "}, " << wealth << " moneyz, " << hcp_type() << "]";

	return o;
}

/*Puts a string representation of h into ostream o.
Format: [name, { topics0, ..., topicsn }, wealth moneyz, hcp_type]*/
std::ostream& operator<<(std::ostream& o, const Health_Care_Provider& h) {
	return h.print(o);
}




	/*Initializes member variables.Same rules as Health_Care_Provider Constructor.
	If at least one of the parameters is not matching the requirements, an exception of type
	std::runtime_error must be thrown*/
Teaching_Health_Care_Provider::Teaching_Health_Care_Provider(unsigned fee, std::string name, const std::set<Medical_Specialty>& topics, unsigned wealth) : Health_Care_Provider(name, topics, wealth), fee(fee) {
}
	

	/*If this is eligible for m and p requires treatment in m and p can pay the
	price x, p is cured from m.Wealth is increased by x.Returns number of cured illnesses*/
unsigned Teaching_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m) {
	if (eligible_for(m) && (p->requires_treatment_in(m)) && (p->pay_procedure(x))) {

				//unsigned curedIllnesses = p->cure(m);

				increase_wealth(x);
				return p->cure(m);;

	}
	return 0;
	}

	//Returns "Teacher"
std::string Teaching_Health_Care_Provider::hcp_type() const {
	return "Teacher";
	}

	/*If target points to this, knows m already or cannot afford to pay fee, false is returned.
	Otherwise wealth is increased by fee, target pays the fee and receives a license for the topic m and true is returned.*/
bool Teaching_Health_Care_Provider::teach(Medical_Specialty m, std::shared_ptr<Health_Care_Provider> target) {

	if (target.get() == this || target->eligible_for(m) || !eligible_for(m))
		return false;

	else if (target->pay_license(fee)) {

		increase_wealth(fee);

		target->receive_license(m);
		return true;
	}
	else
		return false;
	}



	/*Initializes member variables.Same rules as Health_Care_Provider Constructor.If at
	least one of the parameters is not matching the requirements, an exception of type
	std::runtime_error must be thrown.*/
	Smart_Health_Care_Provider::Smart_Health_Care_Provider(unsigned fee, std::string name, const std::set<Medical_Specialty>& topics, unsigned wealth) : Health_Care_Provider(name, topics, wealth), fee(fee) {
	}

	//Returns 0.
	unsigned Smart_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m) {
		return 0;
	}

	//Returns "Smart"
	std::string Smart_Health_Care_Provider::hcp_type() const {
		return "Smart";
	}

	//Adds the license to the topics.In addition,the wealth of this is increased by fee
	void Smart_Health_Care_Provider::receive_license(Medical_Specialty m) {

		Health_Care_Provider::receive_license(m);

		increase_wealth(fee);
	}



std::ostream& operator<<(std::ostream& o, Medical_Specialty m) {
    switch (m) {
        case Medical_Specialty::Cardiology:
            o << "Cardiology";
            break;
        case Medical_Specialty::Dermatology:
            o << "Dermatology";
            break;
        case Medical_Specialty::Endocrinology:
            o << "Endocrinology";
            break;
        case Medical_Specialty::Gynecology:
            o << "Gynecology";
            break;
        case Medical_Specialty::Neurology:
            o << "Neurology";
            break;
        case Medical_Specialty::Oncology:
            o << "Oncology";
            break;
        case Medical_Specialty::Pathology:
            o << "Pathology";
            break;
        case Medical_Specialty::Pediatrics:
            o << "Pediatrics";
            break;
        case Medical_Specialty::Pulmonology:
            o << "Pulmonology";
            break;
        case Medical_Specialty::Urology:
            o << "Urology";
            break;
    }
    return o;
}
    



