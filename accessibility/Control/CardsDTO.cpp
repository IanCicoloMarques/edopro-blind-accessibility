#include "CardsDTO.h"
namespace ygo {
	bool CardsDTO::loaded = false;
	std::vector<ClientCard*>* CardsDTO::_deck = nullptr;
	std::vector<ClientCard*>* CardsDTO::_hand = nullptr;
	std::vector<ClientCard*>* CardsDTO::_mzone = nullptr;
}
