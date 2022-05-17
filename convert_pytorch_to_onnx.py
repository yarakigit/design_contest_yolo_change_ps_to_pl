import model
import torch.onnx
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--weights', type=str)
parser.add_argument('--num_classes', type=int)
args = parser.parse_args()
weight_file = args.weights
cls = args.num_classes

device = "cpu"

model = model.load_model(weight_file, device, num_classes=cls)

def main():
    batch_size = 1
    #model.eval()
    dummy_input = torch.randn(1, 3, 416, 416) 
    torch.onnx.export(
        model=model,
        args=dummy_input,
        f="yolov3-tiny.onnx",
        export_params=True,
        verbose=False,
        #_retain_param_name=True,
        training=True,
        do_constant_folding=False,
        opset_version=11,
        input_names = ['input'],   
        output_names = ['output'], 
        dynamic_axes={"input":{0:"batch_size"}, "output":{0:"batch_size"}}
    ) 

main()
