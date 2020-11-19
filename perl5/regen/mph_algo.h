#define MPH_VALt I16

/*
rows: 0
seed: 1348825708
full length of keys: 0
blob length: 0
ref length: 0
data size: 0 (%NaN)
*/

STATIC const unsigned char mph_blob[] =
/* mph_blob length: 0 */

struct mph_bucket_info {
    U16 seed2;
    U16 pfx;
    U16 sfx;
    U8  pfx_len;
    U8  sfx_len;
    MPH_VALt value;
};

#define MPH_RSHIFT 8
#define MPH_BUCKETS 0

STATIC const U32 MPH_SEED1 = 0x5065726c;
STATIC const U32 MPH_FNV_CONST = 0x01000193;

/* The comments give the input key for the row it is in */
STATIC const struct mph_bucket_info mph_table[MPH_BUCKETS] = {

};

MPH_VALt mph_match( const unsigned char * const key, const U16 key_len ) {
    const unsigned char * ptr= key;
    const unsigned char * ptr_end= key + key_len;
    U32 h= MPH_SEED1;
    U32 s;
    U32 n;
    do {
        h ^= NATIVE_TO_LATIN1(*ptr);    /* table collated in Latin1 */
        h *= MPH_FNV_CONST;
    } while ( ++ptr < ptr_end );
    n= h % MPH_BUCKETS;
    s = mph_table[n].seed2;
    if (s) {
        h= (h >> MPH_RSHIFT) ^ s;
        n = h % MPH_BUCKETS;
        if (
            ( mph_table[n].pfx_len + mph_table[n].sfx_len == key_len ) &&
            ( memcmp(mph_blob + mph_table[n].pfx, key, mph_table[n].pfx_len) == 0 ) &&
            ( !mph_table[n].sfx_len || memcmp(mph_blob + mph_table[n].sfx,
                key + mph_table[n].pfx_len, mph_table[n].sfx_len) == 0 )
        ) {
            return mph_table[n].value;
        }
    }
    return 0;
}
