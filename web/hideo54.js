{
  config: {
    title: 'SunPro 2016技術書典',
    author: 'hideo54',
    email: 'admin@sunpro.io',
    description: '皆さんご存知の通り、現在Slackには、Reactionという、各投稿に対して絵文字で反応をつけられる機能があります。この機能はめちゃ便利だし楽しいのですが、付けるのが少し面倒という側面があります。たとえば、:+1:絵文字をReactionとして付けたい時には、直前の投稿に付けるならば:+1:と入力するか、そうでない場合は“Add reaction”を押して、表示された絵文字パレットからReactionとして付けたい絵文字を選択しなければいけません。個人的に、簡単な反応であればなるべくReactionで済ませたいという気持ちがありますので、頻繁に使うこの面倒なReactionをなんとか楽にできないかと考えていた結果、Reaction専用キーボードを作るという発想に至りました。',
  },
  page: {
    url: 'hideo54.html',
    plain_title: 'まだReactionで消耗してるの?',
    title: 'まだ<wbr>Reactionで<wbr>消耗してるの?',
    subtitle: 'hideo54',
    content: fs.readFileSync('../webroot/hideo54.html'),
    pdf: {
      link: 'hideo54.pdf',
      size: 0.8,
    },
    prev: {
      link: 'hakatashi.html',
      title: 'もしインターネットの1秒が1年だったら',
    },
  },
  theme: {
    'navbar-links': {
      'Home': undefined,
      'GitHub': 'https://github.com/hakatashi/SunPro-techbookfest',
    },
    footer: [{
      link: 'hiromu.html',
      title: 'ディープラーニングでご飯を作ってみる',
      icon: 'fa-cutlery',
    }, {
      link: 'hakatashi.html',
      title: 'もしインターネットの1秒が1年だったら',
      icon: 'fa-clock-o',
    }, {
      self: true,
      link: 'hideo54.html',
      title: 'まだReactionで消耗してるの?',
      icon: 'fa-thumbs-up',
    }],
    avatar: '/../../favicon.png',
    comment: {
      enable: false,
    },
    highlight: {
      enable: true,
    },
  },
  url_for: (path) => {
    if (path === undefined) {
      return './';
    } else if (path.startsWith('http')) {
      return path;
    } else {
      return `beautiful-hexo/source${path}`;
    }
  },
}
