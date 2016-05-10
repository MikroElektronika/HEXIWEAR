/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef FT_GPIO_H
#define FT_GPIO_H

/** Gpio scan states
 */
enum ft_gpio_scan_states {
    FT_GPIO_MEASURED    = 0,
    FT_GPIO_IN_PROGRESS = 1,
};

/** Gpio module flags
 */
enum ft_gpio_flags {
    FT_GPIO_INTERRUPTED_FLAG = FT_FLAGS_SPECIFIC_SHIFT(0),
};

#define FT_GPIO_PORT_SHIFT (16)

/** Gpio pin name symbols. Each symbol contains a port and a pin number.
 */
enum ft_gpio_pinname {
    GPIO_PTA4 = ((0 << FT_GPIO_PORT_SHIFT) | 4),
    GPIO_PTA5 = ((0 << FT_GPIO_PORT_SHIFT) | 5),
    GPIO_PTA6 = ((0 << FT_GPIO_PORT_SHIFT) | 6),
    GPIO_PTA7 = ((0 << FT_GPIO_PORT_SHIFT) | 7),
    GPIO_PTA8 = ((0 << FT_GPIO_PORT_SHIFT) | 8),
    GPIO_PTA9 = ((0 << FT_GPIO_PORT_SHIFT) | 9),
    GPIO_PTA10 = ((0 << FT_GPIO_PORT_SHIFT) | 10),
    GPIO_PTA11 = ((0 << FT_GPIO_PORT_SHIFT) | 11),
    GPIO_PTA12 = ((0 << FT_GPIO_PORT_SHIFT) | 12),
    GPIO_PTA13 = ((0 << FT_GPIO_PORT_SHIFT) | 13),
    GPIO_PTA14 = ((0 << FT_GPIO_PORT_SHIFT) | 14),
    GPIO_PTA15 = ((0 << FT_GPIO_PORT_SHIFT) | 15),
    GPIO_PTA16 = ((0 << FT_GPIO_PORT_SHIFT) | 16),
    GPIO_PTA17 = ((0 << FT_GPIO_PORT_SHIFT) | 17),
    GPIO_PTA18 = ((0 << FT_GPIO_PORT_SHIFT) | 18),
    GPIO_PTA19 = ((0 << FT_GPIO_PORT_SHIFT) | 19),
    GPIO_PTA20 = ((0 << FT_GPIO_PORT_SHIFT) | 20),
    GPIO_PTA21 = ((0 << FT_GPIO_PORT_SHIFT) | 21),
    GPIO_PTA22 = ((0 << FT_GPIO_PORT_SHIFT) | 22),
    GPIO_PTA23 = ((0 << FT_GPIO_PORT_SHIFT) | 23),
    GPIO_PTA24 = ((0 << FT_GPIO_PORT_SHIFT) | 24),
    GPIO_PTA25 = ((0 << FT_GPIO_PORT_SHIFT) | 25),
    GPIO_PTA26 = ((0 << FT_GPIO_PORT_SHIFT) | 26),
    GPIO_PTA27 = ((0 << FT_GPIO_PORT_SHIFT) | 27),
    GPIO_PTA28 = ((0 << FT_GPIO_PORT_SHIFT) | 28),
    GPIO_PTA29 = ((0 << FT_GPIO_PORT_SHIFT) | 29),
    GPIO_PTA30 = ((0 << FT_GPIO_PORT_SHIFT) | 30),
    GPIO_PTA31 = ((0 << FT_GPIO_PORT_SHIFT) | 31),
    GPIO_PTB0 = ((1 << FT_GPIO_PORT_SHIFT) | 0),
    GPIO_PTB1 = ((1 << FT_GPIO_PORT_SHIFT) | 1),
    GPIO_PTB2 = ((1 << FT_GPIO_PORT_SHIFT) | 2),
    GPIO_PTB3 = ((1 << FT_GPIO_PORT_SHIFT) | 3),
    GPIO_PTB4 = ((1 << FT_GPIO_PORT_SHIFT) | 4),
    GPIO_PTB5 = ((1 << FT_GPIO_PORT_SHIFT) | 5),
    GPIO_PTB6 = ((1 << FT_GPIO_PORT_SHIFT) | 6),
    GPIO_PTB7 = ((1 << FT_GPIO_PORT_SHIFT) | 7),
    GPIO_PTB8 = ((1 << FT_GPIO_PORT_SHIFT) | 8),
    GPIO_PTB9 = ((1 << FT_GPIO_PORT_SHIFT) | 9),
    GPIO_PTB10 = ((1 << FT_GPIO_PORT_SHIFT) | 10),
    GPIO_PTB11 = ((1 << FT_GPIO_PORT_SHIFT) | 11),
    GPIO_PTB12 = ((1 << FT_GPIO_PORT_SHIFT) | 12),
    GPIO_PTB13 = ((1 << FT_GPIO_PORT_SHIFT) | 13),
    GPIO_PTB14 = ((1 << FT_GPIO_PORT_SHIFT) | 14),
    GPIO_PTB15 = ((1 << FT_GPIO_PORT_SHIFT) | 15),
    GPIO_PTB16 = ((1 << FT_GPIO_PORT_SHIFT) | 16),
    GPIO_PTB17 = ((1 << FT_GPIO_PORT_SHIFT) | 17),
    GPIO_PTB18 = ((1 << FT_GPIO_PORT_SHIFT) | 18),
    GPIO_PTB19 = ((1 << FT_GPIO_PORT_SHIFT) | 19),
    GPIO_PTB20 = ((1 << FT_GPIO_PORT_SHIFT) | 20),
    GPIO_PTB21 = ((1 << FT_GPIO_PORT_SHIFT) | 21),
    GPIO_PTB22 = ((1 << FT_GPIO_PORT_SHIFT) | 22),
    GPIO_PTB23 = ((1 << FT_GPIO_PORT_SHIFT) | 23),
    GPIO_PTB24 = ((1 << FT_GPIO_PORT_SHIFT) | 24),
    GPIO_PTB25 = ((1 << FT_GPIO_PORT_SHIFT) | 25),
    GPIO_PTB26 = ((1 << FT_GPIO_PORT_SHIFT) | 26),
    GPIO_PTB27 = ((1 << FT_GPIO_PORT_SHIFT) | 27),
    GPIO_PTB28 = ((1 << FT_GPIO_PORT_SHIFT) | 28),
    GPIO_PTB29 = ((1 << FT_GPIO_PORT_SHIFT) | 29),
    GPIO_PTB30 = ((1 << FT_GPIO_PORT_SHIFT) | 30),
    GPIO_PTB31 = ((1 << FT_GPIO_PORT_SHIFT) | 31),
    GPIO_PTC0 = ((2 << FT_GPIO_PORT_SHIFT) | 0),
    GPIO_PTC1 = ((2 << FT_GPIO_PORT_SHIFT) | 1),
    GPIO_PTC2 = ((2 << FT_GPIO_PORT_SHIFT) | 2),
    GPIO_PTC3 = ((2 << FT_GPIO_PORT_SHIFT) | 3),
    GPIO_PTC4 = ((2 << FT_GPIO_PORT_SHIFT) | 4),
    GPIO_PTC5 = ((2 << FT_GPIO_PORT_SHIFT) | 5),
    GPIO_PTC6 = ((2 << FT_GPIO_PORT_SHIFT) | 6),
    GPIO_PTC7 = ((2 << FT_GPIO_PORT_SHIFT) | 7),
    GPIO_PTC8 = ((2 << FT_GPIO_PORT_SHIFT) | 8),
    GPIO_PTC9 = ((2 << FT_GPIO_PORT_SHIFT) | 9),
    GPIO_PTC10 = ((2 << FT_GPIO_PORT_SHIFT) | 10),
    GPIO_PTC11 = ((2 << FT_GPIO_PORT_SHIFT) | 11),
    GPIO_PTC12 = ((2 << FT_GPIO_PORT_SHIFT) | 12),
    GPIO_PTC13 = ((2 << FT_GPIO_PORT_SHIFT) | 13),
    GPIO_PTC14 = ((2 << FT_GPIO_PORT_SHIFT) | 14),
    GPIO_PTC15 = ((2 << FT_GPIO_PORT_SHIFT) | 15),
    GPIO_PTC16 = ((2 << FT_GPIO_PORT_SHIFT) | 16),
    GPIO_PTC17 = ((2 << FT_GPIO_PORT_SHIFT) | 17),
    GPIO_PTC18 = ((2 << FT_GPIO_PORT_SHIFT) | 18),
    GPIO_PTC19 = ((2 << FT_GPIO_PORT_SHIFT) | 19),
    GPIO_PTC20 = ((2 << FT_GPIO_PORT_SHIFT) | 20),
    GPIO_PTC21 = ((2 << FT_GPIO_PORT_SHIFT) | 21),
    GPIO_PTC22 = ((2 << FT_GPIO_PORT_SHIFT) | 22),
    GPIO_PTC23 = ((2 << FT_GPIO_PORT_SHIFT) | 23),
    GPIO_PTC24 = ((2 << FT_GPIO_PORT_SHIFT) | 24),
    GPIO_PTC25 = ((2 << FT_GPIO_PORT_SHIFT) | 25),
    GPIO_PTC26 = ((2 << FT_GPIO_PORT_SHIFT) | 26),
    GPIO_PTC27 = ((2 << FT_GPIO_PORT_SHIFT) | 27),
    GPIO_PTC28 = ((2 << FT_GPIO_PORT_SHIFT) | 28),
    GPIO_PTC29 = ((2 << FT_GPIO_PORT_SHIFT) | 29),
    GPIO_PTC30 = ((2 << FT_GPIO_PORT_SHIFT) | 30),
    GPIO_PTC31 = ((2 << FT_GPIO_PORT_SHIFT) | 31),
    GPIO_PTD0 = ((3 << FT_GPIO_PORT_SHIFT) | 0),
    GPIO_PTD1 = ((3 << FT_GPIO_PORT_SHIFT) | 1),
    GPIO_PTD2 = ((3 << FT_GPIO_PORT_SHIFT) | 2),
    GPIO_PTD3 = ((3 << FT_GPIO_PORT_SHIFT) | 3),
    GPIO_PTD4 = ((3 << FT_GPIO_PORT_SHIFT) | 4),
    GPIO_PTD5 = ((3 << FT_GPIO_PORT_SHIFT) | 5),
    GPIO_PTD6 = ((3 << FT_GPIO_PORT_SHIFT) | 6),
    GPIO_PTD7 = ((3 << FT_GPIO_PORT_SHIFT) | 7),
    GPIO_PTD8 = ((3 << FT_GPIO_PORT_SHIFT) | 8),
    GPIO_PTD9 = ((3 << FT_GPIO_PORT_SHIFT) | 9),
    GPIO_PTD10 = ((3 << FT_GPIO_PORT_SHIFT) | 10),
    GPIO_PTD11 = ((3 << FT_GPIO_PORT_SHIFT) | 11),
    GPIO_PTD12 = ((3 << FT_GPIO_PORT_SHIFT) | 12),
    GPIO_PTD13 = ((3 << FT_GPIO_PORT_SHIFT) | 13),
    GPIO_PTD14 = ((3 << FT_GPIO_PORT_SHIFT) | 14),
    GPIO_PTD15 = ((3 << FT_GPIO_PORT_SHIFT) | 15),
    GPIO_PTD16 = ((3 << FT_GPIO_PORT_SHIFT) | 16),
    GPIO_PTD17 = ((3 << FT_GPIO_PORT_SHIFT) | 17),
    GPIO_PTD18 = ((3 << FT_GPIO_PORT_SHIFT) | 18),
    GPIO_PTD19 = ((3 << FT_GPIO_PORT_SHIFT) | 19),
    GPIO_PTD20 = ((3 << FT_GPIO_PORT_SHIFT) | 20),
    GPIO_PTD21 = ((3 << FT_GPIO_PORT_SHIFT) | 21),
    GPIO_PTD22 = ((3 << FT_GPIO_PORT_SHIFT) | 22),
    GPIO_PTD23 = ((3 << FT_GPIO_PORT_SHIFT) | 23),
    GPIO_PTD24 = ((3 << FT_GPIO_PORT_SHIFT) | 24),
    GPIO_PTD25 = ((3 << FT_GPIO_PORT_SHIFT) | 25),
    GPIO_PTD26 = ((3 << FT_GPIO_PORT_SHIFT) | 26),
    GPIO_PTD27 = ((3 << FT_GPIO_PORT_SHIFT) | 27),
    GPIO_PTD28 = ((3 << FT_GPIO_PORT_SHIFT) | 28),
    GPIO_PTD29 = ((3 << FT_GPIO_PORT_SHIFT) | 29),
    GPIO_PTD30 = ((3 << FT_GPIO_PORT_SHIFT) | 30),
    GPIO_PTD31 = ((3 << FT_GPIO_PORT_SHIFT) | 31),
    GPIO_PTE0 = ((4 << FT_GPIO_PORT_SHIFT) | 0),
    GPIO_PTE1 = ((4 << FT_GPIO_PORT_SHIFT) | 1),
    GPIO_PTE2 = ((4 << FT_GPIO_PORT_SHIFT) | 2),
    GPIO_PTE3 = ((4 << FT_GPIO_PORT_SHIFT) | 3),
    GPIO_PTE4 = ((4 << FT_GPIO_PORT_SHIFT) | 4),
    GPIO_PTE5 = ((4 << FT_GPIO_PORT_SHIFT) | 5),
    GPIO_PTE6 = ((4 << FT_GPIO_PORT_SHIFT) | 6),
    GPIO_PTE7 = ((4 << FT_GPIO_PORT_SHIFT) | 7),
    GPIO_PTE8 = ((4 << FT_GPIO_PORT_SHIFT) | 8),
    GPIO_PTE9 = ((4 << FT_GPIO_PORT_SHIFT) | 9),
    GPIO_PTE10 = ((4 << FT_GPIO_PORT_SHIFT) | 10),
    GPIO_PTE11 = ((4 << FT_GPIO_PORT_SHIFT) | 11),
    GPIO_PTE12 = ((4 << FT_GPIO_PORT_SHIFT) | 12),
    GPIO_PTE13 = ((4 << FT_GPIO_PORT_SHIFT) | 13),
    GPIO_PTE14 = ((4 << FT_GPIO_PORT_SHIFT) | 14),
    GPIO_PTE15 = ((4 << FT_GPIO_PORT_SHIFT) | 15),
    GPIO_PTE16 = ((4 << FT_GPIO_PORT_SHIFT) | 16),
    GPIO_PTE17 = ((4 << FT_GPIO_PORT_SHIFT) | 17),
    GPIO_PTE18 = ((4 << FT_GPIO_PORT_SHIFT) | 18),
    GPIO_PTE19 = ((4 << FT_GPIO_PORT_SHIFT) | 19),
    GPIO_PTE20 = ((4 << FT_GPIO_PORT_SHIFT) | 20),
    GPIO_PTE21 = ((4 << FT_GPIO_PORT_SHIFT) | 21),
    GPIO_PTE22 = ((4 << FT_GPIO_PORT_SHIFT) | 22),
    GPIO_PTE23 = ((4 << FT_GPIO_PORT_SHIFT) | 23),
    GPIO_PTE24 = ((4 << FT_GPIO_PORT_SHIFT) | 24),
    GPIO_PTE25 = ((4 << FT_GPIO_PORT_SHIFT) | 25),
    GPIO_PTE26 = ((4 << FT_GPIO_PORT_SHIFT) | 26),
    GPIO_PTE27 = ((4 << FT_GPIO_PORT_SHIFT) | 27),
    GPIO_PTE28 = ((4 << FT_GPIO_PORT_SHIFT) | 28),
    GPIO_PTE29 = ((4 << FT_GPIO_PORT_SHIFT) | 29),
    GPIO_PTE30 = ((4 << FT_GPIO_PORT_SHIFT) | 30),
    GPIO_PTE31 = ((4 << FT_GPIO_PORT_SHIFT) | 31),
};

#endif
