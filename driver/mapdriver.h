/****
 * mapdriver.h
 *
 * Mostly macros and prototypes for the ASCII character device
 * driver.
 *
 * CREDITS:
 *   o Many parts of the driver code has to be credited to
 *     Ori Pomerantz, in his chardev.c (Copyright (C) 1998-1999)
 *
 *     Source:  The Linux Kernel Module Programming Guide (specifically,
 *              http://www.tldp.org/LDP/lkmpg/2.6/html/index.html)
 */

#ifndef _MAP_DRIVE_DEVICE_H
#define _MAP_DRIVE_DEVICE_H


/* The necessary header files */

/* Standard in kernel modules */
#include <linux/kernel.h>   /* We're doing kernel work */
#include <linux/module.h>   /* Specifically, a module */

/* For character devices */
#include <linux/fs.h>       /* The character device
                             * definitions are here
                             * */
#include <linux/ioctl.h>

#include <asm/uaccess.h>  /* for put/get_user */
#include "common.h"
/* Return codes */
#define SUCCESS      0


/* Device Declarations **************************** */

/* The maximum length of the message from the device */
#define DRV_BUF_SIZE 80

#define BSIZE             100
#define size              BSIZE * BSIZE

/* The name for or device, as it will appear
 * in /proc/devices
 */
#define DEVICE_NAME  "/dev/asciimap"
 
typedef struct _driver_status
{	
	/* Is the device open right now? Used to prevent
	 * concurent access into the same device
	 */
	bool  busy;

	/* The message the device will give when asked */
	char  buf[DRV_BUF_SIZE];

	/* How far did the process reading the message
	 * get? Useful if the message is larger than the size
	 * of the buffer we get to fill in device_read.
	 */
	char* buf_ptr;

	/* The major device number for the device.
	 */
	int   major;

	/* The minor device number for the device.
	 */
	int   minor;
	
	/*The map buffer*/
	char mapBuffer[size];
	
	/*map buffer pointer*/
	char buffPos;
	
} driver_status_t;


/*
 * Driver funcitons' prototypes
 */
static int device_open(struct inode*, struct file*);
static int  device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);
int device_ioctl(struct inode*, struct file*, unsigned int, unsigned long);
static loff_t device_lseek(struct file*, loff_t, int);

/* Kernel module-related */

/* Module Declarations ***************************** */


/* This structure will hold the functions to be
 * called when a process does something to the device
 * we created. Since a pointer to this structure is
 * kept in the devices table, it can't be local to
 * init_module. NULL is for unimplemented functions.
 */
struct file_operations Fops =
{
	NULL,   /* owner */
	device_lseek,   /* seek */
	device_read,
	device_write,
	NULL,   /* readdir */
	NULL,   /* poll/select */
	device_ioctl,   /* ioctl */
	NULL,   /* mmap */
	device_open,
	NULL,   /* flush */
	device_release  /* a.k.a. close */
};

int init_module(void);
void cleanup_module(void);

int width = 0;
int height = 0;
char static_buffer[] = "engkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammse\nengkammsengkammsengkammsengkammsengkammsengkammsQ\n";

int mapSize = 0;

#endif /* _MAP_DRIVE_DEVICE_H */
