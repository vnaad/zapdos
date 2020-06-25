/**
 * @project zapdos
 * @file include/store/ServiceDefine.hh
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
 *  ServiceDefine.hh : Definitions of access rules
 *
 */
#ifndef _ZPDS_STORE_SERVICE_DEFINE_HH_
#define _ZPDS_STORE_SERVICE_DEFINE_HH_

#define ZPDS_MAX_HEX_VALUE_FIFTEEN  0x0FFFF
#define ZPDS_MAX_PROFILE_RULES 10
#define ZPDS_MAX_RULE_WEIGHT 1000

#define ZPDS_FORBIDDEN_USERNAMES "admin","root","superuser","system"

/* ---- Actions ---- */

#define ZPDS_UACTION_NONE           0x00000
#define ZPDS_UACTION_CREATE         0x00001
#define ZPDS_UACTION_UPSERT         0x00002
#define ZPDS_UACTION_UPDATE         0x00004
#define ZPDS_UACTION_DELETE         0x00008
#define ZPDS_UACTION_READ           0x00010

// update permissions
#define ZPDS_WRITR_IS_SELF          0x00001 // user or exter is self
#define ZPDS_WRITR_IS_ADMIN         0x00002 // exter is admin
#define ZPDS_WRITR_CREATING         0x00004 // exter with user new
#define ZPDS_WRITR_UPDATING         0x00008 // exter with user
#define ZPDS_WRITR_DELETING         0x00010 // exter with user

// read permissions
#define ZPDS_READR_IS_SELF          0x00001 // user or exter is self
#define ZPDS_READR_IS_ADMIN         0x00002 // exter is admin
#define ZPDS_READR_IS_CREATR        0x00004 // exter who created
#define ZPDS_READR_IS_EXTER         0x00008 // another exter non admin
#define ZPDS_READR_IS_USER          0x00010 // other user not self
#define ZPDS_READR_IS_PUBLIC        0x00020 // generic data

/* --- UserDataT --- */

// fields common to UserDataT and ExterDataT
#define ZPDS_UDFLD_NONE             0x00000
#define ZPDS_UDFLD_SIGNKEY          0x00001
#define ZPDS_UDFLD_PASSKEY          0x00002
#define ZPDS_UDFLD_ROLE             0x00004
#define ZPDS_UDFLD_INFO             0x00008
#define ZPDS_UDFLD_GNAME            0x00010
#define ZPDS_UDFLD_MOBILE           0x00020
#define ZPDS_UDFLD_EMAIL            0x00040
#define ZPDS_UDFLD_PROFILES         0x00080
#define ZPDS_UDFLD_INVITED          0x00100
#define ZPDS_UDFLD_TAGS             0x00200
#define ZPDS_UDFLD_SUBSCR           0x00400
#define ZPDS_UDFLD_CATEGORIES       0x00800

// UserDataT update permissions
#define ZPDS_WRTPUD_SIGNKEY         ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING
#define ZPDS_WRTPUD_PASSKEY         ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING
#define ZPDS_WRTPUD_ROLE            0x00000 // NA
#define ZPDS_WRTPUD_INFO            ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_GNAME           ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_MOBILE          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_EMAIL           ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_PROFILES        0x00000 // NA
#define ZPDS_WRTPUD_INVITED         ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_TAGS            ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_SUBSCR          ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPUD_CATEGORIES      ZPDS_WRITR_IS_ADMIN                      | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING

// UserDataT read permissions
#define ZPDS_READUD_SIGNKEY         ZPDS_READR_IS_ADMIN
#define ZPDS_READUD_PASSKEY         ZPDS_READR_IS_ADMIN
#define ZPDS_READUD_ROLE            0x00000 // NA
#define ZPDS_READUD_INFO            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER
#define ZPDS_READUD_GNAME           ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER
#define ZPDS_READUD_MOBILE          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR
#define ZPDS_READUD_EMAIL           ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR
#define ZPDS_READUD_PROFILES        0x00000 // NA
#define ZPDS_READUD_INVITED         ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER
#define ZPDS_READUD_TAGS            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER
#define ZPDS_READUD_SUBSCR          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER
#define ZPDS_READUD_CATEGORIES      ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER

