// const int NOC_MASTER = 0;
// #include <string.h>
// #include <machine/spm.h>
// #include <machine/patmos.h>
// #include <stdio.h>
// #include "libnoc/noc.h"
// #include "libcorethread/corethread.h"

// // void blink(int nblinks);

// // void master(void);

// // void slave(void* param);

// /*/////////////////////////////////////////////////////////////////////////
// // Main application
// /////////////////////////////////////////////////////////////////////////*/

// // int main() {
// // 	int slave_param = 1;

// // 	// Clear scratch pad in all cores
// // 	// 16+16 integers
// // 	int i;
// // 	for(i = 0; i < get_cpucnt()*4; i++) {
// // 		*(NOC_SPM_BASE+i) = 0;
// // 		*(NOC_SPM_BASE+get_cpucnt()*4+i) = 0;
// // 	}

// // 	for(int i = 0; i < get_cpucnt(); i++) {
// // 		if (i != NOC_MASTER) {
// // 			int ct = i;
// // 			int corethread_res = corethread_create(ct,&slave,(void*)slave_param); //wait for cores to initialize, otherwise corethreads are not created.
// // 			while(corethread_res == EAGAIN ){
// // 				printf("Corethread %d not created\n",i);
// // 				corethread_res = corethread_create(ct,&slave,(void*)slave_param);
// // 				if (corethread_res == 0)
// // 				{
// // 					printf("Corethread %d created\n",i);
// // 					break;
// // 				}
// // 			}
// // 		}
// // 	}

// // 	master();

// // 	int* ret;
// // 	for (int i = 0; i < get_cpucnt(); ++i) {
// // 		if (i != NOC_MASTER) {
// // 			corethread_join(i,(void**)&ret);
// // 			//printf("Slave %d joined\n",i);
// // 		}
// // 	}

// //   	return 0;
// // }

// // void blink(int nblinks) {

// // 	volatile _SPM int *led_ptr = (volatile _SPM int *) PATMOS_IO_LED;

// // 	// Blinking lights
// //         int k, i, j;
// //         for (k = 0; k < nblinks; k++)
// //         {
// //             //UART_DATA = '1';
// //             for (i=2000; i!=0; --i)
// //                 for (j=2000; j!=0; --j)
// //                     *led_ptr = 1;

// //             //UART_DATA = '0';
// //             for (i=2000; i!=0; --i)
// //                 for (j=2000; j!=0; --j)
// //                     *led_ptr = 0;

// //         }
// // 	return;
// // }

// // void master(void) {
// // 	//blink(6);

// // 	volatile _SPM char *spm_base = (volatile _SPM char *) NOC_SPM_BASE;		//0
// // 	volatile _SPM char *spm_slave_1 = spm_base+get_cpucnt()*16;	 			//64
// //     volatile _SPM char *spm_slave_2 = spm_base+get_cpucnt()*32;	 			//80
// //     volatile _SPM char *spm_slave_3 = spm_base+get_cpucnt()*48;	 			//96

// // 	// message to be send
// //     const char *msg_snd = "Hello slaves coreid:0";
// // 	char msg_rcv_1[22];
// //     char msg_rcv_2[22];
// //     char msg_rcv_3[22];

// // 	// put message to spm
// // 	int i;
// // 	for (i = 0; i < 21; i++) {
// // 		*(spm_base+i) = *(msg_snd+i);
// // 	}
// // 	//*(spm_base+i) = '\0';

// // 	puts("MASTER: sending\n");

// // 	// send message
// // 	noc_write(1, spm_slave_1, spm_base, 21, 0); //21 bytes
// //     noc_write(2, spm_slave_2, spm_base, 21, 0); //21 bytes
// //     noc_write(3, spm_slave_3, spm_base, 21, 0); //21 bytes

// // 	puts("MASTER: message sent: ");
// // 	puts(msg_snd);
// // 	puts("\n");

// // 	// wait and poll
// // 	while(1) {
// //         blink(6);
// //         puts("MASTER: finished polling\n");

// //             // received message
// //         puts("MASTER: message received from slave 1:");
// //         // copy message to static location and print
// //         for (i = 0; i < 21; i++) {
// //             msg_rcv_1[i] = *(spm_slave_1+i);
// //         }
// //         msg_rcv_1[i] = '\0';

// //         puts(msg_rcv_1);

// //                 puts("MASTER: message received from slave 2:");
// //         // copy message to static location and print
// //         for (i = 0; i < 21; i++) {
// //             msg_rcv_2[i] = *(spm_slave_2+i);
// //         }
// //         msg_rcv_2[i] = '\0';

// //         puts(msg_rcv_2);

// //                 puts("MASTER: message received from slave 3:");
// //         // copy message to static location and print
// //         for (i = 0; i < 21; i++) {
// //             msg_rcv_3[i] = *(spm_slave_3+i);
// //         }
// //         msg_rcv_3[i] = '\0';

// //         puts(msg_rcv_3);
// //     }
// // 	return;
// // }

// // void slave(void* param) {

// // 	volatile _SPM char *spm_base = (volatile _SPM char *) NOC_SPM_BASE; 			//0
// //     volatile _SPM char *spm_slave_1 = spm_base+get_cpucnt()*16;	 			//64
// //     volatile _SPM char *spm_slave_2 = spm_base+get_cpucnt()*32;	 			//80
// //     volatile _SPM char *spm_slave_3 = spm_base+get_cpucnt()*48;	 			//96

// // 	// PROCESS : add ID to sum_id
// // 	//*(spm_slave+20) = *(spm_slave+20) + get_cpuid();

// // 	// send to next slave
// // 	//int rcv_id = (get_cpuid()==(get_cpucnt()-1))? 0 : get_cpuid()+1;

// //     if(get_cpuid() == 1){

// //             // wait and poll until message arrives
// //         while(*(spm_slave_1+20) == 0) {;}

// //         // put message for master to spm
// //         const char *msg = "Hello master ";
// //         int i;
// //         for (i = 0; i < 12; i++) {
// //             *(spm_slave_1+i) = *(msg+i);
// //         }

// //         *(spm_slave_1+20) = get_cpuid() + '0';

// //         noc_write(NOC_MASTER, spm_slave_1, spm_slave_1, 21, 0);

// //     }else if(get_cpuid() == 2){

// //                     // wait and poll until message arrives
// //         while(*(spm_slave_2+20) == 0) {;}

// //         // put message for master to spm
// //         const char *msg = "Hello master ";
// //         int i;
// //         for (i = 0; i < 12; i++) {
// //             *(spm_slave_2+i) = *(msg+i);
// //         }

// //         *(spm_slave_2+20) = get_cpuid() + '0';

// //         noc_write(NOC_MASTER, spm_slave_2, spm_slave_2, 21, 0);

// //     }else if(get_cpuid() == 3)
// //     {

// //                     // wait and poll until message arrives
// //         while(*(spm_slave_3+20) == 0) {;}

// //         // put message for master to spm
// //         const char *msg = "Hello master ";
// //         int i;
// //         for (i = 0; i < 12; i++) {
// //             *(spm_slave_3+i) = *(msg+i);
// //         }

// //         *(spm_slave_3+20) = get_cpuid() + '0';

// //         noc_write(NOC_MASTER, spm_slave_3, spm_slave_3, 21, 0);

// //     }

// // 	return;
// // }
