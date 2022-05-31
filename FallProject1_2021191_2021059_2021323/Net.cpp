
#include "Net.h"


//random weights
double randW()
{
	srand(time(0));
	return rand() / double(RAND_MAX);          //0-1
}


//sigmoid function
double sigmoid(double x) {
	double result;
	result = 1 / (1 + exp(-x));

	return result;
}

//-----------------------------connection---------------------------------------

//constructor for connection
Connection::Connection()
{
	weight = rand() / double(RAND_MAX);
}



//-----------------------------neuron---------------------------------------

double Neuron::eta = 0.15;		// [0 -  1] overall net training rate
double Neuron::alpha = 0.5;		// multiplier of last weight change (momentum)

double Neuron::getOutputVal(void)const { return m_outputVal; }

void Neuron::setOutputVal(double val) { m_outputVal = val; }

void Neuron::updateInputWeights(Layer& prevLayer) {

	//the weights to be updated are in the conncetion container 
	// in the neurons in the preceding layer

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		Neuron& neuron = prevLayer[n]; // the other neuron in the prev layer which we are updatign
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			//indivula input, magnified by the gradient and train rate
			eta
			* neuron.getOutputVal()
			* m_gradient
			//Also add momentum = a fraction of the prev delta weight
			+ alpha
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
		//store weights that go  from it to all other to which it feeds
		//change in wieght also need to be stored we need to doubles so we make a struct connection which stores weight and change in weight

	}
}

double Neuron::sumDOW(const Layer& nextLayer) {

	double sum = 0.0;

	//Sum of our contributions of the errors at the nodes we feed
	for (unsigned n = 0; n < nextLayer.size(); ++n) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal) {
	//supposed to look at the difference btw target values that its supposed to have and
	//and the actual it has
	//then it multiplies it that diff by the derivative of its output val

	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{

	return sigmoid(sigmoid(x));		//[0 - 1]
}

double Neuron::transferFunctionDerivative(double x)
{
	double res = ((sigmoid(x) * (1 - sigmoid(x))) * (1 - (sigmoid(x) * (1 - sigmoid(x)))));
	return res;
}

void Neuron::feedForward(const Layer& prevLayer) {

	double sum = 0.0;
	//sum the privous layer's outputs (which are our  inputs)
	//inlcude the bais node from the previous layer

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() *
			prevLayer[n].m_outputWeights[m_myIndex].weight;

	}

	m_outputVal = Neuron::transferFunction(sum);

}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	// c for connections
	// changed t0 c <= numOutputs from <
	for (unsigned c = 0; c <= numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randW();//assigning weights
	}

	m_myIndex = myIndex;
}



//-----------------------------net---------------------------------------

void Net::getResults(vector <double>& resultVals) const {
	/// <summary>
	/// clears out  the container then loops thru all the neuron in th eouptut layer moves their val to the
	/// resultsVals
	/// </summary>
	/// <param name="resultVals"></param>
	resultVals.clear();
	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}

}

