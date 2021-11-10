/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Glue code for libsodium tests
 *
 * Authors: Michalis Pappas <michalis.pappas@opensynergy.com>
 *
 * Copyright (c) 2021 OpenSynergy GmbH. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <sodium.h>
#include <stdio.h>
#include <uk/plat/console.h>
#include <uk_sodium_test_defs.h>

#define ANSI_GREEN UK_ANSI_MOD_COLORFG(UK_ANSI_COLOR_GREEN)
#define ANSI_RED   UK_ANSI_MOD_COLORFG(UK_ANSI_COLOR_RED)
#define ANSI_RESET UK_ANSI_MOD_RESET

#define RES_BUF_LEN_MAX 44 * 1024 /* > largest .exp file in tests/default/ */

FILE *fp_res;
char exp_buf[RES_BUF_LEN_MAX];
char res_buf[RES_BUF_LEN_MAX];
unsigned char *guard_page;

struct uk_sodium_test uk_tests[] = {
	{"aead_aes256gcm", aead_aes256gcm_res, aead_aes256gcm_xmain},
	{"aead_aes256gcm2", aead_aes256gcm2_res, aead_aes256gcm2_xmain},
	{"aead_chacha20poly1305", aead_chacha20poly1305_res, aead_chacha20poly1305_xmain},
	{"aead_chacha20poly13052", aead_chacha20poly13052_res, aead_chacha20poly13052_xmain},
	{"aead_xchacha20poly1305", aead_xchacha20poly1305_res, aead_xchacha20poly1305_xmain},
	{"auth", auth_res, auth_xmain},
	{"auth2", auth2_res, auth2_xmain},
	{"auth3", auth3_res, auth3_xmain},
	{"auth5", auth5_res, auth5_xmain},
	{"auth6", auth6_res, auth6_xmain},
	{"auth7", auth7_res, auth7_xmain},
	{"box", box_res, box_xmain},
	{"box2", box2_res, box2_xmain},
	{"box7", box7_res, box7_xmain},
	{"box8", box8_res, box8_xmain},
	{"box_easy", box_easy_res, box_easy_xmain},
	{"box_easy2", box_easy2_res, box_easy2_xmain},
	{"box_seal", box_seal_res, box_seal_xmain},
	{"box_seed", box_seed_res, box_seed_xmain},
	{"chacha20", chacha20_res, chacha20_xmain},
	{"codecs", codecs_res, codecs_xmain},
	{"core1", core1_res, core1_xmain},
	{"core2", core2_res, core2_xmain},
	{"core3", core3_res, core3_xmain},
	{"core4", core4_res, core4_xmain},
	{"core5", core5_res, core5_xmain},
	{"core6", core6_res, core6_xmain},
	{"ed25519_convert", ed25519_convert_res, ed25519_convert_xmain},
	{"generichash", generichash_res, generichash_xmain},
	{"generichash2", generichash2_res, generichash2_xmain},
	{"generichash3", generichash3_res, generichash3_xmain},
	{"hash", hash_res, hash_xmain},
	{"hash3", hash3_res, hash3_xmain},
	{"kdf", kdf_res, kdf_xmain},
	{"keygen", keygen_res, keygen_xmain},
	{"kx", kx_res, kx_xmain},
	{"metamorphic", metamorphic_res, metamorphic_xmain},
	{"misuse", misuse_res, misuse_xmain},
	{"onetimeauth", onetimeauth_res, onetimeauth_xmain},
	{"onetimeauth2", onetimeauth2_res, onetimeauth2_xmain},
	{"onetimeauth7", onetimeauth7_res, onetimeauth7_xmain},
	{"pwhash_argon2i", pwhash_argon2i_res, pwhash_argon2i_xmain},
	{"pwhash_argon2id", pwhash_argon2id_res, pwhash_argon2id_xmain},
	{"randombytes", randombytes_res, randombytes_xmain},
	{"scalarmult", scalarmult_res, scalarmult_xmain},
	{"scalarmult2", scalarmult2_res, scalarmult2_xmain},
	{"scalarmult5", scalarmult5_res, scalarmult5_xmain},
	{"scalarmult6", scalarmult6_res, scalarmult6_xmain},
	{"scalarmult7", scalarmult7_res, scalarmult7_xmain},
	{"scalarmult8", scalarmult8_res, scalarmult8_xmain},
	{"secretbox", secretbox_res, secretbox_xmain},
	{"secretbox2", secretbox2_res, secretbox2_xmain},
	{"secretbox7", secretbox7_res, secretbox7_xmain},
	{"secretbox8", secretbox8_res, secretbox8_xmain},
	{"secretbox_easy", secretbox_easy_res, secretbox_easy_xmain},
	{"secretbox_easy2", secretbox_easy2_res, secretbox_easy2_xmain},
	{"secretstream", secretstream_res, secretstream_xmain},
	{"shorthash", shorthash_res, shorthash_xmain},
	{"sign", sign_res, sign_xmain},
	{"sodium_core", sodium_core_res, sodium_core_xmain},
	{"sodium_utils", sodium_utils_res, sodium_utils_xmain},
	{"sodium_utils2", sodium_utils2_res, sodium_utils2_xmain},
	{"sodium_utils2", sodium_utils3_res, sodium_utils3_xmain},
	{"sodium_version", sodium_version_res, sodium_version_xmain},
	{"stream", stream_res, stream_xmain},
	{"stream2", stream2_res, stream2_xmain},
	{"stream3", stream3_res, stream3_xmain},
	{"stream4", stream4_res, stream4_xmain},
	{"verify1", verify1_res, verify1_xmain},
};

