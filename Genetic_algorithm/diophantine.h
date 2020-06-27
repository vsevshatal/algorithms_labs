#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#define MAXPOP	200

struct gene {
	int alleles[5];
	int fitness;
	float likelihood;

	// Test for equality.
	int operator==(gene gn) {
		for (int i = 0; i < 5; i++) {
			if (gn.alleles[i] != alleles[i]) return false;
		}

		return true;
	}
};

class CDiophantine {
public:
	CDiophantine(int, int, int, int, int, int);
	int Solve();

	gene GetGene(int i) { return population[i]; }

protected:
	int a, b, c, d, e;
	int result;
	gene population[MAXPOP];

	int Fitness(gene &);
	void GenerateLikelihoods();
	float MultInv();
	int CreateFitnesses();
	void CreateNewPopulation();
	int GetIndex(float val);
	void Mutate(int parent1, int parent2);


	gene Breed(int p1, int p2);

};

CDiophantine::CDiophantine(int u, int w, int x, int y, int z,int res) : a(u), b(w), c(x), d(y), e(z), result(res) {}

int CDiophantine::Solve() {
	int fitness = -1;

	
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAXPOP; i++) {
		for (int j = 0; j < 5; j++) {
			population[i].alleles[j] = rand() % (result*2 + 1) - 40;
		}
	}

	if (fitness = CreateFitnesses()) {
		return fitness;
	}

	int iterations = 0;
	while (fitness != 0 || iterations < 200) {
		cout << "Iteration: " << iterations << endl;
		GenerateLikelihoods();
		CreateNewPopulation();

		if (fitness = CreateFitnesses()) {
			return fitness;
		}

		iterations++;
	}

	return -1;
}

int CDiophantine::Fitness(gene &gn) {
	int total = (a*gn.alleles[0] * b*gn.alleles[1] * c*gn.alleles[2]*gn.alleles[2] * d*gn.alleles[3]) + (d*gn.alleles[3]) + (b*gn.alleles[1]*gn.alleles[1] * c*gn.alleles[2] * e*gn.alleles[4]) + (a*gn.alleles[0]
		* b*gn.alleles[1] * c*gn.alleles[2] * e*gn.alleles[4]) + (a*gn.alleles[0] * b*gn.alleles[1] * c*gn.alleles[2] * e*gn.alleles[4]);
	return gn.fitness = abs(total - result);
}

int CDiophantine::CreateFitnesses() {
	float avgfit = 0;
	int fitness = 0;
	for (int i = 0; i < MAXPOP; i++) {
		fitness = Fitness(population[i]);
		avgfit += fitness;
		if (fitness == 0) {
			return i;
		}
	}

	return 0;
}

float CDiophantine::MultInv() {
	float sum = 0;

	for (int i = 0; i < MAXPOP; i++) {
		sum += 1 / ((float)population[i].fitness);
	}

	return sum;
}

void CDiophantine::GenerateLikelihoods() {
	float multinv = MultInv();

	float last = 0;
	for (int i = 0; i < MAXPOP; i++) {
		population[i].likelihood = last = last + ((1 / ((float)population[i].fitness) / multinv) * 100);
	}
}

int CDiophantine::GetIndex(float val) {
	float last = 0;
	for (int i = 0; i < MAXPOP; i++) {
		if (last <= val && val <= population[i].likelihood) return i;
		else last = population[i].likelihood;
	}

	return 5;
}

 void CDiophantine::Mutate(int parent1, int parent2) {
	 if (rand() % 10 == 1) {
		 gene temp = population[parent1];
		 population[parent1] = population[parent2];
		 population[parent2] = temp;
	 }

}

gene CDiophantine::Breed(int p1, int p2) {
	int crossover = rand() % 3 + 1;
	int first = rand() % 100;

	gene child = population[p1];

	int initial = 0, final = 3;
	if (first < 50) initial = crossover;
	else final = crossover + 1;

	for (int i = initial; i < final; i++) {
		child.alleles[i] = population[p2].alleles[i];
		if (rand() % 101 < 5) child.alleles[i] = rand() % (result + 1);
	}

	return child;
}

void CDiophantine::CreateNewPopulation() {
	gene temppop[MAXPOP];

	for (int i = 0; i < MAXPOP; i++) {
		int parent1 = 0, parent2 = 0, iterations = 0;
		while (parent1 == parent2 || population[parent1] == population[parent2]) {
			parent1 = GetIndex((float)(rand() % 101));
			parent2 = GetIndex((float)(rand() % 101));
			Mutate(parent1, parent2);
			if (++iterations > 100) break;
		}

		temppop[i] = Breed(parent1, parent2);
	}
	
		for (int i = 0; i < MAXPOP; i++) {
			if (temppop[i].fitness > 30) {
				population[i] = temppop[i];
			}
		}
}

