const { createSideBarConfig } = require('./util')
const VUE_PATH = '/blogs/vue-base'
// const TIPS_PATH = '/blogs/tips'
// const TEST_PATH = '/blogs/test'
// const DEMO_PATH = '/blogs/demo'

module.exports = {
  [VUE_PATH]: [createSideBarConfig('vue 基础学识', VUE_PATH)],
  // [TIPS_PATH]: [createSideBarConfig('小识书屋', TIPS_PATH)],
  // [TEST_PATH]: [createSideBarConfig('测试', TEST_PATH)],
  // [DEMO_PATH]: [createSideBarConfig('demo', DEMO_PATH)],
}