void Net::backProp(const vector<double>& targetVals)
{
	//calculate overall net error (RMS of ouput errors)

	Layer& outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1;// get avergae error squared
	m_error = sqrt(m_error); //RMS

	// implement a recent Average measurement;
	m_recentAverageError =
		(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
		/ (m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients

	for (unsigned n = 0; n < outputLayer.size() - 1;n++)
		outputLayer[n].calcOutputGradients(targetVals[n]);

	// Calculate gradients on hidden layers
	// initialize it to right most hidden layer
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer& hiddenLayer = m_layers[layerNum];
		Layer& nextLayer = m_layers[layerNum + 1];
		for (unsigned n = 0; n < hiddenLayer.size(); ++n)
			hiddenLayer[n].calcHiddenGradients(nextLayer);
	}
	// For all layers from outputs to first hidden layer
	// update connection weights
	// no need to include input layer
	for (unsigned layerNum = m_layers.size() - 1;layerNum > 0;--layerNum)
	{
		Layer& layer = m_layers[layerNum]; //reference to current num
		Layer& prevLayer = m_layers[layerNum - 1];  //reference to prev layer


		// for each neuron we index  indivual to udpate its input weight
		for (unsigned n = 0; n < layer.size() - 1; ++n)
			layer[n].updateInputWeights(prevLayer);
	}
}

void Net::feedForward(const vector<double>& inputVals) {

	//assert that no of inputs=layer size
	assert(inputVals.size() == m_layers[0].size() - 1);
	//gives us number of neurons and we subtract them

	//Assign (latch) the input values into the input neurons
	//i for input
	for (unsigned i = 0; i < inputVals.size(); ++i)
		m_layers[0][i].setOutputVal(inputVals[i]);	//0th layer and ith neuron

	//forward propgate
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
	{
		Layer& prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
			m_layers[layerNum][n].feedForward(prevLayer);
	}
}

Net::Net(const vector<unsigned>& topology) {

	m_error = 0.0;
	m_recentAverageError = 0.0;
	m_recentAverageSmoothingFactor = 100.0;

	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {

		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 1 : topology[layerNum + 1];
		//topology.size()-1 is for the last layer if its that then numOutputs zero else
		//otherwise its whatever is in the next layer
		//we have a new layer, now fill it with ith neurons, and 
		//add  abias neuron to the layer:
		//<= because we want that bias neuron

		//cout << "numOutputs is : " << numOutputs << endl;
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));

			//cout << "neuron num: " << neuronNum << endl;
		}

		//cout << "layer num:  " << layerNum << "\n";
	}

	/// force the bias to constant 1.0 
	m_layers.back().back().setOutputVal(1.0);

}

void board(char square[])
{
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

	cout << "     |     |     " << endl << endl;
}


int checkwin(char square[])
{
	if (square[1] == square[2] && square[2] == square[3])

		return 1;
	else if (square[4] == square[5] && square[5] == square[6])

		return 1;
	else if (square[7] == square[8] && square[8] == square[9])

		return 1;
	else if (square[1] == square[4] && square[4] == square[7])

		return 1;
	else if (square[2] == square[5] && square[5] == square[8])

		return 1;
	else if (square[3] == square[6] && square[6] == square[9])

		return 1;
	else if (square[1] == square[5] && square[5] == square[9])

		return 1;
	else if (square[3] == square[5] && square[5] == square[7])

		return 1;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3'
		&& square[4] != '4' && square[5] != '5' && square[6] != '6'
		&& square[7] != '7' && square[8] != '8' && square[9] != '9')

		return 0;
	else
		return -1;
}


