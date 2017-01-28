{
  config: {
    title: 'SunPro 技術書典',
    author: 'hakatashi / Mine02C4',
    email: 'admin@sunpro.io',
    description: '2016年、インターネットが日本中のあらゆる人間に行き渡るようになってから、すでに10年単位の時間が経過しています。今日においてインターネットを支えるネットワーク技術が重要であることは言うまでもありませんが、実際にネットワークでどのタイミングで何が起こり、どれくらいの時間が費やされるのかということを身を持って体感している人は、たとえネットワークに精通している人でも少ないのではないでしょうか？この記事では、1秒というわずかな時間を1年にまで拡大し、ネットワーク上で何が起こっているかを人間スケールでざっくりと解説していきます。',
  },
  page: {
    plain_title: 'もしインターネットの1秒が1年だったら',
    title: 'もし<wbr>インターネットの<wbr>1秒が<wbr>1年だったら',
    subtitle: 'hakatashi / Mine02C4',
    content: fs.readFileSync('../hakatashi.html'),
    prev: {
      link: 'hiromu.html',
      title: 'ディープラーニングでご飯を作ってみる',
    },
    next: {
      link: 'hideo54.html',
      title: 'まだReactionで消耗してるの?',
    },
  },
  theme: {
    'navbar-links': {
      'Home': undefined,
      'GitHub': 'https://github.com/hakatashi/SunPro-techbookfest',
    },
    footer: [{
      link: '/../../hiromu.html',
      title: 'ディープラーニングでご飯を作ってみる',
      icon: 'fa-cutlery',
    }, {
      self: true,
      link: '/../../hakatashi.html',
      title: 'もしインターネットの1秒が1年だったら',
      icon: 'fa-clock-o',
    }, {
      link: '/../../hideo54.html',
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
