#ifndef CLIENT_FIELD_H
#define CLIENT_FIELD_H

#include <vector>
#include <set>
#include <map>
#include <IEventReceiver.h>
#include <vector3d.h>
#include <vector2d.h>

namespace ygo {

class ClientCard;

struct ChainInfo {
	irr::core::vector3df chain_pos;
	ClientCard* chain_card;
	uint32_t code;
	uint64_t desc;
	uint8_t controler;
	uint8_t location;
	uint32_t sequence;
	bool solved;
	std::set<ClientCard*> target;
	void UpdateDrawCoordinates();
};

//! Information on a joystick, returned from @ref irr::IrrlichtDevice::activateJoysticks()
struct AccessibilityFieldFocus
{
	/** A identifier to tell where the accessibility reader will look at in the field*/
	enum FieldLookerLocId
	{
		PLAYER_HAND = 0,
		PLAYER_MONSTERS = 1007,
		PLAYER_SPELLS = 1,
		PLAYER_GRAVEYARD = 2,
		PLAYER_EXTRA_DECK = 3,
		PLAYER_DECK = 4,
		PLAYER_BANNED_CARDS = 5,
		PLAYER_FIELD = 6,
		PLAYER_PENDULUM_ZONE = 7,
		PLAYER_SUMMONABLE_MONSTERS = 8,
		PLAYER_SPECIAL_SUMMONABLE_MONSTERS = 9,
		PLAYER_ACTIVABLE_CARDS = 10,
		PLAYER_SETTABLE_CARDS = 11,
		ATTACKABLE_CARDS = 12,
		SELECTABLE_CARDS = 13,
		SELECTED_CARDS = 14,
		MUST_SELECT_CARDS = 15,
		ENEMY_PLAYER_HAND = 0,
		ENEMY_PLAYER_MONSTERS = 0,
		ENEMY_PLAYER_SPELLS = 0,
		ENEMY_PLAYER_GRAVEYARD = 0,
		ENEMY_PLAYER_EXTRA_DECK = 0,
		ENEMY_PLAYER_DECK = 0,
		ENEMY_PLAYER_BANNED_CARDS = 0,
		ENEMY_PLAYER_FIELD = 0,
		ENEMY_PLAYER_PENDULUM_ZONE = 0,
		LINK_ZONE = 0,
	};

	enum DisplayedField
	{
		PLAYER = 0,
		ENEMY_PLAYER = 1
	};

	enum DisplayedCards
	{
		NO_DISPLAY = 0,
		DISPLAY_HAND = 1,
		DISPLAY_FIELD = 2

	};

	enum UseType
	{
		NO_USE = 0,
		NORMAL_SUMMON = 1,
		SPECIAL_SUMMON = 2,
		SPECIAL_SUMMON_DEFENSE = 3,
		SET_MONSTER = 4,
		SET_SPELL = 5,
		MONSTER_ATTACK = 6,
		EFFECT = 7,
		SELECT_CARD = 8,
		MONSTER_ATTACK_SELECT = 9,
		ACTIVATE = 10,
		SET_CARD = 11,
		CHANGE_MODE = 12
	};

	enum CardType
	{
		NO_CARD_TYPE = 0,
		MONSTER = 1,
		SPELL = 2,
		ACTIVABLE_EFFECT = 3,
		SELECTABLE = 4,
		LINK = 5
	};

	enum BattleStep
	{
		MP1 = 0,
		BP = 1,
		MP2 = 2,
		ED = 3
	};

	enum Scroll
	{
		NO_SCROLL = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};
};

class ClientField: public irr::IEventReceiver {
public:
	std::vector<ClientCard*> deck[2];
	std::vector<ClientCard*> hand[2];
	std::vector<ClientCard*> mzone[2];
	std::vector<ClientCard*> szone[2];
	std::vector<ClientCard*> grave[2];
	std::vector<ClientCard*> remove[2];
	std::vector<ClientCard*> extra[2];
	std::vector<ClientCard*> limbo_temp;
	std::set<ClientCard*> overlay_cards;
	std::vector<ClientCard*> summonable_cards;
	std::vector<ClientCard*> spsummonable_cards;
	std::vector<ClientCard*> msetable_cards;
	std::vector<ClientCard*> ssetable_cards;
	std::vector<ClientCard*> reposable_cards;
	std::vector<ClientCard*> activatable_cards;
	std::vector<ClientCard*> attackable_cards;
	std::vector<ClientCard*> conti_cards;
	ClientCard* skills[2];
	std::vector<std::pair<uint64_t, uint8_t>> activatable_descs;
	std::vector<uint64_t> select_options;
	std::vector<ChainInfo> chains;
	int extra_p_count[2];

	size_t selected_option;
	ClientCard* attacker;
	ClientCard* attack_target;
	uint32_t disabled_field;
	uint32_t selectable_field;
	uint32_t selected_field;
	uint32_t select_min;
	uint32_t select_max;
	uint32_t must_select_count;
	uint32_t select_sumval;
	uint8_t select_mode;
	bool select_cancelable;
	bool select_ready;
	uint8_t announce_count;
	uint16_t select_counter_count;
	uint16_t select_counter_type;
	std::vector<ClientCard*> selectable_cards;
	std::vector<ClientCard*> selected_cards;
	std::vector<ClientCard*> must_select_cards;
	std::set<ClientCard*> selectsum_cards;
	std::vector<ClientCard*> selectsum_all;
	std::vector<uint64_t> declare_opcodes;
	std::vector<ClientCard*> display_cards;
	std::vector<int> sort_list;
	std::map<uint64_t, int> player_desc_hints[2];
	bool grave_act[2];
	bool remove_act[2];
	bool deck_act[2];
	bool extra_act[2];
	bool pzone_act[2];
	bool conti_act;
	bool chain_forced;
	ChainInfo current_chain;
	bool last_chain;
	bool deck_reversed;
	bool conti_selecting;

