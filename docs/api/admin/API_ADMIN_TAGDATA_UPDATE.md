# TagData Update ( POST _admin/api/v1/tagdata/update )

Exter with admin `is_admin` can update any tags, non admin with `can_add_tags` can update self-created tags.

**Test Script** : `test/test_admin_tagdata_update.sh`

## Parameters

| Input | Description |
| ---- | ----------- |
| `username` | user name |
| `sessionkey` | user session key |
| `payload` | Object. Fields `keytype`, `name` are needed, flags `is_allowed` , `is_repeated`, `is_searchable` |
| `payloads` | array of `payload` |

## Typical Session Example

```
POST /_admin/api/v1/tagdata/update HTTP/1.1
Accept: application/json, */*
Content-Type: application/json
Content-Length: 341

{
  "sessionkey" : "6Hqia6axlaLQZ6gNEIn8L5babDPANTfPsfu31Q==",
  "username" : "admin",
  "payload" : { "keytype" : "K_USERDATA", "name" : "agegroup" , "is_allowed" : true , "is_searchable" : true },
  "payloads" : [
    { "keytype" : "K_USERDATA", "name" : "goodtag", "is_allowed" : true, "is_repeated": true, "is_searchable" : true }
  ]
}


HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 51

{
   "updatecount" : "2",
   "inputcount" : "2",
   "success" : true
}
```

## Note

- Assuming sessionkey exists
- Dont use both `payload` and `payloads` in same query , the example is for berevity.

