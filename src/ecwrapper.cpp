// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ecwrapper.h"

#include "serialize.h"
#include "uint256.h"

#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/opensslv.h>

namespace
{

static void GetECDSASigValues(
    const ECDSA_SIG* sig,
    const BIGNUM** sig_r,
    const BIGNUM** sig_s)
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    *sig_r = sig->r;
    *sig_s = sig->s;
#else
    ECDSA_SIG_get0(sig, sig_r, sig_s);
#endif
}

static bool SetECDSASigValues(
    ECDSA_SIG* sig,
    BIGNUM* sig_r,
    BIGNUM* sig_s)
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    if (sig == NULL || sig_r == NULL || sig_s == NULL)
        return false;

    BN_clear_free(sig->r);
    BN_clear_free(sig->s);
    sig->r = sig_r;
    sig->s = sig_s;
    return true;
#else
    return ECDSA_SIG_set0(sig, sig_r, sig_s) == 1;
#endif
}
/**
 * Perform ECDSA key recovery (see SEC1 4.1.6) for curves over (mod p)-fields
 * recid selects which key is recovered
 * if check is non-zero, additional checks are performed
 */
int ECDSA_SIG_recover_key_GFp(EC_KEY* eckey, ECDSA_SIG* ecsig, const unsigned char* msg, int msglen, int recid, int check)
{
    if (!eckey) return 0;

    const BIGNUM* sig_r = NULL;
    const BIGNUM* sig_s = NULL;
    GetECDSASigValues(ecsig, &sig_r, &sig_s);

    int ret = 0;
    BN_CTX* ctx = NULL;

    BIGNUM* x = NULL;
    BIGNUM* e = NULL;
    BIGNUM* order = NULL;
    BIGNUM* sor = NULL;
    BIGNUM* eor = NULL;
    BIGNUM* field = NULL;
    EC_POINT* R = NULL;
    EC_POINT* O = NULL;
    EC_POINT* Q = NULL;
    BIGNUM* rr = NULL;
    BIGNUM* zero = NULL;
    int n = 0;
    int i = recid / 2;

    const EC_GROUP* group = EC_KEY_get0_group(eckey);
    if ((ctx = BN_CTX_new()) == NULL) {
        ret = -1;
        goto err;
    }
    BN_CTX_start(ctx);
    order = BN_CTX_get(ctx);
    if (!EC_GROUP_get_order(group, order, ctx)) {
        ret = -2;
        goto err;
    }
    x = BN_CTX_get(ctx);
    if (!BN_copy(x, order)) {
        ret = -1;
        goto err;
    }
    if (!BN_mul_word(x, i)) {
        ret = -1;
        goto err;
    }
    if (!BN_add(x, x, sig_r)) {
        ret = -1;
        goto err;
    }
    field = BN_CTX_get(ctx);
    if (!EC_GROUP_get_curve_GFp(group, field, NULL, NULL, ctx)) {
        ret = -2;
        goto err;
    }
    if (BN_cmp(x, field) >= 0) {
        ret = 0;
        goto err;
    }
    if ((R = EC_POINT_new(group)) == NULL) {
        ret = -2;
        goto err;
    }
    if (!EC_POINT_set_compressed_coordinates_GFp(group, R, x, recid % 2, ctx)) {
        ret = 0;
        goto err;
    }
    if (check) {
        if ((O = EC_POINT_new(group)) == NULL) {
            ret = -2;
            goto err;
        }
        if (!EC_POINT_mul(group, O, NULL, R, order, ctx)) {
            ret = -2;
            goto err;
        }
        if (!EC_POINT_is_at_infinity(group, O)) {
            ret = 0;
            goto err;
        }
    }
    if ((Q = EC_POINT_new(group)) == NULL) {
        ret = -2;
        goto err;
    }
    n = EC_GROUP_get_degree(group);
    e = BN_CTX_get(ctx);
    if (!BN_bin2bn(msg, msglen, e)) {
        ret = -1;
        goto err;
    }
    if (8 * msglen > n) BN_rshift(e, e, 8 - (n & 7));
    zero = BN_CTX_get(ctx);
    BN_zero(zero);
    if (!BN_mod_sub(e, zero, e, order, ctx)) {
        ret = -1;
        goto err;
    }
    rr = BN_CTX_get(ctx);
    if (!BN_mod_inverse(rr, sig_r, order, ctx)) {
        ret = -1;
        goto err;
    }
    sor = BN_CTX_get(ctx);
    if (!BN_mod_mul(sor, sig_s, rr, order, ctx)) {
        ret = -1;
        goto err;
    }
    eor = BN_CTX_get(ctx);
    if (!BN_mod_mul(eor, e, rr, order, ctx)) {
        ret = -1;
        goto err;
    }
    if (!EC_POINT_mul(group, Q, eor, R, sor, ctx)) {
        ret = -2;
        goto err;
    }
    if (!EC_KEY_set_public_key(eckey, Q)) {
        ret = -2;
        goto err;
    }

    ret = 1;

err:
    if (ctx) {
        BN_CTX_end(ctx);
        BN_CTX_free(ctx);
    }
    if (R != NULL) EC_POINT_free(R);
    if (O != NULL) EC_POINT_free(O);
    if (Q != NULL) EC_POINT_free(Q);
    return ret;
}

} // anon namespace

