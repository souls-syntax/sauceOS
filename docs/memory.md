## Notes
2026-02-20

## Current Implementation

BMalloc currently allocates from a single memory section (index 6).
This is a temporary bootstrap allocator used before full memory
enumeration is implemented.

Assumptions:
- Section 6 is guaranteed usable by bootloader memory map.
- No cross-section allocation yet.
- Fragmentation handling is ignored.


### Representation of the section(maybe)

```C
struct section {
    uint64_t* base;
    uint64_t length
};
```
Represents a contiguous usable physical memory region.

base   : physical start address
length : Lenght of the buddy. in bytes

## Failure Model

BMalloc returns NULL when:
- section capacity exhausted
- no next section implemented yet

Caller must treat NULL as non-fatal during early boot.

## Boot Environment

Memory map provided by Limine.
Only USABLE regions are considered.
Paging not yet enabled.

## Future Ideas / Hypothesis:

Maybe what i could do is add all the section in a NULL terminated array. 
Then when we get NULL from BMalloc we check if the array is over if not then go to next section and 
try once again. Tho it feels slightly less efficeint actually no cause we will keep the size of the 
length same as we would have found it to be so jump should have been seamless. Will have to verify ,
also likely this is going to make the free memory super headache inducing.