// ExterDataT update permissions
#define ZPDS_WRTPED_SIGNKEY         ZPDS_WRITR_IS_ADMIN
#define ZPDS_WRTPED_PASSKEY         ZPDS_WRITR_IS_ADMIN
#define ZPDS_WRTPED_ROLE            ZPDS_WRITR_IS_ADMIN
#define ZPDS_WRTPED_INFO            ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF
#define ZPDS_WRTPED_GNAME           ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF
#define ZPDS_WRTPED_MOBILE          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF
#define ZPDS_WRTPED_EMAIL           ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF
#define ZPDS_WRTPED_PROFILES        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_IS_SELF
#define ZPDS_WRTPED_INVITED         0x00000 // NA
#define ZPDS_WRTPED_TAGS            ZPDS_WRITR_IS_ADMIN
#define ZPDS_WRTPED_SUBSCR          0x00000 // NA
#define ZPDS_WRTPED_CATEGORIES      ZPDS_WRITR_IS_ADMIN

// ExterDataT read permissions
#define ZPDS_READED_SIGNKEY         ZPDS_READR_IS_ADMIN
#define ZPDS_READED_PASSKEY         ZPDS_READR_IS_ADMIN
#define ZPDS_READED_ROLE            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_INFO            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_GNAME           ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_MOBILE          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_EMAIL           ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_PROFILES        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_INVITED         0x00000 // NA
#define ZPDS_READED_TAGS            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF
#define ZPDS_READED_SUBSCR          0x00000 // NA
#define ZPDS_READED_CATEGORIES      ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_SELF

/* --- ItemDataT --- */

// ItemDataT fields common to ItemDataT derivatives

#define ZPDS_IDFLD_NONE             0x00000
#define ZPDS_IDFLD_TEXTFIELDS       0x00001 // lang, description
#define ZPDS_IDFLD_CANSEE           0x00002
#define ZPDS_IDFLD_LANGUAGE         0x00004
#define ZPDS_IDFLD_TAGS             0x00008
#define ZPDS_IDFLD_CONTACTS         0x00010
#define ZPDS_IDFLD_IMAGES           0x00020 // thumbnail .. landscape
#define ZPDS_IDFLD_VERSIONS         0x00040
#define ZPDS_IDFLD_PARENT           0x00080
#define ZPDS_IDFLD_ALIAS            0x00100
#define ZPDS_IDFLD_CATEGORY         0x00200
#define ZPDS_IDFLD_ORIGIN           0x00400
#define ZPDS_IDFLD_LOCALFIELDS      0x00800
#define ZPDS_IDFLD_OSMFIELDS        0x01000
#define ZPDS_IDFLD_IMPORTANCE       0x02000
#define ZPDS_IDFLD_GEOMETRY         0x04000
#define ZPDS_IDFLD_RATING           0x08000

// ItemDataT write permissions
#define ZPDS_WRTPID_TEXTFIELDS      ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_CANSEE          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_LANGUAGE        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_IMAGES          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_TAGS            ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_CONTACTS        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_VERSIONS        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_PARENT          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_ALIAS           ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_CATEGORY        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_ORIGIN          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_LOCALFIELDS     ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_OSMFIELDS       ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_IMPORTANCE      ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_GEOMETRY        ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING
#define ZPDS_WRTPID_RATING          ZPDS_WRITR_IS_ADMIN | ZPDS_WRITR_CREATING | ZPDS_WRITR_UPDATING

// ItemDataT read permissions
#define ZPDS_READID_TEXTFIELDS      ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_CANSEE          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_LANGUAGE        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_IMAGES          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_TAGS            ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_CONTACTS        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_VERSIONS        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_PARENT          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_ALIAS           ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_CATEGORY        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_ORIGIN          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_LOCALFIELDS     ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_OSMFIELDS       ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_IMPORTANCE      ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_GEOMETRY        ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC
#define ZPDS_READID_RATING          ZPDS_READR_IS_ADMIN | ZPDS_READR_IS_CREATR | ZPDS_READR_IS_EXTER | ZPDS_READR_IS_USER | ZPDS_READR_IS_PUBLIC


#endif /* _ZPDS_STORE_SERVICE_DEFINE_HH_ */