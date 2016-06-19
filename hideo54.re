= まだReactionで消耗してるの?

//raw[|latex|\\chapterauthor{hideo54}]

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
    * 特定のボタンが押されたら、そのボタンに割り当てられたReactionを送信

Slackメッセージの送信には、Real Time Messaging API@<fn>{rtm-doc}を使います。

//footnote[rtm-doc][@<href>{https://api.slack.com/rtm}]

== @<tt>{:design:}

Reactionボタンを作ります。今回使用するものは以下のとおりです:

    * Raspberry Pi
    * SDカード
    * ブレッドボード
    * 押しボタンスイッチ(1回路1接点) 4つ
    * 抵抗

まず、SDカードにRaspbian Jessieをインストール@<fn>{raspbian-install}し、Raspberry Piに入れて起動します。JessieベースのRaspbianは、Wheezyと違ってGPIOの制御にroot権限が必要ないという長所もあるのです。

//footnote[raspbian-install][@<href>{https://www.raspberrypi.org/downloads/raspbian/}にDLリンクがあります。インストール方法は適当にぐぐってください。]

ブレッドボードに各スイッチを刺し、抵抗を通すようにして適当に配線します。

@<img>{wiring}は配線例です。狭いブレッドボードを使ったので、配線がややわかりにくい感がありますが、許してください。

//image[wiring][配線例]{
//}

@<img>{wiring}では、11, 13, 15, 16番目のピンをそれぞれのスイッチに割り当てています。次章のソースコードでも、この配線を前提としたものを掲載しています。

実物の写真も用意しました。こんな感じです。

//image[pic][実物写真]{
//}

(ボタンの様子が見えやすいように、配線図と上下が逆になるように撮りました。)

== @<tt>{:code:}

実装めんどくさいな〜、と思うところですが、ありがたいことに有志が作ったライブラリがたくさんあります@<fn>{library}。(感謝)
//footnote[library][@<href>{https://api.slack.com/community}]

今回は、僕が一番手馴れているPythonで書きたいと思ったので、python-slackclient@<fn>{python-slackclient}を使うことにしました。pipなどでインストールすると良いでしょう。
//footnote[python-slackclient][@<href>{https://github.com/slackhq/python-slackclient}]

というわけで書いたコードがこちらです。

//emlistnum[ボタンを押すとReactionが送信されるコード(Python3)][python]{
import time
import RPi.GPIO as GPIO
from slackclient import SlackClient

# Slack
token = 'xoxp-1234567890a-1234567890a-1234567890a-1234567890'
sc = SlackClient(token)

# Buttons
reactions = {11:'+1', 13:'weary', 15:'wakaru', 16:'uke'}
GPIO.setmode(GPIO.BOARD)
GPIO.setup(list(reactions.keys()), GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
def add_selected_reactions(sc, channel_id, ts):
    for button in reactions.keys():
        if GPIO.input(button):
            reaction = reactions[button]
            sc.api_call('reactions.add', name=reaction, channel=channel_id, timestamp=ts)

if sc.rtm_connect():
    latest_message = None
    while True:
        res = sc.rtm_read()
        for item in res:
            item_type = item.get('type')
            if item_type == 'hello':
                print('Connected successfully.')
            elif item_type == 'message':
                if latest_message != item:
                    latest_message = item
            else:
                pass
        if latest_message is not None:
            add_selected_reactions(sc, latest_message['channel'], latest_message['ts'])
        time.sleep(1)
else:
    print('Connection failed.')
//}

4行目のtokenは、OAuth Test Tokens@<fn>{test-token}から取得します。
10行目のreactionsは、keyに使用するピン番号、valueに対応するEmojiの名前をとる辞書です。ここでは、僕が所属している灘校パソコン研究部@<fn>{npca}のSlackにあるReactionのうち、この4つがあればなんとかなるかな、というものを選んでいます。

Reactionの追加は、python-slackclientのapi_callメソッドを使用しまんま該当するSlack API@<fn>{api}を叩いています(17行目)。

//footnote[test-token][@<href>{https://api.slack.com/docs/oauth-test-tokens}]
//footnote[npca][@<href>{http://www.npca.jp/}]
//footnote[api][@<href>{https://api.slack.com/methods/reactions.add}]

これをRaspberry Pi上で実行しておけば、ボタンが押されていると、そのボタンに対応したReactionを付加するようになります!(ただしインターネット接続が必要)

ボタンが押されているかどうかを1秒毎に見ているので、最大で1秒押し続ける必要がありますが、叩いているのは追加メソッドなので、複数命令が送られてもReactionが取り消されることはないようになっています。

== @<tt>{:postscript:}

と、まあ、以上です。
実際は、さらにRPiにディスプレイ付けて、受信したメッセージを選択してReactionを付けるなど、より実用的なものを作りたかったのですが、記事の締め切り直前に作業を始めたため、さすがにそこまでは行きませんでした…。(大げさなタイトルの割に単純なものに仕上がってしまった…)

曰く「かなり許されない部類」のギリギリ提出になってしまったものの記事を待ち続けてくれた編集長のhakatashiには深く感謝しています…!

余談ですが、hakatashiにSlackで「hideoの記事、機械学習でSlackのメッセージに自動でReactionつけるみたいな記事かと思ったら全然違った」と言われました。それも一瞬考えていたので、またそのうちやりたいですね。

何かあれば、冒頭で書いたTwitterアカウントやメールアドレスまでご連絡ください。ここまで読んでくださってありがとうございました!
