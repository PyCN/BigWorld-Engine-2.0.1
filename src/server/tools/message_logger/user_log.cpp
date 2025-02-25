/******************************************************************************
BigWorld Technology 
Copyright BigWorld Pty, Ltd.
All Rights Reserved. Commercial in confidence.

WARNING: This computer program is protected by copyright law and international
treaties. Unauthorized use, reproduction or distribution of this program, or
any portion of this program, may result in the imposition of civil and
criminal penalties as provided by law.
******************************************************************************/

#include "user_log.hpp"

#include "log_entry.hpp"

#include <dirent.h>
#include <string>


/**
 * Constructor.
 */
UserLog::UserLog( uint16 uid, const std::string &username ) :
	uid_( uid ),
	username_( username ),
	isGood_( false )
{ }


/**
 * Destructor.
 */
UserLog::~UserLog()
{
	for (unsigned i=0; i < userSegments_.size(); i++)
	{
		delete userSegments_[i];
	}
}


/**
 * Initialises the base UserLog instance.
 */
bool UserLog::init( const std::string rootPath )
{
	path_ = rootPath;
	path_.push_back( '/' );
	path_ += username_;

	return true;
}


/**
 * Returns whether the UserLog is in a fit state to use or not.
 *
 * @returns true if the UserLog is ready to use, false if not.
 */
bool UserLog::isGood() const
{
	return isGood_;
}


/**
 * Retrieves the UID this UserLog represents.
 *
 * @returns UID the current UserLog represents.
 */
uint16 UserLog::getUID() const
{
	return uid_;
}


/**
 * Retrieves the username this UserLog represents.
 *
 * @returns An std::string of the username the current UserLog represents.
 */
std::string UserLog::getUsername() const
{
	return username_;
}


/**
 * This method returns whether there are any UserSegments currently being
 * written to by a MessageLogger process.
 *
 * @returns true if UserLog has active segments, false if not.
 */
bool UserLog::hasActiveSegments() const
{
	return !userSegments_.empty();
}


/**
 * This method returns the suffix of the current segment being written to.
 *
 * @returns Active segment suffix string, empty string if there is no active
 *          segment.
 */
std::string UserLog::activeSegmentSuffix() const
{
	if (!this->hasActiveSegments())
	{
		return NULL;
	}

	return userSegments_[0]->getSuffix();
}
