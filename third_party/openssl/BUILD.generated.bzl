# This file is created by generate_build_files.py. Do not edit manually.

ssl_headers = [
    "linux-x86_64/include/openssl/dtls1.h",
    "linux-x86_64/include/openssl/ssl.h",
    "linux-x86_64/include/openssl/ssl23.h",
    "linux-x86_64/include/openssl/ssl3.h",
    "linux-x86_64/include/openssl/tls1.h",
]

ssl_internal_headers = [
    "src/ssl/dtls1.h",
    "src/ssl/kssl.h",
    "src/ssl/kssl_lcl.h",
    "src/ssl/srtp.h",
    "src/ssl/ssl.h",
    "src/ssl/ssl2.h",
    "src/ssl/ssl23.h",
    "src/ssl/ssl3.h",
    "src/ssl/ssl_locl.h",
    "src/ssl/tls1.h",
]

ssl_sources = [
    "src/ssl/bio_ssl.c",
    "src/ssl/d1_both.c",
    "src/ssl/d1_clnt.c",
    "src/ssl/d1_lib.c",
    "src/ssl/d1_meth.c",
    "src/ssl/d1_pkt.c",
    "src/ssl/d1_srtp.c",
    "src/ssl/d1_srvr.c",
    "src/ssl/kssl.c",
    "src/ssl/s23_clnt.c",
    "src/ssl/s23_lib.c",
    "src/ssl/s23_meth.c",
    "src/ssl/s23_pkt.c",
    "src/ssl/s23_srvr.c",
    "src/ssl/s2_clnt.c",
    "src/ssl/s2_enc.c",
    "src/ssl/s2_lib.c",
    "src/ssl/s2_meth.c",
    "src/ssl/s2_pkt.c",
    "src/ssl/s2_srvr.c",
    "src/ssl/s3_both.c",
    "src/ssl/s3_cbc.c",
    "src/ssl/s3_clnt.c",
    "src/ssl/s3_enc.c",
    "src/ssl/s3_lib.c",
    "src/ssl/s3_meth.c",
    "src/ssl/s3_pkt.c",
    "src/ssl/s3_srvr.c",
    "src/ssl/ssl_algs.c",
    "src/ssl/ssl_asn1.c",
    "src/ssl/ssl_cert.c",
    "src/ssl/ssl_ciph.c",
    "src/ssl/ssl_conf.c",
    "src/ssl/ssl_err.c",
    "src/ssl/ssl_err2.c",
    "src/ssl/ssl_lib.c",
    "src/ssl/ssl_rsa.c",
    "src/ssl/ssl_sess.c",
    "src/ssl/ssl_stat.c",
    "src/ssl/ssl_txt.c",
    "src/ssl/ssl_utst.c",
    "src/ssl/t1_clnt.c",
    "src/ssl/t1_enc.c",
    "src/ssl/t1_ext.c",
    "src/ssl/t1_lib.c",
    "src/ssl/t1_meth.c",
    "src/ssl/t1_reneg.c",
    "src/ssl/t1_srvr.c",
    "src/ssl/t1_trce.c",
    "src/ssl/tls_srp.c",
]

crypto_headers = [
    "linux-x86_64/include/openssl/aes.h",
    "linux-x86_64/include/openssl/asn1.h",
    "linux-x86_64/include/openssl/asn1_mac.h",
    "linux-x86_64/include/openssl/asn1t.h",
    "linux-x86_64/include/openssl/bio.h",
    "linux-x86_64/include/openssl/blowfish.h",
    "linux-x86_64/include/openssl/bn.h",
    "linux-x86_64/include/openssl/buffer.h",
    "linux-x86_64/include/openssl/camellia.h",
    "linux-x86_64/include/openssl/cast.h",
    "linux-x86_64/include/openssl/cmac.h",
    "linux-x86_64/include/openssl/cms.h",
    "linux-x86_64/include/openssl/comp.h",
    "linux-x86_64/include/openssl/conf.h",
    "linux-x86_64/include/openssl/conf_api.h",
    "linux-x86_64/include/openssl/crypto.h",
    "linux-x86_64/include/openssl/des.h",
    "linux-x86_64/include/openssl/des_old.h",
    "linux-x86_64/include/openssl/dh.h",
    "linux-x86_64/include/openssl/dsa.h",
    "linux-x86_64/include/openssl/dso.h",
    "linux-x86_64/include/openssl/e_os2.h",
    "linux-x86_64/include/openssl/ebcdic.h",
    "linux-x86_64/include/openssl/ec.h",
    "linux-x86_64/include/openssl/ecdh.h",
    "linux-x86_64/include/openssl/ecdsa.h",
    "linux-x86_64/include/openssl/engine.h",
    "linux-x86_64/include/openssl/err.h",
    "linux-x86_64/include/openssl/evp.h",
    "linux-x86_64/include/openssl/hmac.h",
    "linux-x86_64/include/openssl/idea.h",
    "linux-x86_64/include/openssl/krb5_asn.h",
    "linux-x86_64/include/openssl/kssl.h",
    "linux-x86_64/include/openssl/lhash.h",
    "linux-x86_64/include/openssl/md4.h",
    "linux-x86_64/include/openssl/md5.h",
    "linux-x86_64/include/openssl/mdc2.h",
    "linux-x86_64/include/openssl/modes.h",
    "linux-x86_64/include/openssl/obj_mac.h",
    "linux-x86_64/include/openssl/objects.h",
    "linux-x86_64/include/openssl/ocsp.h",
    "linux-x86_64/include/openssl/opensslconf.h",
    "linux-x86_64/include/openssl/opensslv.h",
    "linux-x86_64/include/openssl/ossl_typ.h",
    "linux-x86_64/include/openssl/pem.h",
    "linux-x86_64/include/openssl/pem2.h",
    "linux-x86_64/include/openssl/pkcs12.h",
    "linux-x86_64/include/openssl/pkcs7.h",
    "linux-x86_64/include/openssl/pqueue.h",
    "linux-x86_64/include/openssl/rand.h",
    "linux-x86_64/include/openssl/rc2.h",
    "linux-x86_64/include/openssl/rc4.h",
    "linux-x86_64/include/openssl/ripemd.h",
    "linux-x86_64/include/openssl/rsa.h",
    "linux-x86_64/include/openssl/safestack.h",
    "linux-x86_64/include/openssl/seed.h",
    "linux-x86_64/include/openssl/sha.h",
    "linux-x86_64/include/openssl/srp.h",
    "linux-x86_64/include/openssl/srtp.h",
    "linux-x86_64/include/openssl/ssl2.h",
    "linux-x86_64/include/openssl/stack.h",
    "linux-x86_64/include/openssl/symhacks.h",
    "linux-x86_64/include/openssl/ts.h",
    "linux-x86_64/include/openssl/txt_db.h",
    "linux-x86_64/include/openssl/ui.h",
    "linux-x86_64/include/openssl/ui_compat.h",
    "linux-x86_64/include/openssl/whrlpool.h",
    "linux-x86_64/include/openssl/x509.h",
    "linux-x86_64/include/openssl/x509_vfy.h",
    "linux-x86_64/include/openssl/x509v3.h",
]

