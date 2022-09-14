#ifndef CARDSDTO_H
#define CARDSDTO_H
#include <vector>
#include "../../gframe/client_card.h"

namespace ygo {
	class CardsDTO 
	{
	public:
		static bool loaded;
		static std::vector<ClientCard*>* _deck;
		static std::vector<ClientCard*>* _hand;
		static std::vector<ClientCard*>* _mzone;
		//static void SetupCards(std::vector<ClientCard*> deck[2], std::vector<ClientCard*> hand[2], std::vector<ClientCard*> mzone,
		//	std::vector<ClientCard*> szone, std::vector<ClientCard*> grave, std::vector<ClientCard*> remove,
		//	std::vector<ClientCard*> extra, std::vector<ClientCard*> summonable, std::vector<ClientCard*> spsummonable,
		//	std::vector<ClientCard*> activatable, std::vector<ClientCard*> attackable, std::set<ClientCard*> overlay) {
		static void SetupCards(std::vector<ClientCard*> deck[2], std::vector<ClientCard*> hand[2], std::vector<ClientCard*> mzone[2]
			//,
			//std::vector<ClientCard*> szone, std::vector<ClientCard*> grave, std::vector<ClientCard*> remove,
			//std::vector<ClientCard*> extra, std::vector<ClientCard*> summonable, std::vector<ClientCard*> spsummonable,
			//std::vector<ClientCard*> activatable, std::vector<ClientCard*> attackable, std::set<ClientCard*> overlay
		) {
			_deck = deck;
			_hand = hand;
			_mzone = mzone;
			/*_szone = szone;
			_grave = grave;
			_extra = remove;
			_overlay_cards = overlay;
			_summonable_cards = summonable;
			_spsummonable_cards = spsummonable;
			_activatable_cards = activatable;
			_attackable_cards = attackable;*/
			CardsDTO::loaded = true;
		}
		static std::vector<ClientCard*> _szone;
		static std::vector<ClientCard*> _grave;
		static std::vector<ClientCard*> _remove;
		static std::vector<ClientCard*> _extra;
		static std::set<ClientCard*> _overlay_cards;
		static std::vector<ClientCard*> _summonable_cards;
		static std::vector<ClientCard*> _spsummonable_cards;
		static std::vector<ClientCard*> _activatable_cards;
		static std::vector<ClientCard*> _attackable_cards;
	};
}

#endif
