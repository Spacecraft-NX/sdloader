/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef FUSEE_SE_H
#define FUSEE_SE_H

#define SE_BASE 0x70012000
#define MAKE_SE_REG(n) MAKE_REG32(SE_BASE + n)

#define KEYSLOT_SWITCH_LP0TZRAMKEY 0x2
#define KEYSLOT_SWITCH_SRKGENKEY 0x8
#define KEYSLOT_SWITCH_PACKAGE2KEY 0x8
#define KEYSLOT_SWITCH_TEMPKEY 0x9
#define KEYSLOT_SWITCH_SESSIONKEY 0xA
#define KEYSLOT_SWITCH_RNGKEY 0xB
#define KEYSLOT_SWITCH_MASTERKEY 0xC
#define KEYSLOT_SWITCH_DEVICEKEY 0xD

/* This keyslot was added in 4.0.0. */
#define KEYSLOT_SWITCH_4XNEWDEVICEKEYGENKEY 0xD
#define KEYSLOT_SWITCH_4XNEWCONSOLEKEYGENKEY 0xE
#define KEYSLOT_SWITCH_4XOLDDEVICEKEY 0xF

/* This keyslot was added in 5.0.0. */
#define KEYSLOT_SWITCH_5XNEWDEVICEKEYGENKEY 0xA

#define KEYSLOT_AES_MAX 0x10
#define KEYSLOT_RSA_MAX 0x2

#define KEYSIZE_AES_MAX 0x20
#define KEYSIZE_RSA_MAX 0x100

// SE_CONFIG_0
#define ENC_MODE_SHIFT	(24)
// SHA params
#define   ENC_MODE_SHA1		(1 << ENC_MODE_SHIFT)
#define   ENC_MODE_SHA224	(4 << ENC_MODE_SHIFT)
#define   ENC_MODE_SHA256	(5 << ENC_MODE_SHIFT)
#define   ENC_MODE_SHA384	(6 << ENC_MODE_SHIFT)
#define   ENC_MODE_SHA512	(7 << ENC_MODE_SHIFT)
// AES params
#define   ENC_MODE_KEY128	(0 << ENC_MODE_SHIFT)
#define   ENC_MODE_KEY192	(1 << ENC_MODE_SHIFT)
#define   ENC_MODE_KEY256	(2 << ENC_MODE_SHIFT)
#define DEC_MODE_SHIFT	(16)
#define   DEC_MODE_KEY128	(0 << DEC_MODE_SHIFT)
#define   DEC_MODE_KEY192	(1 << DEC_MODE_SHIFT)
#define   DEC_MODE_KEY256	(2 << DEC_MODE_SHIFT)
#define ENC_ALG_SHIFT	(12)
#define   ENC_ALG_NOP		(0 << ENC_ALG_SHIFT)
#define   ENC_ALG_AES_ENC	(1 << ENC_ALG_SHIFT)
#define   ENC_ALG_RNG		(2 << ENC_ALG_SHIFT)
#define   ENC_ALG_SHA		(3 << ENC_ALG_SHIFT)
#define   ENC_ALG_RSA		(4 << ENC_ALG_SHIFT)
#define DEC_ALG_SHIFT	(8)
#define   DEC_ALG_NOP		(0 << DEC_ALG_SHIFT)
#define   DEC_ALG_AES_DEC	(1 << DEC_ALG_SHIFT)
#define DST_SHIFT	(2)
#define   DST_MEMORY		(0 << DST_SHIFT)
#define   DST_HASHREG		(1 << DST_SHIFT)
#define   DST_KEYTAB		(2 << DST_SHIFT)
#define   DST_SRK			(3 << DST_SHIFT)
#define   DST_RSAREG		(4 << DST_SHIFT)

// SE_CRYPTO_CONFIG_0
#define MEMIF_SHIFT			(31)
#define   MEMIF_AHB						(0 << MEMIF_SHIFT)
#define   MEMIF_MCCIF					(1 << MEMIF_SHIFT)
#define KEY_INDEX_SHIFT		(24)
#define CTR_CNTN_SHIFT		(11)
#define CORE_SEL_SHIFT		(8)
#define   CORE_SEL_DECRYPT				(0 << CORE_SEL_SHIFT)
#define   CORE_SEL_ENCRYPT				(1 << CORE_SEL_SHIFT)
#define IV_SELECT_SHIFT		(7)
#define   IV_SELECT_ORIGINAL			(0 << IV_SELECT_SHIFT)
#define   IV_SELECT_UPDATED				(1 << IV_SELECT_SHIFT)
#define VCTRAM_SEL_SHIFT	(5)
#define   VCTRAM_SEL_MEMORY				(0 << VCTRAM_SEL_SHIFT)
#define   VCTRAM_SEL_INIT_AESOUT		(2 << VCTRAM_SEL_SHIFT)
#define   VCTRAM_SEL_INIT_PREV_MEMORY	(3 << VCTRAM_SEL_SHIFT)
#define INPUT_SEL_SHIFT		(3)
#define   INPUT_SEL_MEMORY				(0 << INPUT_SEL_SHIFT)
#define   INPUT_SEL_RANDOM				(1 << INPUT_SEL_SHIFT)
#define   INPUT_SEL_INIT_AESOUT			(2 << INPUT_SEL_SHIFT)
#define   INPUT_SEL_LINEAR_CTR			(3 << INPUT_SEL_SHIFT)
#define XOR_POS_SHIFT		(1)
#define   XOR_POS_BYPASS				(0 << XOR_POS_SHIFT)
#define   XOR_POS_TOP					(2 << XOR_POS_SHIFT)
#define   XOR_POS_BOTTOM				(3 << XOR_POS_SHIFT)
#define HASH_ENB_SHIFT		(0)
#define   HASH_ENB_DISABLE				(0 << HASH_ENB_SHIFT)
#define   HASH_ENB_ENABLE				(1 << HASH_ENB_SHIFT)

