# FPGA デザインコンテスト 物体認識
- Pytorchで学習した重みを、YOLOのFPGA実装のPSで読み込むCのヘッダファイルに変換します。

## 手順
1. [Pytorch](https://github.com/yarakigit/design_contest_yolo)を用いて学習
2. 重みファイル (```.pt```)のパスとクラス数を設定して、  
   ~~~bash
   $ make
   ~~~
3. 結果が```./final_output```下に配置されます。

## 参考文献
- [GitHub, matsuda-slab, MyYOLO](https://github.com/matsuda-slab/MyYOLO)
