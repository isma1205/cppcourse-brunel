
#ifndef CORTEX_H
#define CORTEX_H
 
#include <vector>
#include "neuron.hpp"

class cortex: public neuron
{
	private:
	/**@brief :The vector containing pointer on neurons*/
	std::vector<neuron*> neurons_; 			
	/**@brief :The number of neurons in the cortex*/		
	size_t neuronsNbr_; 	
	/**@brief :Delay in [ms]*/						
	const double D_ = 1.5; 	
	/**@brief :Step of the simulation in [ms]*/					
	const double h_= 0.1; 
	/**@brief :delay in step*/							
	const int stepDelay_ = (D_/h_);	
	/**@brief :double vector for connexions between neurons*/				
	std::vector<std::vector<double> > connexions_; 
		


	
	public:
//constructor:
	cortex();										 /**<The Constructor for cortex initialized with an empty vector neurons_*/
	
// methods:
	/**
	 @brief : Call the buffer's setter of the neuron n to add on its buffer the strength of the received current
	 @param n: a neuron
	 @param weight: the random strength of the connection
	 */
	void receiveSpike(neuron* n, unsigned int i, double weight);
	
	/**
	 @brief : call update function of all neurons and call the function receiveSpike if the neurons j and k are connected
	 @param nit : the number of iteration in the all simulation
	 */
	void updates(unsigned int nit, bool percent);
	
	/**
	 @brief : place the pointer on a neuron in the vector neurons_
	 @param pointer : the pointer on a neuron
	 */
	void initiateNeurons(neuron* pointer);
	
		/**
	 @brief : create a random double number between a & b
	 @param a: borne a of the interval
	 @param b: borne b of the interval
	 @return : the random number
	 */
	double randm(double a, double b); //return a random double number beetween a & b
	
	
		/**
	 @brief : create connections between all neurons 10% of the connections are with excitatory neurons and the same for inhibitory neurons
	 @param ne : number of excitatory neurons
	 @param ni: number of inhibitory neurons 
	 */
	void createConnexions(unsigned int ne, unsigned int ni);
	
	/**
	@brief : work the same as createConnexions but count the connections, allow to do not slow down my program if count isn't needed
	@param ne : number of excitatory neurons
	@param ni: number of inhibitory neurons 
	@return vector<int>: the number of connections with vector[0] and with inhibitory is vector[1]
	*/
	std::vector<int> createCountConnexions(unsigned int ne, unsigned int ni);

	//getters
	
	/**
	 @brief : return the step h of the simulation
	 @return : the step h of the simulation
	 */
	double getH() const;
	
	/**
	 @brief : return the size of neurons_
	 @return : neurons_.size()
	 */
	size_t getSize() const;
	
	/**
	 @param int i:index of the neuron
	 @brief : return a pointer on a neuron (the *neurons_[i])
	 @return : the step h of the simulation
	 */ 
	neuron* getNeuronsi(int i); 
	
	/**
	 @brief : return the vector of connexions_
	 @return : connexions_
	 */ 
	std::vector<std::vector<double> > getConnexions();
	
	/**
	 @brief : return the vector of pointer on neuron neurons_
	 @return neurons_: the vector of neurons
	 */
	
	std::vector<neuron*> getNeurons();
	/**
	 @brief : Store in a file (named membrane potentiel) the membrane potential of all neurons.
	 */ 
	
	//setter 
	/**
	 @brief : could be useful for tests, set one connection between only 2 neurons in one way, with the weight we choose
	 @param unsigned int i: the ID of the donor neuron
	 @param unsigned int j: the ID of the receiver neuron
	 @param double weight: stength of the connection between i and j
	 */ 
	void setOneConnexions2neurons(unsigned int i, unsigned int j, double weight); 
	 
	// file storing
	/**
	 @brief : store spikes of each neurons in a file 
	 @param std::ofstream& file1: the file to store spikes
	 */
	void storeInFile(std::ofstream& file1);
	
	//destructeur
	~cortex(); 															///<destructor

	
};

#endif


