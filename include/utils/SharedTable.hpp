/**
 * @project zapdos
 * @file include/utils/SharedTable.hpp
 * @author  S Roychowdhury < sroycode at gmail dot com>
 * @version 1.0.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2018-2019 S Roychowdhury
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 *  SharedTable.hpp :   Shared pointer to sharedtable object
 *
 */
#ifndef _ZPDS_UTILS_SHAREDTABLE_HPP_
#define _ZPDS_UTILS_SHAREDTABLE_HPP_

#include <memory>
#include <vector>
#include <random>

#include "utils/SharedCounter.hpp"
#include "utils/SharedPairMap.hpp"
#include "utils/SharedMap.hpp"

#include "store/StoreLevel.hpp"

#include "store/CacheContainer.hpp"
#include "search/StoreTrie.hpp"
#include "jamspell/StoreJam.hpp"

namespace zpds {
namespace utils {
class SharedTable : public std::enable_shared_from_this<SharedTable> {
public:
	using pointer=std::shared_ptr<SharedTable>;
	using dbpointer=zpds::store::StoreLevel::dbpointer;

	using SharedString = SharedObject<std::string>;
	using SharedUnsigned = SharedObject<uint64_t>;
	using SharedDBPointer = SharedObject<dbpointer>;
	using SharedBool = SharedObject<bool>;

	using SharedRemote = SharedPairMap<std::string,uint64_t,uint64_t>;
	using RemoteMapT = SharedPairMap<std::string,uint64_t,uint64_t>::PairMapT;

	using SharedTrans = SharedMap<uint64_t,std::string>;

	using SharedCache = zpds::store::CacheContainer::pointer;
	using SharedTrie = zpds::search::StoreTrie::pointer;
	using SharedJam = zpds::jamspell::StoreJam::pointer;

	using LockT = boost::shared_mutex;

	// map of shared followers
	SharedRemote remotes;

	// map of shared transactions
	SharedTrans transactions;

	// string shared
	SharedString master;
	SharedString shared_secret;
	SharedString hostname;
	SharedString baseurl;
	SharedString thisurl;
	SharedString lastslave;

	// whatwhere
	SharedString xapath;
	SharedTrie xapdb;

	// spellcheck
	SharedJam jamdb;

	// counter shared
	SharedCounter maincounter;
	SharedCounter logcounter;

	// database pointers
	SharedDBPointer maindb;
	SharedDBPointer logdb;

	// cache pointers
	SharedCache dbcache;

	// booleans
	SharedBool is_master;
	SharedBool is_ready;

	SharedBool dont_use_cache;
	SharedBool dont_create_profile;
	SharedBool allow_free_update;
	SharedBool use_local_whatwhere;

	SharedBool force_commit;

	// lockers
	LockT update_lock;

	/**
	* make noncopyable
	*/

	SharedTable(const SharedTable&) = delete;
	SharedTable& operator=(const SharedTable&) = delete;

	/**
	* create : static construction creates new first time
	*
	* @return
	*   pointer
	*/
	static pointer create()
	{
		pointer p(new SharedTable());
		return p;
	}

	/**
	* share : return instance
	*
	* @return
	*   pointer
	*/
	pointer share()
	{
		return shared_from_this();
	}

	/**
	* destructor
	*/
	virtual ~SharedTable () {}


private:

	/**
	* Constructor : default private
	*
	* @return
	*   none
	*/
	SharedTable() :
		dbcache(zpds::store::CacheContainer::create())
	{}

};
} // namespace utils
} // namespace zpds
#endif /* _ZPDS_UTILS_SHAREDTABLE_HPP_ */
