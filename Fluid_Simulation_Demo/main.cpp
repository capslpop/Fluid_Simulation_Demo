#include "main.h"

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <set>
using namespace std;

vector<Particle> particles;
float cellSize = 2;
float interactionDist = 3;
float distSQ = interactionDist * interactionDist;
int hashSize = 7919;
vector<set<int>> hashCollided;
vector<set<int>> naiveCollided;

void hash_combine(size_t& idx, int val) {
	idx ^= val + 0x9e3779b9 + (idx << 6) + (idx >> 2);
}

int int_coords(float a) {
	return floor(a / cellSize);
}

size_t hash_coords(int x, int y, int z) {
	size_t idx = 0;
	hash_combine(idx, x);
	hash_combine(idx, y);
	hash_combine(idx, z);
	return idx % hashSize;
}

size_t hash_particle(const Position& p) {
	return hash_coords(int_coords(p.x), int_coords(p.y), int_coords(p.z));
}

size_t hash_pos(float x, float y, float z) {
	return hash_coords(int_coords(x), int_coords(y), int_coords(z));
}

void physics(Particle& a, Particle& b) {

}

bool pythagLess(Position& a, Position& b) {
	return (a.x - b.x) * (a.x - b.x) + 
		   (a.y - b.y) * (a.y - b.y) + 
		   (a.z - b.z) * (a.z - b.z) < distSQ;
}

void step() {
	vector<int> hashCounts(hashSize + 1, 0);
	for (const Particle& p : particles) {
		hashCounts[hash_particle(p.last)]++;
	}

	int total = 0;
	for (int& i : hashCounts) {
		total += i;
		i = total;
	}

	vector<int> hashedIdx (particles.size(), 0);
	for (int i = 0; i < particles.size(); i++) {
		size_t hashPos = hash_particle(particles[i].last);
		hashedIdx[--hashCounts[hashPos]] = i;
	}

	for (int idx = 0; idx < particles.size(); idx++) {
		Particle& p = particles[idx];
		int minX = int_coords(p.last.x - interactionDist)-1;
		int minY = int_coords(p.last.y - interactionDist)-1;
		int minZ = int_coords(p.last.z - interactionDist)-1;
		int maxX = int_coords(p.last.x + interactionDist)+1;
		int maxY = int_coords(p.last.y + interactionDist)+1;
		int maxZ = int_coords(p.last.z + interactionDist)+1;

		for (int x = minX; x < maxX; x++) {
			for (int y = minY; y < maxY; y++) {
				for (int z = minZ; z < maxZ; z++) {
					size_t cell = hash_coords(x, y, z);
					int start = hashCounts[cell];
					int end = hashCounts[cell + 1];
					int other;
					for (; start < end; start++) {
						other = hashedIdx[start];
						if (other == idx) continue;
						if (pythagLess(p.last, particles[other].last)) {
							hashCollided[idx].insert(other);
						}
					}
				}
			}
		}
	}
}

void stepNaive() {
	for (int i = 0; i < particles.size(); i++) {
		Position& p = particles[i].last;
		for (int j = 0; j < particles.size(); j++) {
			if (i == j) continue;
			if (pythagLess(p, particles[j].last)) {
				naiveCollided[i].insert(j);
			}
		}
	}
}

void test() {
	int COUNT = 100000;
	int RANGE = 100;
	mt19937 eng(time(NULL));
	uniform_real_distribution<float> rng(0.0, RANGE);
	hashCollided = vector<set<int>>(COUNT);
	naiveCollided = vector<set<int>>(COUNT);

	for (int i = 0; i < COUNT; i++) {
		particles.push_back(Particle (Position {rng(eng), rng(eng), rng(eng)}));
	}

	auto hashStart = chrono::steady_clock::now();
	step();
	auto hashEnd = chrono::steady_clock::now();
	auto hashTime = chrono::duration_cast<chrono::milliseconds>(hashEnd - hashStart);

	auto naiveStart = chrono::steady_clock::now();
	stepNaive();
	auto naiveEnd = chrono::steady_clock::now();
	auto naiveTime = chrono::duration_cast<chrono::milliseconds>(naiveEnd - naiveStart);

	cout << "Hash time: " << hashTime << " | Naive time: " << naiveTime << endl;

	int count = 0;
	for (int i = 0; i < COUNT; i++) {
		if (hashCollided[i] != naiveCollided[i]) {
			count++;
			/*vector<int> difference;
			set_symmetric_difference(hashCollided[i].begin(), hashCollided[i].end(), naiveCollided[i].begin(), naiveCollided[i].end(), back_inserter(difference));

			for (auto z : difference) {
				cout << z << " ";
			}
			cout << endl;*/
		}
	}

	cout << "Errors: " << count << endl;
}

int main() {
	test();
	return 0;
}
