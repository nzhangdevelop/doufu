#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <pthread.h>

struct fbinfo {
	char * fb_mem;
	unsigned long xres;
	unsigned long yres;
	long int screensize;
};

inline static unsigned short int make16color(unsigned char r, unsigned char g, unsigned char b)
{
	return ((((r>>3)&31)<<11) | (((g>>2)&63)<<5) | ((b>>3)&31));
}

void *thread1(void *pdata);

pthread_t thread[2];

int main(int argc, char *argv[])
{
	int result = -1;
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char *fbp = 0;
	int x = 0, y = 0;
	int guage_height = 20, step = 10;
	long int location = 0;
	struct fbinfo* pfb = NULL;
	
	pfb = (struct fbinfo*)malloc(sizeof(struct fbinfo));
	memset(pfb, 0, sizeof(struct fbinfo));
	
	// Open the file for reading and writing
	fbfd = open("/dev/graphics/fb0", O_RDWR);
	if (!fbfd) {
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}
	printf("The framebuffer device was opened successfully.\n");

	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		exit(2);
	}
	// Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information.\n");
		exit(3);
	}

	printf("length of frame buffer memory: %d.\n", finfo.smem_len);
	printf("numbers of buffers: %d.\n", finfo.smem_len/vinfo.xres/vinfo.yres/4);
	printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );
	printf("xoffset:%d, yoffset:%d, line_length: %d\n", vinfo.xoffset, vinfo.yoffset, finfo.line_length );
	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;;
	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fbfd, 0);
	
	if ((int)fbp == -1) {
		printf("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
	pfb->fb_mem = fbp;
	pfb->xres = vinfo.xres;
	pfb->yres = vinfo.yres;
	pfb->screensize = screensize;
	
	//set to black color first
	//memset(fbp, 0, screensize);
	printf("Debug Begin!\n");
	
	long int i = 0, j = 0;
	for (i = 0; i < vinfo.xres; i++)
	{
		//*(fbp + 4*i) = 255;
		//*(fbp + 4*i + 1) = 255;
		//*(fbp + 4*i + 2) = 255;
		//*(fbp + 4*i + 3) = 0;
		printf("%02x %02x %02x %02x\n", *(fbp+200*vinfo.xres+4*i), *(fbp+200*vinfo.xres+4*i+1), *(fbp+200*vinfo.xres+4*i+2), *(fbp+200*vinfo.xres+4*i+3));
	}
	printf("Debug Completed!\n");
	/*
	if ((result = pthread_create(&thread[0], NULL, thread1, (void*)pfb)) != 0)
	{
		printf(" create thread failed.\n");
		return result;
	}
	else
	{
		printf("thread1 create ok! thread[0] = %d.\n", thread[0]);
	}
	//wait for thread exit.
	if (thread[0] != 0)
	{
		pthread_join(thread[0], NULL);
		printf("thread1 exit.\n");
	}*/
	
	munmap(fbp, screensize);
	close(fbfd);
	return 0;
}

void *thread1(void *pdata)
{
	struct fbinfo* pfbinfo = (struct fbinfo*)pdata;
	int i = 10;
	while (i > 0)
	{
		i--;
		printf("thread1 is running...\n");
		memset(pfbinfo->fb_mem, i*25, pfbinfo->screensize);
		sleep(1);
	}
	return 0;
}
