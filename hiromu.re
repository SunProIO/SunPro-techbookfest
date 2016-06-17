= ディープラーニングでご飯を作ってみる

== はじめに

こんにちは。SunProメンバーのhiromu(@hiromu1996)です。
今回は、世間で何でもできると話題になっているディープラーニングについて、
本当は何でもできるのであれば、この空いたお腹も満たしてくれようということで、
ディープラーニングでご飯を作ってみるということに挑戦してみました。

……という出落ち記事です。
実際は、ディープラーニングを使った画像生成アルゴリズムとして
最近話題になっている「Deep Convolutional Generative Adversarial Network (DCGAN)」で
ご飯の画像を生成するということに挑戦してみました。

=== 対象について

この記事では、DCGANやその実装について詳しい解説をせず、
むしろ公開されている実装をベースにして話を進める予定です。
なので、この記事の対象は、以下の3種類の方となります。

 * DCGANについてざっくりと知りたい方
 * non-rootな計算環境でTensorFlowを使う方法を知りたい方
 * ご飯の画像データセットについて知りたい方

== DCGANとは

DCGANは、Generative Adversarial Network(GAN, 敵対的生成ネットワーク)を発展させたアルゴリズムです。
もともと、GANは2014年にGoodfellowらによって提案された@<bib>{goodfellow}もので、
2つのニューラルネットワークを競い合わせることで画像生成をさせるというアルゴリズムになっています。

=== GANのアルゴリズム

GANには、GeneratorとDiscriminatorという2つのニューラルネットワークが登場します。
Generatorは、ランダムなベクトルzから画像を生成するニューラルネットワークで、
Discriminatorは、サンプルデータ(学習データ)として与えられた画像とGeneratorが生成した画像を
見分けるニューラルネットワークとして学習されます。
ここで、DiscriminatorがGeneratorの生成した画像を見分けられるようになるほど、
GeneratorはDiscriminatorが見分けられないよう、リアルな画像を生成するようになるという仕組みです。

わかりやすく例えると、Generatorは贋作画家、Discriminatorは鑑定士といえます。
贋作画家には、鑑定士を騙せるような絵を書けると報酬が与えられ、
鑑定士は、贋作を見分けることができると報酬が与えられるという風に考えることができます。

//image[dcgan][GANのアルゴリズムのイメージ]

読者の中には、なぜ2つのニューラルネットワークを使うのかと疑問に思った方もいらっしゃるかもしれません。
Discriminatorがいなくても、Generatorがそれっぽい画像を生成した時に報酬を与えるようにすればいいようにも思えます。
しかしながら、「それっぽい」という判断を下すのが非常に難しいのです。
サンプルデータと似ているかという判定基準だと、サンプルデータによく似た画像を生成できるようにはなりますが、
全くのコピーしか生成されず、新しい画像を生成することができなくなります。
しかし、Discriminatorと競い合うという形式を取ることで、どういった特徴を持っていれば
サンプルデータの仲間として判断されやすいのかということを学習することができるようになるのです。

=== DCGANのアルゴリズム

GANの問題点として、Discriminatorが強くなりすぎてしまい、Generatorが上手くならないまま学習が進んでしまうということや、
Generatorがほとんど同じような画像しか生成しなくなってしまうということが往々にしてありました。

それを解決したのが、2015年にRadfordらによって提案されたDCGAN@<bib>{radford}です。
Radfordらは、GANのアルゴリズムに畳み込みニューラルネットワークに関する最新の研究成果を組み合わせることによって、
GeneratorとDiscriminatorをバランスよく、効果的に学習させることに成功しました。

GANとの違いを細かく説明しようとすると、畳み込みニューラルネットワークとは何かという点から詳しく述べる必要があるため、
本稿では割愛しますが、Springenbergら@<bib>{springenberg}に従ってプーリング層を畳み込み層で置き換えたり、全結合層を無くしたりしています。
また、最近のニューラルネットワークでは一般的になってきたテクニックではありますが、バッチ最適化を取り入れたり、
活性化関数にGeneratorではReLU(出力層ではTanh)を、DiscriminatorではLeakyReLUを用いたりしているようです。