CECKey::CECKey()
{
    pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
    assert(pkey != NULL);
}

CECKey::~CECKey()
{
    EC_KEY_free(pkey);
}

void CECKey::GetPubKey(std::vector<unsigned char>& pubkey, bool fCompressed)
{
    EC_KEY_set_conv_form(pkey, fCompressed ? POINT_CONVERSION_COMPRESSED : POINT_CONVERSION_UNCOMPRESSED);
    int nSize = i2o_ECPublicKey(pkey, NULL);
    assert(nSize);
    assert(nSize <= 65);
    pubkey.clear();
    pubkey.resize(nSize);
    unsigned char* pbegin(begin_ptr(pubkey));
    int nSize2 = i2o_ECPublicKey(pkey, &pbegin);
    assert(nSize == nSize2);
}

bool CECKey::SetPubKey(const unsigned char* pubkey, size_t size)
{
    return o2i_ECPublicKey(&pkey, &pubkey, size) != NULL;
}

static bool ReadLaxDERLength(
    const unsigned char* input,
    size_t inputLen,
    size_t& pos,
    size_t& length)
{
    if (pos >= inputLen)
        return false;

    unsigned char lengthByte = input[pos++];

    if ((lengthByte & 0x80) == 0) {
        length = lengthByte;
        return true;
    }

    size_t lengthBytes = lengthByte & 0x7f;
    if (lengthBytes == 0 || pos + lengthBytes > inputLen)
        return false;

    while (lengthBytes > 0 && input[pos] == 0) {
        ++pos;
        --lengthBytes;
    }

    if (lengthBytes > sizeof(size_t))
        return false;

    length = 0;
    for (size_t i = 0; i < lengthBytes; ++i)
        length = (length << 8) | input[pos++];

    return true;
}

