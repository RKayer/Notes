#include "delay.h"

/**
 * @function ´ÖÂÔºÁÃëÑÓÊ±
 */
void delay_ms(uint16_t ms) {
    uint16_t i;
    uint8_t j;
    for(i = 0; i < ms; i ++) {
        for(j = 0; j < 110; j ++);
    }
}
