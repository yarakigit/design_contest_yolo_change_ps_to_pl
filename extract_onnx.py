import onnx, onnx.numpy_helper
import numpy as np
import sys
import re
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--num_classes', type=int)
args = parser.parse_args()

cls = args.num_classes
default_cls=80
default_ch = 5 # x,y,w,h,s_obj
valid_ch = default_ch + cls

conv_dict = {
    ".bn.weight"       :"scales",
    ".bn.bias"         :"biases",
    ".bn.running_mean" :"rolling_mean",
    ".bn.running_var"  :"rolling_variance",
    ".conv.weight"    :"weights"
}
conv_dict_non_bn = {
    ".conv.weight":"weights_bn",
    ".conv.bias":"biases_bn"
}

def main():
    model = onnx.load('yolov3-tiny.onnx')
    weights = model.graph.initializer

    print_line = "\n{:<2s} | {:<30s} | {:<15s}".format("","weight.name","weight.dims")
    print(print_line)
    temp_str = "----------------------------------------------------------------------"
    before_layer_cnt = -1

    yolo_layer_set = [9,12]
    for i,weight in enumerate(weights):
        now_layer_cnt = int((re.search('[0-9]+', str(weight.name)).group()))
        now_layer_cnt -= 1
        if not now_layer_cnt == before_layer_cnt:
            print(temp_str)
            file = open("conv"+str(now_layer_cnt)+"/conv_"+str(now_layer_cnt)+"_weight.h","w")
        print_line = "{:<2s} | {:<30s} | {:<15s}".format(str(now_layer_cnt),str(weight.name),str(weight.dims))
        print(print_line)
        before_layer_cnt = now_layer_cnt
    
        if now_layer_cnt in yolo_layer_set:
            layer_type = re.sub("conv*.\d","",str(weight.name),1)
            np_weights = onnx.numpy_helper.to_array(weights[i])
            if conv_dict_non_bn[".conv.bias"]==conv_dict_non_bn[layer_type]:
                np_weights_default = np.zeros([(default_ch+default_cls)*3+1])
            elif conv_dict_non_bn[".conv.weight"]==conv_dict_non_bn[layer_type]:
                np_weights_default = np.zeros([int((default_ch+default_cls)*3+1),int(weight.dims[1]),1,1])
            for j in range(3):
                np_weights_default[0+(default_ch+default_cls)*j:valid_ch+(default_ch+default_cls)*j] = np_weights[0+valid_ch*j:valid_ch+valid_ch*j]
            make_headflie(now_layer_cnt+1,conv_dict_non_bn[layer_type],file,np_weights_default)
        else:
            layer_type = re.sub("conv*.\d","",str(weight.name),1)
            np_weights = onnx.numpy_helper.to_array(weights[i])
            make_headflie(now_layer_cnt,conv_dict[layer_type],file,np_weights)
    print(temp_str)

    ## onnx format to numpy sample                      ## 
    ## weights = onnx.numpy_helper.to_array(weights[0]) ##

def make_headflie(layer_num, weight_type, file, weights):
    if weights.ndim ==4:
        file.write("float conv_"+str(layer_num)+"_"+weight_type+"["+str(weights.shape[0]*weights.shape[1]*weights.shape[2]*weights.shape[3])+"] ={")
        weights = np.ravel(weights)
    elif weights.ndim ==1:
        file.write("float conv_"+str(layer_num)+"_"+weight_type+"["+str(weights.shape[0])+"] ={")
    for out_ch  in range(weights.shape[0]):
        if not out_ch+1 == weights.shape[0]:
            file.write(str(weights[out_ch])+",\n")
        else:
            file.write(str(weights[out_ch])+"};\n")
    
            
if __name__ == "__main__":
    main()
