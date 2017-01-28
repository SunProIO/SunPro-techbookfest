  {
    config: {},
    page: {
      title: 'もし<wbr>インターネットの<wbr>1秒が<wbr>1年だったら',
      subtitle: 'hakatashi',
      content: fs.readFileSync('../hakatashi.html'),
    },
    theme: {
      'navbar-links': [],
      footer: [],
      comment: {
        enable: false,
      },
      highlight: {
        enable: true,
      },
    },
    url_for: (path) => {
      if (path === undefined) {
        return '';
      } else {
        return `beautiful-hexo/source${path}`;
      }
    },
  }
