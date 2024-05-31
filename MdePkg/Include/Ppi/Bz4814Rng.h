/** @file
  The Random Number Generator (RNG) PPI is used to provide random bits for use
  in PEIMs, or entropy for seeding other random number generators.

  Copyright (c) Microsoft Corporation.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef BZ4814_RNG_PPI_H_
#define BZ4814_RNG_PPI_H_

#include <Protocol/Rng.h>

///
/// Global ID for the Random Number Generator PPI
///
#define BZ4814_RNG_PPI_GUID \
  { \
    0xeaed0a7e, 0x1a70, 0x4c2b, { 0x85, 0x58, 0x37, 0x17, 0x74, 0x56, 0xd8, 0x06 } \
  }

typedef EFI_RNG_PROTOCOL BZ4814_RNG_PPI;

extern EFI_GUID  gBz4814EfiRngPpiGuid;

#endif