/* Replacement for libsodium's cmptest function (test/default/cmptest.h) */
int uk_sodium_cmptest(struct uk_sodium_test *test)
{
	FILE *fp_exp = NULL;
	unsigned char *gp = NULL;
	int c;
	int res = 0;

	/* Prepare guard page */
	if (!(gp = (unsigned char *) sodium_malloc(0))) {
		perror("sodium_malloc()");
		res = -1;
		goto out;
	}
	guard_page = gp + 1;

	/* Prepare expected result buffer */
	if (!(fp_exp = fmemopen(test->exp, sizeof(exp_buf), "r"))) {
		perror("fmemopen");
		res = -1;
		goto out;
	}
	fprintf(fp_exp, "%s", test->exp);

	/* Prepare actual result buffer */
	if (!(fp_res = fmemopen(res_buf, sizeof(res_buf), "w+"))) {
		perror("fmemopen");
		res = -1;
		goto out;
	}

	/* Execute test */
	if (test->func() != 0) {
		res = -1;
		goto out;
	}

	/* Compare */
	rewind(fp_exp);
	rewind(fp_res);
	while ((c = fgetc(fp_res)) != EOF) {
		if (c != fgetc(fp_exp)) {
			res = -1;
			goto out;
		}
	}

out:
	if (gp)
		sodium_free(gp);

	if (fp_res)
		fclose(fp_res);

	if (fp_exp)
		fclose(fp_exp);

	return res;
}

int uk_sodium_run_tests(void)
{
	int ntests = sizeof(uk_tests) / sizeof(uk_tests[0]);
	unsigned int npass = 0;
	unsigned int nfail = 0;

	if (sodium_init() != 0) {
		printf("Could not init sodium\n");
		return -1;
	}

	for (int i = 0; i < ntests; i++) {
		if (!uk_sodium_cmptest(&uk_tests[i])) {
			printf(ANSI_GREEN"PASS"ANSI_RESET": ");
			npass++;
		} else {
			printf(ANSI_RED"FAIL"ANSI_RESET": ");
			nfail++;
		}
		printf("%s\n", uk_tests[i].name);
	}
	printf(ANSI_GREEN"=============================================="
	       ANSI_RESET"\n");
	printf(ANSI_GREEN"Testsuite summary for libsodium "VERSION""ANSI_RESET"\n");
	printf(ANSI_GREEN"=============================================="
	       ANSI_RESET"\n");
	printf("# TOTAL: %d\n", ntests);
	if (npass)
		printf(ANSI_GREEN"# PASS: %d"ANSI_RESET"\n", npass);
	else
		printf("# PASS: %d\n", npass);
	if (nfail)
		printf(ANSI_RED"# FAIL: %d"ANSI_RESET"\n", nfail);
	else
		printf("# FAIL: %d\n", nfail);
	printf(ANSI_GREEN"=============================================="
	       ANSI_RESET"\n");

	return nfail;
}