crypto_internal_headers = [
    # To be fixed
    "src/e_os.h",
    # Done
    "src/crypto/aes/aes.h",
    "src/crypto/aes/aes_locl.h",
    "src/crypto/arm_arch.h",
    "src/crypto/asn1/asn1.h",
    "src/crypto/asn1/asn1_locl.h",
    "src/crypto/asn1/asn1_mac.h",
    "src/crypto/asn1/asn1t.h",
    "src/crypto/asn1/charmap.h",
    "src/crypto/bf/bf_locl.h",
    "src/crypto/bf/bf_pi.h",
    "src/crypto/bf/blowfish.h",
    "src/crypto/bio/bio.h",
    "src/crypto/bio/bio_lcl.h",
    "src/crypto/bn/bn.h",
    "src/crypto/bn/bn_lcl.h",
    "src/crypto/bn/bn_prime.h",
    "src/crypto/bn/rsaz_exp.h",
    "src/crypto/buffer/buffer.h",
    "src/crypto/camellia/camellia.h",
    "src/crypto/camellia/cmll_locl.h",
    "src/crypto/cast/cast.h",
    "src/crypto/cast/cast_lcl.h",
    "src/crypto/cast/cast_s.h",
    "src/crypto/cmac/cmac.h",
    "src/crypto/cms/cms.h",
    "src/crypto/cms/cms_lcl.h",
    "src/crypto/comp/comp.h",
    "src/crypto/conf/conf.h",
    "src/crypto/conf/conf_api.h",
    "src/crypto/conf/conf_def.h",
    "src/crypto/constant_time_locl.h",
    "src/crypto/cryptlib.h",
    "src/crypto/crypto.h",
    "src/crypto/des/des.h",
    "src/crypto/des/des_locl.h",
    "src/crypto/des/des_old.h",
    "src/crypto/des/des_ver.h",
    "src/crypto/des/rpc_des.h",
    "src/crypto/des/spr.h",
    "src/crypto/dh/dh.h",
    "src/crypto/dsa/dsa.h",
    "src/crypto/dsa/dsa_locl.h",
    "src/crypto/dso/dso.h",
    "src/crypto/ebcdic.h",
    "src/crypto/ec/ec.h",
    "src/crypto/ec/ec_lcl.h",
    "src/crypto/ecdh/ecdh.h",
    "src/crypto/ecdh/ech_locl.h",
    "src/crypto/ecdsa/ecdsa.h",
    "src/crypto/ecdsa/ecs_locl.h",
    "src/crypto/engine/eng_int.h",
    "src/crypto/engine/engine.h",
    "src/crypto/err/err.h",
    "src/crypto/evp/evp.h",
    "src/crypto/evp/evp_locl.h",
    "src/crypto/fips_err.h",
    "src/crypto/hmac/hmac.h",
    "src/crypto/idea/idea.h",
    "src/crypto/idea/idea_lcl.h",
    "src/crypto/jpake/jpake.h",
    "src/crypto/krb5/krb5_asn.h",
    "src/crypto/lhash/lhash.h",
    "src/crypto/md2/md2.h",
    "src/crypto/md32_common.h",
    "src/crypto/md4/md4.h",
    "src/crypto/md4/md4_locl.h",
    "src/crypto/md5/md5.h",
    "src/crypto/md5/md5_locl.h",
    "src/crypto/mdc2/mdc2.h",
    "src/crypto/modes/modes.h",
    "src/crypto/modes/modes_lcl.h",
    "src/crypto/o_dir.h",
    "src/crypto/o_str.h",
    "src/crypto/o_time.h",
    "src/crypto/objects/obj_dat.h",
    "src/crypto/objects/obj_mac.h",
    "src/crypto/objects/obj_xref.h",
    "src/crypto/objects/objects.h",
    "src/crypto/ocsp/ocsp.h",
    "src/crypto/opensslv.h",
    "src/crypto/ossl_typ.h",
    "src/crypto/pem/pem.h",
    "src/crypto/pem/pem2.h",
    "src/crypto/pkcs12/pkcs12.h",
    "src/crypto/pkcs7/pkcs7.h",
    "src/crypto/ppc_arch.h",
    "src/crypto/pqueue/pqueue.h",
    "src/crypto/rand/rand.h",
    "src/crypto/rand/rand_lcl.h",
    "src/crypto/rc2/rc2.h",
    "src/crypto/rc2/rc2_locl.h",
    "src/crypto/rc4/rc4.h",
    "src/crypto/rc4/rc4_locl.h",
    "src/crypto/rc5/rc5.h",
    "src/crypto/rc5/rc5_locl.h",
    "src/crypto/ripemd/ripemd.h",
    "src/crypto/ripemd/rmd_locl.h",
    "src/crypto/ripemd/rmdconst.h",
    "src/crypto/rsa/rsa.h",
    "src/crypto/rsa/rsa_locl.h",
    "src/crypto/seed/seed.h",
    "src/crypto/seed/seed_locl.h",
    "src/crypto/sha/sha.h",
    "src/crypto/sha/sha_locl.h",
    "src/crypto/sparc_arch.h",
    "src/crypto/srp/srp.h",
    "src/crypto/srp/srp_grps.h",
    "src/crypto/srp/srp_lcl.h",
    "src/crypto/stack/safestack.h",
    "src/crypto/stack/stack.h",
    "src/crypto/store/store.h",
    "src/crypto/store/str_locl.h",
    "src/crypto/symhacks.h",
    "src/crypto/ts/ts.h",
    "src/crypto/txt_db/txt_db.h",
    "src/crypto/ui/ui.h",
    "src/crypto/ui/ui_compat.h",
    "src/crypto/ui/ui_locl.h",
    "src/crypto/vms_rms.h",
    "src/crypto/whrlpool/whrlpool.h",
    "src/crypto/whrlpool/wp_locl.h",
    "src/crypto/x509/vpm_int.h",
    "src/crypto/x509/x509.h",
    "src/crypto/x509/x509_vfy.h",
    "src/crypto/x509v3/ext_dat.h",
    "src/crypto/x509v3/pcy_int.h",
    "src/crypto/x509v3/x509v3.h",
]

