/*
 * @Author: your name
 * @Date: 2020-10-01 14:10:28
 * @LastEditTime: 2021-01-05 03:46:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Editain
 * @FilePath: /test/test.cpp
 */
#include "openssl/hmac.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

#include <string>
using namespace std;

const uint16_t KDF_KEY_LEN = 32;
const uint16_t MAX_KEY_STR_LEN = 10;

typedef uint8_t kdf_key_t[KDF_KEY_LEN];

struct key_config
{
    unsigned char str[MAX_KEY_STR_LEN];
    uint8_t key[KDF_KEY_LEN];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

#if 0

const uint16_t MAX_KEY_LEN_224 = 56;
const uint16_t MAX_KEY_LEN_256 = 64;
const uint16_t MAX_KEY_LEN_384 = 96;
const uint16_t MAX_KEY_LEN_512 = 128;




enum class SHA
{
    SHA224,
    SHA256,
    SHA384,
    SHA512
};
#endif
void key_gen(key_config key_config, uint8_t *key)
{
    uint8_t result[KDF_KEY_LEN];
    uint32_t res_len = key_config.res_len;
    uint8_t res_start_offset = key_config.res_start_offset;
    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key_config.key, key_config.key_len, EVP_sha256(), NULL);
    HMAC_Update(&ctx, key_config.str, key_config.str_len);
    HMAC_Final(&ctx, (unsigned char *)&result, (uint32_t *)&key_config.key_len);
    HMAC_CTX_cleanup(&ctx);
    std::memcpy(key, (result + res_start_offset), res_len);
}
struct pdcp_secity_key_gen_req_info
{
    uint16_t pci;
    uint64_t dl_arfcn;
    kdf_key_t k_gnb;
    kdf_key_t nh;
};

struct pdcp_secity_key_gen_rsp_info
{
    bool k_gnb_star_present;
    kdf_key_t k_gnb_star;
};

pdcp_secity_key_gen_rsp_info hmac_256(const pdcp_secity_key_gen_req_info &pdcp_secity_key_gen_req_info)
{
    key_config key_config;
    pdcp_secity_key_gen_rsp_info pdcp_secity_key_gen_rsp;
    key_config.str[0] = 0x70;

    key_config.str[1] = (pdcp_secity_key_gen_req_info.pci & 0xff00) >> 8;
    key_config.str[2] = (pdcp_secity_key_gen_req_info.pci & 0x00ff);

    key_config.str[3] = 0x00;
    key_config.str[4] = 0x02;

    key_config.str[5] = (pdcp_secity_key_gen_req_info.dl_arfcn & 0x00ff0000) >> 16;
    key_config.str[6] = (pdcp_secity_key_gen_req_info.dl_arfcn & 0x0000ff00) >> 8;
    key_config.str[7] = (pdcp_secity_key_gen_req_info.dl_arfcn & 0x000000ff);

    key_config.str[8] = 0x00;
    key_config.str[9] = 0x03;
    string str;
    for (int i = 0; i < 10; i++)
    {
        str += std::to_string(key_config.str[i]);
    }
    std::cout << str << std::endl;

    key_config.str_len = MAX_KEY_STR_LEN;
    key_config.res_len = KDF_KEY_LEN;
    key_config.res_start_offset = 0;
    key_config.key_len = sizeof(kdf_key_t);
    std::memcpy(key_config.key, pdcp_secity_key_gen_req_info.k_gnb, sizeof(kdf_key_t));
    key_gen(key_config, pdcp_secity_key_gen_rsp.k_gnb_star);
    pdcp_secity_key_gen_rsp.k_gnb_star_present = true;
    return pdcp_secity_key_gen_rsp;
}

int main(int argc, char const *argv[])
{
#if 0
    string s;
    string key;
    SHA hash;
    int choose_sha;
    std::cout << "please write the s:" << std::endl;
    std::cin >> s;
    std::cout << "please write the key:" << std::endl;
    std::cin >> key;
    std::cout << "please write the sha you chose:" << std::endl;
    std::cout << "1.sha256:" << std::endl;
    std::cout << "2.sha384:" << std::endl;
    std::cout << "3.sha512:" << std::endl;
    std::cin >> choose_sha;
    hash = (SHA)choose_sha;

    switch (hash)
    {
    case SHA::SHA224:
    {
        key_config hand_out_key_config;
        break;
    }
    case SHA::SHA256:
    {
        key_config hand_out_key_config;
        break;
    }
    case SHA::SHA384:
    {
        break;
    }
    case SHA::SHA512:
    {
        break;
    }

    default:
        break;
    }
#endif

#if 0
    string s;
    string key;
    std::cout << "please write the s:" << std::endl;
    std::cin >> s;
    std::cout << "please write the key:" << std::endl;
    std::cin >> key;

    key_config hand_out_key_config;
    memset(&hand_out_key_config, 0, sizeof(key_config));
    kdf_key_t k_gnb_star = {0};

    const char *text = s.c_str();
    int text_len = s.length();

    const char *px = key.c_str();
    int len = key.length();

    std::memcpy(hand_out_key_config.key, px, len);
    std::memset(hand_out_key_config.key + len, 0, sizeof(kdf_key_t) - len);

    std::memcpy(hand_out_key_config.str, text, text_len);

    hand_out_key_config.key_len = 64;
    hand_out_key_config.str_len = text_len;

    hand_out_key_config.res_len = 64;
    hand_out_key_config.res_start_offset = 0;
    key_gen(hand_out_key_config, k_gnb_star);
    for (size_t i = 0; i < 64; i++)

    {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)(unsigned char)k_gnb_star[i];
    }
#endif
    key_config hand_out_key_config;
    memset(&hand_out_key_config, 0, sizeof(key_config));
    kdf_key_t k_gnb_star = {0x96, 0x45, 0xb7, 0xa1, 0x24, 0x9c, 0xfd, 0xff, 0xfe, 0x0e, 0xa1, 0x96, 0x19, 0xef, 0xe0, 0x53,
                            0x50, 0xf4, 0xd5, 0x92, 0x44, 0xe8, 0x69, 0x38, 0x57, 0x5c, 0x6a, 0x24, 0xde, 0x8c, 0xf7, 0x5f};
    pdcp_secity_key_gen_req_info pdcp_secity_key_gen_req_info;

    memcpy(&pdcp_secity_key_gen_req_info.k_gnb, &k_gnb_star, sizeof(kdf_key_t));
    pdcp_secity_key_gen_req_info.pci = 12;
    pdcp_secity_key_gen_req_info.dl_arfcn = 633984;
    pdcp_secity_key_gen_rsp_info pdcp_secity_key_gen_rsp_info = hmac_256(pdcp_secity_key_gen_req_info);
    fstream ofile;
    ofile.open("test.txt", std::ios::out);
    for (int i = 0; i < 32; i++)

    {
        ofile << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)(unsigned char)pdcp_secity_key_gen_rsp_info.k_gnb_star[i];
    };

    return 0;
}
