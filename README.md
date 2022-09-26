# ROMAJI conversion program

Copyright (c) 2020-2022 Windy
Version 2.0


# What is this?

昔のパソコンのエミュレータなどで、ローマ字変換を実現するためのルーチンです。

以前は、Shift JISコードに依存していましたが、UTF-8 で書き直しました。


## 使い方

OSキーイベントのキーが押されたとき、convert_romaji2kana 関数を呼んでください。

ローマ字変換が成功した時、convert_romaji2kana 関数の中の、PutAutokeyMessage 関数を呼び出す箇所で、結果が渡されるので、、エミュレータ側で、自動的に、渡されたキーコードを、押されたことにする処理を書いてください。


test.c は、テストですので、結果を１６進数と、半角カタカナで表示します。
Windows のcmd.exe で、半角カタカナは表示できます。（文字コードの設定を SHIFT JIS から変えてない場合）


## test プログラムの ビルドの仕方

Un*x 系OSだと、gcc でビルドできます。 make と打ち込んでください。

Windowsの Visual Studio では、開発者用コマンドプロンプトを開いて、nmake -f win32.mak でビルドできます。



## ライセンス

LICENSE ファイルを見てください。


## 免責事項

ソースリストは、基本的に無保証です。 テストは行っておりますが、使用した結果、何らかの損害があったとしても、当方では 一切感知できませんので、宜しくお願いします。 


