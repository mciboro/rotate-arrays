#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 8

bool get_bit_value(const uint8_t byte, const uint8_t offset)
{
    assert(offset < TABLE_SIZE);
    uint8_t mask = 1 << offset;
    return byte & mask;
}

void set_bit_value(uint8_t *byte, const uint8_t offset)
{
    assert(offset < TABLE_SIZE);
    uint8_t mask = 1 << offset;
    *byte |= mask;
}

void print_font(const uint8_t *table)
{
    assert(sizeof(table) * sizeof(uint8_t) == TABLE_SIZE);
    for(int index = 0; index < TABLE_SIZE; index++)
    {
        for(int offset = 0; offset < TABLE_SIZE; offset++)
        {
            printf("%c ", get_bit_value(table[index], offset) ? '*' : ' ');        
        }
        printf("\n");
    }
}

void rotate_90deg_right(uint8_t *orig_table, uint8_t *rotated_table)
{
    assert(sizeof(orig_table) == TABLE_SIZE && sizeof(rotated_table) == TABLE_SIZE);
    memset(rotated_table, 0, TABLE_SIZE);
    for(int index = 0; index < TABLE_SIZE; index++)
    {
        for(int offset = 0; offset < TABLE_SIZE; offset++)
        {
            if(get_bit_value(orig_table[index], offset))
                set_bit_value(&rotated_table[offset], (TABLE_SIZE - index - 1));
        }
    }
}

void rotate_90deg_left(uint8_t *orig_table, uint8_t *rotated_table)
{
    assert(sizeof(orig_table) == TABLE_SIZE && sizeof(rotated_table) == TABLE_SIZE);
    memset(rotated_table, 0, TABLE_SIZE);
    for(int index = 0; index < TABLE_SIZE; index++)
    {
        for(int offset = 0; offset < TABLE_SIZE; offset++)
        {
            if(get_bit_value(orig_table[index], offset))
                set_bit_value(&rotated_table[TABLE_SIZE - offset -1], index);
        }
    }
}

void rotate_180deg(uint8_t *orig_table, uint8_t *rotated_table)
{
    assert(sizeof(orig_table) == TABLE_SIZE && sizeof(rotated_table) == TABLE_SIZE);
    memset(rotated_table, 0, TABLE_SIZE);
    for(int index = 0; index < TABLE_SIZE; index++)
    {
        for(int offset = 0; offset < TABLE_SIZE; offset++)
        {
            if(get_bit_value(orig_table[index], offset))
                set_bit_value(&rotated_table[TABLE_SIZE - index - 1], TABLE_SIZE - offset - 1);
        }
    }
}

int main(void)
{
    uint8_t table[TABLE_SIZE] = {(1 << 0), (1 << 0) + (1 << 1), \
                                (1 << 0) + (1 << 2), (1 << 0) + (1 << 3), \
                                (1 << 0) + (1 << 2), (1 << 0) + (1 << 1), \
                                (1 << 0), (1 << 0)};
    uint8_t rotated_table[TABLE_SIZE];
    set_bit_value(&table[7], 7);
    
    // print original table
    print_font(table);
    printf("\n\n");
    
    // print table rotated to the right by 90 degrees
    rotate_90deg_right(table, rotated_table);
    print_font(rotated_table);
    printf("\n\n");

    // print table rotated to the left by 90 degrees
    rotate_90deg_left(table, rotated_table);
    print_font(rotated_table);
    printf("\n\n");

    // print table rotated by 180 degrees
    rotate_180deg(table, rotated_table);
    print_font(rotated_table);
    
    return 0;
}