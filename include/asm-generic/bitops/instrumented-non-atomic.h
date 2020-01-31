/* SPDX-License-Identifier: GPL-2.0 */

/*
 * This file provides wrappers with sanitizer instrumentation for non-atomic
 * bit operations.
 *
 * To use this functionality, an arch's bitops.h file needs to define each of
 * the below bit operations with an arch_ prefix (e.g. arch_set_bit(),
 * arch___set_bit(), etc.).
 */
#ifndef _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H
#define _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H

#include <linux/kasan-checks.h>

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
static inline void __set_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	arch___set_bit(nr, addr);
}

/**
 * __clear_bit - Clears a bit in memory
 * @nr: the bit to clear
 * @addr: the address to start counting from
 *
 * Unlike clear_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
static inline void __clear_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	arch___clear_bit(nr, addr);
}

/**
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to change
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
static inline void __change_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	arch___change_bit(nr, addr);
}

/**
 * __test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
static inline bool __test_and_set_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	return arch___test_and_set_bit(nr, addr);
}

/**
 * __test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
static inline bool __test_and_clear_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	return arch___test_and_clear_bit(nr, addr);
}

/**
 * __test_and_change_bit - Change a bit and return its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
static inline bool __test_and_change_bit(long nr, volatile unsigned long *addr)
{
	kasan_check_write(addr + BIT_WORD(nr), sizeof(long));
	return arch___test_and_change_bit(nr, addr);
}

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline bool test_bit(long nr, const volatile unsigned long *addr)
{
	kasan_check_read(addr + BIT_WORD(nr), sizeof(long));
	return arch_test_bit(nr, addr);
}

#endif /* _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H */