ただし、1つ言えるのは、ディープラーニングに関する他の研究と同様に、
なぜこうすればうまくいくのかということを正確に説明できているわけではないということです。
ここが、ディープラーニングの難しさでもあり、エンジニアリング的な側面だともいえます。

== non-rootな環境でのTensorflowの導入

では、早速DCGANを動かしてみましょうと言いたいところですが、まずはTensorflowの環境構築から始めることとしましょう。
しかし、きっと読者のみなさまの中にも、手元のPCを学習のために3日3晩もCPU 100%で稼働させておくのは厳しいし、
かといって、Amazon EC2に高額課金するのも……誰も使ってない共用サーバならあるのに、という方もいらっしゃることでしょう。

本章では、そんな方々のために、以下の環境でTensorflowの環境を作り上げる方法について紹介したいと思います。

 * OS(ディストリビューション)は、CentOS 6.5
 * Tensorflowの動作に必要なPython 2.7ではなくPython 2.6がインストールされている
 * 開発者用パッケージなどない最小構成だが、root権限もない
 * 割り当てられているホームディレクトリのquotaは3GB

=== minicondaの導入

環境構築にあたって、Python 2.7すら入っていないと聞くと絶望的に思われるかもしれませんが、
幸いなことにAnacondaというPythonとその有名なパッケージ(numpyやscipyなども含まれる)を一括で構築してくれるシステムがあります。
しかしながら、Anacondaだけでディスク容量を3GBも使用してしまうので、そのミニマル版であるminicondaを使うこととします。

