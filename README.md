# ROMAJI conversion program

Copyright (c) 2020-2022 Windy
Version 2.0


# What is this?

昔のパソコンのエミュレータなどで、ローマ字変換を実現するためのルーチンです。

以前は、Shift JISコードに依存していましたが、UTF-8 で書き直しました。


## 使い方

最初に、romaji_init() 関数で、初期化をしてください。
OSキーイベントのキーが押されたとき、romaji_convert_romaji2kana 関数を呼んでください。

ローマ字変換が成功した時、romaji_convert_romaji2kana 関数は、HENKAN_SUCCESS か、HENKAN_SUCCESS_LTU を返却するので、
romaji_get_result(）関数で、変換結果を取得してください。変換結果は半角ひらがなになっています。
カタカナに変換したい場合は、romaji_convertKana2Katakana()関数を呼び出してください。

変換結果を取得したら、エミュレータ側で、自動的に、キーを押されたことにする処理を走らせてください。


test.c は、テストですので、結果を１６進数と、半角カタカナで表示します。
Windows のcmd.exe で、半角カタカナは表示できます。
または、UTF8 で表示したい場合は、-utf8 オプションをつけて起動してください。


## test プログラムの ビルドの仕方

Un*x 系OSだと、gcc でビルドできます。 make と打ち込んでください。

Windowsの Visual Studio では、開発者用コマンドプロンプトを開いて、nmake -f win32.mak でビルドできます。



## ライセンス

LICENSE ファイルを見てください。


## 免責事項

ソースリストは、基本的に無保証です。 テストは行っておりますが、使用した結果、何らかの損害があったとしても、当方では 一切感知できませんので、宜しくお願いします。 