#define SE_CRYPTO_CONFIG_AES_ECB (XOR_POS_BYPASS | INPUT_SEL_MEMORY)
#define SE_CRYPTO_CONFIG_AES_CBC_ENCRYPT (XOR_POS_TOP | INPUT_SEL_MEMORY | IV_SELECT_ORIGINAL | VCTRAM_SEL_INIT_AESOUT | CORE_SEL_ENCRYPT)
#define SE_CRYPTO_CONFIG_AES_CBC_DECRYPT (XOR_POS_BOTTOM | INPUT_SEL_MEMORY | IV_SELECT_ORIGINAL | VCTRAM_SEL_INIT_PREV_MEMORY | CORE_SEL_DECRYPT)
#define SE_CRYPTO_CONFIG_AES_OFB (XOR_POS_BOTTOM | INPUT_SEL_INIT_AESOUT | IV_SELECT_ORIGINAL | VCTRAM_SEL_MEMORY)
#define SE_CRYPTO_CONFIG_AES_CTR (XOR_POS_BOTTOM | INPUT_SEL_LINEAR_CTR)

#define HASH_DISABLE (0x0)
#define HASH_ENABLE (0x1)

#define OP_ABORT 0
#define OP_START 1
#define OP_RESTART 2
#define OP_CTX_SAVE 3
#define OP_RESTART_IN 4

#define CTX_SAVE_SRC_SHIFT 29
#define CTX_SAVE_SRC_STICKY_BITS (0 << CTX_SAVE_SRC_SHIFT)
#define CTX_SAVE_SRC_KEYTABLE_AES (2 << CTX_SAVE_SRC_SHIFT)
#define CTX_SAVE_SRC_KEYTABLE_RSA (1 << CTX_SAVE_SRC_SHIFT)
#define CTX_SAVE_SRC_MEM (4 << CTX_SAVE_SRC_SHIFT)
#define CTX_SAVE_SRC_SRK (6 << CTX_SAVE_SRC_SHIFT)

#define CTX_SAVE_KEY_LOW_BITS 0
#define CTX_SAVE_KEY_HIGH_BITS 1
#define CTX_SAVE_KEY_ORIGINAL_IV 2
#define CTX_SAVE_KEY_UPDATED_IV 3

#define CTX_SAVE_STICKY_BIT_INDEX_SHIFT 24
#define CTX_SAVE_KEY_INDEX_SHIFT 8
#define CTX_SAVE_RSA_KEY_INDEX_SHIFT 16
#define CTX_SAVE_RSA_KEY_BLOCK_INDEX_SHIFT 12

#define RSA_2048_BYTES 0x100