minicondaのダウンロードページ(@<href>{http://conda.pydata.org/miniconda.html})から、今回はPython 2.7 Linux 64-bitを選びました。
シェルスクリプトをダウンロードして実行するだけなので簡単です。
途中でライセンスへの同意や、インストールディレクトリの確認を求められますが、基本はデフォルトのままで問題ありません。

//cmd{
# インストールスクリプトをダウンロードする
$ @<b>{https://repo.continuum.io/miniconda/Miniconda2-latest-Linux-x86_64.sh}

# インストールスクリプトを実行する
$ @<b>{bash Miniconda2-latest-Linux-x86_64.sh}

# PATHに追加します
$ @<b>{export PATH="/home/hiromu/miniconda2/bin:$PATH"}
//}

本節以降、@<code>{/home/hiromu/miniconda2}にminicondaをインストールしたものとして進めますので、
適当に読み替えてください。

=== Tensorflowのインストール

Pythonの環境が整えば、あとはTensorflowの公式ドキュメント(@<href>{https://www.tensorflow.org/versions/r0.9/get_started/os_setup.html#anaconda-installation})通りにインストールすることができます。

まずはminicondaでTensorflow用の環境を用意し、あとはpipでインストールするだけです。
//cmd{
# Tensorflow用の環境のためにopensslやzlibなどが展開される
$ @<b>{conda create -n tensorflow python=2.7}

# Tensorflow用の環境に入る
$ @<b>{source activate tensorflow}

# 今回はLinux 64-bit, CPU only, Python 2.7のパッケージを使用 (最新のURLや別バージョンについてはをドキュメントページを確認してください)
(tensorflow)$ @<b>{export TF_BINARY_URL=https://storage.googleapis.com/tensorflow/linux/cpu/tensorflow-0.9.0rc0-cp27-none-linux_x86_64.whl}

# Tensorflowのインストールの開始
(tensorflow)$ @<b>{pip install --upgrade $TF_BINARY_URL}
//}

これでインストールは完了です。
さて、早速使ってみましょう。
//cmd{
$ @<b>{python}
Python 2.7.11 |Continuum Analytics, Inc.| (default, Dec  6 2015, 18:08:32) 
   <略>
>>> import tensorflow
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/home/hiromu/miniconda2/envs/tensorflow/lib/python2.7/site-packages/tensorflow/__init__.py", line 23, in <module>
    from tensorflow.python import *
  File "/home/hiromu/miniconda2/envs/tensorflow/lib/python2.7/site-packages/tensorflow/python/__init__.py", line 48, in <module>
    from tensorflow.python import pywrap_tensorflow
  File "/home/hiromu/miniconda2/envs/tensorflow/lib/python2.7/site-packages/tensorflow/python/pywrap_tensorflow.py", line 28, in <module>
    _pywrap_tensorflow = swig_import_helper()
  File "/home/hiromu/miniconda2/envs/tensorflow/lib/python2.7/site-packages/tensorflow/python/pywrap_tensorflow.py", line 24, in swig_import_helper
    _mod = imp.load_module('_pywrap_tensorflow', fp, pathname, description)
ImportError: /lib64/libc.so.6: version `GLIBC_2.17' not found (required by /home/hiromu/miniconda2/envs/tensorflow/lib/python2.7/site-packages/tensorflow/python/_pywrap_tensorflow.so)
//}

はい、エラーが出ました……。
これは、Tensorflowが内部で使用しているバイナリに対して、CentOSのglibcのバージョンが古すぎることによって起きる問題です。
というわけで、root権限なしで新しいglibcを使う方法について検討してみましょう。

=== glibcの展開

まずは、glibc-2.17のパッケージを探すところから始めましょう。
今回は、rpmfind.netに掲載されていたCentOS 7.2向けのglibc-2.17(@<href>{http://rpmfind.net/linux/RPM/centos/updates/7.2.1511/x86_64/Packages/glibc-2.17-106.el7_2.6.x86_64.html})を使いました。

次に、このrpmを展開します。
以下の例では、minicondaがTensorflowの環境として用意したディレクトリを使用していますが、別のディレクトリを使用しても構いません。

//cmd{
# 展開用のディレクトリを作る(以降、適当に読み替えてください)
$ @<b>{cd /home/hiromu/miniconda2/envs/tensorflow}

# glibcのパッケージをダウンロードする
$ @<b>{wget ftp://fr2.rpmfind.net/linux/centos/7.2.1511/updates/x86_64/Packages/glibc-2.17-106.el7_2.6.x86_64.rpm}

# 展開する
$ @<b>{rpm2cpio glibc-2.17-106.el7_2.6.x86_64.rpm | cpio -idv}
//}

また、Tensorflowはglibc++-3.4.14も必要とするため、これも展開します。
パッケージは、同様にCentOS 7.2向けのlibstdc++-4.8.5(@<href>{https://rpmfind.net/linux/RPM/centos/7.2.1511/x86_64/Packages/libstdc++-4.8.5-4.el7.x86_64.html})を使いました。

//cmd{
# libstdc++のパッケージをダウンロードする
$ @<b>{wget ftp://fr2.rpmfind.net/linux/centos/7.2.1511/os/x86_64/Packages/libstdc++-4.8.5-4.el7.x86_64.rpm}

# 展開する
$ @<b>{rpm2cpio libstdc++-4.8.5-4.el7.x86_64.rpm | cpio -idv}
//}

これで、必要なパッケージは揃いました。
もう一度、Pythonを実行してみましょう。
ただし、展開したライブラリを使用するために少し特殊な呼び出し方をする必要があります。

//cmd{
$ @<b>{/home/hiromu/miniconda2/envs/tensorflow/lib64/ld-linux-x86-64.so.2 --library-path /home/hiromu/miniconda2/envs/tensorflow/lib64:/home/hiromu/miniconda2/envs/tensorflow/usr/lib64 /home/hiromu/miniconda2/envs/tensorflow/bin/python}
Python 2.7.11 |Continuum Analytics, Inc.| (default, Dec  6 2015, 18:08:32) 
   <略>
>>> import tensorflow
>>> 
//}

これで、正しく実行することができました。
最後に、次回以降の呼び出しを省略するために、aliasを作っておきましょう。

//cmd{
$ @<b>{alias tfpy="/home/hiromu/miniconda2/envs/tensorflow/lib64/ld-linux-x86-64.so.2 --library-path /home/hiromu/miniconda2/envs/tensorflow/lib64:/home/hiromu/miniconda2/envs/tensorflow/usr/lib64 /home/hiromu/miniconda2/envs/tensorflow/bin/python"}
//}

=== 追加のライブラリ

また、今後必要となるPythonライブラリ、scipyとPillowをインストールしておきます。

//cmd{
# scipyはビルド済みパッケージが使えるのでpipからインストール
$ @<b>{pip install scipy}

# Pillowはビルド済みパッケージが使えないのでcondaからインストール
$ @<b>{conda install pillow}
//}

== ご飯データセット

DCGANを動かす前に、サンプルとなるデータセットを用意する必要があります。
そのため、ご飯の画像がたくさん集められたデータセットを探してみましょう。

=== UEC FOOD-256

UEC FOOD-256は電気通信大学の柳井研究室が公開しているデータセットで、もともとはご飯の画像認識@<bib>{kawano}のために作られたものです。
こちらのWebページ(@<href>{http://foodcam.mobi/dataset256.html})で公開されています。

FOOD-256はその名の通り、256種類の食べ物についての画像を集めたもので、
ラーメンからたい焼き、ビールまで様々な種類があります(@<href>{http://foodcam.mobi/gallery.cgi}でプレビュー可能)。
また、特徴的なのは、焼魚定食といった複数の料理が集まった画像もあり、
焼魚や味噌汁、白飯といったそれぞれの要素がどこにあるのかという座標情報も入っています。

しかし、DCGANで生成するとなると、サンプルデータに一品のものと定食のような複数品のものが混ざっていると複雑性が増して、
学習が難しくなるのではないかと考えられます。
そこで、今回は別のデータセットを探すこととしました。

=== PFID

Pittsburgh Fast-Food Image DatasetはIntel Labs Pittsburghが公開しているデータセットで、こちらは画像特徴量のご飯を対象としたベンチマーク@<bib>{mei}のために作られたものです。
こちらのWebページ(@<href>{http://pfid.rit.albany.edu/})で公開されています。

こちらは61種類の食べ物についての画像を集めたものですが、
その名の通り、すべてファストフード店の商品の写真となっています。
マクドナルド、ケンタッキーフライドチキン、サブウェイというような13種類のチェーン店について、
ドリンクからハンバーガーやピザまでいろんな商品が集められています。
また、もう1つ特徴的なのは、普通の皿や包装紙に載せられたバージョンと、
実験室で白い壁に白い皿という背景でいろいろな角度から撮影されたのバージョンの2種類が与えられている点です。

しかし、ドリンクを除くと、ほとんどが茶色っぽい丸い物体で、多様性が少ないため、
画像生成をさせても面白くなさそうという理由で、さらに別のデータセットを探すこととしました。

=== Food 101

Food 101はチューリッヒ工科大学のコンピュータビジョン研究室が公開しているデータセットで、こちらはご飯の画像分類@<bib>{bossard}のために作られたものです。
こちらのWebページ(@<href>{https://www.vision.ee.ethz.ch/datasets_extra/food-101/})で公開されています。

こちらは101種類の食べ物についての画像を集めたものですが、
それぞれの種類ごとになんと1000枚ずつ、合計101000枚の画像が含まれています。
(tar.gzで5GBと、かなりサイズも大きいです。)
また、こちらのデータセットでは、基本的に画像の中央に料理が1つという構成になっていることから、
今回はFood 101を使用することにしました。

=== ご飯の下処理

DCGANのデータセットとして使うには、正方形に切り取った上で、64x64pxくらいにサイズを落としておくと便利です。
なので、以下の様なスクリプトで変換しておきましょう。
(ついでに、グレースケールの変な画像も混入しているので取り除いておきます。)

//emlist[変換スクリプト convert.py][python]{
import sys
from PIL import Image

for path in sys.argv[1:]:
    image = Image.open(path)

    if image.mode != 'RGB':
        print 'Error: %s' % path
        continue

    ratio = 64.0 / min(image.size)
    image.thumbnail(map(lambda x: int(x * ratio), image.size))

    x, y = map(lambda x: (x - 64) / 2, image.size)
    image.crop((x, y, x + 64, y + 64)).save(path)
//}

以下のようにして変換した後に、同じディレクトリからすべての画像にアクセスできるようにシンボリックリンクを作成しておきます。

//cmd{
# food101のimagesディレクトリで実行
$ python convert.py */*.jpg
Error: bread_pudding/1375816.jpg
Error: lasagna/3787908.jpg
Error: steak/1340977.jpg
$ ln -s */*.jpg ./
$ rm 1340977.jpg 1375816.jpg 3787908.jpg
//}

ちなみに、混入していた画像は以下の3つでした。
一見平和な父子の画像がステーキとは何か怖いものがありますね。(適当)

//image[food101][混入していた画像たち]
