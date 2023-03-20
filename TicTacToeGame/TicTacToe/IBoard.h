#pragma once
#include<utility>
#include<memory>

using IBoardPtr = std::shared_ptr<class IBoard>;

class IBoard
{
public:
	static IBoardPtr Produce();

	virtual int GetSize() const = 0;
	virtual void SetValue(char value, int i, int j) = 0;
	virtual char GetValue(int i,int j) const = 0;

	~IBoard() = default;;
};

