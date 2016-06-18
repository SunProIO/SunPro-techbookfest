= まだReactionで消耗してるの? (仮)

//raw[|latex|\\chapterauthor{hideo54}]

//lead{
リード文をここに書く
//}

== @<tt>{:about_me:}

こんにちは、SunProメンバーの1人、hideo54です。灘高校で高校2年生をしながら、いろいろ遊んでいます。
最近だとiOSやWebで動くようなプログラミングを好んでいます。
あと、この記事の内容も該当しますが、工作とプログラミングを絡めたい時にはRaspberry Piを愛用しています。(そういえば, 前回のSunPro会誌でもRPiを使って遊ぶ記事を書きました@<fn>{sunpro-hideo}。無料公開していますのでぜひ。)

//footnote[sunpro-hideo][@<href>{https://sunpro.io/c89/pub/hideo/ch01}]

===[column] 自己紹介リンクいろいろ

    * Twitter: @<href>{https://twitter.com/hideo54, @hideo54}
    * Homepage: @<href>{https://hideo54.com}
    * Blog: @<href>{https://blog.hideo54.com}
    * Wishlist: @<href>{https://wishlist.hideo54.com}
    * E-mail: contact@hideo54.com

===[/column]

== @<tt>{:introduction:}

さて、本題に入りたいと思います。

皆さんご存知の通り、現在Slackには、Reactionという、各投稿に対して絵文字で反応をつけられる機能があります@<fn>{reactions}。
//footnote[reactions][@<href>{https://get.slack.help/hc/en-us/articles/206870317-Emoji-reactions}]
この機能はめちゃ便利だし楽しいのですが、付けるのが少し面倒という側面があります。
たとえば、@<tt>{:+1:}絵文字をReactionとして付けたい時には、直前の投稿に付けるならば@<tt>{+:+1:}と入力するか、そうでない場合は“Add reaction”を押して、表示された絵文字パレットからReactionとして付けたい絵文字を選択しなければいけません。

個人的に、簡単な反応であればなるべくReactionで済ませたいという気持ちがありますので、頻繁に使うこの面倒なReactionをなんとか楽にできないかと考えていた結果、@<strong>{Reaction専用キーボードを作る}という発想に至りました。

== @<tt>{:plan:}

「キーボード 自作」とかでググればやたらArduinoでしてやったぜ記事が出てくるのですが、Arduinoに疎くRaspberry Piに慣れている身なので、Raspberry Piでなんとかできないかと考えました。(そのうちちゃんとArduinoも触っておきたい…。)

やり方として、マイコンチップを使ってどやこやしてUSBキーボードを作り特定マシンに接続して文字入力、という手も考えはしたのですが、設計が非常に面倒くさい上、接続先マシンでSlackを選択状態にしておく必要があります。これではメリットが薄くなりますので、マシンに接続して文字入力をするようなUSBキーボードではなく、ボタンを押したらSlack APIを叩いてReactionを送信、という形をとることにしました。

というわけで、仕様をまとめるとこんな感じです:

    * ボタンやらなんやらを置いた基盤を用意し、Raspberry PiのGPIOピンと接続する
    @<comment>{* メッセージを受信したら液晶に文字列を表示}
    @<comment>{時間なさそうなので、もし間に合えばということで…}
    * 特定のボタンが押されたら、そのボタンに割り当てられたReactionを送信

Slackメッセージの送受信には、Real Time Messaging API@<fn>{rtm-doc}を使います。

//footnote[rtm-doc][@<href>{https://api.slack.com/rtm}]

== @<tt>{:postscript:}

これは文章でした。
