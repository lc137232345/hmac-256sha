/*
 * @Author: your name
 * @Date: 2020-10-01 14:10:28
 * @LastEditTime: 2020-10-02 03:52:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Editain
 * @FilePath: /test/test.cpp
 */
#include <hmac.h>

void hmac::set_str(string _str)
{
    const char *str = _str.c_str();
    std::memcpy(str, str, len);
    str = _str;
}

void hmac::set_str(string _str)
{
    const char *str = _str.c_str();

    str = _str;
}
const uint16_t MAX_KEY_LEN_224 = 56;
const uint16_t MAX_KEY_LEN_256 = 64;
const uint16_t MAX_KEY_LEN_384 = 96;
const uint16_t MAX_KEY_LEN_512 = 128;

struct key_config_256
{
    uint8_t str[MAX_KEY_LEN_256];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

struct key_config_256
{
    uint8_t str[MAX_KEY_STR_LEN];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

struct key_config_256
{
    uint8_t str[MAX_KEY_STR_LEN];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

struct key_config_256
{
    uint8_t str[MAX_KEY_STR_LEN];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

struct key_config_256
{
    uint8_t str[MAX_KEY_STR_LEN];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;
};

enum class SHA
{
    SHA224,
    SHA256,
    SHA384,
    SHA512
};

void key_gen(key_config key_config, uint8_t *key)
{
    uint8_t result[MAX_KEY_LEN];
    uint32_t res_len = key_config.res_len;
    uint8_t res_start_offset = key_config.res_start_offset;
    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key_config.key, key_config.key_len, EVP_sha512(), NULL);
    HMAC_Update(&ctx, key_config.str, key_config.str_len);
    HMAC_Final(&ctx, (unsigned char *)&result, (uint32_t *)&key_config.key_len);
    HMAC_CTX_cleanup(&ctx);
    std::memcpy(key, (result + res_start_offset), res_len);
}
using namespace std;

int main(int argc, char const *argv[])
{
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
    return 0;
}

hmac::hmac(/* args */)
{
}

hmac::~hmac()
{
}