crypto_sources = [
    "src/crypto/aes/aes_cfb.c",
    "src/crypto/aes/aes_ctr.c",
    "src/crypto/aes/aes_ecb.c",
    "src/crypto/aes/aes_ige.c",
    "src/crypto/aes/aes_misc.c",
    "src/crypto/aes/aes_ofb.c",
    "src/crypto/aes/aes_wrap.c",
    "src/crypto/asn1/a_bitstr.c",
    "src/crypto/asn1/a_bool.c",
    "src/crypto/asn1/a_bytes.c",
    "src/crypto/asn1/a_d2i_fp.c",
    "src/crypto/asn1/a_digest.c",
    "src/crypto/asn1/a_dup.c",
    "src/crypto/asn1/a_enum.c",
    "src/crypto/asn1/a_gentm.c",
    "src/crypto/asn1/a_i2d_fp.c",
    "src/crypto/asn1/a_int.c",
    "src/crypto/asn1/a_mbstr.c",
    "src/crypto/asn1/a_object.c",
    "src/crypto/asn1/a_octet.c",
    "src/crypto/asn1/a_print.c",
    "src/crypto/asn1/a_set.c",
    "src/crypto/asn1/a_sign.c",
    "src/crypto/asn1/a_strex.c",
    "src/crypto/asn1/a_strnid.c",
    "src/crypto/asn1/a_time.c",
    "src/crypto/asn1/a_type.c",
    "src/crypto/asn1/a_utctm.c",
    "src/crypto/asn1/a_utf8.c",
    "src/crypto/asn1/a_verify.c",
    "src/crypto/asn1/ameth_lib.c",
    "src/crypto/asn1/asn1_err.c",
    "src/crypto/asn1/asn1_gen.c",
    "src/crypto/asn1/asn1_lib.c",
    "src/crypto/asn1/asn1_par.c",
    "src/crypto/asn1/asn_mime.c",
    "src/crypto/asn1/asn_moid.c",
    "src/crypto/asn1/asn_pack.c",
    "src/crypto/asn1/bio_asn1.c",
    "src/crypto/asn1/bio_ndef.c",
    "src/crypto/asn1/d2i_pr.c",
    "src/crypto/asn1/d2i_pu.c",
    "src/crypto/asn1/evp_asn1.c",
    "src/crypto/asn1/f_enum.c",
    "src/crypto/asn1/f_int.c",
    "src/crypto/asn1/f_string.c",
    "src/crypto/asn1/i2d_pr.c",
    "src/crypto/asn1/i2d_pu.c",
    "src/crypto/asn1/n_pkey.c",
    "src/crypto/asn1/nsseq.c",
    "src/crypto/asn1/p5_pbe.c",
    "src/crypto/asn1/p5_pbev2.c",
    "src/crypto/asn1/p8_pkey.c",
    "src/crypto/asn1/t_bitst.c",
    "src/crypto/asn1/t_crl.c",
    "src/crypto/asn1/t_pkey.c",
    "src/crypto/asn1/t_req.c",
    "src/crypto/asn1/t_spki.c",
    "src/crypto/asn1/t_x509.c",
    "src/crypto/asn1/t_x509a.c",
    "src/crypto/asn1/tasn_dec.c",
    "src/crypto/asn1/tasn_enc.c",
    "src/crypto/asn1/tasn_fre.c",
    "src/crypto/asn1/tasn_new.c",
    "src/crypto/asn1/tasn_prn.c",
    "src/crypto/asn1/tasn_typ.c",
    "src/crypto/asn1/tasn_utl.c",
    "src/crypto/asn1/x_algor.c",
    "src/crypto/asn1/x_attrib.c",
    "src/crypto/asn1/x_bignum.c",
    "src/crypto/asn1/x_crl.c",
    "src/crypto/asn1/x_exten.c",
    "src/crypto/asn1/x_info.c",
    "src/crypto/asn1/x_long.c",
    "src/crypto/asn1/x_name.c",
    "src/crypto/asn1/x_nx509.c",
    "src/crypto/asn1/x_pkey.c",
    "src/crypto/asn1/x_pubkey.c",
    "src/crypto/asn1/x_req.c",
    "src/crypto/asn1/x_sig.c",
    "src/crypto/asn1/x_spki.c",
    "src/crypto/asn1/x_val.c",
    "src/crypto/asn1/x_x509.c",
    "src/crypto/asn1/x_x509a.c",
    "src/crypto/bf/bf_cfb64.c",
    "src/crypto/bf/bf_ecb.c",
    "src/crypto/bf/bf_enc.c",
    "src/crypto/bf/bf_ofb64.c",
    "src/crypto/bf/bf_skey.c",
    "src/crypto/bio/b_dump.c",
    "src/crypto/bio/b_print.c",
    "src/crypto/bio/b_sock.c",
    "src/crypto/bio/bf_buff.c",
    "src/crypto/bio/bf_nbio.c",
    "src/crypto/bio/bf_null.c",
    "src/crypto/bio/bio_cb.c",
    "src/crypto/bio/bio_err.c",
    "src/crypto/bio/bio_lib.c",
    "src/crypto/bio/bss_acpt.c",
    "src/crypto/bio/bss_bio.c",
    "src/crypto/bio/bss_conn.c",
    "src/crypto/bio/bss_dgram.c",
    "src/crypto/bio/bss_fd.c",
    "src/crypto/bio/bss_file.c",
    "src/crypto/bio/bss_log.c",
    "src/crypto/bio/bss_mem.c",
    "src/crypto/bio/bss_null.c",
    "src/crypto/bio/bss_sock.c",
    "src/crypto/bn/asm/x86_64-gcc.c",
    "src/crypto/bn/bn_add.c",
    "src/crypto/bn/bn_blind.c",
    "src/crypto/bn/bn_const.c",
    "src/crypto/bn/bn_ctx.c",
    "src/crypto/bn/bn_depr.c",
    "src/crypto/bn/bn_div.c",
    "src/crypto/bn/bn_err.c",
    "src/crypto/bn/bn_exp.c",
    "src/crypto/bn/bn_exp2.c",
    "src/crypto/bn/bn_gcd.c",
    "src/crypto/bn/bn_gf2m.c",
    "src/crypto/bn/bn_kron.c",
    "src/crypto/bn/bn_lib.c",
    "src/crypto/bn/bn_mod.c",
    "src/crypto/bn/bn_mont.c",
    "src/crypto/bn/bn_mpi.c",
    "src/crypto/bn/bn_mul.c",
    "src/crypto/bn/bn_nist.c",
    "src/crypto/bn/bn_prime.c",
    "src/crypto/bn/bn_print.c",
    "src/crypto/bn/bn_rand.c",
    "src/crypto/bn/bn_recp.c",
    "src/crypto/bn/bn_shift.c",
    "src/crypto/bn/bn_sqr.c",
    "src/crypto/bn/bn_sqrt.c",
    "src/crypto/bn/bn_word.c",
    "src/crypto/bn/bn_x931p.c",
    "src/crypto/bn/rsaz_exp.c",
    "src/crypto/buffer/buf_err.c",
    "src/crypto/buffer/buf_str.c",
    "src/crypto/buffer/buffer.c",
    "src/crypto/camellia/cmll_cfb.c",
    "src/crypto/camellia/cmll_ctr.c",
    "src/crypto/camellia/cmll_ecb.c",
    "src/crypto/camellia/cmll_misc.c",
    "src/crypto/camellia/cmll_ofb.c",
    "src/crypto/camellia/cmll_utl.c",
    "src/crypto/cast/c_cfb64.c",
    "src/crypto/cast/c_ecb.c",
    "src/crypto/cast/c_enc.c",
    "src/crypto/cast/c_ofb64.c",
    "src/crypto/cast/c_skey.c",
    "src/crypto/cmac/cm_ameth.c",
    "src/crypto/cmac/cm_pmeth.c",
    "src/crypto/cmac/cmac.c",
    "src/crypto/cms/cms_asn1.c",
    "src/crypto/cms/cms_att.c",
    "src/crypto/cms/cms_cd.c",
    "src/crypto/cms/cms_dd.c",
    "src/crypto/cms/cms_enc.c",
    "src/crypto/cms/cms_env.c",
    "src/crypto/cms/cms_err.c",
    "src/crypto/cms/cms_ess.c",
    "src/crypto/cms/cms_io.c",
    "src/crypto/cms/cms_kari.c",
    "src/crypto/cms/cms_lib.c",
    "src/crypto/cms/cms_pwri.c",
    "src/crypto/cms/cms_sd.c",
    "src/crypto/cms/cms_smime.c",
    "src/crypto/comp/c_rle.c",
    "src/crypto/comp/c_zlib.c",
    "src/crypto/comp/comp_err.c",
    "src/crypto/comp/comp_lib.c",
    "src/crypto/conf/conf_api.c",
    "src/crypto/conf/conf_def.c",
    "src/crypto/conf/conf_err.c",
    "src/crypto/conf/conf_lib.c",
    "src/crypto/conf/conf_mall.c",
    "src/crypto/conf/conf_mod.c",
    "src/crypto/conf/conf_sap.c",
    "src/crypto/cpt_err.c",
    "src/crypto/cryptlib.c",
    "src/crypto/cversion.c",
    "src/crypto/des/cbc_cksm.c",
    "src/crypto/des/cbc_enc.c",
    "src/crypto/des/cfb64ede.c",
    "src/crypto/des/cfb64enc.c",
    "src/crypto/des/cfb_enc.c",
    "src/crypto/des/des_enc.c",
    "src/crypto/des/des_old.c",
    "src/crypto/des/des_old2.c",
    "src/crypto/des/ecb3_enc.c",
    "src/crypto/des/ecb_enc.c",
    "src/crypto/des/ede_cbcm_enc.c",
    "src/crypto/des/enc_read.c",
    "src/crypto/des/enc_writ.c",
    "src/crypto/des/fcrypt.c",
    "src/crypto/des/fcrypt_b.c",
    "src/crypto/des/ofb64ede.c",
    "src/crypto/des/ofb64enc.c",
    "src/crypto/des/ofb_enc.c",
    "src/crypto/des/pcbc_enc.c",
    "src/crypto/des/qud_cksm.c",
    "src/crypto/des/rand_key.c",
    "src/crypto/des/read2pwd.c",
    "src/crypto/des/rpc_enc.c",
    "src/crypto/des/set_key.c",
    "src/crypto/des/str2key.c",
    "src/crypto/des/xcbc_enc.c",
    "src/crypto/dh/dh_ameth.c",
    "src/crypto/dh/dh_asn1.c",
    "src/crypto/dh/dh_check.c",
    "src/crypto/dh/dh_depr.c",
    "src/crypto/dh/dh_err.c",
    "src/crypto/dh/dh_gen.c",
    "src/crypto/dh/dh_kdf.c",
    "src/crypto/dh/dh_key.c",
    "src/crypto/dh/dh_lib.c",
    "src/crypto/dh/dh_pmeth.c",
    "src/crypto/dh/dh_prn.c",
    "src/crypto/dh/dh_rfc5114.c",
    "src/crypto/dsa/dsa_ameth.c",
    "src/crypto/dsa/dsa_asn1.c",
    "src/crypto/dsa/dsa_depr.c",
    "src/crypto/dsa/dsa_err.c",
    "src/crypto/dsa/dsa_gen.c",
    "src/crypto/dsa/dsa_key.c",
    "src/crypto/dsa/dsa_lib.c",
    "src/crypto/dsa/dsa_ossl.c",
    "src/crypto/dsa/dsa_pmeth.c",
    "src/crypto/dsa/dsa_prn.c",
    "src/crypto/dsa/dsa_sign.c",
    "src/crypto/dsa/dsa_vrf.c",
    "src/crypto/dso/dso_beos.c",
    "src/crypto/dso/dso_dl.c",
    "src/crypto/dso/dso_dlfcn.c",
    "src/crypto/dso/dso_err.c",
    "src/crypto/dso/dso_lib.c",
    "src/crypto/dso/dso_null.c",
    "src/crypto/dso/dso_openssl.c",
    "src/crypto/dso/dso_vms.c",
    "src/crypto/dso/dso_win32.c",
    "src/crypto/ebcdic.c",
    "src/crypto/ec/ec2_mult.c",
    "src/crypto/ec/ec2_oct.c",
    "src/crypto/ec/ec2_smpl.c",
    "src/crypto/ec/ec_ameth.c",
    "src/crypto/ec/ec_asn1.c",
    "src/crypto/ec/ec_check.c",
    "src/crypto/ec/ec_curve.c",
    "src/crypto/ec/ec_cvt.c",
    "src/crypto/ec/ec_err.c",
    "src/crypto/ec/ec_key.c",
    "src/crypto/ec/ec_lib.c",
    "src/crypto/ec/ec_mult.c",
    "src/crypto/ec/ec_oct.c",
    "src/crypto/ec/ec_pmeth.c",
    "src/crypto/ec/ec_print.c",
    "src/crypto/ec/eck_prn.c",
    "src/crypto/ec/ecp_mont.c",
    "src/crypto/ec/ecp_nist.c",
    "src/crypto/ec/ecp_nistp224.c",
    "src/crypto/ec/ecp_nistp256.c",
    "src/crypto/ec/ecp_nistp521.c",
    "src/crypto/ec/ecp_nistputil.c",
    "src/crypto/ec/ecp_nistz256.c",
    "src/crypto/ec/ecp_oct.c",
    "src/crypto/ec/ecp_smpl.c",
    "src/crypto/ecdh/ech_err.c",
    "src/crypto/ecdh/ech_kdf.c",
    "src/crypto/ecdh/ech_key.c",
    "src/crypto/ecdh/ech_lib.c",
    "src/crypto/ecdh/ech_ossl.c",
    "src/crypto/ecdsa/ecs_asn1.c",
    "src/crypto/ecdsa/ecs_err.c",
    "src/crypto/ecdsa/ecs_lib.c",
    "src/crypto/ecdsa/ecs_ossl.c",
    "src/crypto/ecdsa/ecs_sign.c",
    "src/crypto/ecdsa/ecs_vrf.c",
    "src/crypto/engine/eng_all.c",
    "src/crypto/engine/eng_cnf.c",
    "src/crypto/engine/eng_cryptodev.c",
    "src/crypto/engine/eng_ctrl.c",
    "src/crypto/engine/eng_dyn.c",
    "src/crypto/engine/eng_err.c",
    "src/crypto/engine/eng_fat.c",
    "src/crypto/engine/eng_init.c",
    "src/crypto/engine/eng_lib.c",
    "src/crypto/engine/eng_list.c",
    "src/crypto/engine/eng_openssl.c",
    "src/crypto/engine/eng_pkey.c",
    "src/crypto/engine/eng_rdrand.c",
    "src/crypto/engine/eng_table.c",
    "src/crypto/engine/tb_asnmth.c",
    "src/crypto/engine/tb_cipher.c",
    "src/crypto/engine/tb_dh.c",
    "src/crypto/engine/tb_digest.c",
    "src/crypto/engine/tb_dsa.c",
    "src/crypto/engine/tb_ecdh.c",
    "src/crypto/engine/tb_ecdsa.c",
    "src/crypto/engine/tb_pkmeth.c",
    "src/crypto/engine/tb_rand.c",
    "src/crypto/engine/tb_rsa.c",
    "src/crypto/engine/tb_store.c",
    "src/crypto/err/err.c",
    "src/crypto/err/err_all.c",
    "src/crypto/err/err_prn.c",
    "src/crypto/evp/bio_b64.c",
    "src/crypto/evp/bio_enc.c",
    "src/crypto/evp/bio_md.c",
    "src/crypto/evp/bio_ok.c",
    "src/crypto/evp/c_all.c",
    "src/crypto/evp/c_allc.c",
    "src/crypto/evp/c_alld.c",
    "src/crypto/evp/digest.c",
    "src/crypto/evp/e_aes.c",
    "src/crypto/evp/e_aes_cbc_hmac_sha1.c",
    "src/crypto/evp/e_aes_cbc_hmac_sha256.c",
    "src/crypto/evp/e_bf.c",
    "src/crypto/evp/e_camellia.c",
    "src/crypto/evp/e_cast.c",
    "src/crypto/evp/e_des.c",
    "src/crypto/evp/e_des3.c",
    "src/crypto/evp/e_idea.c",
    "src/crypto/evp/e_null.c",
    "src/crypto/evp/e_old.c",
    "src/crypto/evp/e_rc2.c",
    "src/crypto/evp/e_rc4.c",
    "src/crypto/evp/e_rc4_hmac_md5.c",
    "src/crypto/evp/e_rc5.c",
    "src/crypto/evp/e_seed.c",
    "src/crypto/evp/e_xcbc_d.c",
    "src/crypto/evp/encode.c",
    "src/crypto/evp/evp_acnf.c",
    "src/crypto/evp/evp_cnf.c",
    "src/crypto/evp/evp_enc.c",
    "src/crypto/evp/evp_err.c",
    "src/crypto/evp/evp_key.c",
    "src/crypto/evp/evp_lib.c",
    "src/crypto/evp/evp_pbe.c",
    "src/crypto/evp/evp_pkey.c",
    "src/crypto/evp/m_dss.c",
    "src/crypto/evp/m_dss1.c",
    "src/crypto/evp/m_ecdsa.c",
    "src/crypto/evp/m_md2.c",
    "src/crypto/evp/m_md4.c",
    "src/crypto/evp/m_md5.c",
    "src/crypto/evp/m_mdc2.c",
    "src/crypto/evp/m_null.c",
    "src/crypto/evp/m_ripemd.c",
    "src/crypto/evp/m_sha.c",
    "src/crypto/evp/m_sha1.c",
    "src/crypto/evp/m_sigver.c",
    "src/crypto/evp/m_wp.c",
    "src/crypto/evp/names.c",
    "src/crypto/evp/p5_crpt.c",
    "src/crypto/evp/p5_crpt2.c",
    "src/crypto/evp/p_dec.c",
    "src/crypto/evp/p_enc.c",
    "src/crypto/evp/p_lib.c",
    "src/crypto/evp/p_open.c",
    "src/crypto/evp/p_seal.c",
    "src/crypto/evp/p_sign.c",
    "src/crypto/evp/p_verify.c",
    "src/crypto/evp/pmeth_fn.c",
    "src/crypto/evp/pmeth_gn.c",
    "src/crypto/evp/pmeth_lib.c",
    "src/crypto/ex_data.c",
    "src/crypto/fips_ers.c",
    "src/crypto/hmac/hm_ameth.c",
    "src/crypto/hmac/hm_pmeth.c",
    "src/crypto/hmac/hmac.c",
    "src/crypto/idea/i_cbc.c",
    "src/crypto/idea/i_cfb64.c",
    "src/crypto/idea/i_ecb.c",
    "src/crypto/idea/i_ofb64.c",
    "src/crypto/idea/i_skey.c",
    "src/crypto/krb5/krb5_asn.c",
    "src/crypto/lhash/lh_stats.c",
    "src/crypto/lhash/lhash.c",
    "src/crypto/md4/md4_dgst.c",
    "src/crypto/md4/md4_one.c",
    "src/crypto/md5/md5_dgst.c",
    "src/crypto/md5/md5_one.c",
    "src/crypto/mdc2/mdc2_one.c",
    "src/crypto/mdc2/mdc2dgst.c",
    "src/crypto/mem.c",
    "src/crypto/mem_dbg.c",
    "src/crypto/modes/cbc128.c",
    "src/crypto/modes/ccm128.c",
    "src/crypto/modes/cfb128.c",
    "src/crypto/modes/ctr128.c",
    "src/crypto/modes/cts128.c",
    "src/crypto/modes/gcm128.c",
    "src/crypto/modes/ofb128.c",
    "src/crypto/modes/wrap128.c",
    "src/crypto/modes/xts128.c",
    "src/crypto/o_dir.c",
    "src/crypto/o_fips.c",
    "src/crypto/o_init.c",
    "src/crypto/o_str.c",
    "src/crypto/o_time.c",
    "src/crypto/objects/o_names.c",
    "src/crypto/objects/obj_dat.c",
    "src/crypto/objects/obj_err.c",
    "src/crypto/objects/obj_lib.c",
    "src/crypto/objects/obj_xref.c",
    "src/crypto/ocsp/ocsp_asn.c",
    "src/crypto/ocsp/ocsp_cl.c",
    "src/crypto/ocsp/ocsp_err.c",
    "src/crypto/ocsp/ocsp_ext.c",
    "src/crypto/ocsp/ocsp_ht.c",
    "src/crypto/ocsp/ocsp_lib.c",
    "src/crypto/ocsp/ocsp_prn.c",
    "src/crypto/ocsp/ocsp_srv.c",
    "src/crypto/ocsp/ocsp_vfy.c",
    "src/crypto/pem/pem_all.c",
    "src/crypto/pem/pem_err.c",
    "src/crypto/pem/pem_info.c",
    "src/crypto/pem/pem_lib.c",
    "src/crypto/pem/pem_oth.c",
    "src/crypto/pem/pem_pk8.c",
    "src/crypto/pem/pem_pkey.c",
    "src/crypto/pem/pem_seal.c",
    "src/crypto/pem/pem_sign.c",
    "src/crypto/pem/pem_x509.c",
    "src/crypto/pem/pem_xaux.c",
    "src/crypto/pem/pvkfmt.c",
    "src/crypto/pkcs12/p12_add.c",
    "src/crypto/pkcs12/p12_asn.c",
    "src/crypto/pkcs12/p12_attr.c",
    "src/crypto/pkcs12/p12_crpt.c",
    "src/crypto/pkcs12/p12_crt.c",
    "src/crypto/pkcs12/p12_decr.c",
    "src/crypto/pkcs12/p12_init.c",
    "src/crypto/pkcs12/p12_key.c",
    "src/crypto/pkcs12/p12_kiss.c",
    "src/crypto/pkcs12/p12_mutl.c",
    "src/crypto/pkcs12/p12_npas.c",
    "src/crypto/pkcs12/p12_p8d.c",
    "src/crypto/pkcs12/p12_p8e.c",
    "src/crypto/pkcs12/p12_utl.c",
    "src/crypto/pkcs12/pk12err.c",
    "src/crypto/pkcs7/bio_pk7.c",
    "src/crypto/pkcs7/pk7_asn1.c",
    "src/crypto/pkcs7/pk7_attr.c",
    "src/crypto/pkcs7/pk7_doit.c",
    "src/crypto/pkcs7/pk7_lib.c",
    "src/crypto/pkcs7/pk7_mime.c",
    "src/crypto/pkcs7/pk7_smime.c",
    "src/crypto/pkcs7/pkcs7err.c",
    "src/crypto/pqueue/pqueue.c",
    "src/crypto/rand/md_rand.c",
    "src/crypto/rand/rand_egd.c",
    "src/crypto/rand/rand_err.c",
    "src/crypto/rand/rand_lib.c",
    "src/crypto/rand/rand_nw.c",
    "src/crypto/rand/rand_os2.c",
    "src/crypto/rand/rand_unix.c",
    "src/crypto/rand/rand_win.c",
    "src/crypto/rand/randfile.c",
    "src/crypto/rc2/rc2_cbc.c",
    "src/crypto/rc2/rc2_ecb.c",
    "src/crypto/rc2/rc2_skey.c",
    "src/crypto/rc2/rc2cfb64.c",
    "src/crypto/rc2/rc2ofb64.c",
    "src/crypto/rc4/rc4_utl.c",
    "src/crypto/ripemd/rmd_dgst.c",
    "src/crypto/ripemd/rmd_one.c",
    "src/crypto/rsa/rsa_ameth.c",
    "src/crypto/rsa/rsa_asn1.c",
    "src/crypto/rsa/rsa_chk.c",
    "src/crypto/rsa/rsa_crpt.c",
    "src/crypto/rsa/rsa_depr.c",
    "src/crypto/rsa/rsa_eay.c",
    "src/crypto/rsa/rsa_err.c",
    "src/crypto/rsa/rsa_gen.c",
    "src/crypto/rsa/rsa_lib.c",
    "src/crypto/rsa/rsa_none.c",
    "src/crypto/rsa/rsa_null.c",
    "src/crypto/rsa/rsa_oaep.c",
    "src/crypto/rsa/rsa_pk1.c",
    "src/crypto/rsa/rsa_pmeth.c",
    "src/crypto/rsa/rsa_prn.c",
    "src/crypto/rsa/rsa_pss.c",
    "src/crypto/rsa/rsa_saos.c",
    "src/crypto/rsa/rsa_sign.c",
    "src/crypto/rsa/rsa_ssl.c",
    "src/crypto/rsa/rsa_x931.c",
    "src/crypto/seed/seed.c",
    "src/crypto/seed/seed_cbc.c",
    "src/crypto/seed/seed_cfb.c",
    "src/crypto/seed/seed_ecb.c",
    "src/crypto/seed/seed_ofb.c",
    "src/crypto/sha/sha1_one.c",
    "src/crypto/sha/sha1dgst.c",
    "src/crypto/sha/sha256.c",
    "src/crypto/sha/sha512.c",
    "src/crypto/sha/sha_dgst.c",
    "src/crypto/sha/sha_one.c",
    "src/crypto/srp/srp_lib.c",
    "src/crypto/srp/srp_vfy.c",
    "src/crypto/stack/stack.c",
    "src/crypto/ts/ts_asn1.c",
    "src/crypto/ts/ts_conf.c",
    "src/crypto/ts/ts_err.c",
    "src/crypto/ts/ts_lib.c",
    "src/crypto/ts/ts_req_print.c",
    "src/crypto/ts/ts_req_utils.c",
    "src/crypto/ts/ts_rsp_print.c",
    "src/crypto/ts/ts_rsp_sign.c",
    "src/crypto/ts/ts_rsp_utils.c",
    "src/crypto/ts/ts_rsp_verify.c",
    "src/crypto/ts/ts_verify_ctx.c",
    "src/crypto/txt_db/txt_db.c",
    "src/crypto/ui/ui_compat.c",
    "src/crypto/ui/ui_err.c",
    "src/crypto/ui/ui_lib.c",
    "src/crypto/ui/ui_openssl.c",
    "src/crypto/ui/ui_util.c",
    "src/crypto/uid.c",
    "src/crypto/whrlpool/wp_dgst.c",
    "src/crypto/x509/by_dir.c",
    "src/crypto/x509/by_file.c",
    "src/crypto/x509/x509_att.c",
    "src/crypto/x509/x509_cmp.c",
    "src/crypto/x509/x509_d2.c",
    "src/crypto/x509/x509_def.c",
    "src/crypto/x509/x509_err.c",
    "src/crypto/x509/x509_ext.c",
    "src/crypto/x509/x509_lu.c",
    "src/crypto/x509/x509_obj.c",
    "src/crypto/x509/x509_r2x.c",
    "src/crypto/x509/x509_req.c",
    "src/crypto/x509/x509_set.c",
    "src/crypto/x509/x509_trs.c",
    "src/crypto/x509/x509_txt.c",
    "src/crypto/x509/x509_v3.c",
    "src/crypto/x509/x509_vfy.c",
    "src/crypto/x509/x509_vpm.c",
    "src/crypto/x509/x509cset.c",
    "src/crypto/x509/x509name.c",
    "src/crypto/x509/x509rset.c",
    "src/crypto/x509/x509spki.c",
    "src/crypto/x509/x509type.c",
    "src/crypto/x509/x_all.c",
    "src/crypto/x509v3/pcy_cache.c",
    "src/crypto/x509v3/pcy_data.c",
    "src/crypto/x509v3/pcy_lib.c",
    "src/crypto/x509v3/pcy_map.c",
    "src/crypto/x509v3/pcy_node.c",
    "src/crypto/x509v3/pcy_tree.c",
    "src/crypto/x509v3/v3_addr.c",
    "src/crypto/x509v3/v3_akey.c",
    "src/crypto/x509v3/v3_akeya.c",
    "src/crypto/x509v3/v3_alt.c",
    "src/crypto/x509v3/v3_asid.c",
    "src/crypto/x509v3/v3_bcons.c",
    "src/crypto/x509v3/v3_bitst.c",
    "src/crypto/x509v3/v3_conf.c",
    "src/crypto/x509v3/v3_cpols.c",
    "src/crypto/x509v3/v3_crld.c",
    "src/crypto/x509v3/v3_enum.c",
    "src/crypto/x509v3/v3_extku.c",
    "src/crypto/x509v3/v3_genn.c",
    "src/crypto/x509v3/v3_ia5.c",
    "src/crypto/x509v3/v3_info.c",
    "src/crypto/x509v3/v3_int.c",
    "src/crypto/x509v3/v3_lib.c",
    "src/crypto/x509v3/v3_ncons.c",
    "src/crypto/x509v3/v3_ocsp.c",
    "src/crypto/x509v3/v3_pci.c",
    "src/crypto/x509v3/v3_pcia.c",
    "src/crypto/x509v3/v3_pcons.c",
    "src/crypto/x509v3/v3_pku.c",
    "src/crypto/x509v3/v3_pmaps.c",
    "src/crypto/x509v3/v3_prn.c",
    "src/crypto/x509v3/v3_purp.c",
    "src/crypto/x509v3/v3_scts.c",
    "src/crypto/x509v3/v3_skey.c",
    "src/crypto/x509v3/v3_sxnet.c",
    "src/crypto/x509v3/v3_utl.c",
    "src/crypto/x509v3/v3err.c",
]

