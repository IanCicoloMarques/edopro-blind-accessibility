#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

namespace ygo {
	struct Message
	{
		enum MessageType
		{
			WON_ROCK_PAPERS_CISSORS = 156,
			SELECT_YOUR_TURN = 162,
			NEXT_MATCH = 151,
			COMMA_YES_DOT_NO = 151,
			CHECK_FIELD,
			SELECT_CHAIN,
			SELECT_POSITION,
			SELECT_TRIBUTE,
		};
	};
}

#endif //MESSAGE_TYPE_H
