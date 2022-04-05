
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "commons.h"

// These are the core buffer definitions, since the buffer is of fixed size
// CB_SIZE has been statically defined to be 128 in commons.h


uint8_t cb_buffer[2][CB_SIZE];
uint8_t read_index[2] = {0,0};
uint8_t write_index[2] = {0,0};
uint8_t end_index[2] = {CB_SIZE,CB_SIZE};


// -------------------------------------------------------CB-FIFO-ENQUEUE-----------------------------------------------------------------------
size_t cbfifo_enqueue(int buff_no,void *buf, size_t nbyte)
{
    // checking if the input buffer data is null
    if (buf == NULL)
        return -1;
    // type casting the data to uint8_t to make it compatible and generic
    uint8_t *data = buf;
    int i;
    // only when write index is behind end index, data is enqueued
    for (i = 0; i < nbyte && write_index[buff_no] < end_index[buff_no]; i++)
    {
        cb_buffer[buff_no][write_index[buff_no]++] = *data++;
    }
    // type casting the number of bytes written
    return (size_t)i;
}
// -------------------------------------------------------CB-FIFO-DEQUEUE-----------------------------------------------------------------------
size_t cbfifo_dequeue(int buff_no,void *buf, size_t nbyte)
{
    // null buffer pointer check
    if (buf == NULL)
        return -1;

    uint8_t *data = buf;

    int i;

    for (i = 0; i < nbyte; i++)
    {
        // When read_index equals write index all the elements have been dequeued
        if (read_index[buff_no] == write_index[buff_no])
        {
            goto next_step;
        }
        // writing the data back into the write buffer from the cb buffer
        *data++ = cb_buffer[buff_no][i];
        // incrementing the read buffer to account for dequeued elements
        read_index[buff_no]++;
    }
    // In this step the buffer is reset such that remaining elements are brought back to the
    // beginning of the buffer. Alternate algorithm to doing the wrapped subtraction.
next_step:
    if (write_index[buff_no] > read_index[buff_no])
    {
        size_t temp_write_index = write_index[buff_no];
        for (int j = 0; j < temp_write_index - read_index[buff_no]; j++)
        {
            cb_buffer[buff_no][j] = cb_buffer[buff_no][j + read_index[buff_no]];
        }
        // resetting the write index to the new buffer which has been reset
        write_index[buff_no] = write_index[buff_no] - read_index[buff_no];
    }
    // In case of write_index being same as the read index, all the elements have been dequeued and both point at the first location
    else if (write_index[buff_no] == read_index[buff_no])
    {
        write_index[buff_no] = 0;
    }
    // resetting read index to 0 everytime since remaining elements are brought back to starting from the first location
    read_index[buff_no] = 0;

    return (size_t)i;
}
// -------------------------------------------------------CB-FIFO-LENGTH---------------------------------------------------------------------
size_t cbfifo_length(int buff_no)
{
    // because of the dequeue reset function everytime the length of the buffer will be same as the write index
    return (size_t)(write_index[buff_no]);
}
// -------------------------------------------------------CB-FIFO-CAPACITY-----------------------------------------------------------------------
size_t cbfifo_capacity()
{
    // buffer size has been statically allocated to be 128 bytes in commons.h
    return (size_t)CB_SIZE;
}
// -----------------------------------------------------------END-----------------------------------------------------------------------
void cbfifo_reset(int buff_no)
{
    read_index[buff_no] = 0;
    write_index[buff_no] = 0;
}