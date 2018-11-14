#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
//next solve
int result(float W, float X) {
	if (X > W) {
		return 1;
	}
	else {
		return 0;
	}
}
//train
float calculated_answer(float W, float X) {
	//cout << "W= " << W << "--- X=" << X <<"\n";
	//cout << W*X << "\n";
	return W * X;
}
float deltaW(float learnRate, int answer, float X, float W) {
	//cout << (learnRate*(answer - result(W, X))*X) << "\n";
	return (learnRate*(answer - calculated_answer(W, X))*X);
}
float modifyW(float learnRate, int answer, float X, float W) {
	return W + deltaW(learnRate, answer, X, W);
}
//train methods above

void print(std::vector<float> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ' << "\n";
	}
	cout << "\n" << input.size() << "\n";
}

int main(int argc, char const *argv[])
{
	float N = .2;
	srand(time(NULL));
	float W1 = ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
	float W2 = ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
	string dimensions;
	string sizeSet;
	string nSets;
	getline(cin, dimensions);
	getline(cin, sizeSet);
	getline(cin, nSets);
	int dimen = stoi(dimensions);
	int trainSize = stoi(sizeSet);
	int numSets = stoi(nSets);
	if (numSets == 0) {
		cout << "no solution found";
		return 0;
	}
	//cout << dimen << "\n" << trainSize << "\n" << numSets << "\n";

	string buffer;

	vector<float> train;
	float test;
	//parse trainset
	for (int i = 0; i < trainSize; i++) {
		//cout << "hello there/n";
		getline(cin, buffer);
		//cout << buffer << "\n";
		buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
		
		for (int x = 0; x < (dimen+1); x++) {
			//cout << buffer.substr(0, buffer.find(",")) << "\n";
			//cout << "hi" << "\n";
			//cout << buffer << "\n";
			train.push_back(stof(buffer.substr(0, buffer.find(","))));
			buffer.erase(0, (buffer.find(",") + 1));
		}
		
	}
	//print(train);
	//start train
	bool flag = true;
	int ntrainSets = 100000;
	while (true) {
		
		for (int i = 0; i < trainSize; i++) {
			if (result(W1, train[i]) != train[i+2]) {
				//cout << "R1=" << result(W1, train[i]) << "-----R2=" << result(W1, train[i]) << "\n";
				W1 = modifyW(N, train[i + 2], train[i], W1);
				flag = false;
			}
			if (result(W2, train[i + 1]) != train[i+2]) {
				W2 = modifyW(N, train[i + 2], train[i + 1], W2);
				flag = false;
			}
			i=i+2;
			//cout << "W1=" << W1 << "-----W2=" << W2 << "\n"; 
		}
		ntrainSets--;
		if (flag) {
			break;
		}
		else {
			flag = true;
		}
		if (ntrainSets == 0) {
			cout << "no solution found";
			return 0;
		}
	}
	vector<float> trial;
	for(int i=0; i<numSets; i++){
		getline(cin, buffer);
		//cout << buffer << "\n";
		buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
		
		for (int x = 0; x < (dimen); x++) {
			//cout << buffer.substr(0, buffer.find(",")) << "\n";
			//cout << "hi" << "\n";
			//cout << buffer << "\n";
			trial.push_back(stof(buffer.substr(0, buffer.find(","))));
			buffer.erase(0, (buffer.find(",") + 1));
		}
	}
	for(int i=0; i<numSets; i++){
		//cout << "pass "<<i<<"\n";
		if(result(W1,trial[i]==1 && result(W2,trial[i+1]==1))){
			cout<<"1\n";
		}else{
			cout<<"0\n";
		}
		i++;
	}
	


	/*
	//train until all trainning answers are correct
	string hello = "testing , this mehtod, hello";
	vector<string> vector;
	std::vector<int> pos;
	pos.push_back( hello.find(","));
	vector.push_back(hello.substr(0, 8));
	hello.erase(0, 9);
	vector.push_back(hello.substr(0, 12));
	pos.push_back(hello.find(","));
    cout << "Hello World!\n"; 
	*/
}