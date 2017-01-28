  {
    config: {
      title: 'SunPro 技術書典',
      author: 'SunPro',
      email: 'admin@sunpro.io',
    },
    page: {
      title: 'もし<wbr>インターネットの<wbr>1秒が<wbr>1年だったら',
      subtitle: 'hakatashi',
      content: fs.readFileSync('../hakatashi.html'),
    },
    theme: {
      'navbar-links': [],
      footer: [],
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
      } else {
        return `beautiful-hexo/source${path}`;
      }
    },
  }
