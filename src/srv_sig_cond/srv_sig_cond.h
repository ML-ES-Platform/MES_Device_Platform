#ifndef SRV_SIG_COND_H_
#define SRV_SIG_COND_H_

int srv_sig_cond_fifo_push_float(float data, float *buff, int buff_size);
int srv_sig_cond_buff_copy_float(float *buff_src, float *buff_dst, int buff_size);
int srv_sig_cond_buff_sort_float(float *buff, int buff_size );
float srv_sig_cond_buff_wavg_float(float *buff_data, float *buff_weight, int buff_size );




int srv_sig_cond_print_buff_float(float* buff, int buff_size);


#endif