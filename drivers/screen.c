#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include "../libc/types.h"
s32 get_screen_offset(s32 col, s32 row) { 
    return 2 * (row * MAX_COLS + col); 
}

s32 get_row_seqno(s32 offset) { 
    return offset / (2 * MAX_COLS);
}
s32 get_col_seqno(s32 offset) { 
    return (offset - (get_row_seqno(offset)*2*MAX_COLS))/2; 
}

s32 get_cursor_offset() {

   /*  The device uses its control register as an index
       to select its internal registers, of which we are
       interested in:
       reg 14: which is the high byte of the cursors offset
       Once the internal register has been selected, we may read or
       write a byte on the data register. */

   // select hight byte of internal cursor register
   port_byte_out(REG_SCREEN_CTRL, CURSOR_HB); 
   s32 offset = port_byte_in(REG_SCREEN_DATA) << 8;

   // select low byte of internal cursor register
   port_byte_out(REG_SCREEN_CTRL, CURSOR_LD);
   offset += port_byte_in(REG_SCREEN_DATA);

   // Since the cursor offset reported by the VGA hardware is the
   // number of characters, we multiply by two to convert it to
   // a character cell offset.
   return offset * 2;
}

void set_cursor_offset(s32 cursor_offset) {    
   cursor_offset /= 2; // Convert from cell offset to char offset.

   // This is similar to get_cursor_offset, only now we write
   // bytes to those internal device registers.

   // Write high byte of cursor position to register 14
   port_byte_out(REG_SCREEN_CTRL, CURSOR_HB);
   port_byte_out(REG_SCREEN_DATA, (unsigned char)(cursor_offset >> 8));
   
   // Write low byte of cursor position to register 15
   port_byte_out(REG_SCREEN_CTRL, CURSOR_LD);
   port_byte_out(REG_SCREEN_DATA, (unsigned char)(cursor_offset & 0xFF));
}

/* Advance the text cursor , scrolling the video buffer if necessary . */
s32 handle_scrolling(s32 cursor_offset) {
    // If the cursor is within the screen, return it unmodified .
    if (cursor_offset < MAX_ROWS * MAX_COLS * 2) {
        return cursor_offset;
    }

    /* Shuffle the rows back one. */
    s32 iter;
    for (iter = 0; iter < MAX_ROWS; iter += 1) {
        memory_copy(get_screen_offset(0, iter)+VIDEO_ADDRESS,
            get_screen_offset(0, iter-1)+VIDEO_ADDRESS,
            MAX_COLS*2
        );
    }
    /* Blank the last line by setting all bytes to 0 */
    char *ll = get_screen_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
    for (iter = 0; iter < MAX_COLS * 2; iter++) {
        ll[iter] = 0;
    }

    // Move the offset back one row, such that it is now on the last
    // row, rather than off the edge of the screen 
    cursor_offset -= 2 * MAX_COLS;

    return cursor_offset;
}

/* Print a char on the screen at col, row, or at cursor position */
s32 print_char(char character, s32 col, s32 row, char attribute_byte) {

   /* Create a byte (char) pointer to the start of video memory */
   unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

   /* Errors Control */
   if (col >= MAX_COLS || row >= MAX_ROWS) {
        return get_screen_offset(col, row);
    }

   /* If attribute byte is zero, assume the default style. */
   if (!attribute_byte) {
       attribute_byte = WHITE_ON_BLACK;
   }

   /* Get the video memory offset for the screen location */
   s32 offset;
   /* If col and row are non - negative, use them for offset. */

   if (col >= 0 && row >= 0) {
       offset = get_screen_offset(col, row);
       /* Otherwise, use the current cursor position. */
   } else {
       offset = get_cursor_offset();
   }

   // If we see a newline character, set offset to the end of
   // current row, so it will be advanced to the first col
   // of the next row.
   if (character == '\n') {
        row = get_row_seqno(offset);
        offset = get_screen_offset(0, row+1);
       // Otherwise, write the character and its attribute byte to
       // video memory at our calculated offset.
    }  else if (character == 0x08) { /* Backspace */
        vidmem[offset] = ' ';
        vidmem[offset+1] = attribute_byte;
    } else {
       vidmem[offset] = character;
       vidmem[offset+1] = attribute_byte;
       offset += 2;
   }

   // Update the offset to the next character cell, which is
   // two bytes ahead of the current cell.
   
   offset = handle_scrolling(offset);

   set_cursor_offset(offset);
   return offset;
}

void kprint_at(char *message, s32 col, s32 row) {
    /* Set cursor if col/row are negative */
    s32 offset;
    if (col < 0 && row < 0) {
        offset = get_cursor_offset();
        row = get_row_seqno(offset);
        col = get_col_seqno(offset);
    }

    /* Loop through message and print it */
    s32 i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        
        /* Compute row/col for next iteration */
        row = get_row_seqno(offset);
        col = get_col_seqno(offset);
    }
}

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    int row = get_row_seqno(offset);
    int col = get_col_seqno(offset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
}

void kprint(char *message) {
   kprint_at(message, -1, -1);
}

void clear_screen() {
    s32 iter;
    s32 screen_size = MAX_COLS * MAX_ROWS;

    char *screen = VIDEO_ADDRESS;
    for (iter = 0; iter < screen_size; iter += 1) {
        screen[iter*2] = ' ';
        screen[iter*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_screen_offset(0, 0));
}