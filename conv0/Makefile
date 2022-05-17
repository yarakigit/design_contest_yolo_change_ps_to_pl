all:
	@echo "Converting header file..."
	@gcc -o batch_norm_weight batch_norm_weight.c -lm
	@./batch_norm_weight
	@gcc -o head_short head_short.c
	@./head_short
	@gcc -o pad_weight pad_weight.c
	@./pad_weight
	@cp -rf conv_0_weight_bn_short_pad.h group_0_weight.h

