#include "test.h"
#include "pmm.h"  
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h>
#include <string.h> 
void Test_BasicAllocation() {
    kprintf("Basic Allocation...\n");
    
    char* ptr = (char*)KMalloc(4096);
    if (ptr == NULL) { 
        kprintf("FAIL: Allocation failed to return valid coordinates.\n"); 
        return; 
    }

    memset(ptr, 0xDE, 4096);
    
    for(int i = 0; i < 64; i++) {
        if ((uint8_t)ptr[i] != 0xDE) {
            kprintf("FAIL: Memory corruption detected at byte %d\n", i);
            return;
        }
    }
    
    kprintf("SUCCESS: Basic Allocation and Write verified.\n");
}
