all:
	@echo "Converting header file..."
	@gcc -o batch_norm_weight batch_norm_weight.c -lm
	@./batch_norm_weight
	@gcc -o head_short head_short.c
	@./head_short
	@gcc -o pad_weight pad_weight_kernel_1_1.c
	@./pad_weight
	@gcc -o interleave_weight interleave_weight.c
	@./interleave_weight

