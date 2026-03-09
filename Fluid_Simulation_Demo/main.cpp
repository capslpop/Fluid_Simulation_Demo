#include "main.h"
#include "Camera/Camera.hpp"

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
	//test();

	// ----------------- Window -----------------------------
	Window window(800, 600, "3D Points");


	// ----------------- Camera -----------------------------
	Camera camera(vec3(0.0, 0.0, 3.0), (float)800 / (float)600);

	// ----------------- Uniform Buffer -----------------------------
	mat4 projection_matrix = camera.getCameraProjMat();
	mat4 view_matrix = camera.getCameraViewMat();

	mat4 model_matrix = mat4(1.0f);

	struct UniformData {
		mat4 projection;
		mat4 view;
		mat4 model;
	};

	UniformData uniform_data{projection_matrix, view_matrix, model_matrix};

	UniformBufferParams uniform_params;
	uniform_params.data = &uniform_data;
	uniform_params.size = sizeof(UniformData);
	uniform_params.buffer_usage = BUFFER_USAGE::DYNAMIC_DRAW;

	UniformBuffer uniform_buffer(uniform_params);


	// ----------------- Vertex Buffer -----------------------------
	struct Vertex {
		vec3 position;
	};

	Attributes vertex_attributes[] = {
		{ATTRIBUTE::FLOAT, 3},	// postion
	};

	// Generate grid of points
	std::vector<Vertex> vertex_data;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				vertex_data.push_back({
					vec3(x - 1.0f, y - 1.0f, z - 1.0f)
					});
			}
		}
	}

	VertexBuffer vertex_buffer({
		.attributes = vertex_attributes,
		.attributes_count = sizeof(vertex_attributes) / sizeof(Attributes),
		.data = vertex_data.data(),
		.count = (uint)vertex_data.size(),
		});



	// ----------------- Render Pass -----------------------------
	RenderPass render_pass_main("Shaders/fluid_simulation.glsl");



	// ----------------- Descriptor Set -----------------------------
	Descriptor descriptors[] = {
		{DESCRIPTOR_TYPE::VERTEX_BUFFER_IN, (void*)&vertex_buffer, nullptr},
		{DESCRIPTOR_TYPE::UNIFORM_BUFFER, (void*)&uniform_buffer, nullptr},
	};

	DescriptorSetBuffer descriptor_set({
		.descriptors = descriptors,
		.count = sizeof(descriptors) / sizeof(Descriptor),
		});



	// ----------------- Construct Frame Graph -----------------------------
	FrameGraph graph(window);

	graph.addNode(NodeUniformCopy{
		.uniform_buffer = &uniform_buffer,
		.start = 0,
		.size = sizeof(UniformData),
		.data = &uniform_data,
		});

	graph.addNode({
		.color = vec4(0.05, 0.06, 0.05, 1.0),
		});

	// Render the geometry
	graph.addNode({
		.render_pass = &render_pass_main,
		.render_states = {
			.render_type = RENDER_TYPE::POINTS,
			.enable_point_size = true,
		},
		.descriptor_set = &descriptor_set,
		});

	graph.addNodeDisplay(); // Finally we display the frame

	graph.build();

	while (!window.isClosed()) {
		model_matrix = rotate(model_matrix, radians(0.05f), vec3(1.0, 0.0, 0.0));
		model_matrix = rotate(model_matrix, radians(0.05f), vec3(0.0, 1.0, 0.0));
		uniform_data.model = model_matrix;

		graph.run();
	}

	return 0;
}