static ECDSA_SIG* ParseLaxDERSignature(
    const std::vector<unsigned char>& signature)
{
    if (signature.empty())
        return NULL;

    const unsigned char* input = &signature[0];
    const size_t inputLen = signature.size();
    size_t pos = 0;
    size_t sequenceLen = 0;
    size_t rLen = 0;
    size_t sLen = 0;

    if (pos >= inputLen || input[pos++] != 0x30)
        return NULL;

    if (!ReadLaxDERLength(input, inputLen, pos, sequenceLen))
        return NULL;

    if (pos >= inputLen || input[pos++] != 0x02)
        return NULL;

    if (!ReadLaxDERLength(input, inputLen, pos, rLen))
        return NULL;

    if (rLen > inputLen - pos)
        return NULL;

    size_t rPos = pos;
    pos += rLen;

    if (pos >= inputLen || input[pos++] != 0x02)
        return NULL;

    if (!ReadLaxDERLength(input, inputLen, pos, sLen))
        return NULL;

    if (sLen > inputLen - pos)
        return NULL;

    size_t sPos = pos;

    while (rLen > 0 && input[rPos] == 0) {
        ++rPos;
        --rLen;
    }

    while (sLen > 0 && input[sPos] == 0) {
        ++sPos;
        --sLen;
    }

    if (rLen > 32 || sLen > 32)
        return NULL;

    BIGNUM* r = BN_bin2bn(input + rPos, rLen, NULL);
    BIGNUM* s = BN_bin2bn(input + sPos, sLen, NULL);

    if (r == NULL)
        r = BN_new();
    if (s == NULL)
        s = BN_new();

    if (r == NULL || s == NULL) {
        BN_free(r);
        BN_free(s);
        return NULL;
    }

    if (rLen == 0)
        BN_zero(r);
    if (sLen == 0)
        BN_zero(s);

    ECDSA_SIG* parsed = ECDSA_SIG_new();
    if (parsed == NULL || !SetECDSASigValues(parsed, r, s)) {
        BN_free(r);
        BN_free(s);
        ECDSA_SIG_free(parsed);
        return NULL;
    }

    return parsed;
}

bool CECKey::Verify(const uint256& hash, const std::vector<unsigned char>& vchSig)
{
    ECDSA_SIG* normSig = ParseLaxDERSignature(vchSig);
    if (normSig == NULL)
        return false;

    unsigned char* normDer = NULL;
    int derLen = i2d_ECDSA_SIG(normSig, &normDer);
    ECDSA_SIG_free(normSig);

    if (derLen <= 0)
        return false;

    bool result =
        ECDSA_verify(
            0,
            (unsigned char*)&hash,
            sizeof(hash),
            normDer,
            derLen,
            pkey
        ) == 1;

    OPENSSL_free(normDer);
    return result;
}

bool CECKey::Recover(const uint256& hash, const unsigned char* p64, int rec)
{
    if (rec < 0 || rec >= 3)
        return false;
    ECDSA_SIG* sig = ECDSA_SIG_new();
    BIGNUM* sig_r = BN_bin2bn(&p64[0], 32, NULL);
    BIGNUM* sig_s = BN_bin2bn(&p64[32], 32, NULL);
    if (sig == NULL || sig_r == NULL || sig_s == NULL || !SetECDSASigValues(sig, sig_r, sig_s)) {
        BN_free(sig_r);
        BN_free(sig_s);
        ECDSA_SIG_free(sig);
        return false;
    }
    bool ret = ECDSA_SIG_recover_key_GFp(pkey, sig, (unsigned char*)&hash, sizeof(hash), rec, 0) == 1;
    ECDSA_SIG_free(sig);
    return ret;
}

bool CECKey::TweakPublic(const unsigned char vchTweak[32])
{
    bool ret = true;
    BN_CTX* ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    BIGNUM* bnTweak = BN_CTX_get(ctx);
    BIGNUM* bnOrder = BN_CTX_get(ctx);
    BIGNUM* bnOne = BN_CTX_get(ctx);
    const EC_GROUP* group = EC_KEY_get0_group(pkey);
    EC_GROUP_get_order(group, bnOrder, ctx); // what a grossly inefficient way to get the (constant) group order...
    BN_bin2bn(vchTweak, 32, bnTweak);
    if (BN_cmp(bnTweak, bnOrder) >= 0)
        ret = false; // extremely unlikely
    EC_POINT* point = EC_POINT_dup(EC_KEY_get0_public_key(pkey), group);
    BN_one(bnOne);
    EC_POINT_mul(group, point, bnTweak, point, bnOne, ctx);
    if (EC_POINT_is_at_infinity(group, point))
        ret = false; // ridiculously unlikely
    EC_KEY_set_public_key(pkey, point);
    EC_POINT_free(point);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}

bool CECKey::SanityCheck()
{
    EC_KEY* pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (pkey == NULL)
        return false;
    EC_KEY_free(pkey);

    // TODO Is there more EC functionality that could be missing?
    return true;
}
