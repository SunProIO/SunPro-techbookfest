{
  config: {
    title: 'SunPro 2016技術書典',
    author: 'SunPro',
    email: 'admin@sunpro.io',
    description: '技術書オンリーイベント「技術書典」にて発行された同人誌『SunPro会誌 2016技術書典』です。現在無料公開中。「ディープラーニングでご飯を作ってみる」「もしインターネットの1秒が1年だったら」「まだReactionで消耗してるの?」の3本でお届けします。',
  },
  page: {
    url: '',
    plain_title: '',
    subtitle: 'hakatashi / Mine02C4',
    content: fs.readFileSync('../hakatashi.html'),
    posts: [],
  },
  theme: {
    'navbar-links': {
      'Home': undefined,
      'GitHub': 'https://github.com/hakatashi/SunPro-techbookfest',
    },
    footer: [],
    avatar: '/../../favicon.png',
    comment: {
      enable: false,
    },
    highlight: {
      enable: true,
    },
    header: {
      title: 'SunPro <wbr>2016<wbr>技術書典',
      motto: '技術系よろず同人誌 (2016年6月発行)',
      bigimgs: [{
        src: '/../../cover.jpg',
        desc: '表紙',
      }],
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
