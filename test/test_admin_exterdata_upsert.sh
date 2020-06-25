#!/bin/bash
export SRCDIR=$(dirname $(cd ${0%/*} 2>>/dev/null ; echo `pwd`/${0##*/}))
export SRCFIL=$(basename $(cd ${0%/*} 2>>/dev/null ; echo `pwd`/${0##*/}))
. ${SRCDIR}/config.sh

## ---- variables
if [ -z "${sessionkey}" ] ; then echo "define sessionkey by logging in"; exit 1; fi
username=${username:="admin"}

POST_DATA='{
  "sessionkey" : "'${sessionkey}'",
  "username" : "'${username}'",
  "payload" : { "name" : "test001", "passkey" : "test001p" , "given_name" : "atest 001" , "description" : "added later" },
  "payloads" : [
     { "name" : "test003", "passkey" : "test003p" , "given_name" : "test 003" , "tags" : [ { "name" : "goodtag" , "value" : "formal" } ] }
  ]
}'

## ---- main

# wget -q -O - --header="Content-Type: application/json" --post-data="${POST_DATA}" "${TESTURL}/_admin/api/v1/exterdata/upsert"
${HTTPIE} POST "${TESTURL}/_admin/api/v1/exterdata/upsert" <<< "$POST_DATA"