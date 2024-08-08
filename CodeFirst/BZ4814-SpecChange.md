# Title: Introduce a Random Number Generator (RNG) PPI

## Status: Draft

## Document: UEFI Platform Initialization Specification Version 1.9

## License

SPDX-License-Identifier: CC-BY-4.0

## Submitter: [TianoCore Community](https://www.tianocore.org)

## Summary of the change

Introduce a Random Number Generator (RNG) PPI to provide a standard binary interface for a platform PEIM to provide
RNG services to other PEIMs. Similar to the RNG Protocol defined in the UEFI 2.10 Specification, the RNG PPI returns
random numbers and can serve as an entropy source for seeding other cryptographic services. The RNG PPI interface is
proposed to use the same interface as the protocol for API consistency and implementation reuse.

## Benefits of the change

Security has evolved in modern firmware implementations to necessitate supporting technologies that depend on strong
entropy sources such as key derivation functions, signature schemes, initialization vectors, and other cryptographic
services. More content is expected to be secure at rest, in transit, and in use. Interaction with microcontrollers
and peripherals is increasingly growing and demanding secure communication between components. In addition, random
numbers strengthen recent security mitigations being adopted in PEI phase modules such as dynamically generated stack
cookie values.

At the same time, secure software supply chain practices are gaining adoption with an emphasis on software inventory
management and software bill of materials (SBOM) generation. This lends to more binary distribution alongside an
accompanying SBOM especially for security sensitive components such as the platform RNG provider. RNG technologies
also vary across architecture, vendor, and computing segments. A platform may need to provide RNG services in PEI
across binary boundaries and that can be accomplished with the RNG PPI.

## Impact of the change

Because this change is introducing an entirely new API, there will not be any impact on existing implementations. An
instance of the `RngLib` will be provided that instead of statically linking RNG code directly will locate and use the
RNG PPI. As is always the case for dynamic interfaces like PPIs, platform integrators will need to account for
dependencies between the PEIM that produces the RNG PPI and the PEIMs that consume it.

## Detailed description of the change [normative updates]

### Specification Changes

In PI Specification v1.9: Vol. 1, "Optional Additional PPIs", a new section would be introduced to define the RNG
PPI.

If the RNG PPI were fully defined duplicating information the RNG Protocol definition in the UEFI Specification,
it may be presented as shown below. **Feedback is welcome on the preferred way to present the RNG PPI definition
details with respect to the UEFI Specification.**

#### Random Number Generator PPI

This section defines the Random Number Generator (RNG) PPI. This PPI is used to provide random numbers for use in
PEI modules, or as an entropy source for seeding other random number generators. Consumers of the PPI can query
information about the RNG algorithms supported by the driver, and request random numbers from the driver.

When a Deterministic Random Bit Generator (DRBG) is used on the output of a (raw) entropy source, its security level
must be at least 256 bits.

The RNG PPI interface is the same as the RNG Protocol interface defined in the UEFI Specification.

##### RNG_PPI

**Summary**

This PPI provides standard RNG functions. It can be used to provide random bits for use in applications, or
entropy for seeding other random number generators.

**GUID**

```c
#define RNG_PPI_GUID \
{ 0xeaed0a7e, 0x1a70, 0x4c2b,\
  {0x85, 0x58, 0x37, 0x17, 0x74, 0x56, 0xd8, 0x06}}
```

**PPI Structure**

```c
typedef struct _RNG_PPI {
  EFI_RNG_GET_INFO            GetInfo
  EFI_RNG_GET_RNG             GetRNG;
}  RNG_PPI;
```

**Parameters**

`GetInfo`
Returns information about the random number generation implementation.

`GetRNG`
Returns the next set of random numbers.

**Description**

This PPI allows retrieval of RNG values from another PEIM. The *GetInfo* service returns information about the RNG
algorithms the driver supports. The *GetRNG* service creates a RNG value using an (optionally specified) RNG algorithm.

###### RNG_PPI.GetInfo

**Summary**

Returns information about the random number generation implementation.

**Prototype**

```c
typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_INFO) (
  IN RNG_PPI                 *This,
  IN OUT UINTN                   *RNGAlgorithmListSize,
  OUT EFI_RNG_ALGORITHM          *RNGAlgorithmList
);
```

**Parameters**

`This`

A pointer to the *RNG_PPI* instance.

`RNGAlgorithmListSize`

On input, the size in bytes of *RNGAlgorithmList.* On output with a return code of *EFI_SUCCESS,* the size in bytes of
the data returned in *RNGAlgorithmList.*

