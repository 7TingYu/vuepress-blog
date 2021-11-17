const fs = require('fs');
const path = require('path');

const getFile = (prefixPath) => {
  return fs.readdirSync(path.join(process.cwd(), prefixPath))
    .map(item => `${prefixPath}/${item.replace('.md', '')}`)
}

const createSideBarConfig = ({ title, prefixPath, collapsable = true }) => {
  return {
    title,
    collapsable,
    children: getFile(prefixPath)
  }
}


// [VUE_BASE_PATH]: [
//   createSideBarConfig({ title: 'vue 基础学识', prefixPath: VUE_BASE_PATH }),
//   createSideBarConfig({ title: 'vue 进阶学识', prefixPath: VUE_ADVANCE_PATH })
// ],

/**
 * 生成多个侧边栏
 * type sideBar = {title: String, prefixPath: String, collapsable?: Boolean}
 * @param {*} sideBars Array<sideBar>
 * @returns Object
 */
const createSideBarsConfig = (sideBars) => {
  const options = {}

  const sideBarsOptions = sideBars.map(sideBar => createSideBarConfig(sideBar))

  for(const item of sideBars){
    options[item.prefixPath] = sideBarsOptions
  }

  return options
}

module.exports = {
  createSideBarConfig,
  createSideBarsConfig
}