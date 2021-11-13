const { createSideBarConfig } = require('./util')
const VUE_BASE_PATH = '/blogs/vue-base'
const VUE_ADVANCE_PATH = '/blogs/vue-advance'
const C_BASE_PATH = '/blogs/c-base'

module.exports = {
  [VUE_BASE_PATH]: [createSideBarConfig('vue 基础学识', VUE_BASE_PATH), createSideBarConfig('vue 进阶学识', VUE_ADVANCE_PATH)],
  [VUE_ADVANCE_PATH]: [createSideBarConfig('vue 基础学识', VUE_BASE_PATH), createSideBarConfig('vue 进阶学识', VUE_ADVANCE_PATH)],
  [C_BASE_PATH]: [createSideBarConfig('c语言 基础学识', C_BASE_PATH)],
  // [VUE_ADVANCE_PATH]: [createSideBarConfig('vue 进阶学识', VUE_ADVANCE_PATH)],
}
