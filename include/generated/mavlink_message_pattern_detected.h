// MESSAGE PATTERN_DETECTED PACKING

#define MAVLINK_MSG_ID_PATTERN_DETECTED 200

typedef struct __pattern_detected_t 
{
	float confidence; ///< Confidence of detection
	int8_t file[100]; ///< Pattern file name

} pattern_detected_t;

/**
 * @brief Send a pattern_detected message
 *
 * @param confidence Confidence of detection
 * @param file Pattern file name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t message_pattern_detected_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float confidence, const int8_t* file)
{
	msg->msgid = MAVLINK_MSG_ID_PATTERN_DETECTED;
	uint16_t i = 0;

	i += put_float_by_index(confidence, i, msg->payload); //Confidence of detection
	i += put_array_by_index(file, 100, i, msg->payload); //Pattern file name

	return finalize_message(msg, system_id, component_id, i);
}

static inline uint16_t message_pattern_detected_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const pattern_detected_t* pattern_detected)
{
	return message_pattern_detected_pack(system_id, component_id, msg, pattern_detected->confidence, pattern_detected->file);
}

#if !defined(_WIN32) && !defined(__linux) && !defined(__APPLE__)

#include "global_data.h"

static inline void message_pattern_detected_send(mavlink_channel_t chan, float confidence, const int8_t* file)
{
	mavlink_message_t msg;
	message_pattern_detected_pack(global_data.param[PARAM_SYSTEM_ID], global_data.param[PARAM_COMPONENT_ID], &msg, confidence, file);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE PATTERN_DETECTED UNPACKING

/**
 * @brief Get field confidence from pattern_detected message
 *
 * @return Confidence of detection
 */
static inline float message_pattern_detected_get_confidence(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload)[0];
	r.b[2] = (msg->payload)[1];
	r.b[1] = (msg->payload)[2];
	r.b[0] = (msg->payload)[3];
	return (float)r.f;
}

/**
 * @brief Get field file from pattern_detected message
 *
 * @return Pattern file name
 */
static inline uint16_t message_pattern_detected_get_file(const mavlink_message_t* msg, int8_t* r_data)
{

	memcpy(r_data, msg->payload+sizeof(float), 100);
	return 100;
}

static inline void message_pattern_detected_decode(const mavlink_message_t* msg, pattern_detected_t* pattern_detected)
{
	pattern_detected->confidence = message_pattern_detected_get_confidence(msg);
	message_pattern_detected_get_file(msg, pattern_detected->file);
}