# SunPro会誌 2016技術書典

[![Build Status][travis-image]][travis-url]

[travis-image]: https://travis-ci.com/hakatashi/SunPro-techbookfest.svg?token=LBP6dMS3oXazpwBS3Fws&branch=master
[travis-url]: https://travis-ci.com/hakatashi/SunPro-techbookfest

[![](https://sunpro.io/techbookfest/cover.jpg)](https://sunpro.io/techbookfest/)

2016年6月25日に開催された技術書オンリーイベント「技術書典」にて頒布された、技術系よろず同人誌『SunPro会誌 2016技術書典』のソースリポジトリです。

## 読む

* [HTML版 (sunpro.io)](https://sunpro.io/techbookfest/)
* [BOOTH](https://sunpro.booth.pm/items/277203)
* [Releases](https://github.com/hakatashi/SunPro-techbookfest/releases)

## 開発に必要なソフト

* Ruby
* LaTeX
* Git LFS

## インストール

    cd /path/to/SunPro-techbookfest
    git lfs pull
    bundle install

## ビルド

### PDFをビルド

    bundle exec rake pdf

### EPUBをビルド

    bundle exec rake epub

### HTMLをビルド

    bundle exec rake html_all
    cd web
    npm install
    npm run build
