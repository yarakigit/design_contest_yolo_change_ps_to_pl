#include <stdio.h>
//fix "_before-num_" --> "_after-num_"
#include "conv_10_weight_bn_short.h"
int INPUT_CHANNEL = 512;//fix
int OUTPUT_CHANNEL = 256;//fix

int main()
{
	FILE *fp;
	fp = fopen("conv_10_weight_bn_short_pad.h","w");
	fprintf(fp,"short group_10_biases[]={");
	int i;
	for(i=0;i<OUTPUT_CHANNEL;i++)
	{
		if(i==OUTPUT_CHANNEL-1)
			fprintf(fp,"%hd};\n\n",conv_10_biases_bn_short[i]);
		else
			fprintf(fp,"%hd,\n",conv_10_biases_bn_short[i]);
	}

	fprintf(fp,"short group_10_weights[]={");

	for(i=0;i<OUTPUT_CHANNEL*INPUT_CHANNEL;i++)
	{

			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);

			fprintf(fp,"%hd,\n",conv_10_weights_bn_short[i]);


			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);

			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);
			fprintf(fp,"%hd,\n",0);


	}
	fseek(fp,-2,SEEK_CUR);
	fprintf(fp,"};\n");

	return 0;
}