crypto_sources_linux_arm = [
    "src/crypto/chacha/chacha_vec_arm.S",
    "src/crypto/cpu-arm-asm.S",
    "src/crypto/curve25519/asm/x25519-asm-arm.S",
    "src/crypto/poly1305/poly1305_arm_asm.S",
]

crypto_sources_linux_x86_64 = [
    "linux-x86_64/crypto/aes/asm/aes-x86_64.S",
    "linux-x86_64/crypto/aes/asm/aesni-mb-x86_64.S",
    "linux-x86_64/crypto/aes/asm/aesni-sha1-x86_64.S",
    "linux-x86_64/crypto/aes/asm/aesni-sha256-x86_64.S",
    "linux-x86_64/crypto/aes/asm/aesni-x86_64.S",
    "linux-x86_64/crypto/aes/asm/bsaes-x86_64.S",
    "linux-x86_64/crypto/aes/asm/vpaes-x86_64.S",
    "linux-x86_64/crypto/bn/asm/rsaz-avx2.S",
    "linux-x86_64/crypto/bn/asm/rsaz-x86_64.S",
    "linux-x86_64/crypto/bn/asm/x86_64-gf2m.S",
    "linux-x86_64/crypto/bn/asm/x86_64-mont.S",
    "linux-x86_64/crypto/bn/asm/x86_64-mont5.S",
    "linux-x86_64/crypto/camellia/asm/cmll-x86_64.S",
    "linux-x86_64/crypto/ec/asm/ecp_nistz256-x86_64.S",
    "linux-x86_64/crypto/md5/asm/md5-x86_64.S",
    "linux-x86_64/crypto/modes/asm/aesni-gcm-x86_64.S",
    "linux-x86_64/crypto/modes/asm/ghash-x86_64.S",
    "linux-x86_64/crypto/rc4/asm/rc4-md5-x86_64.S",
    "linux-x86_64/crypto/rc4/asm/rc4-x86_64.S",
    "linux-x86_64/crypto/sha/asm/sha1-mb-x86_64.S",
    "linux-x86_64/crypto/sha/asm/sha1-x86_64.S",
    "linux-x86_64/crypto/sha/asm/sha256-mb-x86_64.S",
    "linux-x86_64/crypto/sha/asm/sha256-x86_64.S",
    "linux-x86_64/crypto/sha/asm/sha512-x86_64.S",
    "linux-x86_64/crypto/whrlpool/asm/wp-x86_64.S",
    "linux-x86_64/crypto/x86_64cpuid.S",
]
