#ifndef HEARTRATE4_HW_H
#define HEARTRATE4_HW_H

#include "heartrate4_hal.h"
#define HR4_I2C_ADDRESS 0x57

#include <stdint.h>
#include <stdbool.h>


// HELPER FUNCTIONS
uint8_t hr4_read_reg (uint8_t reg);

void hr4_read_reg_multi (uint8_t reg, uint8_t *buffer, uint8_t count);

void hr4_write_reg(uint8_t reg, uint8_t reg_val);

// LIBRARY ROUTINES

void hr4_init();

void hr4_set_registers();

void hr4_read_fifo_oldest_sample();

uint32_t hr4_get_red();

uint8_t hr4_is_fifo_full();

uint8_t hr4_is_new_fifo_data_ready();

uint8_t hr4_is_alc_overflow();

uint32_t hr4_read_red(void);

uint8_t hr4_is_proximity_int();

uint8_t hr4_is_powered_up();

uint8_t hr4_is_internal_temp_ready();

void hr4_fifo_full_int_enable(bool enable);

void hr4_new_fifo_data_int_enable(bool enable);

void hr4_alc_int_enable(bool enable);

void hr4_proximity_int_enable(bool enable);

void hr4_new_internal_temp_int_enable(bool enable);

void hr4_read_fifo(uint8_t *buffer);

int8_t hr4_set_fifo_sample_averaging(uint8_t sample_number);

void hr4_fifo_rollover_enable(bool enable);

int8_t hr4_set_fifo_almost_full_value(uint8_t full_value);

void hr4_shut_down_enable(bool enable);

void hr4_reset();

void read_fifo_one_sample(uint8_t *buffer);

int8_t hr4_set_mode(uint8_t mode);

int8_t hr4_set_spo2_range(uint8_t range);

int8_t hr4_set_spo2_sample_rate(uint8_t rate);

int8_t hr4_set_led_pulse_width(uint8_t pulse_width);

void hr4_set_led_pulse_amplitude(uint32_t amplitude);

void hr4_set_red_led_pulse_amplitude(uint8_t amplitude);

void hr4_set_ir_led_pulse_amplitude(uint8_t amplitude);

void hr4_set_green_led_pulse_amplitude(uint8_t amplitude);

void hr4_set_proximity_led_pulse_amplitude(uint8_t amplitude);

int16_t hr4_get_temperature();

void hr4_set_proximity_threshold(uint8_t threshold);

uint8_t hr4_get_write_pointer( void );

uint8_t hr4_get_read_pointer( void );

#endif // HEARTRATE4_HW_H

