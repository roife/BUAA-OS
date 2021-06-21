/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs) {
    // 0x200: the size of a sector: 512 bytes.
    int offset_begin = secno * 0x200;
    int offset_end = offset_begin + nsecs * 0x200;
    int offset_now = offset_begin;
    int offset = 0;
    int op_status = 0;
    int read = 0;
    int can_read = 0;

    while (offset_begin + offset < offset_end) {
        offset_now = offset_begin + offset;

        // set diskno
        if (syscall_write_dev(&diskno, 0x13000010, 4) != 0) user_panic("write failed!\n");
        // set offset
        if (syscall_write_dev(&offset_now, 0x13000000, 4) != 0) user_panic("write failed!\n");
        // set value
        if (syscall_write_dev(&read, 0x13000020, 4) != 0) user_panic("write failed!\n");
        // --- reading ---

        // get status
        if (syscall_read_dev(&op_status, 0x13000030, 4) != 0) user_panic("write failed!\n");
        if (op_status == 0) user_panic("read failed!\n");

        // get data
        if (syscall_read_dev(dst + offset, 0x13004000, 0x200) != 0) user_panic("read failed\n");

        offset += 0x200;
    }
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs) {
    int offset_begin = secno * 0x200;
    int offset_end = offset_begin + nsecs * 0x200;
    int offset_now = offset_begin;
    int offset = 0;
    int op_status = 0;
    int write = 1;
    int can_read = 0;

    writef("diskno: %d\n", diskno);

    while (offset_begin + offset < offset_end) {
        offset_now = offset_begin + offset;

        // set diskno
        if (syscall_write_dev(&diskno, 0x13000010, 4) != 0) user_panic("write failed!\n");
        // set offset
        if (syscall_write_dev(&offset_now, 0x13000000, 4) != 0) user_panic("write failed!\n");
        // write data
        if (syscall_write_dev(src + offset, 0x13004000, 0x200) != 0) user_panic("read failed!\n");
        // set value
        if (syscall_write_dev(&write, 0x13000020, 4) != 0) user_panic("write failed!\n");
        // --- writing ---

        // get status
        if (syscall_read_dev(&op_status, 0x13000030, 4) != 0) user_panic("write failed!\n");
        if (op_status == 0) user_panic("read failed!\n");

        offset = offset + 0x200;
    }
}

