#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "sha256.h"

#define DIFFICULTY_LEVEL 4

class BlockChain;
class Block;

class Block {
private:
	typedef std::chrono::system_clock::time_point stamp;
	friend class BlockChain;

	int internalData;
	int index;
	stamp timeStamp;
	std::string data;
	std::string previousHash;
	std::string hash;

	std::string generateHashStatement() const {
		return std::to_string(internalData) + std::to_string(index) + std::to_string(std::chrono::system_clock::to_time_t(timeStamp)) + data + previousHash;
	}

	bool check(const std::string& tempHash) const {
		for (int i = 0; i < DIFFICULTY_LEVEL && i < tempHash.length(); ++i) {
			if (tempHash[i] != '0') return false;
		}

		return true;
	}

public:
	Block(const int index, const std::string& data, const std::string& previousHash)
		: internalData(0), index(index), data(data), previousHash(previousHash) {
		timeStamp = std::chrono::system_clock::now();
		generateHash();
	}

	bool operator==(const Block& other) const {
		return hash == other.hash;
	}

	void generateHash() {
		std::string hashStatement = generateHashStatement();
		hash = sha256(hashStatement);

		while (!check(hash)) {
			++internalData;
			hashStatement = generateHashStatement();
			hash = sha256(hashStatement);
		}
	}
};

class BlockChain {
private:
	int numberOfBlocks;
	std::vector<Block> blocks;
	Block* previousBlock;

	inline void createGenesisBlock() {
		blocks.emplace_back(Block(0, "GEN", "GEN"));
		previousBlock = &blocks[0];
	}

public:
	BlockChain() {
		createGenesisBlock();
	}

	void addBlock(const std::string& data) {
		blocks.emplace_back(Block(previousBlock->index + 1, data, previousBlock->hash));
		previousBlock = &blocks[blocks.size() - 1];

		std::cout << "\nBlock " << previousBlock->index << " Created : " << previousBlock->internalData;
		std::cout << "\nBlock Hash : " << previousBlock->hash << std::endl;
	}

	~BlockChain() {
		//trivial destruction of raw pointer, the object will be automatically be deleted by vector
		previousBlock = nullptr;
		delete previousBlock;
	}
};

int main() {
	std::chrono::system_clock::time_point startPoint = std::chrono::system_clock::now();

	{
		BlockChain chain;
		chain.addBlock("FirstBlock");
		chain.addBlock("SecondBlock");
		chain.addBlock("ThirdBlock");
		chain.addBlock("FourthBlock");
		chain.addBlock("FifthBlock");
	}

	std::cout << "\nExecution Time With Difficulty " << DIFFICULTY_LEVEL << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startPoint).count() << "ms" << std::endl;
	return 0;
}