typedef struct {
    uint32_t SE_SE_SECURITY;
    uint32_t SE_TZRAM_SECURITY;
    uint32_t SE_OPERATION;
    uint32_t SE_INT_ENABLE;
    uint32_t SE_INT_STATUS;
    uint32_t SE_CONFIG;
    uint32_t SE_IN_LL_ADDR;
    uint32_t SE_IN_CUR_BYTE_ADDR;
    uint32_t SE_IN_CUR_LL_ID;
    uint32_t SE_OUT_LL_ADDR;
    uint32_t SE_OUT_CUR_BYTE_ADDR;
    uint32_t SE_OUT_CUR_LL_ID;
    uint32_t SE_HASH_RESULT[0x10];
    uint32_t SE_CTX_SAVE_CONFIG;
    uint32_t _0x74[0x63];
    uint32_t SE_SHA_CONFIG;
    uint32_t SE_SHA_MSG_LENGTH[0x4];
    uint32_t SE_SHA_MSG_LEFT[0x4];
    uint32_t _0x224[0x17];
    uint32_t SE_CRYPTO_SECURITY_PERKEY;
    uint32_t SE_CRYPTO_KEYTABLE_ACCESS[0x10];
    uint32_t _0x2C4[0x10];
    uint32_t SE_CRYPTO_CONFIG;
    uint32_t SE_CRYPTO_LINEAR_CTR[0x4];
    uint32_t SE_CRYPTO_LAST_BLOCK;
    uint32_t SE_CRYPTO_KEYTABLE_ADDR;
    uint32_t SE_CRYPTO_KEYTABLE_DATA;
    uint32_t _0x324[0x3];
    uint32_t SE_CRYPTO_KEYTABLE_DST;
    uint32_t _0x334[0x3];
    uint32_t SE_RNG_CONFIG;
    uint32_t SE_RNG_SRC_CONFIG;
    uint32_t SE_RNG_RESEED_INTERVAL;
    uint32_t _0x34C[0x2D];
    uint32_t SE_RSA_CONFIG;
    uint32_t SE_RSA_KEY_SIZE;
    uint32_t SE_RSA_EXP_SIZE;
    uint32_t SE_RSA_SECURITY_PERKEY;
    uint32_t SE_RSA_KEYTABLE_ACCESS[0x2];
    uint32_t _0x418[0x2];
    uint32_t SE_RSA_KEYTABLE_ADDR;
    uint32_t SE_RSA_KEYTABLE_DATA;
    uint32_t SE_RSA_OUTPUT[0x40];
    uint32_t _0x528[0xB6];
    uint32_t SE_STATUS;
    uint32_t SE_ERR_STATUS;
    uint32_t SE_MISC;
    uint32_t SE_SPARE;
    uint32_t SE_ENTROPY_DEBUG_COUNTER;
    uint32_t _0x814;
    uint32_t _0x818;
    uint32_t _0x81C;
    uint32_t _0x820[0x5F8];
} tegra_se_t;

typedef struct {
    uint32_t address;
    uint32_t size;
} se_addr_info_t;

typedef struct {
    uint32_t num_entries; /* Set to total entries - 1 */
    se_addr_info_t addr_info; /* This should really be an array...but for our use case it works. */
} se_ll_t;

static inline volatile tegra_se_t *se_get_regs(void) {
    return (volatile tegra_se_t *)SE_BASE;
}

void NOINLINE ll_init(volatile se_ll_t *ll, void *buffer, size_t size);
void trigger_se_blocking_op(unsigned int op, void *dst, size_t dst_size, const void *src, size_t src_size);

void se_check_error_status_reg(void);
void se_check_for_error(void);
void se_trigger_interrupt(void);

void se_validate_stored_vector(void);
void se_generate_stored_vector(void);

void se_verify_flags_cleared(void);

void set_aes_keyslot_flags(unsigned int keyslot, unsigned int flags);
void set_rsa_keyslot_flags(unsigned int keyslot, unsigned int flags);
void clear_aes_keyslot(unsigned int keyslot);
void clear_rsa_keyslot(unsigned int keyslot);

void set_aes_keyslot(unsigned int keyslot, const void *key, size_t key_size);
void decrypt_data_into_keyslot(unsigned int keyslot_dst, unsigned int keyslot_src, const void *wrapped_key, size_t wrapped_key_size);
void set_rsa_keyslot(unsigned int keyslot, const void *modulus, size_t modulus_size, const void *exponent, size_t exp_size);
void set_aes_keyslot_iv(unsigned int keyslot, const void *iv, size_t iv_size);
void set_se_ctr(const void *ctr);

/* Secure AES API */
void se_aes_128_xts_nintendo_decrypt(unsigned int keyslot_1, unsigned int keyslot_2, unsigned int base_sector, void *dst, const void *src, size_t size, unsigned int sector_size);
void se_aes_128_xts_nintendo_encrypt(unsigned int keyslot_1, unsigned int keyslot_2, unsigned int base_sector, void *dst, const void *src, size_t size, unsigned int sector_size);
void se_compute_aes_128_cmac(unsigned int keyslot, void *cmac, size_t cmac_size, const void *data, size_t data_size);
void se_compute_aes_256_cmac(unsigned int keyslot, void *cmac, size_t cmac_size, const void *data, size_t data_size);
void se_aes_128_ecb_encrypt_block(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size);
void se_aes_256_ecb_encrypt_block(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size);
void se_aes_ctr_crypt(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size, const void *ctr, size_t ctr_size);
void se_aes_ecb_decrypt_block(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size);
void se_aes_cbc_encrypt(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size, const void *iv);
void se_aes_cbc_decrypt(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size, const void *iv);
void se_aes_256_cbc_encrypt(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size, const void *iv);

/* Hash API */
void se_calculate_sha256(void *dst, const void *src, size_t src_size);

/* RSA API */
void se_get_exp_mod_output(void *buf, size_t size);
void se_synchronous_exp_mod(unsigned int keyslot, void *dst, size_t dst_size, const void *src, size_t src_size);
bool se_rsa2048_pss_verify(const void *signature, size_t signature_size, const void *modulus, size_t modulus_size, const void *data, size_t data_size);

/* RNG API */
void se_initialize_rng(unsigned int keyslot);
void se_generate_random(unsigned int keyslot, void *dst, size_t size);

#endif
