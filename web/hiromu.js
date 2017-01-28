{
  config: {
    title: 'SunPro 2016技術書典',
    author: 'hiromu',
    email: 'admin@sunpro.io',
    description: 'こんにちは。SunProメンバーのhiromu(@hiromu1996)です。今回は、世間で何でもできると話題になっているディープラーニングについて、本当は何でもできるのであれば、この空いたお腹も満たしてくれようということで、ディープラーニングでご飯を作ってみるということに挑戦してみました。……という出落ち記事です。実際は、ディープラーニングを使った画像生成アルゴリズムとして最近話題になっている「Deep Convolutional Generative Adversarial Network (DCGAN)」でご飯の画像を生成するということに挑戦してみました。',
  },
  page: {
    plain_title: 'ディープラーニングでご飯を作ってみる',
    title: 'ディープ<wbr>ラーニングで<wbr>ご飯を<wbr>作ってみる',
    subtitle: 'hiromu',
    content: fs.readFileSync('../hiromu.html'),
    pdf: {
      link: 'hiromu.pdf',
      size: 8.2,
    },
    next: {
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
      self: true,
      link: '/../../hiromu.html',
      title: 'ディープラーニングでご飯を作ってみる',
      icon: 'fa-cutlery',
    }, {
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
