#include <stdio.h>
//fix "_0_" --> "_1_"
#include "conv_3_weight_bn_short.h"
int INPUT_CHANNEL = 64;//fix
int OUTPUT_CHANNEL = 128;//fix
int KERNEL_DIM = 3;
int main()
{
	FILE *fp;
	fp = fopen("conv_3_weight_bn_short_pad.h","w");
	fprintf(fp,"short group_3_biases[]={");
	int i,j;
	for(i=0;i<OUTPUT_CHANNEL;i++)
	{
		if(i==OUTPUT_CHANNEL-1)
			fprintf(fp,"%hd};\n\n",conv_3_biases_bn_short[i]);
		else
			fprintf(fp,"%hd,\n",conv_3_biases_bn_short[i]);
	}

	fprintf(fp,"short group_3_weights[]={");

	for(i=0;i<OUTPUT_CHANNEL*INPUT_CHANNEL;i++)
	  {
	    for(j=0;j<KERNEL_DIM*KERNEL_DIM;j++)
	      {
		fprintf(fp,"%hd,\n",conv_3_weights_bn_short[i*KERNEL_DIM*KERNEL_DIM+j]);
	      }
	    if(i==OUTPUT_CHANNEL*INPUT_CHANNEL-1)
	      {
		fprintf(fp,"%hd,\n",0);
		fprintf(fp,"%hd,\n",0);
		fprintf(fp,"%hd};\n\n",0);
	      }
	    else
	      {
		fprintf(fp,"%hd,\n",0);
		fprintf(fp,"%hd,\n",0);
		fprintf(fp,"%hd,\n",0);
	      }
	  }
	
	return 0;
}
