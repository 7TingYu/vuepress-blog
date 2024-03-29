const { createSideBarConfig, createSideBarsConfig } = require("./util");

module.exports = {
  ...createSideBarsConfig([
    { title: "vue 基础学识", prefixPath: "/blogs/vue-base" },
    { title: "vue 进阶学识", prefixPath: "/blogs/vue-advance" },
  ]),
  ...createSideBarsConfig([
    { title: "react 基础学识", prefixPath: "/blogs/react-base" },
    { title: "react Hook", prefixPath: "/blogs/react-hook" },
  ]),
  ...createSideBarsConfig([
    { title: "c语言 c 基础", prefixPath: "/blogs/c-base" },
    { title: "c语言 数据结构", prefixPath: "/blogs/c-data-structure" },
    { title: "c语言 c++ 基础", prefixPath: "/blogs/c++-base" },
  ]),
  ...createSideBarsConfig([
    { title: "英语 先导课", prefixPath: "/blogs/English-base" },
  ]),
  ...createSideBarsConfig([
    { title: "数学 先导课", prefixPath: "/blogs/Math-base" },
  ]),
  ...createSideBarsConfig([{ title: "政治", prefixPath: "/blogs/political" }]),
  ...createSideBarsConfig([
    { title: "interview", prefixPath: "/blogs/interview" },
  ]),
  ...createSideBarsConfig([{ title: "门徒", prefixPath: "/blogs/mentu" }]),
  ...createSideBarsConfig([{ title: "小识书屋", prefixPath: "/blogs/tips" }]),
  ...createSideBarsConfig([
    { title: "threejs 基础", prefixPath: "/blogs/threejs-base" },
  ]),
};
