const sidebar = require('./siderbar.js');

module.exports = {
  title: '听雨の小屋',
  description: "人生如白纸，何不记录生活的五彩墨迹",
  dest: "public",
  base: "/",
  head: [
    [
      "link",
      // {
      //   rel: "icon",
      //   href: "/logo.jpg"
      // }
    ],
    [
      "meta",
      {
        name: "viewport",
        content: "width=device-width,initial-scale=1,user-scalable=no"
      }
    ]
  ],
  plugins: ["@vuepress-reco/vuepress-plugin-comments", "vuepress-plugin-meting"],
  theme: "reco",
  themeConfig: {
    mode: 'light',
    subSidebar: 'auto',
    valineConfig: {
      appId: 'h6i7vXvVEK37fFFwb1DtMJ6W-gzGzoHsz',
      appKey: 'cYI3hypnGAI00CPuzhNfeY8Q',
    },
    nav: [
      {
        text: "主页",
        link: "/",
        icon: "reco-home"
      },
      {
        text: "时间线",
        link: "/timeline/",
        icon: "reco-date"
      },
      {
        text: "Contact",
        icon: "reco-message",
        items: [
          {
            text: "GitHub",
            link: "https://github.com/7tingyu",
            icon: "reco-github"
          }
        ]
      }
    ],
    sidebar,
    type: "blog",
    blogConfig: {
      category: {
        location: 2,
        text: "目录索引"
      },
      tag: {
        location: 3,
        text: "标签索引"
      }
    },
    friendLink: [
      {
        title: "vuepress-theme-reco",
        desc: "A simple and beautiful vuepress Blog & Doc theme.",
        avatar: "https://vuepress-theme-reco.recoluan.com/icon_vuepress_reco.png",
        link: "https://vuepress-theme-reco.recoluan.com"
      }
    ],
    logo: "/logo.png",
    search: true,
    searchMaxSuggestions: 10,
    lastUpdated: "Last Updated",
    author: "听雨",
    authorAvatar: "/avatar.jpg",
    record: "xxxx",
    startYear: "2020"
  },
  markdown: {
    lineNumbers: true
  }
}
