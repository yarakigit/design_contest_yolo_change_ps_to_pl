PARAM_FILE  = ./sample/yolo-tiny.pt
NUM_CLASSES = 2

all: pytorch_to_onnx extract_onnx mv_yolo convert_format copy

pytorch_to_onnx: $(PARAM_FILE)
	python convert_pytorch_to_onnx.py --weights $(PARAM_FILE) --num_classes $(NUM_CLASSES)

extract_onnx: 
	python extract_onnx.py --num_classes $(NUM_CLASSES)

convert_format:
	@for i in `seq 0 12`; do \
		make -C conv$$i; \
	done

copy:
	cp -f ./conv*/group_*_weight*.h ./final_output/.

clean:
	rm -rf conv*/*.h final_output/* conv*/batch_norm_weight conv*/head_short conv*/interleave_weight conv*/pad_weight ./*.pyc ./*.onnx __pycache__ ./utils/__pycache__

mv_yolo:
	mv ./conv9/conv_9_weight.h ./conv9/conv_10_weight_bn.h
	mv ./conv12/conv_12_weight.h ./conv12/conv_13_weight_bn.h
