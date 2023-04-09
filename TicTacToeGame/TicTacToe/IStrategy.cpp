#include "IStrategy.h"

IStrategyPtr IStrategy::Produce(EDifficulty type)
{
	switch (type)
	{
	case EDifficulty::Easy:
		return std::make_shared<EasyStrategy>();
		break;

	case EDifficulty::Medium:
		return std::make_shared<MediumStrategy>();
		break;

	case EDifficulty::Hard:
		return std::make_shared<HardStrategy>();
		break;

	/*case EDifficulty::Multiplayer:
		return std::make_shared<MultiplayerStrategy>();
		break;*/
	}

	return {};
}