void tictactoeWithAi()
{

	vector <unsigned> topology;
	topology.push_back(9);
	topology.push_back(3);
	topology.push_back(1);

	Net myNet((topology)); // needs to know number of layers and number of  neurons per layer (topology)

	//feeding inputs

	vector <double> inputVals;

	// for training to know what the real output were supposed to be
	//pass it array of target values
	vector <double> targetVals;
	vector <double> resultVals;
	vector <double> reset;
	ifstream inputData;
	//inputData.ignore();
	inputData.open("tic-tac-toe.txt");

	for (int i = 0; i < 958; i++)
	{

		string c;
		inputVals.clear();
		targetVals.clear();
		inputData >> c;
		for (int i = 0; c[i] != '\0'; i++) {

			if (c[i] == 'x') {
				inputVals.push_back(0.8);
			}
			if (c[i] == 'o' && i < 18) {
				inputVals.push_back(0.5);
			}
			if (c[i] == 'b') {
				inputVals.push_back(0.01);
			}

			if (c[i] == 'p') {
				targetVals.push_back(1);
			}
			if (c[i] == 'n') {
				targetVals.push_back(0);
			}
		}


		myNet.feedForward(inputVals);
		myNet.backProp(targetVals);



		//to use it normally after it has been trained

		myNet.getResults(resultVals);

	}

	cout << "\nNeural Network has been successfully trained";
	cout << "\nPress any key to continue";
	getchar();


	inputVals.clear();
	for (int i = 0; i < 9; i++)
		inputVals.push_back(0.01);

	char square[10] = { 'o','1','2','3','4','5','6','7','8','9' };
	int player = 1, i, choice;

	char mark;
	do
	{
		board(square);
		if (player % 2 == 1)
			player = 1;
		else
			player = 2;
		vector<double> rests;
		// Ai
		if (player == 2)
		{
			mark = 'X';
			int turn = 1;
			int placed = 0;
			while (placed == 0)
			{
				double bestoptn = 10;
				int bestPos = 0;

				for (int j = 0; j < 9; j++)
				{
					if (inputVals[j] == 0.01)		//blank
					{
						inputVals[j] = 0.8;		// value of x
						myNet.feedForward(inputVals);
						myNet.getResults(resultVals);

						if (resultVals[0] < bestoptn)
						{
							bestoptn = resultVals[0];
							bestPos = j;
						}
						inputVals[j] = 0.01;
					}
				}
				choice = bestPos + 1;
				if (choice == 1 && square[1] == '1') {
					square[1] = mark;
					inputVals[0] = 0.8;
					placed = 1;
				}
				else if (choice == 2 && square[2] == '2') {

					square[2] = mark;
					inputVals[1] = 0.8;
					placed = 1;
				}
				else if (choice == 3 && square[3] == '3') {

					square[3] = mark;
					inputVals[2] = 0.8;
					placed = 1;
				}
				else if (choice == 4 && square[4] == '4') {

					placed = 1;
					square[4] = mark;
					inputVals[3] = 0.8;

				}
				else if (choice == 5 && square[5] == '5') {

					square[5] = mark;
					placed = 1;
					inputVals[4] = 0.8;

				}
				else if (choice == 6 && square[6] == '6') {

					square[6] = mark;
					placed = 1;
					inputVals[5] = 0.8;

				}
				else if (choice == 7 && square[7] == '7') {

					square[7] = mark;
					placed = 1;
					inputVals[6] = 0.8;

				}
				else if (choice == 8 && square[8] == '8') {

					square[8] = mark;
					placed = 1;
					inputVals[7] = 0.8;

				}
				else if (choice == 9 && square[9] == '9') {

					square[9] = mark;
					placed = 1;
					inputVals[8] = 0.8;

				}

			}
			cout << "\nAI placed at pos: " << choice;
			i = checkwin(square);
			player++;
			getchar();
			board(square);
		}

		// player 
		else if (player == 1)
		{
			cout << "Player!\nEnter a number\n>>\t";
			cin >> choice;
			mark = 'O';

			if (choice == 1 && square[1] == '1')
			{
				square[1] = mark;
				inputVals[0] = 0.5;
			}
			else if (choice == 2 && square[2] == '2')
			{
				square[2] = mark;
				inputVals[1] = 0.5;

			}
			else if (choice == 3 && square[3] == '3')
			{
				square[3] = mark;
				inputVals[2] = 0.5;

			}
			else if (choice == 4 && square[4] == '4')
			{
				square[4] = mark;
				inputVals[3] = 0.5;

			}
			else if (choice == 5 && square[5] == '5')
			{
				square[5] = mark;
				inputVals[4] = 0.5;

			}
			else if (choice == 6 && square[6] == '6')
			{
				square[6] = mark;
				inputVals[5] = 0.5;

			}
			else if (choice == 7 && square[7] == '7')
			{
				square[7] = mark;
				inputVals[6] = 0.5;

			}
			else if (choice == 8 && square[8] == '8')
			{
				square[8] = mark;
				inputVals[7] = 0.5;

			}
			else if (choice == 9 && square[9] == '9')
			{
				square[9] = mark;
				inputVals[8] = 0.5;

			}
			else
			{
				cout << "Invalid move ";

				player--;
				getchar();
			}
			i = checkwin(square);

			player++;
		}
	} while (i == -1);
	board(square);
	if (i == 1)
	{
		--player;
		if (player == 2)
			cout << "\n AI Wins!";
		else
			cout << "\n Congratulations! \nPlayer wins! ";
	}
	else
		cout << "  Oops!\nGame draw";

	getchar();

}