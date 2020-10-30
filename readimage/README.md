## 注意・要修正項目

擬似的に再現という体だが、実際は指定した数だけ細い線による円が描かれるだけで、
現実世界で言うLEDの大きさは考慮されていない。

>>>変更
バーサライタの上部に表示する画像のデータ化をする。

test.cpp内のFILENAME,HEIGHT,WIDTHを表示したい画像に変更

実行後に`build/RotateLED > img2arr.txt`をしてimg2arr.txtを全コピーして
only_top.inoのtopLedDataに代入してやる。

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