On output with a return code of *EFI_BUFFER_TOO_SMALL,* the size of *RNGAlgorithmList* required to obtain the list.

`RNGAlgorithmList`

A caller-allocated memory buffer filled by the driver with one *EFI_RNG_ALGORITHM* element for each supported RNG
algorithm. The list must not change across multiple calls to the same driver. The first algorithm in the list is the
default algorithm for the driver.

**Description**

This function returns information about supported RNG algorithms.

A driver implementing the RNG PPI need not support more than one RNG algorithm, but shall support a minimum of one
RNG algorithm.

**Related Definitions**

```c
typedef EFI_GUID EFI_RNG_ALGORITHM;
```

**Status Codes Returned**

| Status           | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| EFI_SUCCESS      | The RNG algorithm list was returned successfully.                           |
| EFI_UNSUPPORTED  | The service is not supported by this driver.                                |
| EFI_DEVICE_ERROR | The list of algorithms could not be retrieved due to a hardware or firmware error. |
| EFI_BUFFER_TOO_SMALL | The buffer *RNGAlgorithmList* is too small to hold the result.               |

###### RNG_PPI.GetRNG

**Summary**

Produces and returns an RNG value using either the default or specified RNG algorithm.

**Prototype**

```c
typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_RNG) (
  IN RNG_PPI                 *This,
  IN EFI_RNG_ALGORITHM           *RNGAlgorithm, OPTIONAL
  IN UINTN                       RNGValueLength,
  OUT UINT8                      *RNGValue
);
```

**Parameters**

`This`

A pointer to the *RNG_PPI* instance.

`RNGAlgorithm`

A pointer to the *EFI_RNG_ALGORITHM* that identifies the RNG algorithm to use. May be NULL in which case the function
will use its default RNG algorithm.

`RNGValueLength`

The length in bytes of the memory buffer pointed to by *RNGValue.* The driver shall return exactly this number of
bytes.

`RNGValue`

A caller-allocated memory buffer filled by the driver with the resulting RNG value.

**Description**

This function fills the RNGValue buffer with random bytes from the specified RNG algorithm. The driver must not reuse
random bytes across calls to this function. It is the caller’s responsibility to allocate the *RNGValue* buffer.

**Status Codes Returned**

| Status           | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| EFI_SUCCESS      | The RNG value was returned successfully.                                    |
| EFI_UNSUPPORTED  | The algorithm specified by *RNGAlgorithm* is not supported by this driver.  |
| EFI_DEVICE_ERROR | An RNG value could not be retrieved due to a hardware or firmware error.    |
| EFI_NOT_READY    | There is not enough random data available to satisfy the length requested by *RNGValueLength.* |
| EFI_INVALID_PARAMETER | RNGValue is null or RNGValueLength is zero.                             |

##### EFI RNG Algorithm Definitions

**Summary**

The *RNG PPI* identifies algorithms by an *EFI_GUID* value as defined in the *UEFI Specification*.

##### RNG References

"EFI RNG Algorithm Definitions," UEFI Specification (<https://uefi.org/specifications>), Version 2.10, Section 37.5.4.

NIST SP 800-90, "Recommendation for Random Number Generation Using Deterministic Random Bit Generators," March 2007.
See "Links to UEFI-Related Documents" (<http://uefi.org/uefi>) under the heading "Recommendation for Random Number
Generation Using Deterministic Random Bit Generators".

NIST, "Recommended Random Number Generator Based on ANSI X9.31 Appendix A.2.4 Using the 3-Key Triple DES and AES
Algorithms," January 2005. See "Links to UEFI-Related Documents" (<http://uefi.org/uefi>) under the heading
"Recommended Random Number Generator Based on ANSI X9.31".

### Code Changes

- Introduce a new module `RngPei` in `SecurityPkg` that produces the `RNG_PPI` interface.
  - Similar to `RngDxe`, this module will consume an instance of `RngLib` to provide the actual RNG services.
  - This should allow significant code reuse for platforms already using that `RngLib` instance today in PEI.
- Introduce a new `RngLib` library instance called `PeiRngLib` in `MdePkg` that locates and uses `RNG_PPI`.
  - As platforms adopt the RNG PPI, they should link the `RngLib` instance that implements RNG to `RngPei` and
    this instance to all other PEIMs (similar in DXE usage today).
- `Rng.h` will be introduced in `MdePkg/Include/Ppi` to define the `RNG_PPI` interface. It will use the same
  definitions from `MdePkg/Include/Protocol/Rng.h`.
