/*
 * @Author: your name
 * @Date: 2020-10-02 01:18:26
 * @LastEditTime: 2020-10-02 03:31:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /hmac-sha256/hmac.h
 */
#include "openssl/hmac.h"
#include <iostream>
#include <iomanip>
#include <cstring>

#include <string>
using namespace std;
class hmac
{
private:
    uint8_t str[MAX_KEY_LEN_256];
    uint8_t key[MAX_KEY_LEN_256];
    uint8_t key_len;
    uint8_t str_len;
    uint8_t res_len;
    uint8_t res_start_offset;

public:
    hmac(/* args */);
    ~hmac();

    inline void set_key_len(uint8_t _key_len)
    {
        key_len = _key_len;
    }
    inline void set_res_len(uint8_t _res_len)
    {
        res_len = _res_len;
    }
    inline void set_res_start_offset(uint8_t _res_start_offset)
    {
        res_start_offset = _res_start_offset;
    }
    inline void set_str_len(uint8_t _str_len)
    {
        str_len = _str_len;
    }
     void set_str(string _str);

     void set_key(string _key);



    inline uint8_t get_key_len()
    {
        return key_len;
    }
    inline uint8_t get_res_len()
    {
        return res_len;
    }
    inline uint8_t get_res_start_offset()
    {
        return res_start_offset;
    }

    inline uint8_t get_str_len()
    {
        return str_len;
    }
};

hmac::hmac(/* args */)
{
}

hmac::~hmac()
{
}
