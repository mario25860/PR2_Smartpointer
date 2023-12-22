#ifndef HPC_H
#define HPC_H

#include<iostream>
#include<stdexcept>
#include<set>
#include<vector>
#include<memory>
#include "patient.h"
#include "illness.h"


class Health_Care_Provider{
	std::string name;
	std::set <Medical_Specialty> topics;
	unsigned wealth;

public:
	/*Initializes member variables. name must not be empty. If at least one of the parameters
	is not matching the requirements, an exception of type std::runtime_error must be thrown*/
	Health_Care_Provider(std::string name, const std::set <Medical_Specialty>& topics, unsigned wealth = 500);

	// Returns name
	std::string get_name() const;


	virtual ~Health_Care_Provider() = default;

	// Increases wealth by x
	void increase_wealth(unsigned x);

	virtual unsigned perform_procedure(unsigned u, std::shared_ptr<Patient> p, Medical_Specialty m) = 0;
	//both not implemented
	virtual std::string hcp_type() const = 0;

	// If possible, wealth is decreased by x and true is returned. Otherwise false.
	bool pay_license(unsigned x);

	// Adds x to topics
	virtual void receive_license(Medical_Specialty x) {
		topics.insert(x);
	}

	// Return true if m is present in topics
	bool eligible_for(Medical_Specialty m);

  friend class Teaching_Health_Care_Provider;

  
	std::ostream& print(std::ostream& o) const;
};
/*<Puts a string representation of h into ostream o.
Format: [name, { topics0, ..., topicsn }, wealth moneyz, hcp_type*/
std::ostream& operator<<(std::ostream& o, const Health_Care_Provider& h);


class Teaching_Health_Care_Provider : public Health_Care_Provider {

	unsigned fee; //Teaching fee

public:
	/*Initializes member variables.Same rules as Health_Care_Provider Constructor.
	If at least one of the parameters is not matching the requirements, an exception of type
	std::runtime_error must be thrown*/
	Teaching_Health_Care_Provider(unsigned fee, std::string name, const std::set<Medical_Specialty>& topics, unsigned wealth = 500);

	/*If this is eligible for m and p requires treatment in m and p can pay the 
	price x, p is cured from m.Wealth is increased by x.Returns number of cured illnesses*/
	unsigned perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m) override;

	//Returns "Teacher"
	std::string hcp_type() const override; 

	/*If target points to this, knows m already or cannot afford to pay fee, false is returned.
	Otherwise wealth is increased by fee, target pays the fee and receives a license for the topic m and true is returned.*/
	bool teach(Medical_Specialty m, std::shared_ptr<Health_Care_Provider> target);
};


class Smart_Health_Care_Provider : public Health_Care_Provider {
	unsigned fee; //Learning fee

public:
	/*Initializes member variables.Same rules as Health_Care_Provider Constructor.If at
	least one of the parameters is not matching the requirements, an exception of type
	std::runtime_error must be thrown.*/
	Smart_Health_Care_Provider(unsigned fee, std::string name, const std::set<Medical_Specialty>& topics, unsigned wealth = 500);

	//Returns 0.
	unsigned perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m) override;
	
	//Returns "Smart"
	std::string hcp_type() const override;

	//Adds the license to the topics.In addition,the wealth of this is increased by fee
	void receive_license(Medical_Specialty m) override;

};

#endif