	ClientField();
	void Clear();
	void Initial(uint8_t player, uint32_t deckc, uint32_t extrac);
	std::vector<ClientCard*>* GetList(uint8_t location, uint8_t controler);
	ClientCard* GetCard(uint8_t controler, uint8_t location, uint32_t sequence, uint32_t sub_seq = 0);
	void AddCard(ClientCard* pcard, uint8_t controler, uint8_t location, uint32_t sequence);
	ClientCard* RemoveCard(uint8_t controler, uint8_t location, uint32_t sequence);
	void UpdateCard(uint8_t controler, uint8_t location, uint32_t sequence, char* data, uint32_t len = 0);
	void UpdateFieldCard(uint8_t controler, uint8_t location, char* data, uint32_t len = 0);
	void ClearCommandFlag();
	void ClearSelect();
	void ClearChainSelect();
	void ShowSelectCard(bool buttonok = false, bool chain = false);
	void ShowChainCard();
	void ShowLocationCard();
	void ShowSelectOption(uint64_t select_hint = 0, bool should_lock = true);
	void ReplaySwap();
	void RefreshAllCards();
	void RefreshHandHitboxes();

	void GetChainDrawCoordinates(uint8_t controler, uint8_t location, uint32_t sequence, irr::core::vector3df* t);
	void GetCardDrawCoordinates(ClientCard* pcard, irr::core::vector3df* t, irr::core::vector3df* r, bool setTrans = false);
	void MoveCard(ClientCard* pcard, float frame);
	void FadeCard(ClientCard* pcard, float alpha, float frame);
	bool ShowSelectSum();
	bool CheckSelectSum();
	bool check_min(const std::set<ClientCard*>& left, std::set<ClientCard*>::const_iterator index, int min, int max);
	bool check_sel_sum_s(const std::set<ClientCard*>& left, int index, int acc);
	void check_sel_sum_t(const std::set<ClientCard*>& left, int acc);
	bool check_sum(std::set<ClientCard*>::const_iterator index, std::set<ClientCard*>::const_iterator end, int acc, uint32_t count);

	void UpdateDeclarableList(bool refresh = false);

	irr::gui::IGUIElement* panel;
	std::vector<uint32_t> ancard;
	uint8_t hovered_controler;
	uint16_t hovered_location;
	uint32_t hovered_sequence;
	uint8_t command_controler;
	uint16_t command_location;
	uint32_t command_sequence;
	ClientCard* hovered_card;
	uint8_t hovered_player;
	ClientCard* clicked_card;
	ClientCard* command_card;
	ClientCard* highlighting_card;
	uint16_t list_command;

	int indexLookedUpCard = 0;

	virtual bool OnEvent(const irr::SEvent& event);
	virtual bool OnCommonEvent(const irr::SEvent& event, bool& stopPropagation);
	void GetHoverField(irr::core::vector2d<irr::s32> mouse);
	void ShowMenu(int flag, int x, int y);
	void UpdateChainButtons(irr::gui::IGUIElement* caller = nullptr);
	void ShowCancelOrFinishButton(int buttonOp);
	void SetShowMark(ClientCard* pcard, bool enable);
	void ShowCardInfoInList(ClientCard* pcard, irr::gui::IGUIElement* element, irr::gui::IGUIElement* parent);
	void SetResponseSelectedCards() const;
	void SetResponseSelectedOption() const;
	void CancelOrFinish();

	//Accessibility Focus
	bool accessibilityFocus = true; //TODO- FAZER UMA CONFIGURAÇÃO NO MENU PRA ISSO
	int cardSelectPosition = 0;
	AccessibilityFieldFocus::DisplayedField displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
	int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
	int battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
	int cardType = AccessibilityFieldFocus::CardType::MONSTER;
	void CloseDialog();
	void DisplayCards(const std::vector<ClientCard*> &field);
	void DisplayCards(const std::vector<ChainInfo>& field);
	bool UseCard(const AccessibilityFieldFocus::UseType& useType, irr::SEvent event);
	bool CheckIfCanViewCards(irr::SEvent event);
	void SelectFieldSlot(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
	void SelectFieldSlotNoPlayer(const int& slot);
	int GetFieldSlot(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
	int SearchFieldSlot(const int& displayedField);
	void ScrollCardList(const AccessibilityFieldFocus::Scroll& position = AccessibilityFieldFocus::Scroll::RIGHT);
	float GetYPosition();
	float GetXPosition(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
	float GetXPosition(const AccessibilityFieldFocus::Scroll& position = AccessibilityFieldFocus::Scroll::RIGHT);
	AccessibilityFieldFocus::DisplayedCards GetCardField();
	void SimulateButton(irr::gui::IGUIElement* caller = nullptr);
	void MouseClick(const irr::SEvent& event);
	void MouseRightClick(const irr::SEvent& event);
	//bool SetCard(const int& setType, const AccessibilityFieldFocus::UseType& useType = AccessibilityFieldFocus::UseType::NORMAL_SUMMON);
	void SetMouseOnCard();
};

}

//special cards
#define CARD_MARINE_DOLPHIN	78734254
#define CARD_TWINKLE_MOSS	13857930

#define LOCATION_SKILL   0x400

#endif //CLIENT_FIELD_H
