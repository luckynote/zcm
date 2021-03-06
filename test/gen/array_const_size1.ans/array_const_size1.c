// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by zcm-gen

#include <string.h>
#include "array_const_size1.h"

static int __array_const_size1_hash_computed;
static uint64_t __array_const_size1_hash;

uint64_t __array_const_size1_hash_recursive(const __zcm_hash_ptr *p)
{
    const __zcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __array_const_size1_get_hash)
            return 0;

    __zcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = (void*)__array_const_size1_get_hash;
    (void) cp;

    uint64_t hash = (uint64_t)0xbb93d1c57076cddbLL
         + __int8_t_hash_recursive(&cp)
         + __int16_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int64_t_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
         + __string_hash_recursive(&cp)
         + __boolean_hash_recursive(&cp)
         + __byte_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __array_const_size1_get_hash(void)
{
    if (!__array_const_size1_hash_computed) {
        __array_const_size1_hash = (int64_t)__array_const_size1_hash_recursive(NULL);
        __array_const_size1_hash_computed = 1;
    }

    return __array_const_size1_hash;
}

int __array_const_size1_encode_array(void *buf, int offset, int maxlen, const array_const_size1 *p, int elements)
{
    int pos = 0, element;
    int thislen;

    for (element = 0; element < elements; element++) {

        thislen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, p[element].i8, 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int16_t_encode_array(buf, offset + pos, maxlen - pos, p[element].i16, 2);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, p[element].i32, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, p[element].i64, 4);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].f, 5);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].d, 6);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_encode_array(buf, offset + pos, maxlen - pos, p[element].s, 7);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __boolean_encode_array(buf, offset + pos, maxlen - pos, p[element].bl, 8);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __byte_encode_array(buf, offset + pos, maxlen - pos, p[element].b, 9);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int array_const_size1_encode(void *buf, int offset, int maxlen, const array_const_size1 *p)
{
    int pos = 0, thislen;
    int64_t hash = __array_const_size1_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __array_const_size1_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __array_const_size1_encoded_array_size(const array_const_size1 *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int8_t_encoded_array_size(p[element].i8, 1);

        size += __int16_t_encoded_array_size(p[element].i16, 2);

        size += __int32_t_encoded_array_size(p[element].i32, 3);

        size += __int64_t_encoded_array_size(p[element].i64, 4);

        size += __float_encoded_array_size(p[element].f, 5);

        size += __double_encoded_array_size(p[element].d, 6);

        size += __string_encoded_array_size(p[element].s, 7);

        size += __boolean_encoded_array_size(p[element].bl, 8);

        size += __byte_encoded_array_size(p[element].b, 9);

    }
    return size;
}

int array_const_size1_encoded_size(const array_const_size1 *p)
{
    return 8 + __array_const_size1_encoded_array_size(p, 1);
}

int __array_const_size1_decode_array(const void *buf, int offset, int maxlen, array_const_size1 *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, p[element].i8, 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int16_t_decode_array(buf, offset + pos, maxlen - pos, p[element].i16, 2);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, p[element].i32, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, p[element].i64, 4);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].f, 5);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].d, 6);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __string_decode_array(buf, offset + pos, maxlen - pos, p[element].s, 7);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __boolean_decode_array(buf, offset + pos, maxlen - pos, p[element].bl, 8);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __byte_decode_array(buf, offset + pos, maxlen - pos, p[element].b, 9);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __array_const_size1_decode_array_cleanup(array_const_size1 *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int8_t_decode_array_cleanup(p[element].i8, 1);

        __int16_t_decode_array_cleanup(p[element].i16, 2);

        __int32_t_decode_array_cleanup(p[element].i32, 3);

        __int64_t_decode_array_cleanup(p[element].i64, 4);

        __float_decode_array_cleanup(p[element].f, 5);

        __double_decode_array_cleanup(p[element].d, 6);

        __string_decode_array_cleanup(p[element].s, 7);

        __boolean_decode_array_cleanup(p[element].bl, 8);

        __byte_decode_array_cleanup(p[element].b, 9);

    }
    return 0;
}

int array_const_size1_decode(const void *buf, int offset, int maxlen, array_const_size1 *p)
{
    int pos = 0, thislen;
    int64_t hash = __array_const_size1_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __array_const_size1_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int array_const_size1_decode_cleanup(array_const_size1 *p)
{
    return __array_const_size1_decode_array_cleanup(p, 1);
}

int __array_const_size1_clone_array(const array_const_size1 *p, array_const_size1 *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int8_t_clone_array(p[element].i8, q[element].i8, 1);

        __int16_t_clone_array(p[element].i16, q[element].i16, 2);

        __int32_t_clone_array(p[element].i32, q[element].i32, 3);

        __int64_t_clone_array(p[element].i64, q[element].i64, 4);

        __float_clone_array(p[element].f, q[element].f, 5);

        __double_clone_array(p[element].d, q[element].d, 6);

        __string_clone_array(p[element].s, q[element].s, 7);

        __boolean_clone_array(p[element].bl, q[element].bl, 8);

        __byte_clone_array(p[element].b, q[element].b, 9);

    }
    return 0;
}

array_const_size1 *array_const_size1_copy(const array_const_size1 *p)
{
    array_const_size1 *q = (array_const_size1*) malloc(sizeof(array_const_size1));
    __array_const_size1_clone_array(p, q, 1);
    return q;
}

void array_const_size1_destroy(array_const_size1 *p)
{
    __array_const_size1_decode_array_cleanup(p, 1);
    free(p);
}

int array_const_size1_publish(zcm_t *lc, const char *channel, const array_const_size1 *p)
{
      int max_data_size = array_const_size1_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = array_const_size1_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = zcm_publish (lc, channel, (char *)buf, (size_t)data_size);
      free (buf);
      return status;
}

struct _array_const_size1_subscription_t {
    array_const_size1_handler_t user_handler;
    void *userdata;
    zcm_sub_t *z_sub;
};
static
void array_const_size1_handler_stub (const zcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    array_const_size1 p;
    memset(&p, 0, sizeof(array_const_size1));
    status = array_const_size1_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding array_const_size1!!!\n", status);
        return;
    }

    array_const_size1_subscription_t *h = (array_const_size1_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    array_const_size1_decode_cleanup (&p);
}

array_const_size1_subscription_t* array_const_size1_subscribe (zcm_t *zcm,
                    const char *channel,
                    array_const_size1_handler_t f, void *userdata)
{
    array_const_size1_subscription_t *n = (array_const_size1_subscription_t*)
                       malloc(sizeof(array_const_size1_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->z_sub = zcm_subscribe (zcm, channel,
                              array_const_size1_handler_stub, n);
    if (n->z_sub == NULL) {
        fprintf (stderr,"couldn't reg array_const_size1 ZCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int array_const_size1_unsubscribe(zcm_t *zcm, array_const_size1_subscription_t* hid)
{
    int status = zcm_unsubscribe (zcm, hid->z_sub);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe array_const_size1_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

