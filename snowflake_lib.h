/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | Snowflake �㷨����                                                   |
  | ռλ 0 + ���뼶ʱ��41λ + ����ID 10λ + ����������12λ��             |
  | 0 - 1 - 42 - 52 - 64  = 0 + time + macheine id + increment           |
  | 1bits ռλ������                                                     |  
  | 41bits����΢��Ϊ��λ��timestamp��                                    |
  | 10bits���������úõĻ���ID,���ֻ����1023̨����ͬʱ����ID            |
  | 12bits���ۼӼ�����,Ҳ����1̨����1ms��������4095��ID��              |
  | ��Ϊʹ�õ�λ�����㣬��Ҫ64λ����ϵͳ����Ȼ���ɵ�ID���п��ܲ���ȷ.    |
  +----------------------------------------------------------------------+
  | Author: Kevin <841694874@qq.com>                                     |
  +----------------------------------------------------------------------+
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/types.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#define WORKID_WIDTH 1024

typedef struct globle
{
	int global_int:12;
	int64_t last_stamp;
	int workid;
	int seqid;
} globle;

void set_workid(int workid);
pid_t gettid( void );
uint64_t get_curr_ms();
uint64_t wait_next_ms(int64_t lastStamp);
int atomic_incr(int id);
int64_t get_unique_id();
