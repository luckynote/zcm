// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by zcm-gen

#include <stdint.h>
#include <stdlib.h>
#include <zcm/zcm_coretypes.h>
#include <zcm/zcm.h>

#ifndef _nested2_h
#define _nested2_h

#ifdef __cplusplus
extern "C" {
#endif

#include "b.h"
typedef struct _nested2 nested2;
struct _nested2
{
    int8_t     g;
    b          **b_array;
};

/**
 * Create a deep copy of a nested2.
 * When no longer needed, destroy it with nested2_destroy()
 */
nested2* nested2_copy(const nested2* to_copy);

/**
 * Destroy an instance of nested2 created by nested2_copy()
 */
void nested2_destroy(nested2* to_destroy);

/**
 * Identifies a single subscription.  This is an opaque data type.
 */
typedef struct _nested2_subscription_t nested2_subscription_t;

/**
 * Prototype for a callback function invoked when a message of type
 * nested2 is received.
 */
typedef void(*nested2_handler_t)(const zcm_recv_buf_t *rbuf,
             const char *channel, const nested2 *msg, void *userdata);

/**
 * Publish a message of type nested2 using ZCM.
 *
 * @param zcm The ZCM instance to publish with.
 * @param channel The channel to publish on.
 * @param msg The message to publish.
 * @return 0 on success, <0 on error.  Success means ZCM has transferred
 * responsibility of the message data to the OS.
 */
int nested2_publish(zcm_t *zcm, const char *channel, const nested2 *msg);

/**
 * Subscribe to messages of type nested2 using ZCM.
 *
 * @param zcm The ZCM instance to subscribe with.
 * @param channel The channel to subscribe to.
 * @param handler The callback function invoked by ZCM when a message is received.
 *                This function is invoked by ZCM during calls to zcm_handle() and
 *                zcm_handle_timeout().
 * @param userdata An opaque pointer passed to @p handler when it is invoked.
 * @return 0 on success, <0 if an error occured
 */
nested2_subscription_t* nested2_subscribe(zcm_t *zcm, const char *channel, nested2_handler_t handler, void *userdata);

/**
 * Removes and destroys a subscription created by nested2_subscribe()
 */
int nested2_unsubscribe(zcm_t *zcm, nested2_subscription_t* hid);

/**
 * Sets the queue capacity for a subscription.
 * Some ZCM providers (e.g., the default multicast provider) are implemented
 * using a background receive thread that constantly revceives messages from
 * the network.  As these messages are received, they are buffered on
 * per-subscription queues until dispatched by zcm_handle().  This function
 * how many messages are queued before dropping messages.
 *
 * @param subs the subscription to modify.
 * @param num_messages The maximum number of messages to queue
 *  on the subscription.
 * @return 0 on success, <0 if an error occured
 */
int nested2_subscription_set_queue_capacity(nested2_subscription_t* subs,
                              int num_messages);

/**
 * Encode a message of type nested2 into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to nested2_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int nested2_encode(void *buf, int offset, int maxlen, const nested2 *p);

/**
 * Decode a message of type nested2 from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with nested2_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int nested2_decode(const void *buf, int offset, int maxlen, nested2 *msg);

/**
 * Release resources allocated by nested2_decode()
 * @return 0
 */
int nested2_decode_cleanup(nested2 *p);

/**
 * Check how many bytes are required to encode a message of type nested2
 */
int nested2_encoded_size(const nested2 *p);

// ZCM support functions. Users should not call these
int64_t __nested2_get_hash(void);
int64_t __nested2_hash_recursive(const __zcm_hash_ptr *p);
int     __nested2_encode_array(void *buf, int offset, int maxlen, const nested2 *p, int elements);
int     __nested2_decode_array(const void *buf, int offset, int maxlen, nested2 *p, int elements);
int     __nested2_decode_array_cleanup(nested2 *p, int elements);
int     __nested2_encoded_array_size(const nested2 *p, int elements);
int     __nested2_clone_array(const nested2 *p, nested2 *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
