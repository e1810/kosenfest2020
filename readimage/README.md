## 注意・要修正項目

擬似的に再現という体だが、実際は指定した数だけ細い線による円が描かれるだけで、
現実世界で言うLEDの大きさは考慮されていない。
image.jpegというファイルしか読み込めない。
また、そのファイルは**450x498のカラー画像**でないといけない。
今回は針のない時計の画像を用意したが実質この画像専用になっている。

## ビルド

```
cd build
cmake ..
make
```

## 実行

`build/RotateLED (引数)`

引数は正整数 角度ごとの光点の数を指定する。

## 参考資料
https://www.trifields.jp/how-to-install-opencv-on-ubuntu-2742
https://qiita.com/janus\_wel/items/a673793d448c72cbc95e
