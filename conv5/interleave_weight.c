#include "stdio.h"
//fix "_0_" --> "_1_"
#include "conv_6_weight_bn_short_pad.h"
int N_max = 32; //max channel

int output_ch = 512; //fix
int input_fold_factor = 8;//fix

int main()
{
  FILE *fp = fopen("group_6_weight_it.h","w");//fix    " " or "_it"
  int i,j,k; //cnt
  fprintf(fp,"short group_6_biases[]={");
  for(i=0;i<sizeof(group_6_biases)/sizeof(short);i++)
    {
      fprintf(fp,"%hd,\n",group_6_biases[i]);
    }
  fseek(fp,-2,SEEK_CUR);
  fprintf(fp,"};\n\n");
  
  //int output_fold_factor = 4;
  fprintf(fp,"short group_6_weights[]={");
  for(i=0;i<input_fold_factor;i++)
    {
      for(j=0;j<output_ch;j++)
	{
	  for(k=0;k<N_max*12;k++)
	    {
	      fprintf(fp,"%hd,\n",group_6_weights[j*12*N_max*input_fold_factor+12*N_max*i+k]);
	      //printf("%d,%d,%d,%d\n",i,j,k,j*12*N_max*input_fold_factor+12*N_max*i+k);
	    }		
	}
    }
  fseek(fp,-2,SEEK_CUR);
  fprintf(fp,"};");
  fclose(fp);
  
  return 0;
}
