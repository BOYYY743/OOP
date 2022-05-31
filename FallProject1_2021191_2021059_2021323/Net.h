#ifndef Net_h
#define Net_h

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <cassert>
#include <cmath>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

class Neuron;

typedef vector<Neuron> Layer;

class Connection
{
public:

	double weight, deltaWeight;

	Connection();
};


class Neuron
{
public:
	void updateInputWeights(Layer& prevLayer);
	void calcHiddenGradients(const Layer& nextLayer);
	void calcOutputGradients(double targetVal);
	double getOutputVal(void)const;
	void setOutputVal(double val);
	void feedForward(const Layer& prevLayer);
	Neuron(unsigned numOutputs, unsigned myIndex);

private:
	static double eta;
	static double alpha;


	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	unsigned m_myIndex;
	double sumDOW(const Layer& nextLayer);
	double m_outputVal;
	double m_gradient;
	vector<Connection> m_outputWeights;

};


class Net
{
public:

	Net(const vector<unsigned>& topology);

	void feedForward(const vector<double>& inputVals);
	void backProp(const vector<double>& targetVals);
	void getResults(vector <double>& resultVals) const;


private:
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
	double m_error;
	vector <Layer> m_layers; //m_layers []layernum][neuronnum]
};


void board(char square[]);
int checkwin(char square[]);
void tictactoeWithAi();

#endif // !Net_h