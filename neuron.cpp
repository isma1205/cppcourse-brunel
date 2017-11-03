#include <iostream>
#include "neuron.hpp"
#include <cmath>

   
//constructeur
neuron::neuron(double mPot, double Iext, bool type, unsigned int spikesNb, int clock, double tRef)
: mPot_(mPot),Iext_(Iext), type_(type), spikesNb_(spikesNb),  clock_(clock), tRef_(0.0), buffer_(10,0)
{}




// getters

	double neuron::getMPot()
	{
		return mPot_;
	}
	
	double neuron::getSpikesNb()
	{
		return spikesNb_;
	}
	
	std::vector<double> neuron::getTSpike()
	{
		return tSpike_;
	}
	double neuron::getTRef() const
	{
		return tRef_;
	}
	double neuron::getH() const
	{
		return h_;
	}
	std::vector<double> neuron::getTspike() const
	{
		return tSpike_;
	}
	bool neuron::getType()
	{
		return type_;
	}


// setters
	void neuron::setMPot(double mPot)
	{
		mPot_=mPot;
	}
	void neuron::setSpikesNb(unsigned int spikesNb)
	{
		spikesNb_= spikesNb;
	}
	void neuron::setTRef( double dt)
	{
		tRef_= dt;
	}
	void neuron::setBuffer(int delayStep, double weight)
	{
		buffer_[(clock_+delayStep)% buffer_.size()] +=(weight); //give the weight to te buffer
		//debugg
		//std::cout<<buffer_[(clock_+delayStep)% buffer_.size()] << std::endl;
	}
	void neuron::setDisplaySpikes(bool b)
	{
		displaySpikes_ = b;
	}


//update
bool neuron::update(unsigned int i)
{
	bool anySpike (false); // return if there's a spike, false initially
	
	if(mPot_ >= treshold_) // if there is a spike ->
	{
		++ spikesNb_; //increase number of spikes
		tSpike_.push_back(i*h_); //add the time of the new spike
		
		if (displaySpikes_) //if true allow to diplay spikes in terminal
		{
			std::cout<<"! Spike detected ! "<< "At time: "<< i*h_ << std:: endl;
		}
	
		
		refSteps_= (2/h_); // 2ms 
		mPot_= 0.0;
		anySpike = true;
	
	}
	
	if (refSteps_ <=0)  				
	{
		double J = (buffer_[i%buffer_.size()]*J_); // go in the buffer to the place i%buffersize and take the value in it to add it to the membrane potential on next step if empty J=0
		if (type_== true)
		{
			mPot_ = (expn_*mPot_ + Iext_*cste_ + J); // +j if exitatory
		}
		else if (type_ == false)
		{
			mPot_ = (expn_*mPot_ + Iext_*cste_ + J*g_); // +j*g if inhibitory	
		}
	} 

	clock_ = i; // the neurone time is refresh and become the actual number of restant iteration 
	--refSteps_; // the refractory steps decrease 
	buffer_[i%buffer_.size()] = 0;
	
	return anySpike;
	

}

/*
 * new constants c1 &c2:
 recompute exp*V 
 recompute IextR(1-exp)
*/







