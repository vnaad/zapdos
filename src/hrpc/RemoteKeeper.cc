/**
 * @project zapdos
 * @file src/hrpc/RemoteKeeper.cc
 * @author  S Roychowdhury < sroycode at gmail dot com >
 * @version 1.0.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2018-2020 S Roychowdhury
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
 *  RemoteKeeper.cc : Hrpc Remote List Manager impl
 *
 */
#include <thread>
#include "hrpc/RemoteKeeper.hpp"
#include "hrpc/ServiceDefine.hh"
#include "hrpc/HrpcClient.hpp"

/**
* constructor
*
*/
zpds::hrpc::RemoteKeeper::RemoteKeeper(zpds::utils::SharedTable::pointer s) : stptr(s) {}

/**
* destructor
*/
zpds::hrpc::RemoteKeeper::~RemoteKeeper() {}

/**
* SetHosts : set list of hosts
*
*/
void zpds::hrpc::RemoteKeeper::SetHosts(zpds::hrpc::StateT* state)
{
	if (state->is_master()) {
		zpds::utils::SharedTable::RemoteMapT rmap;
		for (auto i=0; i<state->remotes_size(); ++i) {
			zpds::hrpc::RemoteT* rms = state->mutable_remotes(i);
			rmap[rms->address()]= {rms->logcounter(), rms->updated_at()};
		}
		stptr->remotes.AddMany(std::move(rmap));
	}
	else {
		stptr->remotes.AddOne( state->thisurl(), { state->logcounter(), state->ts() } );
	}
	LOG(INFO) << "Added Remote from: " << state->thisurl() ;
}

/**
* AddHost : add a single host
*
*/
void zpds::hrpc::RemoteKeeper::AddHost(zpds::hrpc::RemoteT* rms)
{
	stptr->remotes.AddOne( rms->address(), { rms->logcounter(), rms->updated_at() } );
}

/**
* AddHost : add a single host
*
*/
void zpds::hrpc::RemoteKeeper::AddHost(std::string name, uint64_t logcounter, uint64_t updated_at)
{
	stptr->remotes.AddOne( std::move(name), {logcounter, updated_at});
}

/**
* GetHosts : get params and list of hosts
*
*/
void zpds::hrpc::RemoteKeeper::GetHosts(zpds::hrpc::StateT* state)
{
	// get params
	state->set_hostname( stptr->hostname.Get() );
	state->set_master( stptr->master.Get() );
	state->set_logcounter( stptr->logcounter.Get() );
	state->set_is_master( stptr->is_master.Get() );
	state->set_ts( ZPDS_CURRTIME_MS );
	state->set_thisurl( stptr->thisurl.Get() );
	if ( !state->is_master() ) return;

	for (const auto& p : stptr->remotes.GetCopy() ) {
		zpds::hrpc::RemoteT* rem = state->add_remotes();
		rem->set_address( p.first );
		rem->set_logcounter( p.second.first );
		rem->set_updated_at( p.second.second );
	}
}

/**
* HostUpdate : update hosts with latest
*
*/
void zpds::hrpc::RemoteKeeper::HostUpdate()
{
	// get params
	zpds::hrpc::StateT state;
	GetHosts(&state);
	zpds::hrpc::HrpcClient hclient;
	for (const auto& p : stptr->remotes.GetCopy() ) {
		LOG(INFO) << "Intimate Remote: " << p.first ;
		bool status = hclient.SendToRemote(stptr,p.first,::zpds::hrpc::R_SETINFO,&state,true);
	}
}

/**
* MasterUpdate: elect the master based on info received after cutoff
*
*/
void zpds::hrpc::RemoteKeeper::MasterUpdate(uint64_t cutoff)
{
	uint64_t max_logcounter = stptr->logcounter.Get();
	std::string newmaster = stptr->thisurl.Get();
	DLOG(INFO) << "Cand 0: " << newmaster << " " << max_logcounter;
	for (const auto& p : stptr->remotes.GetCopy() ) {
		DLOG(INFO) << "Cand 1: " << p.first << " " << p.second.first;
		// eliminate too low , lower counter , me
		if ( (p.second.second < cutoff) || (p.second.first < max_logcounter) || (p.first == newmaster) )
			continue;
		// we are now left with eligible entries only
		if ( (p.second.first > max_logcounter)  || ((p.second.first == max_logcounter) && (p.first > newmaster)) ) {
			newmaster = p.first;
			max_logcounter = p.second.first;
		}
		DLOG(INFO) << "Cand 2: " << newmaster << " " << max_logcounter;
	}

	if (newmaster == stptr->thisurl.Get()) {
		// lastslave initialised
		stptr->lastslave.Set("");
		stptr->is_master.Set(true);
		LOG(INFO) << "New Master elected: ME !";
	}
	else {
		zpds::hrpc::StateT state;
		GetHosts(&state);
		zpds::hrpc::HrpcClient hclient;
		int retries = 0;
		do {
			bool status = hclient.SendToRemote(stptr,newmaster,::zpds::hrpc::R_REGISTER,&state,true);
			if (status) {
				stptr->master.Set(newmaster);
				LOG(INFO) << "New Master elected: " << newmaster;
				break;
			}
			else {
				LOG(INFO) << "New Master is not ready: " << newmaster;
				std::this_thread::sleep_for( std::chrono::milliseconds( ELECTION_SLEEP_INTERVAL ) );
			}
		}
		while(++retries< ELECTION_MAX_RETRIES );
	}
}
