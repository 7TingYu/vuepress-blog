const sidebar = require('./siderbar.js');

module.exports = {
  title: "听雨の小屋",
  description: "人生如白纸，何不记录生活的五彩墨迹",
  dest: "dist",
  base: "/",
  head: [
    [
      "meta",
      {
        name: "viewport",
        content: "width=device-width,initial-scale=1,user-scalable=no",
      },
    ],
  ],
  plugins: [
    "@vuepress-reco/vuepress-plugin-comments",
    "vuepress-plugin-meting",
  ],
  theme: "reco",
  themeConfig: {
    mode: "light",
    subSidebar: "auto",
    valineConfig: {
      appId: "DfvwhrxlThMXJccy5zFQcUTv-gzGzoHsz",
      appKey: "etS7iob4efrfwWmTsNfxrID7",
    },
    nav: [
      {
        text: "主页",
        link: "/",
        icon: "reco-home",
      },
      {
        text: "时间线",
        link: "/timeline/",
        icon: "reco-date",
      },
      // {
      //   text: "Contact",
      //   icon: "reco-message",
      //   items: [
      //     {
      //       text: "GitHub",
      //       link: "https://github.com/7tingyu",
      //       icon: "reco-github",
      //     },
      //   ],
      // },
    ],
    sidebar,
    type: "blog",
    blogConfig: {
      category: {
        location: 2,
        text: "目录索引",
      },
      tag: {
        location: 3,
        text: "标签索引",
      },
    },
    friendLink: [
      {
        title: "vuepress-theme-reco",
        desc: "A simple and beautiful vuepress Blog & Doc theme.",
        avatar:
          "https://vuepress-theme-reco.recoluan.com/icon_vuepress_reco.png",
        link: "https://vuepress-theme-reco.recoluan.com",
      },
    ],
    codeTheme: "solarizedlight",
    logo: "/images/config/logo.png",
    search: true,
    searchMaxSuggestions: 10,
    lastUpdated: "Last Updated",
    author: "听雨",
    authorAvatar: "/images/config/avatar.png",
    startYear: "2020",
  },
  markdown: {
    lineNumbers: true,
  },
  configureWebpack: {
    resolve: {
      alias: {
        "@assies": "assies",
      },
    },
  },
};
