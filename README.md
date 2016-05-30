# SunPro会誌 2016年技術書典版(仮) 開発用リポジトリ

[![Build Status][travis-image]][travis-url]

[travis-image]: https://travis-ci.com/hakatashi/SunPro-techbookfest.svg?token=LBP6dMS3oXazpwBS3Fws&branch=master
[travis-url]: https://travis-ci.com/hakatashi/SunPro-techbookfest

## 開発方針

**1次締切は6月13日24:00(JST)です**

* ブランチは切らずmasterにガンガンpushしてください。
    * `--force` はダメ
* 新規記事を書き始める場合は、
    1. 新しく`(自分のid).re`を作成し、
    1. catarog.ymlのCHAPSの欄にそれを追加し、(順番は後で考えます)
    1. config.ymlのautの欄に自分のidを追加してください。
* ひとり1章です。複数ファイルへの分割も避けてください。
    * 辛くなってきたらあとからERB化とか考えます。
* 挿絵はimagesディレクトリの下に自分のidと同じフォルダを作成し、その中に置いてください。
    * 書籍版では白黒で印刷されることに注意してください。
* このリポジトリは初版発行から半年後に公開する予定なので公開できない情報をコミットしないでください。
