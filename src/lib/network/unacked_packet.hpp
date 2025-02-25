/******************************************************************************
BigWorld Technology 
Copyright BigWorld Pty, Ltd.
All Rights Reserved. Commercial in confidence.

WARNING: This computer program is protected by copyright law and international
treaties. Unauthorized use, reproduction or distribution of this program, or
any portion of this program, may result in the imposition of civil and
criminal penalties as provided by law.
******************************************************************************/

#ifndef UNACKED_PACKET_HPP
#define UNACKED_PACKET_HPP

#include "channel.hpp"
#include "reliable_order.hpp"

namespace Mercury
{

/**
 *	This class stores sent packets that may need to be resent.  These things
 *	need to be fast so we pool them and use custom allocators.
 */
class Channel::UnackedPacket
{
public:
	UnackedPacket( Packet * pPacket = NULL );
	SeqNum seq() const	{ return pPacket_->seq(); }

	PacketPtr pPacket_;

	/// The outgoing sequence number on the channel the last time this
	/// packet was sent.
	SeqNum  lastSentAtOutSeq_;

	/// The time this packet was initially sent.
	uint64	lastSentTime_;

	/// Whether or not this packet has been resent.
	bool	wasResent_;

	/// A series of records detailing which parts of the packet were
	/// reliable, used when forming piggyback packets.
	ReliableVector reliableOrders_;

	static UnackedPacket * initFromStream(
		BinaryIStream & data, uint64 timeNow );

	static void addToStream(
		UnackedPacket * pInstance, BinaryOStream & data );
};

} // namespace Mercury
#endif // UNACKED_PACKET_HPP
