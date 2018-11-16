/**
 * @project zapdos
 * @file include/store/TextRecordTable.hpp
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
 *  TextRecordTable.hpp :   Headers for TextRecordTable  textrecord
 *
 */
#ifndef _ZPDS_STORE_TEXT_RECORD_TABLE_HPP_
#define _ZPDS_STORE_TEXT_RECORD_TABLE_HPP_

#include "StoreTable.hpp"

namespace zpds {
namespace store {
class TextRecordTable : public StoreTable<TextRecordT> {
public:
	using StoreTable<TextRecordT>::dbpointer;
	using StoreTable<TextRecordT>::StoreTable;
	using StoreTable<TextRecordT>::MapT;

	/**
	* Constructor
	*
	* @param trydb
	*   dbpointer shared pointer to db
	*
	*/
	TextRecordTable(dbpointer trydb);

	/**
	* Destructor
	*
	*/
	virtual ~TextRecordTable() {}

	/**
	* make noncopyable and remove default
	*/

	TextRecordTable() = delete;
	TextRecordTable(const std::string, const size_t) = delete;
	TextRecordTable(const TextRecordTable&) = delete;
	TextRecordTable& operator=(const TextRecordTable&) = delete;


protected:

	/**
	* GetKey: get a key
	*
	* @param record
	*   TextRecordT* record
	*
	* @param keytype
	*   KeyTypeE key type for index
	*
	* @param pre
	*   bool non unique keys
	*
	* @return
	*   std::string key
	*/
	std::string GetKey(TextRecordT* record, KeyTypeE keytype, bool pre) override;

};
} // namespace store
} // namespace zpds
#endif /* _ZPDS_STORE_TEXT_RECORD_TABLE_HPP_ */
